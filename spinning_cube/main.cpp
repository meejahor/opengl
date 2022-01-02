// On linux compile with:
// g++ -std=c++17 main.cpp glad/src/glad.c -I./glad/include -o prog -lSDL2 -ldl
// On windows compile with (if using mingw)
// g++ main.cpp ./glad/src/glad.c -I./glad/include -o prog.exe -lmingw32 -lSDL2main -lSDL2

// https://stackoverflow.com/questions/31933141/opengl-es2-black-screen-c-osx-sdl2

// C++ Standard Libraries
#include <iostream>

// Third-party library
#include <SDL.h>
// #include <GL/glew.h>
// #include <SDL_opengl.h>
#define GL_SILENCE_DEPRECATION
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "load_shader.hpp"
#include "model.hpp"

// Include GLAD
// #include <glad/glad.h>

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_GLContext context;

GLuint vertexArray;
GLuint vertexBuffer;
GLuint normalBuffer;
GLuint shader;

glm::mat4 projectionMatrix;
glm::mat4 viewMatrix;

Uint64 timeNow = SDL_GetPerformanceCounter();
Uint64 timeLast = 0;
float deltaTime = 0;

void initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not be initialized: " << SDL_GetError();
    } else {
        std::cout << "SDL video system is ready to go\n";
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,24);

    window = SDL_CreateWindow(
        "C++ SDL2 Window",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,
        800,
        SDL_WINDOW_SHOWN
        );

    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
        );

    context = SDL_GL_CreateContext(window);
}

void setShaderMatrix(const char* name, glm::f32* matrix) {
    unsigned int matrixID = glGetUniformLocation(shader, name);
    std::cout << matrixID << std::endl;
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, matrix);
}

void initGL() {
    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 5.0f);
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);

    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); 
    glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
    glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

    viewMatrix = glm::lookAt(
        cameraPos,
        cameraTarget,
        cameraUp
        );

    projectionMatrix = glm::perspective(glm::radians(70.0f), 800.0f/800.0f, 0.0001f, 1000.0f);

    glEnable(GL_DEPTH_TEST);  
}

int main(int argc, char* argv[]) {

    Model* m = new Model("cube.obj");

    if (!m->valid) {
        std::cout << "Error loading model." << std::endl;
        return 0;
    }

    initSDL();
    initGL();

    shader = loadShader("vert.vert", "frag.frag");
    setShaderMatrix("mat4_view", glm::value_ptr(viewMatrix));
    setShaderMatrix("mat4_projection", glm::value_ptr(projectionMatrix));

    glGenBuffers(1, &vertexBuffer);
    // glGenBuffers(1, &normalBuffer);

    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    // unsigned long sizeofVertices = sizeof(glm::vec3) * m->out_vertices.size();
    // unsigned long sizeofNormals = sizeof(glm::vec3) * m->out_normals.size();

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m->out_vertices.size(), m->out_vertices.data(), GL_STATIC_DRAW);
    // glBufferSubData(GL_ARRAY_BUFFER, 0, sizeofVertices, m->out_vertices.data());
    // glBufferSubData(GL_ARRAY_BUFFER, sizeofVertices, sizeofNormals, m->out_normals.data());

    // glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m->out_normals.size(), m->out_normals.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3)*2, (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3)*2, (void*)sizeof(glm::vec3));

    // GLint posIndex = glGetAttribLocation(shader, "aPos");
    // GLint normalIndex = glGetAttribLocation(shader, "aNormal");

    bool gameIsRunning = true;
    float rotation = 0;
    const float SPEED = 90;

    while (gameIsRunning) {

        timeLast = timeNow;
        timeNow = SDL_GetPerformanceCounter();
        deltaTime = (float)((timeNow - timeLast) / (double)SDL_GetPerformanceFrequency());

        glViewport(0, 0, 800, 800);

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                gameIsRunning = false;
            }
        }

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        rotation += SPEED * deltaTime;
        glm::mat4 modelMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(1, 0, 1));

        setShaderMatrix("mat4_model", glm::value_ptr(modelMatrix));

        glUseProgram(shader);
        glDrawArrays(GL_TRIANGLES, 0, m->out_vertices.size() * 3);

        SDL_GL_SwapWindow(window);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

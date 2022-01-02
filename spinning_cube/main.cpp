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

GLuint vertArray;
GLuint vertBuffer;
GLuint shader;

glm::mat4 projectionMatrix;

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

void initGL() {
    // projectionMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.1, 0.1, 0.1));
    projectionMatrix = glm::perspective(glm::radians(70.0f), 800.0f/800.0f, 0.0001f, 1000.0f);
    // projectionMatrix *= glm::scale(glm::mat4(1.0f), glm::vec3(0.01, 0.01, 0.01));
    // projectionMatrix = glm::rotate(projectionMatrix, glm::radians(45), glm::vec3(0.0, 0.0, 1.0));

    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 5.0f);
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);

    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); 
    glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
    glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

    projectionMatrix *= glm::lookAt(
        cameraPos,
        cameraTarget,
        cameraUp
        );
}

int main(int argc, char* argv[]) {

    Model* m = new Model("cube.obj");

    initSDL();
    initGL();

    glGenVertexArrays(1, &vertArray);
    glBindVertexArray(vertArray);

    glGenBuffers(1, &vertBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m->out_vertices.size(), m->out_vertices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    shader = loadShader("vert.shader", "frag.shader");

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
        glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(1, 0, 1));
        glm::mat4 matrix = projectionMatrix * rotationMatrix;

        unsigned int matrixID = glGetUniformLocation(shader, "transform");
        glUniformMatrix4fv(matrixID, 1, GL_FALSE, glm::value_ptr(matrix));

        glUseProgram(shader);
        glDrawArrays(GL_TRIANGLES, 0, m->out_vertices.size() * 3);

        SDL_GL_SwapWindow(window);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

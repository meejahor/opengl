#include <iostream>

#include <SDL.h>
#define GL_SILENCE_DEPRECATION
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "shader.hpp"
#include "model.hpp"

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_GLContext context;

GLuint vertexArray;
GLuint vertexBuffer;
GLuint normalBuffer;
GLuint shader;

glm::mat4 matrixProjection;
glm::mat4 matrixView;
glm::mat4 matrixViewProjection;

Uint64 timeNow = SDL_GetPerformanceCounter();
Uint64 timeLast = 0;
float deltaTime = 0;

bool initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return false;

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
    return true;
}

void initGL() {
    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 5.0f);
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);

    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); 
    glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
    glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

    matrixView = glm::lookAt(
        cameraPos,
        cameraTarget,
        cameraUp
        );

    matrixProjection = glm::perspective(glm::radians(70.0f), 800.0f/800.0f, 0.0001f, 1000.0f);
    matrixViewProjection = matrixProjection * matrixView;

    glEnable(GL_DEPTH_TEST);  
}

int main(int argc, char* argv[]) {

    Model* m = new Model("cube.obj");

    if (!m->valid) {
        std::cout << "Error loading model." << std::endl;
        return 0;
    }

    if (!initSDL()) return 0;
    initGL();

    shader = loadShader("vert.vert", "frag.frag");
    glUseProgram(shader);

    glGenBuffers(1, &vertexBuffer);

    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m->out_vertices.size(), m->out_vertices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3)*2, (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3)*2, (void*)sizeof(glm::vec3));

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

        setShaderProperty(shader, "matrix_model", modelMatrix);
        setShaderProperty(shader, "matrix_mvp", matrixViewProjection * modelMatrix);

        glDrawArrays(GL_TRIANGLES, 0, m->out_vertices.size() * 3);

        SDL_GL_SwapWindow(window);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

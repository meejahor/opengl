#include <iostream>

#include <SDL.h>
#define GL_SILENCE_DEPRECATION
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "window.hpp"
#include "shader.hpp"
#include "model.hpp"

GLuint vertexArray;
GLuint vertexBuffer;
GLuint normalBuffer;
GLuint shader;

Uint64 timeNow = SDL_GetPerformanceCounter();
Uint64 timeLast = 0;
float deltaTime = 0;

int main(int argc, char* argv[]) {

    Model *model;
    try {
        model = new Model("cube.obj");
    } catch (...) {
        return 0;
    }

    Window *window;
    try {
        window = new Window();
    } catch (...) {
        return 0;
    }

    shader = loadShader("vert.vert", "frag.frag");
    glUseProgram(shader);

    glGenBuffers(1, &vertexBuffer);

    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * model->out_vertices.size(), model->out_vertices.data(), GL_STATIC_DRAW);

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
        setShaderProperty(shader, "matrix_mvp", window->matrixViewProjection * modelMatrix);

        glDrawArrays(GL_TRIANGLES, 0, model->out_vertices.size() * 3);

        window->swap();
    }

    window->destroy();
    SDL_Quit();
    return 0;
}

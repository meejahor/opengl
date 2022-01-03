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

GLuint shader;

float timeLast;
float timeNow;
float timeFrequencyReciprocal;
float deltaTime;

int main(int argc, char* argv[]) {

    Window *window;
    try {
        window = new Window();
    } catch (...) {
        return 0;
    }

    shader = loadShader("vert.vert", "frag.frag");

    Model *model;
    try {
        model = new Model("cube.obj", shader);
    } catch (...) {
        return 0;
    }

    bool gameIsRunning = true;
    float rotation = 0;
    const float SPEED = 90;

    timeNow = static_cast<float>(SDL_GetPerformanceCounter());
    timeFrequencyReciprocal = static_cast<float>(SDL_GetPerformanceFrequency());
    timeFrequencyReciprocal = 1.0f / timeFrequencyReciprocal;

    while (gameIsRunning) {
        timeLast = timeNow;
        timeNow = static_cast<float>(SDL_GetPerformanceCounter());
        float timeDiff = timeNow - timeLast;
        timeDiff *= timeFrequencyReciprocal;
        deltaTime = timeDiff;

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

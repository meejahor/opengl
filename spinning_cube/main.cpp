#include <iostream>

#include <SDL.h>
#define GL_SILENCE_DEPRECATION
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>

#include "window.hpp"
#include "shader.hpp"
#include "model.hpp"
#include "deltatime.hpp"
#include "object.hpp"

GLuint shader;

int main(int argc, char* argv[]) {

    std::chrono::time_point<std::chrono::high_resolution_clock> tp_start, tp_end;

    tp_start = std::chrono::high_resolution_clock::now();

    deltaTimeInit();

    for (int n=0; n<1000000; n++) {
        deltaTimeUpdate();
    }

    tp_end = std::chrono::high_resolution_clock::now();

    long start = std::chrono::time_point_cast<std::chrono::microseconds>(tp_start).time_since_epoch().count();
    long end = std::chrono::time_point_cast<std::chrono::microseconds>(tp_end).time_since_epoch().count();
    std::cout << "deltaTimeUpdate " << (end - start) / 1000 << "ms" << std::endl;

    Window* window;
    try {
        window = new Window();
    } catch (...) {
        return 0;
    }

    shader = loadShader("vert.vert", "frag.frag");

    Model* model;
    try {
        model = new Model("cube.obj", shader);
    } catch (...) {
        return 0;
    }

    Object* object = new Object(model);

    bool gameIsRunning = true;

    deltaTimeInit();

    while (gameIsRunning) {
        deltaTimeUpdate();

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                gameIsRunning = false;
            }
        }

        window->clear();

        object->update();
        object->render(window);

        window->swap();
    }

    window->destroy();
    SDL_Quit();
    return 0;
}

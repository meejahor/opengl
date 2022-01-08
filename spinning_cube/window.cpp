#include <iostream>

#include <SDL.h>
#define GL_SILENCE_DEPRECATION
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "window.hpp"
#include "utils.hpp"

Window* window;

void Window::initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::exception();
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
        width,
        height,
        SDL_WINDOW_SHOWN
        );

    // renderer = SDL_CreateRenderer(
    //     window,
    //     -1,
    //     SDL_RENDERER_ACCELERATED
    //     );

    context = SDL_GL_CreateContext(window);
}

void Window::initGL() {
    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 5.0f);
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);

    matrixViewProjection = calcViewProjection(cameraPos, cameraTarget, 70.0f);

    glEnable(GL_DEPTH_TEST);  
}

void Window::swap() {
    SDL_GL_SwapWindow(window);
}

void Window::destroy() {
    SDL_GL_DeleteContext(context);  
    SDL_DestroyWindow(window);
}

Window::Window(int _width, int _height) {
    width = _width;
    height = _height;

    try {
        initSDL();
    } catch (...) {
        throw;
    }

    initGL();
}

void Window::clear() {
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void Window::activate() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    // glBindRenderbuffer(GL_RENDERBUFFER, 0);
    // glDrawBuffer(GL_BACK);
    glViewport(0, 0, width, height);
}

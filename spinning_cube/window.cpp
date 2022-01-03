#include <iostream>

#include <SDL.h>
#define GL_SILENCE_DEPRECATION
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "window.hpp"

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

void Window::initGL() {
    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 5.0f);
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);

    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); 
    glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
    glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

    glm::mat4 matrixView = glm::lookAt(
        cameraPos,
        cameraTarget,
        cameraUp
        );

    glm::mat4 matrixProjection = glm::perspective(glm::radians(70.0f), 800.0f/800.0f, 0.0001f, 1000.0f);
    matrixViewProjection = matrixProjection * matrixView;

    glEnable(GL_DEPTH_TEST);  
}

void Window::swap() {
    SDL_GL_SwapWindow(window);
}

void Window::destroy() {
    SDL_DestroyWindow(window);
}

Window::Window() {
    try {
        initSDL();
    } catch (...) {
        throw;
    }
    initGL();
}

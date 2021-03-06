#include <iostream>

#include <SDL.h>
#define GL_SILENCE_DEPRECATION
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "window.hpp"
#include "utils.hpp"
#include "renderTexture.hpp"

Window* window;
int windowWidth = 800;
int windowHeight = 800;

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
        windowHeight,
        windowHeight,
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
    glm::vec3 cameraPos = glm::vec3(0.0f, 30.0f, 50.0f);
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);

    matrixViewProjection = calcViewProjection(cameraPos, cameraTarget, 30.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void Window::swap() {
    SDL_GL_SwapWindow(window);
}

void Window::destroy() {
    SDL_GL_DeleteContext(context);  
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

void Window::clear() {
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClearDepth(1);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void Window::activate() {
    // glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    // RenderTexture::resetDrawBuffer();
        
    // glBindRenderbuffer(GL_RENDERBUFFER, 0);
    // glDrawBuffer(GL_BACK);
    glViewport(0, 0, windowWidth, windowHeight);
}

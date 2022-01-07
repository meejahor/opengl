#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#define GL_SILENCE_DEPRECATION
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl3.h>

#include "glm/glm.hpp"

class Window {
    public:
        glm::mat4 matrixViewProjection;

        Window(int _width, int _height);
        void swap();
        void destroy();
        void clear();
        void activate();

    private:
        SDL_Window* window;
        SDL_GLContext context;
        int width, height;

        void initSDL();
        void initGL();
};

extern Window* window;

#endif

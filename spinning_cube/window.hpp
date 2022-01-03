#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#define GL_SILENCE_DEPRECATION
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Window {
    public:
        glm::mat4 matrixViewProjection;

        Window();
        void swap();
        void destroy();

    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_GLContext context;

        void initSDL();
        void initGL();
};

#endif

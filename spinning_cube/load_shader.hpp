#ifndef LOAD_SHADER_H
#define LOAD_SHADER_H

// #include <SDL_opengl.h>
// #include "GL/glew.h"
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl3.h>

GLuint loadShader(const char *vertex_path, const char *fragment_path);

#endif

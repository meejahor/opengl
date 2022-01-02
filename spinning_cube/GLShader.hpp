#ifndef GLSHADER_H
#define GLSHADER_H

// #include <SDL_opengl.h>
// #include "GL/glew.h"
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl3.h>

GLuint LoadShader(const char *vertex_path, const char *fragment_path);

#endif

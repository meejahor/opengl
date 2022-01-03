#ifndef SHADER_H
#define SHADER_H

#include <OpenGL/gl3.h>

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "glm/gtc/type_ptr.hpp"

GLuint loadShader(const char *vertex_path, const char *fragment_path);
void setShaderProperty(GLuint shaderID, const char* name, glm::mat4 matrix);

#endif

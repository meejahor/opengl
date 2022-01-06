#ifndef SHADER_H
#define SHADER_H

#include <OpenGL/gl3.h>

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "glm/gtc/type_ptr.hpp"

class Shader {
    public:
    Shader(const char *vertex_path, const char *fragment_path);
    void use();
    void setMatrices(glm::mat4 const& matrixModel, glm::mat4 const& matrixMVP);

    private:
    void findIDs();
    GLuint program;
    unsigned int matrixModel_ID;
    unsigned int matrixMVP_ID;
};

// GLuint loadShader(const char *vertex_path, const char *fragment_path);
// void setShaderProperty(GLuint shaderID, const char* name, glm::mat4 const& matrix);

#endif

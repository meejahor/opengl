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
    void setLightmapMatrices(glm::mat4 const& mat4_MVP);
    void setRenderMatrices(glm::mat4 const& mat4_Model, glm::mat4 const& mat4_MVP, glm::mat4 const& mat4_LightMVP);

    private:
    void findIDs();
    GLuint program;
    unsigned int mat4_Model_ID;
    unsigned int mat4_MVP_ID;
    unsigned int mat4_LightMVP_ID;
};

// GLuint loadShader(const char *vertex_path, const char *fragment_path);
// void setShaderProperty(GLuint shaderID, const char* name, glm::mat4 const& matrix);

#endif

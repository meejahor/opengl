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
    void setMatricesForLightmap(glm::mat4 const& mat4_Model, glm::mat4 const& mat4_Light_MVP);
    void setMatricesForScreenRenderingWithLighting(
        glm::mat4 const& mat4_Model,
        glm::mat4 const& mat4_Camera_MVP,
        glm::mat4 const& mat4_Light_MVP,
        glm::vec3 const& lightPosition,
        glm::vec3 const& lightDirection
        );
    void setMatricesForScreenRenderingNoLighting(glm::mat4 const& mat4_Model, glm::mat4 const& mat4_Camera_MVP);
    // void setDepthNormalsTextures(GLuint depthTexture, GLuint normalsTexture);
    void setMatricesForScreen(glm::mat4 const& mat4_Model, glm::mat4 const& mat4_Screen_MVP);

    private:
    void findIDs();
    GLuint program;
    unsigned int mat4_Model_ID;
    unsigned int mat4_Camera_MVP_ID;
    unsigned int mat4_Light_MVP_ID;
    unsigned int lightPosition_ID;
    unsigned int lightDirection_ID;
    // unsigned int depthTexture_ID;
    // unsigned int normalsTexture_ID;
};

// GLuint loadShader(const char *vertex_path, const char *fragment_path);
// void setShaderProperty(GLuint shaderID, const char* name, glm::mat4 const& matrix);

#endif

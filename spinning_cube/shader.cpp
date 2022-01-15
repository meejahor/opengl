#define GL_SILENCE_DEPRECATION
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <OpenGL/gl3.h>
#include "glm/gtc/type_ptr.hpp"

#include "shader.hpp"

std::string readFile(const char *filePath) {
    std::string content;
    std::ifstream fileStream(filePath, std::ios::in);

    if(!fileStream.is_open()) {
        std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
        return "";
    }

    std::string line = "";
    while(!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}

void Shader::findIDs() {
    mat4_Model_ID = glGetUniformLocation(program, "mat4_Model");
    mat4_Camera_MVP_ID = glGetUniformLocation(program, "mat4_Camera_MVP");
    mat4_Light_MVP_ID = glGetUniformLocation(program, "mat4_Light_MVP");
    lightPosition_ID = glGetUniformLocation(program, "lightPosition");
    lightDirection_ID = glGetUniformLocation(program, "lightDirection");
    // depthTexture_ID = glGetUniformLocation(program, "depthTexture");
    // normalsTexture_ID = glGetUniformLocation(program, "normalsTexture");
    // std::cout << lightPosition_ID << std::endl;
    // std::cout << lightDirection_ID << std::endl;
}

Shader::Shader(const char *vertex_path, const char *fragment_path) {
    std::cout << "Loading: " << vertex_path << " " << fragment_path << std::endl;
    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Read shaders

    std::string vertShaderStr = readFile(vertex_path);
    std::string fragShaderStr = readFile(fragment_path);
    const char *vertShaderSrc = vertShaderStr.c_str();
    const char *fragShaderSrc = fragShaderStr.c_str();

    GLint result = GL_FALSE;
    int logLength;

    // Compile vertex shader

    // std::cout << "Compiling vertex shader." << std::endl;
    glShaderSource(vertShader, 1, &vertShaderSrc, NULL);
    glCompileShader(vertShader);

    // Check vertex shader

    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> vertShaderError((logLength > 1) ? logLength : 1);
    glGetShaderInfoLog(vertShader, logLength, NULL, &vertShaderError[0]);
    std::cout << &vertShaderError[0] << std::endl;

    // Compile fragment shader

    // std::cout << "Compiling fragment shader." << std::endl;
    glShaderSource(fragShader, 1, &fragShaderSrc, NULL);
    glCompileShader(fragShader);

    // Check fragment shader

    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> fragShaderError((logLength > 1) ? logLength : 1);
    glGetShaderInfoLog(fragShader, logLength, NULL, &fragShaderError[0]);
    if (std::strlen(&fragShaderError[0]) > 0) {
        std::cout << &fragShaderError[0] << std::endl;
    }

    // std::cout << "Linking program" << std::endl;
    program = glCreateProgram();
    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &result);
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> programError( (logLength > 1) ? logLength : 1 );
    glGetProgramInfoLog(program, logLength, NULL, &programError[0]);
    if (std::strlen(&programError[0]) > 0) {
        std::cout << &programError[0] << std::endl;
    }

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    findIDs();
}

void Shader::use() {
    glUseProgram(program);

	// GLuint TextureID = glGetUniformLocation(program, "renderedTexture");
    // glUniform1i(TextureID, 0);
}

void Shader::setMatricesForLightmap(
    glm::mat4 const& mat4_Model,
    glm::mat4 const& mat4_Light_MVP
    ) {
    glUniformMatrix4fv(mat4_Model_ID, 1, GL_FALSE, glm::value_ptr(mat4_Model));
    glUniformMatrix4fv(mat4_Light_MVP_ID, 1, GL_FALSE, glm::value_ptr(mat4_Light_MVP));
}

void Shader::setMatricesForScreen(
    glm::mat4 const& mat4_Model,
    glm::mat4 const& mat4_Camera_MVP
    ) {
    glUniformMatrix4fv(mat4_Model_ID, 1, GL_FALSE, glm::value_ptr(mat4_Model));
    glUniformMatrix4fv(mat4_Camera_MVP_ID, 1, GL_FALSE, glm::value_ptr(mat4_Camera_MVP));
}

void Shader::setMatricesForScreenRenderingWithLighting(
    glm::mat4 const& mat4_Model,
    glm::mat4 const& mat4_Camera_MVP,
    glm::mat4 const& mat4_Light_MVP,
    glm::vec3 const& lightPosition,
    glm::vec3 const& lightDirection
    ) {
    glUniformMatrix4fv(mat4_Model_ID, 1, GL_FALSE, glm::value_ptr(mat4_Model));
    glUniformMatrix4fv(mat4_Camera_MVP_ID, 1, GL_FALSE, glm::value_ptr(mat4_Camera_MVP));
    glUniformMatrix4fv(mat4_Light_MVP_ID, 1, GL_FALSE, glm::value_ptr(mat4_Light_MVP));
    glUniform3fv(lightPosition_ID, 1, glm::value_ptr(lightPosition));
    glUniform3fv(lightDirection_ID, 1, glm::value_ptr(lightDirection));
}

void Shader::setMatricesForScreenRenderingNoLighting(
    glm::mat4 const& mat4_Model,
    glm::mat4 const& mat4_Camera_MVP
    ) {
    glUniformMatrix4fv(mat4_Model_ID, 1, GL_FALSE, glm::value_ptr(mat4_Model));
    glUniformMatrix4fv(mat4_Camera_MVP_ID, 1, GL_FALSE, glm::value_ptr(mat4_Camera_MVP));
}

// void Shader::setDepthNormalsTextures(GLuint depthTexture, GLuint normalsTexture) {
//     glUniform1i(depthTexture_ID, 0);
//     glUniform1i(normalsTexture_ID, 1);
//     glActiveTexture(GL_TEXTURE0);
//     glBindTexture(GL_TEXTURE_2D, depthTexture);
//     glActiveTexture(GL_TEXTURE1);
//     glBindTexture(GL_TEXTURE_2D, normalsTexture);

//     // comment on stack said this is required but it doesn't seem to make any difference?
//     glActiveTexture(GL_TEXTURE0);
// }

// void setShaderProperty(GLuint shaderID, const char* name, glm::mat4 const& matrix) {
//     unsigned int propertyID = glGetUniformLocation(shaderID, name);
//     glUniformMatrix4fv(propertyID, 1, GL_FALSE, glm::value_ptr(matrix[0]));
// }

#define GL_SILENCE_DEPRECATION
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <OpenGL/gl3.h>
#include "glm/gtc/type_ptr.hpp"

#include "shader.hpp"

// glm::mat4 biasMatrix(
//     0.5, 0.0, 0.0, 0.0,
//     0.0, 0.5, 0.0, 0.0,
//     0.0, 0.0, 0.5, 0.0,
//     0.5, 0.5, 0.5, 1.0
// );

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
    mat4_MVP_ID = glGetUniformLocation(program, "mat4_MVP");
    mat4_LightMVP_ID = glGetUniformLocation(program, "mat4_LightMVP");
}

Shader::Shader(const char *vertex_path, const char *fragment_path) {
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

    std::cout << "Compiling vertex shader." << std::endl;
    glShaderSource(vertShader, 1, &vertShaderSrc, NULL);
    glCompileShader(vertShader);

    // Check vertex shader

    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> vertShaderError((logLength > 1) ? logLength : 1);
    glGetShaderInfoLog(vertShader, logLength, NULL, &vertShaderError[0]);
    std::cout << &vertShaderError[0] << std::endl;

    // Compile fragment shader

    std::cout << "Compiling fragment shader." << std::endl;
    glShaderSource(fragShader, 1, &fragShaderSrc, NULL);
    glCompileShader(fragShader);

    // Check fragment shader

    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> fragShaderError((logLength > 1) ? logLength : 1);
    glGetShaderInfoLog(fragShader, logLength, NULL, &fragShaderError[0]);
    std::cout << &fragShaderError[0] << std::endl;

    std::cout << "Linking program" << std::endl;
    program = glCreateProgram();
    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &result);
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> programError( (logLength > 1) ? logLength : 1 );
    glGetProgramInfoLog(program, logLength, NULL, &programError[0]);
    std::cout << &programError[0] << std::endl;

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    findIDs();
}

void Shader::use() {
    glUseProgram(program);

	// GLuint TextureID = glGetUniformLocation(program, "renderedTexture");
    // glUniform1i(TextureID, 0);
}

void Shader::setLightmapMatrices(glm::mat4 const& mat4_LightMVP) {
    glUniformMatrix4fv(mat4_LightMVP_ID, 1, GL_FALSE, glm::value_ptr(mat4_LightMVP));
}

void Shader::setRenderMatrices(glm::mat4 const& mat4_Model, glm::mat4 const& mat4_MVP, glm::mat4 const& mat4_LightMVP) {
    glUniformMatrix4fv(mat4_Model_ID, 1, GL_FALSE, glm::value_ptr(mat4_Model));
    glUniformMatrix4fv(mat4_MVP_ID, 1, GL_FALSE, glm::value_ptr(mat4_MVP));
    glUniformMatrix4fv(mat4_LightMVP_ID, 1, GL_FALSE, glm::value_ptr(mat4_LightMVP));
}

// void setShaderProperty(GLuint shaderID, const char* name, glm::mat4 const& matrix) {
//     unsigned int propertyID = glGetUniformLocation(shaderID, name);
//     glUniformMatrix4fv(propertyID, 1, GL_FALSE, glm::value_ptr(matrix[0]));
// }

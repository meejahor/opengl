#include <iostream>

#include "light.hpp"
#include "renderTexture.hpp"
#include "utils.hpp"
#include "shader.hpp"

#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl3.h>

GLuint depthShader;

void Light::loadDepthShader() {
    depthShader = loadShader("shaders/vert.vert", "shaders/depth.frag");
}

Light::Light(glm::vec3 _position, glm::vec3 _direction, float _cone) {
    position = _position;
    direction = _direction;
    cone = _cone;

    matrixViewProjection = calcViewProjection(
        position,
        position + direction,
        cone
        );

    try {
        texture = RenderTexture::createColorTexture(1024, 1024);
    } catch (...) {
        std::cout << "couldn't create render texture for light" << std::endl;
        throw;
    }
}

void Light::activate() {
    texture->activate();
}

void Light::clear() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}
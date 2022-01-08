#include <iostream>

#include "light.hpp"
#include "renderTexture.hpp"
#include "utils.hpp"
#include "shader.hpp"

#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl3.h>

Shader* depthShader;

void Light::loadDepthShader() {
    depthShader = new Shader("shaders/vert.vert", "shaders/depth.frag");
}

Light::Light(glm::vec3 _position, glm::vec3 _direction, float _cone, glm::vec3 up) {
    position = _position;
    direction = _direction;
    cone = _cone;

    matrixViewProjection = calcViewProjection(
        position,
        position + direction,
        cone,
        up
        );

    try {
        texture = RenderTexture::createColorTexture(1024, 1024);
    } catch (...) {
        std::cout << "couldn't create render texture for light" << std::endl;
        throw;
    }
}

void Light::activate() {
    texture->activateAsLightmap();
}

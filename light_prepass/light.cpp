#include <iostream>

#include "light.hpp"
#include "renderTexture.hpp"
#include "utils.hpp"

#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl3.h>

Light::Light(glm::vec3 _position, glm::vec3 _direction, float _cone, float _radius, glm::vec3 _up) {
    position = _position;
    direction = glm::normalize(_direction);
    up = _up;
    cone = _cone;
    radius = _radius;

    calculateMatrixViewProjection();

    try {
        texture = RenderTexture::createLightmap(1024, 1024);
    } catch (...) {
        std::cout << "couldn't create render texture for light" << std::endl;
        throw;
    }
}

void Light::calculateMatrixViewProjection() {
    matrixViewProjection = calcViewProjection(
            position,
            position + direction,
            cone,
            up
    );
}

void Light::moveTo(float x, float y, float z) {
    position = glm::vec3(x, y, z);
    calculateMatrixViewProjection();
}

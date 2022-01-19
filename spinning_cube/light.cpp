#include <iostream>

#include "light.hpp"
#include "renderTexture.hpp"
#include "utils.hpp"
#include "shader.hpp"
#include "model.hpp"
#include "object.hpp"

#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl3.h>

Model* modelLightSphere;
Object* objectLightSphere;

void Light::loadResources() {
    try {
        modelLightSphere = new Model("sphere");
    } catch (...) {
        throw;
    }

    objectLightSphere = new Object(modelLightSphere);
}

Light::Light(glm::vec3 _position, glm::vec3 _direction, float _cone, float _radius, glm::vec3 up) {
    position = _position;
    direction = glm::normalize(_direction);
    cone = _cone;
    radius = _radius;

    matrixViewProjection = calcViewProjection(
        position,
        position + direction,
        cone,
        up
        );

    try {
        texture = RenderTexture::createLightmap(1024, 1024);
    } catch (...) {
        std::cout << "couldn't create render texture for light" << std::endl;
        throw;
    }
}

void Light::beginRenderingLightmap() {
    texture->beginRenderingLightmap();
}

void Light::useShadowMap() {
    texture->showTexture();
}

void Light::renderLightSphere(RenderTexture* rt) {
    objectLightSphere->moveTo(position);
    objectLightSphere->setScale(radius * 2);
    objectLightSphere->update();
    shaderRenderLightSphere->setLightPosAndRadius(position, radius);
    shaderRenderLightSphere->setTextureSize(glm::vec2(windowWidth, windowHeight));
    objectLightSphere->renderLightSphere(rt);
}

void Light::setShaderPositionAndRadius() {
    objectLightSphere->moveTo(position);
    objectLightSphere->setScale(radius * 2);
    objectLightSphere->update();
    shaderRenderLightSphere->setLightPosAndRadius(position, radius);
}

#include "object.hpp"
#include "deltatime.hpp"

#include "glm/gtc/matrix_transform.hpp"

static const float SPEED = 90;

Object::Object(Model* _model) {
    model = _model;
    rotation = 0;
    calcMatrix();
}

void Object::calcMatrix() {
    modelMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(1, 0, 1));
}

void Object::update() {
    rotation += SPEED * deltaTime;
    calcMatrix();
}

void Object::renderLightMap(Light* light) {
    model->renderLightMap(light, modelMatrix);
}

void Object::render(Light* light) {
    model->render(light, modelMatrix);
}

void Object::showLightmap(Light* light, RenderTexture* rt) {
    model->showLightmap(light, modelMatrix, rt);
}

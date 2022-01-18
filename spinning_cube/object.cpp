#include "object.hpp"
#include "deltatime.hpp"

#include "glm/gtc/matrix_transform.hpp"

static const float SPEED = 90;
static glm::mat4 mat4_one = glm::mat4(1.0f);

Object::Object(Model* _model, float _scale, glm::vec3 _position) {
    model = _model;
    scale = _scale;
    position = _position;
    rotation = 0;
    calcMatrix();
}

void Object::calcMatrix() {
    modelMatrix = glm::translate(mat4_one, position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation), glm::vec3(1, 0, 0));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(scale));
}

void Object::update() {
    rotation += SPEED * deltaTime;
    calcMatrix();
}

void Object::renderToLightmap(Light* light) {
    model->renderToLightmap(light, modelMatrix);
}

void Object::renderWithShadow(Light* light) {
    model->renderWithShadow(light, modelMatrix);
}

void Object::showLightmap(Light* light) {
    model->showLightmap(modelMatrix, light->texture);
}

void Object::renderPositionNormalsAlbedo(RenderTexture* rt) {
    model->renderPositionNormalsAlbedo(modelMatrix, rt);
}

void Object::showPosition(RenderTexture* rt) {
    model->showPosition(modelMatrix, rt);
}

void Object::showNormals(RenderTexture* rt) {
    model->showNormals(modelMatrix, rt);
}

void Object::showAlbedo(RenderTexture* rt) {
    model->showAlbedo(modelMatrix, rt);
}

void Object::renderLightSphere(RenderTexture* rt) {
    model->renderLightSphere(modelMatrix, rt);
}

void Object::moveTo(glm::vec3 _position) {
    position = _position;
}

void Object::setScale(float _scale) {
    scale = _scale;
}

void Object::showFinal(RenderTexture* rt) {
    model->showFinal(modelMatrix, rt);
}

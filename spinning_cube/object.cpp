#include "object.hpp"
#include "deltatime.hpp"

#include "glm/gtc/matrix_transform.hpp"

static const float SPEED = 90;

Object::Object(Model* _model, float _scale, glm::vec3 _translation) {
    model = _model;
    scale = _scale;
    translation = _translation;
    rotation = 0;
    calcMatrix();
}

void Object::calcMatrix() {
    modelMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(1, 0, 0));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(scale));
    modelMatrix = glm::translate(modelMatrix, translation);
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

void Object::render(RenderTexture* rt) {
    model->render(modelMatrix, rt);
}

void Object::showDepthNormals(RenderTexture* rt) {
    model->showDepthNormals(modelMatrix, rt);
}

void Object::showLightmap(RenderTexture* rt) {
    model->showLightmap(modelMatrix, rt);
}

void Object::renderDepthNormals(RenderTexture* rt) {
    model->renderDepthNormals(modelMatrix, rt);
}

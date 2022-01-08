#include "object.hpp"
#include "deltatime.hpp"

#include "glm/gtc/matrix_transform.hpp"

static const float SPEED = 90;

Object::Object(Model* _model, glm::vec3 _translation) {
    model = _model;
    translation = _translation;
    rotation = 0;
    calcMatrix();
}

void Object::calcMatrix() {
    modelMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(1, 0, 0));
    modelMatrix = glm::translate(modelMatrix, translation);
}

void Object::update() {
    rotation += SPEED * deltaTime;
    calcMatrix();
}

void Object::render(glm::mat4 const& matrixViewProjection, Shader* renderShader, RenderTexture* rt) {
    model->render(matrixViewProjection, modelMatrix, renderShader, rt);
}

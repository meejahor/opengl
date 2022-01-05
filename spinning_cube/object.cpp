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

void Object::render(glm::mat4 const& matrixViewProjection, GLuint renderShader) {
    model->render(matrixViewProjection, modelMatrix, renderShader);
}

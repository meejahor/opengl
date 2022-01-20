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

void Object::moveTo(glm::vec3 _position) {
    position = _position;
}

void Object::setScale(float _scale) {
    scale = _scale;
}

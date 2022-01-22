#include "object.hpp"
#include "deltatime.hpp"

#include "glm/gtc/matrix_transform.hpp"

static const float SPEED = 90;
static glm::mat4 mat4_identity = glm::mat4(1.0f);

Object::Object(Model* _model) {
    model = _model;
    update();
}

void Object::update() {
    modelMatrix = glm::translate(mat4_identity, position);
    modelMatrix = modelMatrix * rotation;
    modelMatrix = glm::scale(modelMatrix, glm::vec3(scale));
}

void Object::rotate(float degrees, glm::vec3 axis) {
    rotation = glm::rotate(rotation, glm::radians(degrees), axis);
}

void Object::moveTo(glm::vec3 _position) {
    position = _position;
}

void Object::moveTo(float x, float y, float z) {
    position = glm::vec3(x, y, z);
}

void Object::setScale(float _scale) {
    scale = _scale;
}

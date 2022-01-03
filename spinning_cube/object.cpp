#include "object.hpp"
#include "deltatime.hpp"

#include "glm/gtc/matrix_transform.hpp"

static const float SPEED = 90;

Object::Object(Model* _model) {
    rotation = 0;
    model = _model;
}

void Object::update() {
    rotation += SPEED * deltaTime;
    modelMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(1, 0, 1));
}

void Object::render(Window* window) {
    model->render(window, modelMatrix);
}

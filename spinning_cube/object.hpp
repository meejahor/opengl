#ifndef OBJECT_H
#define OBJECT_H

#include "model.hpp"
#include "glm/glm.hpp"
#include "window.hpp"
#include "shader.hpp"
#include "light.hpp"

class Object {
    private:
    float scale = 1;
    glm::vec3 position;
    glm::mat4 rotation;

    public:
    Model* model;
    glm::mat4 modelMatrix;
    Object(Model* _model);
    void update();
    void rotate(float degrees, glm::vec3 axis);
    void moveTo(glm::vec3 _translation);
    void setScale(float _scale);
};

#endif

#ifndef OBJECT_H
#define OBJECT_H

#include "model.hpp"
#include "glm/glm.hpp"
#include "window.hpp"

class Object {
    private:
    Model* model;
    float rotation;
    glm::mat4 modelMatrix;

    public:
    Object(Model* _model);
    void update();
    void render(Window* window);
};

#endif

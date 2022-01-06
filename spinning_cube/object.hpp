#ifndef OBJECT_H
#define OBJECT_H

#include "model.hpp"
#include "glm/glm.hpp"
#include "window.hpp"
#include "shader.hpp"

class Object {
    private:
    Model* model;
    float rotation;
    glm::mat4 modelMatrix;
    void calcMatrix();

    public:
    Object(Model* _model);
    void update();
    void render(glm::mat4 const& matrixViewProjection, Shader* renderShader = NULL, RenderTexture* rt = NULL);
};

#endif

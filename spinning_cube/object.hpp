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
    glm::vec3 translation;
    glm::mat4 modelMatrix;
    void calcMatrix();

    public:
    Object(Model* _model, glm::vec3 _translation = glm::vec3(0, 0, 0));
    void update();
    void render(glm::mat4 const& matrixViewProjection, Shader* renderShader = NULL, RenderTexture* rt = NULL);
};

#endif

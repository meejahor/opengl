#ifndef OBJECT_H
#define OBJECT_H

#include "model.hpp"
#include "glm/glm.hpp"
#include "window.hpp"
#include "shader.hpp"
#include "light.hpp"

class Object {
    private:
    Model* model;
    float rotation;
    glm::mat4 modelMatrix;
    void calcMatrix();

    public:
    Object(Model* _model);
    void update();
    void renderLightMap(Light* light);
    void render(Light* light);
    void showLightmap(Light* light, RenderTexture* rt);
};

#endif

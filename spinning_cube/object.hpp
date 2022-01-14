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
    glm::vec3 translation;
    glm::mat4 modelMatrix;
    void calcMatrix();

    public:
    Object(Model* _model, glm::vec3 _translation = glm::vec3(0, 0, 0));
    void update();
    void renderToLightmap(Light* light);
    void renderWithShadow(Light* light);
    void render(RenderTexture* rt = NULL);
    void showNormals(RenderTexture* rt = NULL);
    void renderDepthNormals(RenderTexture* rt);
};

#endif

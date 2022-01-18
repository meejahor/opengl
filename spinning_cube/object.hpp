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
    float scale;
    glm::vec3 position;
    glm::mat4 modelMatrix;
    void calcMatrix();

    public:
    Object(Model* _model, float _scale = 1, glm::vec3 _position = glm::vec3(0, 0, 0));
    void update();
    void renderToLightmap(Light* light);
    void renderWithShadow(Light* light);
    void showLightmap(Light* light);
    void renderPositionNormalsAlbedo(RenderTexture* rt);
    void renderLightSphere(RenderTexture* rt);
    void showPosition(RenderTexture* rt);
    void showNormals(RenderTexture* rt);
    void showAlbedo(RenderTexture* rt);
    void moveTo(glm::vec3 _translation);
};

#endif

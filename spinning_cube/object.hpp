#ifndef OBJECT_H
#define OBJECT_H

#include "model.hpp"
#include "glm/glm.hpp"
#include "window.hpp"
#include "shader.hpp"
#include "light.hpp"

class Object {
    private:
    float rotation;
    float scale;
    glm::vec3 position;
    void calcMatrix();

    public:
    Model* model;
    glm::mat4 modelMatrix;
    Object(Model* _model, float _scale = 1, glm::vec3 _position = glm::vec3(0, 0, 0));
    void update();
    void showLightmap(Light* light);
    void showPosition(RenderTexture* rt);
    void showNormals(RenderTexture* rt);
    void showAlbedo(RenderTexture* rt);
    void showFinal(RenderTexture* rt);

    void moveTo(glm::vec3 _translation);
    void setScale(float _scale);
};

#endif

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
    glm::vec3 scale;
    glm::mat4 modelMatrix;
    void calcMatrix();

    public:
    Object(
        Model* _model,
        glm::vec3 _translation = glm::vec3(0, 0, 0),
        glm::vec3 _scale = glm::vec3(1, 1, 1)
        );
    void update();
    void renderToLightmap(Light* light);
    void renderWithShadow(Light* light);
    void render(RenderTexture* rt = NULL);
    void renderNormals(RenderTexture* rt = NULL);
    void renderColorDepthNormals(RenderTexture* rt);
};

#endif

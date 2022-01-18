#ifndef LIGHT_H
#define LIGHT_H

#include "glm/glm.hpp"
#include "renderTexture.hpp"
#include "shader.hpp"

class Light {
    public:
    float cone;
    float size;
    RenderTexture* texture;
    glm::vec3 position;
    glm::vec3 direction;
    Light(glm::vec3 _position, glm::vec3 _direction, float _cone, float _size, glm::vec3 up);
    void beginRenderingLightmap();
    glm::mat4 matrixViewProjection;
    void useShadowMap();
    static void loadResources();
    void renderLightSphere(RenderTexture* rt);
};

#endif

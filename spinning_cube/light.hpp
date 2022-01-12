#ifndef LIGHT_H
#define LIGHT_H

#include "glm/glm.hpp"
#include "renderTexture.hpp"
#include "shader.hpp"

extern Shader* depthShader;

class Light {
    public:
    float cone;
    RenderTexture* texture;
    glm::vec3 position;
    glm::vec3 direction;
    static void loadDepthShader();
    Light(glm::vec3 _position, glm::vec3 _direction, float _cone, glm::vec3 up);
    void activate();
    glm::mat4 matrixViewProjection;
    void useShadowMap();
};

#endif

#ifndef LIGHT_H
#define LIGHT_H

#include "glm/glm.hpp"
#include "renderTexture.hpp"

extern GLuint depthShader;

class Light {
    private:
    glm::vec3 position;
    glm::vec3 direction;
    float cone;
    RenderTexture* texture;

    public:
    static void loadDepthShader();
    Light(glm::vec3 _position, glm::vec3 _direction, float _cone);
    void activate();
    void clear();
    glm::mat4 matrixViewProjection;
};

#endif

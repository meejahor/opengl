#ifndef MODEL_H
#define MODEL_H

#include <vector>

#define GL_SILENCE_DEPRECATION
#include <OpenGL/OpenGL.h>
#include "glm/glm.hpp"

#include "window.hpp"
#include "renderTexture.hpp"
#include "shader.hpp"
#include "light.hpp"

class Model {
    public:
    std::vector<glm::vec3> out_vertices;
    std::vector<glm::vec2> out_uvs;
    std::vector<glm::vec3> out_normals;

    Model(const char *filename, Shader* _shader);
    void draw();
    void renderToLightmap(Light* light, glm::mat4 const& matrixModel);
    void render(glm::mat4 const& matrixModel, RenderTexture* rt = NULL);

    private:
    FILE* file;

    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> temp_normals;

    GLuint vertexArray;
    GLuint vertexBuffer;

    Shader* shader;

    void loadVertex();
    void loadUV();
    void loadNormal();
    void loadFace();
    void setupBuffers();
    void load(const char *filename);
};

#endif

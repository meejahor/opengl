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
    Model(std::string filename, Shader* _shader = NULL, bool flipUV_y = true);
    void draw();
    void renderToLightmap();
    // void renderWithShadow(Light* light, glm::mat4 const& matrixModel);
    void showLightmap(glm::mat4 const& matrixModel, RenderTexture* rt);
    void renderPositionNormalsAlbedo();
    void renderLightSphere(glm::mat4 const& matrixModel, RenderTexture* rt);
    void showPosition(glm::mat4 const& matrixModel, RenderTexture* rt);
    void showNormals(glm::mat4 const& matrixModel, RenderTexture* rt);
    void showAlbedo(glm::mat4 const& matrixModel, RenderTexture* rt);
    void showFinal(glm::mat4 const& matrixModel, RenderTexture* rt);
    void renderLightSphere();
    RenderTexture* rt_Albedo;

    private:
    std::vector<float> data;

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
    void load(std::string filename, bool flipUV_y);
    void loadTextures(std::string filename);
};

#endif

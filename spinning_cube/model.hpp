#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include "glm/glm.hpp"

class Model {
    public:
    std::vector<glm::vec3> out_vertices;
    std::vector<glm::vec2> out_uvs;
    std::vector<glm::vec3> out_normals;
    Model(const char *filename);

    private:
    FILE* file;
    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> temp_normals;
    void loadVertex();
    void loadUV();
    void loadNormal();
    void loadFace();
};

#endif

#include <iostream>

#include "model.hpp"

void Model::loadVertex() {
    glm::vec3 vertex;
    fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
    temp_vertices.push_back(vertex);
}

void Model::loadUV() {
    glm::vec2 uv;
    fscanf(file, "%f %f\n", &uv.x, &uv.y);
    temp_uvs.push_back(uv);
}

void Model::loadNormal() {
    glm::vec3 normal;
    fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
    temp_normals.push_back(normal);
}

bool Model::loadFace() {
    std::string vertex1, vertex2, vertex3;
    unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
    int matches = fscanf(
        file,
        "%d/%d/%d %d/%d/%d %d/%d/%d\n",
        &vertexIndex[0], &uvIndex[0], &normalIndex[0],
        &vertexIndex[1], &uvIndex[1], &normalIndex[1],
        &vertexIndex[2], &uvIndex[2], &normalIndex[2]
        );
    if (matches != 9) return false;

    vertexIndices.push_back(vertexIndex[0]);
    vertexIndices.push_back(vertexIndex[1]);
    vertexIndices.push_back(vertexIndex[2]);
    uvIndices.push_back(uvIndex[0]);
    uvIndices.push_back(uvIndex[1]);
    uvIndices.push_back(uvIndex[2]);
    normalIndices.push_back(normalIndex[0]);
    normalIndices.push_back(normalIndex[1]);
    normalIndices.push_back(normalIndex[2]);
    return true;
}

Model::Model(const char *filename) {
    valid = false;
    
    file = fopen(filename, "r");
    if (file == NULL) return;

    while (true) {
        char lineHeader[128];
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF) break;

        if (strcmp(lineHeader, "v") == 0 ) {
            loadVertex();
        } else if (strcmp(lineHeader, "vt") == 0) {
            loadUV();
        } else if (strcmp(lineHeader, "vn") == 0) {
            loadNormal();
        } else if (strcmp(lineHeader, "f") == 0) {
            if (!loadFace()) return;
        }
    }

    for (unsigned int i=0; i<vertexIndices.size(); i++) {
        unsigned int vertexIndex = vertexIndices[i];
        glm::vec3 vertex = temp_vertices[vertexIndex-1];
        out_vertices.push_back(vertex);
    }

    valid = true;
}

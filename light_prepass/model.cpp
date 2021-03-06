#include <iostream>

#include "model.hpp"
#include "shader.hpp"
#include "window.hpp"
#include "utils.hpp"

#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl3.h>
#include "glm/glm.hpp"

FILE* file;

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

void Model::loadFace() {
    std::string vertex1, vertex2, vertex3;
    unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
    int matches = fscanf(
        file,
        "%d/%d/%d %d/%d/%d %d/%d/%d\n",
        &vertexIndex[0], &uvIndex[0], &normalIndex[0],
        &vertexIndex[1], &uvIndex[1], &normalIndex[1],
        &vertexIndex[2], &uvIndex[2], &normalIndex[2]
        );
    // if (matches != 9) return false;

    vertexIndices.push_back(vertexIndex[0]);
    vertexIndices.push_back(vertexIndex[1]);
    vertexIndices.push_back(vertexIndex[2]);
    uvIndices.push_back(uvIndex[0]);
    uvIndices.push_back(uvIndex[1]);
    uvIndices.push_back(uvIndex[2]);
    normalIndices.push_back(normalIndex[0]);
    normalIndices.push_back(normalIndex[1]);
    normalIndices.push_back(normalIndex[2]);
}

void Model::setupBuffers() {
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.size(), data.data(), GL_STATIC_DRAW);

    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*8, (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float)*8, (void*)(sizeof(float)*3));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float)*8, (void*)(sizeof(float)*6));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
}

void Model::load(std::string filename, bool flipUV_y) {
    std::string modelFilename = "models/" + filename + ".obj";
    file = fopen(const_cast<char*>(modelFilename.c_str()), "r");
    if (file == NULL) {
        throw std::exception();
    }

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
            loadFace();
        }
    }

    for (unsigned int i=0; i<vertexIndices.size(); i++) {
        unsigned int vertexIndex = vertexIndices[i];
        unsigned int normalIndex = normalIndices[i];
        unsigned int uvIndex = uvIndices[i];
        glm::vec3 vertex = temp_vertices[vertexIndex-1];
        // out_vertices.push_back(vertex);
        data.push_back(vertex.x);
        data.push_back(vertex.y);
        data.push_back(vertex.z);
        glm::vec3 normal = temp_normals[normalIndex-1];
        // out_vertices.push_back(normal);
        data.push_back(normal.x);
        data.push_back(normal.y);
        data.push_back(normal.z);
        glm::vec2 uv = temp_uvs[uvIndex-1];
        // out_vertices.push_back(glm::vec3(uv.x, uv.y, 0));
        data.push_back(uv.x);

        float uvy = uv.y;
        if (flipUV_y) {
            uvy = 1 - uvy;
        }

        data.push_back(uvy);
    }
}

RenderTexture* loadTexture(std::string filename) {
    if (fileExists(filename)) {
        return RenderTexture::loadAlbedo(filename);
    }

    return NULL;
}

void Model::loadTextures(std::string filename) {
    rt_Albedo = loadTexture("images/" + filename + "_albedo.png");
}

Model::Model(std::string filename, Shader* _shader, bool flipUV_y) {
    shader = _shader;

    try {
        load(filename, flipUV_y);
    } catch (...) {
        throw;
    }

    setupBuffers();
    loadTextures(filename);
}

void Model::draw() {
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBindVertexArray(vertexArray);
    glDrawArrays(GL_TRIANGLES, 0, data.size() / 8);
}

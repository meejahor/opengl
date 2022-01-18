#include <iostream>

#include "model.hpp"
#include "shader.hpp"
#include "window.hpp"
#include "utils.hpp"

#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl3.h>
#include "glm/glm.hpp"

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

void Model::load(std::string filename) {
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
        data.push_back(1-uv.y);
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

Model::Model(std::string filename, Shader* _shader) {
    shader = _shader;

    try {
        load(filename);
    } catch (...) {
        throw;
    }

    setupBuffers();
    loadTextures(filename);
}

void Model::draw(bool uvs) {
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBindVertexArray(vertexArray);

    // if (uvs) {
    //     glEnableVertexAttribArray(2);
    // } else {
    //     glDisableVertexAttribArray(2);
    // }
    
    glDrawArrays(GL_TRIANGLES, 0, data.size() / 8);
}

void Model::renderToLightmap(Light* light, glm::mat4 const& matrixModel) {
    shaderRenderToLightmap->use();
    shaderRenderToLightmap->setMatricesForLightmap(matrixModel, light->matrixViewProjection * matrixModel);
    glCullFace(GL_FRONT);
    draw(true);
    glCullFace(GL_BACK);
}

void Model::renderWithShadow(Light* light, glm::mat4 const& matrixModel) {
    shader->use();
    shader->setMatricesForScreenRenderingWithLighting(
        matrixModel,
        window->matrixViewProjection * matrixModel,
        light->matrixViewProjection * matrixModel,
        light->position,
        light->direction
        );
    light->useShadowMap();
    draw(true);
}

void Model::showLightmap(glm::mat4 const& matrixModel, RenderTexture* rt) {
    shaderShowLightmap->use();
    shaderShowLightmap->setMatricesForScreenRenderingNoLighting(matrixModel, window->matrixViewProjection * matrixModel);
    rt->showLightmap();
    // shader->setDepthNormalsTextures(rt->depth, rt->normals);
    draw(true);
}

void Model::renderPositionNormalsAlbedo(glm::mat4 const& matrixModel, RenderTexture* rt) {
    shaderRenderPositionNormalsAlbedo->setMatricesForScreen(matrixModel, window->matrixViewProjection * matrixModel);
    if (rt_Albedo != NULL) {
        rt_Albedo->useAlbedo();
    }
    draw(true);
}

void Model::showPosition(glm::mat4 const& matrixModel, RenderTexture* rt) {
    shaderShowPosition->use();
    shaderShowPosition->setMatricesForScreenRenderingNoLighting(matrixModel, window->matrixViewProjection * matrixModel);
    rt->showPosition();
    draw(true);
}

void Model::showNormals(glm::mat4 const& matrixModel, RenderTexture* rt) {
    shaderShowTexture->use();
    shaderShowTexture->setMatricesForScreenRenderingNoLighting(matrixModel, window->matrixViewProjection * matrixModel);
    rt->showNormals();
    draw(true);
}

void Model::showAlbedo(glm::mat4 const& matrixModel, RenderTexture* rt) {
    shaderShowTexture->use();
    shaderShowTexture->setMatricesForScreenRenderingNoLighting(matrixModel, window->matrixViewProjection * matrixModel);
    rt->showAlbedo();
    draw(true);
}

void Model::renderLightSphere(glm::mat4 const& matrixModel, RenderTexture* rt) {
    shaderRenderLightSphere->setMatricesForScreen(matrixModel, window->matrixViewProjection * matrixModel);
    draw(true);
}

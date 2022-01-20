#include "rendering.hpp"
#include "window.hpp"
#include "shader.hpp"
#include "light.hpp"

RenderTexture* rt_PositionNormalsAlbedo;

void Rendering::init() {
    rt_PositionNormalsAlbedo = RenderTexture::createPositionNormalsAlbedo(windowWidth, windowHeight);
}

void Rendering::beginLightmaps() {
    shaderRenderToLightmap->use();
}

void Rendering::renderObjectToLightmap(Object* object, Light* light) {
    shaderRenderToLightmap->setMatricesForLightmap(
        object->modelMatrix,
        light->matrixViewProjection * object->modelMatrix
        );
    light->texture->beginRenderingLightmap();
    object->model->renderToLightmap();
}

void Rendering::beginPositionsNormalAlbedo() {
    shaderRenderPositionNormalsAlbedo->use();
    rt_PositionNormalsAlbedo->beginRenderingPositionNormalsAlbedo();
}

void Rendering::renderObjectToPositionsNormalAlbedo(Object* object) {
    shaderRenderPositionNormalsAlbedo->setMatricesForScreen(
        object->modelMatrix,
        window->matrixViewProjection * object->modelMatrix
        );
    object->model->renderPositionNormalsAlbedo();
}

void Rendering::beginLightSpheres() {
    shaderRenderLightSphere->use();
    shaderRenderLightSphere->setTextureSize(glm::vec2(windowWidth, windowHeight));
    shaderRenderLightSphere->setPositionNormalsTextures();
    rt_PositionNormalsAlbedo->beginRenderingLighting();
}

void Rendering::renderLightSphere(Light* light) {
    light->setShaderPositionAndRadius();
    shaderRenderLightSphere->setMatricesForScreen(
        objectLightSphere->modelMatrix,
        window->matrixViewProjection * objectLightSphere->modelMatrix
        );
    objectLightSphere->model->renderLightSphere();
}

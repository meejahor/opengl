#include "rendering.hpp"
#include "window.hpp"
#include "shader.hpp"

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

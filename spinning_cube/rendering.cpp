#include "rendering.hpp"
#include "window.hpp"
#include "shader.hpp"
#include "light.hpp"

RenderTexture* rt_PositionNormalsAlbedo;
RenderTexture* rt_TorchCookie;

Object* objectLightSphere;

void Rendering::init() {
    rt_PositionNormalsAlbedo = RenderTexture::createPositionNormalsAlbedo(windowWidth, windowHeight);
    rt_TorchCookie = RenderTexture::loadCookie("images/torch_cookie.png");

    try {
        Model* modelLightSphere = new Model("sphere");
        objectLightSphere = new Object(modelLightSphere);
    } catch (...) {
        throw;
    }
}

void Rendering::beginLightmaps() {
    shaderRenderToLightmap->use();
    glCullFace(GL_FRONT);
}

void Rendering::renderObjectToLightmap(Object* object, Light* light) {
    shaderRenderToLightmap->setMatricesForLightmap(
        object->modelMatrix,
        light->matrixViewProjection * object->modelMatrix
        );
    light->texture->beginRenderingLightmap();
    object->model->draw();
}

void Rendering::endLightmaps() {
    glCullFace(GL_BACK);
}

void Rendering::beginPositionNormalsAlbedo() {
    shaderRenderPositionNormalsAlbedo->use();
    rt_PositionNormalsAlbedo->beginRenderingPositionNormalsAlbedo();
}

void Rendering::renderObjectToPositionNormalsAlbedo(Object* object) {
    shaderRenderPositionNormalsAlbedo->setMatricesForScreen(
        object->modelMatrix,
        window->matrixViewProjection * object->modelMatrix
        );

    object->model->rt_Albedo->showAlbedo();
    object->model->draw();
}

void Rendering::beginLightSpheres() {
    shaderRenderLightSphere->use();
    rt_PositionNormalsAlbedo->beginRenderingLighting();
    // glDisable(GL_CULL_FACE);
    // glDisable(GL_DEPTH_TEST);
}

void Rendering::renderLightSphere(Light* light) {
    shaderRenderLightSphere->setMatricesForScreenAndLight(
        objectLightSphere->modelMatrix,
        window->matrixViewProjection * objectLightSphere->modelMatrix,
        light->matrixViewProjection
        );

    objectLightSphere->moveTo(light->position);
    objectLightSphere->setScale(light->radius);
    objectLightSphere->update();
    shaderRenderLightSphere->setLightPosAndRadius(light->position, light->radius);
    light->texture->showLightmap();
    rt_TorchCookie->showCookie();
    objectLightSphere->model->draw();
}

void Rendering::endLightSpheres() {
    RenderTexture::setDefaultDrawBuffersAndTexture();
    // glEnable(GL_CULL_FACE);
    // glEnable(GL_DEPTH_TEST);
}

void Rendering::showLightmap(Object* plane, Light* light) {
    shaderShowLightmap->use();
    shaderShowLightmap->setMatricesForScreenRenderingNoLighting(
        plane->modelMatrix,
        window->matrixViewProjection * plane->modelMatrix
        );
    light->texture->showLightmap();
    plane->model->draw();
}

void Rendering::showPosition(Object* plane) {
    shaderShowPosition->use();
    shaderShowLightmap->setMatricesForScreenRenderingNoLighting(
        plane->modelMatrix,
        window->matrixViewProjection * plane->modelMatrix
        );
    rt_PositionNormalsAlbedo->showPosition();
    plane->model->draw();
}

void Rendering::showNormals(Object* plane) {
    shaderShowTexture->use();
    shaderShowLightmap->setMatricesForScreenRenderingNoLighting(
        plane->modelMatrix,
        window->matrixViewProjection * plane->modelMatrix
        );
    rt_PositionNormalsAlbedo->showNormals();
    plane->model->draw();
}

void Rendering::showFinal(Object* plane) {
    shaderShowFinal->use();
    shaderShowFinal->setAlbedoLightingTextures();
    rt_PositionNormalsAlbedo->showFinal();
    plane->model->draw();
}

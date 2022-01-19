#include <iostream>

#include <SDL.h>
#define GL_SILENCE_DEPRECATION
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>

#include "window.hpp"
#include "shader.hpp"
#include "model.hpp"
#include "deltatime.hpp"
#include "object.hpp"
#include "renderTexture.hpp"
#include "light.hpp"
#include "rendering.hpp"

int main(int argc, char* argv[]) {
    try {
        window = new Window();
    } catch (...) {
        return 0;
    }

    shaderToScreen = new Shader("shaders/renderToScreen.vert", "shaders/renderToScreen.frag");
    shaderShowTexture = new Shader("shaders/showTexture.vert", "shaders/showTexture.frag");
    shaderShowLightmap = new Shader("shaders/showLightmap.vert", "shaders/showLightmap.frag");
    shaderRenderPositionNormalsAlbedo = new Shader("shaders/renderPositionNormalsAlbedo.vert", "shaders/renderPositionNormalsAlbedo.frag");
    shaderShowPosition = new Shader("shaders/showPosition.vert", "shaders/showPosition.frag");
    shaderRenderToLightmap = new Shader("shaders/renderToLightmap.vert", "shaders/renderToLightmap.frag");
    shaderRenderLightSphere = new Shader("shaders/renderLightSphere.vert", "shaders/renderLightSphere.frag");
    shaderShowFinal = new Shader("shaders/showFinal.vert", "shaders/showFinal.frag");

    Rendering::init();
    
    Light* light;
    try {
        light = new Light(
            glm::vec3(  3.0f,  3.0f,  0.0f),
            glm::vec3( -1.0f, -1.0f,  0.0f),
            60.0f,
            6,
            glm::vec3(  0.0f,  1.0f,  0.0f)
        );
    } catch (...) {
        std::cout << "couldn't create light" << std::endl;
        return 0;
    }

    Model* modelCube;
    try {
        modelCube = new Model("square_with_cube_smooth");
    } catch (...) {
        return 0;
    }

    Model* modelPlane;
    try {
        modelPlane = new Model("plane", NULL, false);
    } catch (...) {
        return 0;
    }

    Light::loadResources();

    Object* objectCube = new Object(modelCube);
    Object* objectPlaneLightmap = new Object(modelPlane, 1.5f, glm::vec3(-1.5f, 1.5f, 0));
    Object* objectPlanePosition = new Object(modelPlane, 1.5f, glm::vec3(1.5f, 1.5f, 0));
    Object* objectPlaneNormals = new Object(modelPlane, 1.5f, glm::vec3(-1.5f, -1.5f, 0));
    Object* objectPlaneAlbedo = new Object(modelPlane, 1.5f, glm::vec3(1.5f, -1.5f, 0));
    Object* objectPlaneFinal = new Object(modelPlane, 1.5f, glm::vec3(1.5f, -1.5f, 0));

    bool gameIsRunning = true;

    deltaTimeInit();

    while (gameIsRunning) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                gameIsRunning = false;
            }
            // if (event.type == SDL_KEYDOWN) {
            //     objectCube->update();
            // }
        }

        deltaTimeUpdate();

        objectCube->update();

        Rendering::beginLightmaps();
        Rendering::renderObjectToLightmap(objectCube, light);

        Rendering::beginPositionsNormalAlbedo();
        Rendering::renderObjectToPositionsNormalAlbedo(objectCube);

        // shaderRenderPositionNormalsAlbedo->use();
        // rt_PositionNormalsAlbedo->beginRenderingPositionNormalsAlbedo();
        // objectCube->renderPositionNormalsAlbedo(rt_PositionNormalsAlbedo);

        shaderRenderLightSphere->use();
        shaderRenderLightSphere->setAlbedoNormalsTextures();
        rt_PositionNormalsAlbedo->beginRenderingLighting();
        light->renderLightSphere(rt_PositionNormalsAlbedo);

        // render camera views of objects
        // shader->use();
        window->activate();
        window->clear();

        RenderTexture::resetDrawBuffer();

        // objectCube->render(window->matrixViewProjection, shader);
        // GLuint texID = glGetUniformLocation(shaderTexture, "renderedTexture");
        // glActiveTexture(GL_TEXTURE0);
        // glUniform1i(texID, 0);

        // window->activate();
        // objectCube->renderWithShadow(light);
        // objectPlane->showDepthNormals(rt_DepthNormals);

        objectPlaneLightmap->showLightmap(light);
        objectPlanePosition->showPosition(rt_PositionNormalsAlbedo);
        objectPlaneNormals->showNormals(rt_PositionNormalsAlbedo);
        // objectPlaneAlbedo->showAlbedo(rt_PositionNormalsAlbedo);
        objectPlaneFinal->showFinal(rt_PositionNormalsAlbedo);

        // show back buffer
        window->swap();
    }

    window->destroy();
    SDL_Quit();
    return 0;
}

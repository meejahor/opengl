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

    Shader::loadShaders();
    Rendering::init();
    
    Light* light = new Light(
        glm::vec3(  3.0f,  3.0f,  0.0f),
        glm::vec3( -1.0f, -1.0f,  0.0f),
        60.0f,
        6,
        glm::vec3(  0.0f,  1.0f,  0.0f)
        );

    Model* modelCube = new Model("square_with_cube_smooth");
    Model* modelPlane = new Model("plane", NULL, false);

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
        Rendering::endLightmaps();

        Rendering::beginPositionNormalsAlbedo();
        Rendering::renderObjectToPositionNormalsAlbedo(objectCube);

        Rendering::beginLightSpheres();
        Rendering::renderLightSphere(light);

        window->activate();
        window->clear();

        RenderTexture::resetDrawBuffer();

        Rendering::showLightmap(objectPlaneLightmap, light);
        Rendering::showPosition(objectPlanePosition);
        Rendering::showNormals(objectPlaneNormals);
        Rendering::showFinal(objectPlaneFinal);

        // make rendered buffer visible
        window->swap();
    }

    window->destroy();
    SDL_Quit();
    return 0;
}

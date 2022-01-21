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
    // objectCube->rotate(45, glm::vec3(1, 0, 0));
    // objectCube->moveTo(glm::vec3(0, -1, 0));

    Object* objectPlaneLightmap = new Object(modelPlane);
    Object* objectPlanePosition = new Object(modelPlane);
    Object* objectPlaneNormals = new Object(modelPlane);
    Object* objectPlaneAlbedo = new Object(modelPlane);
    Object* objectPlaneFinal = new Object(modelPlane);

    Object* objectPlaneFinalLarge = new Object(modelPlane);
    // objectPlaneFinalLarge->setScale(3);
    objectPlaneFinalLarge->update();

    bool gameIsRunning = true;

    DeltaTime::init();

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

        DeltaTime::update();

        objectCube->rotate(45 * DeltaTime::time, glm::vec3(0, 1, 0));
        objectCube->update();
        // objectCube->update();

        Rendering::beginLightmaps();
        Rendering::renderObjectToLightmap(objectCube, light);
        Rendering::endLightmaps();

        Rendering::beginPositionNormalsAlbedo();
        Rendering::renderObjectToPositionNormalsAlbedo(objectCube);

        Rendering::beginLightSpheres();
        Rendering::renderLightSphere(light);
        Rendering::endLightSpheres();

        window->activate();
        window->clear();

        // Rendering::showLightmap(objectPlaneLightmap, light);
        // Rendering::showPosition(objectPlanePosition);
        // Rendering::showNormals(objectPlaneNormals);
        // Rendering::showFinal(objectPlaneFinal);
        // objectPlaneFinalLarge->update();
        Rendering::showFinal(objectPlaneFinalLarge);

        // make rendered buffer visible
        window->swap();
    }

    window->destroy();
    SDL_Quit();
    return 0;
}

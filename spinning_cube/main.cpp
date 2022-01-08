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

Shader* shaderToScreen;
Shader* shaderShowTexture;
Shader* shaderShowDepth;

int main(int argc, char* argv[]) {
    try {
        window = new Window(800, 800);
    } catch (...) {
        return 0;
    }

    Light::loadDepthShader();

    shaderToScreen = new Shader("shaders/renderToScreen.vert", "shaders/renderToScreen.frag");
    shaderShowTexture = new Shader("shaders/showTexture.vert", "shaders/showTexture.frag");
    shaderShowDepth = new Shader("shaders/showDepth.vert", "shaders/showDepth.frag");

    RenderTexture* rt = RenderTexture::createColorTexture(1024, 1024);

    Light* light;
    try {
        light = new Light(
            glm::vec3(  0.0f,  5.0f,  0.0f),
            glm::vec3(  0.0f, -1.0f,  0.0f),
            45.0f,
            glm::vec3(  0.0f,  0.0f, -1.0f)
        );
    } catch (...) {
        std::cout << "couldn't create light" << std::endl;
        return 0;
    }

    Model* modelCube;
    try {
        modelCube = new Model("cube.obj", shaderToScreen);
    } catch (...) {
        return 0;
    }

    Model* modelPlane;
    try {
        modelPlane = new Model("plane.obj", shaderShowDepth);
    } catch (...) {
        return 0;
    }

    Object* objectCube = new Object(modelCube);
    Object* objectPlane = new Object(modelPlane, glm::vec3(2, 0, 0));

    bool gameIsRunning = true;

    deltaTimeInit();

    while (gameIsRunning) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                gameIsRunning = false;
            }
        }

        deltaTimeUpdate();

        objectCube->update();

        // render light views of objects
        // light->activate();
        // depthShader->use();
        // objectCube->renderToLightmap(light);

        // render camera views of objects
        // shader->use();
        window->activate();
        window->clear();

        // objectCube->render(window->matrixViewProjection, shader);
        // GLuint texID = glGetUniformLocation(shaderTexture, "renderedTexture");
        // glActiveTexture(GL_TEXTURE0);
        // glUniform1i(texID, 0);

        // window->activate();
        shaderToScreen->use();
        objectCube->render();

        shaderShowDepth->use();
        objectPlane->render(light->texture);
        // show back buffer
        window->swap();
    }

    window->destroy();
    SDL_Quit();
    return 0;
}

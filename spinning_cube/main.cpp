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

Shader* shader;
Shader* shaderTexture;

int main(int argc, char* argv[]) {
    Window* window;
    try {
        window = new Window(800, 800);
    } catch (...) {
        return 0;
    }

    Light::loadDepthShader();

    shader = new Shader("shaders/vert.vert", "shaders/frag.frag");
    shaderTexture = new Shader("shaders/vert.vert", "shaders/texture.frag");

    RenderTexture* rt = RenderTexture::createColorTexture(1024, 1024);

    Light* light;
    try {
        light = new Light(
            glm::vec3( 5.0f, 0.0f, 0.0f),
            glm::vec3(-1.0f, 0.0f, 0.0f),
            45.0f
        );
    } catch (...) {
        std::cout << "couldn't create light" << std::endl;
        return 0;
    }

    Model* modelCube;
    try {
        modelCube = new Model("cube.obj", shader);
    } catch (...) {
        return 0;
    }

    Model* modelPlane;
    try {
        modelPlane = new Model("plane.obj", shaderTexture);
    } catch (...) {
        return 0;
    }

    Object* objectCube = new Object(modelCube);
    Object* objectPlane = new Object(modelPlane);

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
        light->activate();
        // depthShader->use();
        depthShader->use();
        objectCube->render(light->matrixViewProjection, depthShader);

        // render camera views of objects
        // shader->use();
        window->activate();
        window->clear();

        // objectCube->render(window->matrixViewProjection, shader);
        // GLuint texID = glGetUniformLocation(shaderTexture, "renderedTexture");
        // glActiveTexture(GL_TEXTURE0);
        // glUniform1i(texID, 0);

        // window->activate();
        shader->use();
        objectCube->render(window->matrixViewProjection, shader);

        shaderTexture->use();
        objectPlane->render(window->matrixViewProjection, shaderTexture, light->texture);
        // show back buffer
        window->swap();
    }

    window->destroy();
    SDL_Quit();
    return 0;
}

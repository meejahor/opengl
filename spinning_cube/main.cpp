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
Shader* shaderShowNormals;
Shader* shaderRenderDepthNormals;
Shader* shaderShowDepthNormals;

int windowWidth = 800;
int windowHeight = 800;

int main(int argc, char* argv[]) {
    try {
        window = new Window(windowWidth, windowHeight);
    } catch (...) {
        return 0;
    }

    Light::loadDepthShader();

    shaderToScreen = new Shader("shaders/renderToScreen.vert", "shaders/renderToScreen.frag");
    shaderShowTexture = new Shader("shaders/showTexture.vert", "shaders/showTexture.frag");
    shaderShowDepth = new Shader("shaders/showDepth.vert", "shaders/showDepth.frag");
    shaderShowNormals = new Shader("shaders/showNormals.vert", "shaders/showNormals.frag");
    shaderRenderDepthNormals = new Shader("shaders/renderDepthNormals.vert", "shaders/renderDepthNormals.frag");
    shaderShowDepthNormals = new Shader("shaders/showDepthNormals.vert", "shaders/showDepthNormals.frag");

    RenderTexture* depthNormals = RenderTexture::createDepthNormals(windowWidth, windowHeight);

    Light* light;
    try {
        light = new Light(
            glm::vec3(  0.0f,  5.0f,  0.0f),
            glm::vec3(  0.0f, -1.0f,  0.0f),
            60.0f,
            glm::vec3(  0.0f,  0.0f,  1.0f)
        );
    } catch (...) {
        std::cout << "couldn't create light" << std::endl;
        return 0;
    }

    Model* modelCube;
    try {
        modelCube = new Model("square_with_cube_smooth.obj", shaderRenderDepthNormals);
    } catch (...) {
        return 0;
    }

    Model* modelPlane;
    try {
        modelPlane = new Model("plane.obj", shaderShowDepthNormals);
    } catch (...) {
        return 0;
    }

    Object* objectCube = new Object(modelCube);
    // Object* objectPlane = new Object(modelPlane, glm::vec3(2, -2, 0));
    Object* objectPlane = new Object(
        modelPlane,
        glm::vec3(0, 0, 0),
        glm::vec3(3)
        );

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

        // render light views of objects
        light->activate();
        objectCube->renderToLightmap(light);
        objectCube->renderColorDepthNormals(depthNormals);

        // render camera views of objects
        // shader->use();
        window->activate();
        window->clear();

        // objectCube->render(window->matrixViewProjection, shader);
        // GLuint texID = glGetUniformLocation(shaderTexture, "renderedTexture");
        // glActiveTexture(GL_TEXTURE0);
        // glUniform1i(texID, 0);

        // window->activate();
        // objectCube->renderWithShadow(light);
        objectPlane->renderNormals(depthNormals);
        // show back buffer
        window->swap();
    }

    window->destroy();
    SDL_Quit();
    return 0;
}

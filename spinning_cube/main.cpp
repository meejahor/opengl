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
    shaderShowLightmap = new Shader("shaders/showLightmap.vert", "shaders/showLightmap.frag");
    shaderRenderDepthNormals = new Shader("shaders/renderDepthNormals.vert", "shaders/renderDepthNormals.frag");
    shaderShowDepthNormals = new Shader("shaders/showDepthNormals.vert", "shaders/showDepthNormals.frag");

    RenderTexture* rt_DepthNormals = RenderTexture::createDepthNormals(windowWidth, windowHeight);

    Light* light;
    try {
        light = new Light(
            glm::vec3(  5.0f,  5.0f,  0.0f),
            glm::vec3( -1.0f, -1.0f,  0.0f),
            60.0f,
            glm::vec3(  0.0f,  0.0f,  1.0f)
        );
    } catch (...) {
        std::cout << "couldn't create light" << std::endl;
        return 0;
    }

    Model* modelCube;
    try {
        modelCube = new Model("square_with_cube_smooth.obj");
    } catch (...) {
        return 0;
    }

    Model* modelPlane;
    try {
        modelPlane = new Model("plane.obj");
    } catch (...) {
        return 0;
    }

    Object* objectCube = new Object(modelCube);
    Object* objectPlaneLightmap = new Object(modelPlane, 1, glm::vec3(-1.5f, 0, 0));
    Object* objectPlaneDepthNormals = new Object(modelPlane, 1, glm::vec3(1.5f, 0, 0));

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
        light->beginLightmap();
        objectCube->renderToLightmap(light);

        shaderRenderDepthNormals->use();
        rt_DepthNormals->beginDepthNormals();
        objectCube->renderDepthNormals(rt_DepthNormals);

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
        // objectPlane->showDepthNormals(rt_DepthNormals);
        objectPlaneLightmap->showLightmap(light->texture);
        objectPlaneDepthNormals->showDepthNormals(rt_DepthNormals);
        // show back buffer
        window->swap();
    }

    window->destroy();
    SDL_Quit();
    return 0;
}

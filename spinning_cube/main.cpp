// On linux compile with:
// g++ -std=c++17 main.cpp glad/src/glad.c -I./glad/include -o prog -lSDL2 -ldl
// On windows compile with (if using mingw)
// g++ main.cpp ./glad/src/glad.c -I./glad/include -o prog.exe -lmingw32 -lSDL2main -lSDL2

// https://stackoverflow.com/questions/31933141/opengl-es2-black-screen-c-osx-sdl2

// C++ Standard Libraries
#include <iostream>

#include "GLShader.hpp"

// Third-party library
#include <SDL.h>
// #include <GL/glew.h>
// #include <SDL_opengl.h>
#define GL_SILENCE_DEPRECATION
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

// Include GLAD
// #include <glad/glad.h>

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_GLContext context;

SDL_Rect makeRect(int width, int height) {
    SDL_Rect rectangle;
    rectangle.w = width;
    rectangle.h = height;
    rectangle.x = -width/2;
    rectangle.y = -height/2;
    return rectangle;
}

float vertices[] = {
    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
    -0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
};

unsigned int indices[] = {
    0, 1, 3, 0, 3, 2,
    5, 4, 6, 5, 6, 7,
};

GLuint vertAttributes;
GLuint vertBuffer;
GLuint indexBuffer;
GLuint shader;

glm::mat4 projectionMatrix;

Uint64 timeNow = SDL_GetPerformanceCounter();
Uint64 timeLast = 0;
float deltaTime = 0;

void initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not be initialized: " << SDL_GetError();
    } else {
        std::cout << "SDL video system is ready to go\n";
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,24);

    window = SDL_CreateWindow(
        "C++ SDL2 Window",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,
        800,
        SDL_WINDOW_SHOWN
        );

    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
        );

    context = SDL_GL_CreateContext(window);
    // gladLoadGLLoader(SDL_GL_GetProcAddress);
}

void initGL() {
    // SDL_GL_MAT
    // glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();

    // projectionMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.1, 0.1, 0.1));
    projectionMatrix = glm::perspective(glm::radians(70.0f), 800.0f/800.0f, 0.0001f, 1000.0f);
    // projectionMatrix *= glm::scale(glm::mat4(1.0f), glm::vec3(0.01, 0.01, 0.01));
    // projectionMatrix = glm::rotate(projectionMatrix, glm::radians(45), glm::vec3(0.0, 0.0, 1.0));

    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);

    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); 
    glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
    glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

    // glm::mat4 view;
    projectionMatrix *= glm::lookAt(
        cameraPos,
        cameraTarget,
        cameraUp
        );
}

int main(int argc, char* argv[]) {

    initSDL();
    initGL();

    glGenVertexArrays(1, &vertAttributes);
    glGenBuffers(1, &vertBuffer);
    glGenBuffers(1, &indexBuffer);

    glBindVertexArray(vertAttributes);
    glBindBuffer(GL_ARRAY_BUFFER, vertBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // glDisableVertexAttribArray(0);


    // glVertexAttribPointer(0, 1, GL_INT, GL_FALSE, sizeof(int), (void*)0);

    // glBindVertexArray(vertAttributes);

    // glGenBuffers(1, &VBO);  
    // glBindBuffer(GL_ARRAY_BUFFER, VBO);

    shader = LoadShader("vert.shader", "frag.shader");

    SDL_Rect rectangle = makeRect(200, 200);

    // Request a window to be created for our platform
    // The parameters are for the title, x and y position,
    // and the width and height of the window.

    bool gameIsRunning = true;
    float rotation = 0;
    const float SPEED = 90;

    while (gameIsRunning) {

        timeLast = timeNow;
        timeNow = SDL_GetPerformanceCounter();
        deltaTime = (float)((timeNow - timeLast) / (double)SDL_GetPerformanceFrequency());

        glViewport(0, 0, 800, 800);

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                gameIsRunning = false;
            }
        }

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        rotation += SPEED * deltaTime;
        glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(1, 0, 1));
        // glm::mat4 transformMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -2));
        glm::mat4 matrix = projectionMatrix * rotationMatrix;

        unsigned int matrixID = glGetUniformLocation(shader, "transform");
        glUniformMatrix4fv(matrixID, 1, GL_FALSE, glm::value_ptr(matrix));

        // glColor(0.0f,0.0f,0.0f,1.0f);
        glUseProgram(shader);
        // glBindBuffer(GL_ARRAY_BUFFER, vertBuffer);
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        // glDrawElements(GL_TRIANGLES, 2, GL_UNSIGNED_BYTE, 0);
        glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);
        // glBindVertexArray(0);

        // SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        // SDL_RenderClear(renderer);

        // SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        // SDL_RenderFillRect(renderer, &rectangle);

        // SDL_RenderPresent(renderer);

        // glfwSwapBuffers(window);

        SDL_GL_SwapWindow(window);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

#include <iostream>
#include <fstream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/ext.hpp"

#include "window.hpp"

// glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); 

glm::mat4 calcViewProjection(glm::vec3 position, glm::vec3 lookAt, float fov, glm::vec3 up) {
    glm::vec3 direction = glm::normalize(position - lookAt);
    glm::vec3 viewRight = glm::normalize(glm::cross(up, direction));
    glm::vec3 viewUp = glm::cross(direction, viewRight);

    // std::cout << glm::to_string(position) << std::endl;
    // std::cout << glm::to_string(position - lookAt) << std::endl;
    // std::cout << glm::to_string(direction) << std::endl;
    // std::cout << glm::to_string(viewRight) << std::endl;
    // std::cout << glm::to_string(viewUp) << std::endl;

    glm::mat4 matrixView = glm::lookAt(
        position,
        lookAt,
        viewUp
        );

    glm::mat4 matrixProjection = glm::perspective(
        glm::radians(fov),
        float(windowWidth / windowHeight),
        0.1f,
        100.0f
        );

    return matrixProjection * matrixView;
}

bool fileExists(std::string filename) {
    return std::filesystem::exists(filename);
}

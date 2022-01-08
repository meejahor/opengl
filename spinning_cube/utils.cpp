#include <iostream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/ext.hpp"

// glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); 

glm::mat4 calcViewProjection(glm::vec3 position, glm::vec3 lookAt, float fov, glm::vec3 up) {
    glm::vec3 direction = glm::normalize(position - lookAt);
    glm::vec3 viewRight = glm::normalize(glm::cross(up, direction));
    glm::vec3 viewUp = glm::cross(direction, viewRight);

    std::cout << glm::to_string(direction) << std::endl;
    std::cout << glm::to_string(viewRight) << std::endl;
    std::cout << glm::to_string(viewUp) << std::endl;

    glm::mat4 matrixView = glm::lookAt(
        position,
        direction,
        viewUp
        );

    glm::mat4 matrixProjection = glm::perspective(
        glm::radians(70.0f),
        800.0f/800.0f,
        0.0001f,
        1000.0f
        );

    return matrixProjection * matrixView;
}

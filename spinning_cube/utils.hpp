#ifndef UTILS_H
#define UTILS_H

#include "glm/glm.hpp"

glm::mat4 calcViewProjection(glm::vec3 position, glm::vec3 lookAt, float fov);

#endif

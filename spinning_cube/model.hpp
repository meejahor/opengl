#include <vector>
#include "glm/glm.hpp"

class Model {
    public:
    std::vector<glm::vec3> out_vertices;
    std::vector<glm::vec2> out_uvs;
    std::vector<glm::vec3> out_normals;
    Model(const char *filename);
};

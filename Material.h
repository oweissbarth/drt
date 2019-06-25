#pragma once

#include <glm/glm.hpp>

class Material
{
public:
    Material(glm::vec3 color, glm::vec3 emissive, unsigned int start_index = 0);
    glm::vec3 color;
    glm::vec3 emissive;
    int start_index;
};

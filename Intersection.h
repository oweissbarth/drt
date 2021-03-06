#pragma once

#include <glm/glm.hpp>
#include "Mesh.h"

class Intersection
{
public:
    Intersection(glm::vec3 position, Mesh* object, unsigned long face_index, float distance);
    glm::vec3 position;
    Mesh* object;
    unsigned long face_index;
    float distance;
};

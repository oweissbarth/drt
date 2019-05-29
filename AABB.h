#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "Ray.h"

class AABB
{
public:
    AABB(std::vector<glm::vec3*> points);
    bool intersect(Ray* ray);
    glm::vec3 min;
    glm::vec3 max;
};
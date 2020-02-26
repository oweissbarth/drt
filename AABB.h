#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "Ray.h"

class AABB
{
public:
    AABB(std::vector<glm::vec3*> points);
    bool intersect(Ray* ray);
    void get_preview(std::vector<glm::vec3>* verts);
    void ensure_non_zero(float epsilon = 0.0001);
    glm::vec3 min;
    glm::vec3 max;
};

#pragma once

#include "Intersection.h"
#include "AABB.h"

class BVHNode
{
public:
    //BVHNode();

    virtual ~BVHNode() {}

    Intersection* traverse(Ray* ray);

    virtual Intersection* intersect_content(Ray* ray) = 0;

    void get_preview(std::vector<glm::vec3>* verts);

    AABB* aabb;
    std::vector<BVHNode*> children;
    bool is_leaf;

    const unsigned int child_count = 4;
};

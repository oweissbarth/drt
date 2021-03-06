#pragma once

#include "Intersection.h"
#include "AABB.h"

#define K 4

class BVHNode
{
public:
    //BVHNode();

    virtual ~BVHNode() {}

    Intersection* traverse(Ray* ray);

    std::vector<unsigned int> kMeans(std::vector<glm::vec3> content_means);

    virtual Intersection* intersect_content(Ray* ray) = 0;

    void get_preview(std::vector<glm::vec3>* verts);

    AABB* aabb;
    bool is_leaf;

    const unsigned int child_count = 4;
};

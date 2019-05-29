#pragma once

#include "AABB.h"
#include "Object.h"
#include "Intersection.h"
#include <vector>


class BVHNode
{
public:
    BVHNode(std::vector<glm::uvec3> faces, std::vector<unsigned long> face_indices, std::vector<Object*> objects);
    AABB* aabb;
    std::vector<BVHNode*> children;
    bool is_leaf;

    std::vector<glm::uvec3> faces;
    std::vector<unsigned long> face_indices;
    std::vector<Object*> objects;

    Intersection* traverse(Ray* ray);

    void get_preview(std::vector<glm::vec3>* verts);

private:
    void split();
    Intersection* intersect_faces(Ray* ray);
};

#pragma once

#include "AABB.h"
#include "Object.h"
#include "Intersection.h"
#include "BVHNode.h"
#include <vector>


class MeshBVHNode: public BVHNode
{
public:
    MeshBVHNode(std::vector<glm::uvec3> faces, std::vector<unsigned long> face_indices, Mesh* object);


    std::vector<glm::uvec3> faces;
    std::vector<unsigned long> face_indices;
    Mesh* object;


private:
    void split();
    Intersection* intersect_content(Ray* ray);
};

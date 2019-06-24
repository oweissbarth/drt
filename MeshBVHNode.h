#pragma once

#include "AABB.h"
#include "Object.h"
#include "Intersection.h"
#include "BVHNode.h"
#include <vector>


class MeshBVHNode: BVHNode
{
public:
    MeshBVHNode(std::vector<glm::uvec3> faces, std::vector<unsigned long> face_indices, Mesh* object);

    std::vector<MeshBVHNode*> children;


    std::vector<glm::uvec3> faces;
    std::vector<unsigned long> face_indices;
    Mesh* object;
    Intersection* traverse(Ray* ray);
    void get_preview(std::vector<glm::vec3>* verts);


private:
    void split();
    Intersection* intersect_content(Ray* ray);
};

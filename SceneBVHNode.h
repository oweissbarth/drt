#pragma once


#include "BVHNode.h"
#include "Object.h"
#include "MeshBVH.h"

class SceneBVHNode: BVHNode{
public:
    SceneBVHNode(std::vector<Mesh*> meshes);
    void split();
    std::vector<Mesh*> meshes;
    std::vector<MeshBVH*> mesh_bvhs;

    std::vector<SceneBVHNode*> children;

    Intersection* traverse(Ray* ray);


    void get_preview(std::vector<glm::vec3>* verts);

private:
    Intersection* intersect_content(Ray* ray);
};


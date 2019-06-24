#pragma once


#include "BVHNode.h"
#include "Object.h"
#include "MeshBVH.h"

class SceneBVHNode : public BVHNode
{
public:
    SceneBVHNode(std::vector<Mesh*> meshes);
    void split();
    std::vector<Mesh*> meshes;
    std::vector<MeshBVH*> mesh_bvhs;
private:
    Intersection* intersect_content(Ray* ray);
};


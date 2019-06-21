#pragma once


#include "BVHNode.h"
#include "Object.h"

class SceneBVHNode : public BVHNode
{
public:
    SceneBVHNode(std::vector<Mesh*> meshes);
    std::vector<Mesh*> meshes;
};


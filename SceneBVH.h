#pragma once

#include "BVH.h"
#include "Scene.h"
#include "SceneBVHNode.h"

class SceneBVH
{
public:
    SceneBVH(Scene* scene);
    Intersection* traverse(Ray* ray);
    SceneBVHNode* root;

    PreviewLines* get_preview();
};


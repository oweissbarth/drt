#pragma once

#include <vector>
#include "BVHNode.h"
#include "Scene.h"
#include "Intersection.h"
#include "preview/PreviewLines.h"

class BVH
{
public:
    BVH(Scene* scene);
    BVHNode* root;
    Intersection* traverse(Ray* ray);
    PreviewLines* get_preview();
};

#pragma once

#include "Intersection.h"
#include "preview/PreviewLines.h"
#include "BVHNode.h"

class BVH
{
public:
    virtual ~BVH() {}
    BVHNode* root;
    Intersection* traverse(Ray* ray);
    PreviewLines* get_preview();
};

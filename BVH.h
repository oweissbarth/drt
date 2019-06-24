#pragma once

#include "Intersection.h"
#include "preview/PreviewLines.h"
#include "BVHNode.h"

class BVH
{
public:
    virtual ~BVH() {}
    BVHNode* root;
    virtual Intersection* traverse(Ray* ray) = 0; // The ray is given in world space coordinates here
    PreviewLines* get_preview();
};

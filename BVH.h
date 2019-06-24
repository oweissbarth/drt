#pragma once

#include "Intersection.h"
#include "preview/PreviewLines.h"
#include "BVHNode.h"

template <typename T>

class BVH
{
public:
    virtual ~BVH() {}
    T* root;
    virtual Intersection* traverse(Ray* ray) = 0; // The ray is given in world space coordinates here
};

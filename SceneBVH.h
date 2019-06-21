#pragma once

#include "BVH.h"
#include "Scene.h"

class SceneBVH: public BVH
{
public:
    SceneBVH(Scene* scene);
};


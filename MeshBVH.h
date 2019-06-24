#pragma once

#include <vector>
#include "MeshBVHNode.h"
#include "Object.h"
#include "Intersection.h"
#include "preview/PreviewLines.h"
#include "BVH.h"

class MeshBVH: public BVH
{
public:
    MeshBVH(Mesh* mesh);

    glm::vec3 location;
    glm::quat rotation;
    glm::vec3 scale;

    glm::mat4 transform;
    glm::mat4 inv_transform;

    Mesh* mesh;

    Intersection * traverse(Ray *ray);
};

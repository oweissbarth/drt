#pragma once

#include <vector>
#include "MeshBVHNode.h"
#include "Object.h"
#include "Intersection.h"
#include "preview/PreviewLines.h"
#include "BVH.h"

class MeshBVH
{
public:
    MeshBVH(Mesh* mesh);

    glm::vec3 location;
    glm::quat rotation;
    glm::vec3 scale;

    glm::mat4 transform;
    glm::mat4 inv_transform;

    Mesh* mesh;
    MeshBVHNode* root;

    Intersection * traverse(Ray *ray);
    void get_preview(std::vector<glm::vec3>* verts);

};

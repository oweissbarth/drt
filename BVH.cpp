#include "BVH.h"


Intersection* BVH::traverse(Ray* ray){
    return this->root->traverse(ray);
}

PreviewLines* BVH::get_preview(){
    std::vector<glm::vec3> verts;

    this->root->get_preview(&verts);

    return new PreviewLines(verts);
}

#include "SceneBVHNode.h"
#include <glm/gtx/component_wise.hpp>


#define MAX_LEAF_SIZE 10


SceneBVHNode::SceneBVHNode(std::vector<Mesh*> meshes)
{

    this->meshes = meshes;
    std::vector<glm::vec3*> points(meshes.size()*2);

    for (unsigned int m = 0; m < meshes.size(); m++) {
        AABB aabb = meshes[m]->get_bounding_box();

        points[2*m] = &aabb.min;
        points[2*m+1] = &aabb.max;
    }

    this->aabb = new AABB(points);


    if(meshes.size() > MAX_LEAF_SIZE){
        this->is_leaf = false;
        this->split();
    }else{
        this->is_leaf = true;
    }
}

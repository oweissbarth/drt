#include "BVHNode.h"


Intersection* BVHNode::traverse(Ray* ray){
    if(!this->aabb->intersect(ray)){
        return nullptr;
    }

    if(this->is_leaf){
        return this->intersect_content(ray);
    }

    // NOTE this is naivly checking every child
    Intersection* bestIntersection = nullptr;
    for (unsigned long k = 0; k < this->child_count; k++) {
        Intersection* intersection = this->children[k]->traverse(ray);
        if(intersection != nullptr and (bestIntersection == nullptr or intersection->distance < bestIntersection->distance)){
            bestIntersection = intersection;
        }

    }
    return bestIntersection;
}

void BVHNode::get_preview(std::vector<glm::vec3> *verts)
{
    float minx = aabb->min.x;
    float miny = aabb->min.y;
    float minz = aabb->min.z;

    float maxx = aabb->max.x;
    float maxy = aabb->max.y;
    float maxz = aabb->max.z;

    //bottom
    verts->push_back(glm::vec3(minx, miny, minz));
    verts->push_back(glm::vec3(maxx, miny, minz));

    verts->push_back(glm::vec3(maxx, miny, minz));
    verts->push_back(glm::vec3(maxx, maxy, minz));

    verts->push_back(glm::vec3(maxx, maxy, minz));
    verts->push_back(glm::vec3(minx, maxy, minz));

    verts->push_back(glm::vec3(minx, maxy, minz));
    verts->push_back(glm::vec3(minx, miny, minz));


    //top
    verts->push_back(glm::vec3(minx, miny, maxz));
    verts->push_back(glm::vec3(maxx, miny, maxz));

    verts->push_back(glm::vec3(maxx, miny, maxz));
    verts->push_back(glm::vec3(maxx, maxy, maxz));

    verts->push_back(glm::vec3(maxx, maxy, maxz));
    verts->push_back(glm::vec3(minx, maxy, maxz));

    verts->push_back(glm::vec3(minx, maxy, maxz));
    verts->push_back(glm::vec3(minx, miny, maxz));

    //sides

    verts->push_back(glm::vec3(minx, miny, minz));
    verts->push_back(glm::vec3(minx, miny, maxz));

    verts->push_back(glm::vec3(minx, maxy, minz));
    verts->push_back(glm::vec3(minx, maxy, maxz));

    verts->push_back(glm::vec3(maxx, miny, minz));
    verts->push_back(glm::vec3(maxx, miny, maxz));

    verts->push_back(glm::vec3(maxx, maxy, minz));
    verts->push_back(glm::vec3(maxx, maxy, maxz));

    for (unsigned long c = 0; c < this->children.size(); c++) {
        this->children[c]->get_preview(verts);
    }


}

#include "BVHNode.h"
#include "utils.h"
#include <iostream>


#define K_MEANS_STEPS 5

Intersection* BVHNode::traverse(Ray* ray){
    //std::cout << "traversing bvh node"<< std::endl;
    if(!this->aabb->intersect(ray)){
        //std::cout << "did not hit" << std::endl;
        return nullptr;
    }
    //std::cout << "hit aabb"<< std::endl;

    if(this->is_leaf){
        //std::cout << "is leaf" << std::endl;
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

std::vector<unsigned int> BVHNode::kMeans(std::vector<glm::vec3> content_means){
    std::vector<glm::vec3> means(K);
    for(unsigned int k = 0; k < K; k++){
        means[k] = random_vec3(this->aabb->min, this->aabb->max);
    }

    std::vector<unsigned int> assignment(content_means.size());
    std::vector<unsigned long> face_count(K);

    for(unsigned int i = 0; i < K_MEANS_STEPS; i++){

        // assign faces to means
        for(unsigned long i = 0; i < content_means.size(); i++){
            float min_distance = std::numeric_limits<float>::infinity();
            for(unsigned int k = 0; k < K; k++){
                float distance = glm::distance(means[k], content_means[i]);
                if( distance < min_distance){
                    min_distance = distance;
                    assignment[i] = k;
                }
            }
        }

        // recompute means
        for (unsigned long k = 0; k < K; k++) {
            means[k] = glm::vec3(0);
            face_count[k] = 0;
            for(unsigned long f = 0; f < content_means.size(); f++){
                if(assignment[f] == k){
                    means[k] += content_means[f];
                    face_count[k]++;
                }
            }
            means[k] /= face_count[k];
        }
    }
    return assignment;
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

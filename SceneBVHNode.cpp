#include "SceneBVHNode.h"
#include <glm/gtx/component_wise.hpp>
#include <limits>

#include <glm/gtx/string_cast.hpp>

#include <iostream>

#define MAX_LEAF_SIZE 10


SceneBVHNode::SceneBVHNode(std::vector<Mesh*> meshes)
{

    this->meshes = meshes;


    std::vector<glm::vec3> minmax(meshes.size()*2);
    std::vector<glm::vec3*> points(meshes.size()*2);

    for (unsigned int m = 0; m < meshes.size(); m++) {
        AABB aabb = meshes[m]->get_world_bounding_box();
        minmax[2*m] = aabb.min;
        minmax[2*m+1] = aabb.max;
        points[2*m] = &minmax[2*m];
        points[2*m+1] = &minmax[2*m+1];
    }

    this->aabb = new AABB(points);
    std::cout << glm::to_string(aabb->min) << ", " << glm::to_string(aabb->max) << std::endl;

    if(meshes.size() > MAX_LEAF_SIZE){
        this->is_leaf = false;
        this->split();
    }else{
        this->is_leaf = true;
        for (unsigned int i = 0; i < meshes.size(); i++) {
            std::cout << "created mesh bvh " << meshes[i]->name << std::endl;
            mesh_bvhs.push_back(new MeshBVH(meshes[i]));

        }
    }
}

Intersection* SceneBVHNode::traverse(Ray* ray){
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

void SceneBVHNode::split(){
    std::vector<glm::vec3> mesh_means(this->meshes.size());
    for(unsigned long i = 0; i < meshes.size(); i++){
        mesh_means[i] = meshes[i]->get_mean();
    }

    std::vector<unsigned int> assignment = kMeans(mesh_means);
    std::vector<unsigned long> mesh_count(K);

    for (unsigned int i = 0; i < assignment.size(); i++) {
        mesh_count[assignment[i]] += 1;
    }

    for(unsigned long k = 0; k < K; k++){
        std::vector<Mesh*> meshes_k(mesh_count[k]);
        std::vector<unsigned long> mesh_indices_k(mesh_count[k]);

        unsigned long current = 0;
        for(unsigned long f = 0; f < meshes.size(); f++){
            if(assignment[f] == k){

                meshes_k[current] = this->meshes[f];
                current++;
            }
        }
        this->children.push_back(new SceneBVHNode(meshes_k));
    }
}

void SceneBVHNode::get_preview(std::vector<glm::vec3> *verts)
{
    aabb->get_preview(verts);

    std::cout << "number of vertices before: " << verts->size() << std::endl;

    if(this->is_leaf){
        for (unsigned int i = 0; i < mesh_bvhs.size(); i++) {
            mesh_bvhs[i]->get_preview(verts);
        }
    }else{
        for (unsigned int i = 0; i < children.size(); ++i) {
            children[i]->get_preview(verts);
        }
    }
    std::cout << "number of vertices after: " << verts->size() << std::endl;
}

Intersection* SceneBVHNode::intersect_content(Ray* ray){
    //std::cout << "checking objects"<< std::endl;
    float best_distance = std::numeric_limits<float>::infinity();
    Intersection* best = nullptr;
    for(unsigned int i = 0; i < mesh_bvhs.size(); i++){
        Intersection* current = mesh_bvhs[i]->traverse(ray);
        if(current != nullptr and current->distance < best_distance){
            best = current;
            best_distance = current->distance;
        }
    }
    return best;
}

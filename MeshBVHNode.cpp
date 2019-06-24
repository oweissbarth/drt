#include <glm/gtx/intersect.hpp>

#include "MeshBVHNode.h"
#include <iostream>
#include <glm/gtx/string_cast.hpp>


#define MAX_LEAF_SIZE 20

MeshBVHNode::MeshBVHNode(std::vector<glm::uvec3> faces, std::vector<unsigned long> face_indices, Mesh* object){
    this->faces = faces;
    this->face_indices = face_indices;
    this->object = object;

    std::vector<glm::vec3*> positions(faces.size()*3);
    for(unsigned long i = 0; i < faces.size(); i++){
        positions[i*3] = &(this->object->vertices[this->faces[i].x]);
        positions[i*3+1] = &(this->object->vertices[this->faces[i].y]);
        positions[i*3+2] = &(this->object->vertices[this->faces[i].z]);
    }
    this->aabb = new AABB(positions);

    std::cout << object->name<<": " << glm::to_string(aabb->min) << ", " << glm::to_string(aabb->max) << std::endl;


    if(faces.size() > MAX_LEAF_SIZE){
        this->is_leaf = false;
        this->split();
    }else{
        this->is_leaf = true;
    }
}

void MeshBVHNode::split(){
    std::vector<glm::vec3> faces_means(this->faces.size());
    for(unsigned long i = 0; i < faces.size(); i++){
        faces_means[i] = (this->object->vertices[this->faces[i].x] + this->object->vertices[this->faces[i].y] +this->object->vertices[this->faces[i].z])/3.f;
    }

    std::vector<unsigned int> assignment = kMeans(faces_means);
    std::vector<unsigned long> face_count(K);

    for (unsigned int i = 0; i < assignment.size(); i++) {
        face_count[assignment[i]] += 1;
    }

    for(unsigned long k = 0; k < K; k++){
        std::vector<glm::uvec3> faces_k(face_count[k]);
        std::vector<unsigned long> face_indices_k(face_count[k]);

        unsigned long current = 0;
        for(unsigned long f = 0; f < faces.size(); f++){
            if(assignment[f] == k){

                faces_k[current] = this->faces[f];
                face_indices_k[current] = this->face_indices[f];
                current++;
            }
        }
        this->children.push_back(new MeshBVHNode(faces_k, face_indices_k, object));
    }
}





Intersection* MeshBVHNode::intersect_content(Ray *ray){
    Intersection* bestIntersection = nullptr;
    glm::vec2 barycentric(0);
    float distance = 0;
    bool found = false;
    for(unsigned long  f = 0; f < this->faces.size(); f++){
        const glm::vec3 v1 = this->object->vertices[this->faces[f].x];
        const glm::vec3 v2 = this->object->vertices[this->faces[f].y];
        const glm::vec3 v3 = this->object->vertices[this->faces[f].z];
        const glm::vec3 origin = ray->origin;
        const glm::vec3 direction = ray->direction;
        found = glm::intersectRayTriangle(origin, direction, v1, v2, v3, barycentric, distance);

        if(found and distance > std::numeric_limits<float>::epsilon() and(bestIntersection == nullptr or distance < bestIntersection->distance)){
            glm::vec3 position = ray->origin + distance * ray->direction;
            bestIntersection = new Intersection(position, object, face_indices[f], distance);
        }
    }
    return bestIntersection;
}

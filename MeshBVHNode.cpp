#include <glm/gtx/intersect.hpp>

#include "MeshBVHNode.h"
#include "utils.h"
#include <iostream>
#include <glm/gtx/string_cast.hpp>

#define K 4
#define K_MEANS_STEPS 5
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

    std::vector<glm::vec3> means(K);
    for(unsigned long k = 0; k < K; k++){
        means[k] = random_vec3(this->aabb->min, this->aabb->max);
    }

    std::vector<unsigned long> assignment(faces.size());
    std::vector<unsigned long> face_count(K);

    for(unsigned int i = 0; i < K_MEANS_STEPS; i++){

        // assign faces to means
        for(unsigned long i = 0; i < faces.size(); i++){
            float min_distance = std::numeric_limits<float>::infinity();
            for(unsigned long k = 0; k < K; k++){
                float distance = glm::distance(means[k], faces_means[i]);
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
            for(unsigned long f = 0; f < faces.size(); f++){
                if(assignment[f] == k){
                    means[k] += faces_means[f];
                    face_count[k]++;
                }
            }
            means[k] /= face_count[k];
        }
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

        if(found and (bestIntersection == nullptr or distance < bestIntersection->distance)){
            glm::vec3 position = ray->origin + distance * ray->direction;
            bestIntersection = new Intersection(position, object, face_indices[f], distance);
        }
    }
    return bestIntersection;
}

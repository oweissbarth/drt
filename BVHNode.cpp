#include <glm/gtx/intersect.hpp>

#include "BVHNode.h"
#include "utils.h"
#include <iostream>
#include <glm/gtx/string_cast.hpp>

#define K 5
#define K_MEANS_STEPS 5
#define MAX_LEAF_SIZE 20

BVHNode::BVHNode(std::vector<glm::uvec3> faces, std::vector<unsigned long> face_indices, std::vector<Object*> objects){
    this->faces = faces;
    this->face_indices = face_indices;
    this->objects = objects;

    std::vector<glm::vec3*> positions(faces.size()*3);
    for(unsigned long i = 0; i < faces.size(); i++){
        positions[i*3] = &(this->objects[i]->vertices[this->faces[i].x]);
        positions[i*3+1] = &(this->objects[i]->vertices[this->faces[i].y]);
        positions[i*3+2] = &(this->objects[i]->vertices[this->faces[i].z]);
    }
    this->aabb = new AABB(positions);

    if(faces.size() > MAX_LEAF_SIZE){
        this->is_leaf = false;
        this->split();
    }else{
        this->is_leaf = true;
    }
}

void BVHNode::split(){
    std::vector<glm::vec3> faces_means(this->faces.size());
    for(unsigned long i = 0; i < faces.size(); i++){
        faces_means[i] = (this->objects[i]->vertices[this->faces[i].x] + this->objects[i]->vertices[this->faces[i].y] +this->objects[i]->vertices[this->faces[i].z])/3.f;
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
        std::vector<Object*> objects_k(face_count[k]);

        unsigned long current = 0;
        for(unsigned long f = 0; f < faces.size(); f++){
            if(assignment[f] == k){

                faces_k[current] = this->faces[f];
                face_indices_k[current] = this->face_indices[f];
                objects_k[current] = this->objects[f];
                current++;
            }
        }
        this->children.push_back(new BVHNode(faces_k, face_indices_k, objects_k));
    }
}

Intersection* BVHNode::traverse(Ray* ray){
    if(!this->aabb->intersect(ray)){
        return nullptr;
    }

    if(this->is_leaf){
        return this->intersect_faces(ray);
    }

    // NOTE this is naivly checking every child
    Intersection* bestIntersection = nullptr;
    for (unsigned long k = 0; k < K; k++) {
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

Intersection* BVHNode::intersect_faces(Ray *ray){
    Intersection* bestIntersection = nullptr;
    glm::vec2 barycentric(0);
    float distance = 0;
    bool found = false;
    for(unsigned long  f = 0; f < this->faces.size(); f++){
        const glm::vec3 v1 = this->objects[f]->vertices[this->faces[f].x];
        const glm::vec3 v2 = this->objects[f]->vertices[this->faces[f].y];
        const glm::vec3 v3 = this->objects[f]->vertices[this->faces[f].z];
        const glm::vec3 origin = ray->origin;
        const glm::vec3 direction = ray->direction;
        found = glm::intersectRayTriangle(origin, direction, v1, v2, v3, barycentric, distance);

        if(found and (bestIntersection == nullptr or distance < bestIntersection->distance)){
            glm::vec3 position = ray->origin + distance * ray->direction;
            bestIntersection = new Intersection(position, objects[f], face_indices[f], distance);
        }
    }
    return bestIntersection;
}

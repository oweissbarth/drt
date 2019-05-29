#include "BVH.h"
#include <iostream>

BVH::BVH(Scene* scene)
{
    unsigned long face_count = 0;
    for(unsigned long o=0; o < scene->objects.size(); o++){
        face_count += scene->objects[o]->faces.size();
    }

    std::vector<glm::uvec3> faces(face_count);
    std::vector<unsigned long> faces_indices(face_count);
    std::vector<Object*> objects(face_count);

    unsigned long current = 0;

    for(unsigned long o=0; o < scene->objects.size(); o++){
        for(unsigned long f = 0; f < scene->objects[o]->faces.size(); f++){
            faces[current] = scene->objects[o]->faces[f];
            faces_indices[current] = f;
            objects[current] = scene->objects[o];
            current++;
        }
    }
    this->root = new BVHNode(faces, faces_indices, objects);
}

Intersection* BVH::traverse(Ray* ray){
    return this->root->traverse(ray);
}

PreviewLines* BVH::get_preview(){
    std::vector<glm::vec3> verts;

    this->root->get_preview(&verts);

    return new PreviewLines(verts);
}

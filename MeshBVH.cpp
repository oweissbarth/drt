#include "MeshBVH.h"
#include <iostream>

#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/matrix_operation.hpp>
#include <glm/gtx/transform.hpp>

MeshBVH::MeshBVH(Mesh* mesh)
{
    unsigned long face_count = mesh->faces.size();

    std::vector<glm::uvec3> faces(face_count);
    std::vector<unsigned long> faces_indices(face_count);


    glm::mat4 translation = glm::translate(mesh->location);
    glm::mat4 rotation = glm::toMat4(mesh->rotation);
    glm::mat4 scale = glm::diagonal4x3(mesh->scale);
    this->transform = translation * rotation * scale;
    this->inv_transform = glm::inverse(this->transform);

    this->mesh = mesh;

    for (unsigned int f = 0; f < mesh->faces.size();f++) {
        faces_indices[f] = f;
        faces[f] = mesh->faces[f];
    }

    this->root = new MeshBVHNode(faces, faces_indices, mesh);
}

Intersection* MeshBVH::traverse(Ray* ray){
    //std::cout << "hit mesh bvh of object " << this->mesh->name << std::endl;
    glm::vec3 new_origin = glm::vec3(inv_transform*glm::vec4(ray->origin, 1.0));
    glm::vec3 new_direction = glm::normalize(glm::vec3(inv_transform*glm::vec4(ray->direction, 1.0)));
    Ray* transformed = new Ray(new_origin, new_direction);
    return this->root->traverse(transformed);
}



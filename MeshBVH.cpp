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

    for (unsigned int f = 0; f < mesh->faces.size();f++) {
        faces_indices[f] = f;
        faces[f] = mesh->faces[f];
    }


    this->root = new MeshBVHNode(faces, faces_indices, mesh);
}



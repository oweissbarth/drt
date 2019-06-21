#include "Object.h"
#include <glm/gtx/intersect.hpp>
#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/matrix_operation.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>

Mesh::Mesh(std::vector<glm::vec3> vertices, std::vector<glm::uvec3> faces, std::vector<glm::vec3> normals, std::string meshname, glm::vec3 pos, glm::quat rot, glm::vec3 scale): Object(pos, rot, scale){
	this->vertices = vertices;
	this->faces = faces;
    this->normals = normals;
    this->name = meshname;

    float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);


    this->color = glm::vec3(r,g,b);
}

void Mesh::intersect(Ray* ray, glm::vec3* intersection, glm::vec3* normal, bool* foundIntersection){
    float minDistance = 99999999.0f;
    glm::vec2 barycentric(0);
    float distance = 0;
    bool found = false;
    //std::cout << "testing for intersections with "<< this->name << std::endl;
    for(unsigned long  f = 0; f < this->faces.size(); f++){
        //std::cout << glm::to_string(this->faces[f]) << this->vertices.size() << std::endl;
        const glm::vec3 v1 = this->vertices[this->faces[f].x];
        const glm::vec3 v2 = this->vertices[this->faces[f].y];
        const glm::vec3 v3 = this->vertices[this->faces[f].z];
        const glm::vec3 origin = ray->origin;
        const glm::vec3 direction = ray->direction;
        found = glm::intersectRayTriangle(origin, direction, v1, v2, v3, barycentric, distance);
        *foundIntersection = *foundIntersection or found;
        if(found and distance < minDistance){
            *intersection = ray->origin + distance * ray->direction;
            minDistance = distance;
        }
    }
}


PreviewSolid* Mesh::get_preview(){
    std::vector<glm::vec3> verts(faces.size()*3);

    for(unsigned int i = 0; i < faces.size(); i++){

        verts[i*3] = this->vertices[faces[i].x];
        verts[i*3+1] = this->vertices[faces[i].y];
        verts[i*3+2] = this->vertices[faces[i].z];

    }
    return new PreviewSolid(verts, normals, get_matrix(), color);
}

AABB Mesh::get_bounding_box()
{
    std::vector<glm::vec3*> positions(vertices.size());
    for (unsigned int i = 0; i < vertices.size(); i++) {
        positions[i] = &vertices[i];
    }
    return AABB(positions);
}

glm::mat4 Object::get_matrix()
{
    glm::mat4 translation = glm::translate(this->location);
    glm::mat4 rotation = glm::toMat4(this->rotation);
    glm::mat4 scale = glm::diagonal4x3(this->scale);

    glm::mat4 modelMatrix = translation * rotation * scale;


    if(this->parent != nullptr){
        return this->parent->get_matrix() * modelMatrix;
    }else{
        return modelMatrix;
    }
}

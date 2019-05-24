#include "Object.h"
#include <glm/gtx/intersect.hpp>
#include <iostream>
#include <glm/gtx/string_cast.hpp>

Object::Object(std::vector<glm::vec3> vertices, std::vector<glm::uvec3> faces, std::string name){
	this->vertices = vertices;
	this->faces = faces;
    this->name = name;
}

void Object::intersect(Ray* ray, glm::vec3* intersection, glm::vec3* normal, bool* foundIntersection){
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

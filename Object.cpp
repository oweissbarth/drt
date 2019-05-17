#include "Object.h"
#include <glm/gtx/intersect.hpp>

Object::Object(std::vector<glm::vec3> vertices, std::vector<glm::uvec3> faces){
	this->vertices = vertices;
	this->faces = faces;
}

void Object::intersect(Ray* ray, glm::vec3* intersection, glm::vec3* normal, bool* foundIntersection){
    float minDistance = 99999999.0;
    glm::vec2 barycentric(0);
    float distance = 0;
    for(int f = 0; f < this->faces.size(); f++){
        const glm::vec3 v1 = this->vertices[this->faces[f].x];
        const glm::vec3 v2 = this->vertices[this->faces[f].y];
        const glm::vec3 v3 = this->vertices[this->faces[f].z];
        const glm::vec3 origin = ray->origin;
        const glm::vec3 direction = ray->direction;
        *foundIntersection = glm::intersectRayTriangle(origin, direction, v1, v2, v3, barycentric, distance);
        
        if(foundIntersection and distance < minDistance){
            *intersection = ray->origin + distance * ray->direction;
            minDistance = distance;
        }
    }
}

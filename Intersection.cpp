#include "Intersection.h"

Intersection::Intersection(glm::vec3 position, Mesh* object, unsigned long face_index, float distance){
    this->position = position;
    this->object = object;
    this->face_index = face_index;
    this->distance = distance;
}

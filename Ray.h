#pragma once

#include <glm/glm.hpp>

class Ray{
public:
  Ray(glm::vec3 origin, glm::vec3 direction){
    this->origin = origin;
    this->direction = direction;
    this->inv_direction = glm::vec3(1)/this->direction;
  }
  glm::vec3 origin;
  glm::vec3 direction;
  glm::vec3 inv_direction;
  
};

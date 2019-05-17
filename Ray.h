#pragma once

#include <glm/glm.hpp>

class Ray{
public:
  Ray(glm::vec3 origin, glm::vec3 direction){
    this->origin = origin;
    this->direction = direction;
  }
  glm::vec3 origin;
  glm::vec3 direction;
  
};

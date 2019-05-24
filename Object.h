#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>
#include "Ray.h"

class Object{
private:
	std::vector<glm::vec3> vertices;
	std::vector<glm::uvec3> faces;
    std::string name;
public:
    Object(std::vector<glm::vec3> vertices, std::vector<glm::uvec3> faces, std::string name = "_NO_NAME_");
  void intersect(Ray* ray, glm::vec3* intersection, glm::vec3* normal, bool* foundIntersection);
};

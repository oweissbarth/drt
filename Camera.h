#pragma once

#include <glm/glm.hpp>

class Camera{
private:

	float fov;
	float near_clip = 0.01;
	float far_clip = 100;
	unsigned int width;
	unsigned int height;
public:
	Camera(float fov, unsigned int width, unsigned int height, glm::vec3 position, glm::vec3 up, glm::vec3 forward);
  	glm::vec3 position;
	glm::mat4 view;
	glm::mat4 projection;
};

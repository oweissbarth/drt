#include "Camera.h"

#include <glm/gtx/projection.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(float fov, unsigned int width, unsigned int height, glm::vec3 position, glm::vec3 center, glm::vec3 up){
	this->fov = fov;
	this->width = width;
	this->height = height;
	this->position = position;

	this->view = glm::lookAt(position, center, up);

	this->projection = glm::perspective(glm::radians(this->fov), (float)this->width/(float)this->height, this->near_clip, this->far_clip);

}

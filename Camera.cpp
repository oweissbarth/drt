#include "Camera.h"

#include <glm/gtx/projection.hpp>
#include <glm/gtc/matrix_transform.hpp>

/*Camera::Camera(float fov, unsigned int width, unsigned int height, glm::vec3 position, glm::vec3 center, glm::vec3 up){
	this->fov = fov;
	this->width = width;
	this->height = height;
	this->position = position;

	this->view = glm::lookAt(position, center, up);

	this->projection = glm::perspective(glm::radians(this->fov), (float)this->width/(float)this->height, this->near_clip, this->far_clip);

}*/


Camera::Camera(float fov, float znear, float zfar, glm::vec3 pos, glm::quat rot, glm::vec3 scale): Object(pos, rot, glm::vec3(1)){
    this->fov = fov;
    this->near_clip = znear;
    this->far_clip = zfar;
}


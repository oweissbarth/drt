#pragma once

#include "Object.h"
#include "preview/PreviewLines.h"

#include <glm/glm.hpp>


class Camera: public Object{
private:

public:
    Camera(float fov, float znear, float zfar, glm::vec3 pos = glm::vec3(0), glm::quat rot = glm::quat(), glm::vec3 scale = glm::vec3(1));
    //Camera(float fov, unsigned int width, unsigned int height, glm::vec3 position, glm::vec3 up, glm::vec3 forward);

    PreviewLines* get_preview();

    float fov;
    float near_clip = 0.01;
    float far_clip = 100;
    unsigned int width;
    unsigned int height;
};

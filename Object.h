#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <vector>
#include <string>
#include "Ray.h"
#include "preview/PreviewSolid.h"
#include "AABB.h"


class Object{

public:
    Object(glm::vec3 pos, glm::quat rot, glm::vec3 scale){
        this->location = pos;
        this->rotation = rot;
        this->scale = scale;
    }

    glm::mat4 get_matrix();
    glm::vec3 get_location();


    virtual ~Object() = default;
    std::string name;
    std::vector<Object*> children;
    Object* parent;
    glm::vec3 location;
    glm::quat rotation;
    glm::vec3 scale;
};


class Empty: public Object{
public:
    Empty(glm::vec3 pos, glm::quat rot, glm::vec3 scale): Object(pos, rot, scale){
    }
};



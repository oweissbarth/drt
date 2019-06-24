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

class Mesh: public Object{
private:

public:
    Mesh(std::vector<glm::vec3> vertices, std::vector<glm::uvec3> faces, std::vector<glm::vec3> normals, std::string name = "_NO_NAME_", glm::vec3 pos = glm::vec3(0), glm::quat rot = glm::quat(), glm::vec3 scale = glm::vec3(3));
    void intersect(Ray* ray, glm::vec3* intersection, glm::vec3* normal, bool* foundIntersection);
    std::vector<glm::vec3> vertices;
    std::vector<glm::uvec3> faces;
    std::vector<glm::vec3> normals;
    glm::mat4 modelMatrix;
    PreviewSolid* get_preview();
    glm::vec3 color;

    AABB get_bounding_box();
    AABB get_world_bounding_box();

    glm::vec3 get_mean();


};

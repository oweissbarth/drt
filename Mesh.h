#pragma once

#include "Object.h"
#include "Material.h"

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
    std::vector<Material*> materials;

    AABB get_bounding_box();
    AABB get_world_bounding_box();

    Material* get_material(unsigned int faceid);
    bool is_light();

    glm::vec3 get_mean();


};

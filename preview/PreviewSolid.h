#pragma once

#include "PreviewObject.h"

class PreviewSolid: public PreviewObject
{
public:
    PreviewSolid(std::vector<glm::vec3> vertices, std::vector<glm::vec3> norms, glm::mat4 modelMatrix=glm::mat4(), glm::vec3 color=glm::vec3(1,0,0));
    void draw(glm::mat4 projectionMatrix, glm::mat4 viewMatrix) override;
private:
    GLsizei buffer_size;
    glm::vec3 color;
};

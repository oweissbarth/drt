#pragma once

#include "PreviewObject.h"

class PreviewSolid: public PreviewObject
{
public:
    PreviewSolid(std::vector<glm::vec3> vertices, std::vector<glm::vec3> norms);
    void draw(glm::mat4 projectionMatrix, glm::mat4 viewMatrix) override;
private:
    GLsizei buffer_size;
};

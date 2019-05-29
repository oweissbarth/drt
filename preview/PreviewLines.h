#pragma once


#include "PreviewObject.h"

#include <glm/glm.hpp>

class PreviewLines : public PreviewObject
{
public:
    PreviewLines(std::vector<glm::vec3> verts);
    void draw(glm::mat4 projectionMatrix, glm::mat4 viewMatrix) override;
private:
    GLsizei buffer_size;
};


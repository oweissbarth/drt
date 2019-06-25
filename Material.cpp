#include "Material.h"

Material::Material(glm::vec3 color, glm::vec3 emissive,unsigned int start_index)
{
    this->color = color;
    this->emissive = emissive;
    this->start_index = start_index;
}

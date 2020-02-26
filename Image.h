#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>


class Image{
public:
  unsigned int width;
  unsigned int height;
  std::vector<glm::vec4> pixels;
  Image(unsigned int width, unsigned int height);
  bool save(std::string path);
  void tonemap();
  void scale_values(float);
};

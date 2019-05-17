#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>


class Image{
public:
  int width;
  int height;
  std::vector<glm::vec4> pixels;
  Image(int width, int height);
  bool save(std::string path);
};

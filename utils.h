#pragma once

#include <glm/glm.hpp>
#include <cstdlib>
#include <ctime>


inline float random_float(float min, float max){
    std::srand(static_cast<unsigned int>(clock()));

    float random = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) + 1.0f);

    return (random * (max - min))+min;
}

inline glm::vec3 random_vec3(glm::vec3 min, glm::vec3 max){
    return glm::vec3(random_float(min.x, max.x), random_float(min.y, max.y), random_float(min.z, max.z) );
}

inline float luminance(glm::vec3 color){
    return 0.299f*color.r + 0.587f*color.g + 0.114f*color.b;
}

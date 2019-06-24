#include "BVHNode.h"
#include "utils.h"
#include <iostream>


#define K_MEANS_STEPS 5


std::vector<unsigned int> BVHNode::kMeans(std::vector<glm::vec3> content_means){
    std::vector<glm::vec3> means(K);
    for(unsigned int k = 0; k < K; k++){
        means[k] = random_vec3(this->aabb->min, this->aabb->max);
    }

    std::vector<unsigned int> assignment(content_means.size());
    std::vector<unsigned long> face_count(K);

    for(unsigned int i = 0; i < K_MEANS_STEPS; i++){

        // assign faces to means
        for(unsigned long i = 0; i < content_means.size(); i++){
            float min_distance = std::numeric_limits<float>::infinity();
            for(unsigned int k = 0; k < K; k++){
                float distance = glm::distance(means[k], content_means[i]);
                if( distance < min_distance){
                    min_distance = distance;
                    assignment[i] = k;
                }
            }
        }

        // recompute means
        for (unsigned long k = 0; k < K; k++) {
            means[k] = glm::vec3(0);
            face_count[k] = 0;
            for(unsigned long f = 0; f < content_means.size(); f++){
                if(assignment[f] == k){
                    means[k] += content_means[f];
                    face_count[k]++;
                }
            }
            means[k] /= face_count[k];
        }
    }
    return assignment;
}

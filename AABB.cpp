#include "AABB.h"
#include <limits>


#define min(x, y) ((x) < (y) ? (x) : (y))
#define max(x, y) ((x) > (y) ? (x) : (y))

AABB::AABB(std::vector<glm::vec3*> points){
    float xmin = std::numeric_limits<float>::infinity();
    float ymin = std::numeric_limits<float>::infinity();
    float zmin = std::numeric_limits<float>::infinity();


    float xmax = -std::numeric_limits<float>::infinity();
    float ymax = -std::numeric_limits<float>::infinity();
    float zmax = -std::numeric_limits<float>::infinity();

    for(unsigned long i = 0; i < points.size(); i++){
        xmin = min(xmin, points[i]->x);
        ymin = min(ymin, points[i]->y);
        zmin = min(zmin, points[i]->z);

        xmax = max(xmax, points[i]->x);
        ymax = max(ymax, points[i]->y);
        zmax = max(zmax, points[i]->z);
    }
    this->min = glm::vec3(xmin, ymin, zmin);
    this->max = glm::vec3(xmax, ymax, zmax);

}


bool AABB::intersect(Ray* ray){
    float t1 = (this->min.x - ray->origin.x)*ray->inv_direction.x;
    float t2 = (this->max.x - ray->origin.x)*ray->inv_direction.x;

    float tmin = min(t1, t2);
    float tmax = max(t1, t2);

    for (int i = 0; i < 3; ++i) {
            t1 = (this->min[i] - ray->origin[i])*ray->inv_direction[i];
            t2 = (this->max[i] - ray->origin[i])*ray->inv_direction[i];

           /* if(ray->inv_direction[i] < 0.0f){
                float temp = t2;
                t2 = t1;
                t1 = temp;
            }*/

            tmin = max(tmin, min(min(t1, t2), tmax));
            tmax = min(tmax, max(max(t1, t2), tmin));
        }

        return tmax > max(tmin, 0.0f);
}

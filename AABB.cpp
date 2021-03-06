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

void AABB::ensure_non_zero(float epsilon){
    if(this->min.x == this->max.x){
        this->max.x += epsilon;
    }

    if(this->min.y == this->max.y){
        this->max.y += epsilon;
    }

    if(this->min.z == this->max.z){
        this->max.z += epsilon;
    }
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

void AABB::get_preview(std::vector<glm::vec3>* verts){
    float minx = this->min.x;
    float miny = this->min.y;
    float minz = this->min.z;

    float maxx = this->max.x;
    float maxy = this->max.y;
    float maxz = this->max.z;

    //bottom
    verts->push_back(glm::vec3(minx, miny, minz));
    verts->push_back(glm::vec3(maxx, miny, minz));

    verts->push_back(glm::vec3(maxx, miny, minz));
    verts->push_back(glm::vec3(maxx, maxy, minz));

    verts->push_back(glm::vec3(maxx, maxy, minz));
    verts->push_back(glm::vec3(minx, maxy, minz));

    verts->push_back(glm::vec3(minx, maxy, minz));
    verts->push_back(glm::vec3(minx, miny, minz));


    //top
    verts->push_back(glm::vec3(minx, miny, maxz));
    verts->push_back(glm::vec3(maxx, miny, maxz));

    verts->push_back(glm::vec3(maxx, miny, maxz));
    verts->push_back(glm::vec3(maxx, maxy, maxz));

    verts->push_back(glm::vec3(maxx, maxy, maxz));
    verts->push_back(glm::vec3(minx, maxy, maxz));

    verts->push_back(glm::vec3(minx, maxy, maxz));
    verts->push_back(glm::vec3(minx, miny, maxz));

    //sides

    verts->push_back(glm::vec3(minx, miny, minz));
    verts->push_back(glm::vec3(minx, miny, maxz));

    verts->push_back(glm::vec3(minx, maxy, minz));
    verts->push_back(glm::vec3(minx, maxy, maxz));

    verts->push_back(glm::vec3(maxx, miny, minz));
    verts->push_back(glm::vec3(maxx, miny, maxz));

    verts->push_back(glm::vec3(maxx, maxy, minz));
    verts->push_back(glm::vec3(maxx, maxy, maxz));



}

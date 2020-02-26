#include "Renderer.h"
#include "Ray.h"
#include "Image.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>

#include <iostream>
#include "Intersection.h"
#include "SceneBVH.h"
#include "utils.h"

#define MAX_DEPTH 5

Renderer::Renderer(Scene* scene, Camera* camera, unsigned int x_res, unsigned int y_res, Preview* p){
	this->scene = scene;
	this->camera = camera;
	this->x_res = x_res;
	this->y_res = y_res;

    this->p = p;

    this->bvh = new SceneBVH(this->scene);
}

void Renderer::render(){

    Image* result = new Image(this->x_res, this->y_res);

    unsigned int samples = 10;

    glm::mat4 projection = glm::perspective(this->camera->fov, (float)this->x_res/(float)this->y_res, this->camera->near_clip, this->camera->far_clip);

    glm::mat4 view = glm::inverse(camera->get_matrix());

    std::vector<glm::vec3> verts;

    #pragma omp parallel for
	for(unsigned int i = 0; i < this->x_res*this->y_res; i++){
        unsigned int x = i%x_res;
        unsigned int y = i/x_res;

        for(unsigned int s = 0; s < samples; ++s){

            float offset_x = random_float(-0.5, 0.5);
            float offset_y = random_float(-0.5, 0.5);

            glm::vec3 nearPlanePos = glm::unProject(glm::vec3(x+offset_x, y+offset_y, 0), view, projection, glm::vec4(0.0,0.0,x_res, y_res));
            glm::vec3 farPlanePos = glm::unProject(glm::vec3(x+offset_x, y+offset_y, 1), view, projection, glm::vec4(0.0, 0.0, x_res, y_res));

            Ray* ray = new Ray(this->camera->get_location(), glm::normalize(farPlanePos-nearPlanePos));


            if( p && x % 20 == 0 && y % 20 == 0){
                std::cout << "Rendering " << i << "/" << this->x_res*this->y_res << "\r"<<std::flush;
                verts.push_back(ray->origin);
                verts.push_back(ray->origin + ray->direction*2000.f);
            }


            Intersection* intersection = bvh->traverse(ray);

            if(intersection != nullptr){
                Material* material = intersection->object->get_material(intersection->face_index);
                glm::vec3 color;
                if(material == nullptr){
                    color = glm::vec3(1., 0., 1.);
                }else{
                   color = material->color;
                   if(material->emissive != glm::vec3(0,0,0)){
                       std::cout  << "hit light!" << std::endl;
                   }
                }

                result->pixels[i] += glm::vec4(color, 1.0);
            }else{
                result->pixels[i] += glm::vec4(0., 0., 0., 1.0);
            }
        }
    }
    std::cout << "number of lines: " << verts.size()/2 << std::endl;
    if(p){
        PreviewLines* raypreview = new PreviewLines(verts, glm::mat4(1));
        p->add(raypreview);
    }

     result->scale_values(1.f/samples);
    //result->tonemap();

    result->save("result.png");
}

void Renderer::trace(Ray *ray, int depth, glm::vec3* radiosity)
{
    if(depth > MAX_DEPTH){
        return;
    }
    Intersection* intersection = bvh->traverse(ray);

    glm::vec3 contribution(0);

    /*this->trace(reflected_ray, depth+1, &contribution);

    for(unsigned int i = 0; i < scene->lights)

    radiosity =*/

}

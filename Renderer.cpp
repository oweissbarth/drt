#include "Renderer.h"
#include "Ray.h"
#include "Image.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include <iostream>
#include "Intersection.h"
#include "SceneBVH.h"

#define MAX_DEPTH 5

Renderer::Renderer(Scene* scene, Camera* camera, unsigned int x_res, unsigned int y_res){
	this->scene = scene;
	this->camera = camera;
	this->x_res = x_res;
	this->y_res = y_res;

    this->bvh = new SceneBVH(this->scene);
}

void Renderer::render(){

    Image* result = new Image(this->x_res, this->y_res);

    glm::mat4 projection = glm::perspective(this->camera->fov, (float)this->x_res/(float)this->y_res, this->camera->near_clip, this->camera->far_clip);

    glm::mat4 view = glm::inverse(camera->get_matrix());

	for(unsigned int i = 0; i < this->x_res*this->y_res; i++){
        unsigned int x = i%x_res;
        unsigned int y = i/x_res;

        if( i % 20 == 0){
            std::cout << "Rendering " << i << "/" << this->x_res*this->y_res << "\r"<<std::flush;
        }
		
        glm::vec3 nearPlanePos = glm::unProject(glm::vec3(x, y, 0), view, projection, glm::vec4(0.0,0.0,x_res, y_res));
        glm::vec3 farPlanePos = glm::unProject(glm::vec3(x, y, 1), view, projection, glm::vec4(0.0, 0.0, x_res, y_res));

        Ray* ray = new Ray(this->camera->location, glm::normalize(farPlanePos-nearPlanePos));
        
        Intersection* intersection = bvh->traverse(ray);

        if(intersection != nullptr){
            float value = intersection->distance;
            //std::cout << value << std::endl;
            result->pixels[i] = glm::vec4(intersection->object->color, 1.0);
            //result->pixels[i] = glm::vec4(1.0, 0., 0., 1.0);
        }else{
            result->pixels[i] = glm::vec4(0., 0., 0., 1.0);
        }
    }
    result->save("/home/oliver/result.png");
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

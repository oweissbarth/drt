#include "Renderer.h"
#include "Ray.h"
#include "Image.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "Intersection.h"

Renderer::Renderer(Scene* scene, Camera* camera, unsigned int x_res, unsigned int y_res){
	this->scene = scene;
	this->camera = camera;
	this->x_res = x_res;
	this->y_res = y_res;

    this->bvh = new BVH(this->scene);
}

void Renderer::render(){

    Image* result = new Image(this->x_res, this->y_res);



	for(unsigned int i = 0; i < this->x_res*this->y_res; i++){
        unsigned int x = i%x_res;
        unsigned int y = i/x_res;

        if( i % 20 == 0){
            std::cout << "Rendering " << i << "/" << this->x_res*this->y_res << "\r"<<std::flush;
        }
		
		glm::vec3 nearPlanePos = glm::unProject(glm::vec3(x, y, 0), this->camera->view, this->camera->projection, glm::vec4(0.0,0.0,x_res, y_res));
        glm::vec3 farPlanePos = glm::unProject(glm::vec3(x, y, 1), this->camera->view, this->camera->projection, glm::vec4(0.0, 0.0, x_res, y_res));

        Ray* ray = new Ray(camera->position, glm::normalize(farPlanePos-nearPlanePos));
        
        Intersection* intersection = bvh->traverse(ray);

        if(intersection != nullptr){
            result->pixels[i] = glm::vec4(1.0, 0.,0., 1.0);
        }else{
            result->pixels[i] = glm::vec4(0., 0.,0., 1.0);
        }
    }
    result->save("/home/oliver/result.png");
}

#include "Renderer.h"
#include "Ray.h"
#include "Image.h"
#include <glm/gtc/matrix_transform.hpp>

Renderer::Renderer(Scene* scene, Camera* camera, unsigned int x_res, unsigned int y_res){
	this->scene = scene;
	this->camera = camera;
	this->x_res = x_res;
	this->y_res = y_res;
}

void Renderer::render(){

    Image* result = new Image(this->x_res, this->y_res);


	for(unsigned int i = 0; i < this->x_res*this->y_res; i++){
		int x = i%x_res;
		int y = i/x_res;
		
		glm::vec3 nearPlanePos = glm::unProject(glm::vec3(x, y, 0), this->camera->view, this->camera->projection, glm::vec4(0.0,0.0,x_res, y_res));
        glm::vec3 farPlanePos = glm::unProject(glm::vec3(x, y, 1), this->camera->view, this->camera->projection, glm::vec4(0.0, 0.0, x_res, y_res));

        Ray* ray = new Ray(camera->position, glm::normalize(farPlanePos-nearPlanePos));
        
        float minDistance = 999999999.f;
        glm::vec3 closest_intersection;
        bool found = false;
        
        for(int i = 0; i < scene->objects.size(); i++){
            bool foundIntersection = false;
            glm::vec3 intersection;
            glm::vec3 normal;
            scene->objects[i]->intersect(ray, &intersection, &normal, &foundIntersection);
            
            found = found or foundIntersection;
            
            float distance = glm::distance(ray->origin, intersection);
            
            if(foundIntersection and distance < minDistance){
                minDistance = distance;
                closest_intersection = intersection;
            }
        }
        if(found){
            result->pixels[i] = glm::vec4(1.0, 0.,0., 1.0);
        }else{
            result->pixels[i] = glm::vec4(0., 0.,0., 1.0);
        }
    }
    result->save("/home/oliver/result.png");
}

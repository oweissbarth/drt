
#include "Object.h"
#include "Scene.h"
#include "Camera.h"
#include "Renderer.h"
#include "gltf.h"
#include "preview/Preview.h"

#include <glm/gtx/string_cast.hpp>


#include <iostream>

int main(){

	/*std::vector<glm::vec3> verts = {
		glm::vec3(-1., -1., -1.),
		glm::vec3(1., -1., -1.),
		glm::vec3(-1., 1., -1.),
		glm::vec3(-1., -1., 1.),
		glm::vec3(1., 1., -1.),
		glm::vec3(-1., 1., 1.),
		glm::vec3(1., -1., 1.),
		glm::vec3(1., 1., 1.)
	};

	std::vector<glm::uvec3> faces = {
		glm::uvec3(0, 1, 2),
		glm::uvec3(2, 3, 0),
		glm::uvec3(1, 5, 6),
		glm::uvec3(6, 2, 1),
		glm::uvec3(7, 6, 5),
		glm::uvec3(5, 4, 7),
		glm::uvec3(4, 0, 3),
		glm::uvec3(3, 7, 4),
		glm::uvec3(4, 5, 1),
		glm::uvec3(1, 0, 4),
		glm::uvec3(3, 2, 6),
		glm::uvec3(6, 7, 3)
	};
	
	Object* cube = new Object(verts, faces);

	Scene* scene = new Scene();

	scene->addObject(cube);

	Camera* camera = new Camera(60.f, 640, 480, glm::vec3(0.0, 2.0, -3.0) , glm::vec3(0), glm::vec3(0.0, 1.0, 0.0));

	Renderer* renderer = new Renderer(scene, camera, 640, 480);

	renderer->render();*/

    Scene* scene = import_gltf("/home/oliver/sample.gltf");

    Camera* camera = new Camera(60.f, 640, 480, glm::vec3(3.0, 6.0, -5.0) , glm::vec3(0), glm::vec3(0.0, 1.0, 0.0));

    Renderer* renderer = new Renderer(scene, camera, 640, 480);


   /* Preview p = Preview();

    for (unsigned long i = 0; i < scene->objects.size(); i++) {        
        p.add(scene->objects[i]->get_preview());
    }

    p.add(renderer->bvh->get_preview());*/
    renderer->render();

    //p.draw();



}

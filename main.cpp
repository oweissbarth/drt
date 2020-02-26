
#include "Object.h"
#include "Scene.h"
#include "Camera.h"
#include "Renderer.h"
#include "gltf.h"
#include "preview/Preview.h"

#include <glm/gtx/string_cast.hpp>
#include <iostream>


int main(int argc, char* argv[]){

    std::string file_name(argv[1]);

    Scene* scene = import_gltf(file_name);


    Camera* camera = scene->getCamera();



    Renderer* renderer = new Renderer(scene, camera, 500, 500, nullptr);

#ifdef DEBUG
    Preview p = Preview();


    for (unsigned long i = 0; i < scene->objects.size(); i++) {
        Mesh* mesh = dynamic_cast<Mesh*>(scene->objects[i]);
        if(mesh){
            p.add(mesh->get_preview());
            std::cout << mesh->name << std::endl;
        }
    }

    p.add(camera->get_preview());

    p.add(renderer->bvh->get_preview());
#endif
    renderer->render();

#ifdef DEBUG
    p.draw();
#endif



}

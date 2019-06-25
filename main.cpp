
#include "Object.h"
#include "Scene.h"
#include "Camera.h"
#include "Renderer.h"
#include "gltf.h"
#include "preview/Preview.h"

#include <glm/gtx/string_cast.hpp>


#include <iostream>

int main(){

    Scene* scene = import_gltf("/home/oliver/cornell.gltf");


    Camera* camera = scene->getCamera();



    //Preview p = Preview();

    Renderer* renderer = new Renderer(scene, camera, 500, 500, nullptr);


    //for (unsigned long i = 0; i < 1; i++) {

    /*for (unsigned long i = 0; i < scene->objects.size(); i++) {
        Mesh* mesh = dynamic_cast<Mesh*>(scene->objects[i]);
        if(mesh){
            p.add(mesh->get_preview());
            std::cout << mesh->name << std::endl;
        }
    }

    p.add(camera->get_preview());

    p.add(renderer->bvh->get_preview());*/
    renderer->render();

    //p.draw();



}

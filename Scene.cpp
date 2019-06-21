#include "Scene.h"

void Scene::addObject(Object* o){
	this->objects.push_back(o);
}

Camera* Scene::getCamera(){
    return findCamera(this->objects);
}

Camera* Scene::findCamera(std::vector<Object*> objects){
    for (unsigned int i = 0; i < objects.size(); i++) {
        Camera* cam = dynamic_cast<Camera*>(objects[i]);
        if(cam){
            return cam;
        }
        cam = findCamera(objects[i]->children);

        if(cam){
            return cam;
        }
    }
    return nullptr;
}



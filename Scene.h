#pragma once

#include "Object.h"
#include "Camera.h"

class Scene{
	
public:
	Scene(){};
    void addObject(Object* o);
    Camera* getCamera();
    Camera* findCamera(std::vector<Object*> objects);
    std::vector<Object*> objects;
};

#pragma once

#include "Object.h"

class Scene{
	
public:
	Scene(){};
	void addObject(Object* o);
  std::vector<Object*> objects;
};

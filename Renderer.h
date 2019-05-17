#pragma once

#include "Scene.h"
#include "Camera.h"

class Renderer{
private:
	Scene* scene;
	Camera* camera;
	unsigned int x_res;
	unsigned int y_res;
public:
	Renderer(Scene* scene, Camera* camera, unsigned int x_res, unsigned int y_res);
	void render();
};
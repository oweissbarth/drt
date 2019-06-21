#pragma once

#include "Scene.h"
#include "Camera.h"
#include "BVH.h"

class Renderer{
private:
	Scene* scene;
	Camera* camera;
	unsigned int x_res;
	unsigned int y_res;
public:
	Renderer(Scene* scene, Camera* camera, unsigned int x_res, unsigned int y_res);
	void render();
    void trace(Ray* ray, int depth, glm::vec3* radiosity);
    BVH* bvh;

};

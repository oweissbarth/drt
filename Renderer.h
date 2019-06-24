#pragma once

#include "Scene.h"
#include "Camera.h"
#include "SceneBVH.h"
#include "preview/Preview.h"

class Renderer{
private:
	Scene* scene;
	Camera* camera;
	unsigned int x_res;
	unsigned int y_res;
public:
    Renderer(Scene* scene, Camera* camera, unsigned int x_res, unsigned int y_res, Preview* p);
	void render();
    void trace(Ray* ray, int depth, glm::vec3* radiosity);
    SceneBVH* bvh;
    Preview* p;
};

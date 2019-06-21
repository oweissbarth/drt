#include "SceneBVH.h"

SceneBVH::SceneBVH(Scene* scene)
{
    std::vector<Mesh*> meshes;
    for (unsigned int i = 0; i < scene->objects.size(); i++) {
        Mesh* mesh = dynamic_cast<Mesh*>(scene->objects[i]);
        if(mesh){
            meshes.push_back(mesh);
        }
    }

    this->root = new SceneBVHNode(meshes);
}

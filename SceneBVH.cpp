#include "SceneBVH.h"
#include "SceneBVHNode.h"


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

Intersection* SceneBVH::traverse(Ray* ray){
    return this->root->traverse(ray);
}

PreviewLines *SceneBVH::get_preview()
{
    std::vector<glm::vec3> verts;
    this->root->get_preview(&verts);
    return new PreviewLines(verts);
}

#pragma once

#include "Scene.h"
#include "Camera.h"
#include "Mesh.h"
#include <string>

#include "json.hpp"


using json = nlohmann::json;

Scene* import_gltf(std::string path); 

Camera* import_camera(json node, json full);
Mesh* import_mesh(json node, json full);
Empty* import_empty(json node, json full);
Material* import_material(unsigned id, json full);


std::vector<Object*> import_nodes(std::vector<unsigned int> node_ids, json full);

unsigned int get_scene(json j);
std::vector<unsigned int> get_scene_nodes(unsigned int scene_id, json j);
std::vector<unsigned int> get_child_nodes(json node);


void get_transformation(json node, glm::vec3 &pos, glm::quat &rot, glm::vec3 &scale);


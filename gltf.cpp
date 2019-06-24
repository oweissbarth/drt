#include "gltf.h"

#include <fstream>
#include <iostream>

#include "base64.h"


Mesh* import_mesh(json node, json full){

    glm::vec3 pos;
    glm::quat rot;
    glm::vec3 scale;

    get_transformation(node, pos, rot, scale);

    json meshes = full["meshes"];
    json buffers = full["buffers"];
    json accessors = full["accessors"];
    json bufferviews = full["bufferViews"];

    std::vector<Mesh*> objects;

    std::cout << "loading mesh " << node["name"] << std::endl;
    unsigned long mesh_index = node["mesh"];


    json mesh = meshes[mesh_index];
    unsigned long position_i = mesh["primitives"][0]["attributes"]["POSITION"];
    unsigned long normal_i = mesh["primitives"][0]["attributes"]["NORMAL"];
    unsigned long face_i = mesh["primitives"][0]["indices"];


    json position_accessor = accessors[position_i];
    json normal_accessor = accessors[normal_i];
    json face_accessor = accessors[face_i];


    json position_buffer_view = bufferviews[static_cast<unsigned long>(position_accessor["bufferView"])];
    json normal_buffer_view = bufferviews[static_cast<unsigned long>(normal_accessor["bufferView"])];
    json face_buffer_view = bufferviews[static_cast<unsigned long>(face_accessor["bufferView"])];

    unsigned long position_buffer_index = static_cast<unsigned long>(position_buffer_view["buffer"]);
    unsigned long normal_buffer_index = static_cast<unsigned long>(normal_buffer_view["buffer"]);
    unsigned long face_buffer_index = static_cast<unsigned long>(face_buffer_view["buffer"]);

    json position_buffer = buffers[position_buffer_index];
    json normal_buffer = buffers[normal_buffer_index];

    unsigned long base64begin = std::string("data:application/octet-stream;base64,").size();
    std::string base64data = static_cast<std::string>(position_buffer["uri"]).erase(0, base64begin);

    std::string data;
    data.resize(static_cast<unsigned long>(position_buffer["byteLength"]));
    Base64::Decode(base64data, &data);

    unsigned long position_buffer_offset = position_buffer_view["byteOffset"];
    unsigned long position_buffer_length = position_buffer_view["byteLength"];


    const glm::vec3* position_bytes = reinterpret_cast<const glm::vec3*>(data.c_str()+position_buffer_offset);

    std::vector<glm::vec3> positions(position_bytes, position_bytes + position_buffer_length/sizeof (glm::vec3));


    unsigned long normal_buffer_offset = position_buffer_view["byteOffset"];
    unsigned long normal_buffer_length = position_buffer_view["byteLength"];
    const glm::vec3* normal_bytes = reinterpret_cast<const glm::vec3*>(data.c_str()+normal_buffer_offset);

    std::vector<glm::vec3> normals(normal_bytes, normal_bytes + normal_buffer_length/sizeof (glm::vec3));


    unsigned long face_buffer_offset = face_buffer_view["byteOffset"];
    unsigned long face_buffer_length = face_buffer_view["byteLength"];

    assert(face_buffer_index == position_buffer_index);

    const short* face_bytes = reinterpret_cast<const short*>(data.c_str()+face_buffer_offset);

    unsigned long face_count = static_cast<unsigned long>(face_accessor["count"])/3;

    std::vector<glm::uvec3> faces(face_count);
    for(unsigned long i = 0; i < faces.size(); i++){
        faces[i] = glm::uvec3(face_bytes[i*3], face_bytes[i*3+1], face_bytes[i*3+2]);
    }


    Mesh* obj = new Mesh(positions, faces, normals, mesh["name"], pos, rot, scale);

    return obj;

}

Camera* import_camera(json node, json full){

    std::cout << "loading camera " << node["name"] << std::endl;


    glm::vec3 pos;
    glm::quat rot;
    glm::vec3 scale;

    get_transformation(node, pos, rot, scale);

    json cameras = full["cameras"];
    unsigned camera_index = node["camera"];

    json camera_data = cameras[camera_index];

    json perspective = camera_data["perspective"];

    float fov = perspective["yfov"];
    float near = perspective["znear"];
    float far = perspective["zfar"];

    Camera* cam = new Camera(fov, near, far, pos, rot, scale);

    return cam;

}

void get_transformation(json node, glm::vec3 &pos, glm::quat &rot, glm::vec3 &scale){
    if(node.contains("translation")){
        float posx = node["translation"][0];
        float posy = node["translation"][1];
        float posz = node["translation"][2];
        pos = glm::vec3(posx, posy, posz);

    }else{
        pos = glm::vec3(0);
    }

    if(node.contains("rotation")){
        float rotx = node["rotation"][0];
        float roty = node["rotation"][1];
        float rotz = node["rotation"][2];
        float rotw = node["rotation"][3];

        rot = glm::quat(rotw, rotx, roty, rotz);
    }else{
        rot = glm::quat();
    }


    if(node.contains("scale")){
        float scalex = node["scale"][0];
        float scaley = node["scale"][1];
        float scalez = node["scale"][2];

        scale = glm::vec3(scalex, scaley, scalez);
    }else{
        scale = glm::vec3(1);
    }

}

Empty* import_empty(json node, json full){

    std::cout << "loading empty " << node["name"] << std::endl;


    glm::vec3 pos;
    glm::quat rot;
    glm::vec3 scale;


    get_transformation(node, pos, rot, scale);

    Empty* empty = new Empty(pos, rot, scale);
    empty->name = "Empty";

    return empty;
}

Scene* import_gltf(std::string path){
	std::ifstream ifs(path);

	json j;

	ifs >> j;



    std::vector<unsigned int> nodes_ids = get_scene_nodes(get_scene(j), j);

    std::vector<Object*> objects = import_nodes(nodes_ids, j);

    Scene* scene = new Scene();

    scene->objects = objects;

	return scene;
}

std::vector<Object*> import_nodes(std::vector<unsigned int> node_ids, json full){

    json nodes = full["nodes"];

    std::vector<Object*> objects;
    Object* current;
    for(unsigned int n = 0; n < node_ids.size(); n++){
        json node = nodes[node_ids[n]];
        if(node.contains("mesh")){
            current = import_mesh(node, full);
        }else if(node.contains("camera")){
            current = import_camera(node, full);
        }else{
            current = import_empty(node, full);
        }

        std::vector<unsigned int> children_ids = get_child_nodes(node);

        current->parent = nullptr;

        current->children = import_nodes(children_ids, full);

        for (unsigned int i = 0; i < current->children.size(); i++) {
            current->children[i]->parent = current;
        }

        objects.push_back(current);

    }

    return objects;
}

unsigned int get_scene(json j)
{
    return j["scene"];
}

std::vector<unsigned int> get_scene_nodes(unsigned int scene_id, json j)
{
    json scene = j["scenes"][scene_id];

    return scene["nodes"];

}

std::vector<unsigned int> get_child_nodes(json node)
{
    std::vector<unsigned int> children;
    if(!node.contains("children")){
        return children;
    }

    json children_indices = node["children"];
    for(auto c = children_indices.begin(); c != children_indices.end(); ++c){
        unsigned int index = c[0];
        children.push_back(index);
    }
    return children;

}

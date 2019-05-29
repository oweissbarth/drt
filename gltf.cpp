#include "gltf.h"

#include <fstream>
#include <iostream>

#include "json.hpp"
#include "base64.h"

using json = nlohmann::json;


Scene* import_gltf(std::string path){
	std::ifstream ifs(path);

	json j;

	ifs >> j;

	json nodes = j["nodes"];
	json meshes = j["meshes"];
	json buffers = j["buffers"];
    json accessors = j["accessors"];
    json bufferviews = j["bufferViews"];

    Scene* scene = new Scene();


	// import objects
	for(auto it = nodes.begin(); it != nodes.end(); ++it){
		if(it[0].contains("mesh")){
			std::cout << "loading mesh " << it[0]["name"] << std::endl;
            unsigned long mesh_index = it[0]["mesh"];
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

            std::vector<glm::vec3> positions(position_bytes, position_bytes + position_buffer_length);


            unsigned long face_buffer_offset = face_buffer_view["byteOffset"];
            unsigned long face_buffer_length = face_buffer_view["byteLength"];

            assert(face_buffer_index == position_buffer_index);

            const short* face_bytes = reinterpret_cast<const short*>(data.c_str()+face_buffer_offset);

            unsigned long face_count = static_cast<unsigned long>(face_accessor["count"])/3;

            std::vector<glm::uvec3> faces(face_count);
            for(unsigned long i = 0; i < faces.size(); i++){
                faces[i] = glm::uvec3(face_bytes[i*3], face_bytes[i*3+1], face_bytes[i*3+2]);
            }


            Object* obj = new Object(positions, faces, mesh["name"]);
            scene->addObject(obj);

		}
	}


	return scene;
}

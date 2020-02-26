#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>


class PreviewObject
{
public:
    virtual ~PreviewObject() = default;
    virtual void draw(glm::mat4 projectionMatrix, glm::mat4 viewMatrix) = 0;

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec3> colors;

protected:

    GLuint vertex_buffer, normal_buffer, color_buffer, vertex_shader, fragment_shader, program, VaoID;
    GLint v_position_location, v_normal_location, v_color_location, modelview_location, view_location, projection_location, modelviewprojection_location, normal_location, color_location;



    glm::mat4 modelMatrix;
    glm::mat4 viewMatrix;
    glm::mat4 modelViewMatrix;
    glm::mat4 normalMatrix;
    glm::mat4 projectionMatrix;
    glm::mat4 modelViewProjectionMatrix;


    std::string load_shader_code(std::string path);

    void update_shader(std::string name);
    void update_geometry();
    void retrieve_locations();
private:
    void check_compile_status(GLuint shader);
    void check_linking_status(GLuint program);

};

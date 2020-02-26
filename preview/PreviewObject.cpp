#include "PreviewObject.h"

#include <fstream>
#include <streambuf>
#include <iostream>

std::string PreviewObject::load_shader_code(std::string path){
    std::ifstream input_stream(path);

    std::string shader_text((std::istreambuf_iterator<char>(input_stream)),
                                   std::istreambuf_iterator<char>());


    //std::cout << "shader code:" <<shader_text << std::endl;

    return shader_text;
}

void PreviewObject::update_shader(std::string name){
    std::string vertex_shader_code = load_shader_code("../shaders/"+name+".vert");
    std::string fragment_shader_code = load_shader_code("../shaders/"+name+".frag");

    const char* vertex_shader_code_bytes = vertex_shader_code.c_str();
    const char* fragment_shader_code_bytes = fragment_shader_code.c_str();


    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_code_bytes, NULL);
    glCompileShader(vertex_shader);



    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_code_bytes, NULL);
    glCompileShader(fragment_shader);
    program = glCreateProgram();

    this->check_compile_status(vertex_shader);
    this->check_compile_status(fragment_shader);

    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);

    glBindAttribLocation(program, 0, "position");
    glBindAttribLocation(program, 1, "normal");
    glBindAttribLocation(program, 2, "vertexColor");

    glLinkProgram(program);

    this->check_linking_status(program);
}

void PreviewObject::check_compile_status(GLuint shader){
    GLint isCompiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE){
        GLint maxLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);
        std::string error (errorLog.begin(), errorLog.end());
        std::cout << error << std::endl;

    }
}

void PreviewObject::check_linking_status(GLuint programm){
    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE){
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> errorLog(maxLength);
        glGetProgramInfoLog(program, maxLength, &maxLength, &errorLog[0]);
        std::string error (errorLog.begin(), errorLog.end());
        std::cout << error << std::endl;
    }
}

void PreviewObject::update_geometry(){
    glGenVertexArrays(1, &VaoID);
    glBindVertexArray(VaoID);


    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertices.size()*3, vertices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(v_position_location);
    glVertexAttribPointer(v_position_location, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), NULL);


    if(normals.size() > 0){

        glGenBuffers(1, &normal_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float)*normals.size()*3, normals.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(v_normal_location);
        glVertexAttribPointer(v_normal_location, 3, GL_FLOAT, GL_FALSE, sizeof(normals[0]), NULL);
    }

    if(colors.size() > 0){
        glGenBuffers(1, &color_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float)*colors.size()*3, colors.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(v_color_location);
        glVertexAttribPointer(v_color_location, 3, GL_FLOAT, GL_FALSE, sizeof(colors[0]), NULL);

    }
    glBindVertexArray(0);

}

void PreviewObject::retrieve_locations(){
    modelview_location = glGetUniformLocation(program, "modelview_mat");
    projection_location = glGetUniformLocation(program, "projection_mat");
    modelviewprojection_location = glGetUniformLocation(program, "modelviewprojection_mat");
    view_location = glGetUniformLocation(program, "view_mat");
    normal_location = glGetUniformLocation(program, "normal_mat");
    color_location = glGetUniformLocation(program, "color");


    v_position_location = glGetAttribLocation(program, "position");
    v_normal_location = glGetAttribLocation(program, "normal");
    v_color_location = glGetAttribLocation(program, "vertexColor");

    std::cout << v_position_location <<"," << v_normal_location << ", "<< v_color_location <<std::endl;




}











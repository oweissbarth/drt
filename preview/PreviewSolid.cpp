#include "PreviewSolid.h"
#include <iostream>

PreviewSolid::PreviewSolid(std::vector<glm::vec3> verts, std::vector<glm::vec3> norms, std::vector<glm::vec3> colors, glm::mat4 transform): PreviewObject()
{
    this->vertices = verts;
    this->normals = norms;
    this->modelMatrix = transform;
    this->colors = colors;

    std::cout << vertices.size() << ", "<< colors.size() << std::endl;

    this->update_shader("phong");
    this->retrieve_locations();
    this->update_geometry();

    buffer_size = static_cast<GLsizei>(verts.size());

}

void PreviewSolid::draw(glm::mat4 projection, glm::mat4 view){
    //this->modelMatrix = glm::mat4(1.0);
    this->viewMatrix = view;
    this->projectionMatrix = projection;
    this->modelViewMatrix =  viewMatrix * modelMatrix;
    this->modelViewProjectionMatrix = projectionMatrix * modelViewMatrix;


    this->normalMatrix =  glm::transpose(glm::inverse(modelViewMatrix));

    glUseProgram(program);
    glUniformMatrix4fv(modelview_location, 1, GL_FALSE, &modelViewMatrix[0][0]);
    glUniformMatrix4fv(projection_location, 1, GL_FALSE, &projectionMatrix[0][0]);
    glUniformMatrix4fv(modelviewprojection_location, 1, GL_FALSE, &modelViewProjectionMatrix[0][0]);
    glUniformMatrix4fv(normal_location, 1, GL_FALSE, &normalMatrix[0][0]);
    glUniformMatrix4fv(view_location, 1, GL_FALSE, &viewMatrix[0][0]);


    glBindVertexArray(VaoID);
    glDrawArrays(GL_TRIANGLES, 0 , buffer_size);
    glBindVertexArray(0);

}



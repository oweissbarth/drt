#include "PreviewLines.h"

PreviewLines::PreviewLines(std::vector<glm::vec3> verts)
{
    this->vertices = verts;

    this->update_shader("simple");
    this->retrieve_locations();
    this->update_geometry();

    buffer_size = static_cast<GLsizei>(verts.size());

}

void PreviewLines::draw(glm::mat4 projection, glm::mat4 view){
    this->modelMatrix = glm::mat4(1.0);
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

    glUniform3f(color_location, 1.f ,1.f, 1.f);
    glBindVertexArray(VaoID);
    glDrawArrays(GL_LINES, 0 , buffer_size);
    glBindVertexArray(0);

}

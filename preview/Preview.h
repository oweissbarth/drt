#pragma once

#include <glm/gtx/quaternion.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "PreviewLines.h"
#include "PreviewSolid.h"

class Preview
{
public:
    Preview();
    void add(PreviewObject* obj);
    void draw();
private:
    std::vector<PreviewObject*> objects;

    float fov = 60;

    glm::mat4 projectionMatrix;
    glm::mat4 viewMatrix;

    glm::quat rotation = glm::angleAxis(0.f, glm::vec3(0,0,1));
    double distance;

    glm::vec2 cursor_pos;
    bool rotating = false;

    GLFWwindow* window;

    static void handle_mouse_button(GLFWwindow* window, int button, int action, int mods);
    static void handle_mouse_move(GLFWwindow* window, double xpos, double ypos);
    static void handle_mouse_scroll(GLFWwindow* window, double xoffset, double yoffset);

};


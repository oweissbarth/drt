#include "Preview.h"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>

#include <glm/gtx/string_cast.hpp>
void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void GLAPIENTRY gl_error_handler( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam )
{
  fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, severity, message );
}

Preview::Preview()
{
    glfwSetErrorCallback(error_callback);


    if (!glfwInit())
    {
        std::cerr << "GLFW init failed" << std::endl;
    }



    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_DEPTH_BITS, 32);

    window = glfwCreateWindow(640, 480, "DRT", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "GLFW window creation failed" << std::endl;
    }

    glfwMakeContextCurrent(window);

    gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));


    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glfwSwapInterval(1);

    float aspectratio = (float)width/(float)height;
    std::cout << "aspect ratio" << aspectratio << std::endl;
    projectionMatrix= glm::perspective(fov*3.14f/180.f, aspectratio , 1.f, 50.0f);
    viewMatrix = glm::lookAt(glm::vec3(0.0, 0.0, 10.0), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));


    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(gl_error_handler, 0 );

    glfwSetWindowUserPointer(window, this);




    int num_ext = 0;
    glGetIntegerv(GL_NUM_EXTENSIONS, &num_ext);
    for(int i=0; i<num_ext; i++){
        std::string ex = reinterpret_cast<char const * >(glGetStringi(GL_EXTENSIONS,i));
        if(ex == "GL_ARB_compatibility"){
             printf("Compatiblity Profile");
        }
    }

    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glEnable (GL_DEPTH_TEST);

}

void Preview::add(PreviewObject *obj){
    this->objects.push_back(obj);
}

void Preview::handle_mouse_button(GLFWwindow* window, int button, int action, int mods){
    Preview* p = static_cast<Preview*>(glfwGetWindowUserPointer(window));
    if(button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS){
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        p->cursor_pos = glm::vec2(xpos, ypos);
        p->rotating = true;
    }else if(button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE){
        p->rotating = false;
    }
}

void Preview::handle_mouse_move(GLFWwindow *window, double xpos, double ypos){
    Preview* p = static_cast<Preview*>(glfwGetWindowUserPointer(window));
    if(!p->rotating){
        return;
    }
    float sensitivity = 0.007f;

    glm::mat3 m = glm::mat3_cast(p->rotation);
    m = glm::inverse(m);


    glm::vec3 xaxis(glm::column(m,0));

    float xangle = sensitivity*(static_cast<float>(ypos) - p->cursor_pos.y);
    float yangle = sensitivity*(static_cast<float>(xpos) - p->cursor_pos.x);

    glm::quat xquat = glm::angleAxis(xangle , xaxis);
    glm::quat yquat = glm::angleAxis(yangle, glm::vec3(0,1,0));


    p->rotation = p->rotation * xquat * yquat;

    p->rotation = glm::normalize(p->rotation);

    p->cursor_pos = glm::vec2(xpos, ypos);


}

void Preview::draw(){

    glfwSetMouseButtonCallback(window, handle_mouse_button);
    glfwSetCursorPosCallback(window, handle_mouse_move);

    std::cout << glm::to_string(projectionMatrix) << std::endl;


    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.2f, 0.2f, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 rot = glm::mat4_cast(rotation);

        //std::cout << glm::to_string(rotation) <<std::endl;

        for (unsigned long i = 0; i < objects.size(); i++) {
            objects[i]->draw(projectionMatrix, viewMatrix*rot);
        }

        glfwSwapBuffers(window);
        glfwWaitEvents();

    }
    std::cout << "Should close window" << std::endl;
    glfwDestroyWindow(window);
    glfwTerminate();
}



#include "App.hpp"
#include "debug.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace app;

void App::initOpenGL() {
    if (!glfwInit()) {
        throw "Failed to init glfw library";
    }
    // create window with opengl context
    window = glfwCreateWindow(640, 480, "OpenGL app", NULL, NULL);
    if (!window) 
    {
        glfwTerminate();
        throw "Failed to create opengl window";
    }
    // make window current context
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // vsync
    // glew init
    GLenum err = glewInit();
    if (GLEW_OK != err) 
    {
        char buffer[100] = {0};
        snprintf(buffer, 100, "%s", glewGetErrorString(err));
        throw (const char *)buffer;
    }
    // set debugger
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(HandleDebug, nullptr);
        
    // get opengl version
    std::cout << "OpenGL version: " <<
        glGetString(GL_VERSION) << std::endl;
}
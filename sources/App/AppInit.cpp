#include "App.hpp"
#include "Debug.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <iostream>

void App::initOpenGL() {
    if (!glfwInit()) {
        std::cerr << "Failed to init glfw library" << std::endl;
        exit(EXIT_FAILURE);
    }
    // set opengl profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // create window with opengl context
    window = glfwCreateWindow(640, 480, "OpenGL app", NULL, NULL);
    if (!window) 
    {
        glfwTerminate();
        std::cerr << "Failed to create opengl window" << std::endl;
        exit(EXIT_FAILURE);
    }
    // make window current context
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // vsync
    // glew init
    GLenum err = glewInit();
    if (GLEW_OK != err) 
    {
        std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
        exit(EXIT_FAILURE);
    }
    // set debugger
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(HandleDebug, nullptr);
        
    // get opengl version
    std::cout << "OpenGL version: " <<
        glGetString(GL_VERSION) << std::endl;
}
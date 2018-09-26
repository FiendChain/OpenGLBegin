#include "App.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <exception>

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
    // glew init
    GLenum err = glewInit();
    if (GLEW_OK != err) 
    {
        char buffer[100] = {0};
        snprintf(buffer, 100, "%s", glewGetErrorString(err));
        throw (const char *)buffer;
    }
        
    // get opengl version
    fprintf(stdout, "OpenGL version: %s\n", glGetString(GL_VERSION));
}
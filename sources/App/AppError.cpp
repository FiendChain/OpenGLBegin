#include "App.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace app;

void App::GLClearErrors() {
    while (glGetError() != GL_NO_ERROR)
    {

    }
}

void App::GLCheckErrors() {
    while (GLenum error = glGetError())
    {
        std::cerr << "[OpenGL Error] (" << error << ")" << std::endl;
    }
}

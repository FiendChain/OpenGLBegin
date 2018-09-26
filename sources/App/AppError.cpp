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
 
bool App::GLCheckErrors(const char *funcName, const char *file, int line) {
    while (GLenum error = glGetError())
    {
        std::cerr << "[OpenGL Error] (" << error << "): "
            << funcName << "@" << file << ":" << line << std::endl;
        return false;
    }
    return true; 
}

#include "App.hpp"
#include "Debug.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <iostream>
#include <imgui/imgui.h>
#include "ImGui.h"
#include <memory>

bool App::InitGLFW() {
    if (glfwInit() == GL_FALSE) {
        std::cerr << "Failed to init glfw library" << std::endl;
        return false;
    }
    // set opengl profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // create window with opengl context
    window = std::unique_ptr<GLFWwindow, DestroyglfwWin>(glfwCreateWindow(m_Width, m_Height, "OpenGL app", NULL, NULL));
    if (!window.get()) 
    {
        glfwTerminate();
        std::cerr << "Failed to create opengl window" << std::endl;
        return false;
    }
    // make window current context
    glfwMakeContextCurrent(window.get());
    glfwSwapInterval(1);
}

bool App::InitGlew()
{
    GLenum err = glewInit();
    if (err != GLEW_OK) 
    {
        std::cerr << "Glew init error: " << glewGetErrorString(err) << std::endl;
        return false;
    }
    return true;
}

bool App::InitImGui()
{
    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(window.get(), true);
    ImGui::StyleColorsDark();
    return true;
}

void App::EnableDebug()
{
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(HandleDebug, nullptr);
}

void App::Enable3D() 
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}
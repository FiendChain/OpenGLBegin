#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class App {
    private:
        GLFWwindow* window;
        unsigned int m_Width;
        unsigned int m_Height;
    public:
        App(unsigned int width, unsigned int height);
        void Run();
        void EnableDebug();
    private:
        void Render();
        bool InitGLFW();
        bool InitGlew();
        bool InitImGui();
};
#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <memory>

struct DestroyglfwWin {
    void operator()(GLFWwindow* ptr){
        glfwDestroyWindow(ptr);
    }
};

class App {
    private:
        std::unique_ptr<GLFWwindow, DestroyglfwWin> window;
        unsigned int m_Width;
        unsigned int m_Height;
    public:
        App(unsigned int width, unsigned int height);
        ~App();
        void Run();
        void EnableDebug();
        void Enable3D();
    private:
        void Render();
        bool InitGLFW();
        bool InitGlew();
        bool InitImGui();
};
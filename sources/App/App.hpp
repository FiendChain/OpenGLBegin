#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

struct Position {
    float x;
    float y;
};

struct TextCoords {
    float x;
    float y;
};

struct VertexData {
    struct Position position;
    struct TextCoords textCoords;
};

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
};
#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

namespace app {

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
    public:
        App();
        void run();
    private:
        GLFWwindow* window;
        void render();
        void initOpenGL();
};

};
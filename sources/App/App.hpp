#ifndef _APP_H_
#define _APP_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

namespace app {

struct Position {
    float x;
    float y;
};

struct VertexData {
    struct Position position;
};

struct ShaderFile {
    std::string vertex;
    std::string fragment;
};

class App {
    public:
        App();
        void run();
    private:
        GLFWwindow* window;
        void render();
        // error handling
        void GLClearErrors();
        bool GLCheckErrors(const char *, const char *, int);
        // compile shaders and create program
        unsigned int createProgram(const std::string&, const std::string&);
        struct ShaderFile parseShaderFile(const std::string&);
        unsigned int compileShader(unsigned int, const std::string&);
        // init
        void initOpenGL();
};

};

#endif
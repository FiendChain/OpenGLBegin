#include "App.hpp"
#include "../RainbowColour/RainbowColour.hpp"
#include "macros.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace app;

App::App() {
    initOpenGL();
}

void App::run() {
    render();
}

void App::render() {
    struct VertexData vertex_data[] = {
        {-0.5f, -0.5f},
        { 0.5f, -0.5f},
        { 0.5f,  0.5f},
        {-0.5f,  0.5f}, // use an index buffer to reuse prev vertexes
    };
    // induces
    unsigned int indices[] = {
        0, 1, 2, // bottom triangle
        2, 3, 0, // top triangle
    };
    // creating and assigning data
    unsigned int buffer;
    GLCall(glGenBuffers(1, &buffer));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW));
    // vertex layout
    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(struct Position), (const void*)offsetof(VertexData, position)));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0)); 
    // create index buffer object
    unsigned int ibo; // index buffer object
    GLCall(glGenBuffers(1, &ibo));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));
    // load shaders
    struct ShaderFile shaderFile = parseShaderFile("resources/shaders/basicShader.glsl");
    unsigned int shader = createProgram(shaderFile.vertex, shaderFile.fragment);
    GLCall(glUseProgram(shader));
    // create a uniform
    GLCall(int location = glGetUniformLocation(shader, "u_Color"));
    ASSERT((location != -1));
    GLCall(glUniform4f(location, 0.2f, 0.3f, 0.8f, 1.0f));
    // dynamic uniform
    RainbowColour rainbow;
    // main render loop
    while (!glfwWindowShouldClose(window)) 
    {
        // clear window
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        GLCall(glUniform4f(location, rainbow.r, rainbow.g, rainbow.b, rainbow.a));
        GLCall(glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(unsigned int), GL_UNSIGNED_INT, nullptr));
        rainbow.update(); 
        // swap front and back buffers
        GLCall(glfwSwapBuffers(window)); 
        // poll events
        GLCall(glfwPollEvents());
    }
    GLCall(glDeleteProgram(shader));
    // terminate the opengl library? or context?
    glfwTerminate();
}


#include "App.hpp"
#include "../RainbowColour/RainbowColour.hpp"
#include "Errors.hpp"
#include "Shaders.hpp" 
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace app;

App::App() {
    initOpenGL();
}

void App::run() {
    render();
    glfwTerminate(); // terminate the opengl library? or context?
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
    // create vertex array object
    unsigned int vao;
    GLCall(glGenVertexArrays(1, &vao));
    GLCall(glBindVertexArray(vao));
    // creating and assigning data
    VertexBuffer vertexBuffer(vertex_data, sizeof(vertex_data));
    // vertex layout/attributes
    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(struct Position), (const void*)offsetof(VertexData, position)));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0)); 
    // create index buffer object
    IndexBuffer indexBuffer(indices, 6);
    // load shaders
    struct ShaderFile shaderFile = parseShaderFile("resources/shaders/basicShader.glsl");
    unsigned int shader = createProgram(shaderFile.vertex, shaderFile.fragment);
    GLCall(glUseProgram(shader));
    // create a uniform
    GLCall(int location = glGetUniformLocation(shader, "u_Color"));
    ASSERT(location != -1);
    // dynamic uniform
    RainbowColour rainbow;
    // unbind all the buffers
    GLCall(glUseProgram(0));
    vertexBuffer.Unbind();
    indexBuffer.Unbind();
    // main render loop
    while (!glfwWindowShouldClose(window)) 
    {
        // clear window
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
        // set program and uniform for the shader
        GLCall(glUseProgram(shader));
        GLCall(glUniform4f(location, rainbow.r, rainbow.g, rainbow.b, rainbow.a));
        // bind vertex buffer
        vertexBuffer.Bind();
        // set vertex layout again
        GLCall(glEnableVertexAttribArray(0)); 
        GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(struct Position), (const void*)offsetof(VertexData, position)));
        // index buffer
        indexBuffer.Bind();
        // render
        GLCall(glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(unsigned int), GL_UNSIGNED_INT, nullptr));
        rainbow.update(); 
        // swap front and back buffers
        GLCall(glfwSwapBuffers(window)); 
        // poll events
        GLCall(glfwPollEvents());
    }
    GLCall(glDeleteProgram(shader));
}


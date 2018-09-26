#include "App.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>

#include <string>
#include <fstream>
#include <sstream>

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
    unsigned int bufferId;
    glGenBuffers(1, &bufferId);
    glBindBuffer(GL_ARRAY_BUFFER, bufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);
    // vertex layout
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(struct Position), (const void*)offsetof(VertexData, position));
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    // create index buffer object
    unsigned int ibo; // index buffer object
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // load shaders
    struct ShaderFile shaderFile = parseShaderFile("resources/shaders/basicShader.glsl");
    unsigned int programId = createProgram(shaderFile.vertex, shaderFile.fragment);
    glUseProgram(programId);

    // main render loop
    while (!glfwWindowShouldClose(window)) 
    {
        // clear window
        glClear(GL_COLOR_BUFFER_BIT);
        // render using index buffer
        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(unsigned int), GL_UNSIGNED_INT, nullptr);
        // swap double buffer (front and back)
        glfwSwapBuffers(window); 
        // poll events
        glfwPollEvents();
    }
    glDeleteProgram(programId);
    // terminate the opengl library? or context?
    glfwTerminate();
}


#include "App.hpp"
#include "../RainbowColour/RainbowColour.hpp"
#include "Errors.hpp"
#include "Shader.hpp" 
#include "Uniform.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "Renderer.hpp"
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
    VertexArray vertexArray;
    VertexBuffer vertexBuffer(vertex_data, sizeof(vertex_data));
    
    VertexBufferLayout layout;
    layout.Push<float>(2);
    vertexArray.AddBuffer(vertexBuffer, layout);

    IndexBuffer indexBuffer(indices, 6);

    Shader shader("resources/shaders/basicShader.glsl");
    UniformRainbow uniform; 
    shader.AddUniform("u_Color", &uniform);

    shader.Unbind();
    vertexBuffer.Unbind();
    indexBuffer.Unbind();

    Renderer renderer;
    while (!glfwWindowShouldClose(window)) 
    {
        renderer.Clear();
        renderer.Draw(vertexArray, indexBuffer, shader);
        GLCall(glfwSwapBuffers(window)); 
        GLCall(glfwPollEvents());
    }
}


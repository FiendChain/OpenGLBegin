#include "App.hpp"
#include "../RainbowColour/RainbowColour.hpp"
#include "OpenGL.hpp"
#include "Shader.hpp" 
#include "Uniform.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "Renderer.hpp"
#include "Texture.hpp"

App::App() {
    initOpenGL();
}

void App::run() {
    render();
    glfwTerminate(); // terminate the opengl library? or context?
}

void App::render() {
    struct VertexData vertex_data[] = {
        {-0.5f, -0.5f, 0.0f, 0.0f},
        { 0.5f, -0.5f, 1.0f, 0.0f},
        { 0.5f,  0.5f, 1.0f, 1.0f},
        {-0.5f,  0.5f, 0.0f, 1.0f}, // use an index buffer to reuse prev vertexes
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
    layout.Push<float>(2);
    vertexArray.AddBuffer(vertexBuffer, layout);

    IndexBuffer indexBuffer(indices, 6);

    Shader shader("resources/shaders/basicShader.glsl");
    UniformRainbow rainbowUniform; 
    Uniform4<float> uniform(0.5f, 0.5f, 0.5f, 1.0f);
    shader.AddUniform("u_Color", &uniform);

    Texture texture("resources/textures/doge.png");
    texture.Bind(0);
    Uniform1<int> textureUniform(0);
    shader.AddUniform("u_Texture", &textureUniform);

    shader.Unbind();
    vertexBuffer.Unbind();
    indexBuffer.Unbind();

    Renderer renderer;
    while (!glfwWindowShouldClose(window)) 
    {
        renderer.Clear();
        renderer.Draw(vertexArray, indexBuffer, shader);
        rainbowUniform.Update();
        GLCall(glfwSwapBuffers(window)); 
        GLCall(glfwPollEvents());
    }
}


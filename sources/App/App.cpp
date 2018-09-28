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

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

App::App(unsigned int width, unsigned int height) 
    : m_Width(width), m_Height(height)
{
    ASSERT(InitGLFW());
    ASSERT(InitGlew());
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
}

void App::Run() {
    Render();
    glfwTerminate(); // terminate the opengl library? or context?
}

void App::Render() {
    struct VertexData vertex_data[] = {
        // position of vertex, texture coordinate
        // texture coordinate is normalised coordinate on texture where the vertex is
        {{200, 200}, {0.0f, 0.0f}}, // 0 (bottom left)
        {{400, 200}, {1.0f, 0.0f}}, // 1 (bottom right)
        {{400, 400}, {1.0f, 1.0f}}, // 2 (top right)
        {{200, 400}, {0.0f, 1.0f}}, // 3 (top left)
    };
    // induces
    unsigned int indices[] = {
        0, 1, 2, 
        2, 3, 0, 
    };
    // projection matrix
    glm::mat4 proj = glm::ortho(0.0f, (float)m_Width, 0.0f, (float)m_Height, -1.0f, 1.0f);
    // view matrix
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));
    // model
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200, 200, 0));
    // Model * View * Projection matrix
    // reverse order b/c column major
    // standard matrix mult MVP is for row major matrixes
    glm::mat4 mvp = proj * view * model; 
    UniformMat4f u_MVP(mvp);
    // create buffers
    VertexArray vertexArray;
    VertexBuffer vertexBuffer(vertex_data, sizeof(vertex_data));
    
    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    vertexArray.AddBuffer(vertexBuffer, layout);

    IndexBuffer indexBuffer(indices, 6);

    Shader shader("resources/shaders/basicShader.glsl");
    UniformRainbow u_Rainbow; 
    shader.AddUniform("u_Color", &u_Rainbow);
    shader.SetUniform("u_MVP", &u_MVP);

    Texture texture("resources/textures/doge.png");
    texture.Bind(0);
    Uniform1<int> u_Texture(0);
    shader.SetUniform("u_Texture", &u_Texture);

    shader.Unbind();
    vertexBuffer.Unbind();
    indexBuffer.Unbind();

    Renderer renderer;
    while (!glfwWindowShouldClose(window)) 
    {
        renderer.Clear();
        renderer.Draw(vertexArray, indexBuffer, shader);
        u_Rainbow.Update();
        GLCall(glfwSwapBuffers(window)); 
        GLCall(glfwPollEvents());
    }
}


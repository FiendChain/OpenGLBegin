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
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>

App::App(unsigned int width, unsigned int height) 
    : m_Width(width), m_Height(height)
{
    ASSERT(InitGLFW());
    ASSERT(InitGlew());
    ASSERT(InitImGui());
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
}

void App::Run() {
    Render();
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate(); // terminate the opengl library? or context?
}

void App::Render() {
    struct VertexData vertex_data[] = {
        // centre the object around (0,0,0)
        {{-50.0f, -50.0f}, {0.0f, 0.0f}}, // 0 (bottom left)
        {{ 50.0f, -50.0f}, {1.0f, 0.0f}}, // 1 (bottom right)
        {{ 50.0f,  50.0f}, {1.0f, 1.0f}}, // 2 (top right)
        {{-50.0f,  50.0f}, {0.0f, 1.0f}}, // 3 (top left)
    };
    // induces
    unsigned int indices[] = {
        0, 1, 2, 
        2, 3, 0, 
    };
    // projection matrix - projection of model to screen
    glm::mat4 proj = glm::ortho(0.0f, (float)m_Width, 0.0f, (float)m_Height, -1.0f, 1.0f);
    // view matrix - position of camera
    glm::vec3 viewTranslation(0, 0, 0);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), viewTranslation);
    // model - position of model
    glm::mat4 model = glm::mat4(1.0f);
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
    shader.AddUniform("u_MVP", &u_MVP);

    Texture texture("resources/textures/doge.png");
    texture.Bind(0);
    Uniform1<int> u_Texture(0);
    shader.SetUniform("u_Texture", &u_Texture);

    shader.Unbind();
    vertexBuffer.Unbind();
    indexBuffer.Unbind();

    Renderer renderer;
    glm::vec3 dogeTranslations[2] = {
        glm::vec3(0, 0, 0), 
        glm::vec3(0, 0, 0),
    };

    while (!glfwWindowShouldClose(window)) 
    {
        // renderer
        renderer.Clear();
        u_Rainbow.Update();
        view = glm::translate(glm::mat4(1.0f), viewTranslation); 
        // doges
        for (const auto& modelTranslation: dogeTranslations)
        {
            model = glm::translate(glm::mat4(1.0f), modelTranslation);    
            mvp = proj * view * model;
            u_MVP.Update(mvp);
            renderer.Draw(vertexArray, indexBuffer, shader);
        }
        // imgui test window
        ImGui_ImplGlfwGL3_NewFrame();
        {
            ImGui::SliderFloat3("View translation", &viewTranslation.x, 0, m_Width);
            ImGui::SliderFloat3("Doge 1 translation", &dogeTranslations[0].x, 0, m_Width);
            ImGui::SliderFloat3("Doge 2 translation", &dogeTranslations[1].x, 0, m_Width);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }
        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
        // update window
        GLCall(glfwSwapBuffers(window)); 
        GLCall(glfwPollEvents());
    }
}


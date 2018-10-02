#include "App.hpp"
#include "RainbowColour/RainbowColour.hpp"
#include "OpenGL.hpp"
#include "Shader.hpp"  
#include "Uniform.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "Renderer.hpp"
#include "Texture.hpp"

#include "Tests/TestClearColour.hpp"
#include "Tests/TestRainbow.hpp"
#include "Tests/TestDoge.hpp"
#include "Tests/TestTexture.hpp"
#include "Tests/TestMenu.hpp"

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
    test::TestMenu testMenu;
    testMenu.AddTest<test::TestClearColour>("Clear colour");
    testMenu.AddTest<test::TestDoge>("Doge", m_Width, m_Height);
    testMenu.AddTest<test::TestRainbow>("Rainbow");
    testMenu.AddTest<test::TestTexture>("Texture", "resources/textures/doge.png");
    Renderer renderer;
    while (!glfwWindowShouldClose(window)) 
    {
        renderer.Clear();
        testMenu.OnUpdate(0.0f);
        testMenu.OnRender();

        // imgui test window
        ImGui_ImplGlfwGL3_NewFrame();
        {
            testMenu.OnImGuiRender();
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }
        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
        
        GLCall(glfwSwapBuffers(window)); 
        GLCall(glfwPollEvents());
    }
}


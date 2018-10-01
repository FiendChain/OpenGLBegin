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
    test::TestClearColour testClearColour;
    test::TestRainbow testRainbow;
    Renderer renderer;
    while (!glfwWindowShouldClose(window)) 
    {
        renderer.Clear();
        testRainbow.OnUpdate(0.0f);
        testRainbow.OnRender();

        // imgui test window
        ImGui_ImplGlfwGL3_NewFrame();
        {
            testRainbow.OnImGuiRender();
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }
        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
        
        GLCall(glfwSwapBuffers(window)); 
        GLCall(glfwPollEvents());
    }
}


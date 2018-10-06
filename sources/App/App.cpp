#include "App.hpp"
#include "OpenGL.hpp"

#include "Tests/TestClearColour.hpp"
#include "Tests/TestRainbow.hpp"
#include "Tests/TestDoge.hpp"
#include "Tests/TestTexture.hpp"
#include "Tests/TestMenu.hpp"
#include "Tests/TestCube.hpp"
#include "Tests/TestCubeTexture.hpp"

#include <iostream>
#include <imgui/imgui.h>
#include "ImGui.h"

App::App(unsigned int width, unsigned int height) 
    : m_Width(width), m_Height(height)
{
    ASSERT(InitGLFW());
    ASSERT(InitGlew());
    ASSERT(InitImGui());
    Enable3D();
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
}

App::~App()
{
    ImGui::DestroyContext();
    glfwTerminate(); // terminate the opengl library? or context?
}

void App::Run() 
{
    Render();
}

void App::Render() 
{
    test::TestMenu testMenu;
    testMenu.AddTest<test::TestClearColour>("Clear colour");
    testMenu.AddTest<test::TestDoge>("Doge", m_Width, m_Height);
    testMenu.AddTest<test::TestRainbow>("Rainbow");
    testMenu.AddTest<test::TestTexture>("Texture", "resources/textures/doge.png");
    testMenu.AddTest<test::TestCube>("Cube", m_Width, m_Height);
    testMenu.AddTest<test::TestCubeTexture>("Dice", "resources/textures/dice.png", m_Width, m_Height);
    testMenu.AddTest<test::TestCubeTexture>("Rainbow Cube", "resources/textures/rainbow_cube.png", m_Width, m_Height);
    Renderer renderer;
    while (!glfwWindowShouldClose(window.get())) 
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
        
        GLCall(glfwSwapBuffers(window.get())); 
        GLCall(glfwPollEvents());
    }
    ImGui_ImplGlfwGL3_Shutdown();
}


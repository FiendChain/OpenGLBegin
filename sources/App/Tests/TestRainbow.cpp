#include "TestRainbow.hpp"
#include "RainbowColour/RainbowColour.hpp"
#include "OpenGL.hpp"
#include <imgui/imgui.h>

namespace test
{

TestRainbow::TestRainbow()
{

}

TestRainbow::~TestRainbow()
{

}

void TestRainbow::OnUpdate(float deltaTime)
{
    m_Rainbow.update();
}

void TestRainbow::OnRender()
{
    GLCall(glClearColor(m_Rainbow.r, m_Rainbow.g, m_Rainbow.b, m_Rainbow.a));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void TestRainbow::OnImGuiRender()
{
    ImGui::ColorEdit4("Clear colour", m_Rainbow.components);
}

}

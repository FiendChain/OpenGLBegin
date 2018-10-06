#include "TestCube.hpp"

#include "VertexBufferLayout.hpp"
#include <imgui/imgui.h>
#include <memory>
#include <glm/glm.hpp>

struct VertexData
{
    struct { float x, y, z; } position;
    struct { float r, g, b; } colour;
};

static const VertexData vertexData[] = {
    {{-1.0f, -1.0f, -1.0f}, { 1.0f, 0.0f, 0.0f}},
    {{ 1.0f, -1.0f, -1.0f}, { 1.0f, 1.0f, 0.0f}},
    {{-1.0f,  1.0f, -1.0f}, { 0.0f, 1.0f, 0.0f}},
    {{ 1.0f,  1.0f, -1.0f}, { 0.0f, 1.0f, 1.0f}},
    {{-1.0f, -1.0f,  1.0f}, { 0.0f, 0.0f, 1.0f}},
    {{ 1.0f, -1.0f,  1.0f}, { 1.0f, 0.0f, 1.0f}},
    {{-1.0f,  1.0f,  1.0f}, { 1.0f, 0.0f, 0.0f}},
    {{ 1.0f,  1.0f,  1.0f}, { 1.0f, 1.0f, 0.0f}},
};

static unsigned int indices[] = {
    0, 1, 2, // bottom face
    1, 2, 3,
    4, 5, 6, // top face
    5, 6, 7,
    0, 1, 4, // front face
    1, 4, 5,
    2, 3, 6, // back face
    3, 6, 7,
    0, 2, 4, // left face
    2, 4, 6,
    1, 3, 5, // right face
    3, 5, 7,
};

namespace test
{

TestCube::TestCube(unsigned int width, unsigned int height)
    : m_MVP_Control(width, height),
      m_Width(width), m_Height(height),
      m_Shader("resources/shaders/cubeTest.glsl"),
      m_VertexBuffer(vertexData, sizeof(vertexData)),
      m_IndexBuffer(indices, 3*2*6),
      u_MVP(std::make_shared<UniformMat4f>(glm::mat4(1.0f)))
{
    VertexBufferLayout vertexBufferLayout;
    vertexBufferLayout.Push<float>(3);
    vertexBufferLayout.Push<float>(3, GL_FALSE);
    m_VertexArray.AddBuffer(m_VertexBuffer, vertexBufferLayout);
    m_Shader.AddUniform("u_MVP", u_MVP);
}

void TestCube::OnUpdate(float deltaTime)
{
    m_MVP_Control.OnUpdate();
}

void TestCube::OnRender()
{
    u_MVP->Update(m_MVP_Control.GetMVP());
    m_Renderer.Draw(m_VertexArray, m_IndexBuffer, m_Shader);
}

void TestCube::OnImGuiRender()
{
    m_MVP_Control.OnImGuiRender(); 
}

}
#include "TestCubeTexture.hpp"
#include "VertexBufferLayout.hpp"
#include "Uniform.hpp"

#include <imgui/imgui.h>
#include <memory>
#include <glm/glm.hpp>
#include <string>

struct VertexData
{
    struct { float x, y, z; } position;
    struct { float u, v; }    textCoord;
};

static const VertexData vertexData[] = {
    {{-1.0f, -1.0f, -1.0f}, { 0.00f, 0.66f}}, // 0
    {{ 1.0f, -1.0f, -1.0f}, { 0.00f, 0.33f}},
    {{-1.0f,  1.0f, -1.0f}, { 0.25f, 0.66f}},
    {{ 1.0f,  1.0f, -1.0f}, { 0.25f, 0.33f}},
    {{-1.0f, -1.0f,  1.0f}, { 0.75f, 0.66f}},
    {{ 1.0f, -1.0f,  1.0f}, { 0.75f, 0.33f}},
    {{-1.0f,  1.0f,  1.0f}, { 0.50f, 0.66f}},
    {{ 1.0f,  1.0f,  1.0f}, { 0.50f, 0.33f}}, // 7
    // add duplicate vertices to wrap texture
    {{-1.0f, -1.0f, -1.0f}, { 1.00f, 0.66f}}, // 8:0a // edge a
    {{ 1.0f, -1.0f, -1.0f}, { 1.00f, 0.33f}}, // 9:1a
    {{-1.0f, -1.0f, -1.0f}, { 0.75f, 1.00f}}, // 10:0b // edge b
    {{-1.0f,  1.0f, -1.0f}, { 0.50f, 1.00f}}, // 11:2b
    {{ 1.0f, -1.0f, -1.0f}, { 0.75f, 0.00f}}, // 12:1c // edge c
    {{ 1.0f,  1.0f, -1.0f}, { 0.50f, 0.00f}}, // 13:3c
};

static unsigned int indices[] = {
     0,  1,  2, // 1
     1,  2,  3,
     2,  3,  6, // 2
     3,  6,  7,
     6,  7,  4, // 3
     7,  4,  5,
     4,  5,  8, // 4: 4,5,0a
     5,  8,  9, //    5,0a,1a
     7, 13,  5, // 5: 7,3c,5
    13,  5, 12, //    3c,5,1c
    11,  6, 10, // 6: 2b,6,0b
     6, 10,  4, //    6,0b,4
};

namespace test
{

TestCubeTexture::TestCubeTexture(const std::string& filepath, unsigned int width, unsigned int height)
    : m_MVP_Control(width, height),
      m_Width(width), m_Height(height),
      m_Filepath(filepath),
      m_Shader("resources/shaders/cubeTextureTest.glsl"),
      m_Texture(filepath),
      m_VertexBuffer(vertexData, sizeof(vertexData)),
      m_IndexBuffer(indices, 3*2*6),
      u_MVP(std::make_shared<UniformMat4f>(glm::mat4(1.0f))),
      u_Texture(std::make_shared<Uniform1<int>>(0))
{
    VertexBufferLayout vertexBufferLayout;
    vertexBufferLayout.Push<float>(3);
    vertexBufferLayout.Push<float>(2);
    m_VertexArray.AddBuffer(m_VertexBuffer, vertexBufferLayout);
    m_Shader.AddUniform("u_MVP", u_MVP);
    m_Shader.AddUniform("u_Texture", u_Texture);
    m_Texture.Bind(0);
}

void TestCubeTexture::OnUpdate(float deltaTime)
{
    m_MVP_Control.OnUpdate();
}

void TestCubeTexture::OnRender()
{
    u_MVP->Update(m_MVP_Control.GetMVP());
    m_Texture.Bind(0);
    m_Renderer.Draw(m_VertexArray, m_IndexBuffer, m_Shader);
}

void TestCubeTexture::OnImGuiRender()
{
    ImGui::Text("Rendering texture %s", m_Filepath.c_str());
    m_MVP_Control.OnImGuiRender(); 
}

}
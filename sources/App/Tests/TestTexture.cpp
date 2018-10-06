#include "TestTexture.hpp"
#include "Uniform.hpp"
#include <string>
#include <memory>
#include <imgui/imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct VertexData {
    struct { float x, y; } position;
    struct { float x, y; } textCoord;
};

static VertexData vertexData[4] = {
    {{-1.0f, -1.0f}, {0.0f, 0.0f}},
    {{ 1.0f, -1.0f}, {1.0f, 0.0f}},
    {{ 1.0f,  1.0f}, {1.0f, 1.0f}},
    {{-1.0f,  1.0f}, {0.0f, 1.0f}},
};

static unsigned int indices[] = {
    0, 1, 2, 
    2, 3, 0, 
};

namespace test
{

TestTexture::TestTexture(const std::string& filepath)
    : m_Filepath(filepath),
      m_Texture(filepath),
      m_Shader("resources/shaders/textureTest.glsl"),
      u_Texture(std::make_shared<Uniform1<int>>(0)),
      u_MVP(std::make_shared<UniformMat4f>(glm::mat4(1.0f))),
      m_Translation(0.0f), m_Rotation(0.0f, 0.0f, 1.0f), m_Scale(1.0f), m_Angle(0),
      m_VertexBuffer(vertexData, sizeof(vertexData)),
      m_IndexBuffer(indices, 6) 
{
    // set layout
    m_VertexBufferLayout.Push<float>(2);
    m_VertexBufferLayout.Push<float>(2);
    m_VertexArray.AddBuffer(m_VertexBuffer, m_VertexBufferLayout);
    // bind texture
    m_Texture.Bind(0);
    m_Shader.AddUniform("u_Texture", u_Texture);
    m_Shader.AddUniform("u_MVP", u_MVP);
}

TestTexture::~TestTexture()
{

}

void TestTexture::OnRender()
{
    glm::mat4 model = glm::scale(glm::mat4(1.0f), m_Scale);
    model = glm::translate(model, m_Translation);
    model = glm::rotate(model, (float)m_Angle, m_Rotation);
    u_MVP->Update(model);
    m_Renderer.Draw(m_VertexArray, m_IndexBuffer, m_Shader);
}

void TestTexture::OnImGuiRender()
{
    ImGui::Text("Rendering texture %s", m_Texture.GetFilePath().c_str());
    ImGui::SliderFloat3("Translation", &m_Translation.x, 0, 1.0f);
    ImGui::SliderFloat3("Rotation", &m_Rotation.x, 0, 1.0f);
    ImGui::SliderFloat3("Scale", &m_Scale.x, 0, 1.0f);
    ImGui::SliderAngle("Angle", &m_Angle, 0, 360);
}

}
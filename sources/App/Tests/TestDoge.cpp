#include "TestDoge.hpp"
#include "Uniform.hpp"
#include <memory>
#include <imgui/imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <sstream>

struct VertexData {
    struct {
        float x, y;
    } position;
    struct {
        float x, y;
    } textCoords;
};

static const VertexData vertexData[] = {
    // centre the object around (0,0,0)
    {{-50.0f, -50.0f}, {0.0f, 0.0f}}, // 0 (bottom left)
    {{ 50.0f, -50.0f}, {1.0f, 0.0f}}, // 1 (bottom right)
    {{ 50.0f,  50.0f}, {1.0f, 1.0f}}, // 2 (top right)
    {{-50.0f,  50.0f}, {0.0f, 1.0f}}, // 3 (top left)
};

static unsigned int indices[] = {
    0, 1, 2, 
    2, 3, 0, 
};

namespace test
{

TestDoge::TestDoge(unsigned int width, unsigned int height)
    : m_Width(width), m_Height(height),
      m_Texture("resources/textures/doge.png"),
      m_Shader("resources/shaders/basicShader.glsl"),
      m_ViewTranslation(0.0f),
      m_ModelTranslations(),
      m_VertexBuffer(vertexData, sizeof(vertexData)),
      m_IndexBuffer(indices, 6),
      m_Projection(glm::ortho(0.0f, (float)width, 0.0f, (float)height, -1.0f, 1.0f)),
      u_MVP(std::make_shared<UniformMat4f>(glm::mat4(1.0f))),
      u_Rainbow(std::make_shared<UniformRainbow>()),
      u_Texture(std::make_shared<Uniform1<int>>(0))
{
    // set buffer layout
    m_VertexBufferLayout.Push<float>(2);
    m_VertexBufferLayout.Push<float>(2);
    m_VertexArray.AddBuffer(m_VertexBuffer, m_VertexBufferLayout);
    // set m_Shader uniforms
    m_Shader.AddUniform("u_Color", u_Rainbow);
    m_Shader.AddUniform("u_MVP", u_MVP);
    // set texture
    m_Texture.Bind(0);
    m_Shader.SetUniform("u_Texture", u_Texture);
}

TestDoge::~TestDoge()
{

}

void TestDoge::OnUpdate(float deltaTime)
{
    u_Rainbow->Update();
}

void TestDoge::OnRender()
{
    glm::mat4 view = glm::translate(glm::mat4(1.0f), m_ViewTranslation);
    for (const auto& modelTranslation: m_ModelTranslations)
    {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), modelTranslation);    
        u_MVP->Update(m_Projection * view * model);
        m_Renderer.Draw(m_VertexArray, m_IndexBuffer, m_Shader);
    }
}

void TestDoge::OnImGuiRender()
{
    ImGui::SliderFloat2("View translation", m_ViewTranslation.components, -(float)m_Width, (float)m_Width);
    for (unsigned int i = 0; i < m_ModelTranslations.size(); i++)
    {
        auto& modelTranslation = m_ModelTranslations.at(i);
        std::stringstream description;
        description << "Doge " << i << " translation";
        ImGui::SliderFloat2(description.str().c_str(), modelTranslation.components, -(float)m_Width, (float)m_Width);
    }
}

}
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
      texture("resources/textures/doge.png"),
      shader("resources/shaders/basicShader.glsl"),
      viewTranslation(0.0f),
      modelTranslations(),
      vertexBuffer(vertexData, sizeof(vertexData)),
      indexBuffer(indices, 6),
      projection(glm::ortho(0.0f, (float)width, 0.0f, (float)height, -1.0f, 1.0f)),
      u_MVP(std::make_shared<UniformMat4f>(glm::mat4(1.0f))),
      u_Rainbow(std::make_shared<UniformRainbow>()),
      u_Texture(std::make_shared<Uniform1<int>>(0))
{
    // set buffer layout
    vertexBufferLayout.Push<float>(2);
    vertexBufferLayout.Push<float>(2);
    vertexArray.AddBuffer(vertexBuffer, vertexBufferLayout);
    // set shader uniforms
    shader.AddUniform("u_Color", u_Rainbow);
    shader.AddUniform("u_MVP", u_MVP);
    // set texture
    texture.Bind(0);
    shader.SetUniform("u_Texture", u_Texture);
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
    glm::mat4 view = glm::translate(glm::mat4(1.0f), viewTranslation);
    for (const auto& modelTranslation: modelTranslations)
    {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), modelTranslation);    
        u_MVP->Update(projection * view * model);
        renderer.Draw(vertexArray, indexBuffer, shader);
    }
}

void TestDoge::OnImGuiRender()
{
    ImGui::SliderFloat2("View translation", viewTranslation.components, -(float)m_Width, (float)m_Width);
    for (unsigned int i = 0; i < modelTranslations.size(); i++)
    {
        auto& modelTranslation = modelTranslations.at(i);
        std::stringstream description;
        description << "Doge " << i << " translation";
        ImGui::SliderFloat2(description.str().c_str(), modelTranslation.components, -(float)m_Width, (float)m_Width);
    }
}

}
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
      texture(filepath),
      shader("resources/shaders/textureTest.glsl"),
      u_Texture(std::make_shared<Uniform1<int>>(0)),
      u_MVP(std::make_shared<UniformMat4f>(glm::mat4(1.0f))),
      translation(0.0f), rotation(0.0f, 0.0f, 1.0f), scale(1.0f),
      vertexBuffer(vertexData, sizeof(vertexData)),
      indexBuffer(indices, 6) 
{
    // set layout
    vertexBufferLayout.Push<float>(2);
    vertexBufferLayout.Push<float>(2);
    vertexArray.AddBuffer(vertexBuffer, vertexBufferLayout);
    // bind texture
    texture.Bind(0);
    shader.AddUniform("u_Texture", u_Texture);
    shader.AddUniform("u_MVP", u_MVP);
}

TestTexture::~TestTexture()
{

}

void TestTexture::OnRender()
{
    glm::mat4 model = glm::scale(glm::mat4(1.0f), scale);
    model = glm::translate(model, translation);
    model = glm::rotate(model, (float)m_Angle, rotation);
    u_MVP->Update(model);
    renderer.Draw(vertexArray, indexBuffer, shader);
}

void TestTexture::OnImGuiRender()
{
    ImGui::SliderFloat3("Translation", translation.components, 0, 1.0f);
    ImGui::SliderFloat3("Rotation", rotation.components, 0, 1.0f);
    ImGui::SliderFloat3("Scale", scale.components, 0, 1.0f);
    ImGui::SliderAngle("Angle", &m_Angle, 0, 360);
}

}
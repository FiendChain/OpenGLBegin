#include "TestCube.hpp"
#include "VertexBufferLayout.hpp"
#include "OpenGL.hpp"
#include <imgui/imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

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
    : m_Width(width), m_Height(height),
      m_Shader("resources/shaders/cubeTest.glsl"),
      m_VertexBuffer(vertexData, sizeof(vertexData)),
      m_IndexBuffer(indices, 3*2*6), // 3 indices, 2 triangles per face, 6 faces
      m_ModelTranslation(0.0f), m_ModelRotation(0.0f, 1.0f, 1.0f), 
      m_ModelScale(1.0f), m_ModelAngle(0.0f),
      m_ViewTranslation(10.0f, 10.0f, 0.0f), m_ViewRotation(0.0f, 1.0f, 0.0f), 
      m_ViewPosition(0.0f),
      m_FOV(45.0f),
      u_MVP(std::make_shared<UniformMat4f>(glm::mat4(1.0f)))
{
    VertexBufferLayout vertexBufferLayout;
    vertexBufferLayout.Push<float>(3);
    vertexBufferLayout.Push<float>(3, GL_FALSE);
    m_VertexArray.AddBuffer(m_VertexBuffer, vertexBufferLayout);
    m_Shader.AddUniform("u_MVP", u_MVP);
}

void TestCube::OnRender()
{
    static float aspectRatio = (float)m_Width/(float)m_Height;
    // projection frustrum matrix
    glm::mat4 projection = glm::perspective(
        (float)glm::radians(m_FOV),
        aspectRatio,
        0.01f,              // Near clipping plane
        1000.0f             // Far clipping plane
    );
    // camera matrix
    glm::mat4 view = glm::lookAt(
        m_ViewTranslation, // Camera is at (4,3,3), in World Space
        m_ViewPosition, // and looks at the origin
        m_ViewRotation  // Head is up (set to 0,-1,0 to look upside-down)
    );
    // model matrix
    glm::mat4 model = glm::scale(glm::mat4(1.0f), m_ModelScale);
    model = glm::translate(model, m_ModelTranslation);
    model = glm::rotate(model, (float)m_ModelAngle, m_ModelRotation);
    // set MVP matrix
    u_MVP->Update(projection*view*model);
    m_Renderer.Draw(m_VertexArray, m_IndexBuffer, m_Shader);
}

void TestCube::OnImGuiRender()
{
    ImGuiRenderModelControls();
    ImGuiRenderViewControls();
    ImGuiRenderProjectionControls();
}

void TestCube::ImGuiRenderModelControls()
{
    ImGui::PushID(0);
    ImGui::Text("Model");
    ImGui::SliderFloat3("Translation", &m_ModelTranslation.x, 0, 1.0f);
    ImGui::SliderFloat3("Rotation", &m_ModelRotation.x, 0, 1.0f);
    ImGui::SliderFloat3("Scale", &m_ModelScale.x, 0, 1.0f);
    ImGui::SliderAngle("Angle", &m_ModelAngle, 0, 360);
    ImGui::PopID();
}

void TestCube::ImGuiRenderViewControls()
{
    static float x = 20.0f;
    ImGui::PushID(1);
    ImGui::Text("View");
    ImGui::SliderFloat3("Translation", &m_ViewTranslation.x, -x, x);
    ImGui::SliderFloat3("Rotation", &m_ViewRotation.x, -1.0f, 1.0f);
    ImGui::SliderFloat3("Position (aim)", &m_ViewPosition.x, -x, x);
    ImGui::SliderFloat("Max movements", &x, 0.0f, 100.0f);
    ImGui::PopID();
}

void TestCube::ImGuiRenderProjectionControls()
{
    ImGui::PushID(2);
    ImGui::Text("Projection");
    ImGui::SliderFloat("FOV", &m_FOV, 0, 90);
    ImGui::PopID();
}

}
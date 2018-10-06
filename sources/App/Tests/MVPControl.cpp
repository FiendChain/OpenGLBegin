#include "MVPControl.hpp"
#include <imgui/imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace test
{

MVPControl::MVPControl(unsigned int width, unsigned int height)
    : m_Width(width), m_Height(height), 
      m_AspectRatio((float)width/(float)height),
      m_ModelTranslation(0.0f), m_ModelRotation(0.0f, 1.0f, 1.0f), 
      m_ModelScale(1.0f), m_ModelAngle(0.0f),
      m_ViewTranslation(10.0f, 10.0f, 0.0f), m_ViewRotation(0.0f, 1.0f, 0.0f), 
      m_ViewPosition(0.0f),
      m_FOV(45.0f),
      m_MaxTranslate(10.0f),
      m_MVP(1.0f)
{

}

void MVPControl::OnUpdate()
{
    // projection frustrum matrix
    glm::mat4 projection = glm::perspective(
        (float)glm::radians(m_FOV),
        m_AspectRatio,
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
    m_MVP = projection * view * model;
}

void MVPControl::OnImGuiRender()
{
    ImGuiRenderModelControls();
    ImGuiRenderViewControls();
    ImGuiRenderProjectionControls();
}

void MVPControl::ImGuiRenderModelControls()
{
    ImGui::PushID(0);
    ImGui::Text("Model");
    ImGui::SliderFloat3("Translation", &m_ModelTranslation.x, 0, 1.0f);
    ImGui::SliderFloat3("Rotation", &m_ModelRotation.x, 0, 1.0f);
    ImGui::SliderFloat3("Scale", &m_ModelScale.x, 0, 1.0f);
    ImGui::SliderAngle("Angle", &m_ModelAngle, 0, 360);
    ImGui::PopID();
}

void MVPControl::ImGuiRenderViewControls()
{
    ImGui::PushID(1);
    ImGui::Text("View");
    ImGui::SliderFloat3("Translation", &m_ViewTranslation.x, -m_MaxTranslate, m_MaxTranslate);
    ImGui::SliderFloat3("Rotation", &m_ViewRotation.x, -1.0f, 1.0f);
    ImGui::SliderFloat3("Position (aim)", &m_ViewPosition.x, -m_MaxTranslate, m_MaxTranslate);
    ImGui::SliderFloat("Max movements", &m_MaxTranslate, 0.0f, 100.0f);
    ImGui::PopID();
}

void MVPControl::ImGuiRenderProjectionControls()
{
    ImGui::PushID(2);
    ImGui::Text("Projection");
    ImGui::SliderFloat("FOV", &m_FOV, 0, 90);
    ImGui::PopID();
}

}
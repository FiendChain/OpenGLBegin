#pragma once
// base class for test with camera
#include <glm/glm.hpp>
#include <memory>

namespace test
{

class MVPControl
{
    private:
        const unsigned int m_Width, m_Height;
        const float m_AspectRatio;
        glm::vec3 m_ModelTranslation, m_ModelRotation, m_ModelScale; // model
        float m_ModelAngle;
        glm::vec3 m_ViewTranslation, m_ViewRotation, m_ViewPosition; // view
        float m_FOV; // projection 
        glm::mat4 m_MVP;
        float m_MaxTranslate;
    public:
        MVPControl(unsigned int width, unsigned int height);
        void OnUpdate();
        void OnImGuiRender();
        inline const glm::mat4& GetMVP() const { return m_MVP; }
    private:
        void ImGuiRenderModelControls();
        void ImGuiRenderViewControls();
        void ImGuiRenderProjectionControls();


};
}
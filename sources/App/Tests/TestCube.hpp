#pragma once
#include "Test.hpp"
#include "Shader.hpp"
#include "IndexBuffer.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "VertexArray.hpp"
#include "Renderer.hpp"
#include "Uniform.hpp"

#include <glm/glm.hpp>
#include <memory>

namespace test
{
class TestCube: public Test
{
    private:
        float m_Width, m_Height;
        Shader m_Shader;
        VertexArray m_VertexArray;
        VertexBuffer m_VertexBuffer;
        IndexBuffer m_IndexBuffer;
        Renderer m_Renderer;
        std::shared_ptr<UniformMat4f> u_MVP; // mvp matrix
        glm::vec3 m_ModelTranslation, m_ModelRotation, m_ModelScale; // model
        float m_ModelAngle;
        glm::vec3 m_ViewTranslation, m_ViewRotation, m_ViewPosition; // view
        float m_FOV; // projection                                  
    public:
        TestCube(unsigned int width, unsigned int height);
        void OnRender() override;
        void OnImGuiRender() override;
    private:
        void ImGuiRenderModelControls();
        void ImGuiRenderViewControls();
        void ImGuiRenderProjectionControls();
};
}
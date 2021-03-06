#pragma once
#include "Test.hpp"
#include "MVPControl.hpp"

#include "Shader.hpp"
#include "IndexBuffer.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "VertexArray.hpp"
#include "Renderer.hpp"
#include "Uniform.hpp"

#include <memory>

namespace test
{
class TestCube: public Test
{
    private:
        const unsigned int m_Width, m_Height;
        Shader m_Shader;
        VertexArray m_VertexArray;
        VertexBuffer m_VertexBuffer;
        IndexBuffer m_IndexBuffer;
        Renderer m_Renderer;
        std::shared_ptr<UniformMat4f> u_MVP;                         
        MVPControl m_MVP_Control;
    public:
        TestCube(unsigned int width, unsigned int height);
        void OnRender() override;
        void OnUpdate(float deltaTime) override;
        void OnImGuiRender() override;
};
}
#pragma once
#include "Test.hpp"
#include "VertexArray.hpp"
#include "VertexBufferLayout.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"
#include "Uniform.hpp"
#include "Texture.hpp"
#include "Renderer.hpp"
#include <glm/glm.hpp>
#include <memory>
#include <array>

namespace test
{
class TestDoge: public Test
{
    private:
        Renderer m_Renderer;
        Shader m_Shader;
        Texture m_Texture;
        VertexArray m_VertexArray;
        VertexBuffer m_VertexBuffer;
        VertexBufferLayout m_VertexBufferLayout;
        IndexBuffer m_IndexBuffer;
        std::shared_ptr<UniformRainbow> u_Rainbow; // uniforms
        std::shared_ptr<UniformMat4f> u_MVP; 
        std::shared_ptr<Uniform1<int>> u_Texture;
        std::array<glm::vec3, 2> m_ModelTranslations; // MVP
        glm::vec3 m_ViewTranslation;
        const glm::mat4 m_Projection;
        const unsigned int m_Width, m_Height;
    public:
        TestDoge(unsigned int width, unsigned int height);
        ~TestDoge();
        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;
};
}
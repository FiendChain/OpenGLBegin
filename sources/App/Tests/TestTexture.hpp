#pragma once
#include "Test.hpp"
#include "Texture.hpp"
#include "Shader.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Uniform.hpp"
#include "Renderer.hpp"
#include <memory>
#include <glm/glm.hpp>

namespace test
{
class TestTexture: public Test
{
    private:
        std::string m_Filepath;
        Renderer m_Renderer;
        Texture m_Texture; // resources
        Shader m_Shader;
        VertexArray m_VertexArray; // buffers
        VertexBuffer m_VertexBuffer;
        VertexBufferLayout m_VertexBufferLayout;
        IndexBuffer m_IndexBuffer;
        std::shared_ptr<Uniform1<int>> u_Texture; // uniforms
        std::shared_ptr<UniformMat4f> u_MVP;
        glm::vec3 m_Rotation;
        glm::vec3 m_Translation;
        glm::vec3 m_Scale;
        float m_Angle;
    public:
        TestTexture(const std::string& filepath);
        ~TestTexture();
        void OnRender() override;
        void OnImGuiRender() override;
};
}
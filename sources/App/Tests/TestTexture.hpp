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
        const std::string& m_Filepath;
        Renderer renderer;
        Texture texture; // resources
        Shader shader;
        VertexArray vertexArray; // buffers
        VertexBuffer vertexBuffer;
        VertexBufferLayout vertexBufferLayout;
        IndexBuffer indexBuffer;
        std::shared_ptr<Uniform1<int>> u_Texture; // uniforms
        std::shared_ptr<UniformMat4f> u_MVP;
        glm::vec3 rotation;
        glm::vec3 translation;
        glm::vec3 scale;
        float m_Angle;
    public:
        TestTexture(const std::string& filepath);
        ~TestTexture();
        void OnRender() override;
        void OnImGuiRender() override;
};
}
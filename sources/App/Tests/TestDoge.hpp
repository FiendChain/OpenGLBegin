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
        Renderer renderer;
        Shader shader;
        Texture texture;
        VertexArray vertexArray;
        VertexBuffer vertexBuffer;
        VertexBufferLayout vertexBufferLayout;
        IndexBuffer indexBuffer;
        std::shared_ptr<UniformRainbow> u_Rainbow; // uniforms
        std::shared_ptr<UniformMat4f> u_MVP; 
        std::shared_ptr<Uniform1<int>> u_Texture;
        std::array<glm::vec3, 2> modelTranslations; // MVP
        glm::vec3 viewTranslation;
        const glm::mat4 projection;
        const unsigned int m_Width, m_Height;
    public:
        TestDoge(unsigned int width, unsigned int height);
        ~TestDoge();
        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;
};
}
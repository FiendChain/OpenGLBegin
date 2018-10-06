#pragma once
#include "Test.hpp"
#include "MVPControl.hpp"

#include "IndexBuffer.hpp"
#include "Renderer.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Uniform.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

#include <memory>
#include <string>

namespace test
{

class TestCubeTexture: public Test
{
    private:
        const unsigned int m_Width, m_Height;
        std::string m_Filepath;
        Shader m_Shader;
        Texture m_Texture;
        VertexArray m_VertexArray;
        VertexBuffer m_VertexBuffer;
        IndexBuffer m_IndexBuffer;
        Renderer m_Renderer;
        std::shared_ptr<UniformMat4f> u_MVP;
        std::shared_ptr<Uniform1<int>> u_Texture;
        MVPControl m_MVP_Control;
    public:
        TestCubeTexture(const std::string& filepath, unsigned int width, unsigned int height);
        void OnRender() override;
        void OnUpdate(float deltaTime) override;
        void OnImGuiRender() override;
};

}
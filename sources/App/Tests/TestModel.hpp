#pragma once
#include "Test.hpp"
#include "MVPControl.hpp"

#include "Renderer.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Uniform.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"

#include <string>
#include <memory>
#include <vector>

namespace test
{

class TestModel: public Test
{
    public:
        struct Position { float x, y, z; };
        struct TextCoord { float u, v; };
        struct Normal { float x, y, z; };
        struct VertexData {
            Position position;
            TextCoord textCoord;
            Normal normal;
        };
    private:
        const unsigned int m_Width, m_Height;
        std::string m_Filepath;
        std::string m_TexturePath;
        Shader m_Shader;
        std::unique_ptr<Texture> m_Texture;
        std::shared_ptr<UniformMat4f> u_MVP;
        std::shared_ptr<Uniform1<int>> u_Texture;
        Renderer m_Renderer;
        std::vector<VertexData> m_VertexData;       // data
        std::vector<unsigned int> m_Indices;
        VertexArray m_VertexArray;  // gl objects
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<IndexBuffer> m_IndexBuffer; 
        MVPControl m_MVP_Control;
    public:
        TestModel(const std::string& filepath, unsigned int width, unsigned int height);
        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;
    private:
        void ParseFile();
};

}
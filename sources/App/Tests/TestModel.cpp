#include "TestModel.hpp"
#include "VertexBufferLayout.hpp"
#include "Uniform.hpp"

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <stdio.h>
#include <stdlib.h>

#include <imgui/imgui.h>
#include <glm/glm.hpp>

namespace test
{

TestModel::TestModel(const std::string& filepath, unsigned int width, unsigned int height)
    : m_Width(width), m_Height(height),
      m_Filepath(filepath),
      m_Shader("resources/shaders/testModel.glsl"),
      u_MVP(std::make_shared<UniformMat4f>(glm::mat4(1.0f))),
      u_Texture(std::make_shared<Uniform1<int>>(0)),
      m_MVP_Control(width, height) 
{
    ParseFile();
    // set buffers
    m_VertexBuffer = std::make_unique<VertexBuffer>(&m_VertexData[0], sizeof(VertexData) * m_VertexData.size());
    m_IndexBuffer = std::make_unique<IndexBuffer>(&m_Indices[0], m_Indices.size());
    // set buffer layout
    VertexBufferLayout vertexBufferLayout;
    vertexBufferLayout.Push<float>(3);
    vertexBufferLayout.Push<float>(2);
    vertexBufferLayout.Push<float>(3);
    m_VertexArray.AddBuffer(*m_VertexBuffer.get(), vertexBufferLayout);
    // set texture
    m_Texture = std::make_unique<Texture>(m_TexturePath);
    m_Texture->Bind(0);
    // add bindings to shader
    m_Shader.AddUniform("u_MVP", u_MVP);
    m_Shader.AddUniform("u_Texture", u_Texture);
} 

void TestModel::OnUpdate(float deltaTime)
{
    m_MVP_Control.OnUpdate();
}

void TestModel::OnRender()
{
    u_MVP->Update(m_MVP_Control.GetMVP());
    m_Texture->Bind(0);
    m_Renderer.Draw(m_VertexArray, *m_IndexBuffer.get(), m_Shader);
}

void TestModel::OnImGuiRender()
{
    ImGui::Text("Rendering model %s", m_Filepath.c_str());
    ImGui::Text("Model texture %s", m_TexturePath.c_str());
    ImGui::Separator();
    m_MVP_Control.OnImGuiRender();
}

void TestModel::ParseFile()
{
    // temp vectors
    std::vector<Position> positions;
    std::vector<Normal> normals;
    std::vector<TextCoord> textCoords;
    // buffers
    std::ifstream filestream(m_Filepath);
    std::string buffer;
    // debug info
    unsigned int line = 0;
    bool textureDefined = false;
    while (getline(filestream, buffer))
    {
        line++;
        const char *cBuf = buffer.c_str();
        if (buffer.find("v ") != std::string::npos)
        {
            Position position;
            int args = sscanf(cBuf, "v %f %f %f", &position.x, &position.y, &position.z);
            if (args != 3)
            {
                std::stringstream sstream;
                sstream << "Invalid vertex position on line " << line; 
                throw sstream.str();
            }
                
            positions.push_back(position);
        }
        else if (buffer.find("vt ") != std::string::npos)
        {
            TextCoord textCoord;
            int args = sscanf(cBuf, "vt %f %f", &textCoord.u, &textCoord.v);
            if (args != 2)
            {
                std::stringstream sstream;
                sstream << "Invalid texture coordinate on line " << line; 
                throw sstream.str();
            }
            textCoords.push_back(textCoord);
        }
        else if (buffer.find("vn ") != std::string::npos)
        {
            Normal normal;
            int args = sscanf(cBuf, "vn %f %f %f", &normal.x, &normal.y, &normal.z);
            if (args != 3)
            {
                std::stringstream sstream;
                sstream << "Invalid normal on line " << line; 
                throw sstream.str();
            }
            normals.push_back(normal);
        }
        else if (buffer.find("f ") != std::string::npos)
        {
            int vPosition[3];
            int vTextCoord[3];
            int vNormal[3];
            int args = sscanf(cBuf, "f %d/%d/%d %d/%d/%d %d/%d/%d",
                                &vPosition[0], &vTextCoord[0], &vNormal[0],
                                &vPosition[1], &vTextCoord[1], &vNormal[1],
                                &vPosition[2], &vTextCoord[2], &vNormal[2]);
            if (args != 9)
            {
                std::stringstream sstream;
                sstream << "Invalid triangle definition on line " << line; 
                throw sstream.str();
            }
            for (unsigned int i = 0; i < 3; i++)
            {
                VertexData vertexData;
                vertexData.position = positions.at(vPosition[i]-1);
                vertexData.textCoord = textCoords.at(vTextCoord[i]-1);
                vertexData.normal = normals.at(vNormal[i]-1);
                m_VertexData.push_back(vertexData);
                m_Indices.push_back(m_Indices.size());
            }
        }
        else if (buffer.find("usemtl ") != std::string::npos)
        {
            m_TexturePath = buffer.substr(std::string("usemtl ").size());
            textureDefined = true;
        }
    }
    if (!textureDefined)
        throw std::string("Texture not defined!");
}

}
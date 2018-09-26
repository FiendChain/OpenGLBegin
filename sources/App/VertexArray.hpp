#pragma once
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp" 

class VertexArray
{
    public:
        VertexArray();
        ~VertexArray();
        void AddBuffer(const VertexBuffer& vertexBuffer,
                       const VertexBufferLayout& layout);
        void Bind() const;
        void Unbind() const;
    private:
        unsigned int m_RendererID;
};
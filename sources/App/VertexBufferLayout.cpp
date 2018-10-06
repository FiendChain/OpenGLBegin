#include "VertexBufferLayout.hpp"
#include "OpenGL.hpp"
#include <GL/glew.h>

VertexBufferLayout::VertexBufferLayout()
    : m_Stride(0)
{

}

VertexBufferLayout::~VertexBufferLayout()
{

}

template<>
void VertexBufferLayout::Push<float>(unsigned int count, GLboolean normalised)
{
    m_Elements.push_back({ GL_FLOAT, count, normalised });
    m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
}

template<>
void VertexBufferLayout::Push<unsigned int>(unsigned int count, GLboolean normalised)
{
    m_Elements.push_back({ GL_UNSIGNED_INT, count, normalised });
    m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
}

template<>
void VertexBufferLayout::Push<unsigned char>(unsigned int count, GLboolean normalised)
{
    m_Elements.push_back({ GL_UNSIGNED_BYTE, count, normalised });
    m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
}
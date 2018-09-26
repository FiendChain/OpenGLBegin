#pragma once
#include "Errors.hpp"
#include <vector>
#include <GL/glew.h>

struct VertexBufferElement
{
    unsigned int type;
    unsigned int count;
    unsigned char normalised;

    static unsigned int GetSizeOfType(unsigned int type)
    {
        switch (type) {
        case GL_FLOAT: return 4; //sizeof(GLfloat);
        case GL_UNSIGNED_INT: return 4; //sizeof(GLuint);
        case GL_UNSIGNED_BYTE: return 1; //sizeof(GLubyte);
        }
        ASSERT(false);
        return 0;
    }
};

class VertexBufferLayout
{
    public:
        VertexBufferLayout();
        ~VertexBufferLayout();
        template <typename T>
        void Push(unsigned int count) 
        {
            ASSERT(false);
        }
        inline const std::vector<VertexBufferElement>& GetElements() const { return m_Elements; };
        inline unsigned int GetStride() const { return m_Stride; };
    private:
        std::vector<VertexBufferElement> m_Elements;
        unsigned int m_Stride;
};

template<>
inline void VertexBufferLayout::Push<float>(unsigned int count)
{
    m_Elements.push_back({ GL_FLOAT, count, GL_TRUE });
    m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
}

template<>
inline void VertexBufferLayout::Push<unsigned int>(unsigned int count)
{
    m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_TRUE });
    m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
}

template<>
inline void VertexBufferLayout::Push<unsigned char>(unsigned int count)
{
    m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
    m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
}


#include "Errors.hpp"
#include "IndexBuffer.hpp"
#include "Renderer.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"
#include <GL/glew.h>

Renderer::Renderer()
    : m_ClearColour(0.0f, 0.0f, 0.0f, 1.0f)
{

}

void Renderer::Clear() const
{
    GLCall(glClearColor(m_ClearColour.r, m_ClearColour.g, m_ClearColour.b, m_ClearColour.a));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& vertexArray,
                    const IndexBuffer& indexBuffer,
                    const Shader& shader) const
{
    shader.Bind();
    vertexArray.Bind();
    indexBuffer.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, indexBuffer.GetCount(), GL_UNSIGNED_INT, nullptr));
}
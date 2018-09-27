#include "Errors.hpp"
#include "IndexBuffer.hpp"
#include "Renderer.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"
#include <GL/glew.h>

Renderer::Renderer()
{

}

void Renderer::Clear() const
{
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
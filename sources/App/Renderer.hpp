#pragma once
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"
#include "OpenGL.hpp"
#include <GL/glew.h>
#include <glm/glm.hpp>

class Renderer
{
    private:
        glm::vec4 m_ClearColour;
    public:
        Renderer();
        void Clear() const;
        void Draw(const VertexArray& vertexArray,
                  const IndexBuffer& indexBuffer,
                  const Shader& shader) const;
        inline void SetClearColour(glm::vec4 clearColour) { m_ClearColour = clearColour; }
        inline void SetClearColour(float r, float g, float b, float a=1.0f) {
            m_ClearColour.r = r;
            m_ClearColour.g = g;
            m_ClearColour.b = b;
            m_ClearColour.a = a;
        }
};
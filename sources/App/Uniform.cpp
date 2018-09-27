#include "Uniform.hpp"
#include "OpenGL.hpp"
#include "../RainbowColour/RainbowColour.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// rainbow
UniformRainbow::UniformRainbow()
    : rainbow()
{

}

void UniformRainbow::Apply(int location) const
{
    GLCall(glUniform4f(location, rainbow.r, rainbow.g, rainbow.b, rainbow.a));
}

void UniformRainbow::Update()
{   
    rainbow.update();
}

// mat4f
UniformMat4f::UniformMat4f(glm::mat4 matrix)
    : m_Matrix(matrix)
{

}

void UniformMat4f::Apply(int location) const
{
    GLCall(glUniformMatrix4fv(location, 1, GL_FALSE, &m_Matrix[0][0]));
}






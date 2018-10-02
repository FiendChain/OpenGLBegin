#include "Uniform.hpp"
#include "OpenGL.hpp"
#include "RainbowColour/RainbowColour.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// vec4 
template <typename T>
Uniform4<T>::Uniform4(T v0, T v1, T v2, T v3) 
{   
    m_Data[0] = v0;
    m_Data[1] = v1;
    m_Data[2] = v2;
    m_Data[3] = v3;
}

template Uniform4<float>::Uniform4(float, float, float, float);
template <>
void Uniform4<float>::Apply(int location) const
{
    GLCall(glUniform4f(location, m_Data[0], m_Data[1], m_Data[2], m_Data[3])); 
}

template Uniform4<int>::Uniform4(int, int, int, int);
template <>
void Uniform4<int>::Apply(int location) const
{
    GLCall(glUniform4i(location, m_Data[0], m_Data[1], m_Data[2], m_Data[3])); 
}

// vec1
template <typename T>
Uniform1<T>::Uniform1(T value)
    : m_Value(value)
{}

template Uniform1<int>::Uniform1(int);
template <>
void Uniform1<int>::Apply(int location) const
{
    GLCall(glUniform1i(location, m_Value));
}

// rainbow
UniformRainbow::UniformRainbow()
    : rainbow()
{

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

void UniformMat4f::Update(glm::mat4 matrix)
{
    m_Matrix = matrix;
}

// rainbow
void UniformRainbow::Apply(int location) const
{
    GLCall(glUniform4f(location, rainbow.r, rainbow.g, rainbow.b, rainbow.a));
}

void UniformRainbow::Update()
{   
    rainbow.update();
}








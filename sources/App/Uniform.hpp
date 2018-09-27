#pragma once
#include <vector>
#include "OpenGL.hpp"
#include "../RainbowColour/RainbowColour.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Uniform
{
    public:
        virtual void Apply(int location) const = 0;
};


class UniformRainbow: public Uniform
{
    private:
        RainbowColour rainbow;
    public:
        UniformRainbow();
        void Apply(int location) const;
        void Update();
};

class UniformMat4f: public Uniform
{
    private:
        glm::mat4 m_Matrix;
    public:
        UniformMat4f(glm::mat4 matrix);
        void Apply(int location) const;
};

template <typename T>
class Uniform4: public Uniform
{
    private:
        T m_Data[4];
    public:
        Uniform4(T v0, T v1, T v2, T v3);
        void Apply(int location) const;
};

template <typename T>
inline Uniform4<T>::Uniform4(T v0, T v1, T v2, T v3) 
{   
    m_Data[0] = v0;
    m_Data[1] = v1;
    m_Data[2] = v2;
    m_Data[3] = v3;
}

// vec4 types
template <>
inline void Uniform4<float>::Apply(int location) const
{
    GLCall(glUniform4f(location, m_Data[0], m_Data[1], m_Data[2], m_Data[3])); 
}

template <>
inline void Uniform4<int>::Apply(int location) const
{
    GLCall(glUniform4i(location, m_Data[0], m_Data[1], m_Data[2], m_Data[3])); 
}

template <typename T>
class Uniform1: public Uniform
{
    private:
        T m_Value;
    public:
        Uniform1(T value);
        void Apply(int location) const;
};

template <typename T>
inline Uniform1<T>::Uniform1(T value)
    : m_Value(value)
{}

template <>
inline void Uniform1<int>::Apply(int location) const
{
    GLCall(glUniform1i(location, m_Value));
}

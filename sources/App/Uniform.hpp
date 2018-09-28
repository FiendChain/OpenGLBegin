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
        void Update(glm::mat4 matrix);
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
class Uniform1: public Uniform
{
    private:
        T m_Value;
    public:
        Uniform1(T value);
        void Apply(int location) const;
};



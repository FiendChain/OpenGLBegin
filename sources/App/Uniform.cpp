#include "Uniform.hpp"
#include "OpenGL.hpp"
#include "../RainbowColour/RainbowColour.hpp"

// auto updating vec4 with rainbows
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






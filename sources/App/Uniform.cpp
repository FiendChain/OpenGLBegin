#include "Uniform.hpp"
#include "Errors.hpp"
#include "../RainbowColour/RainbowColour.hpp"
#include <GL/glew.h>

UniformRainbow::UniformRainbow(const RainbowColour& rainbow_)
    : rainbow(rainbow_)
{

}

void UniformRainbow::Apply(int location) const
{
    GLCall(glUniform4f(location, rainbow.r, rainbow.g, rainbow.b, rainbow.a));
}
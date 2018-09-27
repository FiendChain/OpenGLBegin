#include "Uniform.hpp"
#include "Errors.hpp"
#include "../RainbowColour/RainbowColour.hpp"
#include <GL/glew.h>

UniformRainbow::UniformRainbow()
    : rainbow()
{

}

void UniformRainbow::Apply(int location)
{
    GLCall(glUniform4f(location, rainbow.r, rainbow.g, rainbow.b, rainbow.a));
    rainbow.update();
}
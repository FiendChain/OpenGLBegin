#pragma once
#include <vector>
#include "../RainbowColour/RainbowColour.hpp"

class Uniform
{
    public:
        virtual void Apply(int location) = 0;
};


class UniformRainbow: public Uniform
{
    public:
        UniformRainbow();
        void Apply(int location);
    private:
        RainbowColour rainbow;
};


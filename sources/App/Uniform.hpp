#pragma once
#include <vector>
#include "../RainbowColour/RainbowColour.hpp"

class Uniform
{
    public:
        virtual void Apply(int location) const = 0;
};


class UniformRainbow: public Uniform
{
    public:
        UniformRainbow(const RainbowColour& rainbow_);
        void Apply(int location) const;
    private:
        const RainbowColour& rainbow;
};


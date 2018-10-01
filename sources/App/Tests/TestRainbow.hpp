#pragma once
#include "Test.hpp"
#include "RainbowColour/RainbowColour.hpp"
namespace test
{
class TestRainbow: public Test
{
    private:
        RainbowColour m_Rainbow;
    public:
        TestRainbow();
        ~TestRainbow();
        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;
};
}
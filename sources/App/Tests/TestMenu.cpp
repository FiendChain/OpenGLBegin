#include "TestMenu.hpp"
#include "TestClearColour.hpp"
#include "TestDoge.hpp"
#include "TestTexture.hpp"
#include "TestRainbow.hpp"
#include <imgui/imgui.h>
#include <memory>
#include <bits/move.h>

namespace test
{

TestMenu::TestMenu() 
{
    
}

TestMenu::~TestMenu()
{

}

void TestMenu::OnUpdate(float deltaTime)
{
    for (auto& testEntry: m_TestList)
    {
        if (testEntry.second.enabled) 
        {
            std::unique_ptr<Test>& test = testEntry.second.test;
            test->OnUpdate(deltaTime);
        }
    }
}

void TestMenu::OnRender()
{
    for (auto& testEntry: m_TestList)
    {
        if (testEntry.second.enabled) 
        {
            std::unique_ptr<Test>& test = testEntry.second.test;
            test->OnRender();
        }
    }
}

void TestMenu::OnImGuiRender()
{   
    DrawTestMenu();
    DrawActiveTests();   
}

void TestMenu::DrawTestMenu()
{
    ImGui::Begin("Test menu");
    for (auto& test: m_TestList)
    {
        ImGui::Checkbox(test.first.c_str(), &test.second.enabled);
    }
    ImGui::End();
}

void TestMenu::DrawActiveTests()
{
    for (auto& testEntry: m_TestList)
    {
        if (testEntry.second.enabled) 
        {
            std::unique_ptr<Test>& test = testEntry.second.test;
            ImGui::Begin(testEntry.first.c_str(), &testEntry.second.enabled);
            test->OnImGuiRender();
            ImGui::End();
        }
    }
}

}
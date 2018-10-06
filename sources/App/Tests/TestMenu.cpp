#include "TestMenu.hpp"
#include <imgui/imgui.h>
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
        if (testEntry.enabled) 
        {
            testEntry.test->OnUpdate(deltaTime);
        }
    }
}

void TestMenu::OnRender()
{
    for (auto& testEntry: m_TestList)
    {
        if (testEntry.enabled) 
        {
            testEntry.test->OnRender();
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
        ImGui::Checkbox(test.name.c_str(), &test.enabled);
    }
    ImGui::End();
}

void TestMenu::DrawActiveTests()
{
    for (auto& testEntry: m_TestList)
    {
        if (testEntry.enabled) 
        {
            ImGui::Begin(testEntry.name.c_str(), &testEntry.enabled);
            testEntry.test->OnImGuiRender();
            ImGui::End();
        }
    }
}

}
#pragma once
#include "Test.hpp"
#include <type_traits>
#include <vector>
#include <memory>

namespace test
{


class TestMenu: public Test
{
    public:
        struct TestEntry
        {
            std::string name;
            std::unique_ptr<Test> test;
            bool enabled;
        };
    private:
        std::vector<TestEntry> m_TestList;
    public:
        TestMenu();
        ~TestMenu();
        template <typename T, typename... Args>
        void AddTest(const std::string& name, Args&& ... args)
        {
            static_assert(std::is_base_of<Test, T>::value, "Not derived from Test");
            m_TestList.push_back((TestEntry){name, std::make_unique<T>(std::forward<Args>(args)...), false});
        }
        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;
    private:
        void DrawTestMenu();
        void DrawActiveTests();
};
}
#pragma once
#include "Test.hpp"
#include <unordered_map>
#include <type_traits>
#include <memory>

namespace test
{


class TestMenu: public Test
{
    public:
        struct TestEntry
        {
            std::unique_ptr<Test> test;
            bool enabled;
        };
    private:
        std::unordered_map<std::string, TestEntry> m_TestList;
    public:
        TestMenu();
        ~TestMenu();
        template <typename T, typename... Args>
        void AddTest(const std::string& name, Args&& ... args)
        {
            static_assert(std::is_base_of<Test, T>::value, "Not derived from Test");
            m_TestList.insert(std::make_pair(name, (TestEntry){std::make_unique<T>(std::forward<Args>(args)...), false}));
        }
        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;
    private:
        void DrawTestMenu();
        void DrawActiveTests();
};
}
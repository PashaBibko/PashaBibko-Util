#pragma once

#include <vector>

#include <core/Log.h>

namespace PashaBibko::Util::Testing
{
    struct TestReturnVal
    {
        virtual bool Passed() { return false; }
    };

    struct TestPassed : public TestReturnVal
    {
        virtual bool Passed() override { return true; }
    };

    struct UnitTest
    {
        UnitTest(const char* testGroup, const char* testName, const char* filename)
            : name(testName)
        {}

        virtual TestReturnVal* TestBody()
        {
            return nullptr;
        }

        const std::string name;
    };

    class UnitTestGroup
    {
        public:
            UnitTestGroup(const char* name);

            void RegisterTest(UnitTest* _test)
            {
                m_Tests.push_back(_test);
            }

            friend void ExecuteAllTests();

        private:
            void ExecuteBatch()
            {
                bool batchPassed = true;

                for (UnitTest* test : m_Tests)
                {
                    TestReturnVal* result = test->TestBody();

                    /* Handles passing / failing of the test */
                    if (result->Passed())
                        Util::Print<Util::Colour::LightGreen>("[ Passed ] ");
                    else
                        Util::Print<Util::Colour::LightRed>("[ Failed ] ");

                    Util::PrintLn(test->name);

                    batchPassed = batchPassed && result->Passed();
                }
            }

            std::vector<UnitTest*> m_Tests;
            std::string m_Name;
    };

    void ExecuteAllTests();
}

#define PB_TEST_GROUP(name) ::PashaBibko::Util::Testing::UnitTestGroup name(#name)

#define PB_TEST(group, name) \
    struct name final : public ::PashaBibko::Util::Testing::UnitTest { \
        name(::PashaBibko::Util::Testing::UnitTestGroup& _group) : UnitTest(#group, #name, __FILE__) { \
            _group.RegisterTest(this); \
        } \
        ::PashaBibko::Util::Testing::TestReturnVal* TestBody() override; \
    }; \
    name test_instance##name(group);\
    ::PashaBibko::Util::Testing::TestReturnVal* name::TestBody()

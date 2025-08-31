#pragma once

#include <vector>

#include <core/Log.h>

/* Classes used by the macros, should not be accesed by the user */
namespace PashaBibko::Util::Testing
{
    /* Base class of all errors that can occur in a test */
    struct TestError {};

    /* Error when values are not equal when they should be */
    struct NotEqualError : public TestError {};

    /* Base class of every unit test, constructor is auto filled and user defines the contents of the Dispatch() function */
    struct UnitTest
    {
        UnitTest(const char* testGroup, const char* testName, const char* filename)
            : group(testGroup), name(testName)
        {}

        virtual void Dispatch(std::vector<TestError*>& errors) {}

        const std::string group;
        const std::string name;
    };

    /* Class to hold a selection of related unit tests and run them together */
    class UnitTestGroup final
    {
        public:
            UnitTestGroup(const char* name);

            void RegisterTest(UnitTest* _test)
            {
                m_Tests.push_back(_test);
            }

            friend void ExecuteAllTests();

        private:
            void ExecuteBatch(std::vector<UnitTest*>& failures)
            {
                /* Runs the tests and counts all the failures */
                size_t testsFailed = 0;
                for (UnitTest* test : m_Tests)
                {
                    /* Runs the test and captures all the errors */
                    std::vector<TestError*> errors;
                    test->Dispatch(errors);

                    if (errors.size() == 0)
                    {
                        /* Prints the sucess to the console */
                        Util::Print<Util::Colour::LightGreen>("[ Passed ] ");
                        Util::Print(test->name, Util::NewLine);
                    }

                    else
                    {
                        /* Prints the failure to the console */
                        Util::Print<Util::Colour::LightRed>("[ Failed ] ");
                        Util::Print(test->name, Util::NewLine);

                        /* TODO: Print error in the console from the test */

                        /* Registers the test as a failure */
                        failures.push_back(test);
                        testsFailed++;
                    }
                }

                /* Displays a summary to the console */
                if (testsFailed == 0)
                {
                    Util::Print<Util::Colour::LightGreen>("[ ------ ] ");
                    Util::Print<Util::Colour::Green>("All tests in ", m_Name, " group passed.", Util::NewLine);
                }

                else
                {
                    Util::Print<Util::Colour::Yellow>("[ ------ ] ");
                    
                    if (m_Tests.size() != 1)
                        Util::Print<Util::Colour::Yellow>(testsFailed, " out of ", m_Tests.size(), " tests failed.", Util::NewLine);

                    else
                        Util::Print<Util::Colour::Yellow>("1 out of 1 test failed.", Util::NewLine);
                }
            }

            std::vector<UnitTest*> m_Tests;
            std::string m_Name;
    };

    void ExecuteAllTests();
}

/* Defines a group of unit tests, each test is required to be a part of a group */
#define PB_TEST_GROUP(name) ::PashaBibko::Util::Testing::UnitTestGroup name(#name)

/* Declares a unit test belogining to a certain group */
#define PB_TEST(group, name) \
    struct name final : public ::PashaBibko::Util::Testing::UnitTest { \
        name(::PashaBibko::Util::Testing::UnitTestGroup& _group) : UnitTest(#group, #name, __FILE__) { \
            _group.RegisterTest(this); \
        } \
        void Dispatch(std::vector<::PashaBibko::Util::Testing::TestError*>& errors) override; \
    }; \
    name test_instance##name(group);\
    void name::Dispatch(std::vector<::PashaBibko::Util::Testing::TestError*>& errors)

/* Checks two values are equal within a PB_TEST */
#define PB_EXPECT_EQL(lhs, rhs) if (lhs != rhs) errors.push_back(new ::PashaBibko::Util::Testing::NotEqualError);

/* Helpers for checking values of booleans */

#define PB_EXPECT_FALSE(val) PB_EXPECT_EQL(val, false)
#define PB_EXPECT_TRUE(val) PB_EXPECT_EQL(val, true)

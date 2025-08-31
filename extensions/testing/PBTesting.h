#pragma once

#include <vector>
#include <string>

#include <extensions/testing/PBTestErrors.h>

/* Classes used by the macros, should not be accesed by the user */
namespace PashaBibko::Util::Testing
{
    /* Base class of every unit test, constructor is auto filled and user defines the contents of the Dispatch() function */
    struct UnitTest
    {
        UnitTest(const char* testGroup, const char* testName, const char* filename);
        virtual void Dispatch(std::vector<TestError*>& errors) = 0;

        const std::string group;
        const std::string name;
    };

    /* Holds a selection of related unit tests and run them together */
    class UnitTestGroup final
    {
        public:
            UnitTestGroup(const char* name, const std::vector<UnitTestGroup*>& deps);

            inline void RegisterTest(UnitTest* _test) { m_Tests.push_back(_test); }
            inline operator UnitTestGroup*() { return this; }

        private:
            friend int ExecuteAllTests();

            void ExecuteBatch(std::vector<UnitTest*>& failures);

            std::vector<UnitTestGroup*> m_GroupDependencies;
            std::vector<UnitTest*> m_Tests;
            std::string m_Name;
    };

    int ExecuteAllTests();
}

/* Defines a group of unit tests, each test is required to be a part of a group */
#define PB_TEST_GROUP(name, ...) \
::PashaBibko::Util::Testing::UnitTestGroup name(#name, std::vector<::PashaBibko::Util::Testing::UnitTestGroup*>{ __VA_ARGS__ } )

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

/* Internal macros */
#define _PB_INTERNAL_LOCATION __FILE__, __LINE__
#define _PB_INTERNAL_EXPAND_PARAM(param) #param, param

/* Checks two values are equal within a PB_TEST */
#define PB_EXPECT_EQL(lhs, rhs) if (lhs != rhs) \
errors.push_back(new ::PashaBibko::Util::Testing::NotEqualError( \
_PB_INTERNAL_EXPAND_PARAM(lhs), _PB_INTERNAL_EXPAND_PARAM(rhs), _PB_INTERNAL_LOCATION));

/* Helpers for checking values of booleans */

#define PB_EXPECT_FALSE(val) PB_EXPECT_EQL(val, false)
#define PB_EXPECT_TRUE(val) PB_EXPECT_EQL(val, true)

#pragma once

#include <vector>

#include <core/Log.h>

namespace PashaBibko::Util::Testing
{
    struct UnitTest
    {
        UnitTest(const char* testGroup, const char* testName, const char* filename) {}

        virtual void TestBody() {}
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
                for (UnitTest* test : m_Tests)
                    test->TestBody();
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
        void TestBody() override; \
    }; \
    name name_instance(group);\
    void name::TestBody()

#pragma once

#include <vector>

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
            void RegisterTest(UnitTest* _test)
            {
                m_Tests.push_back(_test);
            }

        private:
            std::vector<UnitTest*> m_Tests;
    };
}

#define PB_TEST_GROUP ::PashaBibko::Util::Testing::UnitTestGroup

#define PB_TEST(group, name) \
    struct name final : public ::PashaBibko::Util::Testing::UnitTest { \
        name(::PashaBibko::Util::Testing::UnitTestGroup& _group) : UnitTest(#group, #name, __FILE__) { \
            _group.RegisterTest(this); \
        } \
        void TestBody() override; \
    }; \
    name name_instance(group);\
    void name::TestBody()

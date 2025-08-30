#pragma once

namespace PashaBibko::Util::Testing
{
    struct UnitTest
    {
        UnitTest(const char* testGroup, const char* testName, const char* filename) {}
    };
}

#define PB_TEST(group, name) \
    struct name final : public ::PashaBibko::Util::Testing::UnitTest { \
        name() : UnitTest(#group, #name, __FILE__) { TestBody(); } \
        void TestBody(); \
    }; \
    ##name  name_instance;\
    void name::TestBody()

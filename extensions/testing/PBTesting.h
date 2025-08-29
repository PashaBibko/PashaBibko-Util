#pragma once

namespace PashaBibko::Util::Testing
{
    struct UnitTest
    {
        UnitTest(const char* testGroup, const char* testName, const char* filename) {}
    };
}

#define PB_TEST_IMPL(fulltestname, group, name, file) \
    struct _PBUTIL_TEST_##fulltestname final : public ::PashaBibko::Util::Testing::UnitTest { \
        _PBUTIL_TEST_##fulltestname() : UnitTest(#group, #name, file) { TestBody(); } \
        void TestBody(); \
    }; \
    _PBUTIL_TEST_##fulltestname  fulltestname_instance; \
    void _PBUTIL_TEST_##fulltestname::TestBody()


#define PB_TEST(group, name) PB_TEST_IMPL(group_##name, group, name, __FILE__)

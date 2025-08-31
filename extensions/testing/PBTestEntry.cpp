#include <Util.h>

/* Only defines main function if ENABLE_TESTING has been defined */
#if defined(PB_TESTS_ENABLED) || defined(PB_UTIL_VSC_DEV)

int main()
{
    int ec = PashaBibko::Util::Testing::ExecuteAllTests();

    return ec;
}

#endif

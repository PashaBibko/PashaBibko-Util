# Adds a C-Macro to the compiler so it can include the correct files in Util.h #
target_compile_definitions(PashaBibko-UTIL PUBLIC _PBUTIL_TEST_EXTENSION_ENABLED)

# Adds the C++ source files of the extension to the Util binary #
target_sources(PashaBibko-UTIL PRIVATE
    "PBTesting.cpp"
)

#include <extensions/python/CTPython.h>

#include <core/Log.h>

#if defined(_WIN32) || defined(_WIN64)
    #ifndef NOMINMAX // Defined by GCC
    #define NOMINMAX
    #endif // NOMINMAX
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
#else
    #error "Support for non-windows operating systems for this version has not been implemented yet"
#endif

namespace PashaBibko::Util::CTG
{
    static bool AreValuesLoaded()
    {
        HMODULE hModule = GetModuleHandleW(L"PB-UTIL-CTG-PYTHON-VALUES.dll");
        return hModule;
    }

    void InitialisePythonCTG()
    {
        /* Checks if it is the first initalisation */
        static bool initalised = false;
        if (initalised == true)
        {
            Util::Log("[CTG::InitalisePythonCTG]: Function has been called after initalisation");
            return;
        }

        /* Either the code results have already been generated or they need to be generated */
        if (AreValuesLoaded())
        {
            Util::Log("[CTG::InitalisePythonCTG]: Values are loaded");
            return;
        }

        /* Else it is the first run after the compile so the values need to be loaded */
        std::vector<const char*>& pycode = GetCodeStorage();
        for (const auto& snippet : pycode)
        {
            Util::Log("[CTG::InitalisePythonCTG]: Compiling python code: ", std::string(snippet));
        }
    }
}

#include <extensions/python/CTPython.h>

#include <core/Misc.h>
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

    /* Helper typedef to extract the RunPythonSnippet function from the DLL */
    typedef const char* (*RunPythonSnippet)(const char*, const char*);

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

        /* Attaches the DLL to the process (automatically unloaded) */
        HMODULE hDLL = LoadLibraryA("PashaBibko-UTIL-PythonCTG.dll");
        if (!hDLL)
        {
            Util::Log("ERROR[Failed to load PashaBibko-UTIL-PythonCTG.dll]");
            Util::EndProcess();
            return; // return is only here for intelisense
        }

        /* Loads the RunPythonSnippet function from the DLL */
        RunPythonSnippet run = (RunPythonSnippet)GetProcAddress(hDLL, "RunPythonSnippet");
        if (!run)
        {
            Util::Log("ERROR[Could not load RunPythonSnippet function from PashaBibko-UTIL-PythonCTG.dll]");
            Util::EndProcess();
            return; // return is only here for intelisense
        }

        /* Runs the RunPythonSnippet function on each of the code snippets */
        std::vector<PythonSnippet> snippets = GetCodeStorage();
        for (auto& snippet : snippets)
        {
            const char* errorMessage = run(snippet.resName, snippet.code);
            if (errorMessage != nullptr)
            {
                std::string errorMsg = errorMessage;
                Util::Log("Python ERROR[", errorMsg, "]");
                Util::EndProcess();
            }  
        }
    }
}

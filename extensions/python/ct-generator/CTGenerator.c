#include <CTGenerator.h>

/* Forces release version as MSVC has errors with debug headers */
#ifdef _DEBUG
    #undef _DEBUG
    #include <Python.h>
    #define _DEBUG
#else
    #include <Python.h>
#endif

/* Includes Operating system specific files */
#if defined(_WIN32) || defined(_WIN64)
    #ifndef NOMINMAX // Defined by GCC
    #define NOMINMAX
    #endif // NOMINMAX
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
#else
    #error "Support for non-windows operating systems for this version has not been implemented yet"
#endif

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID reserved)
{
    switch(reason)
    {
        case DLL_PROCESS_ATTACH:
            MessageBoxA(NULL, "DLL attached!", "Info", MB_OK);
            return;

        case DLL_PROCESS_DETACH:
            MessageBoxA(NULL, "DLL detached!", "Info", MB_OK);
            return;

        default:
            return;
    }
}

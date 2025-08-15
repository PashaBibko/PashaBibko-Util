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

/* C standard library */
#include <stdio.h>

/* [Windows only] function called when a DLL is loaded to an .exe */
static BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID reserved)
{
    switch(reason)
    {
        case DLL_PROCESS_ATTACH:
            Py_Initialize();
            return TRUE;

        case DLL_PROCESS_DETACH:
            Py_Finalize();
            return TRUE;

        default:
            return TRUE;
    }
}

/* Exported function to run python code from c-strings */
__declspec(dllexport) const char* RunPythonSnippet(const char* varName, const char* snippet)
{
    /* Fetches the dictionary from __main__ to store variables */
    PyObject* module = PyImport_AddModule("__main__");
    PyObject* global = PyModule_GetDict(module);

    /* Runs the python code */
    PyRun_String(snippet, Py_file_input, global, global);

    /* Retrives value of X */
    PyObject* xObj = PyDict_GetItemString(global, varName);
    long x = PyLong_AsLong(xObj);

    /* Displays it to the screen(temporary) */
    char str[20];
    sprintf(str, "%ld", x);

    MessageBoxA(NULL, str, "Info", MB_OK);

    return NULL;
}

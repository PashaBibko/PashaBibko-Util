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

/* Helper macro for validating a pointer */
#define VALIDATE_POINTER(ptr) if (ptr == NULL) { return "Internal: \"malloc failed to allocate\""; }

/* C standard library */
#include <stdio.h>

/* All saved values */
static PyObject* savedModule = NULL;
static PyObject* savedDict = NULL;

/* Function called on the DLL being attached */
static void DLL_Attach(void)
{
    /* Initialises the python interpreter */
    Py_Initialize();

    /* Creates the saved module */
    savedModule = PyImport_AddModule("saved");
    savedDict = PyModule_GetDict(savedModule);
}

/* Saves results to a cpp file */
__declspec(dllexport) void SaveResults(const char* file)
{
    if (!Py_IsInitialized())
        return;

    /* Loads the saved values into the gloval dictionary for access */
    PyObject* mainModule = PyImport_AddModule("__main__");
    PyObject* global = PyModule_GetDict(mainModule);

    PyObject* savedCopy = PyDict_Copy(savedDict);
    PyDict_SetItemString(global, "values", savedCopy);

    Py_DECREF(savedCopy);

    /* Loads the filepath into the dictionary so the python script knows where to write */
    PyObject* filepath = PyUnicode_FromString(file);
    PyDict_SetItemString(global, "filepath", filepath);
    Py_DECREF(filepath);

    PyRun_SimpleString("exec(open('../extensions/python/ct-generator/GenerateCppFile.py').read())");

    /* Finalize interpreter */
    Py_Finalize();
}

/* [Windows only] function called when a DLL is loaded to an .exe */
static BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID reserved)
{
    if (reason == DLL_PROCESS_ATTACH)
        DLL_Attach();

    return TRUE;
}

/* Exported function to run python code from c-strings */
__declspec(dllexport) const char* RunPythonSnippet(const char* varName, const char* snippet)
{
    /* Fetches the dictionary from __main__ to store variables */
    PyObject* module = PyImport_AddModule("__main__");
    PyObject* global = PyModule_GetDict(module);

    /* Runs the python code */
    PyRun_String(snippet, Py_file_input, global, global);

    /* Retrives the value object if it exists */
    PyObject* resultObj = PyDict_GetItemString(global, varName);
    if (resultObj == NULL)
    {
        char* errorPrefixMessage = "Could not find value of: ";
        size_t errorLen = strlen(errorPrefixMessage) + strlen(varName) + 1; // +1 for null terminator

        char* fullErrorMessage = malloc(errorLen);
        VALIDATE_POINTER(fullErrorMessage);

        strcpy(fullErrorMessage, errorPrefixMessage);
        strcat(fullErrorMessage, varName);

        return fullErrorMessage;
    }

    /* Adds the value to the saved dictionary */
    PyDict_SetItemString(savedDict, varName, resultObj);
    Py_INCREF(resultObj);

    /* Resets the global dictionary to stop contamination between snippets */
    PyDict_Clear(global);
    PyDict_SetItemString(global, "__builtins__", PyEval_GetBuiltins());

    return NULL;
}

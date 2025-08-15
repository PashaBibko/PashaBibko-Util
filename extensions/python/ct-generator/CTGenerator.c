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

/* Linked list node for integers */
typedef struct IntNode
{
    struct IntNode* next;
    long data;
} IntNode;

/* Linked list node for floats */
typedef struct FloatNode
{
    struct FloatNode* next;
    float data;
} FloatNode;

/* Linked list node for c-strings */
typedef struct CStringNode
{
    struct CStringNode* next;
    char* data;
} CStringNode;

/* Linked lists for tracking the values */

IntNode* intNodeRoot            = NULL; 
IntNode* intNodeTop             = NULL;

FloatNode* floatNodeRoot        = NULL;
FloatNode* floatNodeTop         = NULL;

CStringNode* stringNodeRoot     = NULL;
CStringNode* stringNodeTop      = NULL;

/* Function called on the DLL being attached */
static void DLL_Attach()
{
    /* Initialises the python interpreter */
    Py_Initialize();
}

/* Function called on the DLL being detached */
static void DLL_Detach()
{
    /* Deletes the python interpreter */
    Py_Finalize();
}

/* [Windows only] function called when a DLL is loaded to an .exe */
static BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID reserved)
{
    switch(reason)
    {
        case DLL_PROCESS_ATTACH:
            DLL_Attach();
            return TRUE;

        case DLL_PROCESS_DETACH:
            DLL_Detach();
            return TRUE;

        default:
            return TRUE;
    }
}

/* Handler for integer type */
static const char* StoreResultInt(PyObject* obj)
{
    /* Fetches the value out of the PyObject */
    long val = PyLong_AsLong(obj);

    /* Creates a node with the value */
    IntNode* node = malloc(sizeof(IntNode));
    VALIDATE_POINTER(node);
    node->next = NULL;
    node->data = val;

    /* Adds the node to the list */
    if (intNodeTop != NULL)
    {
        intNodeTop->next = node;
        intNodeTop = node;
    }

    else
    {
        intNodeRoot = node;
        intNodeTop = node;
    }

    return NULL;
}

/* Handler for float type */
static const char* StoreResultFloat(PyObject* obj)
{
    /* Fetches the value out of the PyObject */
    float val = PyFloat_AsDouble(obj);

    /* Creates a node with the value */
    FloatNode* node = malloc(sizeof(FloatNode));
    VALIDATE_POINTER(node);
    node->next = NULL;
    node->data = val;

    /* Adds the node to the list */
    if (floatNodeTop != NULL)
    {
        floatNodeTop->next = node;
        floatNodeTop = node;
    }

    else
    {
        floatNodeRoot = node;
        floatNodeTop = node;
    }

    return NULL;
}

/* Handler for string type */
static const char* StoreResultString(PyObject* obj)
{
    /* Copies the C-String so it is not accidentally destroyed */
    const char* temp = PyUnicode_AsUTF8(obj);

    char* val = malloc(strlen(temp) + 1);
    VALIDATE_POINTER(val);

    strcpy(val, temp);

    /* Creates the node with the value */
    CStringNode* node = malloc(sizeof(CStringNode));
    VALIDATE_POINTER(node);
    node->next = NULL;
    node->data = val;

    /* Adds the node to the list */
    if (stringNodeTop != NULL)
    {
        stringNodeTop->next = node;
        stringNodeTop = node;
    }

    else
    {
        stringNodeRoot = node;
        stringNodeTop = node;
    }

    return NULL;
}

/* Calls the correct StoreResult<T> depending on the type of the PyObject */
static const char* HandleStoreResult(PyObject* obj)
{
    /* Handles all supported types */
    if (PyLong_Check(obj))
        return StoreResultInt(obj);

    if (PyFloat_Check(obj))
        return StoreResultFloat(obj);

    if (PyUnicode_Check(obj))
        return StoreResultString(obj);

    /* Else it must be an error so it finds the type of the object */
    PyObject* objectType = PyObject_Type(obj);
    PyObject* objectTypename = PyObject_GetAttrString(objectType, "__name__");
    const char* typename = PyUnicode_AsUTF8(objectTypename);

    /* And creates an error message to return */
    char* errorPrefix = "Type: [";
    char* errorSuffix = "] is not supported to be returned from CT-Python";
    size_t errorLen = strlen(errorPrefix) + strlen(typename) + strlen(errorSuffix);

    char* fullError = malloc(errorLen);
    VALIDATE_POINTER(fullError);

    strcpy(fullError, errorPrefix);
    strcat(fullError, typename);
    strcat(fullError, errorSuffix);

    /* Cleans up allocated PyObjects before returning */
    Py_DECREF(objectType);
    Py_DECREF(objectTypename);

    return fullError;
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

    /* Retrives the type of the object */
    const char* result = HandleStoreResult(resultObj);

    /* Resets the global dictionary to stop contamination between snippets */
    PyDict_Clear(global);

    return result;
}

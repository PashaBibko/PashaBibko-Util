#pragma once

#include <vector>
#include <string>

namespace PashaBibko::Util::CTG
{
    struct PythonSnippet
    {
        const char* resName;
        const char* code;
    };

    inline std::vector<PythonSnippet>& GetCodeStorage()
    {
        static std::vector<PythonSnippet> storage;
        return storage;
    }

    inline void RegisterPython(const char* varName, const char* code)
    {
        GetCodeStorage().push_back({varName, code});
    }

    void InitialisePythonCTG();
}

#define _CTG_INTERNAL_CONCAT_IMPL(x, y) x##y
#define _CTG_INTERNAL_CONCAT(x, y) _CTG_INTERNAL_CONCAT_IMPL(x, y)

#define _CTG_INTERNAL_Python_IMPL(varName, code, id) \
    namespace CTG::Generated { struct _CTG_INTERNAL_CONCAT(CTG_Registerar_, id) { \
         _CTG_INTERNAL_CONCAT(CTG_Registerar_, id)() { \
            ::PashaBibko::Util::CTG::RegisterPython(varName, code); \
        } \
    } _CTG_INTERNAL_CONCAT(_CTG_Instance_, id); }

#define CTG_Python(varName, code) _CTG_INTERNAL_Python_IMPL(varName, code, __COUNTER__)

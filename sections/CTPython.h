#pragma once

#include <vector>
#include <string>

namespace PashaBibko::Util::CTG
{
    inline std::vector<const char*>& GetCodeStorage()
    {
        static std::vector<const char*> storage;
        return storage;
    }

    inline void RegisterPython(const char* code)
    {
        GetCodeStorage().push_back(code);
    }

    void InitialisePythonCTG();
}

#define _CTG_INTERNAL_CONCAT_IMPL(x, y) x##y
#define _CTG_INTERNAL_CONCAT(x, y) _CTG_INTERNAL_CONCAT_IMPL(x, y)

#define _CTG_INTERNAL_Python_IMPL(code, id) \
    namespace CTG::Generated { struct _CTG_INTERNAL_CONCAT(CTG_Registerar_, id) { \
         _CTG_INTERNAL_CONCAT(CTG_Registerar_, id)() { \
            ::PashaBibko::Util::CTG::RegisterPython(code); \
        } \
    } _CTG_INTERNAL_CONCAT(_CTG_Instance_, id); }

#define CTG_Python(code) _CTG_INTERNAL_Python_IMPL(code, __COUNTER__)

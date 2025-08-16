# Fetches data stored by C API #
output_path = globals().get('filepath')
values = globals().get('values')

# Types that can be written to the CPP file #
allowed_types = (int, float, str)

# Dictionary to store filtered values by type #
type_dicts = { t.__name__: {} for t in allowed_types }

for key, value in values.items():
    # Skip 'hidden' items #
    if key[:2] == "__":
        continue

    # Skip invalid types #
    if not isinstance(value, allowed_types):
        print(f"Invalid type: {type(value).__name__} for key '{key}'")

    # Adds value to correct dictionary #
    type_name = type(value).__name__
    type_dicts[type_name][key] = value

# Turns a python type into it's C++ equivalent string #
def TranslateType(_type):
    if (_type == "int"):
        return "long"
    
    if (_type == "float"):
        return "double"
    
    if (_type == "str"):
        return "std::string"

# Generates a cpp code snippet of std::unordered_map from a dictionary #
def GenerateMapFromDict(_type, dictionary):
    code_snippet = f"static const std::unordered_map<const char*, {TranslateType(_type)}, HASH, EQUAL> {_type}Values = \n{'{'}\n"

    for it, (key, value) in enumerate(dictionary.items()):
        code_snippet += f"\t{'{'} \"{key}\", {value} {'}'}"
        if it != len(dictionary) - 1:
            code_snippet += ','
        code_snippet += "\n"

    return code_snippet + "}\n\n"

# Generates a CPP function that will be exported from the DLL to access the maps #
def GenerateMapGetter(_type, dictionary):
    cpp_type = TranslateType(_type)
    code_snippet = f"""__declspec(dllexport) extern \"C\" {cpp_type} Get{_type}(const char* name)\n{'{'}
    {cpp_type} defaultVal{'{'}{'}'};
    auto it = {_type}Values.find(name);
    return (it != {_type}Values.end()) ? it->second : defaultVal;
{'}'}\n\n"""

    return code_snippet

# Start of the CPP file #
cpp_file = """#include <unordered_map>

struct HASH
{
    size_t operator()(const char* str) const
    {
        size_t hash = 0;
        while (*str) { hash = hash * 31 + *str++; }
        return hash;
    }
};

struct EQUAL
{
    bool operator()(const char* lhs, const char* rhs) const
    {
        return strcmp(lhs, rhs) == 0;
    }
};

"""

# Adds the dictionaries and functions to the file #
for t, d in type_dicts.items():
    if not len(d) == 0:
        cpp_file += GenerateMapFromDict(t, d)
        cpp_file += GenerateMapGetter(t, d)

# Writes the cpp to the provided file #
with open(output_path, "w") as file:
    file.write(cpp_file)

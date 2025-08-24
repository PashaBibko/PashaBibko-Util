#include <core/FileManagment.h>

#include <iostream>
#include <fstream>

#if defined(_WIN32) || defined(_WIN64)
    #define NOMINMAX
    #define WIN32_LEAN_AND_MEAN
    #include <Windows.h>
#elif defined(__linux__)
    #error "Linux is not currently supported for this library version"
#endif

namespace PashaBibko::Util
{
    FileReadError::FileReadError(const std::filesystem::path& _path, Reason _reason)
        : path(_path), reason(_reason)
    {}

    const char* const FileReadError::ReasonStr(Reason reason)
    {
        static const char* reasons[] =
        {
            "File cannot be found",
            "File reading permissions are denied",
            "Not a file"
        };

        return reasons[reason];
    }

    ReturnVal<std::string, FileReadError> ReadFile(const std::filesystem::path& path)
    {
        /* Checks the file exists */
        if (!std::filesystem::exists(path))
            return FunctionFail<FileReadError>(std::filesystem::absolute(path), FileReadError::FileNotFound);

        /* Checks it is a regular file */
        if (!std::filesystem::is_regular_file(path))
            return FunctionFail<FileReadError>(std::filesystem::absolute(path), FileReadError::NotAFile);

        /* Checks it can open the file */
        std::ifstream file(path, std::ios::binary | std::ios::ate);
        if (!file)
            return FunctionFail<FileReadError>(std::filesystem::absolute(path), FileReadError::PermissionDenied);

        /* Copies the file to the output string */
        const std::streamsize len = file.tellg();
        file.seekg(0, std::ios::beg);

        std::string contents(len, '\0');
        file.read(&contents[0], len);

        return contents;
    }

    StringLocation GetLocationAtStringIndex(const std::string& string, uint32_t index)
    {
        /* Creates the output and verifies the index */
        StringLocation location = { 1, 1 };
        if (index > string.length())
            return { 0, 0 };

        /* Iterates over the string until it reaches the index */
        for (uint32_t it = 0; it != index; it++)
        {
            /* Updates location if it reaches a new line */
            if (string[it] == '\n')
            {
                location.colummn = 0;
                location.line++;
            }

            location.colummn++;
        }

        return location;
    }

    std::filesystem::path TempFilePath(const std::string& name)
    {
        char tempFolderPath[MAX_PATH];
        GetTempPath(MAX_PATH, tempFolderPath);

        std::filesystem::path fsPath = tempFolderPath;

        return fsPath / name;
    }
}

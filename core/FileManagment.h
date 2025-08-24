#pragma once

#include <core/ReturnVal.h>

#include <filesystem>

namespace PashaBibko::Util
{
    /**
     * @brief Error returned when PashaBibko::Util::ReadFile() fails.
     * 
     * @details Contains the absolute path of the file that was attempted
     *          to read as well as why the file read failed.
     */
    struct FileReadError final
    {
        /**
         * @brief Different reasons why the error can occur.
         */
        enum Reason
        {
            FileNotFound,       ///< The file path did not point a file location.
            PermissionDenied,   ///< The executable does not have the permissions to read the file.
            NotAFile            ///< The file path pointed to a folder not a file.
        };

        /**
         * @param _path The absolute file path that was tried to read from.
         * @param _reason Why the file read failed.
         */
        FileReadError(const std::filesystem::path& _path, Reason _reason);

        /**
         * @brief Absolute file path of the error.
         */
        const std::filesystem::path path;

        /**
         * @brief Why the file read failed.
         */
        const Reason reason;

        /**
         * @brief Converts a FileReadError::Reason into a relevant c-string.
         */
        static const char* const ReasonStr(Reason reason);
    };

    /**
     * @brief Reads a file to a string.
     * 
     * @details Will check if the file path is valid and will return a FileReadError
     *          with a relevant error if invalid.
     * 
     * @param path File path to read from
     */
    ReturnVal<std::string, FileReadError> ReadFile(const std::filesystem::path& path);

    /**
     * @brief Location within a string.
     * 
     * @details Stored as [colummn, line] with indexing based at 1 as
     *          that is what files use.
     */
    struct StringLocation final
    {
        unsigned short colummn;
        unsigned short line;
    };

    /**
     * @brief Finds the location of [colummn, line] of a given index.
     * 
     * @param string The string that will be searched for the index.
     * @param index The index that the location will be returned.
     * 
     * @note If the index is outside the bounds of the string
     *       it will return { 0, 0 } instead of a valid location.
     */
    StringLocation GetLocationAtStringIndex(const std::string& string, uint32_t index);
}

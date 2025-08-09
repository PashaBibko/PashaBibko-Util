#pragma once

/**
 * @file FileRead.h
 * 
 * @brief Contains the function for reading a file as well as the error
 *        that can be returned if the function failed. Also includes
 *        function to find location of an index within a string.
 */


#include <filesystem>

#include <classes/ReturnVal.h>

namespace PashaBibko::Util
{
    /** Error returned when PashaBibko::Util::ReadFile() fails */
    struct FileReadError final
    {
        /** Different reasons why the error can occur */
        enum Reason
        {
            FileNotFound,
            PermissionDenied,
            NotAFile
        };

        /** Constructor to pass arguments to the struct */
        FileReadError(const std::filesystem::path& _path, Reason _reason);

        /** Error information */
        const std::filesystem::path path;
        const Reason reason;

        /** Turns the error enum into a c-string */
        static const char* const ReasonStr(Reason reason);
    };

    /** */
    ReturnVal<std::string, FileReadError> ReadFile(const std::filesystem::path& path);

    /** */
    struct StringLocation
    {
        unsigned short colummn;
        unsigned short line;
    };

    /** */
    StringLocation GetLocationAtStringIndex(const std::string& string, uint32_t index);
}

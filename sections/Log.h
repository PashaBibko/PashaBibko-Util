#pragma once

#include <classes/Colour.h>

#include <sections/Misc.h>

#include <type_traits>
#include <iomanip>
#include <sstream>
#include <ostream>
#include <ranges>

/**
 * @file Log.h
 * 
 * @brief Includes the functions for logging types to the console and log file.
 */


namespace PashaBibko::Util
{
    /* Excludes the internal namespace from the docs */
    #ifndef DOXYGEN_HIDE

    namespace Internal
    {
        /* Functions defined in Log.cpp to allow writing to their local variables */

        void WriteToConsole(const char* message);
        void WriteToLog(const char* message);

        /* Checks if a type can be outputted to std::ostream */
        template<typename Ty> concept StandardLogable = requires(std::ostream & os, Ty arg)
        {
            { os << arg } -> std::same_as<std::ostream&>;
        };

        /* Checks if the type has a LogStr function */
        template<typename Ty> concept TypeHasLogFunction = requires(Ty obj)
        {
            { obj.LogStr() } -> std::same_as<std::string>;
        };

        /* Assumes all types passed are valid as it is an internal function */
        template<typename Ty>
        std::string ProcessArg(Ty&& arg)
        {
            /* Checks if the argument type is a pointer */
            if constexpr(std::is_pointer_v<std::remove_cvref_t<Ty>>)
            {
                /* If the pointer is valid forwards the derefenced arg */
                if (arg != nullptr)
                    return ProcessArg(*arg);

                /* Else prints a message about a nullptr of type Ty */
                std::ostringstream os{};
                os << "Nullptr of type: [" << typeid(Ty).name() << ']';
                return std::move(os).str();
            }

            /* Custom log function has highest precedence */
            else if constexpr (TypeHasLogFunction<Ty>)
            {
                return arg.LogStr();
            }

            /* Checks for standard logging (std::ostream& << Ty) */
            else if constexpr (StandardLogable<Ty>)
            {
                std::ostringstream os{};
                os << arg;

                return std::move(os).str();
            }

            /* Else returns an error */
            else
            {
                static_assert(false, "Invalid type passed to Util::Internal::ProcessArg(), It is recommended not to use internal functions");
            }
        }

        /* Assumes all types passed are valid as it is an internal function */
        template<typename... Args>
        std::string ProcessArgs(Args&&... args)
        {
            return (ProcessArg(std::forward<Args>(args)) + ... + "");
        }

        template<typename Ty> concept LogableBase = Internal::StandardLogable<Ty> || Internal::TypeHasLogFunction<Ty>;
        template<typename Ty> concept Logable = LogableBase<Ty> || (LogableBase<std::remove_cv_t<std::remove_pointer_t<std::remove_cvref_t<Ty>>>>);
    }

    #endif // DOXYGEN_HIDE

    template<Colour colour = Colour::Default, typename... Args>
        requires (Internal::Logable<std::remove_cvref_t<Args>> && ...)
    inline void Print(Args&&... args)
    {
        if constexpr (colour != Colour::Default)
            Util::SetConsoleColor(colour);

        std::string message = Internal::ProcessArgs(std::forward<Args>(args)...);
        Internal::WriteToConsole(message.c_str());

        if constexpr (colour != Colour::Default)
            Util::SetConsoleColor(Colour::Default);
    }

    template<typename... Args>
        requires (Internal::Logable<std::remove_cvref_t<Args>> && ...)
    inline void Log(Args&&... args)
    {
        std::string message = Internal::ProcessArgs("[PB_Util::Log]: ", std::forward<Args>(args)..., '\n');
        Internal::WriteToConsole(message.c_str());
        Internal::WriteToLog(message.c_str());
    }

    /* These functions documentation are covered by Util::Print and Util::Log so they can be excluded */
    #ifndef DOXYGEN_HIDE

    template< Colour colour = Colour::Default, typename... Args>
        requires (Internal::Logable<std::remove_cvref_t<Args>> && ...)
    inline void PrintLn(Args&&... args)
    {
        Print(std::forward<Args>(args)..., '\n');
    }

    template<typename Ty, std::ranges::range Container_Ty, typename Cargo_Ty = std::ranges::range_value_t<Container_Ty>>
        requires Internal::Logable<Cargo_Ty>
    inline void Log(Ty&& name, const Container_Ty& container)
    {
        /* Creates a JSON like formatting of the range */
        std::ostringstream os{};
        os << "[PB_Util::Log]: \"" << Internal::ProcessArg(name) << "\"\n{\n";

        unsigned counter = 0;
        for (const auto& item : container)
        {
            std::string itemStr = Internal::ProcessArg(item);
            os << '\t' << std::setw(4) << std::left << counter << " | " << itemStr << '\n';
            counter++;
        }

        os << "}\n";
        std::string message = os.str();

        /* Writes the message to console/log */
        Internal::WriteToConsole(message.c_str());
        Internal::WriteToLog(message.c_str());
    }

    #endif // DOXYGEN_HIDE
}

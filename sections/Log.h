#pragma once

#include <classes/Colour.h>

#include <sections/Misc.h>

#include <type_traits>
#include <iomanip>
#include <sstream>
#include <ostream>
#include <ranges>

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
        std::string ProcessArg(Ty arg)
        {
            /* Custom log function has highest precedence */
            if constexpr (TypeHasLogFunction<Ty>)
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
                static_assert(false, "Invalid type passed to Util::Internal::ProcessArg(), Please use dedicated functions and not Internal functions");
            }

            /* Checks if the type can be iterated over */
        }

        /* Assumes all types passed are valid as it is an internal function */
        template<typename... Args>
        std::string ProcessArgs(Args&&... args)
        {
            return (ProcessArg(std::forward<Args>(args)) + ... + "");
        }
    }

    #endif // DOXYGEN_HIDE

    template<typename Ty> concept Logable = Internal::StandardLogable<Ty> || Internal::TypeHasLogFunction<Ty>;

    template<Colour col, typename... Args>
        requires Logable<Args...>
    inline void PrintAs(Args&&... args)
    {
        Util::SetConsoleColor(col);

        std::string message = Internal::ProcessArgs(std::forward<Args>(args)...);
        Internal::WriteToConsole(message.c_str());

        Util::SetConsoleColor(Util::Colour::Default);
    }

    template<typename... Args>
        requires Logable<Args...>
    inline void Print(Args&&... args)
    {
        std::string message = Internal::ProcessArgs(std::forward<Args>(args)...);
        Internal::WriteToConsole(message.c_str());
    }

    template<typename... Args>
        requires Logable<Args...>
    inline void PrintLn(Args&&... args)
    {
        std::string message = Internal::ProcessArgs(std::forward<Args>(args)..., '\n');
        Internal::WriteToConsole(message.c_str());
    }

    template<typename... Args>
        requires Logable<Args...>
    inline void Log(Args&&... args)
    {
        std::string message = Internal::ProcessArgs("[PB_Util::Log]: ", std::forward<Args>(args)..., '\n');
        Internal::WriteToConsole(message.c_str());
        Internal::WriteToLog(message.c_str());
    }

    template<typename Ty, std::ranges::range Container_Ty, typename Cargo_Ty = std::ranges::range_value_t<Container_Ty>>
        requires Logable<Cargo_Ty>
    inline void LogContainer(Ty&& name, const Container_Ty& container)
    {
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
}

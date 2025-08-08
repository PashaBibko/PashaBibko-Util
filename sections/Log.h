#pragma once

#include <classes/Colour.h>

#include <sections/Misc.h>

#include <sstream>
#include <ostream>

namespace PashaBibko::Util
{
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

        /* Check if a type has any way to be logged */
        template<typename Ty> concept Logable = StandardLogable<Ty>;

        /* Functions for turning arguments into their string equivalents */

        template<typename Ty>
            requires StandardLogable<Ty>
        std::string ProcessArg(Ty arg)
        {
            std::ostringstream os{};
            os << arg;

            return std::move(os).str();
        }

        template<typename... Args>
        std::string ProcessArgs(Args&&... args)
        {
            return (ProcessArg(std::forward<Args>(args)) + ... + "");
        }
    }

    template<Colour col, typename... Args>
        requires Internal::Logable<Args...>
    inline void PrintAs(Args&&... args)
    {
        Util::SetConsoleColor(col);

        std::string message = Internal::ProcessArgs(std::forward<Args>(args)...);
        Internal::WriteToConsole(message.c_str());

        Util::SetConsoleColor(Util::Colour::Default);
    }

    template<typename... Args>
        requires Internal::Logable<Args...>
    inline void Print(Args&&... args)
    {
        std::string message = Internal::ProcessArgs(std::forward<Args>(args)...);
        Internal::WriteToConsole(message.c_str());
    }

    template<typename... Args>
        requires Internal::Logable<Args...>
    inline void PrintLn(Args&&... args)
    {
        std::string message = Internal::ProcessArgs(std::forward<Args>(args)..., '\n');
        Internal::WriteToConsole(message.c_str());
    }

    template<typename... Args>
        requires Internal::Logable<Args...>
    inline void Log(Args&&... args)
    {
        std::string message = Internal::ProcessArgs("[PB_Util::Log]: ", std::forward<Args>(args)..., '\n');
        Internal::WriteToConsole(message.c_str());
        Internal::WriteToLog(message.c_str());
    }
}

#pragma once

#include <core/Colour.h>
#include <core/Macros.h>
#include <core/Misc.h>

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
    namespace Internal
    {
        /* Checks if a type can be outputted to std::ostream */
        template<typename Ty> concept StandardLogable = requires(std::ostream & os, Ty arg)
        {
            { os << arg } -> std::same_as<std::ostream&>;
        };

        template<typename Ty> std::string ProcessArg(Ty&& arg, unsigned depth = 0);
    };

    /**/
    class LogStream final
    {
        public:
            template<typename Ty> friend std::string Internal::ProcessArg(Ty&& arg, unsigned depth);

            template<typename Ty>
                requires Internal::StandardLogable<Ty>
            friend LogStream& operator<<(LogStream& _log, Ty&& _val)
            {
                _log.m_Stream << _val;
                return _log;
            }

            struct LogCommand
            {
                enum class CommandInstruction
                {
                    NewLine
                };

                LogCommand(CommandInstruction providedInstruction)
                    : instruction(providedInstruction)
                {}

                const CommandInstruction instruction;
            };

            friend LogStream& operator<<(LogStream& _log, const LogCommand& cmd)
            {
                switch (cmd.instruction)
                {
                    case LogStream::LogCommand::CommandInstruction::NewLine:
                        _log.m_Stream << '\n' << std::string(_log.m_Depth, ' ');
                        return _log;

                    default:
                        TriggerBreakpoint();
                        return _log;
                }
            }

        private:
            LogStream(std::ostringstream& stream, unsigned depth)
                : m_Stream(stream), m_Depth(depth)
            {}

            LogStream(const LogStream&) = default;
            LogStream(LogStream&&) noexcept = default;

            ~LogStream() = default;

            std::ostringstream& m_Stream;
            unsigned m_Depth;
    };

    const LogStream::LogCommand NewLine = LogStream::LogCommand(LogStream::LogCommand::CommandInstruction::NewLine);

    /* Excludes the internal namespace from the docs */
    #ifndef DOXYGEN_HIDE

    namespace Internal
    {
        /* Functions defined in Log.cpp to allow writing to their local variables */

        void WriteToConsole(const char* message);
        void WriteToLog(const char* message);

        /* Checks if the type has a legacy LogStr function */
        template<typename Ty> concept TypeHasLegacyLogFunction = requires(Ty obj)
        {
            { obj.LogStr() } -> std::same_as<std::string>;
        };

        /* Checks if the type has a valid (non-legacy) LogStr function */
        template<typename Ty> concept TypeHasLogFunction = requires(Ty obj, LogStream& stream)
        {
            { obj.LogStr(stream) } -> std::same_as<void>;
        };

        #define CREATE_LOG_STR_FUNCTION void LogStr(LogStream& stream) const

        /* Checks if a type has a custom log iterator */
        template<typename Ty> concept TypeHasCustomLogIterator = requires(Ty obj, std::ostringstream& os, std::size_t index)
        {
            { obj.CustomLogIter(os, index) } -> std::same_as<void>;
        };

        #define CREATE_CUSTOM_LOG_ITERATOR_FUNCTION void CustomLogIter(std::ostringstream& os, std::size_t index) const

	    /* Helper type to display type name in static_assert() */
	    template<typename Ty> struct DependentFalse : std::false_type {};

        /* Helper function to call legacy LogStr function, has to be seperate to mark as deprecated */
        template<typename Ty>
        _DEPRECATED("\n\tTy.LogStr() is deprecated, please define Ty.LogStr(std::ostringstream& os, unsigned depth).\n\tSee documentation for more information\n")
        std::string ProcessLegacyArg(Ty&& arg) { return arg.LogStr(); }

        /* Assumes all types passed are valid as it is an internal function */
        template<typename Ty> std::string ProcessArg(Ty&& arg, unsigned depth)
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

            /* Checks for non-legacy log function */
            else if constexpr (TypeHasLogFunction<Ty>)
            {
                std::ostringstream os{};
                LogStream stream(os, depth);

                arg.LogStr(stream);

                return os.str();
            }

            /* Custom log function has highest precedence                                                         */
            /* Still calls the function but throws a warning as it is legacy and should be changed to new version */
            else if constexpr (TypeHasLegacyLogFunction<Ty>)
            {
                return ProcessLegacyArg(arg);
            }

            /* Checks for standard logging (std::ostream& << Ty) */
            else if constexpr (StandardLogable<Ty>)
            {
                /* Checks if the type is a boolean in which case it replaces it with true/false */
                if constexpr (std::same_as<bool, std::remove_cvref_t<Ty>>)
                {
                    if (arg)
                        return "TRUE";

                    else
                        return "FALSE";
                }

                /* Else uses the ostream& operator to get the desired output */
                std::ostringstream os{};
                os << arg;

                return os.str();
            }

            /* Else returns an error */
            else
            {
                static_assert(DependentFalse<Ty>::value, "Invalid type passed to Util::Internal::ProcessArg(), It is recommended not to use internal functions");
            }
        }

        /* Assumes all types passed are valid as it is an internal function */
        template<typename... Args>
        std::string ProcessArgs(Args&&... args)
        {
            return (ProcessArg(std::forward<Args>(args)) + ... + "");
        }

        template<typename Ty> concept LogableBase = Internal::StandardLogable<Ty> || Internal::TypeHasLogFunction<Ty> || Internal::TypeHasLegacyLogFunction<Ty>;
        template<typename Ty> concept Logable = LogableBase<Ty> || (LogableBase<std::remove_cv_t<std::remove_pointer_t<std::remove_cvref_t<Ty>>>>);
    }

    #endif // DOXYGEN_HIDE

    /**
     * @brief Prints the message to the console.
     * 
     * @details Types can be printed in 2 different ways. The first is if the type has a
     *          std::ostream& bit-shift operator overload defined. This is the operator
     *          that std::cout uses for outputting so will be used by all intergral types.
     * 
     *          The second way is by having a LogStr() method that returns a string. Below
     *          are some examples of logging with these methods.
     * 
     *          @code
     *          struct LogableExample
     *          {
     *              std::string LogStr() const // Function is required to be const //
     *              {
     *                  return "Custom Log method called";
     *              }
     *          }
     * 
     *          int main()
     *          {
     *              // Using the std::ostream& << operator //
     *              Util::Print("Hello, World! ", 3);
     * 
     *              // Using the LogStr() function //
     *              LogableExample object;
     *              Util::Print(object);
     * 
     *              return 0;
     *          }
     *          @endcode
     * 
     *          Instead of adding a new line('\n') character at the end of the message
     *          you can use Util::PrintLn which will automatically apend it for you.
     * 
     * @tparam colour (Optional) the color that it will print to the console in.
     * 
     * @arg args The arguments that will be printed to the console.
     */
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

    /**
     * @brief Logs the message to the log file and console.
     * 
     * @details See PashaBibko::Util::Print() for how different types can be logged.
     *          Log() also has a function overload for printing ranges. Any type that
     *          can be iterated over using begin() and end() such as std::array or
     *          std::vector. It also requires that type that is returned whilst
     *          iterating is also loggable. For example:
     * 
     *          @code
     *          struct A
     *          {
     *              // Empty //
     *          }
     * 
     *          struct B
     *          {
     *              std::string LogStr() const
     *              {
     *                  return "Custom Log function called";
     *              }
     *          }
     * 
     *          int main()
     *          {
     *              // Invalid because A cannot be logged //
     *              std::array<A, 5> array_A{};
     *              Util::Log(array_A);
     * 
     *              // Valid because B can be logged //
     *              std::array<B, 5> array_B{};
     *              Util::Log(array_B);
     *          }
     *          @endcode
     * 
     * @arg args The message that it will log to a file.
     */
    template<typename... Args>
        requires (Internal::Logable<std::remove_cvref_t<Args>> && ...)
    inline void Log(Args&&... args)
    {
        std::string message = Internal::ProcessArgs("[PB_Util::Log()]: ", std::forward<Args>(args)..., '\n');
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

        std::size_t index = 0;
        for (const auto& item : container)
        {
            /* Adds an indent to each item to make them stick out more in the log */
            std::ostringstream prefixStream{};
            prefixStream << std::string(8, ' ') << std::setw(4) << std::left;

            /* Uses the custom iterator if it is availble, else does it by index */
            if constexpr (Internal::TypeHasCustomLogIterator<Container_Ty>)
                container.CustomLogIter(prefixStream, index);

            else
                prefixStream << index;
            
            prefixStream << " | ";
            std::string prefix = prefixStream.str();

            /* Prints the item to the stream with the prefix(indent + iterator + seperator) */
            std::string itemStr = Internal::ProcessArg(item, prefix.length());
            os << prefix << itemStr << '\n';
            index++;
        }

        os << "}\n";
        std::string message = os.str();

        /* Writes the message to console/log */
        Internal::WriteToConsole(message.c_str());
        Internal::WriteToLog(message.c_str());
    }

    #endif // DOXYGEN_HIDE
}

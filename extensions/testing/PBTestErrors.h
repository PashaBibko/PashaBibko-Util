#pragma once

#include <core/Log.h>

#include <string>

/* Classes used by the macros, should not be accesed by the user */
namespace PashaBibko::Util::Testing
{
    /* Base class of all errors that can occur in a test */
    struct TestError
    {
        TestError(const char* _filename, std::size_t _line)
            : filename(_filename), line(_line)
        {}

        virtual void PrintToConsole() = 0;

        void PrintLocation()
        {
            PrintLn<Util::Colour::White>("Error in ", filename, "(", line, ")");
        }

        const std::string filename;
        const std::size_t line;
    };

    /* Error when values are not equal when they should be */
    template<typename LhsTy, typename RhsTy>
    struct NotEqualError : public TestError
    {
        NotEqualError(const char* lhs, const LhsTy& lhsV, const char* rhs, const RhsTy& rhsV, const char* filename, std::size_t line)
            : TestError(filename, line), m_Lhs(lhs), m_LhsVal(lhsV), m_Rhs(rhs), m_RhsVal(rhsV)
        {}

        virtual void PrintToConsole()
        {
            PrintLocation();
            PrintLn("Expected values to be equal: ");

            if constexpr (Internal::Logable<LhsTy>)
                PrintLn("\t\"", m_Lhs, "\" got {", m_LhsVal, "}");
            else
                PrintLn("\t\"", m_Lhs, "\" got {unknown}");

            if constexpr (Internal::Logable<RhsTy>)
                PrintLn("\t\"", m_Rhs, "\" got {", m_RhsVal, "}");
            else
                PrintLn("\t\"", m_Rhs, "\" got {unknown}");
        }

        const std::string m_Lhs;
        const std::string m_Rhs;

        const LhsTy m_LhsVal;
        const RhsTy m_RhsVal;
    };
}

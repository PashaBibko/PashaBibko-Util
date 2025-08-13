#include <Util.h>

#include <cstdlib>

#include <classes/Colour.h>

/*
 * Different operating systems have different includes needed for coloring in the console.
 * Therefore, we need to include the appropriate headers based on the operating system.
 * To avoid unecessary items in the global namespace the includes are local to this file.
 * Each operating system also has it's own function defintion of SetConsoleColor to not interfere with each other.
 */

#if defined(_WIN32) || defined(_WIN64)
	#ifndef NOMINMAX // Defined by GCC
	#define NOMINMAX
	#endif // NOMINMAX
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>

	/* Sets the console color based on the provided Color enum (Windows). */
	void PashaBibko::Util::SetConsoleColor(Colour col)
	{
		/* Static holder of the console handle to avoid excess fetching */
		static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		/* Verifies handle is valid before attempting to modify the console */
		if (hConsole == INVALID_HANDLE_VALUE) [[unlikely]]
			return; /* Fails silently as it will not effect the running process of the program */

		/* Sets the console color using the Color enum value */
		SetConsoleTextAttribute(hConsole, static_cast<WORD>(col));
	}

	/* Triggers a breakpoint if a debugger is attached to the current process */
	void PashaBibko::Util::TriggerBreakpoint()
	{
		/* Breakpoints can only be triggered in Debug builds so it does not check on non-debug builds */
		#ifdef _DEBUG

		/* Only triggers a breakpoint if a debugger is attached to stop accidental errors */
		if (IsDebuggerPresent())
			DebugBreak();

		#endif
	}

#elif defined(__linux__)
	#include <unistd.h>
	#include <string.h>
	#include <signal.h>

	/* Local function to translate Win32 color codes to ansi escape codes */
	static constexpr const char* GetAnsiCode(PashaBibko::Util::Colour color)
	{
		using namespace PashaBibko::Util;

		switch (color)
		{
			case Colour::Black:        return "\x1b[30m";
			case Colour::Blue:         return "\x1b[34m";
			case Colour::Green:        return "\x1b[32m";
			case Colour::Aqua:         return "\x1b[36m";
			case Colour::Red:          return "\x1b[31m";
			case Colour::Purple:       return "\x1b[35m";
			case Colour::Yellow:       return "\x1b[33m";
			case Colour::LightGray:    return "\x1b[0m";
			case Colour::LightBlue:    return "\x1b[94m";
			case Colour::LightGreen:   return "\x1b[92m";
			case Colour::LightAqua:    return "\x1b[96m";
			case Colour::LightRed:     return "\x1b[91m";
			case Colour::LightPurple:  return "\x1b[95m";
			case Colour::LightYellow:  return "\x1b[93m";
			case Colour::White:        return "\x1b[97m";
			default:                   return "\x1b[0m";
		}
	}

	/* Sets the console color based on the provided Color enum (Unix/Linux). */
	void PashaBibko::Util::SetConsoleColor(Colour col)
	{
		/* Fetches the ANSI code for the specified color */
		const char* ansiCode = GetAnsiCode(col);

		/* Writes the ANSI code to the standard output */
		write(STDOUT_FILENO, ansiCode, strlen(ansiCode));
	}

	/* Triggers a breakpoint. TODO: Detect if a debugger is active */
	void PashaBibko::Util::TriggerBreakpoint()
	{
		/* Commented out to stop crashes */
		//raise(SIGTRAP);
	}

#else
	#error "Unsupported operating system."
#endif

void PashaBibko::Util::EndProcess(bool breakpoint)
{
	/* Triggers a breakpoint if wanted */
	if (breakpoint)
		TriggerBreakpoint();

	std::abort();
}


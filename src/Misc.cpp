#include <Util.h>

#include <cstdlib>

/*
 * Different operating systems have different includes needed for coloring in the console.
 * Therefore, we need to include the appropriate headers based on the operating system.
 * To avoid unecessary items in the global namespace the includes are local to this file.
 * Each operating system also has it's own function defintion of SetConsoleColor to not interfere with each other.
 */

#if defined(_WIN32) || defined(_WIN64)
	#define NOMINMAX
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

	/* Ends the current program */
	void PashaBibko::Util::EndProcess(bool breakpoint)
	{
		/* Triggers a breakpoint if wanted */
		if (breakpoint)
			TriggerBreakpoint();

		std::abort();
	}

#elif defined(__linux__) || defined(_unix__)
	#include <unistd.h>
	#include <string.h>

	/* Local function to translate Win32 color codes to ansi escape codes */
	static constexpr const char* GetAnsiCode(Color color)
	{
		switch (color)
		{
		case Colour::BLACK:        return "\x1b[30m";
		case Colour::BLUE:         return "\x1b[34m";
		case Colour::GREEN:        return "\x1b[32m";
		case Colour::AQUA:         return "\x1b[36m";
		case Colour::RED:          return "\x1b[31m";
		case Colour::PURPLE:       return "\x1b[35m";
		case Colour::YELLOW:       return "\x1b[33m";
		case Colour::LIGHT_GRAY:   return "\x1b[0m";
		case Colour::LIGHT_BLUE:   return "\x1b[94m";
		case Colour::LIGHT_GREEN:  return "\x1b[92m";
		case Colour::LIGHT_AQUA:   return "\x1b[96m";
		case Colour::LIGHT_RED:    return "\x1b[91m";
		case Colour::LIGHT_PURPLE: return "\x1b[95m";
		case Colour::LIGHT_YELLOW: return "\x1b[93m";
		case Colour::WHITE:        return "\x1b[97m";
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

#else
	#error "Unsupported operating system."
#endif

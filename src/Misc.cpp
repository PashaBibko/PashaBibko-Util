#include <Util.h>

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
	void PashaBibko::Util::SetConsoleColor(Color col)
	{
		/* Static holder of the console handle to avoid excess fetching */
		static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		/* Verifies handle is valid before attempting to modify the console */
		if (hConsole == INVALID_HANDLE_VALUE) [[unlikely]]
			return; /* Fails silently as it will not effect the running process of the program */

		/* Sets the console color using the Color enum value */
		SetConsoleTextAttribute(hConsole, static_cast<WORD>(col));
	}

#elif defined(__linux__) || defined(_unix__)
	#include <unistd.h>
	#include <string.h>

	/* Local function to translate Win32 color codes to ansi escape codes */
	static constexpr const char* GetAnsiCode(Color color)
	{
		switch (color)
		{
		case Color::BLACK:        return "\x1b[30m";
		case Color::BLUE:         return "\x1b[34m";
		case Color::GREEN:        return "\x1b[32m";
		case Color::AQUA:         return "\x1b[36m";
		case Color::RED:          return "\x1b[31m";
		case Color::PURPLE:       return "\x1b[35m";
		case Color::YELLOW:       return "\x1b[33m";
		case Color::LIGHT_GRAY:   return "\x1b[0m";
		case Color::LIGHT_BLUE:   return "\x1b[94m";
		case Color::LIGHT_GREEN:  return "\x1b[92m";
		case Color::LIGHT_AQUA:   return "\x1b[96m";
		case Color::LIGHT_RED:    return "\x1b[91m";
		case Color::LIGHT_PURPLE: return "\x1b[95m";
		case Color::LIGHT_YELLOW: return "\x1b[93m";
		case Color::WHITE:        return "\x1b[97m";
		default:                  return "\x1b[0m";
		}
	}

	/* Sets the console color based on the provided Color enum (Unix/Linux). */
	void PashaBibko::Util::SetConsoleColor(Color col)
	{
		/* Fetches the ANSI code for the specified color */
		const char* ansiCode = GetAnsiCode(col);

		/* Writes the ANSI code to the standard output */
		write(STDOUT_FILENO, ansiCode, strlen(ansiCode));
	}

#else
	#error "Unsupported operating system."
#endif

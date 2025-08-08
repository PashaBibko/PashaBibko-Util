#include <sections/Log.h>

#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>

namespace PashaBibko::Util::Internal
{
    /* Operating system specific implementation of GetProcessName */
    #if defined(_WIN32) || defined(_WIN64)
	    #define NOMINMAX
	    #define WIN32_LEAN_AND_MEAN
	    #include <Windows.h>

        /* Windows implementation of GetProcessName */
        static std::string GetProcessName()
        {
            /* Fetches the name of the .exe, returns "LOG" if it fails */
            char path[MAX_PATH] = { 0 };
            if (GetModuleFileName(NULL, path, MAX_PATH) == 0)
                return "LOG";

            return std::string(path);
        }

    #elif defined(__linux__)
	    #include <unistd.h>
	    #include <limits.h>

        /* Linuix implementation of GetProcessName */
        static std::string GetProcessName()
        {
            /* Fetches the name of the process, returns "LOG" if it fails */
            char path[MAX_PATH] = { 0 };
            ssize_t count = readlink("/proc/self/exe", path, PATH_MAX);
            if (count == -1)
                return "LOG";

            return std::string(path, count);
        }

    #else
        #error "Unsupported operating system."
    #endif

    /* Static initalizer for the log */

    static std::ofstream log;

    struct LogInitalizer
    {
        LogInitalizer()
        {
            /* Creates the log with the name of the process */
            std::filesystem::path process = GetProcessName();
            std::string logPath = process.string() + ".log";
            log.open(logPath);
        }
    };

    static LogInitalizer logInitInstance;

    /* External functions to allow Log.h to write to the console and log */

    void WriteToConsole(const char* message)
    {
        std::cout << message;
        std::cout.flush();
    }

    void WriteToLog(const char* message)
    {
        log << message;
        log.flush();
    }
}

#pragma once

#include <classes/Colour.h>

/* Floating functions within the lib (not connected to a class) or a general section */
namespace PashaBibko::Util
{
    /**
     * @brief Sets the console to display text with a certain color.
     * 
     * @details Supported on Windows and UNIX based operating systems.
     *          If it is unable to set the color it will silently fail.
     * 
     * @param col The color that the console will be set to.
     */
	void SetConsoleColor(Colour col);

    /**
     * @brief Triggers a breakpoint if there is a Debugger to attach to
     * 
     * @details Calls `DebugBreak()` on Windows or `std::raise(SIGTRAP)` on UNIX based systems.
     *          On windows will check if there is a debugger attached but will not on UNIX.
     */
    void TriggerBreakpoint();

    /**
     * @brief Ends the current process
     * 
     * @param breakpoint If true will trigger a breakpoint before exiting (defaults to true)
     */
    void EndProcess(bool breakpoint = true);
}

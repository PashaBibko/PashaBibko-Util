#pragma once

#include <core/Colour.h>

/**
 * @file Misc.h
 * 
 * @brief No tests as these are either developer functions which trigger actions within the IDE
 *        or do not have a direct way to test via code.
 */

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
     * @details Calls `DebugBreak()` on Windows or `std::raise(SIGTRAP)` on Linux based systems.
     *          On windows will check if there is a debugger attached but will not on Linux.
     */
    void TriggerBreakpoint();

    /**
     * @brief Ends the current process
     * 
     * @param breakpoint If true will trigger a breakpoint before exiting (defaults to true)
     */
    void EndProcess(bool breakpoint = true);
}

#pragma once

/**
 * @file Util.h
 * 
 * @brief Global include for the PashaBibko Util library.
 *        This file includes all of the necessary headers and declarations.
 *        No other files should be included directly from this library.
 */

/* Floating functions within the lib (not connected to a class) */
namespace PashaBibko::Util
{
    /**
     * @brief Representation of each color and its corresponding Win32 console color code.
     *        Other operating systems use a switch statement to translate the codes from Win32 to their values.
     */
	enum class Colour : unsigned short
    {
        Default =       0x07, ///< The default colour of the console 

        Black = 0x00,         ///< <span style="color:#000000;">Black</span>
        Blue = 0x01,          ///< <span style="color:#000080;">Blue</span>
        Green = 0x02,         ///< <span style="color:#008000;">Green</span>
        Aqua = 0x03,          ///< <span style="color:#008080;">Aqua</span>
        Red = 0x04,           ///< <span style="color:#800000;">Red</span>
        Purple = 0x05,        ///< <span style="color:#800080;">Purple</span>
        Yellow = 0x06,        ///< <span style="color:#808000;">Yellow</span>
        LightGray = 0x07,     ///< <span style="color:#C0C0C0;">Light Gray</span>
        LightBlue = 0x09,     ///< <span style="color:#0000FF;">Light Blue</span>
        LightGreen = 0x0a,    ///< <span style="color:#00FF00;">Light Green</span>
        LightAqua = 0x0b,     ///< <span style="color:#00FFFF;">Light Aqua</span>
        LightRed = 0x0c,      ///< <span style="color:#FF0000;">Light Red</span>
        LightPurple = 0x0d,   ///< <span style="color:#FF00FF;">Light Purple</span>
        LightYellow = 0x0e,   ///< <span style="color:#FFFF00;">Light Yellow</span>
        White = 0x0f          ///< <span style="color:#FFFFFF;">White</span>
    };

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
    void EndProcess(bool breakpont = true);
}

/* Includes the classes of the Util library */
#include <classes/ReturnVal.h>

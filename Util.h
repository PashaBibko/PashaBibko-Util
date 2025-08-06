#pragma once

/**
 * @file Util.h
 * @brief Global include for the PashaBibko Util library.
 * This file includes all of the necessary headers and declarations.
 * No other files should be included directly from this library.
 */

/* Floating functions within the lib (not connected to a class) */
namespace PashaBibko::Util
{
    /**
    * Word representation of each color and its corresponding Win32 console color code.
    * Other operating systems use a switch statement to handle their codes.
    */
	enum class Color : unsigned short
    {
        DEFAULT = 0x07,

        BLACK = 0x00,
        BLUE = 0x01,
        GREEN = 0x02,
        AQUA = 0x03,
        RED = 0x04,
        PURPLE = 0x05,
        YELLOW = 0x06,
        LIGHT_GRAY = 0x07,
        LIGHT_BLUE = 0x09,
        LIGHT_GREEN = 0x0a,
        LIGHT_AQUA = 0x0b,
        LIGHT_RED = 0x0c,
        LIGHT_PURPLE = 0x0d,
        LIGHT_YELLOW = 0x0e,
        WHITE = 0x0f,

        TEST = 0x69
    };

    /**
     * @brief Sets the console to display text with a certain color.
     * 
     * @param col The color that the console will be set to.
     */
	void SetConsoleColor(Color col);
    
    /**
     * @brief Temporary class to see in documentation
     */
    struct Rectangle
    {
        int height;
        int width;

        int x;
        int y;

        /**
         * @brief Returns the x position of the rectangle
         */
        int GetX() { return x; }

        /**
         * @brief Returns the y position of the rectangle
         * 
         * @note Marked const for speed
         */
        int GetY() const { return y; }
    };
}

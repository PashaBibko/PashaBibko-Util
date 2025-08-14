#pragma once

/**
 * @file Colour.h
 * 
 * @brief Contains the colour enum
 */

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
}

/*
* Global include for the PashaBibko Util library.
* This file includes all of the necessary headers and declarations.
* No other files should be included directly from this library.
*/

#pragma once

/* Floating functions within the lib (not connected to a class) */
namespace PashaBibko::Util
{
	/**
	 * @brief Returns the version of the Util library.
	 * The function is constexpr to allow the using of it with constexpr if branches.
	 * 
	 * @return int The version number of the Util library.
	 */
	int LibVersion();
}

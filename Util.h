#pragma once

/**
 * @file Util.h
 * 
 * @brief Global include for the PashaBibko Util library.
 *        This file includes all of the necessary headers and declarations.
 *        No other files should be included directly from this library.
 */

/* MSVC Built in macros for non-MSVC enviroments */

#ifndef _UNLIKELY
#define _UNLIKELY [[unlikely]]
#endif // _UNLIKELY

#ifndef _LIKELY
#define _LIKELY [[likely]]
#endif // _LIKELY

/* Includes the classes of the Util library */
#include <classes/ReturnVal.h>
#include <classes/Colour.h>
#include <classes/Vec.h>

/* Includes the additional sections of the Util library */
#include <sections/CTPython.h>
#include <sections/FileRead.h>
#include <sections/Misc.h>
#include <sections/Log.h>

/* Shorthands for the namespace */
namespace PBU = PashaBibko::Util;
namespace PB = PashaBibko;

/* Commonly used STD files */
#include <unordered_map>
#include <type_traits>
#include <functional>
#include <cstdint>
#include <cstring>
#include <memory>
#include <vector>
#include <ranges>
#include <array>
#include <span>

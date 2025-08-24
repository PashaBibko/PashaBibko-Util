#pragma once

/**
 * @file Util.h
 * 
 * @brief Global include for the PashaBibko Util library.
 *        This file includes all of the necessary headers and declarations.
 *        No other files should be included directly from this library.
 */

/* MSVC Built in macros for non-MSVC enviroments                 */
/* Macros are used as attributes do not show up with intelisense */

#ifndef _UNLIKELY
#define _UNLIKELY [[unlikely]]
#endif // _UNLIKELY

#ifndef _LIKELY
#define _LIKELY [[likely]]
#endif // _LIKELY

#ifndef _DEPRECATED
#define _DEPRECATED(reason) [[deprecated(reason)]]
#endif // _DEPRECATED

/* Includes the core of the Util library */
#include <core/ReturnVal.h>
#include <core/Colour.h>
#include <core/Vec.h>
#include <core/FileManagment.h>
#include <core/Misc.h>
#include <core/Log.h>

/* Shorthands for the namespace */
namespace PBU = PashaBibko::Util;
namespace PB = PashaBibko;

/* Commonly used STD files */
#ifndef PB_UTIL_EXCLUDE_STD_INCLUDES
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
#endif // PB_UTIL_EXCLUDE_STD_INCLUDES

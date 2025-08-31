#pragma once

/**
 * @file Util.h
 * 
 * @brief Global include for the PashaBibko Util library.
 *        This file includes all of the necessary headers and declarations.
 *        No other files should be included directly from this library.
 */

/* Includes the core of the Util library */
#include <core/Macros.h>
#include <core/ReturnVal.h>
#include <core/Colour.h>
#include <core/Vec.h>
#include <core/FileManagment.h>
#include <core/Misc.h>
#include <core/Log.h>

/* Optional extensions of the library */
#if defined(_PBUTIL_TEST_EXTENSION_ENABLED) || defined(PB_UTIL_VSC_DEV)
    #include <extensions/testing/PBTesting.h>
#endif // _PBUTIL_TEST_EXTENSION_ENABLED

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

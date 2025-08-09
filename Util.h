#pragma once

/**
 * @file Util.h
 * 
 * @brief Global include for the PashaBibko Util library.
 *        This file includes all of the necessary headers and declarations.
 *        No other files should be included directly from this library.
 */

 /* Includes the classes of the Util library */
#include <classes/ReturnVal.h>
#include <classes/Colour.h>

/* Includes the additional sections of the Util library */
#include <sections/FileRead.h>
#include <sections/Misc.h>
#include <sections/Log.h>

/* Shorthands for the namespace */
namespace PBU = PashaBibko::Util;
namespace PB = PashaBibko;

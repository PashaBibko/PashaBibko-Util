#pragma once

/**
 * @file Macros.h
 * 
 * @brief No tests as macros are handled in the compiler itself where we
 *        cannot check things easily.
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

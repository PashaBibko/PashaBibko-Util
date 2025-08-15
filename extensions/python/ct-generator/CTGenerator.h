#pragma once

/* Forces release version as MSVC has errors with debug headers */
#ifdef _DEBUG
#undef _DEBUG
#include <Python.h>
#define _DEBUG
#else
#include <Python.h>
#endif

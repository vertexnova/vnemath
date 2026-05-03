#pragma once
/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Author:    Ajeet Singh Yadav
 * Created:   March 2026
 * ----------------------------------------------------------------------
 */

/**
 * On Windows: dllexport/dllimport when building or consuming the shared library.
 * On Unix shared builds: default visibility when compiling the library (hidden otherwise).
 */
#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
#if defined(VNE_MATH_BUILDING_DLL)
#define VNE_MATH_API __declspec(dllexport)
#elif defined(VNE_MATH_DLL)
#define VNE_MATH_API __declspec(dllimport)
#else
#define VNE_MATH_API
#endif
#else
#if defined(VNE_MATH_BUILDING_DLL) && (defined(__GNUC__) || defined(__clang__))
#define VNE_MATH_API __attribute__((visibility("default")))
#else
#define VNE_MATH_API
#endif
#endif

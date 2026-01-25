#pragma once
/* ---------------------------------------------------------------------
 * Copyright (c) 2024 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Author:    Ajeet Singh Yadav
 * Created:   August-2024
 *
 * Autodoc:   yes
 * ----------------------------------------------------------------------
 */

/**
 * @file constants.h
 *
 * @brief Contains numeric math constants and limits.
 */

// System library includes
#include <limits>  // For numeric_limits

namespace vne::math {

////////////////////////////////////////////////////////////////////////////
//                              Constants                                 //
// /////////////////////////////////////////////////////////////////////////

/// Pi constant
constexpr float kPi = 3.1415926535897932385f;
/// 2 * Pi
constexpr float kTwoPi = 6.28318530717958647693f;
/// Pi / 2
constexpr float kHalfPi = 1.5707963267948966192f;
/// Pi / 4
constexpr float kQuarterPi = 0.78539816339744830962f;
/// 1 / Pi
constexpr float kOneOverPi = 0.31830988618379067154f;
/// 1 / (2 * Pi)
constexpr float kOneOverTwoPi = 0.15915494309189535f;
/// 2 / Pi
constexpr float kTwoOverPi = 0.63661977236758134308f;
/// sqrt(Pi)
constexpr float kSqrtPi = 1.7724538509055161f;
/// 2 / sqrt(Pi)
constexpr float kTwoOverSqrtPi = 1.1283791670955125739f;

/// Euler's number (e)
constexpr float kE = 2.7182818284590452354f;
/// log2(e)
constexpr float kLog2E = 1.4426950408889634074f;
/// log10(e)
constexpr float kLog10E = 0.43429448190325182765f;
/// ln(2)
constexpr float kLn2 = 0.69314718055994530942f;
/// ln(10)
constexpr float kLn10 = 2.3025850929940456840f;

/// sqrt(2)
constexpr float kSqrtTwo = 1.4142135623730950488f;
/// sqrt(3)
constexpr float kSqrtThree = 1.73205080756887729352f;
/// 1 / sqrt(2)
constexpr float kSqrtOneOverTwo = 0.70710678118654752440f;
/// 1 / sqrt(3)
constexpr float kSqrtOneOverThree = 0.57735026918962576450f;

/// A huge number that should be larger than any valid number used.
constexpr float kFloatInfinity = std::numeric_limits<float>::infinity();
constexpr double kDoubleInfinity = std::numeric_limits<double>::infinity();

/// The smallest positive value where 1.0f + epsilon != 1.0f
constexpr float kFloatEpsilon = std::numeric_limits<float>::epsilon();
constexpr double kDoubleEpsilon = std::numeric_limits<double>::epsilon();

/// The smallest normal positive value
constexpr float kFloatMin = std::numeric_limits<float>::min();
constexpr double kDoubleMin = std::numeric_limits<double>::min();

/// The largest normal value
constexpr float kFloatMax = std::numeric_limits<float>::max();
constexpr double kDoubleMax = std::numeric_limits<double>::max();

/// Not-a-Number value
constexpr float kFloatNan = std::numeric_limits<float>::quiet_NaN();
constexpr double kDoubleNan = std::numeric_limits<double>::quiet_NaN();

// Legacy aliases for backward compatibility
namespace {
constexpr float FLOAT_EPSILON = kFloatEpsilon;
constexpr float FLOAT_INFINITY = kFloatInfinity;
}  // namespace

}  // namespace vne::math

// Legacy macros for backward compatibility
#ifndef PI
#define PI 3.1415926535897932385E0
#endif
#ifndef TWO_PI
#define TWO_PI 6.28318530717958647693E0
#endif
#ifndef HALF_PI
#define HALF_PI 1.5707963267948966192E0
#endif
#ifndef QUARTER_PI
#define QUARTER_PI 7.8539816339744830962E-1
#endif
#ifndef ONE_OVER_PI
#define ONE_OVER_PI 3.1830988618379067154E-1
#endif
#ifndef ONE_OVER_TWO_PI
#define ONE_OVER_TWO_PI 1.5915494309189535E-1
#endif
#ifndef TWO_OVER_PI
#define TWO_OVER_PI 6.3661977236758134308E-1
#endif
#ifndef SQRT_PI
#define SQRT_PI 1.7724538509055161E0
#endif
#ifndef TWO_OVER_SQRT_PI
#define TWO_OVER_SQRT_PI 1.1283791670955125739E0
#endif
#ifndef E
#define E 2.7182818284590452354E0
#endif
#ifndef LOG2E
#define LOG2E 1.4426950408889634074E0
#endif
#ifndef LOG10E
#define LOG10E 4.3429448190325182765E-1
#endif
#ifndef LN2
#define LN2 6.9314718055994530942E-1
#endif
#ifndef LN10
#define LN10 2.3025850929940456840E0
#endif
#ifndef SQRT_TWO
#define SQRT_TWO 1.4142135623730950488E0
#endif
#ifndef SQRT_THREE
#define SQRT_THREE 1.73205080756887729352E0
#endif
#ifndef SQRT_ONE_OVER_TWO
#define SQRT_ONE_OVER_TWO 7.0710678118654752440E-1
#endif
#ifndef SQRT_ONE_OVER_THREE
#define SQRT_ONE_OVER_THREE 5.7735026918962576450E-1
#endif

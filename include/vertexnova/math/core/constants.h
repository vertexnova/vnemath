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
 * @brief Non-templated numeric math constants and limits.
 *
 * This file provides commonly used mathematical constants as
 * concrete float and double values, as well as numeric limits.
 *
 * For templated constants that work with any floating-point type,
 * use the kPiT<T>, kEpsilon<T>, etc. templates in math_utils.h
 *
 * Use this file when:
 * - You need specific float or double constants (kPi, kPiDouble)
 * - You need numeric limits (kFloatMax, kDoubleEpsilon, etc.)
 * - You're working with non-template code
 */

// System library includes
#include <limits>

namespace vne::math {

/// @name Pi-related Constants (float)
/// @{
constexpr float kPi = 3.1415926535897932385f;             ///< Pi constant
constexpr float kTwoPi = 6.28318530717958647693f;         ///< 2 * Pi
constexpr float kHalfPi = 1.5707963267948966192f;         ///< Pi / 2
constexpr float kQuarterPi = 0.78539816339744830962f;     ///< Pi / 4
constexpr float kOneOverPi = 0.31830988618379067154f;     ///< 1 / Pi
constexpr float kOneOverTwoPi = 0.15915494309189535f;     ///< 1 / (2 * Pi)
constexpr float kTwoOverPi = 0.63661977236758134308f;     ///< 2 / Pi
constexpr float kSqrtPi = 1.7724538509055161f;            ///< sqrt(Pi)
constexpr float kTwoOverSqrtPi = 1.1283791670955125739f;  ///< 2 / sqrt(Pi)
/// @}

/// @name Euler's Number Constants (float)
/// @{
constexpr float kE = 2.7182818284590452354f;        ///< Euler's number (e)
constexpr float kLog2E = 1.4426950408889634074f;    ///< log2(e)
constexpr float kLog10E = 0.43429448190325182765f;  ///< log10(e)
constexpr float kLn2 = 0.69314718055994530942f;     ///< ln(2)
constexpr float kLn10 = 2.3025850929940456840f;     ///< ln(10)
/// @}

/// @name Square Root Constants (float)
/// @{
constexpr float kSqrtTwo = 1.4142135623730950488f;            ///< sqrt(2)
constexpr float kSqrtThree = 1.73205080756887729352f;         ///< sqrt(3)
constexpr float kSqrtOneOverTwo = 0.70710678118654752440f;    ///< 1 / sqrt(2)
constexpr float kSqrtOneOverThree = 0.57735026918962576450f;  ///< 1 / sqrt(3)
/// @}

/// @name Numeric Limits (float)
/// @{
constexpr float kFloatInfinity = std::numeric_limits<float>::infinity();  ///< Positive infinity
constexpr float kFloatEpsilon = std::numeric_limits<float>::epsilon();    ///< Smallest difference from 1
constexpr float kFloatMin = std::numeric_limits<float>::min();            ///< Smallest positive normal value
constexpr float kFloatMax = std::numeric_limits<float>::max();            ///< Largest finite value
constexpr float kFloatNan = std::numeric_limits<float>::quiet_NaN();      ///< Not-a-Number value
/// @}

/// @name Numeric Limits (double)
/// @{
constexpr double kDoubleInfinity = std::numeric_limits<double>::infinity();  ///< Positive infinity
constexpr double kDoubleEpsilon = std::numeric_limits<double>::epsilon();    ///< Smallest difference from 1
constexpr double kDoubleMin = std::numeric_limits<double>::min();            ///< Smallest positive normal value
constexpr double kDoubleMax = std::numeric_limits<double>::max();            ///< Largest finite value
constexpr double kDoubleNan = std::numeric_limits<double>::quiet_NaN();      ///< Not-a-Number value
/// @}

/// @name Tolerance Constants
/// @{
constexpr float kZeroTolerance = 1E-5f;         ///< Epsilon for zero-division and normalization
constexpr double kZeroToleranceDouble = 1E-10;  ///< Double precision zero tolerance
constexpr float kColorByteMax = 255.0f;         ///< Color byte conversion factor (0-255)
/// @}

/// @name Pi-related Constants (double)
/// @{
constexpr double kPiDouble = 3.1415926535897932385;             ///< Pi (double)
constexpr double kTwoPiDouble = 6.28318530717958647693;         ///< 2 * Pi (double)
constexpr double kHalfPiDouble = 1.5707963267948966192;         ///< Pi / 2 (double)
constexpr double kQuarterPiDouble = 0.78539816339744830962;     ///< Pi / 4 (double)
constexpr double kOneOverPiDouble = 0.31830988618379067154;     ///< 1 / Pi (double)
constexpr double kOneOverTwoPiDouble = 0.15915494309189535;     ///< 1 / (2 * Pi) (double)
constexpr double kTwoOverPiDouble = 0.63661977236758134308;     ///< 2 / Pi (double)
constexpr double kSqrtPiDouble = 1.7724538509055161;            ///< sqrt(Pi) (double)
constexpr double kTwoOverSqrtPiDouble = 1.1283791670955125739;  ///< 2 / sqrt(Pi) (double)
/// @}

/// @name Euler's Number Constants (double)
/// @{
constexpr double kEDouble = 2.7182818284590452354;        ///< Euler's number (double)
constexpr double kLog2EDouble = 1.4426950408889634074;    ///< log2(e) (double)
constexpr double kLog10EDouble = 0.43429448190325182765;  ///< log10(e) (double)
constexpr double kLn2Double = 0.69314718055994530942;     ///< ln(2) (double)
constexpr double kLn10Double = 2.3025850929940456840;     ///< ln(10) (double)
/// @}

/// @name Square Root Constants (double)
/// @{
constexpr double kSqrtTwoDouble = 1.4142135623730950488;            ///< sqrt(2) (double)
constexpr double kSqrtThreeDouble = 1.73205080756887729352;         ///< sqrt(3) (double)
constexpr double kSqrtOneOverTwoDouble = 0.70710678118654752440;    ///< 1 / sqrt(2) (double)
constexpr double kSqrtOneOverThreeDouble = 0.57735026918962576450;  ///< 1 / sqrt(3) (double)
/// @}

}  // namespace vne::math

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

/// A reasonable epsilon for zero-division checks and normalization
constexpr float kZeroTolerance = 1E-5f;
constexpr double kZeroToleranceDouble = 1E-10;

/// Color component byte conversion factor (0-255 range)
constexpr float kColorByteMax = 255.0f;

/// The smallest normal positive value
constexpr float kFloatMin = std::numeric_limits<float>::min();
constexpr double kDoubleMin = std::numeric_limits<double>::min();

/// The largest normal value
constexpr float kFloatMax = std::numeric_limits<float>::max();
constexpr double kDoubleMax = std::numeric_limits<double>::max();

/// Not-a-Number value
constexpr float kFloatNan = std::numeric_limits<float>::quiet_NaN();
constexpr double kDoubleNan = std::numeric_limits<double>::quiet_NaN();

// Double precision constants
constexpr double kPiDouble = 3.1415926535897932385;
constexpr double kTwoPiDouble = 6.28318530717958647693;
constexpr double kHalfPiDouble = 1.5707963267948966192;
constexpr double kQuarterPiDouble = 0.78539816339744830962;
constexpr double kOneOverPiDouble = 0.31830988618379067154;
constexpr double kOneOverTwoPiDouble = 0.15915494309189535;
constexpr double kTwoOverPiDouble = 0.63661977236758134308;
constexpr double kSqrtPiDouble = 1.7724538509055161;
constexpr double kTwoOverSqrtPiDouble = 1.1283791670955125739;
constexpr double kEDouble = 2.7182818284590452354;
constexpr double kLog2EDouble = 1.4426950408889634074;
constexpr double kLog10EDouble = 0.43429448190325182765;
constexpr double kLn2Double = 0.69314718055994530942;
constexpr double kLn10Double = 2.3025850929940456840;
constexpr double kSqrtTwoDouble = 1.4142135623730950488;
constexpr double kSqrtThreeDouble = 1.73205080756887729352;
constexpr double kSqrtOneOverTwoDouble = 0.70710678118654752440;
constexpr double kSqrtOneOverThreeDouble = 0.57735026918962576450;

}  // namespace vne::math

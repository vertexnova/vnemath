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
 * @file math_utils.h
 *
 * @brief Provides extended mathematical utilities beyond std:: math.
 *
 * This file contains:
 * - Additional templated math constants (kQuarterPiT)
 * - Inverse square root and log-base-x helpers
 * - Relative comparison (areSame)
 * - Midpoint and round-to-multiple helpers
 * - Angle and range utilities (normalizeAngle, wrap, remap, etc.)
 *
 * Core templated utilities (abs, min, max, clamp, lerp, isZero, etc.)
 * are in core/types.h as they're required by the templated vec/mat/quat classes.
 *
 * For non-templated constants, use constants.h.
 * Call std::sin, std::sqrt, std::floor, etc. directly — this header does not
 * wrap the C++ standard library math functions.
 */

// Project includes
#include "vertexnova/math/core/constants.h"
#include "vertexnova/math/core/types.h"
#include "vertexnova/common/macros.h"

// System library includes
#include <cmath>

namespace vne::math {

// ============================================================================
// Additional Templated Constants
// ============================================================================

/// @brief Quarter Pi (templated) - supplemental constant
template<FloatingPoint T>
inline constexpr T kQuarterPiT = kPiT<T> / T(4);

////////////////////////////////////////////////////////////////////////////
//                        Power and Root Functions                         //
// /////////////////////////////////////////////////////////////////////////

/**
 * @brief Computes the inverse square root (1/sqrt(val)).
 * @tparam T Floating-point type
 * @param val Input value
 * @return 1 / sqrt(val)
 */
template<typename T>
[[nodiscard]] inline T invSqrt(const T& val) {
    return static_cast<T>(1) / std::sqrt(val);
}

// ============================================================================
// Comparison Functions (relative epsilon for large values)
// ============================================================================

/**
 * @brief Checks whether two float values are "close enough" using relative epsilon.
 *
 * Uses: |val1 - val2| <= eps * max(1, |val1|, |val2|)
 * This comparison scales with the magnitude of the values.
 *
 * @param val1 First value
 * @param val2 Second value
 * @param eps Relative epsilon tolerance (default: kFloatEpsilon)
 * @return true if values are close enough
 */
[[nodiscard]] inline bool areSame(float val1, float val2, float eps = kFloatEpsilon) {
    return abs(val1 - val2) <= eps * max(1.0f, abs(val1), abs(val2));
}

/**
 * @brief Checks whether two double values are "close enough" using relative epsilon.
 */
[[nodiscard]] inline bool areSame(double val1, double val2, double eps = kDoubleEpsilon) {
    return abs(val1 - val2) <= eps * max(1.0, abs(val1), abs(val2));
}

/**
 * @brief Checks whether two int values are equal.
 */
[[nodiscard]] inline constexpr bool areSame(int val1, int val2, int /*eps*/ = 0) noexcept {
    return val1 == val2;
}

/**
 * @brief Checks whether two long int values are equal.
 */
[[nodiscard]] inline constexpr bool areSame(long int val1, long int val2, long int /*eps*/ = 0) noexcept {
    return val1 == val2;
}

/**
 * @brief Checks whether two unsigned int values are equal.
 */
[[nodiscard]] inline constexpr bool areSame(unsigned int val1, unsigned int val2, unsigned int /*eps*/ = 0) noexcept {
    return val1 == val2;
}

/**
 * @brief Checks whether two unsigned long values are equal.
 */
[[nodiscard]] inline constexpr bool areSame(unsigned long val1,
                                            unsigned long val2,
                                            unsigned long /*eps*/ = 0) noexcept {
    return val1 == val2;
}

/**
 * @brief Checks whether two char values are equal.
 */
[[nodiscard]] inline constexpr bool areSame(char val1, char val2, char /*eps*/ = 0) noexcept {
    return val1 == val2;
}

/**
 * @brief Checks whether two unsigned char values are equal.
 */
[[nodiscard]] inline constexpr bool areSame(unsigned char val1,
                                            unsigned char val2,
                                            unsigned char /*eps*/ = 0) noexcept {
    return val1 == val2;
}

////////////////////////////////////////////////////////////////////////////
//                             Midpoint                                    //
// /////////////////////////////////////////////////////////////////////////

/**
 * @brief Computes the midpoint of two integers.
 * @param a First value
 * @param b Second value
 * @return Midpoint value
 */
[[nodiscard]] inline int midPoint(const int a, const int b) {
    int direction = 1;
    unsigned int lo = static_cast<unsigned int>(a);
    unsigned int hi = static_cast<unsigned int>(b);

    if (a > b) {
        direction = -1;
        lo = static_cast<unsigned int>(b);
        hi = static_cast<unsigned int>(a);
    }

    return a + direction * static_cast<int>((hi - lo) / 2);
}

/**
 * @brief Computes the midpoint of two floats (overflow-safe).
 */
[[nodiscard]] inline float midPoint(const float a, const float b) {
    float lo = kFloatMin * 2;
    float hi = kFloatMax / 2;
    float abs_a = std::abs(a);
    float abs_b = std::abs(b);
    if (abs_a <= hi && abs_b <= hi) {
        return (a + b) / 2;
    }
    if (abs_a < lo) {
        return a + b / 2;
    }
    if (abs_b < lo) {
        return a / 2 + b;
    }
    return a / 2 + b / 2;
}

/**
 * @brief Computes the midpoint of two doubles (overflow-safe).
 */
[[nodiscard]] inline double midPoint(const double a, const double b) {
    double lo = kDoubleMin * 2;
    double hi = kDoubleMax / 2;
    double abs_a = std::abs(a);
    double abs_b = std::abs(b);
    if (abs_a <= hi && abs_b <= hi) {
        return (a + b) / 2;
    }
    if (abs_a < lo) {
        return a + b / 2;
    }
    if (abs_b < lo) {
        return a / 2 + b;
    }
    return a / 2 + b / 2;
}

// Note: lerp(a, b, t) and biLerp are defined in core/types.h

////////////////////////////////////////////////////////////////////////////
//               Nearest Integer floating point operations                 //
// /////////////////////////////////////////////////////////////////////////

template<typename T>
[[nodiscard]] inline T roundMultipleOf(T val, T multiple) {
    if (multiple == static_cast<T>(0)) {
        return std::round(val);
    }
    return T(multiple) * std::floor(val / T(multiple) + static_cast<T>(0.5));
}

////////////////////////////////////////////////////////////////////////////
//                  Exponential Functions                                 //
// /////////////////////////////////////////////////////////////////////////

[[nodiscard]] inline float logx(float x, float b) {
    return std::log(x) * (1.0f / std::log(b));
}

[[nodiscard]] inline double logx(double x, double b) {
    return std::log(x) * (1.0 / std::log(b));
}

[[nodiscard]] inline double logx(int x, int b) {
    return std::log(static_cast<double>(x)) * (1.0 / std::log(static_cast<double>(b)));
}

[[nodiscard]] inline double logx(float x, int b) {
    return std::log(static_cast<double>(x)) * (1.0 / std::log(static_cast<double>(b)));
}

[[nodiscard]] inline double logx(double x, int b) {
    return std::log(x) * (1.0 / std::log(static_cast<double>(b)));
}

// ============================================================================
// Angle Utilities
// ============================================================================

/**
 * @brief Normalizes an angle to the range [0, 2π).
 *
 * @param radians Angle in radians
 * @return Normalized angle in [0, 2π)
 */
template<FloatingPoint T>
[[nodiscard]] inline T normalizeAngle(T radians) noexcept {
    radians = std::fmod(radians, kTwoPiT<T>);
    if (radians < T(0)) {
        radians += kTwoPiT<T>;
    }
    return radians;
}

/**
 * @brief Normalizes an angle to the range [-π, π].
 *
 * @param radians Angle in radians
 * @return Normalized angle in [-π, π]
 */
template<FloatingPoint T>
[[nodiscard]] inline T normalizeAngleSigned(T radians) noexcept {
    radians = std::fmod(radians + kPiT<T>, kTwoPiT<T>);
    if (radians < T(0)) {
        radians += kTwoPiT<T>;
    }
    return radians - kPiT<T>;
}

/**
 * @brief Computes the shortest angular difference between two angles.
 *
 * The result is in the range [-π, π], representing the shortest
 * path from 'from' to 'to'.
 *
 * @param from Starting angle in radians
 * @param to Target angle in radians
 * @return Shortest difference in radians (can be negative)
 */
template<FloatingPoint T>
[[nodiscard]] inline T angleDifference(T from, T to) noexcept {
    T diff = std::fmod(to - from + kPiT<T>, kTwoPiT<T>);
    if (diff < T(0)) {
        diff += kTwoPiT<T>;
    }
    return diff - kPiT<T>;
}

/**
 * @brief Linearly interpolates between two angles, handling wraparound.
 *
 * Takes the shortest path around the circle.
 *
 * @param a Starting angle in radians
 * @param b Target angle in radians
 * @param t Interpolation factor [0, 1]
 * @return Interpolated angle in radians
 */
template<FloatingPoint T>
[[nodiscard]] inline T lerpAngle(T a, T b, T t) noexcept {
    T diff = angleDifference(a, b);
    return a + diff * t;
}

/**
 * @brief Wraps a value to a range [min, max).
 *
 * @param value Value to wrap
 * @param min_val Minimum of range
 * @param max_val Maximum of range (exclusive)
 * @return Wrapped value
 */
template<FloatingPoint T>
[[nodiscard]] inline T wrap(T value, T min_val, T max_val) noexcept {
    T range = max_val - min_val;
    T result = std::fmod(value - min_val, range);
    if (result < T(0)) {
        result += range;
    }
    return result + min_val;
}

/**
 * @brief Maps a value from one range to another.
 *
 * @param value Input value
 * @param in_min Input range minimum
 * @param in_max Input range maximum
 * @param out_min Output range minimum
 * @param out_max Output range maximum
 * @return Mapped value
 */
template<FloatingPoint T>
[[nodiscard]] constexpr T remap(T value, T in_min, T in_max, T out_min, T out_max) noexcept {
    return out_min + (value - in_min) * (out_max - out_min) / (in_max - in_min);
}

/**
 * @brief Inverse lerp: finds t such that lerp(a, b, t) = value.
 *
 * @param a Start value
 * @param b End value
 * @param value Value between a and b
 * @return The t parameter in [0, 1] (or outside if value is outside [a, b])
 */
template<FloatingPoint T>
[[nodiscard]] constexpr T inverseLerp(T a, T b, T value) noexcept {
    if (approxEqual(a, b)) {
        return T(0);
    }
    return (value - a) / (b - a);
}

/**
 * @brief Step function: returns 0 if x < edge, 1 otherwise.
 */
template<FloatingPoint T>
[[nodiscard]] constexpr T step(T edge, T x) noexcept {
    return x < edge ? T(0) : T(1);
}

/**
 * @brief Fractional part of a number (x - floor(x)).
 */
template<FloatingPoint T>
[[nodiscard]] inline T fract(T x) noexcept {
    return x - std::floor(x);
}

/**
 * @brief Modulo that works correctly for negative numbers.
 *
 * Unlike std::fmod, this always returns a positive result
 * when the divisor is positive.
 */
template<FloatingPoint T>
[[nodiscard]] inline T mod(T x, T y) noexcept {
    return x - y * std::floor(x / y);
}

}  // namespace vne::math

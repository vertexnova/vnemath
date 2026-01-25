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
 * @brief Provides extended mathematical utilities.
 *
 * This file contains:
 * - Additional templated math constants (kQuarterPiT)
 * - Legacy constant accessor functions (quarterPi(), etc.) for backward compatibility
 * - Power and root functions (pow, sqrt, invSqrt)
 * - Midpoint calculation
 * - Rounding functions (floor, ceil, trunc, round)
 * - Classification functions (isNaN, isInf, isNormal, isFinite)
 * - Exponential and logarithmic functions
 * - Trigonometric and hyperbolic functions
 *
 * Core templated utilities (abs, min, max, clamp, lerp, isZero, etc.)
 * are in core/types.h as they're required by the templated vec/mat/quat classes.
 *
 * For non-templated constants, use constants.h
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

// ============================================================================
// Legacy Constant Accessor Functions (for backward compatibility)
// ============================================================================

/**
 * @brief Returns the constant π/4 (pi over four) for the given type.
 * @deprecated Use kQuarterPiT<T> template constant instead.
 */
template<typename T>
[[nodiscard]] inline constexpr T quarterPi() noexcept;

template<>
[[nodiscard]] inline constexpr float quarterPi<float>() noexcept {
    return kQuarterPi;
}

template<>
[[nodiscard]] inline constexpr double quarterPi<double>() noexcept {
    return kQuarterPiDouble;
}

////////////////////////////////////////////////////////////////////////////
//                        Power and Root Functions                         //
// /////////////////////////////////////////////////////////////////////////

/**
 * @brief Computes the value of base raised to power exponent.
 * @tparam T Arithmetic type
 * @param base The base value
 * @param exponent The exponent
 * @return base^exponent
 */
template<typename T>
[[nodiscard]] inline T pow(const T& base, T exponent) {
    return std::pow(base, exponent);
}

/**
 * @brief Computes the square root of a value.
 * @tparam T Floating-point type
 * @param val Input value
 * @return Square root of val
 */
template<typename T>
[[nodiscard]] inline T sqrt(const T& val) {
    return std::sqrt(val);
}

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
[[nodiscard]] inline T floor(T val) {
    return std::floor(val);
}

template<typename T>
[[nodiscard]] inline T ceil(T val) {
    return std::ceil(val);
}

template<typename T>
[[nodiscard]] inline T trunc(T val) {
    return std::trunc(val);
}

template<typename T>
[[nodiscard]] inline T round(T val) {
    return std::round(val);
}

template<typename T>
[[nodiscard]] inline T roundMultipleOf(T val, T multiple) {
    if (multiple == static_cast<T>(0)) {
        return std::round(val);
    }
    return T(multiple) * std::floor(val / T(multiple) + static_cast<T>(0.5));
}

constexpr inline int floatToInt(float val) {
    return static_cast<int>(val);
}

[[nodiscard]] inline float modf(float x, float* iptr) {
    return std::modf(x, iptr);
}

[[nodiscard]] inline double modf(double x, double* iptr) {
    return std::modf(x, iptr);
}

////////////////////////////////////////////////////////////////////////////
//               Classification and comparison                            //
// /////////////////////////////////////////////////////////////////////////

[[nodiscard]] inline bool isNaN(float x) {
    return std::isnan(x);
}

[[nodiscard]] inline bool isNaN(double x) {
    return std::isnan(x);
}

[[nodiscard]] inline bool isInf(float x) {
    return std::isinf(x);
}

[[nodiscard]] inline bool isInf(double x) {
    return std::isinf(x);
}

[[nodiscard]] inline bool isNormal(float x) {
    return std::isnormal(x);
}

[[nodiscard]] inline bool isNormal(double x) {
    return std::isnormal(x);
}

[[nodiscard]] inline bool isFinite(float x) {
    return std::isfinite(x);
}

[[nodiscard]] inline bool isFinite(double x) {
    return std::isfinite(x);
}

////////////////////////////////////////////////////////////////////////////
//                  Exponential Functions                                 //
// /////////////////////////////////////////////////////////////////////////

[[nodiscard]] inline float exp(float x) {
    return std::exp(x);
}

[[nodiscard]] inline double exp(double x) {
    return std::exp(x);
}

[[nodiscard]] inline double exp(int x) {
    return std::exp(static_cast<double>(x));
}

[[nodiscard]] inline float log(float x) {
    return std::log(x);
}

[[nodiscard]] inline double log(double x) {
    return std::log(x);
}

[[nodiscard]] inline double log(int x) {
    return std::log(static_cast<double>(x));
}

[[nodiscard]] inline float log2(float x) {
    return std::log2(x);
}

[[nodiscard]] inline double log2(double x) {
    return std::log2(x);
}

[[nodiscard]] inline double log2(int x) {
    return std::log2(static_cast<double>(x));
}

[[nodiscard]] inline float log10(float x) {
    return std::log10(x);
}

[[nodiscard]] inline double log10(double x) {
    return std::log10(x);
}

[[nodiscard]] inline double log10(int x) {
    return std::log10(static_cast<double>(x));
}

[[nodiscard]] inline float logx(float x, float b) {
    return log(x) * (1.0f / log(b));
}

[[nodiscard]] inline double logx(double x, double b) {
    return log(x) * (1.0 / log(b));
}

[[nodiscard]] inline double logx(int x, int b) {
    return log(static_cast<double>(x)) * (1.0 / log(static_cast<double>(b)));
}

[[nodiscard]] inline double logx(float x, int b) {
    return log(static_cast<double>(x)) * (1.0 / log(static_cast<double>(b)));
}

[[nodiscard]] inline double logx(double x, int b) {
    return log(x) * (1.0 / log(static_cast<double>(b)));
}

////////////////////////////////////////////////////////////////////////////
//               Trigonometric and hyperbolic functions                    //
// /////////////////////////////////////////////////////////////////////////

[[nodiscard]] inline float sin(float x) {
    return std::sin(x);
}

[[nodiscard]] inline double sin(double x) {
    return std::sin(x);
}

[[nodiscard]] inline double sin(int x) {
    return std::sin(static_cast<double>(x));
}

[[nodiscard]] inline float asin(float x) {
    return std::asin(x);
}

[[nodiscard]] inline double asin(double x) {
    return std::asin(x);
}

[[nodiscard]] inline double asin(int x) {
    return std::asin(static_cast<double>(x));
}

[[nodiscard]] inline float sinh(float x) {
    return std::sinh(x);
}

[[nodiscard]] inline double sinh(double x) {
    return std::sinh(x);
}

[[nodiscard]] inline double sinh(int x) {
    return std::sinh(static_cast<double>(x));
}

[[nodiscard]] inline float cos(float x) {
    return std::cos(x);
}

[[nodiscard]] inline double cos(double x) {
    return std::cos(x);
}

[[nodiscard]] inline double cos(int x) {
    return std::cos(static_cast<double>(x));
}

[[nodiscard]] inline float acos(float x) {
    return std::acos(x);
}

[[nodiscard]] inline double acos(double x) {
    return std::acos(x);
}

[[nodiscard]] inline double acos(int x) {
    return std::acos(static_cast<double>(x));
}

[[nodiscard]] inline float cosh(float x) {
    return std::cosh(x);
}

[[nodiscard]] inline double cosh(double x) {
    return std::cosh(x);
}

[[nodiscard]] inline double cosh(int x) {
    return std::cosh(static_cast<double>(x));
}

inline void sinCos(float x, float& sin_val, float& cos_val) {
    sin_val = std::sin(x);
    cos_val = std::cos(x);
}

inline void sinCos(double x, double& sin_val, double& cos_val) {
    sin_val = std::sin(x);
    cos_val = std::cos(x);
}

inline void sinCos(int x, double& sin_val, double& cos_val) {
    sin_val = std::sin(static_cast<double>(x));
    cos_val = std::cos(static_cast<double>(x));
}

[[nodiscard]] inline float tan(float x) {
    return std::tan(x);
}

[[nodiscard]] inline double tan(double x) {
    return std::tan(x);
}

[[nodiscard]] inline double tan(int x) {
    return std::tan(static_cast<double>(x));
}

[[nodiscard]] inline float atan(float x) {
    return std::atan(x);
}

[[nodiscard]] inline double atan(double x) {
    return std::atan(x);
}

[[nodiscard]] inline double atan(int x) {
    return std::atan(static_cast<double>(x));
}

[[nodiscard]] inline float atan2(float y, float x) {
    return std::atan2(y, x);
}

[[nodiscard]] inline double atan2(double y, double x) {
    return std::atan2(y, x);
}

[[nodiscard]] inline double atan2(int y, int x) {
    return std::atan2(static_cast<double>(y), static_cast<double>(x));
}

[[nodiscard]] inline float tanh(float x) {
    return std::tanh(x);
}

[[nodiscard]] inline double tanh(double x) {
    return std::tanh(x);
}

[[nodiscard]] inline double tanh(int x) {
    return std::tanh(static_cast<double>(x));
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

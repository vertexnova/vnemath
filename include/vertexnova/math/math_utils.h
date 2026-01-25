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
 * @brief Provides a collection of mathematical utilities.
 *
 * This file contains:
 * - Additional templated math constants (kQuarterPiT)
 * - Legacy constant accessor functions (quarterPi(), etc.) for backward compatibility
 * - Basic math operations (min, max, abs, sign, sqrt)
 * - Robust comparison functions (areSame, isZero) using relative epsilon
 * - Interpolation functions (saturate, midPoint, biLerp)
 * - Exponential, power, and trigonometric functions
 *
 * Comparison function notes:
 * - areSame/isZero: Use relative epsilon - better for large values
 * - approxEqual/approxZero (in types.h): Use absolute epsilon - better for small values
 *
 * Core utilities (clamp, lerp, approxEqual, degToRad) are in core/types.h
 * as they're required by the templated vec/mat/quat classes.
 *
 * For non-templated constants, use constants.h
 */

// Project includes
#include "constants.h"
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
//                        Basic Operations                                 //
// /////////////////////////////////////////////////////////////////////////

/**
 * Computes the absolute value of the input value.
 */
template<typename T>
[[nodiscard]] inline constexpr T abs(const T& val) {
    return std::abs(val);
}

/**
 * Computes the sign value of the given input value.
 */
template<typename T>
[[nodiscard]] inline constexpr T sign(const T& val, T eps = static_cast<T>(0)) {
    return (val > eps ? static_cast<T>(1) : (val < eps ? static_cast<T>(-1) : static_cast<T>(0)));
}

/**
 * Returns the minimum of the two given values
 */
template<typename T>
[[nodiscard]] inline constexpr T min(const T& val1, const T& val2) {
    return val1 <= val2 ? val1 : val2;
}

/**
 * Returns the maximum of the two given values
 */
template<typename T>
[[nodiscard]] inline constexpr T max(const T& val1, const T& val2) {
    return val1 >= val2 ? val1 : val2;
}

/**
 * Returns the minimum of the three given values
 */
template<typename T>
[[nodiscard]] inline constexpr T min(const T& val1, const T& val2, const T& val3) {
    return min(min(val1, val2), val3);
}

/**
 * Returns the maximum of the three given values
 */
template<typename T>
[[nodiscard]] inline constexpr T max(const T& val1, const T& val2, const T& val3) {
    return max(max(val1, val2), val3);
}

/**
 * Clamps a value between 0 and 1.
 */
template<typename T>
[[nodiscard]] inline constexpr T saturate(const T& val) {
    return clamp<T>(val, static_cast<T>(0), static_cast<T>(1));
}

/**
 * Sorts parameters val1 and val2 in the ascending order.
 */
template<typename T>
inline void arrangeMinMax(T* val1, T* val2) {
    if (*val1 > *val2) {
        std::swap(*val1, *val2);
    }
}

/**
 * Checks if the given value is lying in an interval [min, max].
 */
template<typename T>
[[nodiscard]] inline bool isInBetween(T val, T min_val, T max_val, T eps = static_cast<T>(0)) {
    arrangeMinMax(&min_val, &max_val);
    return val >= min_val - eps && val <= max_val + eps;
}

/**
 * Computes the square of the given input.
 */
template<typename T>
[[nodiscard]] inline constexpr T square(const T& val) {
    return val * val;
}

/**
 * Computes the cube of the given input.
 */
template<typename T>
[[nodiscard]] inline constexpr T cube(const T& val) {
    return val * val * val;
}

/**
 * Computes the value of the base raised to power exponent.
 */
template<typename T>
[[nodiscard]] inline constexpr T pow(const T& base, T exponent) {
    return std::pow(base, exponent);
}

/**
 * Computes the square root of the given value.
 */
template<typename T>
[[nodiscard]] inline constexpr T sqrt(const T& val) {
    return std::sqrt(val);
}

/**
 * Computes the inverse of the square root of the given value.
 */
template<typename T>
[[nodiscard]] inline constexpr T invSqrt(const T& val) {
    return static_cast<T>(1) / std::sqrt(val);
}

// ============================================================================
// Robust Comparison Functions (Relative Epsilon)
// ============================================================================

/**
 * @brief Checks whether two values are "close enough" using relative epsilon.
 *
 * For floating-point types, uses: |val1 - val2| <= eps * max(1, |val1|, |val2|)
 * This makes the comparison scale with the magnitude of the values,
 * which is more appropriate for large numbers.
 *
 * For integral types, uses exact equality (eps is ignored).
 *
 * @note For small values near zero (0-1 range), approxEqual() from types.h
 *       may be more appropriate as it uses absolute epsilon.
 *
 * @tparam T Value type
 * @param val1 First value
 * @param val2 Second value
 * @param eps Relative epsilon tolerance
 * @return true if values are close enough
 *
 * @see approxEqual() in types.h for absolute epsilon comparison
 */
template<typename T>
[[nodiscard]] inline constexpr bool areSameImpl(const T& val1, const T& val2, T eps) {
    VNE_UNUSED(eps);
    return val1 == val2;
}

template<>
[[nodiscard]] inline bool areSameImpl(const float& val1, const float& val2, float eps) {
    VNE_ASSERT_MSG(eps >= kFloatEpsilon, "eps cannot be less than kFloatEpsilon.");
    return abs<float>(val1 - val2) <= eps * max<float>(1.0f, abs<float>(val1), abs<float>(val2));
}

template<>
[[nodiscard]] inline bool areSameImpl(const double& val1, const double& val2, double eps) {
    VNE_ASSERT_MSG(eps >= kDoubleEpsilon, "eps cannot be less than kDoubleEpsilon.");
    return abs<double>(val1 - val2) <= eps * max<double>(1.0, abs<double>(val1), abs<double>(val2));
}

[[nodiscard]] inline bool areSame(float val1, float val2, float eps = kFloatEpsilon) {
    return areSameImpl<float>(val1, val2, eps);
}

[[nodiscard]] inline bool areSame(double val1, double val2, double eps = kDoubleEpsilon) {
    return areSameImpl<double>(val1, val2, eps);
}

[[nodiscard]] inline constexpr bool areSame(int val1, int val2, int eps = 0) {
    return areSameImpl<int>(val1, val2, eps);
}

[[nodiscard]] inline constexpr bool areSame(long int val1, long int val2, long int eps = 0) {
    return areSameImpl<long int>(val1, val2, eps);
}

[[nodiscard]] inline constexpr bool areSame(unsigned int val1, unsigned int val2, unsigned int eps = 0) {
    return areSameImpl<unsigned int>(val1, val2, eps);
}

[[nodiscard]] inline constexpr bool areSame(unsigned long val1, unsigned long val2, unsigned long eps = 0) {
    return areSameImpl<unsigned long>(val1, val2, eps);
}

[[nodiscard]] inline constexpr bool areSame(char val1, char val2, char eps = 0) {
    return areSameImpl<char>(val1, val2, eps);
}

[[nodiscard]] inline constexpr bool areSame(unsigned char val1, unsigned char val2, unsigned char eps = 0) {
    return areSameImpl<unsigned char>(val1, val2, eps);
}

/**
 * @brief Checks whether the given value is "close enough" to zero using relative epsilon.
 *
 * For floating-point types, uses: |val| < eps * max(1, |val|)
 * This is the zero-check counterpart to areSame().
 *
 * For integral types, uses exact comparison with zero (eps is ignored).
 *
 * @note For small values, approxZero() from types.h may be more appropriate
 *       as it uses absolute epsilon.
 *
 * @tparam T Value type
 * @param val The value to check
 * @param eps Relative epsilon tolerance
 * @return true if value is close enough to zero
 *
 * @see approxZero() in types.h for absolute epsilon comparison
 */
template<typename T>
[[nodiscard]] inline constexpr bool isZeroImpl(const T& val, T eps = static_cast<T>(0)) {
    VNE_UNUSED(eps);
    return val == T(0);
}

template<>
[[nodiscard]] inline bool isZeroImpl(const float& val, float eps) {
    VNE_ASSERT_MSG(eps >= kFloatEpsilon, "eps cannot be less than kFloatEpsilon.");
    return abs<float>(val) < eps * max<float>(1.0f, abs<float>(val));
}

template<>
[[nodiscard]] inline bool isZeroImpl(const double& val, double eps) {
    VNE_ASSERT_MSG(eps >= kDoubleEpsilon, "eps cannot be less than kDoubleEpsilon.");
    return abs<double>(val) < eps * max<double>(1.0, abs<double>(val));
}

[[nodiscard]] inline bool isZero(float val, float eps = kFloatEpsilon) {
    return isZeroImpl<float>(val, eps);
}

[[nodiscard]] inline bool isZero(double val, double eps = kDoubleEpsilon) {
    return isZeroImpl<double>(val, eps);
}

[[nodiscard]] inline constexpr bool isZero(int val, int eps = 0) {
    return isZeroImpl<int>(val, eps);
}

[[nodiscard]] inline constexpr bool isZero(unsigned int val, unsigned int eps = 0) {
    return isZeroImpl<unsigned int>(val, eps);
}

[[nodiscard]] inline constexpr bool isZero(long int val, long int eps = 0) {
    return isZeroImpl<long int>(val, eps);
}

[[nodiscard]] inline constexpr bool isZero(unsigned long val, unsigned long eps = 0) {
    return isZeroImpl<unsigned long>(val, eps);
}

////////////////////////////////////////////////////////////////////////////
//                             Interpolations                              //
// /////////////////////////////////////////////////////////////////////////

/**
 * Computes the midpoint of the integers, floating-points, or pointers a and b.
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

// Note: lerp(a, b, t) is defined in core/types.h

/**
 * @brief BiLinear interpolation.
 *
 * Interpolates between four corner values using two interpolation factors.
 * Uses lerp from types.h internally.
 *
 * @tparam T Floating-point type for values
 * @param c00 Value at (0, 0)
 * @param c10 Value at (1, 0)
 * @param c01 Value at (0, 1)
 * @param c11 Value at (1, 1)
 * @param tx Interpolation factor in x direction [0, 1]
 * @param ty Interpolation factor in y direction [0, 1]
 * @return Bilinearly interpolated value
 */
template<FloatingPoint T>
[[nodiscard]] inline constexpr T biLerp(
    const T& c00, const T& c10, const T& c01, const T& c11, const T& tx, const T& ty) {
    T a = lerp(c00, c10, tx);
    T b = lerp(c01, c11, tx);
    return lerp(a, b, ty);
}

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

}  // namespace vne::math

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
 * @brief Provides a collection of mathematical utilities, including basic
 * operations, interpolations, exponential functions, power functions, and
 * trigonometric functions.
 */

// Project includes
#include "constants.h"
#include "vertexnova/common/macros.h"

// System library includes
#include <cmath>

namespace vne::math {

/**
 * @brief Returns the constant π (pi) for the given type.
 *
 * @return Value of π
 */
template<typename T>
[[nodiscard]] inline constexpr T pi() noexcept;

template<>
[[nodiscard]] inline constexpr float pi<float>() noexcept {
    return kPi;
}

template<>
[[nodiscard]] inline constexpr double pi<double>() noexcept {
    return static_cast<double>(PI);
}

/**
 * @brief Returns the constant 2π (two pi) for the given type.
 *
 * @return Value of 2π
 */
template<typename T>
[[nodiscard]] inline constexpr T twoPi() noexcept;

template<>
[[nodiscard]] inline constexpr float twoPi<float>() noexcept {
    return kTwoPi;
}

template<>
[[nodiscard]] inline constexpr double twoPi<double>() noexcept {
    return static_cast<double>(TWO_PI);
}

/**
 * @brief Returns the constant π/2 (pi over two) for the given type.
 *
 * @return Value of π/2
 */
template<typename T>
[[nodiscard]] inline constexpr T halfPi() noexcept;

template<>
[[nodiscard]] inline constexpr float halfPi<float>() noexcept {
    return kHalfPi;
}

template<>
[[nodiscard]] inline constexpr double halfPi<double>() noexcept {
    return static_cast<double>(HALF_PI);
}

/**
 * @brief Returns the constant π/4 (pi over four) for the given type.
 *
 * @return Value of π/4
 */
template<typename T>
[[nodiscard]] inline constexpr T quarterPi() noexcept;

template<>
[[nodiscard]] inline constexpr float quarterPi<float>() noexcept {
    return kQuarterPi;
}

template<>
[[nodiscard]] inline constexpr double quarterPi<double>() noexcept {
    return static_cast<double>(QUARTER_PI);
}

/**
 * @brief Returns the constant 1/π (one over pi) for the given type.
 *
 * @return Value of 1/π
 */
template<typename T>
[[nodiscard]] inline constexpr T oneOverPi() noexcept;

template<>
[[nodiscard]] inline constexpr float oneOverPi<float>() noexcept {
    return kOneOverPi;
}

template<>
[[nodiscard]] inline constexpr double oneOverPi<double>() noexcept {
    return static_cast<double>(ONE_OVER_PI);
}

/**
 * @brief Returns the constant 1/(2π) (one over two pi) for the given type.
 *
 * @return Value of 1/(2π)
 */
template<typename T>
[[nodiscard]] inline constexpr T oneOverTwoPi() noexcept;

template<>
[[nodiscard]] inline constexpr float oneOverTwoPi<float>() noexcept {
    return kOneOverTwoPi;
}

template<>
[[nodiscard]] inline constexpr double oneOverTwoPi<double>() noexcept {
    return static_cast<double>(ONE_OVER_TWO_PI);
}

/**
 * @brief Converts radians to degrees.
 *
 * @param angle Angle in radians.
 * @return Angle in degrees.
 */
template<typename T>
[[nodiscard]] inline constexpr T radToDeg(const T& angle) noexcept {
    return angle * (static_cast<T>(180) * oneOverPi<T>());
}

/**
 * @brief Converts degrees to radians.
 *
 * @param angle Angle in degrees.
 * @return Angle in radians.
 */
template<typename T>
[[nodiscard]] inline constexpr T degToRad(const T& angle) noexcept {
    return angle * (pi<T>() / static_cast<T>(180));
}

/**
 * @brief Returns the epsilon value for the given type.
 *
 * @return Epsilon value.
 */
template<typename T>
[[nodiscard]] inline constexpr T getEps() noexcept {
    return static_cast<T>(0);
}

template<>
[[nodiscard]] inline constexpr float getEps<float>() noexcept {
    return kFloatEpsilon;
}

template<>
[[nodiscard]] inline constexpr double getEps<double>() noexcept {
    return kDoubleEpsilon;
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
 * Clamps a value between a pair of boundary values.
 */
template<typename T>
[[nodiscard]] inline constexpr T clamp(const T& val, const T& lower, const T& upper) {
    return min(upper, max(val, lower));
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

/**
 * Checks whether two values are "close enough" to one another.
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
 * Checks whether the given value is "close enough" to zero.
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

/**
 * Linear interpolation
 */
template<typename T, typename U>
[[nodiscard]] inline constexpr T lerp(const T& a, const T& b, const U& t) {
    if ((a <= static_cast<T>(0) && b >= static_cast<T>(0)) || (a >= static_cast<T>(0) && b <= static_cast<T>(0))) {
        return a * static_cast<T>(1 - t) + b * static_cast<T>(t);
    }
    if (t == static_cast<U>(1)) {
        return b;
    }
    const T x = a + static_cast<T>(t * (b - a));
    return (t > static_cast<U>(1)) == (b > a) ? std::max(b, x) : std::min(b, x);
}

/**
 * BiLinear interpolation
 */
template<typename T, typename U>
[[nodiscard]] inline constexpr T biLerp(const T& c00, const T& c10, const T& c01, const T& c11, const U& tx, const U& ty) {
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

// Legacy namespace aliases for backward compatibility
namespace VNE {
namespace Math {

// Constants
constexpr float FLOAT_EPSILON = vne::math::kFloatEpsilon;
constexpr double DOUBLE_EPSILON = vne::math::kDoubleEpsilon;
constexpr float FLOAT_MIN = vne::math::kFloatMin;
constexpr double DOUBLE_MIN = vne::math::kDoubleMin;
constexpr float FLOAT_MAX = vne::math::kFloatMax;
constexpr double DOUBLE_MAX = vne::math::kDoubleMax;

// Template functions
template<typename T>
[[nodiscard]] inline constexpr T Pi() noexcept {
    return vne::math::pi<T>();
}
template<typename T>
[[nodiscard]] inline constexpr T TwoPi() noexcept {
    return vne::math::twoPi<T>();
}
template<typename T>
[[nodiscard]] inline constexpr T HalfPi() noexcept {
    return vne::math::halfPi<T>();
}
template<typename T>
[[nodiscard]] inline constexpr T QuarterPi() noexcept {
    return vne::math::quarterPi<T>();
}
template<typename T>
[[nodiscard]] inline constexpr T OneOverPi() noexcept {
    return vne::math::oneOverPi<T>();
}
template<typename T>
[[nodiscard]] inline constexpr T OneOverTwoPi() noexcept {
    return vne::math::oneOverTwoPi<T>();
}
template<typename T>
[[nodiscard]] inline constexpr T RadToDeg(const T& angle) noexcept {
    return vne::math::radToDeg(angle);
}
template<typename T>
[[nodiscard]] inline constexpr T DegToRad(const T& angle) noexcept {
    return vne::math::degToRad(angle);
}
template<typename T>
[[nodiscard]] inline constexpr T GetEps() noexcept {
    return vne::math::getEps<T>();
}

// Basic operations
template<typename T>
[[nodiscard]] inline constexpr T Abs(const T& val) {
    return vne::math::abs(val);
}
template<typename T>
[[nodiscard]] inline constexpr T Sign(const T& val, T eps = static_cast<T>(0)) {
    return vne::math::sign(val, eps);
}
template<typename T>
[[nodiscard]] inline constexpr T Min(const T& val1, const T& val2) {
    return vne::math::min(val1, val2);
}
template<typename T>
[[nodiscard]] inline constexpr T Max(const T& val1, const T& val2) {
    return vne::math::max(val1, val2);
}
template<typename T>
[[nodiscard]] inline constexpr T Min(const T& val1, const T& val2, const T& val3) {
    return vne::math::min(val1, val2, val3);
}
template<typename T>
[[nodiscard]] inline constexpr T Max(const T& val1, const T& val2, const T& val3) {
    return vne::math::max(val1, val2, val3);
}
template<typename T>
[[nodiscard]] inline constexpr T Clamp(const T& val, const T& lower, const T& upper) {
    return vne::math::clamp(val, lower, upper);
}
template<typename T>
[[nodiscard]] inline constexpr T Saturate(const T& val) {
    return vne::math::saturate(val);
}
template<typename T>
inline void ArrangeMinMax(T* val1, T* val2) {
    vne::math::arrangeMinMax(val1, val2);
}
template<typename T>
[[nodiscard]] inline bool IsInBetween(T val, T min_val, T max_val, T eps = static_cast<T>(0)) {
    return vne::math::isInBetween(val, min_val, max_val, eps);
}
template<typename T>
[[nodiscard]] inline constexpr T Square(const T& val) {
    return vne::math::square(val);
}
template<typename T>
[[nodiscard]] inline constexpr T Cube(const T& val) {
    return vne::math::cube(val);
}
template<typename T>
[[nodiscard]] inline constexpr T Pow(const T& base, T exponent) {
    return vne::math::pow(base, exponent);
}
template<typename T>
[[nodiscard]] inline constexpr T Sqrt(const T& val) {
    return vne::math::sqrt(val);
}
template<typename T>
[[nodiscard]] inline constexpr T InvSqrt(const T& val) {
    return vne::math::invSqrt(val);
}

// AreSame and IsZero
[[nodiscard]] inline bool AreSame(float val1, float val2, float eps = FLOAT_EPSILON) {
    return vne::math::areSame(val1, val2, eps);
}
[[nodiscard]] inline bool AreSame(double val1, double val2, double eps = DOUBLE_EPSILON) {
    return vne::math::areSame(val1, val2, eps);
}
[[nodiscard]] inline constexpr bool AreSame(int val1, int val2, int eps = 0) {
    return vne::math::areSame(val1, val2, eps);
}
[[nodiscard]] inline bool IsZero(float val, float eps = FLOAT_EPSILON) {
    return vne::math::isZero(val, eps);
}
[[nodiscard]] inline bool IsZero(double val, double eps = DOUBLE_EPSILON) {
    return vne::math::isZero(val, eps);
}
[[nodiscard]] inline constexpr bool IsZero(int val, int eps = 0) {
    return vne::math::isZero(val, eps);
}

// Interpolation
[[nodiscard]] inline int MidPoint(const int a, const int b) {
    return vne::math::midPoint(a, b);
}
[[nodiscard]] inline float MidPoint(const float a, const float b) {
    return vne::math::midPoint(a, b);
}
[[nodiscard]] inline double MidPoint(const double a, const double b) {
    return vne::math::midPoint(a, b);
}
template<typename T, typename U>
[[nodiscard]] inline constexpr T Lerp(const T& a, const T& b, const U& t) {
    return vne::math::lerp(a, b, t);
}
template<typename T, typename U>
[[nodiscard]] inline constexpr T BiLerp(const T& c00, const T& c10, const T& c01, const T& c11, const U& tx, const U& ty) {
    return vne::math::biLerp(c00, c10, c01, c11, tx, ty);
}

// Rounding
template<typename T>
[[nodiscard]] inline T Floor(T val) {
    return vne::math::floor(val);
}
template<typename T>
[[nodiscard]] inline T Ceil(T val) {
    return vne::math::ceil(val);
}
template<typename T>
[[nodiscard]] inline T Trunc(T val) {
    return vne::math::trunc(val);
}
template<typename T>
[[nodiscard]] inline T Round(T val) {
    return vne::math::round(val);
}
template<typename T>
[[nodiscard]] inline T RoundMultipleOf(T val, T multiple) {
    return vne::math::roundMultipleOf(val, multiple);
}
constexpr inline int FloatToInt(float val) {
    return vne::math::floatToInt(val);
}
[[nodiscard]] inline float Modf(float x, float* iptr) {
    return vne::math::modf(x, iptr);
}
[[nodiscard]] inline double Modf(double x, double* iptr) {
    return vne::math::modf(x, iptr);
}

// Classification
[[nodiscard]] inline bool IsNaN(float x) {
    return vne::math::isNaN(x);
}
[[nodiscard]] inline bool IsNaN(double x) {
    return vne::math::isNaN(x);
}
[[nodiscard]] inline bool IsInf(float x) {
    return vne::math::isInf(x);
}
[[nodiscard]] inline bool IsInf(double x) {
    return vne::math::isInf(x);
}
[[nodiscard]] inline bool IsNormal(float x) {
    return vne::math::isNormal(x);
}
[[nodiscard]] inline bool IsNormal(double x) {
    return vne::math::isNormal(x);
}
[[nodiscard]] inline bool IsFinite(float x) {
    return vne::math::isFinite(x);
}
[[nodiscard]] inline bool IsFinite(double x) {
    return vne::math::isFinite(x);
}

// Exponential
[[nodiscard]] inline float Exp(float x) {
    return vne::math::exp(x);
}
[[nodiscard]] inline double Exp(double x) {
    return vne::math::exp(x);
}
[[nodiscard]] inline double Exp(int x) {
    return vne::math::exp(x);
}
[[nodiscard]] inline float Log(float x) {
    return vne::math::log(x);
}
[[nodiscard]] inline double Log(double x) {
    return vne::math::log(x);
}
[[nodiscard]] inline double Log(int x) {
    return vne::math::log(x);
}
[[nodiscard]] inline float Log2(float x) {
    return vne::math::log2(x);
}
[[nodiscard]] inline double Log2(double x) {
    return vne::math::log2(x);
}
[[nodiscard]] inline double Log2(int x) {
    return vne::math::log2(x);
}
[[nodiscard]] inline float Log10(float x) {
    return vne::math::log10(x);
}
[[nodiscard]] inline double Log10(double x) {
    return vne::math::log10(x);
}
[[nodiscard]] inline double Log10(int x) {
    return vne::math::log10(x);
}
[[nodiscard]] inline float Logx(float x, float b) {
    return vne::math::logx(x, b);
}
[[nodiscard]] inline double Logx(double x, double b) {
    return vne::math::logx(x, b);
}

// Trigonometric
[[nodiscard]] inline float Sin(float x) {
    return vne::math::sin(x);
}
[[nodiscard]] inline double Sin(double x) {
    return vne::math::sin(x);
}
[[nodiscard]] inline double Sin(int x) {
    return vne::math::sin(x);
}
[[nodiscard]] inline float ASin(float x) {
    return vne::math::asin(x);
}
[[nodiscard]] inline double ASin(double x) {
    return vne::math::asin(x);
}
[[nodiscard]] inline float Sinh(float x) {
    return vne::math::sinh(x);
}
[[nodiscard]] inline double Sinh(double x) {
    return vne::math::sinh(x);
}
[[nodiscard]] inline float Cos(float x) {
    return vne::math::cos(x);
}
[[nodiscard]] inline double Cos(double x) {
    return vne::math::cos(x);
}
[[nodiscard]] inline double Cos(int x) {
    return vne::math::cos(x);
}
[[nodiscard]] inline float ACos(float x) {
    return vne::math::acos(x);
}
[[nodiscard]] inline double ACos(double x) {
    return vne::math::acos(x);
}
[[nodiscard]] inline float Cosh(float x) {
    return vne::math::cosh(x);
}
[[nodiscard]] inline double Cosh(double x) {
    return vne::math::cosh(x);
}
inline void SinCos(float x, float& s, float& c) {
    vne::math::sinCos(x, s, c);
}
inline void SinCos(double x, double& s, double& c) {
    vne::math::sinCos(x, s, c);
}
[[nodiscard]] inline float Tan(float x) {
    return vne::math::tan(x);
}
[[nodiscard]] inline double Tan(double x) {
    return vne::math::tan(x);
}
[[nodiscard]] inline double Tan(int x) {
    return vne::math::tan(x);
}
[[nodiscard]] inline float ATan(float x) {
    return vne::math::atan(x);
}
[[nodiscard]] inline double ATan(double x) {
    return vne::math::atan(x);
}
[[nodiscard]] inline float ATan2(float y, float x) {
    return vne::math::atan2(y, x);
}
[[nodiscard]] inline double ATan2(double y, double x) {
    return vne::math::atan2(y, x);
}
[[nodiscard]] inline float Tanh(float x) {
    return vne::math::tanh(x);
}
[[nodiscard]] inline double Tanh(double x) {
    return vne::math::tanh(x);
}

// Legacy template aliases
template<typename T>
[[nodiscard]] inline constexpr bool are_same(const T& val1, const T& val2, T eps) {
    return vne::math::areSameImpl(val1, val2, eps);
}
template<typename T>
[[nodiscard]] inline constexpr bool is_zero(const T& val, T eps = static_cast<T>(0)) {
    return vne::math::isZeroImpl(val, eps);
}

}  // namespace Math
}  // namespace VNE

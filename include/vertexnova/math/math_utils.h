#ifndef VNE_MATH_MATH_UTILS_H
#define VNE_MATH_MATH_UTILS_H

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
 *
 * @author Ajeet Singh Yadav
 * Contact: yadav.ajeetsingh2020@gmail.com
 *
 */

// Project includes
#include "constants.h"
#include "vertexnova/common/macros.h"

// System library includes
#include <cmath>

namespace VNE {
namespace Math {

/**
 * @brief Returns the constant π (pi) for the given type.
 *
 * @return Value of π
 */
template<typename T>
inline constexpr T Pi() noexcept;

template<>
inline constexpr float Pi<float>() noexcept {
    return static_cast<float>(PI);
}

template<>
inline constexpr double Pi<double>() noexcept {
    return PI;
}

/**
 * @brief Returns the constant 2π (two pi) for the given type.
 *
 * @return Value of 2π
 */
template<typename T>
inline constexpr T TwoPi() noexcept;

template<>
inline constexpr float TwoPi<float>() noexcept {
    return static_cast<float>(TWO_PI);
}

template<>
inline constexpr double TwoPi<double>() noexcept {
    return TWO_PI;
}

/**
 * @brief Returns the constant π/2 (pi over two) for the given type.
 *
 * @return Value of π/2
 */
template<typename T>
inline constexpr T HalfPi() noexcept;

template<>
inline constexpr float HalfPi<float>() noexcept {
    return static_cast<float>(HALF_PI);
}

template<>
inline constexpr double HalfPi<double>() noexcept {
    return HALF_PI;
}

/**
 * @brief Returns the constant π/4 (pi over four) for the given type.
 *
 * @return Value of π/4
 */
template<typename T>
inline constexpr T QuarterPi() noexcept;

template<>
inline constexpr float QuarterPi<float>() noexcept {
    return static_cast<float>(QUARTER_PI);
}

template<>
inline constexpr double QuarterPi<double>() noexcept {
    return QUARTER_PI;
}

/**
 * @brief Returns the constant 1/π (one over pi) for the given type.
 *
 * @return Value of 1/π
 */
template<typename T>
inline constexpr T OneOverPi() noexcept;

template<>
inline constexpr float OneOverPi<float>() noexcept {
    return static_cast<float>(ONE_OVER_PI);
}

template<>
inline constexpr double OneOverPi<double>() noexcept {
    return ONE_OVER_PI;
}

/**
 * @brief Returns the constant 1/(2π) (one over two pi) for the given type.
 *
 * @return Value of 1/(2π)
 */
template<typename T>
inline constexpr T OneOverTwoPi() noexcept;

template<>
inline constexpr float OneOverTwoPi<float>() noexcept {
    return static_cast<float>(ONE_OVER_TWO_PI);
}

template<>
inline constexpr double OneOverTwoPi<double>() noexcept {
    return ONE_OVER_TWO_PI;
}

/**
 * @brief Converts radians to degrees.
 *
 * @param angle Angle in radians.
 * @return Angle in degrees.
 */
template<typename T>
inline constexpr T RadToDeg(const T& angle) noexcept {
    return angle * (static_cast<T>(180) * OneOverPi<T>());
}

/**
 * @brief Converts degrees to radians.
 *
 * @param angle Angle in degrees.
 * @return Angle in radians.
 */
template<typename T>
inline constexpr T DegToRad(const T& angle) noexcept {
    return angle * (Pi<T>() / static_cast<T>(180));
}

/**
 * @brief Returns the epsilon value for the given type.
 *
 * @return Epsilon value.
 */
template<typename T>
inline constexpr T GetEps() noexcept {
    return static_cast<T>(0);
}

template<>
inline constexpr float GetEps<float>() noexcept {
    return FLOAT_EPSILON;
}

template<>
inline constexpr double GetEps<double>() noexcept {
    return DOUBLE_EPSILON;
}

////////////////////////////////////////////////////////////////////////////
//                        Basic Operations                                 //
// /////////////////////////////////////////////////////////////////////////

/**
 * Computes the absolute value of the input value.
 */
template<typename T>
inline constexpr T Abs(const T& val) {
    return std::abs(val);
}

/**
 * Computes the sign value of the given input value.
 */
template<typename T>
inline constexpr T Sign(const T& val, T eps = static_cast<T>(0)) {
    return (val > eps ? static_cast<T>(1) : (val < eps ? static_cast<T>(-1) : static_cast<T>(0)));
}

/**
 * Returns the minimum of the two given values
 */
template<typename T>
inline constexpr T Min(const T& val1, const T& val2) {
    return val1 <= val2 ? val1 : val2;
}

/**
 * Returns the maximum of the two given values
 */
template<typename T>
inline constexpr T Max(const T& val1, const T& val2) {
    return val1 >= val2 ? val1 : val2;
}

/**
 * Returns the minimum of the three given values
 */
template<typename T>
inline constexpr T Min(const T& val1, const T& val2, const T& val3) {
    return Min(Min(val1, val2), val3);
}

/**
 * Returns the maximum of the three given values
 */
template<typename T>
inline constexpr T Max(const T& val1, const T& val2, const T& val3) {
    return Max(Max(val1, val2), val3);
}

/**
 * Clamps a value between a pair of boundary values.
 */
template<typename T>
inline constexpr T Clamp(const T& val, const T& lower, const T& upper) {
    return Min(upper, Max(val, lower));
}

/**
 * Clamps a value between 0 and 1.
 */
template<typename T>
inline constexpr T Saturate(const T& val) {
    return Clamp<T>(val, static_cast<T>(0), static_cast<T>(1));
}

/**
 * Sorts parameters val1 and val2 in the ascending order.
 */
template<typename T>
inline void ArrangeMinMax(T* val1, T* val2) {
    if (*val1 > *val2) {
        std::swap(*val1, *val2);
    }
}

/**
 * Checks if the given value is lying in an interval [min, max].
 */
template<typename T>
inline bool IsInBetween(T val, T min, T max, T eps = static_cast<T>(0)) {
    ArrangeMinMax(&min, &max);
    return val >= min - eps && val <= max + eps;
}

/**
 * Computes the square of the given input.
 */
template<typename T>
inline constexpr T Square(const T& val) {
    return val * val;
}

/**
 * Computes the cube of the given input.
 */
template<typename T>
inline constexpr T Cube(const T& val) {
    return val * val * val;
}

/**
 * Computes the value of the base raised to power exponent.
 */
template<typename T>
inline constexpr T Pow(const T& base, T exponent) {
    return std::pow(base, exponent);
}

/**
 * Computes the square root of the given value.
 */
template<typename T>
inline constexpr T Sqrt(const T& val) {
    return std::sqrt(val);
}

/**
 * Computes the inverse of the square root of the given value.
 */
template<typename T>
inline constexpr T InvSqrt(const T& val) {
    return static_cast<T>(1) / std::sqrt(val);
}

/**
 * Checks whether two values are "close enough" to one another.
 */
template<typename T>
inline constexpr bool are_same(const T& val1, const T& val2, T eps) {
    VNE_UNUSED(eps);
    return val1 == val2;
}

template<>
inline bool are_same(const float& val1, const float& val2, float eps) {
    VNE_ASSERT_MSG(eps >= FLOAT_EPSILON, "eps cannot be less than FLOAT_EPSILON.");
    return Abs<float>(val1 - val2) <= eps * Max<float>(1.0f, Abs<float>(val1), Abs<float>(val2));
}

template<>
inline bool are_same(const double& val1, const double& val2, double eps) {
    VNE_ASSERT_MSG(eps >= DOUBLE_EPSILON, "eps cannot be less than DOUBLE_EPSILON.");
    return Abs<double>(val1 - val2) <= eps * Max<double>(1.0, Abs<double>(val1), Abs<double>(val2));
}

inline bool AreSame(float val1, float val2, float eps = FLOAT_EPSILON) {
    return are_same<float>(val1, val2, eps);
}

inline bool AreSame(double val1, double val2, double eps = DOUBLE_EPSILON) {
    return are_same<double>(val1, val2, eps);
}

inline constexpr bool AreSame(int val1, int val2, int eps = 0) {
    return are_same<int>(val1, val2, eps);
}

inline constexpr bool AreSame(long int val1, long int val2, long int eps = 0) {
    return are_same<long int>(val1, val2, eps);
}

inline constexpr bool AreSame(unsigned int val1, unsigned int val2, unsigned int eps = 0) {
    return are_same<unsigned int>(val1, val2, eps);
}

inline constexpr bool AreSame(unsigned long val1, unsigned long val2, unsigned long eps = 0) {
    return are_same<unsigned long>(val1, val2, eps);
}

inline constexpr bool AreSame(char val1, char val2, char eps = 0) {
    return are_same<char>(val1, val2, eps);
}

inline constexpr bool AreSame(unsigned char val1, unsigned char val2, unsigned char eps = 0) {
    return are_same<unsigned char>(val1, val2, eps);
}

/**
 * Checks whether the given value is "close enough" to zero.
 */
template<typename T>
inline constexpr bool is_zero(const T& val, T eps = static_cast<T>(0)) {
    VNE_UNUSED(eps);
    return val == T(0);
}

template<>
inline bool is_zero(const float& val, float eps) {
    VNE_ASSERT_MSG(eps >= FLOAT_EPSILON, "eps cannot be less than FLOAT_EPSILON.");
    return Abs<float>(val) < eps * Max<float>(1.0f, Abs<float>(val));
}

template<>
inline bool is_zero(const double& val, double eps) {
    VNE_ASSERT_MSG(eps >= DOUBLE_EPSILON, "eps cannot be less than DOUBLE_EPSILON.");
    return Abs<double>(val) < eps * Max<double>(1.0, Abs<double>(val));
}

inline bool IsZero(float val, float eps = FLOAT_EPSILON) {
    return is_zero<float>(val, eps);
}

inline bool IsZero(double val, double eps = DOUBLE_EPSILON) {
    return is_zero<double>(val, eps);
}

inline constexpr bool IsZero(int val, int eps = 0) {
    return is_zero<int>(val, eps);
}

inline constexpr bool IsZero(unsigned int val, unsigned int eps = 0) {
    return is_zero<unsigned int>(val, eps);
}

inline constexpr bool IsZero(long int val, long int eps = 0) {
    return is_zero<long int>(val, eps);
}

inline constexpr bool IsZero(unsigned long val, unsigned long eps = 0) {
    return is_zero<unsigned long>(val, eps);
}

////////////////////////////////////////////////////////////////////////////
//                             Interpolations                              //
// /////////////////////////////////////////////////////////////////////////

/**
 * Computes the midpoint of the integers, floating-points, or pointers a and b.
 */
inline int MidPoint(const int a, const int b) {
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

inline float MidPoint(const float a, const float b) {
    float lo = FLOAT_MIN * 2;
    float hi = FLOAT_MAX / 2;
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

inline double MidPoint(const double a, const double b) {
    double lo = DOUBLE_MIN * 2;
    double hi = DOUBLE_MAX / 2;
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
inline constexpr T Lerp(const T& a, const T& b, const U& t) {
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
inline constexpr T BiLerp(const T& c00, const T& c10, const T& c01, const T& c11, const U& tx, const U& ty) {
    T a = Lerp(c00, c10, tx);
    T b = Lerp(c01, c11, tx);
    return Lerp(a, b, ty);
}

////////////////////////////////////////////////////////////////////////////
//               Nearest Integer floating point operations                 //
// /////////////////////////////////////////////////////////////////////////

template<typename T>
inline T Floor(T val) {
    return std::floor(val);
}

template<typename T>
inline T Ceil(T val) {
    return std::ceil(val);
}

template<typename T>
inline T Trunc(T val) {
    return std::trunc(val);
}

template<typename T>
inline T Round(T val) {
    return std::round(val);
}

template<typename T>
inline T RoundMultipleOf(T val, T multiple) {
    if (multiple == static_cast<T>(0)) {
        return std::round(val);
    }
    return T(multiple) * std::floor(val / T(multiple) + static_cast<T>(0.5));
}

constexpr inline int FloatToInt(float val) {
    return static_cast<int>(val);
}

inline float Modf(float x, float* iptr) {
    return std::modf(x, iptr);
}

inline double Modf(double x, double* iptr) {
    return std::modf(x, iptr);
}

////////////////////////////////////////////////////////////////////////////
//               Classification and comparison                            //
// /////////////////////////////////////////////////////////////////////////

inline bool IsNaN(float x) {
    return std::isnan(x);
}

inline bool IsNaN(double x) {
    return std::isnan(x);
}

inline bool IsInf(float x) {
    return std::isinf(x);
}

inline bool IsInf(double x) {
    return std::isinf(x);
}

inline bool IsNormal(float x) {
    return std::isnormal(x);
}

inline bool IsNormal(double x) {
    return std::isnormal(x);
}

inline bool IsFinite(float x) {
    return std::isfinite(x);
}

inline bool IsFinite(double x) {
    return std::isfinite(x);
}

////////////////////////////////////////////////////////////////////////////
//                  Exponential Functions                                 //
// /////////////////////////////////////////////////////////////////////////

inline float Exp(float x) {
    return std::exp(x);
}

inline double Exp(double x) {
    return std::exp(x);
}

inline double Exp(int x) {
    return std::exp(static_cast<double>(x));
}

inline float Log(float x) {
    return std::log(x);
}

inline double Log(double x) {
    return std::log(x);
}

inline double Log(int x) {
    return std::log(static_cast<double>(x));
}

inline float Log2(float x) {
    return std::log2(x);
}

inline double Log2(double x) {
    return std::log2(x);
}

inline double Log2(int x) {
    return std::log2(static_cast<double>(x));
}

inline float Log10(float x) {
    return std::log10(x);
}

inline double Log10(double x) {
    return std::log10(x);
}

inline double Log10(int x) {
    return std::log10(static_cast<double>(x));
}

inline float Logx(float x, float b) {
    return Log(x) * (1.0f / Log(b));
}

inline double Logx(double x, double b) {
    return Log(x) * (1.0 / Log(b));
}

inline double Logx(int x, int b) {
    return Log(static_cast<double>(x)) * (1.0 / Log(static_cast<double>(b)));
}

inline double Logx(float x, int b) {
    return Log(static_cast<double>(x)) * (1.0 / Log(static_cast<double>(b)));
}

inline double Logx(double x, int b) {
    return Log(x) * (1.0 / Log(static_cast<double>(b)));
}

////////////////////////////////////////////////////////////////////////////
//               Trigonometric and hyperbolic functions                    //
// /////////////////////////////////////////////////////////////////////////

inline float Sin(float x) {
    return std::sin(x);
}

inline double Sin(double x) {
    return std::sin(x);
}

inline double Sin(int x) {
    return std::sin(static_cast<double>(x));
}

inline float ASin(float x) {
    return std::asin(x);
}

inline double ASin(double x) {
    return std::asin(x);
}

inline double ASin(int x) {
    return std::asin(static_cast<double>(x));
}

inline float Sinh(float x) {
    return std::sinh(x);
}

inline double Sinh(double x) {
    return std::sinh(x);
}

inline double Sinh(int x) {
    return std::sinh(static_cast<double>(x));
}

inline float Cos(float x) {
    return std::cos(x);
}

inline double Cos(double x) {
    return std::cos(x);
}

inline double Cos(int x) {
    return std::cos(static_cast<double>(x));
}

inline float ACos(float x) {
    return std::acos(x);
}

inline double ACos(double x) {
    return std::acos(x);
}

inline double ACos(int x) {
    return std::acos(static_cast<double>(x));
}

inline float Cosh(float x) {
    return std::cosh(x);
}

inline double Cosh(double x) {
    return std::cosh(x);
}

inline double Cosh(int x) {
    return std::cosh(static_cast<double>(x));
}

inline void SinCos(float x, float& sin, float& cos) {
    sin = std::sin(x);
    cos = std::cos(x);
}

inline void SinCos(double x, double& sin, double& cos) {
    sin = std::sin(x);
    cos = std::cos(x);
}

inline void SinCos(int x, double& sin, double& cos) {
    sin = std::sin(static_cast<double>(x));
    cos = std::cos(static_cast<double>(x));
}

inline float Tan(float x) {
    return std::tan(x);
}

inline double Tan(double x) {
    return std::tan(x);
}

inline double Tan(int x) {
    return std::tan(static_cast<double>(x));
}

inline float ATan(float x) {
    return std::atan(x);
}

inline double ATan(double x) {
    return std::atan(x);
}

inline double ATan(int x) {
    return std::atan(static_cast<double>(x));
}

inline float ATan2(float y, float x) {
    return std::atan2(y, x);
}

inline double ATan2(double y, double x) {
    return std::atan2(y, x);
}

inline double ATan2(int y, int x) {
    return std::atan2(static_cast<double>(y), static_cast<double>(x));
}

inline float Tanh(float x) {
    return std::tanh(x);
}

inline double Tanh(double x) {
    return std::tanh(x);
}

inline double Tanh(int x) {
    return std::tanh(static_cast<double>(x));
}

}  // namespace Math
}  // namespace VNE

#endif  // VNE_MATH_MATH_UTILS_H

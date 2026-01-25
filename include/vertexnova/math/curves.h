/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Curve evaluation functions for animation and procedural generation.
 * Supports Bezier curves, Catmull-Rom splines, and Hermite splines.
 * ----------------------------------------------------------------------
 */

#pragma once

#include "core/types.h"
#include "core/vec.h"

#include <array>

namespace vne::math {

// ============================================================================
// Bezier Curves
// ============================================================================

/**
 * @brief Evaluates a linear Bezier curve (lerp).
 *
 * @param p0 Start point
 * @param p1 End point
 * @param t Parameter [0, 1]
 * @return Point on the curve
 */
template<typename T>
[[nodiscard]] constexpr T bezierLinear(const T& p0, const T& p1, float t) noexcept {
    return lerp(p0, p1, t);
}

/**
 * @brief Evaluates a quadratic Bezier curve.
 *
 * The curve passes through p0 at t=0 and p2 at t=1.
 * p1 is a control point that influences the shape.
 *
 * Formula: B(t) = (1-t)²p0 + 2(1-t)t*p1 + t²p2
 *
 * @param p0 Start point
 * @param p1 Control point
 * @param p2 End point
 * @param t Parameter [0, 1]
 * @return Point on the curve
 */
template<typename T>
[[nodiscard]] constexpr T bezierQuadratic(const T& p0, const T& p1, const T& p2, float t) noexcept {
    float u = 1.0f - t;
    float u2 = u * u;
    float t2 = t * t;
    return p0 * u2 + p1 * (2.0f * u * t) + p2 * t2;
}

/**
 * @brief Evaluates the derivative of a quadratic Bezier curve.
 *
 * @param p0 Start point
 * @param p1 Control point
 * @param p2 End point
 * @param t Parameter [0, 1]
 * @return Tangent vector at t
 */
template<typename T>
[[nodiscard]] constexpr T bezierQuadraticDerivative(const T& p0, const T& p1, const T& p2, float t) noexcept {
    float u = 1.0f - t;
    return (p1 - p0) * (2.0f * u) + (p2 - p1) * (2.0f * t);
}

/**
 * @brief Evaluates a cubic Bezier curve.
 *
 * The curve passes through p0 at t=0 and p3 at t=1.
 * p1 and p2 are control points that influence the shape.
 *
 * Formula: B(t) = (1-t)³p0 + 3(1-t)²t*p1 + 3(1-t)t²p2 + t³p3
 *
 * @param p0 Start point
 * @param p1 First control point
 * @param p2 Second control point
 * @param p3 End point
 * @param t Parameter [0, 1]
 * @return Point on the curve
 */
template<typename T>
[[nodiscard]] constexpr T bezierCubic(const T& p0, const T& p1, const T& p2, const T& p3, float t) noexcept {
    float u = 1.0f - t;
    float u2 = u * u;
    float u3 = u2 * u;
    float t2 = t * t;
    float t3 = t2 * t;
    return p0 * u3 + p1 * (3.0f * u2 * t) + p2 * (3.0f * u * t2) + p3 * t3;
}

/**
 * @brief Evaluates the derivative of a cubic Bezier curve.
 *
 * @param p0 Start point
 * @param p1 First control point
 * @param p2 Second control point
 * @param p3 End point
 * @param t Parameter [0, 1]
 * @return Tangent vector at t
 */
template<typename T>
[[nodiscard]] constexpr T bezierCubicDerivative(const T& p0, const T& p1, const T& p2, const T& p3, float t) noexcept {
    float u = 1.0f - t;
    float u2 = u * u;
    float t2 = t * t;
    return (p1 - p0) * (3.0f * u2) + (p2 - p1) * (6.0f * u * t) + (p3 - p2) * (3.0f * t2);
}

/**
 * @brief Evaluates the second derivative of a cubic Bezier curve.
 *
 * @param p0 Start point
 * @param p1 First control point
 * @param p2 Second control point
 * @param p3 End point
 * @param t Parameter [0, 1]
 * @return Acceleration vector at t
 */
template<typename T>
[[nodiscard]] constexpr T bezierCubicSecondDerivative(const T& p0,
                                                       const T& p1,
                                                       const T& p2,
                                                       const T& p3,
                                                       float t) noexcept {
    float u = 1.0f - t;
    return (p2 - p1 * 2.0f + p0) * (6.0f * u) + (p3 - p2 * 2.0f + p1) * (6.0f * t);
}

// ============================================================================
// Catmull-Rom Spline
// ============================================================================

/**
 * @brief Evaluates a Catmull-Rom spline segment.
 *
 * A Catmull-Rom spline passes through all control points (p1 and p2),
 * using p0 and p3 to determine the tangents at those points.
 * This creates a smooth curve that interpolates through the points.
 *
 * Properties:
 * - C1 continuous (smooth tangents)
 * - Passes through p1 at t=0 and p2 at t=1
 * - Local control (changing a point only affects nearby segments)
 *
 * @param p0 Previous point (for tangent calculation at p1)
 * @param p1 Start point of this segment
 * @param p2 End point of this segment
 * @param p3 Next point (for tangent calculation at p2)
 * @param t Parameter [0, 1]
 * @return Point on the curve
 */
template<typename T>
[[nodiscard]] constexpr T catmullRom(const T& p0, const T& p1, const T& p2, const T& p3, float t) noexcept {
    float t2 = t * t;
    float t3 = t2 * t;

    // Catmull-Rom basis matrix coefficients
    return p0 * (-0.5f * t3 + t2 - 0.5f * t)
         + p1 * (1.5f * t3 - 2.5f * t2 + 1.0f)
         + p2 * (-1.5f * t3 + 2.0f * t2 + 0.5f * t)
         + p3 * (0.5f * t3 - 0.5f * t2);
}

/**
 * @brief Evaluates the derivative of a Catmull-Rom spline segment.
 *
 * @param p0 Previous point
 * @param p1 Start point
 * @param p2 End point
 * @param p3 Next point
 * @param t Parameter [0, 1]
 * @return Tangent vector at t
 */
template<typename T>
[[nodiscard]] constexpr T catmullRomDerivative(const T& p0, const T& p1, const T& p2, const T& p3, float t) noexcept {
    float t2 = t * t;

    return p0 * (-1.5f * t2 + 2.0f * t - 0.5f)
         + p1 * (4.5f * t2 - 5.0f * t)
         + p2 * (-4.5f * t2 + 4.0f * t + 0.5f)
         + p3 * (1.5f * t2 - t);
}

/**
 * @brief Evaluates a Catmull-Rom spline with tension parameter.
 *
 * Tension controls how tight the curve is:
 * - tension = 0: Standard Catmull-Rom (centripetal)
 * - tension = 1: Linear interpolation
 * - tension < 0: Looser curves, more overshoot
 *
 * @param p0 Previous point
 * @param p1 Start point
 * @param p2 End point
 * @param p3 Next point
 * @param t Parameter [0, 1]
 * @param tension Tension parameter (default 0)
 * @return Point on the curve
 */
template<typename T>
[[nodiscard]] constexpr T catmullRomTension(const T& p0,
                                             const T& p1,
                                             const T& p2,
                                             const T& p3,
                                             float t,
                                             float tension = 0.0f) noexcept {
    float s = (1.0f - tension) * 0.5f;
    float t2 = t * t;
    float t3 = t2 * t;

    return p0 * (-s * t3 + 2.0f * s * t2 - s * t)
         + p1 * ((2.0f - s) * t3 + (s - 3.0f) * t2 + 1.0f)
         + p2 * ((s - 2.0f) * t3 + (3.0f - 2.0f * s) * t2 + s * t)
         + p3 * (s * t3 - s * t2);
}

// ============================================================================
// Hermite Spline
// ============================================================================

/**
 * @brief Evaluates a cubic Hermite spline.
 *
 * A Hermite spline is defined by two points and their tangents.
 * Useful when you have explicit control over the curve's direction
 * at the endpoints.
 *
 * @param p0 Start point
 * @param t0 Tangent at start point
 * @param p1 End point
 * @param t1 Tangent at end point
 * @param t Parameter [0, 1]
 * @return Point on the curve
 */
template<typename T>
[[nodiscard]] constexpr T hermite(const T& p0, const T& t0, const T& p1, const T& t1, float t) noexcept {
    float t2 = t * t;
    float t3 = t2 * t;

    // Hermite basis functions
    float h00 = 2.0f * t3 - 3.0f * t2 + 1.0f;
    float h10 = t3 - 2.0f * t2 + t;
    float h01 = -2.0f * t3 + 3.0f * t2;
    float h11 = t3 - t2;

    return p0 * h00 + t0 * h10 + p1 * h01 + t1 * h11;
}

/**
 * @brief Evaluates the derivative of a cubic Hermite spline.
 *
 * @param p0 Start point
 * @param t0 Tangent at start point
 * @param p1 End point
 * @param t1 Tangent at end point
 * @param t Parameter [0, 1]
 * @return Tangent vector at t
 */
template<typename T>
[[nodiscard]] constexpr T hermiteDerivative(const T& p0, const T& t0, const T& p1, const T& t1, float t) noexcept {
    float t2 = t * t;

    // Derivatives of Hermite basis functions
    float dh00 = 6.0f * t2 - 6.0f * t;
    float dh10 = 3.0f * t2 - 4.0f * t + 1.0f;
    float dh01 = -6.0f * t2 + 6.0f * t;
    float dh11 = 3.0f * t2 - 2.0f * t;

    return p0 * dh00 + t0 * dh10 + p1 * dh01 + t1 * dh11;
}

// ============================================================================
// B-Spline (Uniform Cubic)
// ============================================================================

/**
 * @brief Evaluates a uniform cubic B-spline segment.
 *
 * B-splines are smoother than Catmull-Rom (C2 continuous) but
 * do NOT pass through the control points.
 *
 * @param p0 First control point
 * @param p1 Second control point
 * @param p2 Third control point
 * @param p3 Fourth control point
 * @param t Parameter [0, 1]
 * @return Point on the curve
 */
template<typename T>
[[nodiscard]] constexpr T bsplineCubic(const T& p0, const T& p1, const T& p2, const T& p3, float t) noexcept {
    float t2 = t * t;
    float t3 = t2 * t;

    // B-spline basis matrix (1/6 factor)
    constexpr float k = 1.0f / 6.0f;

    return (p0 * (-t3 + 3.0f * t2 - 3.0f * t + 1.0f)
          + p1 * (3.0f * t3 - 6.0f * t2 + 4.0f)
          + p2 * (-3.0f * t3 + 3.0f * t2 + 3.0f * t + 1.0f)
          + p3 * t3) * k;
}

// ============================================================================
// Arc Length Parameterization Helpers
// ============================================================================

/**
 * @brief Approximate arc length of a cubic Bezier curve using subdivision.
 *
 * @param p0 Start point
 * @param p1 First control point
 * @param p2 Second control point
 * @param p3 End point
 * @param subdivisions Number of subdivisions (higher = more accurate)
 * @return Approximate arc length
 */
template<typename T>
[[nodiscard]] inline float bezierCubicArcLength(const T& p0,
                                                 const T& p1,
                                                 const T& p2,
                                                 const T& p3,
                                                 int subdivisions = 32) noexcept {
    float length = 0.0f;
    T prev = p0;

    for (int i = 1; i <= subdivisions; ++i) {
        float t = static_cast<float>(i) / static_cast<float>(subdivisions);
        T curr = bezierCubic(p0, p1, p2, p3, t);
        length += (curr - prev).length();
        prev = curr;
    }

    return length;
}

// ============================================================================
// Curve Splitting
// ============================================================================

/**
 * @brief Splits a cubic Bezier curve at parameter t using de Casteljau's algorithm.
 *
 * @param p0 Start point
 * @param p1 First control point
 * @param p2 Second control point
 * @param p3 End point
 * @param t Split parameter [0, 1]
 * @param left Output: left segment control points [p0, p1, p2, p3]
 * @param right Output: right segment control points [p0, p1, p2, p3]
 */
template<typename T>
inline void bezierCubicSplit(const T& p0,
                              const T& p1,
                              const T& p2,
                              const T& p3,
                              float t,
                              std::array<T, 4>& left,
                              std::array<T, 4>& right) noexcept {
    // First level
    T q0 = lerp(p0, p1, t);
    T q1 = lerp(p1, p2, t);
    T q2 = lerp(p2, p3, t);

    // Second level
    T r0 = lerp(q0, q1, t);
    T r1 = lerp(q1, q2, t);

    // Third level (split point)
    T s = lerp(r0, r1, t);

    // Left curve
    left[0] = p0;
    left[1] = q0;
    left[2] = r0;
    left[3] = s;

    // Right curve
    right[0] = s;
    right[1] = r1;
    right[2] = q2;
    right[3] = p3;
}

}  // namespace vne::math

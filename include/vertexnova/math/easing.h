/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * High-performance easing and interpolation functions.
 * Implementations inspired by Inigo Quilez (iquilezles.org)
 * ----------------------------------------------------------------------
 */

#pragma once

#include "core/types.h"

#include <cmath>

namespace vne::math {

// ============================================================================
// Smoothstep Variants
// Based on https://iquilezles.org/articles/smoothsteps/
// ============================================================================

/**
 * @brief Standard cubic smoothstep: x²(3-2x)
 *
 * C1 continuous (zero derivative at edges).
 * Most common smoothstep, fast to evaluate.
 *
 * @param x Value in [0,1] range (unclamped input is allowed)
 * @return Smoothly interpolated value in [0,1]
 */
template<FloatingPoint T>
[[nodiscard]] constexpr T smoothstep(T x) noexcept {
    return x * x * (T(3) - T(2) * x);
}

/**
 * @brief Standard smoothstep with edge parameters.
 *
 * Maps x from [edge0, edge1] to [0, 1] with smooth interpolation.
 *
 * @param edge0 Lower edge
 * @param edge1 Upper edge
 * @param x Input value
 * @return 0 if x <= edge0, 1 if x >= edge1, smooth transition otherwise
 */
template<FloatingPoint T>
[[nodiscard]] constexpr T smoothstep(T edge0, T edge1, T x) noexcept {
    x = clamp((x - edge0) / (edge1 - edge0), T(0), T(1));
    return smoothstep(x);
}

/**
 * @brief Quintic smoothstep (smootherstep): x³(x(6x-15)+10)
 *
 * C2 continuous (zero first AND second derivative at edges).
 * Better for noise functions and surface stitching.
 * Slightly more expensive than cubic.
 *
 * @param x Value in [0,1] range
 * @return Smoothly interpolated value in [0,1]
 */
template<FloatingPoint T>
[[nodiscard]] constexpr T smootherstep(T x) noexcept {
    return x * x * x * (x * (x * T(6) - T(15)) + T(10));
}

/**
 * @brief Smootherstep with edge parameters.
 */
template<FloatingPoint T>
[[nodiscard]] constexpr T smootherstep(T edge0, T edge1, T x) noexcept {
    x = clamp((x - edge0) / (edge1 - edge0), T(0), T(1));
    return smootherstep(x);
}

/**
 * @brief Quartic smoothstep: x²(2-x²)
 *
 * Uses only even powers - useful when x is a distance (avoids sqrt).
 * Note: Not symmetric around 0.5.
 *
 * @param x Value in [0,1] range
 * @return Smoothly interpolated value in [0,1]
 */
template<FloatingPoint T>
[[nodiscard]] constexpr T smoothstepQuartic(T x) noexcept {
    return x * x * (T(2) - x * x);
}

/**
 * @brief Inverse of cubic smoothstep.
 *
 * Given y = smoothstep(x), returns x.
 *
 * @param x Value in [0,1] range (output of smoothstep)
 * @return Original input value
 */
template<FloatingPoint T>
[[nodiscard]] inline T smoothstepInverse(T x) noexcept {
    return T(0.5) - std::sin(std::asin(T(1) - T(2) * x) / T(3));
}

/**
 * @brief Rational smoothstep with controllable steepness.
 *
 * C(n-1) continuous. Higher n = steeper transition.
 * Has closed-form inverse: smoothstepRational(x, 1/n).
 *
 * @param x Value in [0,1] range
 * @param n Steepness exponent (default 2 = quadratic)
 * @return Smoothly interpolated value in [0,1]
 */
template<FloatingPoint T>
[[nodiscard]] inline T smoothstepRational(T x, T n = T(2)) noexcept {
    T xn = std::pow(x, n);
    return xn / (xn + std::pow(T(1) - x, n));
}

// ============================================================================
// Impulse Functions
// Based on https://iquilezles.org/articles/functions/
// ============================================================================

/**
 * @brief Exponential impulse: grows fast, decays slowly.
 *
 * Great for triggering behaviors, music envelopes, animations.
 * Maximum value of 1 occurs at x = 1/k.
 *
 * @param x Input value (x >= 0)
 * @param k Controls stretching (higher = narrower peak)
 * @return Impulse value, peaks at 1
 */
template<FloatingPoint T>
[[nodiscard]] inline T expImpulse(T x, T k) noexcept {
    T h = k * x;
    return h * std::exp(T(1) - h);
}

/**
 * @brief Polynomial impulse (no exponential).
 *
 * Faster than expImpulse, different falloff shape.
 * Maximum value of 1 occurs at x = sqrt(1/k).
 *
 * @param x Input value (x >= 0)
 * @param k Controls falloff (higher = narrower peak)
 * @return Impulse value, peaks at 1
 */
template<FloatingPoint T>
[[nodiscard]] inline T polyImpulse(T x, T k) noexcept {
    return T(2) * std::sqrt(k) * x / (T(1) + k * x * x);
}

/**
 * @brief Sinc impulse with controllable bounces.
 *
 * Useful for bouncing behaviors. Can go negative!
 *
 * @param x Input value
 * @param k Number of bounces (integer values work best)
 * @return Impulse value (can be negative)
 */
template<FloatingPoint T>
[[nodiscard]] inline T sincImpulse(T x, T k) noexcept {
    T a = kPiT<T> * (k * x - T(1));
    return std::sin(a) / a;
}

// ============================================================================
// Cubic Pulse (localized bump)
// ============================================================================

/**
 * @brief Cubic pulse centered at c with width w.
 *
 * Equivalent to smoothstep(c-w,c,x) - smoothstep(c,c+w,x) but faster.
 * Useful as a cheap gaussian-like bump with local support.
 *
 * @param c Center of the pulse
 * @param w Half-width of the pulse
 * @param x Input value
 * @return 1 at center, 0 outside [c-w, c+w]
 */
template<FloatingPoint T>
[[nodiscard]] constexpr T cubicPulse(T c, T w, T x) noexcept {
    x = abs(x - c);
    if (x > w) {
        return T(0);
    }
    x /= w;
    return T(1) - x * x * (T(3) - T(2) * x);
}

// ============================================================================
// Gain and Bias (contrast/brightness control)
// ============================================================================

/**
 * @brief Attempt to gain control the midpoint without changing the endpoints.
 *
 * k=1: identity curve
 * k<1: classic "gain" shape (S-curve, expands sides, compresses center)
 * k>1: inverse S-curve
 * Symmetric: gain(x,a) is inverse of gain(x,1/a)
 *
 * @param x Value in [0,1] range
 * @param k Gain parameter
 * @return Adjusted value in [0,1]
 */
template<FloatingPoint T>
[[nodiscard]] inline T gain(T x, T k) noexcept {
    T a = T(0.5) * std::pow(T(2) * ((x < T(0.5)) ? x : T(1) - x), k);
    return (x < T(0.5)) ? a : T(1) - a;
}

/**
 * @brief Attempt to shift the midpoint without changing the endpoints.
 *
 * Similar to gamma correction but for general curve shaping.
 *
 * @param x Value in [0,1] range
 * @param k Bias parameter (0.5 = identity)
 * @return Biased value in [0,1]
 */
template<FloatingPoint T>
[[nodiscard]] inline T bias(T x, T k) noexcept {
    return x / ((T(1) / k - T(2)) * (T(1) - x) + T(1));
}

// ============================================================================
// Parabola (symmetric bump)
// ============================================================================

/**
 * @brief Attempt to create a parabolic mapping: 0 at corners, 1 at center.
 *
 * Attempt to use power k to control the shape.
 *
 * @param x Value in [0,1] range
 * @param k Power exponent (1 = linear falloff, 2 = quadratic)
 * @return Value peaking at 1 for x=0.5
 */
template<FloatingPoint T>
[[nodiscard]] inline T parabola(T x, T k) noexcept {
    return std::pow(T(4) * x * (T(1) - x), k);
}

// ============================================================================
// Power Curve (asymmetric parabola)
// ============================================================================

/**
 * @brief Attempt to create an asymmetric power curve for organic shapes.
 *
 * Maps [0,1] to [0,1] with 0 at corners.
 * Attempt to control left side shape with a, right side with b.
 * Great for leaves, eyes, petals.
 *
 * @param x Value in [0,1] range
 * @param a Left side power
 * @param b Right side power
 * @return Shaped value in [0,1]
 */
template<FloatingPoint T>
[[nodiscard]] inline T powerCurve(T x, T a, T b) noexcept {
    T k = std::pow(a + b, a + b) / (std::pow(a, a) * std::pow(b, b));
    return k * std::pow(x, a) * std::pow(T(1) - x, b);
}

// ============================================================================
// Almost Identity (soft clipping)
// ============================================================================

/**
 * @brief Attempt to softly clip values near zero to a minimum value.
 *
 * Values above m pass through unchanged.
 * Values approaching 0 smoothly blend to n.
 *
 * @param x Input value
 * @param m Threshold (values > m unchanged)
 * @param n Minimum output value (when x=0)
 * @return Soft-clipped value
 */
template<FloatingPoint T>
[[nodiscard]] constexpr T almostIdentity(T x, T m, T n) noexcept {
    if (x > m) {
        return x;
    }
    T a = T(2) * n - m;
    T b = T(2) * m - T(3) * n;
    T t = x / m;
    return (a * t + b) * t * t + n;
}

/**
 * @brief Attempt to provide smooth absolute value (soft mirroring).
 *
 * Behaves like abs(x) but with smooth transition at zero.
 * sqrt(x² + n²) where n controls smoothness.
 *
 * @param x Input value
 * @param n Smoothness (higher = smoother transition at 0)
 * @return Smooth absolute value
 */
template<FloatingPoint T>
[[nodiscard]] inline T smoothAbs(T x, T n) noexcept {
    return std::sqrt(x * x + n * n);
}

// ============================================================================
// Almost Unit Identity
// ============================================================================

/**
 * @brief Attempt to near-identity mapping with zero derivative at origin.
 *
 * Maps 0→0, 1→1 with derivative 0 at x=0 and derivative 1 at x=1.
 * Cousin of smoothstep. Formula: x²(2-x)
 *
 * @param x Value in [0,1] range
 * @return Near-identity value
 */
template<FloatingPoint T>
[[nodiscard]] constexpr T almostUnitIdentity(T x) noexcept {
    return x * x * (T(2) - x);
}

// ============================================================================
// Exponential Step
// ============================================================================

/**
 * @brief Attempt to provide an exponential step with controllable sharpness.
 *
 * Attempt to generalize from Gaussian (n=2) to sharper steps.
 * High n approaches a perfect step function.
 *
 * @param x Value in [0,1] range
 * @param n Sharpness (2 = Gaussian-like, higher = sharper)
 * @return Stepped value
 */
template<FloatingPoint T>
[[nodiscard]] inline T expStep(T x, T n) noexcept {
    return std::exp2(-std::exp2(n) * std::pow(x, n));
}

// ============================================================================
// Standard Easing Functions
// For UI animations and gameplay
// ============================================================================

/// @brief Easing function type enumeration
enum class EaseType : uint8_t {
    eLinear,
    eQuadIn,
    eQuadOut,
    eQuadInOut,
    eCubicIn,
    eCubicOut,
    eCubicInOut,
    eQuartIn,
    eQuartOut,
    eQuartInOut,
    eQuintIn,
    eQuintOut,
    eQuintInOut,
    eSineIn,
    eSineOut,
    eSineInOut,
    eExpoIn,
    eExpoOut,
    eExpoInOut,
    eCircIn,
    eCircOut,
    eCircInOut,
    eBackIn,
    eBackOut,
    eBackInOut,
    eElasticIn,
    eElasticOut,
    eElasticInOut,
    eBounceIn,
    eBounceOut,
    eBounceInOut
};

// Individual easing functions (all take t in [0,1], return value in [0,1] or beyond for overshoot)

template<FloatingPoint T>
[[nodiscard]] constexpr T easeLinear(T t) noexcept {
    return t;
}

// Quadratic
template<FloatingPoint T>
[[nodiscard]] constexpr T easeInQuad(T t) noexcept {
    return t * t;
}

template<FloatingPoint T>
[[nodiscard]] constexpr T easeOutQuad(T t) noexcept {
    return t * (T(2) - t);
}

template<FloatingPoint T>
[[nodiscard]] constexpr T easeInOutQuad(T t) noexcept {
    return t < T(0.5) ? T(2) * t * t : T(-1) + (T(4) - T(2) * t) * t;
}

// Cubic
template<FloatingPoint T>
[[nodiscard]] constexpr T easeInCubic(T t) noexcept {
    return t * t * t;
}

template<FloatingPoint T>
[[nodiscard]] constexpr T easeOutCubic(T t) noexcept {
    T f = t - T(1);
    return f * f * f + T(1);
}

template<FloatingPoint T>
[[nodiscard]] constexpr T easeInOutCubic(T t) noexcept {
    return t < T(0.5) ? T(4) * t * t * t : (t - T(1)) * (T(2) * t - T(2)) * (T(2) * t - T(2)) + T(1);
}

// Quartic
template<FloatingPoint T>
[[nodiscard]] constexpr T easeInQuart(T t) noexcept {
    return t * t * t * t;
}

template<FloatingPoint T>
[[nodiscard]] constexpr T easeOutQuart(T t) noexcept {
    T f = t - T(1);
    return T(1) - f * f * f * f;
}

template<FloatingPoint T>
[[nodiscard]] constexpr T easeInOutQuart(T t) noexcept {
    if (t < T(0.5)) {
        return T(8) * t * t * t * t;
    }
    T f = t - T(1);
    return T(1) - T(8) * f * f * f * f;
}

// Quintic
template<FloatingPoint T>
[[nodiscard]] constexpr T easeInQuint(T t) noexcept {
    return t * t * t * t * t;
}

template<FloatingPoint T>
[[nodiscard]] constexpr T easeOutQuint(T t) noexcept {
    T f = t - T(1);
    return f * f * f * f * f + T(1);
}

template<FloatingPoint T>
[[nodiscard]] constexpr T easeInOutQuint(T t) noexcept {
    if (t < T(0.5)) {
        return T(16) * t * t * t * t * t;
    }
    T f = t - T(1);
    return T(16) * f * f * f * f * f + T(1);
}

// Sine
template<FloatingPoint T>
[[nodiscard]] inline T easeInSine(T t) noexcept {
    return T(1) - std::cos(t * kHalfPiT<T>);
}

template<FloatingPoint T>
[[nodiscard]] inline T easeOutSine(T t) noexcept {
    return std::sin(t * kHalfPiT<T>);
}

template<FloatingPoint T>
[[nodiscard]] inline T easeInOutSine(T t) noexcept {
    return T(0.5) * (T(1) - std::cos(kPiT<T> * t));
}

// Exponential
template<FloatingPoint T>
[[nodiscard]] inline T easeInExpo(T t) noexcept {
    return t == T(0) ? T(0) : std::pow(T(2), T(10) * (t - T(1)));
}

template<FloatingPoint T>
[[nodiscard]] inline T easeOutExpo(T t) noexcept {
    return t == T(1) ? T(1) : T(1) - std::pow(T(2), T(-10) * t);
}

template<FloatingPoint T>
[[nodiscard]] inline T easeInOutExpo(T t) noexcept {
    if (t == T(0)) {
        return T(0);
    }
    if (t == T(1)) {
        return T(1);
    }
    if (t < T(0.5)) {
        return T(0.5) * std::pow(T(2), T(20) * t - T(10));
    }
    return T(1) - T(0.5) * std::pow(T(2), T(-20) * t + T(10));
}

// Circular
template<FloatingPoint T>
[[nodiscard]] inline T easeInCirc(T t) noexcept {
    return T(1) - std::sqrt(T(1) - t * t);
}

template<FloatingPoint T>
[[nodiscard]] inline T easeOutCirc(T t) noexcept {
    T f = t - T(1);
    return std::sqrt(T(1) - f * f);
}

template<FloatingPoint T>
[[nodiscard]] inline T easeInOutCirc(T t) noexcept {
    if (t < T(0.5)) {
        return T(0.5) * (T(1) - std::sqrt(T(1) - T(4) * t * t));
    }
    T f = T(2) * t - T(2);
    return T(0.5) * (std::sqrt(T(1) - f * f) + T(1));
}

// Back (overshoot)
template<FloatingPoint T>
[[nodiscard]] constexpr T easeInBack(T t) noexcept {
    constexpr T c1 = T(1.70158);
    constexpr T c3 = c1 + T(1);
    return c3 * t * t * t - c1 * t * t;
}

template<FloatingPoint T>
[[nodiscard]] constexpr T easeOutBack(T t) noexcept {
    constexpr T c1 = T(1.70158);
    constexpr T c3 = c1 + T(1);
    T f = t - T(1);
    return T(1) + c3 * f * f * f + c1 * f * f;
}

template<FloatingPoint T>
[[nodiscard]] constexpr T easeInOutBack(T t) noexcept {
    constexpr T c1 = T(1.70158);
    constexpr T c2 = c1 * T(1.525);
    if (t < T(0.5)) {
        return T(0.5) * (T(4) * t * t * ((c2 + T(1)) * T(2) * t - c2));
    }
    T f = T(2) * t - T(2);
    return T(0.5) * (f * f * ((c2 + T(1)) * f + c2) + T(2));
}

// Elastic
template<FloatingPoint T>
[[nodiscard]] inline T easeInElastic(T t) noexcept {
    if (t == T(0) || t == T(1)) {
        return t;
    }
    return -std::pow(T(2), T(10) * t - T(10)) * std::sin((t * T(10) - T(10.75)) * kTwoPiT<T> / T(3));
}

template<FloatingPoint T>
[[nodiscard]] inline T easeOutElastic(T t) noexcept {
    if (t == T(0) || t == T(1)) {
        return t;
    }
    return std::pow(T(2), T(-10) * t) * std::sin((t * T(10) - T(0.75)) * kTwoPiT<T> / T(3)) + T(1);
}

template<FloatingPoint T>
[[nodiscard]] inline T easeInOutElastic(T t) noexcept {
    if (t == T(0) || t == T(1)) {
        return t;
    }
    if (t < T(0.5)) {
        return T(-0.5) * std::pow(T(2), T(20) * t - T(10)) * std::sin((T(20) * t - T(11.125)) * kTwoPiT<T> / T(4.5));
    }
    return std::pow(T(2), T(-20) * t + T(10)) * std::sin((T(20) * t - T(11.125)) * kTwoPiT<T> / T(4.5)) * T(0.5) + T(1);
}

// Bounce
template<FloatingPoint T>
[[nodiscard]] constexpr T easeOutBounce(T t) noexcept {
    constexpr T n1 = T(7.5625);
    constexpr T d1 = T(2.75);

    if (t < T(1) / d1) {
        return n1 * t * t;
    }
    if (t < T(2) / d1) {
        T f = t - T(1.5) / d1;
        return n1 * f * f + T(0.75);
    }
    if (t < T(2.5) / d1) {
        T f = t - T(2.25) / d1;
        return n1 * f * f + T(0.9375);
    }
    T f = t - T(2.625) / d1;
    return n1 * f * f + T(0.984375);
}

template<FloatingPoint T>
[[nodiscard]] constexpr T easeInBounce(T t) noexcept {
    return T(1) - easeOutBounce(T(1) - t);
}

template<FloatingPoint T>
[[nodiscard]] constexpr T easeInOutBounce(T t) noexcept {
    return t < T(0.5) ? (T(1) - easeOutBounce(T(1) - T(2) * t)) * T(0.5)
                      : (T(1) + easeOutBounce(T(2) * t - T(1))) * T(0.5);
}

/**
 * @brief Attempt to dispatch easing based on type enum.
 *
 * @param type Easing function type
 * @param t Value in [0,1] range
 * @return Eased value
 */
template<FloatingPoint T>
[[nodiscard]] inline T ease(EaseType type, T t) noexcept {
    switch (type) {
        case EaseType::eLinear:
            return easeLinear(t);
        case EaseType::eQuadIn:
            return easeInQuad(t);
        case EaseType::eQuadOut:
            return easeOutQuad(t);
        case EaseType::eQuadInOut:
            return easeInOutQuad(t);
        case EaseType::eCubicIn:
            return easeInCubic(t);
        case EaseType::eCubicOut:
            return easeOutCubic(t);
        case EaseType::eCubicInOut:
            return easeInOutCubic(t);
        case EaseType::eQuartIn:
            return easeInQuart(t);
        case EaseType::eQuartOut:
            return easeOutQuart(t);
        case EaseType::eQuartInOut:
            return easeInOutQuart(t);
        case EaseType::eQuintIn:
            return easeInQuint(t);
        case EaseType::eQuintOut:
            return easeOutQuint(t);
        case EaseType::eQuintInOut:
            return easeInOutQuint(t);
        case EaseType::eSineIn:
            return easeInSine(t);
        case EaseType::eSineOut:
            return easeOutSine(t);
        case EaseType::eSineInOut:
            return easeInOutSine(t);
        case EaseType::eExpoIn:
            return easeInExpo(t);
        case EaseType::eExpoOut:
            return easeOutExpo(t);
        case EaseType::eExpoInOut:
            return easeInOutExpo(t);
        case EaseType::eCircIn:
            return easeInCirc(t);
        case EaseType::eCircOut:
            return easeOutCirc(t);
        case EaseType::eCircInOut:
            return easeInOutCirc(t);
        case EaseType::eBackIn:
            return easeInBack(t);
        case EaseType::eBackOut:
            return easeOutBack(t);
        case EaseType::eBackInOut:
            return easeInOutBack(t);
        case EaseType::eElasticIn:
            return easeInElastic(t);
        case EaseType::eElasticOut:
            return easeOutElastic(t);
        case EaseType::eElasticInOut:
            return easeInOutElastic(t);
        case EaseType::eBounceIn:
            return easeInBounce(t);
        case EaseType::eBounceOut:
            return easeOutBounce(t);
        case EaseType::eBounceInOut:
            return easeInOutBounce(t);
        default:
            return t;
    }
}

// ============================================================================
// Animation Helpers
// ============================================================================

/**
 * @brief Exponential damping for smooth following.
 *
 * Attempt to smoothly move current towards target.
 * Frame-rate independent with proper dt handling.
 *
 * @param current Current value
 * @param target Target value
 * @param smoothing Smoothing factor (higher = slower, 0 = instant)
 * @param dt Delta time
 * @return New current value
 */
template<typename T, FloatingPoint U>
[[nodiscard]] inline T damp(const T& current, const T& target, U smoothing, U dt) noexcept {
    return lerp(current, target, U(1) - std::exp(-dt / smoothing));
}

/**
 * @brief Attempt to provide critically damped spring physics.
 *
 * Attempt to smoothly move to target without oscillation.
 *
 * @param position Current position (modified in place)
 * @param velocity Current velocity (modified in place)
 * @param target Target position
 * @param omega Natural frequency (higher = faster)
 * @param dt Delta time
 */
template<typename T, FloatingPoint U>
inline void springDamperCritical(T& position, T& velocity, const T& target, U omega, U dt) noexcept {
    T delta = position - target;
    T temp = (velocity + omega * delta) * dt;
    U exp_term = std::exp(-omega * dt);
    velocity = (velocity - omega * temp) * exp_term;
    position = target + (delta + temp) * exp_term;
}

}  // namespace vne::math

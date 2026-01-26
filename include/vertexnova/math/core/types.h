#pragma once
/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Author:    Ajeet Singh Yadav
 * Created:   January 2026
 *
 * Autodoc:   yes
 * ----------------------------------------------------------------------
 */

/**
 * @file types.h
 * @brief Core type definitions, concepts, and traits for the math library.
 *
 * This file provides:
 * - GraphicsApi enums and traits for runtime API selection
 * - C++20 concepts for type constraints
 * - Forward declarations for core math types
 * - Type aliases for vectors, matrices, and quaternions
 * - Core constants and utility functions required by templated types
 *
 * This file contains essential constants (kEpsilon, kPiT) and utility
 * functions (clamp, lerp, approxEqual, degToRad) that are required by
 * vec.h, mat.h, and quat.h templates.
 *
 * For additional math utilities, see math_utils.h
 * For non-templated constants, see constants.h
 */

#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace vne::math {

// ============================================================================
// Graphics API Enum
// ============================================================================

/**
 * @enum GraphicsApi
 * @brief Specifies the target graphics API for projection matrices.
 *
 * Different graphics APIs have different conventions for:
 * - Clip space depth range: [-1, 1] (OpenGL) vs [0, 1] (others)
 * - NDC Y-axis direction: +Y up (OpenGL, Metal, DirectX, WebGPU) vs +Y down (Vulkan)
 * - Framebuffer origin: top-left (Vulkan, Metal, DirectX, WebGPU) vs bottom-left (OpenGL)
 *
 * Note: Coordinate system handedness is best treated as an engine/world convention,
 * not an API property. The kHandedness trait is provided for convenience but should
 * be overridden based on your engine's chosen world convention.
 */
enum class GraphicsApi : uint8_t {
    eOpenGL,   ///< OpenGL: depth [-1,1], NDC Y-up, framebuffer origin bottom-left
    eVulkan,   ///< Vulkan: depth [0,1], NDC Y-down, framebuffer origin top-left
    eMetal,    ///< Metal: depth [0,1], NDC Y-up, framebuffer origin top-left
    eDirectX,  ///< DirectX: depth [0,1], NDC Y-up, framebuffer origin top-left
    eWebGPU    ///< WebGPU: depth [0,1], NDC Y-up, framebuffer origin top-left
};

/**
 * @enum ClipSpaceDepth
 * @brief Specifies the clip space depth range.
 */
enum class ClipSpaceDepth : uint8_t {
    eNegativeOneToOne,  ///< [-1, 1] - OpenGL convention
    eZeroToOne          ///< [0, 1] - Vulkan/Metal/DirectX/WebGPU convention
};

/**
 * @enum Handedness
 * @brief Specifies the coordinate system handedness.
 *
 * Note: Handedness is best treated as an engine/world convention, not an API property.
 * Choose one handedness for your engine and use it consistently across all backends.
 * The API traits provide defaults but you should override based on your engine's choice.
 */
enum class Handedness : uint8_t {
    eLeft,  ///< Left-handed coordinate system
    eRight  ///< Right-handed coordinate system
};

// ============================================================================
// Graphics API Traits
// ============================================================================

/**
 * @brief Compile-time traits for graphics API conventions.
 */
template<GraphicsApi Api>
struct GraphicsApiTraits;

template<>
struct GraphicsApiTraits<GraphicsApi::eOpenGL> {
    static constexpr ClipSpaceDepth kDepth = ClipSpaceDepth::eNegativeOneToOne;
    static constexpr Handedness kHandedness = Handedness::eRight;
    /// Whether to flip Y in the projection matrix (for NDC Y-down APIs like Vulkan)
    static constexpr bool kProjectionYFlip = false;
    /// Whether screen-space/framebuffer coordinates use top-left origin
    static constexpr bool kScreenOriginTopLeft = false;
    /// @deprecated Use kScreenOriginTopLeft instead. Kept for backward compatibility.
    static constexpr bool kFlipY = kScreenOriginTopLeft;
};

template<>
struct GraphicsApiTraits<GraphicsApi::eVulkan> {
    static constexpr ClipSpaceDepth kDepth = ClipSpaceDepth::eZeroToOne;
    static constexpr Handedness kHandedness = Handedness::eRight;
    /// Vulkan NDC is Y-down, so we flip Y in projection matrix (or use VK_KHR_maintenance1 viewport)
    static constexpr bool kProjectionYFlip = true;
    /// Vulkan framebuffer origin is top-left
    static constexpr bool kScreenOriginTopLeft = true;
    /// @deprecated Use kScreenOriginTopLeft instead. Kept for backward compatibility.
    static constexpr bool kFlipY = kScreenOriginTopLeft;
};

template<>
struct GraphicsApiTraits<GraphicsApi::eMetal> {
    static constexpr ClipSpaceDepth kDepth = ClipSpaceDepth::eZeroToOne;
    static constexpr Handedness kHandedness = Handedness::eLeft;
    /// Metal NDC is Y-up, no projection flip needed
    static constexpr bool kProjectionYFlip = false;
    /// Metal framebuffer origin is top-left
    static constexpr bool kScreenOriginTopLeft = true;
    /// @deprecated Use kScreenOriginTopLeft instead. Kept for backward compatibility.
    static constexpr bool kFlipY = kScreenOriginTopLeft;
};

template<>
struct GraphicsApiTraits<GraphicsApi::eDirectX> {
    static constexpr ClipSpaceDepth kDepth = ClipSpaceDepth::eZeroToOne;
    static constexpr Handedness kHandedness = Handedness::eLeft;
    /// DirectX NDC is Y-up, no projection flip needed
    static constexpr bool kProjectionYFlip = false;
    /// DirectX framebuffer origin is top-left
    static constexpr bool kScreenOriginTopLeft = true;
    /// @deprecated Use kScreenOriginTopLeft instead. Kept for backward compatibility.
    static constexpr bool kFlipY = kScreenOriginTopLeft;
};

template<>
struct GraphicsApiTraits<GraphicsApi::eWebGPU> {
    static constexpr ClipSpaceDepth kDepth = ClipSpaceDepth::eZeroToOne;
    static constexpr Handedness kHandedness = Handedness::eRight;
    /// WebGPU NDC is Y-up, no projection flip needed
    static constexpr bool kProjectionYFlip = false;
    /// WebGPU framebuffer origin is top-left
    static constexpr bool kScreenOriginTopLeft = true;
    /// @deprecated Use kScreenOriginTopLeft instead. Kept for backward compatibility.
    static constexpr bool kFlipY = kScreenOriginTopLeft;
};

// ============================================================================
// Runtime API Traits Helper
// ============================================================================

/**
 * @brief Runtime query for graphics API depth range.
 */
[[nodiscard]] constexpr ClipSpaceDepth getClipSpaceDepth(GraphicsApi api) noexcept {
    switch (api) {
        case GraphicsApi::eOpenGL:
            return ClipSpaceDepth::eNegativeOneToOne;
        default:
            return ClipSpaceDepth::eZeroToOne;
    }
}

/**
 * @brief Runtime query for default handedness for a given API.
 *
 * Note: For a multi-backend engine, prefer choosing handedness as an engine/world
 * convention and generating view/projection matrices accordingly, rather than
 * relying on this API-based default.
 */
[[nodiscard]] constexpr Handedness getHandedness(GraphicsApi api) noexcept {
    switch (api) {
        case GraphicsApi::eMetal:
        case GraphicsApi::eDirectX:
            return Handedness::eLeft;
        default:
            return Handedness::eRight;
    }
}

/**
 * @brief Runtime query for whether a projection-matrix Y flip is needed.
 *
 * Use this only if you want to bake Vulkan's NDC Y inversion into the projection
 * matrix (instead of flipping the viewport via VK_KHR_maintenance1).
 *
 * For Metal/DirectX/WebGPU, NDC Y is already +up, so NO projection Y flip is needed.
 * Only Vulkan has NDC Y-down by default.
 */
[[nodiscard]] constexpr bool needsProjectionYFlip(GraphicsApi api) noexcept {
    switch (api) {
        case GraphicsApi::eVulkan:
            return true;
        default:
            return false;
    }
}

/**
 * @brief Runtime query for whether screen-space uses a top-left origin.
 *
 * This is used by project/unproject helpers that operate in screen (pixel) coordinates.
 * Most modern APIs (Vulkan, Metal, DirectX, WebGPU) use top-left origin for framebuffers,
 * while OpenGL traditionally uses bottom-left.
 */
[[nodiscard]] constexpr bool screenOriginIsTopLeft(GraphicsApi api) noexcept {
    switch (api) {
        case GraphicsApi::eVulkan:
        case GraphicsApi::eMetal:
        case GraphicsApi::eDirectX:
        case GraphicsApi::eWebGPU:
            return true;
        default:
            return false;
    }
}

/**
 * @brief Runtime query for whether a screen-space Y-axis flip is needed.
 *
 * @deprecated Use screenOriginIsTopLeft() for screen-space coordinate handling,
 * or needsProjectionYFlip() for projection matrix Y inversion.
 *
 * This function returns true when screen-space (pixel) coordinates use top-left
 * origin, which is the case for Vulkan/Metal/DirectX/WebGPU.
 */
[[nodiscard]] constexpr bool needsYFlip(GraphicsApi api) noexcept {
    return screenOriginIsTopLeft(api);
}

/**
 * @brief Returns a human-readable name for a graphics API.
 */
[[nodiscard]] constexpr const char* graphicsApiName(GraphicsApi api) noexcept {
    switch (api) {
        case GraphicsApi::eOpenGL:
            return "OpenGL";
        case GraphicsApi::eVulkan:
            return "Vulkan";
        case GraphicsApi::eMetal:
            return "Metal";
        case GraphicsApi::eDirectX:
            return "DirectX";
        case GraphicsApi::eWebGPU:
            return "WebGPU";
        default:
            return "Unknown";
    }
}

// ============================================================================
// C++20 Concepts
// ============================================================================

/**
 * @concept Arithmetic
 * @brief Constrains to arithmetic types (integral or floating-point).
 */
template<typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

/**
 * @concept FloatingPoint
 * @brief Constrains to floating-point types.
 */
template<typename T>
concept FloatingPoint = std::is_floating_point_v<T>;

/**
 * @concept Integral
 * @brief Constrains to integral types.
 */
template<typename T>
concept Integral = std::is_integral_v<T>;

/**
 * @concept SignedArithmetic
 * @brief Constrains to signed arithmetic types.
 */
template<typename T>
concept SignedArithmetic = Arithmetic<T> && std::is_signed_v<T>;

// ============================================================================
// Forward Declarations
// ============================================================================

template<typename T, size_t N>
    requires Arithmetic<T>
class Vec;

template<typename T, size_t R, size_t C>
    requires FloatingPoint<T>
class Mat;

template<typename T>
    requires FloatingPoint<T>
class Quat;

// ============================================================================
// Vector Type Aliases
// ============================================================================

/// @name 2D Vector Aliases
/// @{
template<typename T>
using Vec2 = Vec<T, 2>;

using Vec2f = Vec2<float>;
using Vec2d = Vec2<double>;
using Vec2i = Vec2<int32_t>;
using Vec2u = Vec2<uint32_t>;
/// @}

/// @name 3D Vector Aliases
/// @{
template<typename T>
using Vec3 = Vec<T, 3>;

using Vec3f = Vec3<float>;
using Vec3d = Vec3<double>;
using Vec3i = Vec3<int32_t>;
using Vec3u = Vec3<uint32_t>;
/// @}

/// @name 4D Vector Aliases
/// @{
template<typename T>
using Vec4 = Vec<T, 4>;

using Vec4f = Vec4<float>;
using Vec4d = Vec4<double>;
using Vec4i = Vec4<int32_t>;
using Vec4u = Vec4<uint32_t>;
/// @}

// ============================================================================
// Matrix Type Aliases
// ============================================================================

/// @name 2x2 Matrix Aliases
/// @{
template<typename T>
using Mat2 = Mat<T, 2, 2>;

using Mat2f = Mat2<float>;
using Mat2d = Mat2<double>;
/// @}

/// @name 3x3 Matrix Aliases
/// @{
template<typename T>
using Mat3 = Mat<T, 3, 3>;

using Mat3f = Mat3<float>;
using Mat3d = Mat3<double>;
/// @}

/// @name 4x4 Matrix Aliases
/// @{
template<typename T>
using Mat4 = Mat<T, 4, 4>;

using Mat4f = Mat4<float>;
using Mat4d = Mat4<double>;

// Backward-compatible aliases (matching old class names)
using Mat3x3f = Mat3f;
using Mat4x4f = Mat4f;
/// @}

// ============================================================================
// Quaternion Type Aliases
// ============================================================================

using Quatf = Quat<float>;
using Quatd = Quat<double>;

// ============================================================================
// Core Math Constants (Required by vec.h, mat.h, quat.h)
// ============================================================================

/// @brief Default epsilon for floating-point comparisons (templated)
template<FloatingPoint T>
inline constexpr T kEpsilon = T(1e-6);

template<>
inline constexpr float kEpsilon<float> = 1e-6f;

template<>
inline constexpr double kEpsilon<double> = 1e-12;

/**
 * @brief Returns default epsilon for any Arithmetic type.
 *
 * This helper is needed because MSVC evaluates default parameter expressions
 * even when the requires clause would prevent the function from being instantiated.
 * For floating-point types, returns kEpsilon<T>. For integral types, returns 0.
 */
template<Arithmetic T>
[[nodiscard]] constexpr T defaultEpsilon() noexcept {
    if constexpr (FloatingPoint<T>) {
        return kEpsilon<T>;
    } else {
        return T(0);
    }
}

/// @brief Pi constant (templated)
template<FloatingPoint T>
inline constexpr T kPiT = T(3.14159265358979323846);

/// @brief Two times Pi (templated)
template<FloatingPoint T>
inline constexpr T kTwoPiT = T(2) * kPiT<T>;

/// @brief Half of Pi (templated)
template<FloatingPoint T>
inline constexpr T kHalfPiT = kPiT<T> / T(2);

/// @brief One over Pi (templated)
template<FloatingPoint T>
inline constexpr T kOneOverPiT = T(1) / kPiT<T>;

/// @brief One over Two times Pi (templated)
template<FloatingPoint T>
inline constexpr T kOneOverTwoPiT = T(1) / (T(2) * kPiT<T>);

/// @brief Degrees to radians conversion factor (templated)
template<FloatingPoint T>
inline constexpr T kDegToRadT = kPiT<T> / T(180);

/// @brief Radians to degrees conversion factor (templated)
template<FloatingPoint T>
inline constexpr T kRadToDegT = T(180) / kPiT<T>;

// ============================================================================
// Core Utility Functions (Required by vec.h, mat.h, quat.h)
// ============================================================================

/**
 * @brief Converts degrees to radians.
 * @tparam T Floating-point type
 * @param degrees Angle in degrees
 * @return Angle in radians
 */
template<FloatingPoint T>
[[nodiscard]] constexpr T degToRad(T degrees) noexcept {
    return degrees * kDegToRadT<T>;
}

/**
 * @brief Converts radians to degrees.
 * @tparam T Floating-point type
 * @param radians Angle in radians
 * @return Angle in degrees
 */
template<FloatingPoint T>
[[nodiscard]] constexpr T radToDeg(T radians) noexcept {
    return radians * kRadToDegT<T>;
}

/**
 * @brief Computes the absolute value.
 * @tparam T Arithmetic type
 * @param val Input value
 * @return Absolute value
 */
template<Arithmetic T>
[[nodiscard]] constexpr T abs(T val) noexcept {
    return val < T(0) ? -val : val;
}

/**
 * @brief Computes the sign of a value.
 * @tparam T Arithmetic type
 * @param val Input value
 * @param eps Threshold value (values > eps are positive, < eps are negative)
 * @return 1 if val > eps, -1 if val < eps, 0 if val == eps
 */
template<Arithmetic T>
[[nodiscard]] constexpr T sign(T val, T eps = T(0)) noexcept {
    return (val > eps ? T(1) : (val < eps ? T(-1) : T(0)));
}

/**
 * @brief Returns the minimum of two values.
 * @tparam T Arithmetic type
 * @param a First value
 * @param b Second value
 * @return Minimum value
 */
template<Arithmetic T>
[[nodiscard]] constexpr T min(T a, T b) noexcept {
    return a <= b ? a : b;
}

/**
 * @brief Returns the maximum of two values.
 * @tparam T Arithmetic type
 * @param a First value
 * @param b Second value
 * @return Maximum value
 */
template<Arithmetic T>
[[nodiscard]] constexpr T max(T a, T b) noexcept {
    return a >= b ? a : b;
}

/**
 * @brief Returns the minimum of three values.
 * @tparam T Arithmetic type
 */
template<Arithmetic T>
[[nodiscard]] constexpr T min(T a, T b, T c) noexcept {
    return min(min(a, b), c);
}

/**
 * @brief Returns the maximum of three values.
 * @tparam T Arithmetic type
 */
template<Arithmetic T>
[[nodiscard]] constexpr T max(T a, T b, T c) noexcept {
    return max(max(a, b), c);
}

/**
 * @brief Clamps a value between min and max.
 * @tparam T Arithmetic type
 * @param value The value to clamp
 * @param min_val Minimum bound
 * @param max_val Maximum bound
 * @return Clamped value
 */
template<Arithmetic T>
[[nodiscard]] constexpr T clamp(T value, T min_val, T max_val) noexcept {
    return value < min_val ? min_val : (value > max_val ? max_val : value);
}

/**
 * @brief Clamps a value between 0 and 1.
 * @tparam T Arithmetic type
 * @param val Value to saturate
 * @return Value clamped to [0, 1]
 */
template<Arithmetic T>
[[nodiscard]] constexpr T saturate(T val) noexcept {
    return clamp(val, T(0), T(1));
}

/**
 * @brief Sorts two values so that *a <= *b.
 * @tparam T Arithmetic type
 * @param a Pointer to first value
 * @param b Pointer to second value
 */
template<Arithmetic T>
constexpr void arrangeMinMax(T* a, T* b) noexcept {
    if (*a > *b) {
        T temp = *a;
        *a = *b;
        *b = temp;
    }
}

/**
 * @brief Computes the square of a value.
 * @tparam T Arithmetic type
 * @param val Input value
 * @return val * val
 */
template<Arithmetic T>
[[nodiscard]] constexpr T square(T val) noexcept {
    return val * val;
}

/**
 * @brief Computes the cube of a value.
 * @tparam T Arithmetic type
 * @param val Input value
 * @return val * val * val
 */
template<Arithmetic T>
[[nodiscard]] constexpr T cube(T val) noexcept {
    return val * val * val;
}

/**
 * @brief Checks if two values are approximately equal.
 *
 * Uses absolute epsilon comparison: |a - b| <= epsilon
 *
 * @tparam T Floating-point type
 * @param a First value
 * @param b Second value
 * @param epsilon Tolerance (default: kEpsilon<T>)
 * @return true if |a - b| <= epsilon
 */
template<FloatingPoint T>
[[nodiscard]] constexpr bool approxEqual(T a, T b, T epsilon = kEpsilon<T>) noexcept {
    T diff = a - b;
    return diff >= -epsilon && diff <= epsilon;
}

/**
 * @brief Checks if a floating-point value is approximately zero.
 *
 * Uses absolute epsilon comparison: |value| <= epsilon
 *
 * @tparam T Floating-point type
 * @param value The value to check
 * @param epsilon Tolerance (default: kEpsilon<T>)
 * @return true if |value| <= epsilon
 */
template<FloatingPoint T>
[[nodiscard]] constexpr bool isZero(T value, T epsilon = kEpsilon<T>) noexcept {
    return value >= -epsilon && value <= epsilon;
}

/**
 * @brief Checks if an integral value is zero.
 * @tparam T Integral type
 * @param value The value to check
 * @param eps Unused (for API consistency with floating-point version)
 * @return true if value == 0
 */
template<Integral T>
[[nodiscard]] constexpr bool isZero(T value, T /*eps*/ = T(0)) noexcept {
    return value == T(0);
}

/**
 * @brief Linear interpolation between two values.
 *
 * Computes a + t * (b - a) for t in [0, 1].
 *
 * @tparam T Floating-point type
 * @param a Start value (returned when t = 0)
 * @param b End value (returned when t = 1)
 * @param t Interpolation factor [0, 1]
 * @return Interpolated value
 */
template<FloatingPoint T>
[[nodiscard]] constexpr T lerp(T a, T b, T t) noexcept {
    return a + t * (b - a);
}

/**
 * @brief BiLinear interpolation.
 *
 * Interpolates between four corner values using two interpolation factors.
 *
 * @tparam T Floating-point type
 * @param c00 Value at (0, 0)
 * @param c10 Value at (1, 0)
 * @param c01 Value at (0, 1)
 * @param c11 Value at (1, 1)
 * @param tx Interpolation factor in x direction [0, 1]
 * @param ty Interpolation factor in y direction [0, 1]
 * @return Bilinearly interpolated value
 */
template<FloatingPoint T>
[[nodiscard]] constexpr T biLerp(T c00, T c10, T c01, T c11, T tx, T ty) noexcept {
    T a = lerp(c00, c10, tx);
    T b = lerp(c01, c11, tx);
    return lerp(a, b, ty);
}

/**
 * @brief Checks if a value is in the interval [min_val, max_val].
 * @tparam T Arithmetic type
 * @param val Value to check
 * @param min_val Minimum bound
 * @param max_val Maximum bound
 * @param eps Tolerance to extend the interval
 * @return true if val is within [min_val - eps, max_val + eps]
 */
template<Arithmetic T>
[[nodiscard]] constexpr bool isInBetween(T val, T min_val, T max_val, T eps = T(0)) noexcept {
    T lo = min_val <= max_val ? min_val : max_val;
    T hi = min_val <= max_val ? max_val : min_val;
    return val >= lo - eps && val <= hi + eps;
}

}  // namespace vne::math

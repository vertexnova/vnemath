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
 * - GraphicsApi enum for runtime API selection
 * - C++20 concepts for type constraints
 * - Forward declarations for core math types
 * - Common type aliases
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
 * - NDC Y-axis direction: +Y up (OpenGL, DirectX) vs +Y down (Vulkan, Metal, WebGPU)
 * - Coordinate system handedness: left-handed vs right-handed
 */
enum class GraphicsApi : uint8_t {
    eOpenGL,   ///< OpenGL: depth [-1,1], Y-up, right-handed
    eVulkan,   ///< Vulkan: depth [0,1], Y-down, right-handed
    eMetal,    ///< Metal: depth [0,1], Y-down, left-handed
    eDirectX,  ///< DirectX: depth [0,1], Y-up, left-handed
    eWebGPU    ///< WebGPU: depth [0,1], Y-down, right-handed
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
 */
enum class Handedness : uint8_t {
    eLeft,  ///< Left-handed (Metal, DirectX)
    eRight  ///< Right-handed (OpenGL, Vulkan, WebGPU)
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
    static constexpr ClipSpaceDepth depth = ClipSpaceDepth::eNegativeOneToOne;
    static constexpr Handedness handedness = Handedness::eRight;
    static constexpr bool flipY = false;
};

template<>
struct GraphicsApiTraits<GraphicsApi::eVulkan> {
    static constexpr ClipSpaceDepth depth = ClipSpaceDepth::eZeroToOne;
    static constexpr Handedness handedness = Handedness::eRight;
    static constexpr bool flipY = true;
};

template<>
struct GraphicsApiTraits<GraphicsApi::eMetal> {
    static constexpr ClipSpaceDepth depth = ClipSpaceDepth::eZeroToOne;
    static constexpr Handedness handedness = Handedness::eLeft;
    static constexpr bool flipY = true;
};

template<>
struct GraphicsApiTraits<GraphicsApi::eDirectX> {
    static constexpr ClipSpaceDepth depth = ClipSpaceDepth::eZeroToOne;
    static constexpr Handedness handedness = Handedness::eLeft;
    static constexpr bool flipY = false;
};

template<>
struct GraphicsApiTraits<GraphicsApi::eWebGPU> {
    static constexpr ClipSpaceDepth depth = ClipSpaceDepth::eZeroToOne;
    static constexpr Handedness handedness = Handedness::eRight;
    static constexpr bool flipY = true;
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
 * @brief Runtime query for graphics API handedness.
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
 * @brief Runtime query for whether Y-axis flip is needed.
 */
[[nodiscard]] constexpr bool needsYFlip(GraphicsApi api) noexcept {
    switch (api) {
        case GraphicsApi::eVulkan:
        case GraphicsApi::eMetal:
        case GraphicsApi::eWebGPU:
            return true;
        default:
            return false;
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
/// @}

// ============================================================================
// Quaternion Type Aliases
// ============================================================================

using Quatf = Quat<float>;
using Quatd = Quat<double>;

// ============================================================================
// Constants
// ============================================================================

/// @brief Default epsilon for floating-point comparisons
template<FloatingPoint T>
inline constexpr T kEpsilon = T(1e-6);

template<>
inline constexpr float kEpsilon<float> = 1e-6f;

template<>
inline constexpr double kEpsilon<double> = 1e-12;

/// @brief Pi constant
template<FloatingPoint T>
inline constexpr T kPi = T(3.14159265358979323846);

/// @brief Two times Pi
template<FloatingPoint T>
inline constexpr T kTwoPi = T(2) * kPi<T>;

/// @brief Half of Pi
template<FloatingPoint T>
inline constexpr T kHalfPi = kPi<T> / T(2);

/// @brief Degrees to radians conversion factor
template<FloatingPoint T>
inline constexpr T kDegToRad = kPi<T> / T(180);

/// @brief Radians to degrees conversion factor
template<FloatingPoint T>
inline constexpr T kRadToDeg = T(180) / kPi<T>;

// ============================================================================
// Utility Functions
// ============================================================================

/**
 * @brief Converts degrees to radians.
 */
template<FloatingPoint T>
[[nodiscard]] constexpr T degToRad(T degrees) noexcept {
    return degrees * kDegToRad<T>;
}

/**
 * @brief Converts radians to degrees.
 */
template<FloatingPoint T>
[[nodiscard]] constexpr T radToDeg(T radians) noexcept {
    return radians * kRadToDeg<T>;
}

/**
 * @brief Checks if two values are approximately equal.
 */
template<FloatingPoint T>
[[nodiscard]] constexpr bool approxEqual(T a, T b, T epsilon = kEpsilon<T>) noexcept {
    T diff = a - b;
    return diff >= -epsilon && diff <= epsilon;
}

/**
 * @brief Checks if a value is approximately zero.
 */
template<FloatingPoint T>
[[nodiscard]] constexpr bool approxZero(T value, T epsilon = kEpsilon<T>) noexcept {
    return value >= -epsilon && value <= epsilon;
}

/**
 * @brief Clamps a value between min and max.
 */
template<Arithmetic T>
[[nodiscard]] constexpr T clamp(T value, T min_val, T max_val) noexcept {
    return value < min_val ? min_val : (value > max_val ? max_val : value);
}

/**
 * @brief Linear interpolation between two values.
 */
template<FloatingPoint T>
[[nodiscard]] constexpr T lerp(T a, T b, T t) noexcept {
    return a + t * (b - a);
}

}  // namespace vne::math

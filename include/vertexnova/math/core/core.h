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
 * @file core.h
 * @brief Main include file for the templated math library core.
 *
 * This header provides access to all core templated math types:
 * - Vec<T, N>: N-dimensional vectors
 * - Mat<T, R, C>: R x C matrices
 * - Quat<T>: Quaternions for rotations
 *
 * Type aliases are provided for common use cases:
 * - Vec2f, Vec3f, Vec4f, Vec2d, Vec3d, Vec4d, Vec2i, Vec3i, Vec4i
 * - Mat2f, Mat3f, Mat4f, Mat2d, Mat3d, Mat4d
 * - Quatf, Quatd
 *
 * Graphics API support is built-in for:
 * - OpenGL (depth [-1,1], right-handed, Y-up)
 * - Vulkan (depth [0,1], right-handed, Y-down)
 * - Metal (depth [0,1], left-handed, Y-down)
 * - DirectX (depth [0,1], left-handed, Y-up)
 * - WebGPU (depth [0,1], right-handed, Y-down)
 *
 * @example
 * ```cpp
 * #include <vertexnova/math/core/core.h>
 *
 * using namespace vne::math;
 *
 * // Create vectors
 * Vec3f position(1.0f, 2.0f, 3.0f);
 * Vec3d velocity(0.1, 0.2, 0.3);
 *
 * // Create matrices with graphics API support
 * Mat4f view = Mat4f::lookAt(eye, center, up, GraphicsApi::eVulkan);
 * Mat4f proj = Mat4f::perspective(fov, aspect, near, far, GraphicsApi::eVulkan);
 *
 * // Create quaternions
 * Quatf rotation = Quatf::fromAxisAngle(Vec3f::yAxis(), degToRad(90.0f));
 * Vec3f rotated = rotation.rotate(position);
 * ```
 */

// Core types and concepts
#include "types.h"

// Templated math types
#include "vec.h"
#include "mat.h"
#include "quat.h"

namespace vne::math {

/**
 * @brief Namespace containing all core templated math types.
 *
 * The core namespace provides modern C++20 templated math types
 * that can work with any arithmetic type (for vectors) or
 * floating-point type (for matrices and quaternions).
 *
 * Key features:
 * - Type-safe operations using C++20 concepts
 * - GLM backend for optimized float/double operations
 * - Graphics API-agnostic projection matrices
 * - Compile-time and runtime flexibility
 */

// ============================================================================
// Common Transform Helpers
// ============================================================================

/**
 * @brief Creates a model matrix from position, rotation, and scale.
 * @tparam T Floating-point type
 * @param position World position
 * @param rotation Rotation quaternion
 * @param scale Scale factor (uniform or per-axis)
 * @return The model matrix
 */
template<FloatingPoint T>
[[nodiscard]] inline Mat<T, 4, 4> modelMatrix(const Vec<T, 3>& position,
                                              const Quat<T>& rotation,
                                              const Vec<T, 3>& scale) noexcept {
    Mat<T, 4, 4> result = rotation.toMatrix4();
    result[0] *= scale.x();
    result[1] *= scale.y();
    result[2] *= scale.z();
    result[3] = Vec<T, 4>(position, T(1));
    return result;
}

/**
 * @brief Creates a model matrix with uniform scale.
 */
template<FloatingPoint T>
[[nodiscard]] inline Mat<T, 4, 4> modelMatrix(const Vec<T, 3>& position,
                                              const Quat<T>& rotation,
                                              T scale = T(1)) noexcept {
    return modelMatrix(position, rotation, Vec<T, 3>(scale));
}

/**
 * @brief Creates a view-projection matrix for the specified graphics API.
 * @param view The view matrix
 * @param projection The projection matrix
 * @return The combined view-projection matrix
 */
template<FloatingPoint T>
[[nodiscard]] inline Mat<T, 4, 4> viewProjection(const Mat<T, 4, 4>& view, const Mat<T, 4, 4>& projection) noexcept {
    return projection * view;
}

/**
 * @brief Creates a complete MVP matrix.
 */
template<FloatingPoint T>
[[nodiscard]] inline Mat<T, 4, 4> mvp(const Mat<T, 4, 4>& model,
                                      const Mat<T, 4, 4>& view,
                                      const Mat<T, 4, 4>& projection) noexcept {
    return projection * view * model;
}

}  // namespace vne::math

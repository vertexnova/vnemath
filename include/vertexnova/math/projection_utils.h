/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Coordinate space conversion utilities for graphics programming.
 * Supports multi-backend graphics APIs (OpenGL, Vulkan, Metal, DirectX, WebGPU).
 * ----------------------------------------------------------------------
 */

#pragma once

#include "core/mat.h"
#include "core/types.h"
#include "core/vec.h"
#include "geometry/ray.h"
#include "viewport.h"

namespace vne::math {

// ============================================================================
// World-to-Screen Projection
// ============================================================================

/**
 * @brief Projects a 3D world point to 2D screen coordinates.
 *
 * This is the standard gluProject operation.
 *
 * @param world_pos The 3D world position
 * @param mvp The combined Model-View-Projection matrix
 * @param viewport The viewport parameters
 * @param api Graphics API (for Y-flip handling)
 * @return Screen coordinates (x, y) and normalized depth (z)
 *         z is in [0,1] for most APIs, [-1,1] for OpenGL
 */
[[nodiscard]] inline Vec3f project(const Vec3f& world_pos,
                                   const Mat4f& mvp,
                                   const Viewport& viewport,
                                   GraphicsApi api = GraphicsApi::eOpenGL) noexcept {
    // Transform to clip space
    Vec4f clip = mvp * Vec4f(world_pos, 1.0f);

    // Perspective divide to NDC
    if (isZero(clip.w())) {
        return Vec3f(0.0f, 0.0f, -1.0f);  // Behind camera
    }

    Vec3f ndc = clip.xyz() / clip.w();

    // NDC to normalized viewport coordinates [0, 1]
    float sx = (ndc.x() + 1.0f) * 0.5f;
    float sy = (ndc.y() + 1.0f) * 0.5f;

    // Handle screen-space origin convention.
    // Most APIs (Vulkan/Metal/DirectX/WebGPU) use top-left origin for framebuffers.
    if (screenOriginIsTopLeft(api)) {
        sy = 1.0f - sy;
    }

    // Convert normalized coordinates to screen-space pixels
    float screen_x = viewport.x + sx * viewport.width;
    float screen_y = viewport.y + sy * viewport.height;

    // Map depth to viewport range
    float screen_z = viewport.z_near + (ndc.z() + 1.0f) * 0.5f * (viewport.z_far - viewport.z_near);

    // For APIs with [0,1] depth, adjust
    if (getClipSpaceDepth(api) == ClipSpaceDepth::eZeroToOne) {
        screen_z = viewport.z_near + ndc.z() * (viewport.z_far - viewport.z_near);
    }

    return Vec3f(screen_x, screen_y, screen_z);
}

/**
 * @brief Simplified project for common use case.
 */
[[nodiscard]] inline Vec2f projectToScreen(const Vec3f& world_pos,
                                           const Mat4f& mvp,
                                           float screen_width,
                                           float screen_height,
                                           GraphicsApi api = GraphicsApi::eOpenGL) noexcept {
    Vec3f result = project(world_pos, mvp, Viewport(screen_width, screen_height), api);
    return Vec2f(result.x(), result.y());
}

// ============================================================================
// Screen-to-World Unprojection
// ============================================================================

/**
 * @brief Unprojects a 2D screen point to a 3D world position.
 *
 * This is the standard gluUnProject operation.
 *
 * @param screen_pos Screen coordinates (x, y) and depth (z in [0,1])
 * @param inv_mvp The inverse of the Model-View-Projection matrix
 * @param viewport The viewport parameters
 * @param api Graphics API (for Y-flip handling)
 * @return World-space position
 */
[[nodiscard]] inline Vec3f unproject(const Vec3f& screen_pos,
                                     const Mat4f& inv_mvp,
                                     const Viewport& viewport,
                                     GraphicsApi api = GraphicsApi::eOpenGL) noexcept {
    // Screen (pixel) to normalized viewport coordinates [0, 1]
    float sx = (screen_pos.x() - viewport.x) / viewport.width;
    float sy = (screen_pos.y() - viewport.y) / viewport.height;

    // If screen-space uses top-left origin, invert Y to match NDC (+Y up) math
    if (screenOriginIsTopLeft(api)) {
        sy = 1.0f - sy;
    }

    // Normalized viewport to NDC [-1, 1]
    float ndc_x = sx * 2.0f - 1.0f;
    float ndc_y = sy * 2.0f - 1.0f;

    // Unmap depth from viewport range to NDC
    float ndc_z;
    if (getClipSpaceDepth(api) == ClipSpaceDepth::eZeroToOne) {
        ndc_z = (screen_pos.z() - viewport.z_near) / (viewport.z_far - viewport.z_near);
    } else {
        ndc_z = (screen_pos.z() - viewport.z_near) / (viewport.z_far - viewport.z_near) * 2.0f - 1.0f;
    }

    // NDC to clip space (reverse perspective divide)
    Vec4f clip(ndc_x, ndc_y, ndc_z, 1.0f);

    // Transform to world space
    Vec4f world = inv_mvp * clip;

    // Perspective divide
    if (isZero(world.w())) {
        return Vec3f::zero();
    }

    return world.xyz() / world.w();
}

/**
 * @brief Simplified unproject for common use case.
 */
[[nodiscard]] inline Vec3f unprojectFromScreen(const Vec2f& screen_pos,
                                               float depth,
                                               const Mat4f& inv_mvp,
                                               float screen_width,
                                               float screen_height,
                                               GraphicsApi api = GraphicsApi::eOpenGL) noexcept {
    return unproject(Vec3f(screen_pos.x(), screen_pos.y(), depth), inv_mvp, Viewport(screen_width, screen_height), api);
}

// ============================================================================
// Screen-to-World Ray
// ============================================================================

/**
 * @brief Creates a picking ray from screen coordinates.
 *
 * Essential for mouse picking, ray casting, and selection.
 *
 * @param screen_pos Screen coordinates (x, y)
 * @param inv_view_proj Inverse of View-Projection matrix
 * @param viewport The viewport parameters
 * @param camera_pos Camera world position
 * @param api Graphics API (for Y-flip handling)
 * @return World-space ray from camera through screen point
 */
[[nodiscard]] inline Ray screenToWorldRay(const Vec2f& screen_pos,
                                          const Mat4f& inv_view_proj,
                                          const Viewport& viewport,
                                          const Vec3f& camera_pos,
                                          GraphicsApi api = GraphicsApi::eOpenGL) noexcept {
    // Unproject at near plane
    Vec3f near_point = unproject(Vec3f(screen_pos.x(), screen_pos.y(), 0.0f), inv_view_proj, viewport, api);

    // Unproject at far plane
    Vec3f far_point = unproject(Vec3f(screen_pos.x(), screen_pos.y(), 1.0f), inv_view_proj, viewport, api);

    // Create ray from near to far
    Vec3f direction = (far_point - near_point).normalized();

    return Ray(camera_pos, direction);
}

/**
 * @brief Simplified screen-to-ray for common use case.
 */
[[nodiscard]] inline Ray screenToRay(const Vec2f& screen_pos,
                                     const Mat4f& inv_view_proj,
                                     float screen_width,
                                     float screen_height,
                                     const Vec3f& camera_pos,
                                     GraphicsApi api = GraphicsApi::eOpenGL) noexcept {
    return screenToWorldRay(screen_pos, inv_view_proj, Viewport(screen_width, screen_height), camera_pos, api);
}

// ============================================================================
// NDC/Clip Space Utilities
// ============================================================================

/**
 * @brief Converts screen coordinates to normalized device coordinates.
 *
 * @param screen_pos Screen position
 * @param viewport Viewport parameters
 * @param api Graphics API
 * @return NDC coordinates in [-1,1] range
 */
[[nodiscard]] inline Vec2f screenToNDC(const Vec2f& screen_pos,
                                       const Viewport& viewport,
                                       GraphicsApi api = GraphicsApi::eOpenGL) noexcept {
    // Screen (pixel) to normalized viewport coordinates [0, 1]
    float sx = (screen_pos.x() - viewport.x) / viewport.width;
    float sy = (screen_pos.y() - viewport.y) / viewport.height;

    // If screen-space uses top-left origin, invert Y to match NDC (+Y up) math
    if (screenOriginIsTopLeft(api)) {
        sy = 1.0f - sy;
    }

    // Normalized viewport to NDC [-1, 1]
    float ndc_x = sx * 2.0f - 1.0f;
    float ndc_y = sy * 2.0f - 1.0f;

    return Vec2f(ndc_x, ndc_y);
}

/**
 * @brief Converts NDC coordinates to screen coordinates.
 */
[[nodiscard]] inline Vec2f ndcToScreen(const Vec2f& ndc_pos,
                                       const Viewport& viewport,
                                       GraphicsApi api = GraphicsApi::eOpenGL) noexcept {
    // NDC [-1, 1] to normalized viewport coordinates [0, 1]
    float sx = (ndc_pos.x() + 1.0f) * 0.5f;
    float sy = (ndc_pos.y() + 1.0f) * 0.5f;

    // If screen-space uses top-left origin, invert Y
    if (screenOriginIsTopLeft(api)) {
        sy = 1.0f - sy;
    }

    // Normalized viewport to screen (pixel) coordinates
    float screen_x = viewport.x + sx * viewport.width;
    float screen_y = viewport.y + sy * viewport.height;

    return Vec2f(screen_x, screen_y);
}

// ============================================================================
// Depth Utilities
// ============================================================================

/**
 * @brief Linearizes a depth buffer value.
 *
 * Converts from non-linear depth buffer value to linear view-space depth.
 *
 * @param depth Non-linear depth value (from depth buffer)
 * @param z_near Near plane distance
 * @param z_far Far plane distance
 * @param api Graphics API (for depth range)
 * @return Linear depth value
 */
[[nodiscard]] inline float linearizeDepth(float depth,
                                          float z_near,
                                          float z_far,
                                          GraphicsApi api = GraphicsApi::eOpenGL) noexcept {
    if (getClipSpaceDepth(api) == ClipSpaceDepth::eZeroToOne) {
        // Vulkan/Metal/DirectX: depth in [0, 1]
        return z_near * z_far / (z_far - depth * (z_far - z_near));
    }
    // OpenGL: depth in [-1, 1]
    float ndc_z = depth * 2.0f - 1.0f;
    return 2.0f * z_near * z_far / (z_far + z_near - ndc_z * (z_far - z_near));
}

/**
 * @brief Converts linear depth to non-linear depth buffer value.
 */
[[nodiscard]] inline float encodeDepth(float linear_depth,
                                       float z_near,
                                       float z_far,
                                       GraphicsApi api = GraphicsApi::eOpenGL) noexcept {
    if (getClipSpaceDepth(api) == ClipSpaceDepth::eZeroToOne) {
        return (z_far - z_near * z_far / linear_depth) / (z_far - z_near);
    }
    float ndc_z = (z_far + z_near - 2.0f * z_near * z_far / linear_depth) / (z_far - z_near);
    return (ndc_z + 1.0f) * 0.5f;
}

// ============================================================================
// Validation Utilities
// ============================================================================

/**
 * @brief Validates that a projection matrix has the correct Y-flip for the API.
 *
 * This helps catch mismatches where a projection matrix was generated for one API
 * but is being used with another. Only Vulkan requires Y-flip in the projection matrix.
 *
 * @param proj The projection matrix to validate
 * @param api The target graphics API
 * @return true if the Y-flip is correct for the API, false otherwise
 */
[[nodiscard]] inline bool validateProjectionMatrix(const Mat4f& proj, GraphicsApi api) noexcept {
    bool y_flipped = proj[1][1] < 0.0f;
    bool should_flip = needsProjectionYFlip(api);
    return y_flipped == should_flip;
}

/**
 * @brief Validates projection matrix and returns detailed mismatch info.
 *
 * @param proj The projection matrix to validate
 * @param api The target graphics API
 * @param out_expected_flip Output: whether Y-flip was expected
 * @param out_actual_flip Output: whether Y-flip was detected
 * @return true if the Y-flip is correct for the API, false otherwise
 */
[[nodiscard]] inline bool validateProjectionMatrixDetailed(const Mat4f& proj,
                                                           GraphicsApi api,
                                                           bool& out_expected_flip,
                                                           bool& out_actual_flip) noexcept {
    out_actual_flip = proj[1][1] < 0.0f;
    out_expected_flip = needsProjectionYFlip(api);
    return out_actual_flip == out_expected_flip;
}

}  // namespace vne::math

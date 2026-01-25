#pragma once
/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Author:    Ajeet Singh Yadav
 * Created:   January 2026
 *
 * Common graphics utilities for VneMath examples
 * ----------------------------------------------------------------------
 */

#include <vertexnova/math/core/core.h>

namespace vne::math::examples {

/**
 * @brief Get human-readable name for a graphics API.
 * @param api The graphics API enum value
 * @return C-string name of the API
 */
inline const char* apiName(GraphicsApi api) {
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

/**
 * @brief Extract the translation component from a transformation matrix.
 * @param matrix The 4x4 transformation matrix
 * @return Position as Vec3f
 */
inline Vec3f extractPosition(const Mat4f& matrix) {
    return Vec3f(matrix[3][0], matrix[3][1], matrix[3][2]);
}

/**
 * @brief Get clip space depth description for an API.
 * @param api The graphics API
 * @return String describing the depth range
 */
inline const char* depthRangeName(GraphicsApi api) {
    return getClipSpaceDepth(api) == ClipSpaceDepth::eZeroToOne ? "[0, 1]" : "[-1, 1]";
}

/**
 * @brief Get handedness description for an API.
 * @param api The graphics API
 * @return String describing the handedness
 */
inline const char* handednessName(GraphicsApi api) {
    return getHandedness(api) == Handedness::eLeft ? "Left-handed" : "Right-handed";
}

}  // namespace vne::math::examples

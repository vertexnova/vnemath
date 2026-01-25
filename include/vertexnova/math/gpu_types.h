#pragma once
/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Author:    Ajeet Singh Yadav
 * Created:   January 2026
 *
 * GPU-aligned types and utilities for shader uniform buffers.
 *
 * This header provides:
 * - Aligned vector/matrix types for GPU buffers (std140/std430)
 * - Compile-time alignment validation macros
 * - Padding helpers
 * ----------------------------------------------------------------------
 */

#include "core/types.h"
#include "core/vec.h"
#include "core/mat.h"

#include <cstddef>
#include <type_traits>

namespace vne::math {

// ============================================================================
// GPU Buffer Layout Standards
// ============================================================================

/**
 * @enum GpuBufferLayout
 * @brief Specifies the memory layout standard for GPU buffers.
 */
enum class GpuBufferLayout : uint8_t {
    eStd140,  ///< OpenGL/Vulkan uniform buffer default (16-byte struct alignment)
    eStd430,  ///< Storage buffer layout (tighter packing, natural alignment)
    eMetal    ///< Metal layout (largest member alignment)
};

// ============================================================================
// Alignment Constants
// ============================================================================

namespace gpu {

/// @name std140 Alignment Requirements
/// @{

/// Scalar alignment (float, int, uint)
inline constexpr size_t kScalarAlign = 4;

/// Vec2 alignment
inline constexpr size_t kVec2Align = 8;

/// Vec3 alignment (NOTE: 16 bytes, not 12!)
inline constexpr size_t kVec3Align = 16;

/// Vec4 alignment
inline constexpr size_t kVec4Align = 16;

/// Mat4 alignment (array of 4 vec4)
inline constexpr size_t kMat4Align = 16;

/// Minimum struct alignment in std140
inline constexpr size_t kStructAlign = 16;

/// Minimum uniform buffer offset alignment (conservative, works for all APIs)
inline constexpr size_t kUniformBufferAlign = 256;

/// @}

}  // namespace gpu

// ============================================================================
// Aligned Types for GPU Buffers
// ============================================================================

/**
 * @brief 16-byte aligned Vec3 for GPU uniform buffers.
 *
 * In std140 layout, vec3 requires 16-byte alignment AND 16-byte size.
 * This type ensures correct layout when used in uniform buffer structs.
 *
 * @note Size is 16 bytes (3 floats + 4 bytes padding) due to alignas(16).
 *       This matches GPU std140 vec3 layout exactly.
 */
struct alignas(16) GpuVec3f {
    float x, y, z;
    // Implicit 4-byte padding added by alignas(16)

    GpuVec3f() = default;
    constexpr GpuVec3f(float x_, float y_, float z_)
        : x(x_)
        , y(y_)
        , z(z_) {}
    constexpr GpuVec3f(const Vec3f& v)
        : x(v.x())
        , y(v.y())
        , z(v.z()) {}  // NOLINT

    [[nodiscard]] constexpr operator Vec3f() const { return Vec3f(x, y, z); }  // NOLINT

    [[nodiscard]] constexpr Vec3f toVec3f() const { return Vec3f(x, y, z); }
};

/**
 * @brief 16-byte aligned Vec4 for GPU uniform buffers.
 */
struct alignas(16) GpuVec4f {
    float x, y, z, w;

    GpuVec4f() = default;
    constexpr GpuVec4f(float x_, float y_, float z_, float w_)
        : x(x_)
        , y(y_)
        , z(z_)
        , w(w_) {}
    constexpr GpuVec4f(const Vec4f& v)
        : x(v.x())
        , y(v.y())
        , z(v.z())
        , w(v.w()) {}  // NOLINT
    constexpr GpuVec4f(const Vec3f& v, float w_)
        : x(v.x())
        , y(v.y())
        , z(v.z())
        , w(w_) {}

    [[nodiscard]] constexpr operator Vec4f() const { return Vec4f(x, y, z, w); }  // NOLINT

    [[nodiscard]] constexpr Vec4f toVec4f() const { return Vec4f(x, y, z, w); }
    [[nodiscard]] constexpr Vec3f toVec3f() const { return Vec3f(x, y, z); }
};

/**
 * @brief 16-byte aligned Mat4 for GPU uniform buffers.
 *
 * Mat4 is stored as 4 column vectors, each 16-byte aligned.
 */
struct alignas(16) GpuMat4f {
    GpuVec4f columns[4];

    GpuMat4f() = default;

    constexpr GpuMat4f(const Mat4f& m)  // NOLINT
        : columns{GpuVec4f(m[0]), GpuVec4f(m[1]), GpuVec4f(m[2]), GpuVec4f(m[3])} {}

    [[nodiscard]] Mat4f toMat4f() const {
        return Mat4f(columns[0].toVec4f(), columns[1].toVec4f(), columns[2].toVec4f(), columns[3].toVec4f());
    }
};

// ============================================================================
// Padding Helpers
// ============================================================================

/**
 * @brief Explicit padding type for GPU buffers.
 *
 * Use this to add explicit padding in your uniform structs.
 *
 * @tparam Bytes Number of padding bytes
 *
 * Usage:
 * @code
 * struct MyUniform {
 *     Vec3f position;      // 12 bytes
 *     Padding<4> _pad0;    // 4 bytes padding
 *     Vec3f direction;     // 12 bytes
 *     Padding<4> _pad1;    // 4 bytes padding
 * };
 * @endcode
 */
template<size_t Bytes>
struct Padding {
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays)
    char data[Bytes];
};

/// Common padding sizes
using Pad4 = Padding<4>;
using Pad8 = Padding<8>;
using Pad12 = Padding<12>;

// ============================================================================
// Compile-Time Alignment Validation
// ============================================================================

/**
 * @brief Calculate required alignment for a type under std140 rules.
 */
template<typename T>
struct Std140Alignment {
    static constexpr size_t value = alignof(T) < 16 ? alignof(T) : 16;
};

// Specializations for vector types
template<>
struct Std140Alignment<Vec2f> {
    static constexpr size_t value = 8;
};
template<>
struct Std140Alignment<Vec3f> {
    static constexpr size_t value = 16;
};  // NOT 12!
template<>
struct Std140Alignment<Vec4f> {
    static constexpr size_t value = 16;
};
template<>
struct Std140Alignment<Mat4f> {
    static constexpr size_t value = 16;
};

template<typename T>
inline constexpr size_t kStd140Alignment = Std140Alignment<T>::value;

/**
 * @brief Check if a struct has correct std140 layout.
 *
 * This validates that:
 * 1. The struct is 16-byte aligned
 * 2. The struct size is a multiple of 16 bytes
 *
 * Usage:
 * @code
 * struct MyUniform { ... };
 * static_assert(isStd140Compatible<MyUniform>(), "MyUniform has incorrect GPU layout!");
 * @endcode
 */
template<typename T>
constexpr bool isStd140Compatible() {
    return (alignof(T) >= 16) && (sizeof(T) % 16 == 0);
}

/**
 * @brief Calculate the padded size for std140 layout.
 *
 * Rounds size up to the next multiple of 16.
 */
template<typename T>
constexpr size_t std140PaddedSize() {
    return (sizeof(T) + 15) & ~size_t(15);
}

// ============================================================================
// Validation Macros
// ============================================================================

/**
 * @brief Validate that a uniform struct has correct std140 layout.
 *
 * Usage:
 * @code
 * struct CameraUniforms {
 *     GpuMat4f view_projection;
 *     GpuVec4f camera_position;
 * };
 * VNE_VALIDATE_GPU_STRUCT(CameraUniforms);
 * @endcode
 */
#define VNE_VALIDATE_GPU_STRUCT(StructName)                                                      \
    static_assert(alignof(StructName) >= 16, #StructName " must be 16-byte aligned for std140"); \
    static_assert(sizeof(StructName) % 16 == 0, #StructName " size must be multiple of 16 for std140")

/**
 * @brief Validate struct size matches expected GPU size.
 *
 * Usage:
 * @code
 * struct LightData {
 *     GpuVec4f position;
 *     GpuVec4f color;
 * };
 * VNE_VALIDATE_GPU_STRUCT_SIZE(LightData, 32);
 * @endcode
 */
#define VNE_VALIDATE_GPU_STRUCT_SIZE(StructName, ExpectedSize)                                       \
    static_assert(sizeof(StructName) == ExpectedSize, #StructName " size mismatch with GPU layout"); \
    VNE_VALIDATE_GPU_STRUCT(StructName)

/**
 * @brief Validate member offset in a GPU struct.
 *
 * Usage:
 * @code
 * struct MyUniform {
 *     GpuVec4f position;   // offset 0
 *     GpuVec4f color;      // offset 16
 * };
 * VNE_VALIDATE_GPU_MEMBER_OFFSET(MyUniform, position, 0);
 * VNE_VALIDATE_GPU_MEMBER_OFFSET(MyUniform, color, 16);
 * @endcode
 */
#define VNE_VALIDATE_GPU_MEMBER_OFFSET(StructName, MemberName, ExpectedOffset) \
    static_assert(offsetof(StructName, MemberName) == ExpectedOffset,          \
                  #StructName "::" #MemberName " has incorrect offset for GPU layout")

// ============================================================================
// Helper Functions
// ============================================================================

/**
 * @brief Convert a Vec3f to Vec4f with padding.
 *
 * Useful when you need to store Vec3 data in a Vec4 slot.
 *
 * @param v The Vec3f to convert
 * @param w The w component (default: 0.0 for directions, 1.0 for points)
 * @return Vec4f with the Vec3 values and w component
 */
[[nodiscard]] constexpr Vec4f toGpuVec4(const Vec3f& v, float w = 0.0f) {
    return Vec4f(v.x(), v.y(), v.z(), w);
}

/**
 * @brief Convert a Vec3f point to Vec4f (w=1).
 */
[[nodiscard]] constexpr Vec4f toGpuPoint(const Vec3f& v) {
    return Vec4f(v.x(), v.y(), v.z(), 1.0f);
}

/**
 * @brief Convert a Vec3f direction to Vec4f (w=0).
 */
[[nodiscard]] constexpr Vec4f toGpuDirection(const Vec3f& v) {
    return Vec4f(v.x(), v.y(), v.z(), 0.0f);
}

// ============================================================================
// Example Usage Documentation
// ============================================================================

/**
 * @example GPU Uniform Buffer Layout
 *
 * When creating uniform buffers for GPU shaders, follow these guidelines:
 *
 * 1. **Prefer Vec4 over Vec3**:
 *    Vec3 has tricky alignment requirements. When possible, use Vec4:
 *    @code
 *    // AVOID: Vec3 needs padding
 *    struct Bad {
 *        Vec3f position;  // 12 bytes
 *        float intensity; // 4 bytes - might pack incorrectly!
 *    };
 *
 *    // PREFER: Vec4 is naturally aligned
 *    struct Good {
 *        Vec4f position;  // xyz = position, w = intensity
 *    };
 *    @endcode
 *
 * 2. **Use explicit padding with Padding<N>**:
 *    @code
 *    struct LightData {
 *        Vec3f position;    // 12 bytes
 *        Pad4 _pad0;        // 4 bytes explicit padding
 *        Vec3f color;       // 12 bytes
 *        float intensity;   // 4 bytes - fits in the padding slot!
 *    };
 *    @endcode
 *
 * 3. **Use GPU-aligned types**:
 *    @code
 *    struct CameraData {
 *        GpuMat4f view_projection;  // 64 bytes, 16-aligned
 *        GpuVec4f camera_pos;       // 16 bytes, 16-aligned
 *    };
 *    VNE_VALIDATE_GPU_STRUCT(CameraData);
 *    @endcode
 *
 * 4. **Validate your layouts**:
 *    @code
 *    struct SceneData {
 *        GpuMat4f model;
 *        GpuMat4f view;
 *        GpuMat4f projection;
 *        GpuVec4f light_pos;
 *    };
 *    VNE_VALIDATE_GPU_STRUCT_SIZE(SceneData, 208);
 *    VNE_VALIDATE_GPU_MEMBER_OFFSET(SceneData, model, 0);
 *    VNE_VALIDATE_GPU_MEMBER_OFFSET(SceneData, view, 64);
 *    VNE_VALIDATE_GPU_MEMBER_OFFSET(SceneData, projection, 128);
 *    VNE_VALIDATE_GPU_MEMBER_OFFSET(SceneData, light_pos, 192);
 *    @endcode
 */

}  // namespace vne::math

/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Author:    Ajeet Singh Yadav
 * Created:   January 2026
 *
 * GPU types alignment and layout validation tests.
 * ----------------------------------------------------------------------
 */

#include <gtest/gtest.h>

#include "vertexnova/math/gpu_types.h"

namespace vne::math {

// ============================================================================
// Alignment Tests
// ============================================================================

class GpuAlignmentTest : public ::testing::Test {};

TEST_F(GpuAlignmentTest, GpuVec3fAlignment) {
    // GpuVec3f must be 16-byte aligned for std140
    EXPECT_EQ(alignof(GpuVec3f), 16);

    // Size is 16 bytes due to alignas(16) - compiler adds 4 bytes padding
    // This is correct for GPU buffers - matches std140 vec3 layout
    EXPECT_EQ(sizeof(GpuVec3f), 16);
}

TEST_F(GpuAlignmentTest, GpuVec4fAlignment) {
    EXPECT_EQ(alignof(GpuVec4f), 16);
    EXPECT_EQ(sizeof(GpuVec4f), 16);
}

TEST_F(GpuAlignmentTest, GpuMat4fAlignment) {
    EXPECT_EQ(alignof(GpuMat4f), 16);
    EXPECT_EQ(sizeof(GpuMat4f), 64);  // 4 * 16 bytes
}

TEST_F(GpuAlignmentTest, PaddingTypes) {
    EXPECT_EQ(sizeof(Pad4), 4);
    EXPECT_EQ(sizeof(Pad8), 8);
    EXPECT_EQ(sizeof(Pad12), 12);
}

// ============================================================================
// Std140 Alignment Traits Tests
// ============================================================================

class Std140TraitsTest : public ::testing::Test {};

TEST_F(Std140TraitsTest, Vec2Alignment) {
    EXPECT_EQ(kStd140Alignment<Vec2f>, 8);
}

TEST_F(Std140TraitsTest, Vec3Alignment) {
    // Critical: Vec3 requires 16-byte alignment in std140!
    EXPECT_EQ(kStd140Alignment<Vec3f>, 16);
}

TEST_F(Std140TraitsTest, Vec4Alignment) {
    EXPECT_EQ(kStd140Alignment<Vec4f>, 16);
}

TEST_F(Std140TraitsTest, Mat4Alignment) {
    EXPECT_EQ(kStd140Alignment<Mat4f>, 16);
}

// ============================================================================
// Std140 Compatibility Tests
// ============================================================================

// Example well-formed GPU struct
struct alignas(16) CameraUniforms {
    GpuMat4f view_projection;   // 64 bytes
    GpuVec4f camera_position;   // 16 bytes
    GpuVec4f camera_direction;  // 16 bytes
};  // Total: 96 bytes

// Validate at compile time
VNE_VALIDATE_GPU_STRUCT(CameraUniforms);
VNE_VALIDATE_GPU_STRUCT_SIZE(CameraUniforms, 96);
VNE_VALIDATE_GPU_MEMBER_OFFSET(CameraUniforms, view_projection, 0);
VNE_VALIDATE_GPU_MEMBER_OFFSET(CameraUniforms, camera_position, 64);
VNE_VALIDATE_GPU_MEMBER_OFFSET(CameraUniforms, camera_direction, 80);

TEST_F(Std140TraitsTest, CameraUniformsLayout) {
    EXPECT_TRUE(isStd140Compatible<CameraUniforms>());
    EXPECT_EQ(sizeof(CameraUniforms), 96);
    EXPECT_EQ(alignof(CameraUniforms), 16);
}

// Example with padding
struct alignas(16) LightUniforms {
    GpuVec4f position;  // 16 bytes (xyz = pos, w = radius)
    GpuVec4f color;     // 16 bytes (xyz = color, w = intensity)
};

VNE_VALIDATE_GPU_STRUCT(LightUniforms);
VNE_VALIDATE_GPU_STRUCT_SIZE(LightUniforms, 32);

TEST_F(Std140TraitsTest, LightUniformsLayout) {
    EXPECT_TRUE(isStd140Compatible<LightUniforms>());
    EXPECT_EQ(sizeof(LightUniforms), 32);
}

// Example: Using GpuVec3f which has built-in 16-byte alignment
struct alignas(16) MaterialUniforms {
    GpuVec3f albedo;    // 16 bytes (12 + 4 padding)
    GpuVec3f emission;  // 16 bytes (12 + 4 padding)
    float roughness;    // 4 bytes
    float metallic;     // 4 bytes
    Pad8 _pad0;         // 8 bytes to round to 16
};

VNE_VALIDATE_GPU_STRUCT(MaterialUniforms);
VNE_VALIDATE_GPU_STRUCT_SIZE(MaterialUniforms, 48);

TEST_F(Std140TraitsTest, MaterialUniformsLayout) {
    EXPECT_TRUE(isStd140Compatible<MaterialUniforms>());
    EXPECT_EQ(sizeof(MaterialUniforms), 48);

    // Verify offsets
    EXPECT_EQ(offsetof(MaterialUniforms, albedo), 0);
    EXPECT_EQ(offsetof(MaterialUniforms, emission), 16);
    EXPECT_EQ(offsetof(MaterialUniforms, roughness), 32);
    EXPECT_EQ(offsetof(MaterialUniforms, metallic), 36);
}

// ============================================================================
// Type Conversion Tests
// ============================================================================

class GpuTypeConversionTest : public ::testing::Test {
   protected:
    static constexpr float kEps = 1e-6f;
};

TEST_F(GpuTypeConversionTest, GpuVec3fFromVec3f) {
    Vec3f v(1.0f, 2.0f, 3.0f);
    GpuVec3f gv = v;

    EXPECT_FLOAT_EQ(gv.x, 1.0f);
    EXPECT_FLOAT_EQ(gv.y, 2.0f);
    EXPECT_FLOAT_EQ(gv.z, 3.0f);
}

TEST_F(GpuTypeConversionTest, GpuVec3fToVec3f) {
    GpuVec3f gv(1.0f, 2.0f, 3.0f);
    Vec3f v = gv;

    EXPECT_FLOAT_EQ(v.x(), 1.0f);
    EXPECT_FLOAT_EQ(v.y(), 2.0f);
    EXPECT_FLOAT_EQ(v.z(), 3.0f);
}

TEST_F(GpuTypeConversionTest, GpuVec4fFromVec3fWithW) {
    Vec3f v(1.0f, 2.0f, 3.0f);
    GpuVec4f gv(v, 1.0f);

    EXPECT_FLOAT_EQ(gv.x, 1.0f);
    EXPECT_FLOAT_EQ(gv.y, 2.0f);
    EXPECT_FLOAT_EQ(gv.z, 3.0f);
    EXPECT_FLOAT_EQ(gv.w, 1.0f);
}

TEST_F(GpuTypeConversionTest, GpuMat4fRoundTrip) {
    Mat4f original = Mat4f::translate(1.0f, 2.0f, 3.0f);
    GpuMat4f gpu_mat = original;
    Mat4f recovered = gpu_mat.toMat4f();

    EXPECT_TRUE(original.approxEquals(recovered, kEps));
}

TEST_F(GpuTypeConversionTest, ToGpuVec4Helper) {
    Vec3f v(1.0f, 2.0f, 3.0f);

    Vec4f direction = toGpuDirection(v);
    EXPECT_FLOAT_EQ(direction.w(), 0.0f);

    Vec4f point = toGpuPoint(v);
    EXPECT_FLOAT_EQ(point.w(), 1.0f);
}

// ============================================================================
// Practical Usage Tests
// ============================================================================

class GpuPracticalTest : public ::testing::Test {};

TEST_F(GpuPracticalTest, TypicalSceneUniformBuffer) {
    // A typical scene uniform buffer structure
    struct alignas(16) SceneUniforms {
        GpuMat4f model;        // 64 bytes
        GpuMat4f view;         // 64 bytes
        GpuMat4f projection;   // 64 bytes
        GpuVec4f light_pos;    // 16 bytes (xyz = pos, w = unused)
        GpuVec4f light_color;  // 16 bytes (xyz = color, w = intensity)
        GpuVec4f camera_pos;   // 16 bytes (xyz = pos, w = unused)
    };

    VNE_VALIDATE_GPU_STRUCT(SceneUniforms);
    VNE_VALIDATE_GPU_STRUCT_SIZE(SceneUniforms, 240);

    EXPECT_TRUE(isStd140Compatible<SceneUniforms>());
    EXPECT_EQ(sizeof(SceneUniforms), 240);

    // Verify offsets match shader expectations
    EXPECT_EQ(offsetof(SceneUniforms, model), 0);
    EXPECT_EQ(offsetof(SceneUniforms, view), 64);
    EXPECT_EQ(offsetof(SceneUniforms, projection), 128);
    EXPECT_EQ(offsetof(SceneUniforms, light_pos), 192);
    EXPECT_EQ(offsetof(SceneUniforms, light_color), 208);
    EXPECT_EQ(offsetof(SceneUniforms, camera_pos), 224);
}

TEST_F(GpuPracticalTest, Std140PaddedSize) {
    // A struct that's not a multiple of 16
    struct SmallData {
        float value;
    };

    // std140 would pad this to 16 bytes
    EXPECT_EQ(std140PaddedSize<SmallData>(), 16);

    // Already multiple of 16
    EXPECT_EQ(std140PaddedSize<GpuVec4f>(), 16);
    EXPECT_EQ(std140PaddedSize<GpuMat4f>(), 64);
}

// ============================================================================
// Negative Tests - Demonstrate What NOT to Do
// ============================================================================

// This struct has INCORRECT layout for GPU!
struct BadUniformLayout {
    Vec3f position;   // 12 bytes
    Vec3f direction;  // 12 bytes - WRONG! Not 16-byte aligned
    float intensity;  // 4 bytes
};

TEST_F(GpuPracticalTest, BadLayoutDetection) {
    // This demonstrates that regular Vec3f structs won't pass validation
    EXPECT_FALSE(isStd140Compatible<BadUniformLayout>());

    // The size is 28 bytes, not a multiple of 16
    EXPECT_NE(sizeof(BadUniformLayout) % 16, 0);
}

}  // namespace vne::math

/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Example: GPU Buffer Alignment
 * Demonstrates proper memory layout for shader uniform buffers
 * across different graphics APIs (Metal, Vulkan, DirectX, etc.)
 * ----------------------------------------------------------------------
 */

#include "common/logging_guard.h"

#include <vertexnova/math/core/core.h>
#include <vertexnova/math/gpu_types.h>

using namespace vne::math;
using vne::math::examples::LoggingGuard_C;

// ============================================================================
// Example Uniform Structures
// ============================================================================

// Camera uniforms - common in most shaders
struct alignas(16) CameraUniforms {
    GpuMat4f view;             // 64 bytes, offset 0
    GpuMat4f projection;       // 64 bytes, offset 64
    GpuMat4f view_projection;  // 64 bytes, offset 128
    GpuVec4f position;         // 16 bytes, offset 192 (xyz=pos, w=unused)
    GpuVec4f direction;        // 16 bytes, offset 208 (xyz=dir, w=unused)
};

// Validate at compile time
VNE_VALIDATE_GPU_STRUCT(CameraUniforms);
VNE_VALIDATE_GPU_STRUCT_SIZE(CameraUniforms, 224);
VNE_VALIDATE_GPU_MEMBER_OFFSET(CameraUniforms, view, 0);
VNE_VALIDATE_GPU_MEMBER_OFFSET(CameraUniforms, projection, 64);
VNE_VALIDATE_GPU_MEMBER_OFFSET(CameraUniforms, view_projection, 128);
VNE_VALIDATE_GPU_MEMBER_OFFSET(CameraUniforms, position, 192);
VNE_VALIDATE_GPU_MEMBER_OFFSET(CameraUniforms, direction, 208);

// Light data - using Vec4 to pack related values
struct alignas(16) LightUniforms {
    GpuVec4f position;   // 16 bytes (xyz=position, w=radius)
    GpuVec4f color;      // 16 bytes (xyz=color, w=intensity)
    GpuVec4f direction;  // 16 bytes (xyz=direction, w=spot_angle)
    GpuVec4f params;     // 16 bytes (x=type, y=shadow_bias, z=near, w=far)
};

VNE_VALIDATE_GPU_STRUCT(LightUniforms);
VNE_VALIDATE_GPU_STRUCT_SIZE(LightUniforms, 64);

// Material data - demonstrates packing scalars efficiently
struct alignas(16) MaterialUniforms {
    GpuVec4f albedo;      // 16 bytes (xyz=color, w=alpha)
    GpuVec4f emission;    // 16 bytes (xyz=color, w=intensity)
    GpuVec4f properties;  // 16 bytes (x=roughness, y=metallic, z=ao, w=unused)
};

VNE_VALIDATE_GPU_STRUCT(MaterialUniforms);
VNE_VALIDATE_GPU_STRUCT_SIZE(MaterialUniforms, 48);

// Model transform - per-instance data
struct alignas(16) ModelUniforms {
    GpuMat4f model;          // 64 bytes
    GpuMat4f normal_matrix;  // 64 bytes (inverse transpose of model)
};

VNE_VALIDATE_GPU_STRUCT(ModelUniforms);
VNE_VALIDATE_GPU_STRUCT_SIZE(ModelUniforms, 128);

// Complete scene uniforms
struct alignas(16) SceneUniforms {
    GpuMat4f view_projection;  // 64 bytes
    GpuVec4f camera_pos;       // 16 bytes
    GpuVec4f light_pos;        // 16 bytes
    GpuVec4f light_color;      // 16 bytes
    GpuVec4f ambient;          // 16 bytes
};

VNE_VALIDATE_GPU_STRUCT(SceneUniforms);
VNE_VALIDATE_GPU_STRUCT_SIZE(SceneUniforms, 128);

void demonstrateAlignmentBasics() {
    VNE_LOG_INFO << "=== GPU Buffer Alignment Basics ===";
    VNE_LOG_INFO << "";

    VNE_LOG_INFO << "std140 Alignment Requirements:";
    VNE_LOG_INFO << "  float:  " << gpu::kScalarAlign << " bytes";
    VNE_LOG_INFO << "  vec2:   " << gpu::kVec2Align << " bytes";
    VNE_LOG_INFO << "  vec3:   " << gpu::kVec3Align << " bytes (NOT 12!)";
    VNE_LOG_INFO << "  vec4:   " << gpu::kVec4Align << " bytes";
    VNE_LOG_INFO << "  mat4:   " << gpu::kMat4Align << " bytes";
    VNE_LOG_INFO << "  struct: " << gpu::kStructAlign << " bytes minimum";

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "GPU Type Sizes:";
    VNE_LOG_INFO << "  GpuVec3f: " << sizeof(GpuVec3f) << " bytes (16, not 12)";
    VNE_LOG_INFO << "  GpuVec4f: " << sizeof(GpuVec4f) << " bytes";
    VNE_LOG_INFO << "  GpuMat4f: " << sizeof(GpuMat4f) << " bytes";

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Common Mistake - Vec3 alignment:";
    VNE_LOG_INFO << "  C++ Vec3f size: " << sizeof(Vec3f) << " bytes";
    VNE_LOG_INFO << "  GPU vec3 size:  16 bytes (requires padding!)";
    VNE_LOG_INFO << "  Solution: Use GpuVec3f or Vec4f";
}

void demonstrateWrongVsRight() {
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Wrong vs Right Layout ===";

    // WRONG: This struct has incorrect GPU layout
    struct WrongLayout {
        Vec3f position;   // 12 bytes
        Vec3f normal;     // 12 bytes
        float roughness;  // 4 bytes
    };

    // RIGHT: This struct has correct GPU layout
    struct alignas(16) RightLayout {
        GpuVec4f position;  // 16 bytes (w unused or store extra data)
        GpuVec4f normal;    // 16 bytes (w unused)
        GpuVec4f params;    // 16 bytes (x=roughness, y,z,w available)
    };

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Wrong layout (will cause GPU bugs!):";
    VNE_LOG_INFO << "  struct { Vec3f pos; Vec3f normal; float roughness; }";
    VNE_LOG_INFO << "  C++ size: " << sizeof(WrongLayout) << " bytes";
    VNE_LOG_INFO << "  Problem: Vec3 not 16-byte aligned!";

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Right layout:";
    VNE_LOG_INFO << "  struct alignas(16) { GpuVec4f pos; GpuVec4f normal; GpuVec4f params; }";
    VNE_LOG_INFO << "  C++ size: " << sizeof(RightLayout) << " bytes";
    VNE_LOG_INFO << "  is std140 compatible: " << (isStd140Compatible<RightLayout>() ? "YES" : "NO");
}

void demonstrateUniformStructures() {
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Common Uniform Structures ===";

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "CameraUniforms:";
    VNE_LOG_INFO << "  Size: " << sizeof(CameraUniforms) << " bytes";
    VNE_LOG_INFO << "  view offset:            " << offsetof(CameraUniforms, view);
    VNE_LOG_INFO << "  projection offset:      " << offsetof(CameraUniforms, projection);
    VNE_LOG_INFO << "  view_projection offset: " << offsetof(CameraUniforms, view_projection);
    VNE_LOG_INFO << "  position offset:        " << offsetof(CameraUniforms, position);
    VNE_LOG_INFO << "  direction offset:       " << offsetof(CameraUniforms, direction);

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "LightUniforms:";
    VNE_LOG_INFO << "  Size: " << sizeof(LightUniforms) << " bytes";
    VNE_LOG_INFO << "  position offset:  " << offsetof(LightUniforms, position);
    VNE_LOG_INFO << "  color offset:     " << offsetof(LightUniforms, color);
    VNE_LOG_INFO << "  direction offset: " << offsetof(LightUniforms, direction);
    VNE_LOG_INFO << "  params offset:    " << offsetof(LightUniforms, params);

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "MaterialUniforms:";
    VNE_LOG_INFO << "  Size: " << sizeof(MaterialUniforms) << " bytes";
    VNE_LOG_INFO << "  albedo offset:     " << offsetof(MaterialUniforms, albedo);
    VNE_LOG_INFO << "  emission offset:   " << offsetof(MaterialUniforms, emission);
    VNE_LOG_INFO << "  properties offset: " << offsetof(MaterialUniforms, properties);
}

void demonstrateDataPacking() {
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Packing Data into Vec4 ===";

    // Pack position + radius into one Vec4
    Vec3f light_pos(10.0f, 5.0f, -3.0f);
    float light_radius = 15.0f;
    GpuVec4f packed_light(light_pos, light_radius);

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Light position + radius packed into Vec4:";
    VNE_LOG_INFO << "  Original: pos=" << light_pos << ", radius=" << light_radius;
    VNE_LOG_INFO << "  Packed: (" << packed_light.x << ", " << packed_light.y << ", " << packed_light.z << ", "
                 << packed_light.w << ")";

    // Pack multiple scalars into Vec4
    float roughness = 0.5f;
    float metallic = 0.8f;
    float ao = 1.0f;
    float unused = 0.0f;
    GpuVec4f material_params(roughness, metallic, ao, unused);

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Material params packed into Vec4:";
    VNE_LOG_INFO << "  roughness=" << roughness << ", metallic=" << metallic << ", ao=" << ao;
    VNE_LOG_INFO << "  Packed: (" << material_params.x << ", " << material_params.y << ", " << material_params.z << ", "
                 << material_params.w << ")";

    // Using helper functions
    Vec3f camera_pos(0.0f, 5.0f, 10.0f);
    Vec3f camera_dir(0.0f, 0.0f, -1.0f);

    Vec4f pos_vec4 = toGpuPoint(camera_pos);      // w=1 for points
    Vec4f dir_vec4 = toGpuDirection(camera_dir);  // w=0 for directions

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Helper functions for Vec3 -> Vec4:";
    VNE_LOG_INFO << "  toGpuPoint(" << camera_pos << ") = " << pos_vec4;
    VNE_LOG_INFO << "  toGpuDirection(" << camera_dir << ") = " << dir_vec4;
}

void demonstrateFillUniformBuffer() {
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Filling a Uniform Buffer ===";

    // Create camera matrices
    Vec3f eye(0.0f, 5.0f, 10.0f);
    Vec3f target(0.0f, 0.0f, 0.0f);
    Vec3f up = Vec3f::yAxis();

    Mat4f view = Mat4f::lookAt(eye, target, up, GraphicsApi::eVulkan);
    Mat4f proj = Mat4f::perspective(degToRad(60.0f), 16.0f / 9.0f, 0.1f, 100.0f, GraphicsApi::eVulkan);
    Mat4f vp = viewProjection(view, proj);

    // Fill the uniform struct
    CameraUniforms camera;
    camera.view = view;
    camera.projection = proj;
    camera.view_projection = vp;
    camera.position = GpuVec4f(eye, 1.0f);
    camera.direction = GpuVec4f((target - eye).normalized(), 0.0f);

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "CameraUniforms filled:";
    VNE_LOG_INFO << "  Position: (" << camera.position.x << ", " << camera.position.y << ", " << camera.position.z
                 << ")";
    VNE_LOG_INFO << "  Direction: (" << camera.direction.x << ", " << camera.direction.y << ", " << camera.direction.z
                 << ")";

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Ready to upload to GPU:";
    VNE_LOG_INFO << "  Buffer size needed: " << sizeof(CameraUniforms) << " bytes";
    VNE_LOG_INFO << "  memcpy(&gpu_buffer, &camera, sizeof(CameraUniforms));";
}

void demonstrateValidationMacros() {
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Compile-Time Validation ===";

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Available validation macros:";
    VNE_LOG_INFO << "  VNE_VALIDATE_GPU_STRUCT(StructName)";
    VNE_LOG_INFO << "    - Checks 16-byte alignment";
    VNE_LOG_INFO << "    - Checks size is multiple of 16";

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "  VNE_VALIDATE_GPU_STRUCT_SIZE(StructName, ExpectedSize)";
    VNE_LOG_INFO << "    - Same as above plus exact size check";

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "  VNE_VALIDATE_GPU_MEMBER_OFFSET(StructName, Member, Offset)";
    VNE_LOG_INFO << "    - Verifies member is at expected byte offset";
    VNE_LOG_INFO << "    - Catches layout mismatches with shader code";

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Example usage:";
    VNE_LOG_INFO << "  struct alignas(16) MyUniforms {";
    VNE_LOG_INFO << "      GpuMat4f mvp;       // offset 0";
    VNE_LOG_INFO << "      GpuVec4f color;     // offset 64";
    VNE_LOG_INFO << "  };";
    VNE_LOG_INFO << "  VNE_VALIDATE_GPU_STRUCT_SIZE(MyUniforms, 80);";
    VNE_LOG_INFO << "  VNE_VALIDATE_GPU_MEMBER_OFFSET(MyUniforms, mvp, 0);";
    VNE_LOG_INFO << "  VNE_VALIDATE_GPU_MEMBER_OFFSET(MyUniforms, color, 64);";
}

void demonstrateBestPractices() {
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Best Practices ===";

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "1. ALWAYS use alignas(16) on uniform structs";

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "2. Prefer Vec4 over Vec3:";
    VNE_LOG_INFO << "   - Pack extra data in w component";
    VNE_LOG_INFO << "   - Examples: pos.w = radius, dir.w = intensity";

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "3. Use GpuVec3f when you must use 3-component vectors";

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "4. Group related data:";
    VNE_LOG_INFO << "   - Vec4 params; // x=roughness, y=metallic, z=ao, w=alpha";

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "5. Always validate with macros:";
    VNE_LOG_INFO << "   - Catches errors at compile time";
    VNE_LOG_INFO << "   - Documents expected layout";

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "6. Match shader layout exactly:";
    VNE_LOG_INFO << "   - Use VNE_VALIDATE_GPU_MEMBER_OFFSET";
    VNE_LOG_INFO << "   - Keep C++ and shader code in sync";
}

int main() {
    LoggingGuard_C logging_guard;

    VNE_LOG_INFO << "VneMath Example: GPU Buffer Alignment";
    VNE_LOG_INFO << "======================================";
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "This example demonstrates proper memory layout for";
    VNE_LOG_INFO << "GPU uniform buffers across Metal, Vulkan, DirectX, etc.";

    demonstrateAlignmentBasics();
    demonstrateWrongVsRight();
    demonstrateUniformStructures();
    demonstrateDataPacking();
    demonstrateFillUniformBuffer();
    demonstrateValidationMacros();
    demonstrateBestPractices();

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Done ===";
    return 0;
}

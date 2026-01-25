# Example 08: GPU Buffer Alignment

Demonstrates proper memory layout for shader uniform buffers across different graphics APIs (Metal, Vulkan, DirectX, WebGPU).

## The Problem

Different graphics APIs have strict memory alignment requirements for uniform/constant buffers:

| Type | C++ Size | std140 Alignment | std140 Size |
|------|----------|------------------|-------------|
| `float` | 4 | 4 | 4 |
| `vec2` | 8 | 8 | 8 |
| `vec3` | 12 | **16** | **16** |
| `vec4` | 16 | 16 | 16 |
| `mat4` | 64 | 16 | 64 |

**The most common pitfall**: `Vec3` requires 16-byte alignment, not 12!

## Solution: GPU-Aligned Types

VneMath provides GPU-aligned types that match shader buffer layouts:

```cpp
#include <vertexnova/math/gpu_types.h>

// GPU-aligned types
GpuVec3f  // 16-byte aligned Vec3
GpuVec4f  // 16-byte aligned Vec4
GpuMat4f  // 16-byte aligned Mat4
```

## Example Uniform Buffer

```cpp
struct alignas(16) CameraUniforms {
    GpuMat4f view_projection;  // 64 bytes, offset 0
    GpuVec4f camera_position;  // 16 bytes, offset 64
    GpuVec4f camera_direction; // 16 bytes, offset 80
};

// Compile-time validation - catches errors before runtime!
VNE_VALIDATE_GPU_STRUCT(CameraUniforms);
VNE_VALIDATE_GPU_STRUCT_SIZE(CameraUniforms, 96);
VNE_VALIDATE_GPU_MEMBER_OFFSET(CameraUniforms, view_projection, 0);
VNE_VALIDATE_GPU_MEMBER_OFFSET(CameraUniforms, camera_position, 64);
```

## Best Practices

1. **Use `alignas(16)`** on all uniform structs
2. **Prefer Vec4 over Vec3** - pack extra data in w component
3. **Validate with macros** - catches errors at compile time
4. **Match shader layout** - use `VNE_VALIDATE_GPU_MEMBER_OFFSET`

## Build

```bash
cmake -B build -DBUILD_EXAMPLES=ON
cmake --build build
./build/bin/examples/example_08_gpu_alignment
```

## Corresponding Shader Code (GLSL)

```glsl
// This C++ struct:
struct alignas(16) CameraUniforms {
    GpuMat4f view_projection;
    GpuVec4f camera_position;
    GpuVec4f camera_direction;
};

// Matches this GLSL layout:
layout(std140, binding = 0) uniform CameraUniforms {
    mat4 view_projection;   // offset 0
    vec4 camera_position;   // offset 64
    vec4 camera_direction;  // offset 80
};
```

## See Also

- `gpu_types.h` - GPU-aligned types and validation macros
- Example 02 - Multi-backend projection matrices

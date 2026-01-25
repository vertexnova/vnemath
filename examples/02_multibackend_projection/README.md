# 02 - Multi-Backend Projection

Demonstrates the key feature of VertexNova Math: creating projection and view matrices
for different graphics APIs with a single, unified interface.

## What This Example Demonstrates

- Creating perspective projection matrices for each graphics API
- Creating orthographic projection matrices
- Understanding depth range differences ([-1,1] vs [0,1])
- Y-axis flip handling for Vulkan, Metal, and WebGPU
- View matrix (lookAt) generation
- Complete MVP (Model-View-Projection) matrix composition

## Supported Graphics APIs

| API     | Depth Range | Y Direction | Handedness   |
|---------|-------------|-------------|--------------|
| OpenGL  | [-1, 1]     | Y-up        | Right-handed |
| Vulkan  | [0, 1]      | Y-down      | Right-handed |
| Metal   | [0, 1]      | Y-down      | Left-handed  |
| DirectX | [0, 1]      | Y-up        | Left-handed  |
| WebGPU  | [0, 1]      | Y-down      | Right-handed |

## Building

```bash
cmake -B build -DBUILD_EXAMPLES=ON
cmake --build build
./build/bin/examples/example_02_multibackend
```

## Key Concepts

### Projection Matrices
```cpp
// Unified API - just pass the target graphics API
Mat4f proj = Mat4f::perspective(fov, aspect, near, far, GraphicsApi::eVulkan);
Mat4f ortho = Mat4f::ortho(left, right, bottom, top, near, far, GraphicsApi::eMetal);
```

### View Matrices
```cpp
Mat4f view = Mat4f::lookAt(eye, target, up, GraphicsApi::eVulkan);
```

### MVP Composition
```cpp
Mat4f mvpMatrix = mvp(modelMatrix, viewMatrix, projectionMatrix);
```

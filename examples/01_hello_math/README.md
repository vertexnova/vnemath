# 01 - Hello Math

Basic introduction to the VertexNova Math library.

## What This Example Demonstrates

- Creating and manipulating 2D, 3D, and 4D vectors
- Basic matrix operations (identity, transpose, inverse, multiplication)
- Quaternion creation and rotation
- Degree/radian conversions
- Common math utilities

## Building

```bash
cmake -B build -DBUILD_EXAMPLES=ON
cmake --build build
./build/bin/examples/example_01_hello_math
```

## Key Concepts

### Vectors
- `Vec2f`, `Vec3f`, `Vec4f` - Single precision floating-point vectors
- `Vec2d`, `Vec3d`, `Vec4d` - Double precision floating-point vectors
- `Vec2i`, `Vec3i`, `Vec4i` - Integer vectors

### Matrices
- `Mat2f`, `Mat3f`, `Mat4f` - Square matrices
- Row-major storage, column-major access (GLM-compatible)

### Quaternions
- `Quatf`, `Quatd` - Unit quaternions for rotations
- Avoids gimbal lock issues with Euler angles

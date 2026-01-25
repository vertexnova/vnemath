# 12 - Transform Decomposition

Demonstrates matrix decomposition into Translation, Rotation, Scale (TRS) components.

## What This Example Demonstrates

- **Compose**: Building transformation matrices from TRS components
- **Decompose**: Extracting TRS from existing matrices
- **Individual Extraction**: Getting just translation, rotation, or scale
- **Matrix Factories**: Creating translation, rotation, and scale matrices
- **Transform Interpolation**: Smooth blending between transformations

## Building

```bash
cmake -B build -DBUILD_EXAMPLES=ON
cmake --build build
./build/bin/examples/example_12_transform_decomposition
```

## Key Concepts

### Compose (TRS to Matrix)

```cpp
Vec3f translation(10.0f, 0.0f, 0.0f);
Quatf rotation = Quatf::fromAxisAngle(Vec3f::yAxis(), angle);
Vec3f scale(2.0f, 2.0f, 2.0f);

// Create matrix: M = T * R * S
Mat4f matrix = compose(translation, rotation, scale);

// Or from TransformComponents
TransformComponents tc{translation, rotation, scale};
Mat4f matrix = compose(tc);
```

### Decompose (Matrix to TRS)

```cpp
Mat4f matrix = /* some transformation matrix */;

// Extract all components
TransformComponents tc = decompose(matrix);
Vec3f t = tc.translation;
Quatf r = tc.rotation;
Vec3f s = tc.scale;

// Extract individual components
Vec3f translation = extractTranslation(matrix);
Vec3f scale = extractScale(matrix);
Quatf rotation = extractRotation(matrix);
```

### Transform Interpolation

Better than simple matrix lerp - properly interpolates TRS:

```cpp
Mat4f start = compose(pos1, rot1, scale1);
Mat4f end = compose(pos2, rot2, scale2);

// Smooth interpolation at t=0.5
Mat4f mid = lerpTransform(start, end, 0.5f);
```

### Matrix Factory Functions

```cpp
Mat4f t = makeTranslation(Vec3f(x, y, z));
Mat4f r = makeRotation(quaternion);
Mat4f s = makeScale(2.0f);           // Uniform
Mat4f s = makeScale(Vec3f(1, 2, 3)); // Non-uniform
```

## Use Cases

- **Animation blending**: Interpolate between keyframes
- **Scene graph**: Extract local transforms from world matrices
- **Editor tools**: Display/edit TRS components separately
- **Physics**: Extract position/rotation for physics simulation
- **Inverse kinematics**: Decompose bone transforms

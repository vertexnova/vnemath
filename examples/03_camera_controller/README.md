# 03 - Camera Controller

Demonstrates practical camera implementations for 3D graphics.

## What This Example Demonstrates

- FPS-style camera (first-person shooter style movement)
- Orbital camera (rotate around a target point)
- Using quaternions for smooth, gimbal-lock-free rotation
- View matrix generation for different graphics APIs
- Camera movement and rotation

## Camera Types

### FPS Camera
- WASD-style movement in the camera's local space
- Mouse look for pitch and yaw
- No gimbal lock using quaternion rotation

### Orbital Camera
- Orbits around a focal point
- Zoom in/out by changing distance
- Useful for object inspection, 3D modeling views

## Building

```bash
cmake -B build -DBUILD_EXAMPLES=ON
cmake --build build
./build/bin/examples/example_03_camera
```

## Key Concepts

### Quaternion-Based Rotation
Using quaternions avoids gimbal lock and provides smooth interpolation:
```cpp
Quatf orientation = Quatf::fromEuler(pitch, yaw, 0.0f);
Vec3f forward = orientation.rotate(Vec3f::zAxis());
```

### View Matrix from Camera State
```cpp
Mat4f view = Mat4f::lookAt(position, position + forward, up, api);
```

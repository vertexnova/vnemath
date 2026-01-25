# 06 - Ray Intersection

Demonstrates ray casting against geometry primitives.

## What This Example Demonstrates

- Creating rays from origin and direction
- Ray-plane intersection
- Ray-sphere intersection
- Ray-AABB intersection
- Closest point calculations
- Practical mouse picking example

## Why Ray Casting?

Ray casting is fundamental for:
- Mouse picking (clicking on 3D objects)
- Physics raycasts (line of sight, bullet traces)
- Collision detection
- Pathfinding visibility checks

## Building

```bash
cmake -B build -DBUILD_EXAMPLES=ON
cmake --build build
./build/bin/examples/example_06_ray
```

## Key Concepts

### Creating Rays
```cpp
Ray ray(origin, direction);  // Direction is normalized automatically
```

### Intersection Tests
```cpp
// Get point on ray
Vec3f point = ray.getPoint(distance);

// Closest point to ray
Vec3f closest = ray.closestPoint(point);
float distance = ray.distanceToPoint(point);
```

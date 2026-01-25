# 04 - Frustum Culling

Demonstrates visibility testing for rendering optimization.

## What This Example Demonstrates

- Creating a view frustum from a projection matrix
- Testing points against the frustum
- Testing spheres against the frustum
- Testing AABBs (Axis-Aligned Bounding Boxes) against the frustum
- Partial vs full containment tests

## Why Frustum Culling?

Frustum culling is essential for rendering performance:
- Skip objects completely outside the camera view
- Process only visible objects for rendering
- Typically done every frame before rendering

## Building

```bash
cmake -B build -DBUILD_EXAMPLES=ON
cmake --build build
./build/bin/examples/example_04_frustum
```

## Key Concepts

### Frustum Extraction
```cpp
Mat4f vp = proj * view;
Frustum frustum;
frustum.extractFromMatrix(vp);
```

### Containment Tests
```cpp
// Point test
bool visible = frustum.contains(point);

// Sphere test
bool visible = frustum.intersects(sphere);
bool fullyInside = frustum.containsFully(sphere);

// AABB test
bool visible = frustum.intersects(aabb);
bool fullyInside = frustum.containsFully(aabb);
```

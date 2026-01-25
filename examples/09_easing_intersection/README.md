# Example 09: Easing Functions and Ray Intersection

Demonstrates high-performance easing functions inspired by [Inigo Quilez](https://iquilezles.org/articles/functions/) and ray intersection utilities.

## Features Covered

### Smoothstep Variants

```cpp
#include <vertexnova/math/easing.h>

// Standard cubic smoothstep: x²(3-2x)
float y = smoothstep(x);

// Quintic smootherstep: x³(x(6x-15)+10) - C2 continuous
float y = smootherstep(x);

// Quartic: uses only even powers (good when x is a distance)
float y = smoothstepQuartic(x);

// Rational with controllable steepness
float y = smoothstepRational(x, 2.0f);
```

### Easing Functions

```cpp
// Individual functions
float y = easeInQuad(t);
float y = easeOutCubic(t);
float y = easeInOutElastic(t);

// Via enum (useful for animation systems)
float y = ease(EaseType::eBounceOut, t);
```

### Impulse Functions (IQ-style)

```cpp
// Exponential impulse - grows fast, decays slowly
float y = expImpulse(x, k);  // Peaks at x = 1/k

// Polynomial impulse - no exponential, faster
float y = polyImpulse(x, k);

// Cubic pulse - localized bump
float y = cubicPulse(center, width, x);
```

### Ray Intersection

```cpp
#include <vertexnova/math/geometry/intersection.h>

Ray ray(origin, direction);

// Full intersection with hit info
RayHit hit = intersect(ray, sphere);
if (hit) {
    Vec3f point = hit.point;
    Vec3f normal = hit.normal;
    float dist = hit.distance;
}

// Fast bool-only tests (for culling)
if (intersects(ray, aabb)) { ... }
```

### Screen Projection

```cpp
#include <vertexnova/math/projection_utils.h>

Viewport viewport(1920, 1080);

// World to screen
Vec3f screen = project(worldPoint, mvp, viewport, GraphicsApi::eVulkan);

// Screen to world
Vec3f world = unproject(screenPoint, invMvp, viewport, GraphicsApi::eVulkan);

// Create picking ray
Ray ray = screenToWorldRay(mousePos, invMvp, viewport, cameraPos, api);
```

### Angle Utilities

```cpp
// Normalize to [0, 2π]
float a = normalizeAngle(angle);

// Normalize to [-π, π]
float a = normalizeAngleSigned(angle);

// Shortest angular difference
float diff = angleDifference(from, to);

// Interpolate angles (handles wraparound)
float a = lerpAngle(from, to, t);
```

## Build

```bash
cmake -B build -DBUILD_EXAMPLES=ON
cmake --build build
./build/bin/examples/example_09_easing
```

## References

- [Inigo Quilez - Useful Functions](https://iquilezles.org/articles/functions/)
- [Inigo Quilez - Smoothsteps](https://iquilezles.org/articles/smoothsteps/)
- [Easing Functions Cheat Sheet](https://easings.net/)

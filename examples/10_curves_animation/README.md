# 10 - Curves and Animation

Demonstrates curve evaluation functions for smooth animation paths and timing.

## What This Example Demonstrates

- **Bezier Curves**: Quadratic and cubic Bezier curve evaluation
- **Catmull-Rom Splines**: Curves that pass through control points
- **Hermite Splines**: Curves with explicit tangent control
- **Curve Splitting**: Subdividing curves using de Casteljau's algorithm
- **Arc Length**: Approximating curve length for uniform speed motion

## Building

```bash
cmake -B build -DBUILD_EXAMPLES=ON
cmake --build build
./build/bin/examples/example_10_curves_animation
```

## Key Concepts

### Bezier Curves

```cpp
// Quadratic Bezier (3 points)
Vec3f point = bezierQuadratic(p0, p1, p2, t);

// Cubic Bezier (4 points) - like CSS transitions
Vec3f point = bezierCubic(p0, p1, p2, p3, t);
Vec3f tangent = bezierCubicDerivative(p0, p1, p2, p3, t);
```

### Catmull-Rom Splines

Passes through control points - ideal for camera paths:

```cpp
// Curve goes from p1 to p2, using p0 and p3 for tangent calculation
Vec3f point = catmullRom(p0, p1, p2, p3, t);

// With tension control
Vec3f point = catmullRomTension(p0, p1, p2, p3, t, 0.5f);
```

### Hermite Splines

When you need explicit control over tangents:

```cpp
Vec3f point = hermite(position0, tangent0, position1, tangent1, t);
```

## Use Cases

- **Animation paths**: Smooth camera or object movement
- **Timing functions**: Easing curves for UI animations
- **Procedural geometry**: Curved roads, pipes, cables
- **Motion blur**: Interpolating positions for motion blur effects

# 11 - Noise Generation

Demonstrates procedural noise functions for terrain, textures, and effects.

## What This Example Demonstrates

- **Perlin Noise**: Classic gradient noise in 1D, 2D, and 3D
- **Simplex Noise**: Faster alternative with fewer artifacts
- **Fractal Brownian Motion (fBm)**: Layered noise for natural patterns
- **Turbulence**: Absolute value fBm for fire/smoke effects
- **Ridged Noise**: Sharp ridges for mountains and veins
- **Value Noise**: Simple hash-based noise

## Building

```bash
cmake -B build -DBUILD_EXAMPLES=ON
cmake --build build
./build/bin/examples/example_11_noise_generation
```

## Key Concepts

### Basic Noise

```cpp
// 1D/2D/3D Perlin noise (returns ~[-1, 1])
float value = perlin(x);
float value = perlin(x, y);
float value = perlin(Vec3f(x, y, z));

// Simplex noise (faster, cleaner)
float value = simplex(Vec2f(x, y));
float value = simplex(Vec3f(x, y, z));
```

### Fractal Brownian Motion

Layered noise with configurable octaves:

```cpp
// More octaves = more detail
float terrain = fbm(position, 6);  // 6 octaves

// With custom parameters
float cloud = fbm(position, 
    6,      // octaves
    2.0f,   // lacunarity (frequency multiplier)
    0.5f    // gain (amplitude multiplier)
);
```

### Specialized Noise

```cpp
// Turbulence (for fire, smoke, marble)
float fire = turbulence(position);

// Ridged noise (for mountains, veins)
float mountain = ridged(position);

// Value noise (simple, [0,1] range)
float simple = valueNoise(x, y);
```

## Use Cases

| Noise Type | Use Cases |
|------------|-----------|
| Perlin/Simplex | Terrain, clouds, water waves |
| FBM | Natural textures, organic shapes |
| Turbulence | Fire, smoke, marble texture |
| Ridged | Mountains, veins, cracks, lightning |
| Value | Simple procedural patterns |

## Common Patterns

### Terrain Generation

```cpp
// Base terrain shape
float height = fbm(pos * 0.01f, 6);

// Add mountain ridges
height += ridged(pos * 0.02f, 4) * 0.3f;

// Micro detail
height += fbm(pos * 0.1f, 2) * 0.1f;
```

### Animated Effects

```cpp
// Animate noise over time
float animated = perlin(x, y, time * 0.5f);
```

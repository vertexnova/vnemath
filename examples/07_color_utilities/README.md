# 07 - Color Utilities

Demonstrates color manipulation for graphics applications.

## What This Example Demonstrates

- Creating colors from RGBA values
- Creating colors from hex codes
- Color lerp for smooth transitions
- Predefined color constants
- Color arithmetic operations

## Why Color Utilities?

Proper color handling is essential for:
- UI theming and styling
- Smooth color transitions and animations
- Consistent color representation across the application
- Color manipulation (darken, lighten, blend)

## Building

```bash
cmake -B build -DBUILD_EXAMPLES=ON
cmake --build build
./build/bin/examples/example_07_color
```

## Key Concepts

### Color Creation
```cpp
Color red(1.0f, 0.0f, 0.0f, 1.0f);  // RGBA floats [0-1]
Color blue = Color::kBlue;          // Predefined constant
```

### Color Operations
```cpp
Color blended = color1.lerp(color2, 0.5f);  // 50% blend
Color darker = color * 0.5f;                 // Darken
Color combined = color1 + color2;            // Additive blend
```

# VneMath

A high-performance, cross-platform C++ math library for game engines and 3D applications.

## Features

- **Vector Types**: Vec2f, Vec3f, Vec4f with comprehensive operations
- **Matrix Types**: Mat3x3f, Mat4x4f with transformation utilities
- **Quaternion**: Full quaternion support for 3D rotations
- **Color**: RGBA color representation with utilities
- **Transform Node**: Hierarchical transformation system for scene graphs
- **Random**: Template-based random number generation using Mersenne Twister
- **Math Utilities**: Trigonometry, interpolation, and common math functions

## Requirements

- C++20 compatible compiler
- CMake 3.16+

## Dependencies (Git Submodules)

Dependencies are organized into two categories:

### Third-Party Libraries (`external/`)

| Dependency | Version | Description |
|------------|---------|-------------|
| GLM | 1.0.1 | OpenGL Mathematics library |
| Google Test | 1.14.0 | Unit testing framework |

### VertexNova Libraries (`libs/`)

| Library | Version | Description |
|---------|---------|-------------|
| VneCommon | v1.0.0 | Common utilities (macros, platform detection) |
| VneLogging | v1.0.0 | VertexNova logging library |

### CMake Modules (`cmake/vnecmake/`)

| Module | Description |
|--------|-------------|
| VneCMake | Shared CMake modules for VertexNova projects |

### Initializing Submodules

After cloning the repository, initialize the submodules:

```bash
git submodule update --init --recursive
```

## Supported Platforms

- macOS (Clang)
- Linux (GCC/Clang)
- Windows (MSVC)
- iOS
- Android
- Web (Emscripten)

## Building

### Quick Start (macOS)

```bash
./scripts/build_macos.sh -t Debug -a configure_and_build
```

### Quick Start (Linux)

```bash
./scripts/build_linux.sh -t Debug -a configure_and_build
```

### Manual CMake Build

```bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTS=ON ..
make -j$(nproc)
```

### Build Options

| Option | Default | Description |
|--------|---------|-------------|
| `BUILD_TESTS` | ON | Build the test suite |
| `BUILD_EXAMPLES` | OFF | Build example programs |
| `ENABLE_COVERAGE` | OFF | Enable code coverage reporting |
| `ENABLE_CPPCHECK` | OFF | Enable cppcheck static analysis |
| `ENABLE_CLANG_TIDY` | OFF | Enable clang-tidy static analysis |

## Usage

### Basic Example

```cpp
#include <vertexnova/math/math.h>

using namespace VNE::Math;

int main() {
    // Vectors
    Vec3f_C a(1.0f, 2.0f, 3.0f);
    Vec3f_C b(4.0f, 5.0f, 6.0f);
    
    float dot = a.Dot(b);
    Vec3f_C cross = a.Cross(b);
    Vec3f_C normalized = a.Normalize();
    
    // Matrices
    Mat4x4f_C transform = Mat4x4f_C::Identity();
    transform = Mat4x4f_C::Translate(Vec3f_C(10.0f, 0.0f, 0.0f));
    transform = transform * Mat4x4f_C::RotateY(DegToRad(45.0f));
    
    // Quaternions
    Quaternion_C rotation;
    rotation.SetFromAxisAngle(DegToRad(90.0f), Vec3f_C::Up());
    Vec3f_C rotated = rotation.RotateVector(Vec3f_C::Forward());
    
    // Colors
    Color_C red = Color_C::RED;
    Color_C blended = red.Lerp(Color_C::BLUE, 0.5f);
    
    return 0;
}
```

### CMake Integration

```cmake
find_package(VneMath REQUIRED)
target_link_libraries(your_target PRIVATE vne::math)
```

Or using FetchContent:

```cmake
include(FetchContent)
FetchContent_Declare(
    vnemath
    GIT_REPOSITORY https://github.com/yourusername/vnemath.git
    GIT_TAG main
)
FetchContent_MakeAvailable(vnemath)
target_link_libraries(your_target PRIVATE vne::math)
```

## Running Tests

```bash
cd build
ctest --output-on-failure
```

Or using the build script:

```bash
./scripts/build_macos.sh -a test
```

## Project Structure

```
vnemath/
├── CMakeLists.txt              # Root CMake configuration
├── cmake/                      # CMake modules
│   ├── ProjectSetup.cmake
│   ├── ProjectWarnings.cmake
│   └── ...
├── configs/
│   └── config.h.in             # CMake-configured header
├── include/vertexnova/         # Public headers
│   ├── math/
│   │   ├── math.h              # Main include
│   │   ├── vec2f.h
│   │   ├── vec3f.h
│   │   ├── vec4f.h
│   │   ├── mat3x3f.h
│   │   ├── mat4x4f.h
│   │   ├── quaternion.h
│   │   ├── color.h
│   │   ├── transform_node.h
│   │   ├── random.h
│   │   ├── constants.h
│   │   └── math_utils.h
│   └── utils/
│       └── macros.h
├── src/vertexnova/math/        # Implementation
├── tests/                      # Test suite
├── scripts/                    # Build scripts
└── external/                   # Third-party dependencies
```

## License

Apache License 2.0 - See [LICENSE](LICENSE) for details.

## Author

Ajeet Singh Yadav (yadav.ajeetsingh2020@gmail.com)

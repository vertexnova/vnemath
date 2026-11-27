# VneMath Examples

Runnable programs that exercise the public `vne::math` API. Each folder is a
self-contained CMake target with its own `README.md` for feature details.

## Building

### Direct CMake (build dir: `build/`)

Enable examples when configuring (also implied by `VNE_MATH_DEV=ON`):

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Debug -DBUILD_EXAMPLES=ON
# or: cmake -B build -DVNE_MATH_DEV=ON

cmake --build build
```

Binaries: `build/bin/examples/` (layout may differ for multi-config generators).

```bash
./build/bin/examples/example_01_hello_math
cmake --build build --target example_01_hello_math
```

### Platform script (build dir: printed by the script)

`build_macos.sh` / `build_linux.sh` configure with `-DBUILD_EXAMPLES=OFF`. After the
script finishes, reconfigure that build tree with `VNE_MATH_DEV=ON` (forces
examples on even if the cache had them off), then build:

```bash
./scripts/build_macos.sh -t Debug -a configure_and_build
# Linux: ./scripts/build_linux.sh -t Debug -a configure_and_build

# Use the "Build directory: <path>" line the script prints:
BUILD_DIR=build/shared/Debug/build-macos-clang-17.0.0

cmake -B "$BUILD_DIR" -DVNE_MATH_DEV=ON
cmake --build "$BUILD_DIR" --target example_01_hello_math
"$BUILD_DIR"/bin/examples/example_01_hello_math
```

## Catalog

| Directory | Binary | Topic |
|-----------|--------|-------|
| [01_hello_math](01_hello_math/) | `example_01_hello_math` | Vectors, matrices, quaternions |
| [02_multibackend_projection](02_multibackend_projection/) | `example_02_multibackend` | `GraphicsApi` view / projection matrices |
| [03_camera_controller](03_camera_controller/) | `example_03_camera` | FPS and orbital cameras |
| [04_frustum_culling](04_frustum_culling/) | `example_04_frustum` | Frustum visibility tests |
| [05_scene_graph](05_scene_graph/) | `example_05_scene_graph` | `TransformNode` hierarchy |
| [06_ray_intersection](06_ray_intersection/) | `example_06_ray` | Ray casting against primitives |
| [07_color_utilities](07_color_utilities/) | `example_07_color` | Color conversions and ops |
| [08_gpu_buffer_alignment](08_gpu_buffer_alignment/) | `example_08_gpu_alignment` | `Gpu*` layout for UBOs |
| [09_easing_intersection](09_easing_intersection/) | `example_09_easing` | Easing curves and ray helpers |
| [10_curves_animation](10_curves_animation/) | `example_10_curves_animation` | Bezier / Catmull-Rom / Hermite |
| [12_transform_decomposition](12_transform_decomposition/) | `example_12_transform_decomposition` | TRS `compose` / `decompose` |

There is no `11_*` example (noise generation was removed).

## Shared helpers (`common/`)

Headers used by more than one example:

| Header | Role |
|--------|------|
| `common/logging_guard.h` | Init / shutdown for `vne::logging` |
| `common/graphics_utils.h` | Small print helpers for matrices / APIs |
| `common/color_utils.h` | Color demo helpers |

Include them relative to `examples/`, for example:

```cpp
#include "../common/logging_guard.h"
```

## Notes

- Examples are console programs; they print results and exit. No window or GPU
  backend is required.
- Prefer `#include <vertexnova/math/math.h>` (or a narrower header) and
  `using namespace vne::math;`.
- Keep sample options and output behavior when editing; do not strip knobs as
  part of a refactor.

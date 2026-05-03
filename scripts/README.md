# VneMath scripts

Helper scripts for building, formatting, and documentation. Run from the **repository root**.

## Build layout

Platform scripts use CMake binary directories under **`build/<lib_type>/<build_type>/…`** (default `lib_type` is **shared**), matching CI. Example:

`build/shared/Release/build-linux-gcc-14.2.0/`

**Windows paths:** CI and **`build_windows.sh`** / **`build_windows.py`** use the same pattern: **`build/<lib_type>/<build_type>/…`** (for example `build/shared/Release/build-windows-cl-…`). **`build_windows.ps1`** also uses **`build\<lib_type>\<BuildType>\build-windows-msvc`**; with a Visual Studio generator, CMake still places per-configuration outputs under the usual **`Release`/`Debug`** subfolders inside that binary directory. Prefer separate **`build_type`** directories for cache and artifact isolation.

### Linux (`build_linux.sh`)

```bash
./scripts/build_linux.sh -t Debug -a configure_and_build
./scripts/build_linux.sh -c clang -j 20 -t Release
./scripts/build_linux.sh -l static -t Release -clean
./scripts/build_linux.sh -interactive
```

**Options:** `-t` build type, `-a` (`configure` | `build` | `configure_and_build` | `test`), `-c` (`gcc` | `clang`), `-l` (`static` | `shared`), `-j`, `-clean`, `-interactive`, `-h`

Clang passes **`-DENABLE_IPO=OFF`** (same rationale as CI).

### macOS (`build_macos.sh`)

```bash
./scripts/build_macos.sh -t Debug -a configure_and_build
./scripts/build_macos.sh -l static -t Release
./scripts/build_macos.sh -xcode -t Release
./scripts/build_macos.sh -xcode-only -t Release
./scripts/build_macos.sh -a xcode_build -t Debug
```

**Options:** `-t`, `-a` (adds `xcode`, `xcode_build`), `-l`, `-clean`, `-j`, `-xcode`, `-xcode-only`, `-h`

Xcode project name: **`vnemath.xcodeproj`**.

### Windows

**Bash** (Git Bash): `build_windows.sh` — `cl` and `cmake` on `PATH`.

```bash
./scripts/build_windows.sh -t Debug -a configure_and_build
./scripts/build_windows.sh -j 8 -t Release -l static
```

**Python** (Developer Command Prompt): `build_windows.py`

```bash
python scripts/build_windows.py -t Debug -a configure_and_build
python scripts/build_windows.py --build-type Release --jobs 8 -l static
python scripts/build_windows.py --interactive
```

**PowerShell** (`build_windows.ps1`):

```powershell
.\scripts\build_windows.ps1 -BuildType Release -LibType shared -Action test
```

### Web — Emscripten (`build_web.sh`)

```bash
./scripts/build_web.sh Release
./scripts/build_web.sh -c -j 8 Debug
```

Defaults: **`build/shared/<type>/…`**, **`VNE_MATH_TESTS=OFF`**. Override lib type: `-l static`.

### iOS (`build_ios.sh`)

```bash
./scripts/build_ios.sh -t Release -a configure_and_build -simulator
./scripts/build_ios.sh -l shared -device -deployment-target 16.0
```

Defaults: **`lib_type=static`**, **`build/static/<type>/…`**, **`VNE_MATH_TESTS=OFF`**.

## Formatting (`clang_formatter.py`)

Uses **`clang-format-17`** when available (same as CI), else `clang-format`. **`--dry-run`** exits non-zero if anything would change.

Run from the **repository root**. Use **`python3 …`** (recommended): the kernel resolves `python3` from your shell `PATH`. **`./scripts/clang_formatter.py`** relies on the shebang `#!/usr/bin/env python3`; if zsh reports **no such file or directory**, the exec environment could not find `python3`—invoking via **`python3`** avoids that.

```bash
python3 scripts/clang_formatter.py all --dry-run
python3 scripts/clang_formatter.py --folder all --dry-run
python3 scripts/clang_formatter.py src
python3 scripts/clang_formatter.py --file src/vertexnova/math/color.cpp
```

**`all`** (positional) or **`--folder`** with no path (or **`--folder all`**) scans **`src`**, **`include`**, **`examples`** (if present), **`tests`**.

## Documentation (`generate-docs.sh`)

- **API:** runs only if **`docs/doxyfile.in`** exists and CMake exposes a Doxygen target (e.g. after adding `ENABLE_DOXYGEN` to the project).
- Otherwise: link check (optional **`markdown-link-check`**) + a simple tag heuristic on `include/` and `src/`.

```bash
./scripts/generate-docs.sh
./scripts/generate-docs.sh --api-only
./scripts/generate-docs.sh --validate
```

Uses configure tree **`build/shared/Release`** for CMake-driven API generation.

## Prerequisites

- CMake **3.16+**, C++20 compiler  
- GLM: `deps/external/glm` or system / FetchContent per main **README**  
- Submodules: `git submodule update --init --recursive`

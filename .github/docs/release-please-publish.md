# VneMath — release-please and publish artifacts

## Flow

1. **release-please** (push to `main`) updates `CHANGELOG.md`, `VERSION`, and `.release-please-manifest.json`, and opens or updates the release PR.
2. After merge, a **tag** is created.
3. The **publish** job runs when `release_created == 'true'`, builds `cmake --install` trees per platform, and uploads `vnemath-v<version>-<platform>-<detail>.tar.gz`.

Configure **publish** with **`VNE_MATH_LIB_TYPE`** (`shared` for desktop/web/android matrix paths, **`static`** for **iOS**). Embedded **VneLogging** uses the same library kind via cache (`VNE_LOGGING_LIB_TYPE` aligned with the parent).

## Install layout

Tarballs include **`include/vertexnova/math/`** (with **`export.h`** where applicable), **`lib/`** (static or shared **vnemath**), **`LICENSE`**, **`CHANGELOG.md`**, and **`lib/cmake/VneMath/`** (`FindVneMath.cmake`, etc.). Internal deps are built into the library; consumers use **vnecommon** / **vnelogging** as declared by this project’s CMake.

## Artifact naming

Use **[`scripts/ci_artifact_detail.sh`](../../scripts/ci_artifact_detail.sh)** in workflows (see **`release-please.yml`**). For **Android**, set **`ANDROID_PLATFORM`** (e.g. `android-24`) and **`ANDROID_NDK_ROOT`** when invoking the script.

## iOS / Xcode probes

Use **`env -u MD_APPLE_SDK_ROOT -u SDKROOT -u IOS_SDK_VERSION`** with **`xcodebuild -version`** or rely on **`ci_artifact_detail.sh`** to avoid exit **134** / SIGABRT on some runners.

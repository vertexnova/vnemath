#!/bin/bash
#==============================================================================
# VneMath iOS Build Script
#==============================================================================
# Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
# Licensed under the Apache License, Version 2.0 (the "License")
#
# Build dir: build/static/<BuildType>/build-ios-clang-<version> (static matches CI)
#==============================================================================

set -e
JOBS=10
PROJECT_ROOT=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)
BUILD_TYPE="Release"
ACTION="configure_and_build"
CLEAN=false
TARGET="simulator"
IOS_DEPLOYMENT_TARGET="15.0"
LIB_TYPE="static"

usage() {
  echo "Usage: $0 [-t <type>] [-a <action>] [-l static|shared] [-clean] [-simulator|-device] [-deployment-target <ver>] [-j <N>]"
  echo "  -a configure|build|configure_and_build|test|xcode|xcode_build"
  exit 1
}

while [[ $# -gt 0 ]]; do
  case $1 in
    -t|--type) BUILD_TYPE="$2"; shift 2 ;;
    -a|--action) ACTION="$2"; shift 2 ;;
    -l|--lib-type) LIB_TYPE="$2"; shift 2 ;;
    -clean) CLEAN=true; shift ;;
    -simulator) TARGET="simulator"; shift ;;
    -device) TARGET="device"; shift ;;
    -deployment-target) IOS_DEPLOYMENT_TARGET="$2"; shift 2 ;;
    -j) JOBS="$2"; shift 2 ;;
    -h|--help) usage ;;
    *) echo "Unknown: $1"; usage ;;
  esac
done

if [[ "$LIB_TYPE" != "static" && "$LIB_TYPE" != "shared" ]]; then
  echo "Invalid -l/--lib-type: '$LIB_TYPE' (expected static or shared)"
  exit 1
fi

command -v xcodebuild &>/dev/null || { echo "Xcode not found"; exit 1; }
COMPILER_VERSION=$(clang --version 2>/dev/null | head -n1 | awk '{print $4}' | sed 's/(.*)//')
[[ -z "$COMPILER_VERSION" ]] && COMPILER_VERSION=$(clang --version 2>/dev/null | head -n1 | awk '{print $3}')

BUILD_DIR="$PROJECT_ROOT/build/${LIB_TYPE}/${BUILD_TYPE}/build-ios-clang-${COMPILER_VERSION}"
$CLEAN && { rm -rf "$BUILD_DIR"; }
mkdir -p "$BUILD_DIR"

CMAKE_ARGS=(
  -G "Xcode"
  -DCMAKE_BUILD_TYPE="$BUILD_TYPE"
  -DVNE_MATH_LIB_TYPE="$LIB_TYPE"
  -DVNE_TARGET_PLATFORM=iOS
  -DCMAKE_SYSTEM_NAME=iOS
  -DCMAKE_OSX_DEPLOYMENT_TARGET="$IOS_DEPLOYMENT_TARGET"
  -DCMAKE_OSX_ARCHITECTURES=arm64
  -DBUILD_TESTS=OFF
  -DVNE_MATH_TESTS=OFF
  -DENABLE_IPO=OFF
)
[[ "$TARGET" == "device" ]] && CMAKE_ARGS+=(-DCMAKE_OSX_SYSROOT=iphoneos)
[[ "$TARGET" == "simulator" ]] && CMAKE_ARGS+=(-DCMAKE_OSX_SYSROOT=iphonesimulator -DCMAKE_OSX_ARCHITECTURES="arm64;x86_64")

cd "$BUILD_DIR"
cmake "${CMAKE_ARGS[@]}" "$PROJECT_ROOT"

if [[ "$ACTION" == "build" || "$ACTION" == "configure_and_build" || "$ACTION" == "test" ]]; then
  SDK=$([[ "$TARGET" == "device" ]] && echo "iphoneos" || echo "iphonesimulator")
  CONFIG=$([[ "$BUILD_TYPE" == "Release" ]] && echo "Release" || echo "Debug")
  PROJ=$(find . -maxdepth 1 -name "*.xcodeproj" -type d | head -n1)
  [[ -n "$PROJ" ]] && xcodebuild -project "$(basename "$PROJ")" -scheme ALL_BUILD -configuration "$CONFIG" -sdk "$SDK" -jobs "$JOBS"
fi

echo "=== Build completed ==="
echo "Build directory: $BUILD_DIR"
echo "Target: $TARGET ($IOS_DEPLOYMENT_TARGET), lib=$LIB_TYPE"

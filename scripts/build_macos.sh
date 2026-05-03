#!/bin/bash

#==============================================================================
# VneMath macOS Build Script
#==============================================================================
# Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
# Licensed under the Apache License, Version 2.0 (the "License")
#
# Autodoc:   yes
#
# Build directory: build/<lib_type>/<build_type>/...
#==============================================================================

set -e

JOBS=10
ARGS=()
while [[ $# -gt 0 ]]; do
    case $1 in
        -j|--jobs) [[ -n "$2" && "$2" =~ ^[0-9]+$ ]] && { JOBS="$2"; shift 2; } || { echo "Invalid jobs: $2"; exit 1; } ;;
        -j*) JOBS="${1#-j}"; [[ "$JOBS" =~ ^[0-9]+$ ]] || { echo "Invalid jobs: $JOBS"; exit 1; }; shift ;;
        *) ARGS+=("$1"); shift ;;
    esac
done
set -- "${ARGS[@]}"

PLATFORM="Darwin"
COMPILER="clang"

usage() {
  echo "Usage: $0 [-t <build_type>] [-a <action>] [-l <lib_type>] [-clean] [-interactive] [-j <jobs>] [-xcode] [-xcode-only]"
  echo "  -t <build_type>  Debug|Release|RelWithDebInfo|MinSizeRel"
  echo "  -a <action>      configure|build|configure_and_build|test|xcode|xcode_build"
  echo "  -l <lib_type>    static|shared (default: shared). Build dir: build/<lib_type>/..."
  echo "  -clean           Clean build directory first"
  echo "  -interactive     Interactive mode"
  echo "  -j <jobs>        Parallel jobs (default: 10)"
  echo "  -xcode           Also generate Xcode project"
  echo "  -xcode-only      Only generate Xcode project"
  exit 1
}

interactive_mode() {
  echo "=== VneMath macOS Interactive Build Configuration ==="
  echo ""
  echo "Detected Platform: $PLATFORM (Clang)"
  echo ""
  echo "Select Build Type:"
  echo "1) Debug (default)"
  echo "2) Release"
  echo "3) RelWithDebInfo"
  echo "4) MinSizeRel"
  read -r -p "Enter choice (1-4) [1]: " build_choice
  case $build_choice in
    2) BUILD_TYPE="Release" ;;
    3) BUILD_TYPE="RelWithDebInfo" ;;
    4) BUILD_TYPE="MinSizeRel" ;;
    *) BUILD_TYPE="Debug" ;;
  esac

  echo ""
  echo "Select library type:"
  echo "1) shared (default)"
  echo "2) static"
  read -r -p "Enter choice (1-2) [1]: " lib_choice
  case $lib_choice in
    2) LIB_TYPE="static" ;;
    *) LIB_TYPE="shared" ;;
  esac

  echo ""
  echo "Select Xcode integration:"
  echo "1) Unix Makefiles only (default)"
  echo "2) Also generate Xcode (-xcode)"
  echo "3) Xcode only (-xcode-only)"
  read -r -p "Enter choice (1-3) [1]: " xcode_choice
  case $xcode_choice in
    2) GENERATE_XCODE=true; XCODE_ONLY=false ;;
    3) GENERATE_XCODE=true; XCODE_ONLY=true ;;
    *) GENERATE_XCODE=false; XCODE_ONLY=false ;;
  esac

  echo ""
  echo "Select Action:"
  echo "1) Configure only"
  echo "2) Configure and build (default)"
  echo "3) Configure, build, and test"
  read -r -p "Enter choice (1-3) [2]: " action_choice
  case $action_choice in
    1) ACTION="configure" ;;
    3) ACTION="test" ;;
    *) ACTION="configure_and_build" ;;
  esac

  echo ""
  read -r -p "Clean build directory before starting? (y/N): " clean_choice
  if [[ $clean_choice =~ ^[Yy]$ ]]; then
    CLEAN_BUILD=true
  fi

  read -r -p "Parallel jobs [$JOBS]: " jobs_choice
  if [[ -n "$jobs_choice" && "$jobs_choice" =~ ^[0-9]+$ ]]; then
    JOBS="$jobs_choice"
  fi

  echo ""
  echo "=== Configuration Summary ==="
  echo "Build Type: $BUILD_TYPE"
  echo "Library Type: $LIB_TYPE"
  echo "Xcode: GENERATE_XCODE=$GENERATE_XCODE XCODE_ONLY=$XCODE_ONLY"
  echo "Action: $ACTION"
  echo "Clean Build: $CLEAN_BUILD"
  echo "Jobs: $JOBS"
  echo ""
  read -r -p "Proceed with this configuration? (Y/n): " proceed
  if [[ $proceed =~ ^[Nn]$ ]]; then
    echo "Build cancelled."
    exit 0
  fi
}

BUILD_TYPE="Debug"
ACTION="configure_and_build"
LIB_TYPE="shared"
CLEAN_BUILD=false
INTERACTIVE_MODE=false
GENERATE_XCODE=false
XCODE_ONLY=false

while [[ $# -gt 0 ]]; do
  case $1 in
    -t|--build-type) BUILD_TYPE="$2"; shift 2 ;;
    -a|--action) ACTION="$2"; shift 2 ;;
    -l|--lib-type) LIB_TYPE="$2"; shift 2 ;;
    -clean|--clean) CLEAN_BUILD=true; shift ;;
    -interactive|--interactive) INTERACTIVE_MODE=true; shift ;;
    -xcode|--xcode) GENERATE_XCODE=true; shift ;;
    -xcode-only|--xcode-only) XCODE_ONLY=true; GENERATE_XCODE=true; shift ;;
    -h|--help) usage ;;
    *) echo "Unknown option: $1"; usage ;;
  esac
done

if [ "$INTERACTIVE_MODE" = true ]; then
  interactive_mode
fi

[ "$XCODE_ONLY" = true ] && ACTION="xcode"
[ "$GENERATE_XCODE" = true ] && [ "$ACTION" = "configure_and_build" ] && ACTION="xcode_build"
{ [ "$ACTION" = "xcode" ] || [ "$ACTION" = "xcode_build" ]; } && GENERATE_XCODE=true

COMPILER_VERSION=$(clang --version | head -n 1 | awk '{print $4}' | sed 's/(.*)//')
[ "$COMPILER_VERSION" = "version" ] && COMPILER_VERSION=$(clang --version | head -n 1 | awk '{print $3}')

echo "$PLATFORM :: $COMPILER-${COMPILER_VERSION}"
PROJECT_ROOT=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)

if [ "$GENERATE_XCODE" = true ]; then
  BUILD_DIR="$PROJECT_ROOT/build/${LIB_TYPE}/${BUILD_TYPE}/xcode-macos-$COMPILER-${COMPILER_VERSION}"
else
  BUILD_DIR="$PROJECT_ROOT/build/${LIB_TYPE}/${BUILD_TYPE}/build-macos-$COMPILER-${COMPILER_VERSION}"
fi

COMMON_FLAGS="-DCMAKE_BUILD_TYPE=$BUILD_TYPE -DVNE_MATH_LIB_TYPE=$LIB_TYPE -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_OSX_DEPLOYMENT_TARGET=10.15 -DBUILD_TESTS=ON -DVNE_MATH_TESTS=ON -DBUILD_EXAMPLES=OFF -DENABLE_IPO=OFF"

if [ "$GENERATE_XCODE" = true ]; then
  BUILD_CMD="xcodebuild -project vnemath.xcodeproj -configuration $BUILD_TYPE -parallelizeTargets -jobs $JOBS"
  TEST_CMD="xcodebuild -project vnemath.xcodeproj -configuration $BUILD_TYPE -target RUN_TESTS"
else
  BUILD_CMD="make -j$JOBS"
  TEST_CMD="ctest --output-on-failure"
fi

run_configure() {
  if [ "$GENERATE_XCODE" = true ]; then
    cmake -G Xcode $COMMON_FLAGS "$PROJECT_ROOT"
  else
    cmake $COMMON_FLAGS "$PROJECT_ROOT"
  fi
}

clean_build() { rm -rf "$BUILD_DIR"; mkdir -p "$BUILD_DIR"; cd "$BUILD_DIR" || exit; }
ensure_build_dir() { [ ! -d "$BUILD_DIR" ] && mkdir -p "$BUILD_DIR"; cd "$BUILD_DIR" || exit; }

case $ACTION in
  configure) [ "$CLEAN_BUILD" = true ] && clean_build || ensure_build_dir; run_configure ;;
  build) [ "$CLEAN_BUILD" = true ] && clean_build || ensure_build_dir; run_configure; eval "$BUILD_CMD" ;;
  configure_and_build) [ "$CLEAN_BUILD" = true ] && clean_build || ensure_build_dir; run_configure; eval "$BUILD_CMD" ;;
  test) [ "$CLEAN_BUILD" = true ] && clean_build || ensure_build_dir; run_configure; eval "$BUILD_CMD"; eval "$TEST_CMD" ;;
  xcode) [ "$CLEAN_BUILD" = true ] && clean_build || ensure_build_dir; run_configure; echo "Xcode project: $BUILD_DIR (vnemath.xcodeproj)" ;;
  xcode_build) [ "$CLEAN_BUILD" = true ] && clean_build || ensure_build_dir; run_configure; eval "$BUILD_CMD"; echo "Xcode build done: $BUILD_DIR" ;;
  *) usage ;;
esac

echo ""
echo "=== Build completed successfully ==="
echo "Build directory: $BUILD_DIR"

#!/bin/bash

#==============================================================================
# VneMath Linux Build Script
#==============================================================================
# Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
# Licensed under the Apache License, Version 2.0 (the "License")
#
# Autodoc:   yes
#
# Build directory: build/<lib_type>/<build_type>/build-linux-<compiler>-<version>
#==============================================================================

set -e

JOBS=10
ARGS=()
while [[ $# -gt 0 ]]; do
    case $1 in
        -j|--jobs)
            if [[ -n "$2" && "$2" =~ ^[0-9]+$ ]]; then
                JOBS="$2"
                shift 2
            else
                echo "Invalid number of jobs: $2"
                exit 1
            fi
            ;;
        -j*)
            JOBS="${1#-j}"
            if [[ ! "$JOBS" =~ ^[0-9]+$ ]]; then
                echo "Invalid number of jobs: $JOBS"
                exit 1
            fi
            shift
            ;;
        *)
            ARGS+=("$1")
            shift
            ;;
    esac
done
set -- "${ARGS[@]}"

PLATFORM="Linux"
COMPILER="gcc"

usage() {
  echo "Usage: $0 [-t <build_type>] [-a <action>] [-c <compiler>] [-l <lib_type>] [-clean] [-interactive] [-j <jobs>]"
  echo "Options:"
  echo "  -t <build_type>    Debug, Release, RelWithDebInfo, MinSizeRel"
  echo "  -a <action>        configure | build | configure_and_build | test"
  echo "  -c <compiler>      gcc | clang"
  echo "  -l <lib_type>      static | shared (default: shared). Build dir: build/<lib_type>/..."
  echo "  -clean             Clean the build directory before performing the action"
  echo "  -interactive       Interactive mode"
  echo "  -j <jobs>          Parallel jobs (default: 10)"
  exit 1
}

interactive_mode() {
  echo "=== VneMath Interactive Build Configuration ==="
  echo ""
  echo "Detected Platform: $PLATFORM"
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
  echo "Select Compiler:"
  echo "1) GCC (default)"
  echo "2) Clang"
  read -r -p "Enter choice (1-2) [1]: " compiler_choice
  case $compiler_choice in
    2) COMPILER="clang" ;;
    *) COMPILER="gcc" ;;
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

  echo ""
  echo "=== Configuration Summary ==="
  echo "Platform: $PLATFORM"
  echo "Build Type: $BUILD_TYPE"
  echo "Library Type: $LIB_TYPE (build dir: build/$LIB_TYPE/...)"
  echo "Compiler: $COMPILER"
  echo "Action: $ACTION"
  echo "Clean Build: $CLEAN_BUILD"
  echo "Parallel Jobs: $JOBS"
  echo ""
  read -r -p "Proceed with this configuration? (Y/n): " proceed
  if [[ $proceed =~ ^[Nn]$ ]]; then
    echo "Build cancelled."
    exit 0
  fi
}

BUILD_TYPE="Debug"
ACTION="configure_and_build"
COMPILER="gcc"
LIB_TYPE="shared"
CLEAN_BUILD=false
INTERACTIVE_MODE=false

while [[ $# -gt 0 ]]; do
  case $1 in
    -t|--build-type) BUILD_TYPE="$2"; shift 2 ;;
    -a|--action) ACTION="$2"; shift 2 ;;
    -c|--compiler) COMPILER="$2"; shift 2 ;;
    -l|--lib-type) LIB_TYPE="$2"; shift 2 ;;
    -clean|--clean) CLEAN_BUILD=true; shift ;;
    -interactive|--interactive) INTERACTIVE_MODE=true; shift ;;
    -h|--help) usage ;;
    *) echo "Unknown option: $1"; usage ;;
  esac
done

if [ "$INTERACTIVE_MODE" = true ]; then
  interactive_mode
fi

case "$BUILD_TYPE" in
  Debug|Release|RelWithDebInfo|MinSizeRel) ;;
  *)
    echo "Invalid -t/--build-type: '$BUILD_TYPE' (expected Debug, Release, RelWithDebInfo, or MinSizeRel)"
    exit 1
    ;;
esac

case "$LIB_TYPE" in
  static|shared) ;;
  *)
    echo "Invalid -l/--lib-type: '$LIB_TYPE' (expected static or shared)"
    exit 1
    ;;
esac

case "$COMPILER" in
  gcc|clang) ;;
  *)
    echo "Invalid -c/--compiler: '$COMPILER' (expected gcc or clang)"
    exit 1
    ;;
esac

case "$ACTION" in
  configure|build|configure_and_build|test) ;;
  *)
    echo "Invalid -a/--action: '$ACTION'"
    usage
    ;;
esac

if [ "$COMPILER" = "gcc" ]; then
  COMPILER_VERSION=$(gcc --version | head -n 1 | awk '{print $4}')
elif [ "$COMPILER" = "clang" ]; then
  COMPILER_VERSION=$(clang --version | head -n 1 | awk '{print $3}')
fi

echo "$PLATFORM :: $COMPILER-${COMPILER_VERSION}"

PROJECT_ROOT=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)
BUILD_DIR="$PROJECT_ROOT/build/${LIB_TYPE}/${BUILD_TYPE}/build-linux-$COMPILER-${COMPILER_VERSION}"

# Array-based cmake invocation (no eval — avoids injection via cache vars).
CONFIGURE_CMD=(cmake
  "-DCMAKE_BUILD_TYPE=${BUILD_TYPE}"
  "-DVNE_MATH_LIB_TYPE=${LIB_TYPE}"
  -DBUILD_TESTS=ON
  -DVNE_MATH_TESTS=ON
)
if [ "$COMPILER" = "gcc" ]; then
  CONFIGURE_CMD+=(-DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++)
else
  CONFIGURE_CMD+=(-DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DENABLE_IPO=OFF)
fi
CONFIGURE_CMD+=("$PROJECT_ROOT")

BUILD_CMD=(make -j"$JOBS")
TEST_CMD=(ctest --output-on-failure)

clean_build() {
  rm -rf "$BUILD_DIR"
  mkdir -p "$BUILD_DIR"
  cd "$BUILD_DIR" || exit
}

ensure_build_dir() {
  if [ ! -d "$BUILD_DIR" ]; then
    mkdir -p "$BUILD_DIR"
  fi
  cd "$BUILD_DIR" || exit
}

configure_project() {
  echo "Configuring: $(printf '%q ' "${CONFIGURE_CMD[@]}")"
  "${CONFIGURE_CMD[@]}"
}

build_project() {
  echo "Building with $JOBS parallel jobs..."
  "${BUILD_CMD[@]}"
}

run_tests() {
  "${TEST_CMD[@]}"
}

case $ACTION in
  configure)
    if [ "$CLEAN_BUILD" = true ]; then
      clean_build
    else
      ensure_build_dir
    fi
    configure_project
    ;;
  build)
    if [ "$CLEAN_BUILD" = true ]; then
      clean_build
    else
      ensure_build_dir
    fi
    configure_project
    build_project
    ;;
  configure_and_build)
    if [ "$CLEAN_BUILD" = true ]; then
      clean_build
    else
      ensure_build_dir
    fi
    configure_project
    build_project
    ;;
  test)
    if [ "$CLEAN_BUILD" = true ]; then
      clean_build
    else
      ensure_build_dir
    fi
    configure_project
    build_project
    run_tests
    ;;
  *)
    usage
    ;;
esac

echo ""
echo "=== Build completed successfully ==="
echo "Build directory: $BUILD_DIR"

#!/bin/bash

#==============================================================================
# VneMath macOS Build Script
#==============================================================================
# Copyright (c) 2024 Ajeet Singh Yadav. All rights reserved.
# Licensed under the Apache License, Version 2.0 (the "License")
#
# Author:    Ajeet Singh Yadav
# Created:   January 2025
#
# This script builds VneMath for macOS with Xcode integration
#==============================================================================

set -e  # Exit on any error

# Default parallel jobs
JOBS=10

# Parse command line arguments for jobs
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

# Reconstruct ARGS for the rest of the script
set -- "${ARGS[@]}"

# Platform detection (force macOS)
PLATFORM="Darwin"
COMPILER="clang"

# Function to display usage information
usage() {
  echo "Usage: $0 [-t <build_type>] [-a <action>] [-clean] [-interactive] [-j <jobs>] [-xcode] [-xcode-only]"
  echo "Options:"
  echo "  -t <build_type>    Specify the build type (Debug, Release, RelWithDebInfo, MinSizeRel)"
  echo "  -a <action>        Specify the action to perform:"
  echo "                     configure: Configure the project"
  echo "                     build: Build the project"
  echo "                     configure_and_build: Configure and build the project"
  echo "                     test: Run tests"
  echo "  -clean             Clean the build directory before performing the action"
  echo "  -interactive       Run in interactive mode to choose options"
  echo "  -j <jobs>          Number of parallel jobs (default: 10)"
  echo ""
  echo "Examples:"
  echo "  $0 -t Debug -a configure_and_build"
  echo "  $0 -j 32"
  echo "  $0 -interactive"
  echo "  $0 -t Release -clean"
  exit 1
}

# Default values
BUILD_TYPE="Debug"
ACTION="configure_and_build"
COMPILER="clang"
CLEAN_BUILD=false
INTERACTIVE_MODE=false

# Parse command-line arguments
while [[ $# -gt 0 ]]; do
  case $1 in
    -t|--build-type)
      BUILD_TYPE="$2"
      shift 2
      ;;
    -a|--action)
      ACTION="$2"
      shift 2
      ;;
    -clean|--clean)
      CLEAN_BUILD=true
      shift
      ;;
    -interactive|--interactive)
      INTERACTIVE_MODE=true
      shift
      ;;
    -h|--help)
      usage
      ;;
    *)
      echo "Unknown option: $1"
      usage
      ;;
  esac
done

# Determine compiler version
if [ "$COMPILER" = "clang" ]; then
  COMPILER_VERSION=$(clang --version | head -n 1 | awk '{print $4}' | sed 's/(.*)//')
  if [ "$COMPILER_VERSION" = "version" ]; then
    COMPILER_VERSION=$(clang --version | head -n 1 | awk '{print $3}')
  fi
else
  echo "Unsupported compiler: $COMPILER"
  exit 1
fi

echo "$PLATFORM :: $COMPILER-${COMPILER_VERSION}"

# Store project root directory
PROJECT_ROOT=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)

# Set the build directory based on build type and compiler
BUILD_DIR="$PROJECT_ROOT/build/${BUILD_TYPE}/build-macos-$COMPILER-${COMPILER_VERSION}"

# Build CMake command
build_cmake_command() {
  local base_cmd="cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_OSX_DEPLOYMENT_TARGET=10.15 -DBUILD_TESTS=ON"
  echo "$base_cmd $PROJECT_ROOT"
}

CONFIGURE_COMMAND=$(build_cmake_command)
BUILD_COMMAND="make -j$JOBS"
TEST_COMMAND="ctest --output-on-failure"

# Clean previous build
clean_build() {
  rm -rf "$BUILD_DIR"
  mkdir -p "$BUILD_DIR"
  cd "$BUILD_DIR" || exit
}

# Ensure build directory exists (if not cleaning)
ensure_build_dir() {
  if [ ! -d "$BUILD_DIR" ]; then
    mkdir -p "$BUILD_DIR"
  fi
  cd "$BUILD_DIR" || exit
}

# Configure the project
configure_project() {
  echo "Configuring with command: $CONFIGURE_COMMAND"
  eval $CONFIGURE_COMMAND
}

# Build the project
build_project() {
  echo "Building with $JOBS parallel jobs..."
  eval $BUILD_COMMAND
}

# Run tests
run_tests() {
  eval $TEST_COMMAND
}

# Perform actions based on the specified option
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

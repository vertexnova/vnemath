#==============================================================================
# Copyright (c) 2024 Ajeet Singh Yadav. All rights reserved.
# Licensed under the Apache License, Version 2.0 (the "License")
#
# Author:    Ajeet Singh Yadav
# Created:   January 2025
#
# Autodoc:   yes
#==============================================================================

# Minimum required CMake version
cmake_minimum_required(VERSION 3.16)

# Project declaration
project(vnemath VERSION 1.0.0 LANGUAGES CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS False)

#==============================================================================
# Add custom CMake modules path
#==============================================================================
# VneCMake shared modules (submodule)
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/vnecmake/modules")
# Project-specific modules
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

#==============================================================================
# Project Setup
#==============================================================================
include(ProjectSetup)

#==============================================================================
# Platform Detection
#==============================================================================

# Allow manual override of target platform first
if(DEFINED VNE_TARGET_PLATFORM)
    message(STATUS "Using manually specified target platform: ${VNE_TARGET_PLATFORM}")
else()
    # Detect the platform and set platform-specific macros
    if(EMSCRIPTEN)
        set(VNE_TARGET_PLATFORM "Web")
    elseif(WIN32)
        set(VNE_TARGET_PLATFORM "Windows")
    elseif(APPLE)
        if(VISIONOS OR ${CMAKE_SYSTEM_NAME} STREQUAL "visionOS")
            set(VNE_TARGET_PLATFORM "visionOS")
        elseif(IOS OR ${CMAKE_SYSTEM_NAME} STREQUAL "iOS")
            set(VNE_TARGET_PLATFORM "iOS")
        else()
            set(VNE_TARGET_PLATFORM "macOS")
        endif()
    elseif(UNIX)
        if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
            set(VNE_TARGET_PLATFORM "Linux")
        elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Android")
            set(VNE_TARGET_PLATFORM "Android")
        else()
            message(FATAL_ERROR "Unsupported UNIX platform: ${CMAKE_SYSTEM_NAME}")
        endif()
    else()
        message(FATAL_ERROR "Unsupported platform")
    endif()
endif()

# Output the detected platform
message(STATUS "Detected platform: ${VNE_TARGET_PLATFORM}")

#==============================================================================
# Platform-specific compile definitions
#==============================================================================

if(VNE_TARGET_PLATFORM STREQUAL "macOS")
    add_compile_definitions(VNE_PLATFORM_MACOS)
    message(STATUS "Defined VNE_PLATFORM_MACOS")
elseif(VNE_TARGET_PLATFORM STREQUAL "iOS")
    add_compile_definitions(VNE_PLATFORM_IOS)
    message(STATUS "Defined VNE_PLATFORM_IOS")
elseif(VNE_TARGET_PLATFORM STREQUAL "visionOS")
    add_compile_definitions(VNE_PLATFORM_VISIONOS)
    message(STATUS "Defined VNE_PLATFORM_VISIONOS")
elseif(VNE_TARGET_PLATFORM STREQUAL "Windows")
    add_compile_definitions(VNE_PLATFORM_WIN)
    message(STATUS "Defined VNE_PLATFORM_WIN")
elseif(VNE_TARGET_PLATFORM STREQUAL "Linux")
    add_compile_definitions(VNE_PLATFORM_LINUX)
    message(STATUS "Defined VNE_PLATFORM_LINUX")
elseif(VNE_TARGET_PLATFORM STREQUAL "Android")
    add_compile_definitions(VNE_PLATFORM_ANDROID)
    message(STATUS "Defined VNE_PLATFORM_ANDROID")
elseif(VNE_TARGET_PLATFORM STREQUAL "Web")
    add_compile_definitions(VNE_PLATFORM_WEB)
    message(STATUS "Defined VNE_PLATFORM_WEB")
endif()

#==============================================================================
# Build Options
#==============================================================================
# Build presets: DEV (local repo) and CI (pipelines). Default DEV when top-level project.
# Use CMake's built-in top-level detection; fallback for CMake < 3.21.
if(DEFINED PROJECT_IS_TOP_LEVEL AND PROJECT_IS_TOP_LEVEL)
    set(VNE_MATH_DEV_DEFAULT ON)
elseif(NOT DEFINED PROJECT_IS_TOP_LEVEL AND CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    set(VNE_MATH_DEV_DEFAULT ON)
else()
    set(VNE_MATH_DEV_DEFAULT OFF)
endif()
option(VNE_MATH_DEV "Dev build: enable examples and tests (local development)" ${VNE_MATH_DEV_DEFAULT})
option(VNE_MATH_CI "CI build: enable tests, disable examples (e.g. -DVNE_MATH_CI=ON in pipelines)" OFF)

# Ensure CI preset takes precedence over DEV when both are specified.
if(VNE_MATH_CI)
    set(VNE_MATH_DEV OFF CACHE BOOL "Dev build: enable examples and tests (local development)" FORCE)
endif()

# CMake Options and Presets:
# | Option / Preset   | Default        | Description                                                      |
# |-------------------|----------------|------------------------------------------------------------------|
# | VNE_MATH_DEV      | ON (top-level) | Dev preset: BUILD_TESTS=ON, BUILD_EXAMPLES=ON                     |
# | VNE_MATH_CI       | OFF            | CI preset: BUILD_TESTS=ON, BUILD_EXAMPLES=OFF                     |
# | BUILD_TESTS       | ON             | Build the test suite                                              |
# | VNE_MATH_TESTS    | ON             | Build vnemath test suite (can be set to OFF by parent projects)   |
# | BUILD_EXAMPLES    | OFF            | Build example programs                                            |
# | ENABLE_COVERAGE   | OFF            | Enable code coverage reporting                                    |
option(BUILD_TESTS "Build the test suite" ON)
option(VNE_MATH_TESTS "Build vnemath test suite (turn OFF when used as submodule with only parent tests)" ON)
option(BUILD_EXAMPLES "Build example programs" OFF)
option(ENABLE_COVERAGE "Enable code coverage reporting" OFF)

# Apply CI or DEV preset (CI takes precedence; DEV is ignored when CI is active)
if(VNE_MATH_CI)
    set(BUILD_TESTS ON CACHE BOOL "Build the test suite" FORCE)
    set(VNE_MATH_TESTS ON CACHE BOOL "Build vnemath test suite (turn OFF when used as submodule with only parent tests)" FORCE)
    set(BUILD_EXAMPLES OFF CACHE BOOL "Build example programs" FORCE)
    set(VNE_MATH_DEV OFF CACHE BOOL "Disable DEV preset when CI preset is active" FORCE)
    message(STATUS "VneMath: CI build -> BUILD_TESTS=ON, VNE_MATH_TESTS=ON, BUILD_EXAMPLES=OFF")
elseif(VNE_MATH_DEV)
    set(BUILD_TESTS ON CACHE BOOL "Build the test suite" FORCE)
    set(VNE_MATH_TESTS ON CACHE BOOL "Build vnemath test suite (turn OFF when used as submodule with only parent tests)" FORCE)
    set(BUILD_EXAMPLES ON CACHE BOOL "Build example programs" FORCE)
    message(STATUS "VneMath: DEV build -> BUILD_TESTS=ON, VNE_MATH_TESTS=ON, BUILD_EXAMPLES=ON")
endif()

# Enable cache system
option(ENABLE_CACHE "Enable compiler cache if available" OFF)
include(CCache)

# Enable static code analysis tools options
option(ENABLE_CPPCHECK "Enable static analysis with cppcheck" OFF)
include(CppCheck)
option(ENABLE_CLANG_TIDY "Enable static analysis with clang-tidy" OFF)
include(ClangTidy)

#==============================================================================
# Coverage Support
#==============================================================================

if(ENABLE_COVERAGE)
    include(FindCoverage)
endif()

#==============================================================================
# Compiler Warnings
#==============================================================================

add_library(MathWarnings INTERFACE)
include(ProjectWarnings)
set_project_warnings(MathWarnings)
add_library(vne::math::Warnings ALIAS MathWarnings)

#==============================================================================
# Build Settings Interface Library
#==============================================================================

add_library(MathBuildSettings INTERFACE)
add_library(vne::math::BuildSettings ALIAS MathBuildSettings)

# Set compile definitions for the interface library based on the build type
if(CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_definitions(MathBuildSettings INTERFACE VNE_BUILD_TYPE_DEBUG VNE_DEVELOPER_BUILD)
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    target_compile_definitions(MathBuildSettings INTERFACE VNE_BUILD_TYPE_RELEASE)
elseif(CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)
    target_compile_definitions(MathBuildSettings INTERFACE VNE_BUILD_TYPE_RELWITHDEBINFO)
elseif(CMAKE_BUILD_TYPE MATCHES MinSizeRel)
    target_compile_definitions(MathBuildSettings INTERFACE VNE_BUILD_TYPE_MINSIZEREL)
endif()

# Define platform-specific compile definitions
if(${VNE_TARGET_PLATFORM} STREQUAL "Windows")
    target_compile_definitions(MathBuildSettings INTERFACE VNE_PLATFORM_WIN)
elseif(${VNE_TARGET_PLATFORM} STREQUAL "Linux")
    target_compile_definitions(MathBuildSettings INTERFACE VNE_PLATFORM_LINUX)
elseif(${VNE_TARGET_PLATFORM} STREQUAL "macOS")
    target_compile_definitions(MathBuildSettings INTERFACE VNE_PLATFORM_MACOS)
elseif(${VNE_TARGET_PLATFORM} STREQUAL "iOS")
    target_compile_definitions(MathBuildSettings INTERFACE VNE_PLATFORM_IOS)
elseif(${VNE_TARGET_PLATFORM} STREQUAL "visionOS")
    target_compile_definitions(MathBuildSettings INTERFACE VNE_PLATFORM_VISIONOS)
elseif(${VNE_TARGET_PLATFORM} STREQUAL "Android")
    target_compile_definitions(MathBuildSettings INTERFACE VNE_PLATFORM_ANDROID)
elseif(${VNE_TARGET_PLATFORM} STREQUAL "Web")
    target_compile_definitions(MathBuildSettings INTERFACE VNE_PLATFORM_WEB)
endif()

#==============================================================================
# Include Directories
#==============================================================================

set(VNE_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(VNE_SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(VNE_BUILD_DIR ${CMAKE_BINARY_DIR})
set(VNE_DEPS_DIR ${PROJECT_SOURCE_DIR}/deps)

#==============================================================================
# Configure config.h
#==============================================================================

configure_file(configs/config.h.in ${CMAKE_BINARY_DIR}/config.h)
include_directories("${CMAKE_BINARY_DIR}")

#==============================================================================
# External Dependencies (deps/external/) - third-party libraries
#==============================================================================
set(VNE_DEPS_EXTERNAL_DIR ${VNE_DEPS_DIR}/external)

function(_vnemath_configure_glm_dep)
    if(EXISTS "${VNE_DEPS_EXTERNAL_DIR}/glm/CMakeLists.txt")
        message(STATUS "Using GLM from deps/external/glm (v1.0.1)")
        add_subdirectory(${VNE_DEPS_EXTERNAL_DIR}/glm ${CMAKE_BINARY_DIR}/deps/external/glm)
    else()
        find_package(glm QUIET)
        if(NOT glm_FOUND)
            message(STATUS "GLM not found, using FetchContent")
            include(FetchContent)
            FetchContent_Declare(
                glm
                GIT_REPOSITORY https://github.com/g-truc/glm.git
                GIT_TAG 1.0.1
            )
            FetchContent_MakeAvailable(glm)
        else()
            message(STATUS "Using system GLM")
        endif()
    endif()
endfunction()

_vnemath_configure_glm_dep()

#==============================================================================
# Internal Libraries (deps/internal/) - use if already in build, else add
#==============================================================================
set(VNE_DEPS_INTERNAL_DIR ${VNE_DEPS_DIR}/internal)
include(VneUseDep)

function(_vnemath_configure_vnecommon_dep)
    vne_use_dep(TARGET vne::common
        SUBDIR "${VNE_DEPS_INTERNAL_DIR}/vnecommon"
        BINARY_DIR "${CMAKE_BINARY_DIR}/deps/internal/vnecommon")
endfunction()

function(_vnemath_configure_vnelogging_dep)
    set(_vnemath_build_tests_saved "${BUILD_TESTS}")
    set(_vnemath_build_examples_saved "${BUILD_EXAMPLES}")
    vne_use_dep(TARGET vne::logging
        SUBDIR "${VNE_DEPS_INTERNAL_DIR}/vnelogging"
        BINARY_DIR "${CMAKE_BINARY_DIR}/deps/internal/vnelogging"
        CACHE_VARS BUILD_TESTS OFF BUILD_EXAMPLES OFF)
    set_property(CACHE BUILD_TESTS PROPERTY VALUE "${_vnemath_build_tests_saved}")
    set_property(CACHE BUILD_EXAMPLES PROPERTY VALUE "${_vnemath_build_examples_saved}")
endfunction()

_vnemath_configure_vnecommon_dep()
_vnemath_configure_vnelogging_dep()

#==============================================================================
# Add Library
#==============================================================================

add_subdirectory(src)

#==============================================================================
# Tests (only when BUILD_TESTS and VNE_MATH_TESTS; parent can set VNE_MATH_TESTS=OFF)
#==============================================================================

if(BUILD_TESTS AND VNE_MATH_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

#==============================================================================
# Examples
#==============================================================================

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

#==============================================================================
# Installation
#==============================================================================

include(GNUInstallDirs)

# Install the library
install(TARGETS vnemath
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Install public headers from include/
install(DIRECTORY include/vertexnova/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/vertexnova
    FILES_MATCHING PATTERN "*.h"
)

# Install internal headers from src/ (needed for implementation)
install(DIRECTORY src/vertexnova/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/vertexnova
    FILES_MATCHING PATTERN "*.h"
)

# Install config.h
install(FILES ${CMAKE_BINARY_DIR}/config.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/vertexnova/math
)

# Install CMake module
install(FILES cmake/FindVneMath.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/VneMath
)

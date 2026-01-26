#==============================================================================
# Copyright (c) 2024 Ajeet Singh Yadav. All rights reserved.
# Licensed under the Apache License, Version 2.0 (the "License")
#
# Author:    Ajeet Singh Yadav
# Created:   January 2025
#
# Autodoc:   yes
#==============================================================================

cmake_minimum_required(VERSION 3.16)

project(TestVneMath)

# Disable tests for iOS and Web platforms
if(VNE_PLATFORM_IOS OR VNE_PLATFORM_WEB)
    message(STATUS "Math tests disabled for ${CMAKE_SYSTEM_NAME} platform")
    return()
endif()

#==============================================================================
# Setup Google Test
#==============================================================================

# Use external googletest submodule (v1.17.0)
if(EXISTS "${CMAKE_SOURCE_DIR}/external/googletest/CMakeLists.txt")
    message(STATUS "Using Google Test from external/googletest (v1.17.0)")
    add_subdirectory(${CMAKE_SOURCE_DIR}/external/googletest ${CMAKE_BINARY_DIR}/external/googletest)
    include(GoogleTest)
    set(GTEST_LIBRARIES gtest_main gmock)
    set(GTEST_INCLUDE_DIRS 
        ${CMAKE_SOURCE_DIR}/external/googletest/googletest/include 
        ${CMAKE_SOURCE_DIR}/external/googletest/googlemock/include
    )
else()
    # Try to find GoogleTest in system
    find_package(GTest QUIET)
    if(GTest_FOUND)
        message(STATUS "Using system Google Test")
        set(GTEST_LIBRARIES GTest::gtest_main GTest::gmock)
        set(GTEST_INCLUDE_DIRS ${GTEST_INCLUDE_DIRS})
    else()
        # Fallback to FetchContent
        message(STATUS "external/googletest not found, using FetchContent")
        include(FetchContent)
        FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG        v1.17.0
        )
        FetchContent_MakeAvailable(googletest)
        set(GTEST_LIBRARIES gtest_main gmock)
        set(GTEST_INCLUDE_DIRS ${googletest_SOURCE_DIR}/googletest/include ${googletest_SOURCE_DIR}/googlemock/include)
    endif()
endif()

#==============================================================================
#                              Source and Headers                              #
#==============================================================================

set(TEST_SOURCES
    # Core templated types tests
    math/core/vec_test.cpp
    math/core/mat_test.cpp
    math/core/quat_test.cpp
    # Other math tests
    math/color_test.cpp
    math/transform_node_test.cpp
    math/random_test.cpp
    math/math_utils_test.cpp
    math/angle_utils_test.cpp
    math/easing_test.cpp
    # New feature tests
    math/curves_test.cpp
    math/noise_test.cpp
    math/transform_utils_test.cpp
    # Multi-backend graphics API tests
    math/graphics_api_test.cpp
    math/camera_test.cpp
    math/gpu_types_test.cpp
    # Geometry tests
    math/geometry/ray_test.cpp
    math/geometry/plane_test.cpp
    math/geometry/aabb_test.cpp
    math/geometry/sphere_test.cpp
    math/geometry/frustum_test.cpp
    math/geometry/culling_test.cpp
    math/geometry/intersection_test.cpp
    math/geometry/line_segment_test.cpp
    math/geometry/line_test.cpp
    math/geometry/rect_test.cpp
    math/geometry/obb_test.cpp
    math/geometry/capsule_test.cpp
    math/geometry/triangle_test.cpp
    math/statistic_test.cpp
    main.cpp
)

#==============================================================================
#                              Build Executable                                #
#==============================================================================

# Create the test executable
add_executable(TestVneMath ${TEST_SOURCES})

# Include directories
target_include_directories(TestVneMath
    SYSTEM PUBLIC
        ${GTEST_INCLUDE_DIRS}
    PUBLIC
        $<BUILD_INTERFACE:${VNE_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${VNE_SRC_DIR}>
)

# Link libraries
target_link_libraries(TestVneMath
    PRIVATE
        ${GTEST_LIBRARIES}
        vne::math
)

# Web platform specific configuration
if(VNE_PLATFORM_WEB)
    target_compile_definitions(TestVneMath PRIVATE VNE_PLATFORM_WEB)
    set_target_properties(TestVneMath PROPERTIES
        SUFFIX ".js"
    )
endif()

# Add a test
add_test(NAME vnemath.test COMMAND TestVneMath)

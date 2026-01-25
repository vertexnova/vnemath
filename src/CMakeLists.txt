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

project(vnemath)

#==============================================================================
#                              Source and Headers                              #
#==============================================================================

# Define header files
set(INCLUDE_FILES
    ${VNE_INCLUDE_DIR}/vertexnova/math/math.h
    ${VNE_INCLUDE_DIR}/vertexnova/math/color.h
    ${VNE_INCLUDE_DIR}/vertexnova/math/transform_node.h
    ${VNE_INCLUDE_DIR}/vertexnova/math/random.h
    # Interpolation and animation
    ${VNE_INCLUDE_DIR}/vertexnova/math/easing.h
    ${VNE_INCLUDE_DIR}/vertexnova/math/curves.h
    # Procedural generation
    ${VNE_INCLUDE_DIR}/vertexnova/math/noise.h
    # Coordinate space utilities
    ${VNE_INCLUDE_DIR}/vertexnova/math/projection_utils.h
    ${VNE_INCLUDE_DIR}/vertexnova/math/transform_utils.h
    ${VNE_INCLUDE_DIR}/vertexnova/math/viewport.h
    # Geometry headers
    ${VNE_INCLUDE_DIR}/vertexnova/math/geometry/ray.h
    ${VNE_INCLUDE_DIR}/vertexnova/math/geometry/plane.h
    ${VNE_INCLUDE_DIR}/vertexnova/math/geometry/aabb.h
    ${VNE_INCLUDE_DIR}/vertexnova/math/geometry/sphere.h
    ${VNE_INCLUDE_DIR}/vertexnova/math/geometry/frustum.h
    ${VNE_INCLUDE_DIR}/vertexnova/math/geometry/geometry.h
    ${VNE_INCLUDE_DIR}/vertexnova/math/geometry/triangle.h
    ${VNE_INCLUDE_DIR}/vertexnova/math/geometry/capsule.h
    ${VNE_INCLUDE_DIR}/vertexnova/math/geometry/obb.h
    ${VNE_INCLUDE_DIR}/vertexnova/math/geometry/intersection.h
    ${VNE_INCLUDE_DIR}/vertexnova/math/geometry/line.h
    ${VNE_INCLUDE_DIR}/vertexnova/math/geometry/line_segment.h
    ${VNE_INCLUDE_DIR}/vertexnova/math/geometry/rect.h
    # Core headers
    ${VNE_INCLUDE_DIR}/vertexnova/math/core/constants.h
    ${VNE_INCLUDE_DIR}/vertexnova/math/core/math_utils.h
    ${VNE_INCLUDE_DIR}/vertexnova/math/core/types.h
    ${VNE_INCLUDE_DIR}/vertexnova/math/core/vec.h
    ${VNE_INCLUDE_DIR}/vertexnova/math/core/mat.h
    ${VNE_INCLUDE_DIR}/vertexnova/math/core/quat.h
    ${VNE_INCLUDE_DIR}/vertexnova/math/core/core.h
)

# Define source files
set(SOURCE_FILES
    vertexnova/math/color.cpp
    vertexnova/math/transform_node.cpp
    # Geometry sources
    vertexnova/math/geometry/ray.cpp
    vertexnova/math/geometry/plane.cpp
    vertexnova/math/geometry/aabb.cpp
    vertexnova/math/geometry/sphere.cpp
    vertexnova/math/geometry/frustum.cpp
    vertexnova/math/geometry/rect.cpp
    vertexnova/math/geometry/line.cpp
    vertexnova/math/geometry/line_segment.cpp
    vertexnova/math/geometry/triangle.cpp
    vertexnova/math/geometry/obb.cpp
    vertexnova/math/geometry/capsule.cpp
)

#==============================================================================
#                                 Library                                      #
#==============================================================================

# Create a library from the source and header files
add_library(vnemath STATIC ${SOURCE_FILES} ${INCLUDE_FILES})

# Alias for the library
add_library(vne::math ALIAS vnemath)

# Set include directories for the library
target_include_directories(vnemath
    PUBLIC
        $<BUILD_INTERFACE:${VNE_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${VNE_SRC_DIR}>
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>
        $<INSTALL_INTERFACE:include>
)

# Link against interface libraries
target_link_libraries(vnemath
    PRIVATE
        vne::math::Warnings
        vne::math::BuildSettings
)

#==============================================================================
#                          Third-Party Libraries Setup                          #
#==============================================================================

# Link against GLM (use header-only interface if available)
if(TARGET glm::glm-header-only)
    target_link_libraries(vnemath PUBLIC glm::glm-header-only)
elseif(TARGET glm::glm)
    target_link_libraries(vnemath PUBLIC glm::glm)
elseif(TARGET glm)
    target_link_libraries(vnemath PUBLIC glm)
endif()

# Enable experimental features in GLM
target_compile_definitions(vnemath
    PUBLIC
        GLM_ENABLE_EXPERIMENTAL
        GLM_FORCE_DEPTH_ZERO_TO_ONE  # For Vulkan/Metal NDC z-range [0,1]
)

#==============================================================================
#                          VneCommon Integration                               #
#==============================================================================

# Link against VneCommon
if(TARGET vne::common)
    target_link_libraries(vnemath PUBLIC vne::common)
    message(STATUS "VneMath: Linked against vne::common")
endif()

#==============================================================================
#                          VneLogging Integration                              #
#==============================================================================

# Link against VneLogging if available
if(TARGET vne::logging)
    target_link_libraries(vnemath PUBLIC vne::logging)
    message(STATUS "VneMath: Linked against vne::logging")
elseif(TARGET vnelogging)
    target_link_libraries(vnemath PUBLIC vnelogging)
    message(STATUS "VneMath: Linked against vnelogging")
endif()

#==============================================================================
#                          Platform-specific linking                           #
#==============================================================================

if(NOT WIN32)
    target_link_libraries(vnemath PRIVATE pthread)
endif()

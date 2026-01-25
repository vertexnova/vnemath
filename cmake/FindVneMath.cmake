#==============================================================================
# Copyright (c) 2024 Ajeet Singh Yadav. All rights reserved.
# Licensed under the Apache License, Version 2.0 (the "License")
#
# Author:    Ajeet Singh Yadav
# Created:   January 2025
#
# Autodoc:   yes
#==============================================================================

# FindVneMath.cmake
# This module finds VneMath library

include(FindPackageHandleStandardArgs)

# Find include directory
find_path(VneMath_INCLUDE_DIR
    NAMES vertexnova/math/math.h
    PATHS
        ${CMAKE_INSTALL_PREFIX}/include
        /usr/local/include
        /usr/include
)

# Find library
find_library(VneMath_LIBRARY
    NAMES vnemath
    PATHS
        ${CMAKE_INSTALL_PREFIX}/lib
        /usr/local/lib
        /usr/lib
)

# Handle standard arguments
find_package_handle_standard_args(VneMath
    REQUIRED_VARS VneMath_LIBRARY VneMath_INCLUDE_DIR
)

if(VneMath_FOUND AND NOT TARGET vne::math)
    add_library(vne::math STATIC IMPORTED)
    set_target_properties(vne::math PROPERTIES
        IMPORTED_LOCATION "${VneMath_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${VneMath_INCLUDE_DIR}"
    )
endif()

mark_as_advanced(VneMath_INCLUDE_DIR VneMath_LIBRARY)

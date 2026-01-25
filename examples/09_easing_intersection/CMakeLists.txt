#==============================================================================
# Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
# Licensed under the Apache License, Version 2.0 (the "License")
#==============================================================================

add_executable(example_09_easing main.cpp)

target_link_libraries(example_09_easing PRIVATE vne::math)

target_include_directories(example_09_easing PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)

set_target_properties(example_09_easing PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/examples
)

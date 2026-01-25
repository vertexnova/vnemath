#==============================================================================
# Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
# Licensed under the Apache License, Version 2.0 (the "License")
#==============================================================================

add_executable(example_08_gpu_alignment main.cpp)

target_link_libraries(example_08_gpu_alignment PRIVATE vne::math)

target_include_directories(example_08_gpu_alignment PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)

set_target_properties(example_08_gpu_alignment PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/examples
)

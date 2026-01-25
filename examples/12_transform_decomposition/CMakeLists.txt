#==============================================================================
# 12_transform_decomposition Example
#==============================================================================

add_executable(example_12_transform_decomposition main.cpp)

target_link_libraries(example_12_transform_decomposition PRIVATE vne::math)

target_include_directories(example_12_transform_decomposition PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)

set_target_properties(example_12_transform_decomposition PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/examples"
)

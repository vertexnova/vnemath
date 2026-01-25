#==============================================================================
# 06_ray_intersection Example
#==============================================================================

add_executable(example_06_ray main.cpp)

target_link_libraries(example_06_ray PRIVATE vne::math)

target_include_directories(example_06_ray PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)

set_target_properties(example_06_ray PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/examples"
)

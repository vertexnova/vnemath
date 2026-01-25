#==============================================================================
# 05_scene_graph Example
#==============================================================================

add_executable(example_05_scene_graph main.cpp)

target_link_libraries(example_05_scene_graph PRIVATE vne::math)

set_target_properties(example_05_scene_graph PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/examples"
)

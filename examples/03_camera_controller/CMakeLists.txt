#==============================================================================
# 03_camera_controller Example
#==============================================================================

add_executable(example_03_camera main.cpp)

target_link_libraries(example_03_camera PRIVATE vne::math)

set_target_properties(example_03_camera PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/examples"
)

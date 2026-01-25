#==============================================================================
# 03_camera_controller Example
#==============================================================================

add_executable(example_03_camera main.cpp)

target_link_libraries(example_03_camera PRIVATE vne::math)

target_include_directories(example_03_camera PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)

set_target_properties(example_03_camera PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/examples"
)

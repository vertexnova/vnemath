#==============================================================================
# 10_curves_animation Example
#==============================================================================

add_executable(example_10_curves_animation main.cpp)

target_link_libraries(example_10_curves_animation PRIVATE vne::math)

target_include_directories(example_10_curves_animation PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)

set_target_properties(example_10_curves_animation PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/examples"
)

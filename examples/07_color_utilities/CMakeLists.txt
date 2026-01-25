#==============================================================================
# 07_color_utilities Example
#==============================================================================

add_executable(example_07_color main.cpp)

target_link_libraries(example_07_color PRIVATE vne::math)

target_include_directories(example_07_color PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)

set_target_properties(example_07_color PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/examples"
)

#==============================================================================
# 04_frustum_culling Example
#==============================================================================

add_executable(example_04_frustum main.cpp)

target_link_libraries(example_04_frustum PRIVATE vne::math)

target_include_directories(example_04_frustum PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)

set_target_properties(example_04_frustum PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/examples"
)

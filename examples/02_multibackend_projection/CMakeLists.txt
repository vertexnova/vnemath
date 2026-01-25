#==============================================================================
# 02_multibackend_projection Example
#==============================================================================

add_executable(example_02_multibackend main.cpp)

target_link_libraries(example_02_multibackend PRIVATE vne::math)

set_target_properties(example_02_multibackend PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/examples"
)

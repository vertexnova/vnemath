#==============================================================================
# 02_multibackend_projection Example
#==============================================================================

add_executable(example_02_multibackend main.cpp)

target_link_libraries(example_02_multibackend PRIVATE vne::math)

target_include_directories(example_02_multibackend PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)

set_target_properties(example_02_multibackend PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/examples"
)

#==============================================================================
# 01_hello_math Example
#==============================================================================

add_executable(example_01_hello_math main.cpp)

target_link_libraries(example_01_hello_math PRIVATE vne::math)

set_target_properties(example_01_hello_math PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/examples"
)

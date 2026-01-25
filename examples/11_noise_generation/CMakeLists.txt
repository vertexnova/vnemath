#==============================================================================
# 11_noise_generation Example
#==============================================================================

add_executable(example_11_noise_generation main.cpp)

target_link_libraries(example_11_noise_generation PRIVATE vne::math)

target_include_directories(example_11_noise_generation PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)

set_target_properties(example_11_noise_generation PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/examples"
)

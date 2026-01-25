#==============================================================================
# VneMath Examples CMakeLists.txt
#==============================================================================

# 01 - Hello Math: Basic vectors, matrices, and quaternions
add_subdirectory(01_hello_math)

# 02 - Multi-backend Projection: Graphics API-specific projection matrices
add_subdirectory(02_multibackend_projection)

# 03 - Camera Controller: FPS and orbital camera implementations
add_subdirectory(03_camera_controller)

# 04 - Frustum Culling: Visibility testing with geometry primitives
add_subdirectory(04_frustum_culling)

# 05 - Scene Graph: Hierarchical transforms with TransformNode
add_subdirectory(05_scene_graph)

# 06 - Ray Intersection: Ray casting against geometry primitives
add_subdirectory(06_ray_intersection)

# 07 - Color Utilities: Color manipulation and conversions
add_subdirectory(07_color_utilities)

# 08 - GPU Buffer Alignment: Memory layout for shader uniform buffers
add_subdirectory(08_gpu_buffer_alignment)

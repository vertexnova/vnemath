#pragma once
/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Author:    Ajeet Singh Yadav
 * Created:   January 2026
 *
 * Scene object for frustum culling example
 * ----------------------------------------------------------------------
 */

#include <vertexnova/math/geometry/aabb.h>

#include <string>

namespace vne::math::examples {

/**
 * @struct SceneObject
 * @brief Simple scene object with a name and bounding box.
 *
 * Used to demonstrate frustum culling on a collection of objects.
 */
struct SceneObject {
    std::string name;  ///< Human-readable name of the object
    Aabb bounds;       ///< Axis-aligned bounding box
};

}  // namespace vne::math::examples

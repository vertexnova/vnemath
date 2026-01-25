#pragma once
/* ---------------------------------------------------------------------
 * Copyright (c) 2024 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Author:    Ajeet Singh Yadav
 * Created:   January 2025
 *
 * Autodoc:   yes
 * ----------------------------------------------------------------------
 */

/**
 * @file math.h
 * @brief Main include file for the VNE Math library.
 *
 * This file includes all the math module headers for convenient access.
 */

// Core templated types (Vec, Mat, Quat)
#include "core/core.h"

// Math module includes
#include "constants.h"
#include "math_utils.h"
#include "color.h"
#include "transform_node.h"
#include "random.h"

// Geometry module includes
#include "geometry/geometry.h"

namespace vne::math {

// Type alias for backward compatibility
using Quaternion = Quatf;

}  // namespace vne::math

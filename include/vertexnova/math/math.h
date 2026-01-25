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
#include "vertexnova/math/core/constants.h"
#include "vertexnova/math/core/math_utils.h"
#include "color.h"
#include "transform_node.h"
#include "random.h"

// Interpolation and animation
#include "easing.h"
#include "curves.h"

// Procedural generation
#include "noise.h"

// Coordinate space utilities
#include "projection_utils.h"
#include "transform_utils.h"
#include "viewport.h"

// Geometry module includes
#include "geometry/geometry.h"

namespace vne::math {

// Type alias for backward compatibility
using Quaternion = Quatf;

}  // namespace vne::math

#pragma once
/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Author:    Ajeet Singh Yadav
 * Created:   January 2026
 *
 * Color utilities for VneMath examples
 * ----------------------------------------------------------------------
 */

#include "logging_guard.h"

#include <vertexnova/math/color.h>

#include <string>

namespace vne::math::examples {

/**
 * @brief Log a color with its name and RGBA components.
 * @param name Display name for the color
 * @param color The color to log
 */
inline void logColor(const std::string& name, const Color& color) {
    VNE_LOG_INFO << "  " << name << ": RGBA(" << color.r() << ", " << color.g() << ", " << color.b() << ", "
                 << color.a() << ")";
}

}  // namespace vne::math::examples

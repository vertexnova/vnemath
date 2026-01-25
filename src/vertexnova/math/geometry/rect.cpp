/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Author:    Ajeet Singh Yadav
 * Created:   January 2026
 *
 * Autodoc:   yes
 * ----------------------------------------------------------------------
 */

// Corresponding header
#include "vertexnova/math/geometry/rect.h"

namespace vne::math {

// Static factory methods
Rect Rect::fromCorners(const Vec2f& min_corner, const Vec2f& max_corner) noexcept {
    return {min_corner.x(), min_corner.y(), max_corner.x() - min_corner.x(), max_corner.y() - min_corner.y()};
}

Rect Rect::fromCenterAndHalfExtents(const Vec2f& center, const Vec2f& half_extents) noexcept {
    constexpr float kTwo = 2.0f;
    return {center.x() - half_extents.x(),
            center.y() - half_extents.y(),
            half_extents.x() * kTwo,
            half_extents.y() * kTwo};
}

Rect Rect::fromCenterAndSize(const Vec2f& center, const Vec2f& size) noexcept {
    constexpr float kHalf = 0.5f;
    return {center.x() - size.x() * kHalf, center.y() - size.y() * kHalf, size.x(), size.y()};
}

// Non-constexpr methods
bool Rect::areSame(const Rect& other, float epsilon) const noexcept {
    return approxEqual(x, other.x, epsilon) && approxEqual(y, other.y, epsilon)
           && approxEqual(width, other.width, epsilon) && approxEqual(height, other.height, epsilon);
}

}  // namespace vne::math

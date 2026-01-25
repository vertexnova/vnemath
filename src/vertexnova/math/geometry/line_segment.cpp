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
#include "vertexnova/math/geometry/line_segment.h"

namespace vne::math {

// Geometric properties
Vec3f LineSegment::normalizedDirection() const noexcept {
    return direction().normalized();
}

float LineSegment::length() const noexcept {
    return direction().length();
}

// Point queries
Vec3f LineSegment::closestPoint(const Vec3f& point) const noexcept {
    Vec3f dir = direction();
    float len_sq = dir.lengthSquared();

    if (isZero(len_sq)) {
        return start;  // Degenerate segment
    }

    float t = clamp((point - start).dot(dir) / len_sq, 0.0f, 1.0f);
    return getPoint(t);
}

Vec3f LineSegment::closestPoint(const Vec3f& point, float& out_t) const noexcept {
    Vec3f dir = direction();
    float len_sq = dir.lengthSquared();

    if (isZero(len_sq)) {
        out_t = 0.0f;
        return start;
    }

    out_t = clamp((point - start).dot(dir) / len_sq, 0.0f, 1.0f);
    return getPoint(out_t);
}

float LineSegment::distanceToPoint(const Vec3f& point) const noexcept {
    return (point - closestPoint(point)).length();
}

float LineSegment::squaredDistanceToPoint(const Vec3f& point) const noexcept {
    return (point - closestPoint(point)).lengthSquared();
}

// Validation
bool LineSegment::isDegenerate(float epsilon) const noexcept {
    return lengthSquared() < epsilon * epsilon;
}

bool LineSegment::isValid(float epsilon) const noexcept {
    return !isDegenerate(epsilon);
}

// Comparison
bool LineSegment::areSame(const LineSegment& other, float epsilon) const noexcept {
    return start.areSame(other.start, epsilon) && end.areSame(other.end, epsilon);
}

}  // namespace vne::math

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
#include "vertexnova/math/geometry/line.h"

namespace vne::math {

// Constructors
Line::Line(const Vec3f& point_on_line, const Vec3f& direction) noexcept
    : point(point_on_line)
    , dir(direction.normalized()) {}

Line::Line(const Ray& ray) noexcept
    : point(ray.origin())
    , dir(ray.direction()) {}

Line::Line(const LineSegment& segment) noexcept
    : point(segment.start)
    , dir(segment.normalizedDirection()) {}

// Static factory methods
Line Line::fromPoints(const Vec3f& p1, const Vec3f& p2) noexcept {
    return Line(p1, (p2 - p1).normalized());
}

// Point queries
Vec3f Line::closestPoint(const Vec3f& query_point) const noexcept {
    float t = (query_point - point).dot(dir);
    return getPoint(t);
}

Vec3f Line::closestPoint(const Vec3f& query_point, float& out_t) const noexcept {
    out_t = (query_point - point).dot(dir);
    return getPoint(out_t);
}

float Line::distanceToPoint(const Vec3f& query_point) const noexcept {
    return (query_point - closestPoint(query_point)).length();
}

float Line::squaredDistanceToPoint(const Vec3f& query_point) const noexcept {
    return (query_point - closestPoint(query_point)).lengthSquared();
}

// Line-Line queries
Vec3f Line::closestPointToLine(const Line& other, float& out_t1, float& out_t2) const noexcept {
    Vec3f w0 = point - other.point;
    float a = dir.dot(dir);  // Always 1 if normalized
    float b = dir.dot(other.dir);
    float c = other.dir.dot(other.dir);  // Always 1 if normalized
    float d = dir.dot(w0);
    float e = other.dir.dot(w0);

    float denom = a * c - b * b;

    if (isZero(denom)) {
        // Lines are parallel
        out_t1 = 0.0f;
        out_t2 = e / c;
    } else {
        out_t1 = (b * e - c * d) / denom;
        out_t2 = (a * e - b * d) / denom;
    }

    return getPoint(out_t1);
}

float Line::distanceToLine(const Line& other) const noexcept {
    float t1 = 0.0f;
    float t2 = 0.0f;
    Vec3f p1 = closestPointToLine(other, t1, t2);
    Vec3f p2 = other.getPoint(t2);
    return (p1 - p2).length();
}

// Geometric queries
bool Line::contains(const Vec3f& query_point, float epsilon) const noexcept {
    return squaredDistanceToPoint(query_point) < epsilon * epsilon;
}

bool Line::isParallel(const Line& other, float epsilon) const noexcept {
    return std::abs(std::abs(dir.dot(other.dir)) - 1.0f) < epsilon;
}

bool Line::isSame(const Line& other, float epsilon) const noexcept {
    if (!isParallel(other, epsilon)) {
        return false;
    }
    return contains(other.point, epsilon);
}

// Validation
bool Line::isValid(float epsilon) const noexcept {
    float len_sq = dir.lengthSquared();
    return std::abs(len_sq - 1.0f) < epsilon;
}

// Comparison
bool Line::areSame(const Line& other, float epsilon) const noexcept {
    return point.areSame(other.point, epsilon) && dir.areSame(other.dir, epsilon);
}

}  // namespace vne::math

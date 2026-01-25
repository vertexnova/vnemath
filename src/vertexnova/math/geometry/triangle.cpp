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
#include "vertexnova/math/geometry/triangle.h"

namespace vne::math {

namespace {
constexpr float kHalf = 0.5f;
constexpr float kOneThird = 1.0f / 3.0f;
}  // namespace

// Geometric properties
Vec3f Triangle::unitNormal() const noexcept {
    return normal().normalized();
}

float Triangle::area() const noexcept {
    return normal().length() * kHalf;
}

float Triangle::perimeter() const noexcept {
    return edge01().length() + edge12().length() + edge20().length();
}

// Barycentric coordinates
Vec3f Triangle::barycentric(const Vec3f& point) const noexcept {
    Vec3f e0 = edge01();
    Vec3f e1 = edge02();
    Vec3f e2 = point - v0;

    float d00 = e0.dot(e0);
    float d01 = e0.dot(e1);
    float d11 = e1.dot(e1);
    float d20 = e2.dot(e0);
    float d21 = e2.dot(e1);

    float denom = d00 * d11 - d01 * d01;
    if (isZero(denom)) {
        return Vec3f(kOneThird);  // Degenerate triangle
    }

    float inv_denom = 1.0f / denom;
    float v = (d11 * d20 - d01 * d21) * inv_denom;
    float w = (d00 * d21 - d01 * d20) * inv_denom;
    float u = 1.0f - v - w;

    return Vec3f(u, v, w);
}

// Containment tests
bool Triangle::contains(const Vec3f& point, float epsilon) const noexcept {
    Vec3f bary = barycentric(point);
    return bary.x() >= -epsilon && bary.y() >= -epsilon && bary.z() >= -epsilon;
}

bool Triangle::contains2D(const Vec2f& point, float epsilon) const noexcept {
    return contains(Vec3f(point.x(), point.y(), 0.0f), epsilon);
}

// Distance queries
Vec3f Triangle::closestPoint(const Vec3f& point) const noexcept {
    // Check if point projects inside triangle
    Vec3f bary = barycentric(point);

    // If inside, project onto plane
    if (bary.x() >= 0.0f && bary.y() >= 0.0f && bary.z() >= 0.0f) {
        return pointFromBarycentric(bary);
    }

    // Otherwise, find closest point on edges
    Vec3f closest = closestPointOnEdge(point, v0, v1);
    float best_dist_sq = (point - closest).lengthSquared();

    Vec3f candidate = closestPointOnEdge(point, v1, v2);
    float dist_sq = (point - candidate).lengthSquared();
    if (dist_sq < best_dist_sq) {
        closest = candidate;
        best_dist_sq = dist_sq;
    }

    candidate = closestPointOnEdge(point, v2, v0);
    dist_sq = (point - candidate).lengthSquared();
    if (dist_sq < best_dist_sq) {
        closest = candidate;
    }

    return closest;
}

float Triangle::distanceToPoint(const Vec3f& point) const noexcept {
    return (point - closestPoint(point)).length();
}

float Triangle::squaredDistanceToPoint(const Vec3f& point) const noexcept {
    return (point - closestPoint(point)).lengthSquared();
}

// Validation
bool Triangle::isDegenerate(float epsilon) const noexcept {
    return normal().lengthSquared() < epsilon * epsilon;
}

bool Triangle::isValid(float epsilon) const noexcept {
    return !isDegenerate(epsilon);
}

// Comparison
bool Triangle::areSame(const Triangle& other, float epsilon) const noexcept {
    return v0.areSame(other.v0, epsilon) && v1.areSame(other.v1, epsilon) && v2.areSame(other.v2, epsilon);
}

// Private helper
Vec3f Triangle::closestPointOnEdge(const Vec3f& point, const Vec3f& a, const Vec3f& b) noexcept {
    Vec3f ab = b - a;
    float t = clamp((point - a).dot(ab) / ab.dot(ab), 0.0f, 1.0f);
    return a + ab * t;
}

}  // namespace vne::math

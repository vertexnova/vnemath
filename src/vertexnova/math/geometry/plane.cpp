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

// Project includes
#include "vertexnova/math/geometry/plane.h"

#include "vertexnova/common/macros.h"
#include "vertexnova/math/core/math_utils.h"

namespace vne::math {

Plane::Plane(const Vec3f& normal, float d) noexcept
    : normal(normal)
    , d(d) {}

Plane::Plane(float normal_x, float normal_y, float normal_z, float d) noexcept
    : normal(normal_x, normal_y, normal_z)
    , d(d) {}

Plane::Plane(const Vec4f& normal_and_dist) noexcept
    : normal(normal_and_dist.x(), normal_and_dist.y(), normal_and_dist.z())
    , d(normal_and_dist.w()) {}

Plane::Plane(const Vec3f& p0, const Vec3f& p1, const Vec3f& p2) noexcept {
    *this = fromPoints(p0, p1, p2);
}

Plane::Plane(const Vec3f& point, const Vec3f& normal) noexcept {
    *this = fromPointNormal(point, normal);
}

Plane Plane::fromPoints(const Vec3f& p0, const Vec3f& p1, const Vec3f& p2) noexcept {
    // Calculate normal using cross product (counter-clockwise winding)
    Vec3f n = Vec3f::cross(p1 - p0, p2 - p0);
    return fromPointNormal(p0, n);
}

Plane Plane::fromPointNormal(const Vec3f& point, const Vec3f& normal) noexcept {
    Plane result;
    result.normal = normal.isNormalized() ? normal : Vec3f::normalized(normal);
    // Plane equation: n dot p + d = 0, therefore d = -(n dot p)
    result.d = -Vec3f::dot(result.normal, point);
    return result;
}

Plane Plane::normalized(const Plane& plane) noexcept {
    Plane out = plane;
    out.normalize();
    return out;
}

void Plane::flip() noexcept {
    normal = -normal;
    d = -d;
}

void Plane::normalize() noexcept {
    float len_sq = normal.lengthSquare();
    if (isZero(len_sq, kFloatEpsilon)) {
        return;
    }
    float one_over_length = 1.0f / sqrt(len_sq);
    normal *= one_over_length;
    d *= one_over_length;
}

void Plane::translate(const Vec3f& offset) noexcept {
    d -= normal.dot(offset);
}

void Plane::transform(const Mat3x3f& transform) noexcept {
    normal = transform.inverseTranspose() * normal;
    normalize();
}

void Plane::transform(const Mat4x4f& transform) noexcept {
    Vec4f plane_vector(normal, d);
    Vec4f transformed = transform.inverseTranspose() * plane_vector;
    normal = transformed.xyz();
    d = transformed.w();
    normalize();
}

float Plane::signedDistance(const Vec3f& point) const noexcept {
    return Vec3f::dot(normal, point) + d;
}

float Plane::distance(const Vec3f& point) const noexcept {
    return abs(signedDistance(point));
}

Vec3f Plane::closestPoint(const Vec3f& point) const noexcept {
    Vec3f plane_to_point = signedDistance(point) * normal;
    return point - plane_to_point;
}

Vec3f Plane::pointOnPlane() const noexcept {
    return normal * (-d);
}

bool Plane::isNormalized(float eps) const noexcept {
    return normal.isNormalized(eps);
}

bool Plane::isOnPositiveSide(const Vec3f& point, float eps) const noexcept {
    return signedDistance(point) >= eps;
}

bool Plane::isOnNegativeSide(const Vec3f& point, float eps) const noexcept {
    return signedDistance(point) < -eps;
}

bool Plane::isOnPlane(const Vec3f& point, float eps) const noexcept {
    return isZero(signedDistance(point), eps);
}

bool Plane::areOnSameSide(const Vec3f& point1, const Vec3f& point2, float eps) const noexcept {
    return signedDistance(point1) * signedDistance(point2) >= eps;
}

bool Plane::isInPositiveDirection(const Vec3f& dir, float eps) const noexcept {
    return Vec3f::dot(normal, dir) >= eps;
}

bool Plane::isInNegativeDirection(const Vec3f& dir, float eps) const noexcept {
    return Vec3f::dot(normal, dir) < -eps;
}

bool Plane::contains(const Vec3f& point, float eps) const noexcept {
    return isOnPlane(point, eps);
}

bool Plane::operator==(const Plane& plane) const noexcept {
    return normal == plane.normal && d == plane.d;
}

bool Plane::operator!=(const Plane& plane) const noexcept {
    return !(*this == plane);
}

std::ostream& operator<<(std::ostream& os, const Plane& plane) {
    return os << "Plane: [normal: " << plane.normal << ", d: " << plane.d << "]";
}

}  // namespace vne::math

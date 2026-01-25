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
#include "vertexnova/math/geometry/obb.h"

#include "vertexnova/math/core/math_utils.h"
#include "vertexnova/math/geometry/aabb.h"

namespace vne::math {

namespace {
constexpr float kHalf = 0.5f;
constexpr float kSurfaceAreaMultiplier = 2.0f;
constexpr uint32_t kCornerCount = 8;
}  // namespace

// Constructors
Obb::Obb() noexcept = default;

Obb::Obb(const Vec3f& center, const Vec3f& half_extents, const Quatf& orientation) noexcept
    : center_(center)
    , half_extents_(half_extents)
    , orientation_(orientation) {}

Obb::Obb(const Vec3f& center, const Vec3f& half_extents, const Mat3f& rotation) noexcept
    : center_(center)
    , half_extents_(half_extents)
    , orientation_(Quatf::fromMatrix(rotation)) {}

// Static factory methods
Obb Obb::fromAabb(const Aabb& aabb) noexcept {
    return {aabb.center(), aabb.halfExtents(), Quatf::identity()};
}

Obb Obb::fromMinMax(const Vec3f& min, const Vec3f& max) noexcept {
    Vec3f center = (min + max) * kHalf;
    Vec3f half_extents = (max - min) * kHalf;
    return {center, half_extents, Quatf::identity()};
}

// Accessors
void Obb::setCenter(const Vec3f& center) noexcept {
    center_ = center;
}

const Vec3f& Obb::center() const noexcept {
    return center_;
}

void Obb::setHalfExtents(const Vec3f& half_extents) noexcept {
    half_extents_ = half_extents;
}

const Vec3f& Obb::halfExtents() const noexcept {
    return half_extents_;
}

void Obb::setOrientation(const Quatf& orientation) noexcept {
    orientation_ = orientation;
}

const Quatf& Obb::orientation() const noexcept {
    return orientation_;
}

Mat3f Obb::rotationMatrix() const noexcept {
    return orientation_.toMatrix3();
}

// Local axes
Vec3f Obb::axisX() const noexcept {
    return orientation_.rotate(Vec3f::xAxis());
}

Vec3f Obb::axisY() const noexcept {
    return orientation_.rotate(Vec3f::yAxis());
}

Vec3f Obb::axisZ() const noexcept {
    return orientation_.rotate(Vec3f::zAxis());
}

Vec3f Obb::axis(uint32_t index) const noexcept {
    switch (index) {
        case 0:
            return axisX();
        case 1:
            return axisY();
        default:
            return axisZ();
    }
}

// Computed properties
Vec3f Obb::size() const noexcept {
    return half_extents_ * kSurfaceAreaMultiplier;  // 2.0f
}

float Obb::volume() const noexcept {
    Vec3f s = size();
    return s.x() * s.y() * s.z();
}

float Obb::surfaceArea() const noexcept {
    Vec3f s = size();
    return kSurfaceAreaMultiplier * (s.x() * s.y() + s.y() * s.z() + s.z() * s.x());
}

void Obb::getCorners(Vec3f corners[8]) const noexcept {
    Vec3f ax = axisX() * half_extents_.x();
    Vec3f ay = axisY() * half_extents_.y();
    Vec3f az = axisZ() * half_extents_.z();

    corners[0] = center_ - ax - ay - az;
    corners[1] = center_ + ax - ay - az;
    corners[2] = center_ - ax + ay - az;
    corners[3] = center_ + ax + ay - az;
    corners[4] = center_ - ax - ay + az;
    corners[5] = center_ + ax - ay + az;
    corners[6] = center_ - ax + ay + az;
    corners[7] = center_ + ax + ay + az;
}

Vec3f Obb::corner(uint32_t index) const noexcept {
    Vec3f ax = axisX() * half_extents_.x();
    Vec3f ay = axisY() * half_extents_.y();
    Vec3f az = axisZ() * half_extents_.z();

    Vec3f result = center_;
    result += (index & 1) ? ax : -ax;
    result += (index & 2) ? ay : -ay;
    result += (index & 4) ? az : -az;
    return result;
}

Aabb Obb::getAabb() const noexcept {
    Vec3f corners[kCornerCount];
    getCorners(corners);

    Aabb result;
    for (uint32_t i = 0; i < kCornerCount; ++i) {
        result.expand(corners[i]);
    }
    return result;
}

// Modification methods
void Obb::translate(const Vec3f& offset) noexcept {
    center_ += offset;
}

void Obb::rotate(const Quatf& rotation) noexcept {
    center_ = rotation.rotate(center_);
    orientation_ = rotation * orientation_;
}

void Obb::scale(float factor) noexcept {
    half_extents_ *= factor;
}

void Obb::scale(const Vec3f& factors) noexcept {
    half_extents_.x() *= factors.x();
    half_extents_.y() *= factors.y();
    half_extents_.z() *= factors.z();
}

void Obb::transform(const Mat4f& matrix) noexcept {
    // Extract translation
    Vec4f pos = matrix * Vec4f(center_, 1.0f);
    center_ = Vec3f(pos.x(), pos.y(), pos.z());

    // Extract rotation (assuming orthogonal matrix, no shear)
    Vec3f col0(matrix.getColumn(0).x(), matrix.getColumn(0).y(), matrix.getColumn(0).z());
    Vec3f col1(matrix.getColumn(1).x(), matrix.getColumn(1).y(), matrix.getColumn(1).z());
    Vec3f col2(matrix.getColumn(2).x(), matrix.getColumn(2).y(), matrix.getColumn(2).z());

    // Extract scale from rotation matrix
    Vec3f scale_factors(col0.length(), col1.length(), col2.length());

    // Normalize columns
    col0 = col0 / scale_factors.x();
    col1 = col1 / scale_factors.y();
    col2 = col2 / scale_factors.z();

    Mat3f rot(col0, col1, col2);
    orientation_ = Quatf::fromMatrix(rot);
    half_extents_.x() *= scale_factors.x();
    half_extents_.y() *= scale_factors.y();
    half_extents_.z() *= scale_factors.z();
}

// Query methods
bool Obb::isValid() const noexcept {
    return half_extents_.x() > 0.0f && half_extents_.y() > 0.0f && half_extents_.z() > 0.0f;
}

bool Obb::contains(const Vec3f& point) const noexcept {
    // Transform point to local space
    Vec3f local = orientation_.inverse().rotate(point - center_);

    return std::abs(local.x()) <= half_extents_.x() && std::abs(local.y()) <= half_extents_.y()
           && std::abs(local.z()) <= half_extents_.z();
}

Vec3f Obb::closestPoint(const Vec3f& point) const noexcept {
    // Transform point to local space
    Vec3f local = orientation_.inverse().rotate(point - center_);

    // Clamp to box extents
    local.x() = clamp(local.x(), -half_extents_.x(), half_extents_.x());
    local.y() = clamp(local.y(), -half_extents_.y(), half_extents_.y());
    local.z() = clamp(local.z(), -half_extents_.z(), half_extents_.z());

    // Transform back to world space
    return center_ + orientation_.rotate(local);
}

float Obb::squaredDistanceToPoint(const Vec3f& point) const noexcept {
    return (point - closestPoint(point)).lengthSquared();
}

float Obb::distanceToPoint(const Vec3f& point) const noexcept {
    return (point - closestPoint(point)).length();
}

bool Obb::intersects(const Obb& other) const noexcept {
    // Separating Axis Theorem (SAT) for OBB-OBB intersection
    // Test 15 potential separating axes:
    // - 3 axes from this OBB
    // - 3 axes from other OBB
    // - 9 cross products of axes from both

    Vec3f axes_a[3] = {axisX(), axisY(), axisZ()};
    Vec3f axes_b[3] = {other.axisX(), other.axisY(), other.axisZ()};

    Vec3f t = other.center_ - center_;

    // For each axis, compute the projection of the separation vector
    // and compare to the sum of projected half-extents

    auto testAxis = [&](const Vec3f& axis) -> bool {
        if (axis.lengthSquared() < kFloatEpsilon) {
            return true;  // Degenerate axis, skip
        }

        Vec3f normalized_axis = axis.normalized();

        // Project half-extents of both boxes onto axis
        float proj_a = std::abs(axes_a[0].dot(normalized_axis)) * half_extents_.x()
                       + std::abs(axes_a[1].dot(normalized_axis)) * half_extents_.y()
                       + std::abs(axes_a[2].dot(normalized_axis)) * half_extents_.z();

        float proj_b = std::abs(axes_b[0].dot(normalized_axis)) * other.half_extents_.x()
                       + std::abs(axes_b[1].dot(normalized_axis)) * other.half_extents_.y()
                       + std::abs(axes_b[2].dot(normalized_axis)) * other.half_extents_.z();

        float dist = std::abs(t.dot(normalized_axis));

        return dist <= proj_a + proj_b;
    };

    // Test axes from this OBB
    for (const auto& axis : axes_a) {
        if (!testAxis(axis))
            return false;
    }

    // Test axes from other OBB
    for (const auto& axis : axes_b) {
        if (!testAxis(axis))
            return false;
    }

    // Test cross products
    for (const auto& axis_a : axes_a) {
        for (const auto& axis_b : axes_b) {
            if (!testAxis(axis_a.cross(axis_b)))
                return false;
        }
    }

    return true;
}

bool Obb::intersects(const Aabb& aabb) const noexcept {
    Obb aabb_obb = fromAabb(aabb);
    return intersects(aabb_obb);
}

// Comparison operators
bool Obb::operator==(const Obb& other) const noexcept {
    return center_ == other.center_ && half_extents_ == other.half_extents_ && orientation_ == other.orientation_;
}

bool Obb::operator!=(const Obb& other) const noexcept {
    return !(*this == other);
}

bool Obb::areSame(const Obb& other, float epsilon) const noexcept {
    return center_.areSame(other.center_, epsilon) && half_extents_.areSame(other.half_extents_, epsilon)
           && orientation_.approxEquals(other.orientation_, epsilon);
}

std::ostream& operator<<(std::ostream& os, const Obb& obb) {
    return os << "Obb: [center: " << obb.center() << ", half_extents: " << obb.halfExtents()
              << ", orientation: " << obb.orientation() << "]";
}

}  // namespace vne::math

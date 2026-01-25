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
#include "vertexnova/math/geometry/aabb.h"

#include "vertexnova/math/core/math_utils.h"

namespace vne::math {

namespace {
constexpr float kHalf = 0.5f;
constexpr float kSurfaceAreaMultiplier = 2.0f;
}  // namespace

Aabb::Aabb() noexcept
    : min_(kFloatMax, kFloatMax, kFloatMax)
    , max_(-kFloatMax, -kFloatMax, -kFloatMax) {}

Aabb::Aabb(const Vec3f& min, const Vec3f& max) noexcept
    : min_(min)
    , max_(max) {}

Aabb Aabb::fromCenterAndHalfExtents(const Vec3f& center, const Vec3f& half_extents) noexcept {
    return {center - half_extents, center + half_extents};
}

Aabb Aabb::fromCenterAndSize(const Vec3f& center, const Vec3f& size) noexcept {
    Vec3f half = size * kHalf;
    return {center - half, center + half};
}

void Aabb::setMin(const Vec3f& min) noexcept {
    min_ = min;
}

const Vec3f& Aabb::min() const noexcept {
    return min_;
}

void Aabb::setMax(const Vec3f& max) noexcept {
    max_ = max;
}

const Vec3f& Aabb::max() const noexcept {
    return max_;
}

Vec3f Aabb::center() const noexcept {
    return (min_ + max_) * kHalf;
}

Vec3f Aabb::size() const noexcept {
    return max_ - min_;
}

Vec3f Aabb::halfExtents() const noexcept {
    return (max_ - min_) * kHalf;
}

float Aabb::volume() const noexcept {
    Vec3f s = size();
    return s.x() * s.y() * s.z();
}

float Aabb::surfaceArea() const noexcept {
    Vec3f s = size();
    return kSurfaceAreaMultiplier * (s.x() * s.y() + s.y() * s.z() + s.z() * s.x());
}

Vec3f Aabb::corner(uint32_t index) const noexcept {
    return {(index & 1) ? max_.x() : min_.x(), (index & 2) ? max_.y() : min_.y(), (index & 4) ? max_.z() : min_.z()};
}

void Aabb::expand(const Vec3f& point) noexcept {
    min_.x() = vne::math::min(min_.x(), point.x());
    min_.y() = vne::math::min(min_.y(), point.y());
    min_.z() = vne::math::min(min_.z(), point.z());
    max_.x() = vne::math::max(max_.x(), point.x());
    max_.y() = vne::math::max(max_.y(), point.y());
    max_.z() = vne::math::max(max_.z(), point.z());
}

void Aabb::expand(const Aabb& other) noexcept {
    expand(other.min_);
    expand(other.max_);
}

void Aabb::grow(float amount) noexcept {
    min_ -= Vec3f(amount);
    max_ += Vec3f(amount);
}

void Aabb::grow(const Vec3f& amount) noexcept {
    min_ -= amount;
    max_ += amount;
}

void Aabb::translate(const Vec3f& offset) noexcept {
    min_ += offset;
    max_ += offset;
}

void Aabb::reset() noexcept {
    min_ = Vec3f(kFloatMax, kFloatMax, kFloatMax);
    max_ = Vec3f(-kFloatMax, -kFloatMax, -kFloatMax);
}

bool Aabb::isValid() const noexcept {
    return min_.x() <= max_.x() && min_.y() <= max_.y() && min_.z() <= max_.z();
}

bool Aabb::contains(const Vec3f& point) const noexcept {
    return point.x() >= min_.x() && point.x() <= max_.x() && point.y() >= min_.y() && point.y() <= max_.y()
           && point.z() >= min_.z() && point.z() <= max_.z();
}

bool Aabb::contains(const Aabb& other) const noexcept {
    return other.min_.x() >= min_.x() && other.max_.x() <= max_.x() && other.min_.y() >= min_.y()
           && other.max_.y() <= max_.y() && other.min_.z() >= min_.z() && other.max_.z() <= max_.z();
}

bool Aabb::intersects(const Aabb& other) const noexcept {
    return min_.x() < other.max_.x() && max_.x() > other.min_.x() && min_.y() < other.max_.y()
           && max_.y() > other.min_.y() && min_.z() < other.max_.z() && max_.z() > other.min_.z();
}

Vec3f Aabb::closestPoint(const Vec3f& point) const noexcept {
    return {clamp(point.x(), min_.x(), max_.x()),
            clamp(point.y(), min_.y(), max_.y()),
            clamp(point.z(), min_.z(), max_.z())};
}

float Aabb::squaredDistanceToPoint(const Vec3f& point) const noexcept {
    float sq_dist = 0.0f;

    if (point.x() < min_.x()) {
        float d = min_.x() - point.x();
        sq_dist += d * d;
    } else if (point.x() > max_.x()) {
        float d = point.x() - max_.x();
        sq_dist += d * d;
    }

    if (point.y() < min_.y()) {
        float d = min_.y() - point.y();
        sq_dist += d * d;
    } else if (point.y() > max_.y()) {
        float d = point.y() - max_.y();
        sq_dist += d * d;
    }

    if (point.z() < min_.z()) {
        float d = min_.z() - point.z();
        sq_dist += d * d;
    } else if (point.z() > max_.z()) {
        float d = point.z() - max_.z();
        sq_dist += d * d;
    }

    return sq_dist;
}

bool Aabb::operator==(const Aabb& other) const noexcept {
    return min_ == other.min_ && max_ == other.max_;
}

bool Aabb::operator!=(const Aabb& other) const noexcept {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Aabb& aabb) {
    return os << "Aabb: [min: " << aabb.min() << ", max: " << aabb.max() << "]";
}

}  // namespace vne::math

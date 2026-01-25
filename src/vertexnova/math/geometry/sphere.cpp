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

// Project includes
#include "vertexnova/math/geometry/sphere.h"

#include "vertexnova/math/math_utils.h"

namespace vne::math {

Sphere::Sphere() noexcept
    : center_(Vec3f::zero())
    , radius_(-1.0f) {}

Sphere::Sphere(const Vec3f& center, float radius) noexcept
    : center_(center)
    , radius_(radius) {}

void Sphere::setCenter(const Vec3f& center) noexcept {
    center_ = center;
}

const Vec3f& Sphere::center() const noexcept {
    return center_;
}

void Sphere::setRadius(float radius) noexcept {
    radius_ = radius;
}

float Sphere::radius() const noexcept {
    return radius_;
}

float Sphere::diameter() const noexcept {
    return radius_ * 2.0f;
}

float Sphere::volume() const noexcept {
    // V = 4/3 * pi * r^3
    return (4.0f / 3.0f) * kPi * radius_ * radius_ * radius_;
}

float Sphere::surfaceArea() const noexcept {
    // A = 4 * pi * r^2
    return 4.0f * kPi * radius_ * radius_;
}

void Sphere::expand(const Vec3f& point) noexcept {
    if (!isValid()) {
        center_ = point;
        radius_ = 0.0f;
        return;
    }

    Vec3f delta = point - center_;
    float dist = delta.length();

    if (dist > radius_) {
        // Expand sphere to include point
        float new_radius = (radius_ + dist) * 0.5f;
        float move_dist = new_radius - radius_;
        if (dist > kFloatEpsilon) {
            center_ += (delta / dist) * move_dist;
        }
        radius_ = new_radius;
    }
}

void Sphere::expand(const Sphere& other) noexcept {
    if (!other.isValid()) {
        return;
    }

    if (!isValid()) {
        *this = other;
        return;
    }

    Vec3f delta = other.center_ - center_;
    float dist = delta.length();
    float total_radius = dist + other.radius_;

    if (total_radius > radius_) {
        float new_radius = (radius_ + total_radius) * 0.5f;
        if (dist > kFloatEpsilon) {
            float move_dist = new_radius - radius_;
            center_ += (delta / dist) * move_dist;
        }
        radius_ = new_radius;
    }
}

void Sphere::grow(float amount) noexcept {
    radius_ += amount;
}

void Sphere::translate(const Vec3f& offset) noexcept {
    center_ += offset;
}

bool Sphere::isValid() const noexcept {
    return radius_ >= 0.0f;
}

bool Sphere::contains(const Vec3f& point) const noexcept {
    float dist_sq = (point - center_).lengthSquare();
    return dist_sq <= radius_ * radius_;
}

bool Sphere::contains(const Sphere& other) const noexcept {
    float dist = (other.center_ - center_).length();
    return dist + other.radius_ <= radius_;
}

bool Sphere::intersects(const Sphere& other) const noexcept {
    float dist_sq = (other.center_ - center_).lengthSquare();
    float sum_radii = radius_ + other.radius_;
    return dist_sq <= sum_radii * sum_radii;
}

Vec3f Sphere::closestPoint(const Vec3f& point) const noexcept {
    Vec3f delta = point - center_;
    float dist = delta.length();

    if (dist < kFloatEpsilon) {
        // Point is at center, return any point on surface
        return center_ + Vec3f(radius_, 0.0f, 0.0f);
    }

    return center_ + (delta / dist) * radius_;
}

float Sphere::signedDistanceToPoint(const Vec3f& point) const noexcept {
    return (point - center_).length() - radius_;
}

float Sphere::distanceToPoint(const Vec3f& point) const noexcept {
    return max(0.0f, signedDistanceToPoint(point));
}

bool Sphere::operator==(const Sphere& other) const noexcept {
    return center_ == other.center_ && radius_ == other.radius_;
}

bool Sphere::operator!=(const Sphere& other) const noexcept {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Sphere& sphere) {
    return os << "Sphere: [center: " << sphere.center() << ", radius: " << sphere.radius() << "]";
}

}  // namespace vne::math

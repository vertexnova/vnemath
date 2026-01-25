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
#include "vertexnova/math/geometry/ray.h"

#include "vertexnova/math/math_utils.h"

namespace vne::math {

Ray::Ray() noexcept
    : origin_(Vec3f::zero())
    , direction_(Vec3f::zAxis()) {}

Ray::Ray(const Vec3f& origin, const Vec3f& direction) noexcept
    : origin_(origin)
    , direction_(direction.isNormalized() ? direction : Vec3f::normalized(direction)) {}

Vec3f Ray::getPoint(float distance) const noexcept {
    return origin_ + direction_ * distance;
}

Vec3f Ray::closestPoint(const Vec3f& point) const noexcept {
    float distance = 0.0f;
    return closestPoint(point, distance);
}

Vec3f Ray::closestPoint(const Vec3f& point, float& distance) const noexcept {
    distance = max(0.0f, Vec3f::dot(point - origin_, direction_));
    return getPoint(distance);
}

float Ray::distanceToPoint(const Vec3f& point) const noexcept {
    Vec3f closest = closestPoint(point);
    return (point - closest).length();
}

bool Ray::areSame(const Ray& other, float eps) const noexcept {
    return origin_.areSame(other.origin_, eps) && direction_.areSame(other.direction_, eps);
}

void Ray::setOrigin(const Vec3f& origin) noexcept {
    origin_ = origin;
}

const Vec3f& Ray::origin() const noexcept {
    return origin_;
}

void Ray::setDirection(const Vec3f& direction) noexcept {
    if (direction.isNormalized()) {
        direction_ = direction;
    } else {
        direction_ = Vec3f::normalized(direction);
    }
}

const Vec3f& Ray::direction() const noexcept {
    return direction_;
}

std::ostream& operator<<(std::ostream& os, const Ray& ray) {
    return os << "Ray: [origin: " << ray.origin() << ", direction: " << ray.direction() << "]";
}

}  // namespace vne::math

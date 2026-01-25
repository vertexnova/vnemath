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
#include "vertexnova/math/geometry/capsule.h"

#include "vertexnova/math/core/math_utils.h"
#include "vertexnova/math/geometry/aabb.h"
#include "vertexnova/math/geometry/sphere.h"

namespace vne::math {

namespace {
constexpr float kHalf = 0.5f;
constexpr float kTwo = 2.0f;
constexpr float kFour = 4.0f;
constexpr float kVolumeFactor = 4.0f / 3.0f;  // 4/3 for sphere volume
}  // namespace

// Constructors
Capsule::Capsule() noexcept = default;

Capsule::Capsule(const Vec3f& start, const Vec3f& end, float radius) noexcept
    : start_(start)
    , end_(end)
    , radius_(radius) {}

Capsule::Capsule(const LineSegment& segment, float radius) noexcept
    : start_(segment.start)
    , end_(segment.end)
    , radius_(radius) {}

// Static factory methods
Capsule Capsule::fromCenterHeightRadius(const Vec3f& center, float height, float radius) noexcept {
    float segment_length = height - kTwo * radius;
    if (segment_length < 0.0f) {
        segment_length = 0.0f;
    }
    float half_length = segment_length * kHalf;
    return {center - Vec3f(0.0f, half_length, 0.0f), center + Vec3f(0.0f, half_length, 0.0f), radius};
}

Capsule Capsule::fromCenterDirectionLengthRadius(const Vec3f& center,
                                                 const Vec3f& direction,
                                                 float segment_length,
                                                 float radius) noexcept {
    Vec3f half_dir = direction.normalized() * (segment_length * kHalf);
    return {center - half_dir, center + half_dir, radius};
}

// Accessors
void Capsule::setStart(const Vec3f& start) noexcept {
    start_ = start;
}

const Vec3f& Capsule::start() const noexcept {
    return start_;
}

void Capsule::setEnd(const Vec3f& end) noexcept {
    end_ = end;
}

const Vec3f& Capsule::end() const noexcept {
    return end_;
}

void Capsule::setRadius(float radius) noexcept {
    radius_ = radius;
}

float Capsule::radius() const noexcept {
    return radius_;
}

LineSegment Capsule::segment() const noexcept {
    return {start_, end_};
}

// Computed properties
Vec3f Capsule::center() const noexcept {
    return (start_ + end_) * kHalf;
}

Vec3f Capsule::direction() const noexcept {
    return end_ - start_;
}

Vec3f Capsule::normalizedDirection() const noexcept {
    return direction().normalized();
}

float Capsule::segmentLength() const noexcept {
    return direction().length();
}

float Capsule::height() const noexcept {
    return segmentLength() + kTwo * radius_;
}

float Capsule::diameter() const noexcept {
    return kTwo * radius_;
}

float Capsule::volume() const noexcept {
    // Volume = cylinder + sphere
    // Cylinder: π * r² * h
    // Sphere: (4/3) * π * r³
    float r2 = radius_ * radius_;
    float cylinder_volume = kPi * r2 * segmentLength();
    float sphere_volume = kVolumeFactor * kPi * r2 * radius_;
    return cylinder_volume + sphere_volume;
}

float Capsule::surfaceArea() const noexcept {
    // Surface = cylinder lateral + sphere
    // Cylinder lateral: 2 * π * r * h
    // Sphere: 4 * π * r²
    float cylinder_area = kTwo * kPi * radius_ * segmentLength();
    float sphere_area = kFour * kPi * radius_ * radius_;
    return cylinder_area + sphere_area;
}

Aabb Capsule::getAabb() const noexcept {
    Vec3f min_point(vne::math::min(start_.x(), end_.x()) - radius_,
                    vne::math::min(start_.y(), end_.y()) - radius_,
                    vne::math::min(start_.z(), end_.z()) - radius_);
    Vec3f max_point(vne::math::max(start_.x(), end_.x()) + radius_,
                    vne::math::max(start_.y(), end_.y()) + radius_,
                    vne::math::max(start_.z(), end_.z()) + radius_);
    return {min_point, max_point};
}

// Modification methods
void Capsule::translate(const Vec3f& offset) noexcept {
    start_ += offset;
    end_ += offset;
}

void Capsule::grow(float amount) noexcept {
    radius_ += amount;
}

// Query methods
bool Capsule::isValid() const noexcept {
    return radius_ > 0.0f;
}

bool Capsule::isDegenerate(float epsilon) const noexcept {
    return direction().lengthSquared() < epsilon * epsilon;
}

bool Capsule::contains(const Vec3f& point) const noexcept {
    return signedDistanceToPoint(point) <= 0.0f;
}

Vec3f Capsule::closestPointOnSegment(const Vec3f& point) const noexcept {
    return segment().closestPoint(point);
}

Vec3f Capsule::closestPoint(const Vec3f& point) const noexcept {
    Vec3f closest_on_segment = closestPointOnSegment(point);
    Vec3f to_point = point - closest_on_segment;
    float dist = to_point.length();

    if (dist < kFloatEpsilon) {
        // Point is on the segment, return any point on surface
        // Use a perpendicular direction
        Vec3f dir = direction();
        Vec3f perp = dir.cross(Vec3f::up());
        if (perp.lengthSquared() < kFloatEpsilon) {
            perp = dir.cross(Vec3f::right());
        }
        return closest_on_segment + perp.normalized() * radius_;
    }

    return closest_on_segment + (to_point / dist) * radius_;
}

float Capsule::squaredDistanceToPoint(const Vec3f& point) const noexcept {
    float signed_dist = signedDistanceToPoint(point);
    if (signed_dist <= 0.0f) {
        return 0.0f;  // Inside
    }
    return signed_dist * signed_dist;
}

float Capsule::distanceToPoint(const Vec3f& point) const noexcept {
    float signed_dist = signedDistanceToPoint(point);
    return signed_dist > 0.0f ? signed_dist : 0.0f;
}

float Capsule::signedDistanceToPoint(const Vec3f& point) const noexcept {
    Vec3f closest_on_segment = closestPointOnSegment(point);
    return (point - closest_on_segment).length() - radius_;
}

bool Capsule::intersects(const Capsule& other) const noexcept {
    // Two capsules intersect if the distance between their segments
    // is less than the sum of their radii
    LineSegment seg1 = segment();
    LineSegment seg2 = other.segment();

    // Find closest points between segments
    Vec3f dir1 = seg1.direction();
    Vec3f dir2 = seg2.direction();
    Vec3f w = seg1.start - seg2.start;

    float a = dir1.dot(dir1);
    float b = dir1.dot(dir2);
    float c = dir2.dot(dir2);
    float d = dir1.dot(w);
    float e = dir2.dot(w);

    float denom = a * c - b * b;
    float s = 0.0f;
    float t = 0.0f;

    if (isZero(denom)) {
        // Parallel segments
        s = 0.0f;
        t = (b > c ? d / b : e / c);
    } else {
        s = (b * e - c * d) / denom;
        t = (a * e - b * d) / denom;
    }

    s = clamp(s, 0.0f, 1.0f);
    t = clamp(t, 0.0f, 1.0f);

    Vec3f closest1 = seg1.getPoint(s);
    Vec3f closest2 = seg2.getPoint(t);

    float dist_sq = (closest1 - closest2).lengthSquared();
    float sum_radii = radius_ + other.radius_;

    return dist_sq <= sum_radii * sum_radii;
}

bool Capsule::intersects(const Sphere& sphere) const noexcept {
    float dist_to_segment = segment().distanceToPoint(sphere.center());
    float sum_radii = radius_ + sphere.radius();
    return dist_to_segment <= sum_radii;
}

// Comparison operators
bool Capsule::operator==(const Capsule& other) const noexcept {
    return start_ == other.start_ && end_ == other.end_ && radius_ == other.radius_;
}

bool Capsule::operator!=(const Capsule& other) const noexcept {
    return !(*this == other);
}

bool Capsule::areSame(const Capsule& other, float epsilon) const noexcept {
    return start_.areSame(other.start_, epsilon) && end_.areSame(other.end_, epsilon)
           && approxEqual(radius_, other.radius_, epsilon);
}

std::ostream& operator<<(std::ostream& os, const Capsule& capsule) {
    return os << "Capsule: [start: " << capsule.start() << ", end: " << capsule.end()
              << ", radius: " << capsule.radius() << "]";
}

}  // namespace vne::math

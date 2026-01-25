/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Line segment primitive - finite line with start and end points.
 * ----------------------------------------------------------------------
 */

#pragma once

#include "../core/types.h"
#include "../core/vec.h"

namespace vne::math {

/**
 * @class LineSegment
 * @brief A finite line defined by start and end points in 3D space.
 *
 * Using the parametric equation: P(t) = start + t * (end - start)
 * where t is clamped to [0, 1] for points on the segment.
 *
 * Common uses:
 * - Edge representation in meshes
 * - Capsule definition (LineSegment + radius)
 * - Collision detection
 * - Path segments
 */
class LineSegment {
   public:
    Vec3f start{Vec3f::zero()};  ///< Start point of the segment
    Vec3f end{Vec3f::zero()};    ///< End point of the segment

    // ========================================================================
    // Constructors
    // ========================================================================

    /**
     * @brief Default constructor. Creates a zero-length segment at origin.
     */
    constexpr LineSegment() noexcept = default;

    /**
     * @brief Constructs a line segment from start and end points.
     */
    constexpr LineSegment(const Vec3f& start_point, const Vec3f& end_point) noexcept
        : start(start_point)
        , end(end_point) {}

    // ========================================================================
    // Geometric Properties
    // ========================================================================

    /**
     * @brief Returns the direction vector (unnormalized).
     */
    [[nodiscard]] constexpr Vec3f direction() const noexcept { return end - start; }

    /**
     * @brief Returns the normalized direction vector.
     */
    [[nodiscard]] Vec3f normalizedDirection() const noexcept { return direction().normalized(); }

    /**
     * @brief Returns the length of the segment.
     */
    [[nodiscard]] float length() const noexcept { return direction().length(); }

    /**
     * @brief Returns the squared length (faster, avoids sqrt).
     */
    [[nodiscard]] constexpr float lengthSquared() const noexcept { return direction().lengthSquared(); }

    /**
     * @brief Returns the midpoint of the segment.
     */
    [[nodiscard]] constexpr Vec3f midpoint() const noexcept { return (start + end) * 0.5f; }

    /**
     * @brief Returns the center (alias for midpoint).
     */
    [[nodiscard]] constexpr Vec3f center() const noexcept { return midpoint(); }

    // ========================================================================
    // Point Queries
    // ========================================================================

    /**
     * @brief Gets a point along the segment at parameter t.
     *
     * @param t Parameter in [0,1] for points on segment, can be outside
     * @return Point at start + t * (end - start)
     */
    [[nodiscard]] constexpr Vec3f getPoint(float t) const noexcept { return start + direction() * t; }

    /**
     * @brief Finds the closest point on this segment to a given point.
     *
     * @param point The query point
     * @return Closest point on the segment
     */
    [[nodiscard]] Vec3f closestPoint(const Vec3f& point) const noexcept {
        Vec3f dir = direction();
        float len_sq = dir.lengthSquared();

        if (isZero(len_sq)) {
            return start;  // Degenerate segment
        }

        float t = clamp((point - start).dot(dir) / len_sq, 0.0f, 1.0f);
        return getPoint(t);
    }

    /**
     * @brief Finds the closest point and returns the parameter t.
     *
     * @param point The query point
     * @param out_t Output parameter t in [0,1]
     * @return Closest point on the segment
     */
    [[nodiscard]] Vec3f closestPoint(const Vec3f& point, float& out_t) const noexcept {
        Vec3f dir = direction();
        float len_sq = dir.lengthSquared();

        if (isZero(len_sq)) {
            out_t = 0.0f;
            return start;
        }

        out_t = clamp((point - start).dot(dir) / len_sq, 0.0f, 1.0f);
        return getPoint(out_t);
    }

    /**
     * @brief Computes the distance from a point to this segment.
     */
    [[nodiscard]] float distanceToPoint(const Vec3f& point) const noexcept {
        return (point - closestPoint(point)).length();
    }

    /**
     * @brief Computes the squared distance from a point to this segment.
     */
    [[nodiscard]] float squaredDistanceToPoint(const Vec3f& point) const noexcept {
        return (point - closestPoint(point)).lengthSquared();
    }

    // ========================================================================
    // Validation
    // ========================================================================

    /**
     * @brief Checks if the segment is degenerate (zero length).
     */
    [[nodiscard]] bool isDegenerate(float epsilon = kEpsilon<float>) const noexcept {
        return lengthSquared() < epsilon * epsilon;
    }

    /**
     * @brief Checks if the segment is valid (non-zero length).
     */
    [[nodiscard]] bool isValid(float epsilon = kEpsilon<float>) const noexcept { return !isDegenerate(epsilon); }

    // ========================================================================
    // Transformations
    // ========================================================================

    /**
     * @brief Returns a reversed segment (start and end swapped).
     */
    [[nodiscard]] constexpr LineSegment reversed() const noexcept { return LineSegment(end, start); }

    /**
     * @brief Translates the segment by an offset.
     */
    [[nodiscard]] constexpr LineSegment translated(const Vec3f& offset) const noexcept {
        return LineSegment(start + offset, end + offset);
    }

    // ========================================================================
    // Comparison
    // ========================================================================

    [[nodiscard]] constexpr bool operator==(const LineSegment& other) const noexcept = default;

    [[nodiscard]] bool areSame(const LineSegment& other, float epsilon = kEpsilon<float>) const noexcept {
        return start.areSame(other.start, epsilon) && end.areSame(other.end, epsilon);
    }
};

}  // namespace vne::math

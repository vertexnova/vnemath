/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Line primitive - infinite line defined by point and direction.
 * ----------------------------------------------------------------------
 */

#pragma once

#include "../core/types.h"
#include "../core/vec.h"
#include "line_segment.h"
#include "ray.h"

namespace vne::math {

/**
 * @class Line
 * @brief An infinite line defined by a point and direction in 3D space.
 *
 * Using the parametric equation: P(t) = point + t * direction
 * where t can be any real number (extends infinitely in both directions).
 *
 * Common uses:
 * - Intersection tests
 * - Closest point queries
 * - Geometric constructions
 */
class Line {
   public:
    Vec3f point{Vec3f::zero()};  ///< A point on the line
    Vec3f dir{Vec3f::zAxis()};   ///< Direction of the line (should be normalized)

    // ========================================================================
    // Constructors
    // ========================================================================

    /**
     * @brief Default constructor. Creates a line along Z-axis through origin.
     */
    constexpr Line() noexcept = default;

    /**
     * @brief Constructs a line from a point and direction.
     *
     * @param point_on_line A point on the line
     * @param direction Direction vector (will be normalized)
     */
    Line(const Vec3f& point_on_line, const Vec3f& direction) noexcept
        : point(point_on_line)
        , dir(direction.normalized()) {}

    /**
     * @brief Constructs a line from a ray.
     *
     * The line passes through the ray's origin in the ray's direction.
     */
    explicit Line(const Ray& ray) noexcept
        : point(ray.origin())
        , dir(ray.direction()) {}

    /**
     * @brief Constructs a line from a line segment.
     *
     * The line passes through the segment's endpoints.
     */
    explicit Line(const LineSegment& segment) noexcept
        : point(segment.start)
        , dir(segment.normalizedDirection()) {}

    // ========================================================================
    // Static Factory Methods
    // ========================================================================

    /**
     * @brief Creates a line from two points.
     */
    [[nodiscard]] static Line fromPoints(const Vec3f& p1, const Vec3f& p2) noexcept {
        return Line(p1, (p2 - p1).normalized());
    }

    // ========================================================================
    // Point Queries
    // ========================================================================

    /**
     * @brief Gets a point along the line at parameter t.
     *
     * @param t Parameter (can be any real number)
     * @return Point at point + t * direction
     */
    [[nodiscard]] constexpr Vec3f getPoint(float t) const noexcept { return point + dir * t; }

    /**
     * @brief Finds the closest point on this line to a given point.
     *
     * @param query_point The query point
     * @return Closest point on the line
     */
    [[nodiscard]] Vec3f closestPoint(const Vec3f& query_point) const noexcept {
        float t = (query_point - point).dot(dir);
        return getPoint(t);
    }

    /**
     * @brief Finds the closest point and returns the parameter t.
     *
     * @param query_point The query point
     * @param out_t Output parameter t
     * @return Closest point on the line
     */
    [[nodiscard]] Vec3f closestPoint(const Vec3f& query_point, float& out_t) const noexcept {
        out_t = (query_point - point).dot(dir);
        return getPoint(out_t);
    }

    /**
     * @brief Computes the distance from a point to this line.
     */
    [[nodiscard]] float distanceToPoint(const Vec3f& query_point) const noexcept {
        return (query_point - closestPoint(query_point)).length();
    }

    /**
     * @brief Computes the squared distance from a point to this line.
     */
    [[nodiscard]] float squaredDistanceToPoint(const Vec3f& query_point) const noexcept {
        return (query_point - closestPoint(query_point)).lengthSquared();
    }

    // ========================================================================
    // Line-Line Queries
    // ========================================================================

    /**
     * @brief Finds the closest points between two lines.
     *
     * @param other The other line
     * @param out_t1 Output parameter t for this line
     * @param out_t2 Output parameter t for other line
     * @return Closest point on this line
     */
    [[nodiscard]] Vec3f closestPointToLine(const Line& other, float& out_t1, float& out_t2) const noexcept {
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

    /**
     * @brief Computes the distance between two lines.
     */
    [[nodiscard]] float distanceToLine(const Line& other) const noexcept {
        float t1, t2;
        Vec3f p1 = closestPointToLine(other, t1, t2);
        Vec3f p2 = other.getPoint(t2);
        return (p1 - p2).length();
    }

    // ========================================================================
    // Geometric Queries
    // ========================================================================

    /**
     * @brief Checks if a point lies on this line.
     *
     * @param query_point The point to test
     * @param epsilon Tolerance
     * @return true if point is on the line
     */
    [[nodiscard]] bool contains(const Vec3f& query_point, float epsilon = kEpsilon<float>) const noexcept {
        return squaredDistanceToPoint(query_point) < epsilon * epsilon;
    }

    /**
     * @brief Checks if two lines are parallel.
     */
    [[nodiscard]] bool isParallel(const Line& other, float epsilon = kEpsilon<float>) const noexcept {
        return std::abs(std::abs(dir.dot(other.dir)) - 1.0f) < epsilon;
    }

    /**
     * @brief Checks if two lines are the same (coincident).
     */
    [[nodiscard]] bool isSame(const Line& other, float epsilon = kEpsilon<float>) const noexcept {
        if (!isParallel(other, epsilon)) {
            return false;
        }
        return contains(other.point, epsilon);
    }

    // ========================================================================
    // Validation
    // ========================================================================

    /**
     * @brief Checks if the direction is valid (normalized and non-zero).
     */
    [[nodiscard]] bool isValid(float epsilon = kEpsilon<float>) const noexcept {
        float len_sq = dir.lengthSquared();
        return std::abs(len_sq - 1.0f) < epsilon;
    }

    // ========================================================================
    // Comparison
    // ========================================================================

    [[nodiscard]] bool areSame(const Line& other, float epsilon = kEpsilon<float>) const noexcept {
        return point.areSame(other.point, epsilon) && dir.areSame(other.dir, epsilon);
    }
};

}  // namespace vne::math

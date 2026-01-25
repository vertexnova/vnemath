/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Triangle primitive for intersection testing and mesh operations.
 * ----------------------------------------------------------------------
 */

#pragma once

#include "../core/types.h"
#include "../core/vec.h"

namespace vne::math {

/**
 * @class Triangle
 * @brief A triangle defined by three vertices in 3D space.
 *
 * Provides operations for:
 * - Computing normal, area, centroid
 * - Barycentric coordinate calculations
 * - Point containment testing
 * - Edge access
 */
class Triangle {
   public:
    Vec3f v0;  ///< First vertex
    Vec3f v1;  ///< Second vertex
    Vec3f v2;  ///< Third vertex

    // ========================================================================
    // Constructors
    // ========================================================================

    /**
     * @brief Default constructor. Does not initialize vertices.
     */
    Triangle() = default;

    /**
     * @brief Constructs a triangle from three vertices.
     */
    constexpr Triangle(const Vec3f& vertex0, const Vec3f& vertex1, const Vec3f& vertex2) noexcept
        : v0(vertex0)
        , v1(vertex1)
        , v2(vertex2) {}

    // ========================================================================
    // Geometric Properties
    // ========================================================================

    /**
     * @brief Computes the (unnormalized) normal vector.
     *
     * The normal points in the direction of (v1-v0) x (v2-v0).
     * For a normalized normal, call normal().normalized().
     *
     * @return The unnormalized normal vector
     */
    [[nodiscard]] constexpr Vec3f normal() const noexcept { return edge01().cross(edge02()); }

    /**
     * @brief Computes the unit normal vector.
     * @return The normalized normal vector
     */
    [[nodiscard]] Vec3f unitNormal() const noexcept { return normal().normalized(); }

    /**
     * @brief Computes the area of the triangle.
     * @return The area (half the magnitude of the cross product)
     */
    [[nodiscard]] float area() const noexcept { return normal().length() * 0.5f; }

    /**
     * @brief Computes the centroid (center of mass).
     * @return The centroid point
     */
    [[nodiscard]] constexpr Vec3f centroid() const noexcept { return (v0 + v1 + v2) / 3.0f; }

    /**
     * @brief Computes the perimeter of the triangle.
     * @return Sum of all edge lengths
     */
    [[nodiscard]] float perimeter() const noexcept { return edge01().length() + edge12().length() + edge20().length(); }

    // ========================================================================
    // Edge Access
    // ========================================================================

    /**
     * @brief Edge from v0 to v1.
     */
    [[nodiscard]] constexpr Vec3f edge01() const noexcept { return v1 - v0; }

    /**
     * @brief Edge from v0 to v2.
     */
    [[nodiscard]] constexpr Vec3f edge02() const noexcept { return v2 - v0; }

    /**
     * @brief Edge from v1 to v2.
     */
    [[nodiscard]] constexpr Vec3f edge12() const noexcept { return v2 - v1; }

    /**
     * @brief Edge from v2 to v0.
     */
    [[nodiscard]] constexpr Vec3f edge20() const noexcept { return v0 - v2; }

    // ========================================================================
    // Barycentric Coordinates
    // ========================================================================

    /**
     * @brief Computes barycentric coordinates of a point.
     *
     * Given a point P, returns (u, v, w) where:
     * - P = u*v0 + v*v1 + w*v2
     * - u + v + w = 1
     *
     * If the point is inside the triangle: u,v,w all in [0,1]
     *
     * @param point The point to compute coordinates for
     * @return Barycentric coordinates (u, v, w)
     */
    [[nodiscard]] Vec3f barycentric(const Vec3f& point) const noexcept {
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
            return Vec3f(1.0f / 3.0f);  // Degenerate triangle
        }

        float inv_denom = 1.0f / denom;
        float v = (d11 * d20 - d01 * d21) * inv_denom;
        float w = (d00 * d21 - d01 * d20) * inv_denom;
        float u = 1.0f - v - w;

        return Vec3f(u, v, w);
    }

    /**
     * @brief Interpolates a value using barycentric coordinates.
     *
     * @param bary Barycentric coordinates
     * @param a0 Value at v0
     * @param a1 Value at v1
     * @param a2 Value at v2
     * @return Interpolated value
     */
    template<typename T>
    [[nodiscard]] static constexpr T interpolate(const Vec3f& bary, const T& a0, const T& a1, const T& a2) noexcept {
        return a0 * bary.x() + a1 * bary.y() + a2 * bary.z();
    }

    /**
     * @brief Gets a point from barycentric coordinates.
     */
    [[nodiscard]] constexpr Vec3f pointFromBarycentric(const Vec3f& bary) const noexcept {
        return interpolate(bary, v0, v1, v2);
    }

    // ========================================================================
    // Containment Tests
    // ========================================================================

    /**
     * @brief Checks if a point lies on the triangle's plane and inside.
     *
     * Uses barycentric coordinates for robust testing.
     *
     * @param point The point to test
     * @param epsilon Tolerance for edge cases
     * @return true if point is inside or on edge
     */
    [[nodiscard]] bool contains(const Vec3f& point, float epsilon = kEpsilon<float>) const noexcept {
        Vec3f bary = barycentric(point);
        return bary.x() >= -epsilon && bary.y() >= -epsilon && bary.z() >= -epsilon;
    }

    /**
     * @brief Checks if a 2D point is inside the triangle (XY plane projection).
     *
     * @param point 2D point to test
     * @param epsilon Tolerance
     * @return true if inside
     */
    [[nodiscard]] bool contains2D(const Vec2f& point, float epsilon = kEpsilon<float>) const noexcept {
        return contains(Vec3f(point.x(), point.y(), 0.0f), epsilon);
    }

    // ========================================================================
    // Distance Queries
    // ========================================================================

    /**
     * @brief Computes the closest point on the triangle to a given point.
     *
     * @param point The query point
     * @return The closest point on the triangle
     */
    [[nodiscard]] Vec3f closestPoint(const Vec3f& point) const noexcept {
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

    /**
     * @brief Computes the distance from a point to the triangle.
     */
    [[nodiscard]] float distanceToPoint(const Vec3f& point) const noexcept {
        return (point - closestPoint(point)).length();
    }

    /**
     * @brief Computes the squared distance from a point to the triangle.
     */
    [[nodiscard]] float squaredDistanceToPoint(const Vec3f& point) const noexcept {
        return (point - closestPoint(point)).lengthSquared();
    }

    // ========================================================================
    // Validation
    // ========================================================================

    /**
     * @brief Checks if the triangle is degenerate (zero area).
     */
    [[nodiscard]] bool isDegenerate(float epsilon = kEpsilon<float>) const noexcept {
        return normal().lengthSquared() < epsilon * epsilon;
    }

    /**
     * @brief Checks if the triangle is valid (non-degenerate).
     */
    [[nodiscard]] bool isValid(float epsilon = kEpsilon<float>) const noexcept { return !isDegenerate(epsilon); }

    // ========================================================================
    // Comparison
    // ========================================================================

    [[nodiscard]] bool operator==(const Triangle& other) const noexcept = default;

    [[nodiscard]] bool areSame(const Triangle& other, float epsilon = kEpsilon<float>) const noexcept {
        return v0.areSame(other.v0, epsilon) && v1.areSame(other.v1, epsilon) && v2.areSame(other.v2, epsilon);
    }

   private:
    /**
     * @brief Helper: closest point on a line segment.
     */
    [[nodiscard]] static Vec3f closestPointOnEdge(const Vec3f& point, const Vec3f& a, const Vec3f& b) noexcept {
        Vec3f ab = b - a;
        float t = clamp((point - a).dot(ab) / ab.dot(ab), 0.0f, 1.0f);
        return a + ab * t;
    }
};

}  // namespace vne::math

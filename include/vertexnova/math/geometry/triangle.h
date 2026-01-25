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
    [[nodiscard]] Vec3f unitNormal() const noexcept;

    /**
     * @brief Computes the area of the triangle.
     * @return The area (half the magnitude of the cross product)
     */
    [[nodiscard]] float area() const noexcept;

    /**
     * @brief Computes the centroid (center of mass).
     * @return The centroid point
     */
    [[nodiscard]] constexpr Vec3f centroid() const noexcept { return (v0 + v1 + v2) / 3.0f; }

    /**
     * @brief Computes the perimeter of the triangle.
     * @return Sum of all edge lengths
     */
    [[nodiscard]] float perimeter() const noexcept;

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
    [[nodiscard]] Vec3f barycentric(const Vec3f& point) const noexcept;

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
    [[nodiscard]] bool contains(const Vec3f& point, float epsilon = kEpsilon<float>) const noexcept;

    /**
     * @brief Checks if a 2D point is inside the triangle (XY plane projection).
     *
     * @param point 2D point to test
     * @param epsilon Tolerance
     * @return true if inside
     */
    [[nodiscard]] bool contains2D(const Vec2f& point, float epsilon = kEpsilon<float>) const noexcept;

    // ========================================================================
    // Distance Queries
    // ========================================================================

    /**
     * @brief Computes the closest point on the triangle to a given point.
     *
     * @param point The query point
     * @return The closest point on the triangle
     */
    [[nodiscard]] Vec3f closestPoint(const Vec3f& point) const noexcept;

    /**
     * @brief Computes the distance from a point to the triangle.
     */
    [[nodiscard]] float distanceToPoint(const Vec3f& point) const noexcept;

    /**
     * @brief Computes the squared distance from a point to the triangle.
     */
    [[nodiscard]] float squaredDistanceToPoint(const Vec3f& point) const noexcept;

    // ========================================================================
    // Validation
    // ========================================================================

    /**
     * @brief Checks if the triangle is degenerate (zero area).
     */
    [[nodiscard]] bool isDegenerate(float epsilon = kEpsilon<float>) const noexcept;

    /**
     * @brief Checks if the triangle is valid (non-degenerate).
     */
    [[nodiscard]] bool isValid(float epsilon = kEpsilon<float>) const noexcept;

    // ========================================================================
    // Comparison
    // ========================================================================

    [[nodiscard]] bool operator==(const Triangle& other) const noexcept = default;

    [[nodiscard]] bool areSame(const Triangle& other, float epsilon = kEpsilon<float>) const noexcept;

   private:
    /**
     * @brief Helper: closest point on a line segment.
     */
    [[nodiscard]] static Vec3f closestPointOnEdge(const Vec3f& point, const Vec3f& a, const Vec3f& b) noexcept;
};

}  // namespace vne::math

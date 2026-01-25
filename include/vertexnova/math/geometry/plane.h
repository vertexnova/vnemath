#pragma once
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

/**
 * @file plane.h
 * @brief Defines the Plane class for plane operations in 3D space.
 */

// Project includes
#include "vertexnova/math/core/constants.h"
#include "vertexnova/math/core/mat.h"
#include "vertexnova/math/core/vec.h"

// Standard library includes
#include <ostream>

namespace vne::math {

/**
 * @class Plane
 * @brief Represents a plane in 3D space.
 *
 * A plane is defined by the equation: n dot p + d = 0
 * where n is the normal vector and d is the distance from origin.
 *
 * The Hesse normal form: ax + by + cz + d = 0
 */
class Plane {
   public:
    /** @brief Default constructor, creates XY plane at origin */
    Plane() noexcept = default;

    /**
     * @brief Constructs a plane from normal and distance
     * @param normal The plane normal (should be normalized)
     * @param d The signed distance from origin
     */
    Plane(const Vec3f& normal, float d) noexcept;

    /**
     * @brief Constructs a plane from normal components and distance
     * @param normal_x X component of normal
     * @param normal_y Y component of normal
     * @param normal_z Z component of normal
     * @param d The signed distance from origin
     */
    Plane(float normal_x, float normal_y, float normal_z, float d) noexcept;

    /**
     * @brief Constructs a plane from a Vec4f (xyz = normal, w = distance)
     * @param normal_and_dist Combined normal and distance vector
     */
    explicit Plane(const Vec4f& normal_and_dist) noexcept;

    /**
     * @brief Constructs a plane from three points (counter-clockwise order)
     * @param p0 First point
     * @param p1 Second point
     * @param p2 Third point
     * @note Points must not be collinear
     */
    Plane(const Vec3f& p0, const Vec3f& p1, const Vec3f& p2) noexcept;

    /**
     * @brief Constructs a plane from a point and normal
     * @param point A point on the plane
     * @param normal The plane normal
     */
    Plane(const Vec3f& point, const Vec3f& normal) noexcept;

   public:
    /// @name Static Factory Methods
    /// @{

    /**
     * @brief Creates a plane from three points
     * @param p0 First point
     * @param p1 Second point
     * @param p2 Third point
     * @return The constructed plane
     */
    [[nodiscard]] static Plane fromPoints(const Vec3f& p0, const Vec3f& p1, const Vec3f& p2) noexcept;

    /**
     * @brief Creates a plane from a point and normal
     * @param point A point on the plane
     * @param normal The plane normal
     * @return The constructed plane
     */
    [[nodiscard]] static Plane fromPointNormal(const Vec3f& point, const Vec3f& normal) noexcept;

    /**
     * @brief Returns a normalized copy of a plane
     * @param plane The plane to normalize
     * @return The normalized plane
     */
    [[nodiscard]] static Plane normalized(const Plane& plane) noexcept;
    /// @}

   public:
    /// @name Modification Methods
    /// @{

    /** @brief Flips the plane (reverses normal and negates d) */
    void flip() noexcept;

    /** @brief Normalizes this plane */
    void normalize() noexcept;

    /**
     * @brief Translates this plane by an offset
     * @param offset The translation vector
     */
    void translate(const Vec3f& offset) noexcept;

    /**
     * @brief Transforms this plane by a 3x3 matrix
     * @param transform The transformation matrix
     */
    void transform(const Mat3x3f& transform) noexcept;

    /**
     * @brief Transforms this plane by a 4x4 matrix
     * @param transform The transformation matrix
     */
    void transform(const Mat4x4f& transform) noexcept;
    /// @}

   public:
    /// @name Distance Methods
    /// @{

    /**
     * @brief Computes the signed distance from a point to this plane
     * @param point The point to measure from
     * @return Positive if in front, negative if behind
     */
    [[nodiscard]] float signedDistance(const Vec3f& point) const noexcept;

    /**
     * @brief Computes the absolute distance from a point to this plane
     * @param point The point to measure from
     * @return The distance (always positive)
     */
    [[nodiscard]] float distance(const Vec3f& point) const noexcept;

    /**
     * @brief Computes the closest point on this plane to a given point
     * @param point The point to project
     * @return The closest point on the plane
     */
    [[nodiscard]] Vec3f closestPoint(const Vec3f& point) const noexcept;

    /**
     * @brief Gets a point on this plane
     * @return A point on the plane (at -d * normal from origin)
     */
    [[nodiscard]] Vec3f pointOnPlane() const noexcept;
    /// @}

   public:
    /// @name Query Methods
    /// @{

    /**
     * @brief Checks if this plane is normalized
     * @param eps Tolerance for comparison
     * @return true if the normal has unit length
     */
    [[nodiscard]] bool isNormalized(float eps = kFloatEpsilon) const noexcept;

    /**
     * @brief Checks if a point is on the positive side of the plane
     * @param point The point to check
     * @param eps Tolerance for comparison
     * @return true if point is in front of the plane
     */
    [[nodiscard]] bool isOnPositiveSide(const Vec3f& point, float eps = kFloatEpsilon) const noexcept;

    /**
     * @brief Checks if a point is on the negative side of the plane
     * @param point The point to check
     * @param eps Tolerance for comparison
     * @return true if point is behind the plane
     */
    [[nodiscard]] bool isOnNegativeSide(const Vec3f& point, float eps = kFloatEpsilon) const noexcept;

    /**
     * @brief Checks if a point lies on this plane
     * @param point The point to check
     * @param eps Tolerance for comparison
     * @return true if point is on the plane
     */
    [[nodiscard]] bool isOnPlane(const Vec3f& point, float eps = kFloatEpsilon) const noexcept;

    /**
     * @brief Checks if two points are on the same side of the plane
     * @param point1 First point
     * @param point2 Second point
     * @param eps Tolerance for comparison
     * @return true if both points are on the same side
     */
    [[nodiscard]] bool areOnSameSide(const Vec3f& point1,
                                     const Vec3f& point2,
                                     float eps = kFloatEpsilon) const noexcept;

    /**
     * @brief Checks if a direction is in the positive normal direction
     * @param dir The direction to check
     * @param eps Tolerance for comparison
     * @return true if direction aligns with normal
     */
    [[nodiscard]] bool isInPositiveDirection(const Vec3f& dir, float eps = kFloatEpsilon) const noexcept;

    /**
     * @brief Checks if a direction is in the negative normal direction
     * @param dir The direction to check
     * @param eps Tolerance for comparison
     * @return true if direction opposes normal
     */
    [[nodiscard]] bool isInNegativeDirection(const Vec3f& dir, float eps = kFloatEpsilon) const noexcept;

    /**
     * @brief Checks if this plane contains a point
     * @param point The point to check
     * @param eps Tolerance for comparison
     * @return true if point is on the plane
     */
    [[nodiscard]] bool contains(const Vec3f& point, float eps = kFloatEpsilon) const noexcept;
    /// @}

   public:
    /// @name Comparison Operators
    /// @{
    [[nodiscard]] bool operator==(const Plane& plane) const noexcept;
    [[nodiscard]] bool operator!=(const Plane& plane) const noexcept;
    /// @}

   public:
    friend std::ostream& operator<<(std::ostream& os, const Plane& plane);

   public:
    Vec3f normal{Vec3f::zAxis()};  ///< The plane normal (should be normalized)
    float d{0.0f};                 ///< Distance from origin along normal
};

}  // namespace vne::math

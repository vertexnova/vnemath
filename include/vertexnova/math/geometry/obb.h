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

#pragma once

/**
 * @file obb.h
 * @brief Defines the Obb class for oriented bounding box operations.
 */

#include "vertexnova/math/core/constants.h"
#include "vertexnova/math/core/mat.h"
#include "vertexnova/math/core/quat.h"
#include "vertexnova/math/core/vec.h"

#include <ostream>

namespace vne::math {

// Forward declarations
class Aabb;

/**
 * @class Obb
 * @brief Represents an Oriented Bounding Box in 3D space.
 *
 * An OBB is a rectangular box that can be rotated arbitrarily in space.
 * Unlike an AABB, its edges are not aligned with coordinate axes.
 * OBBs provide tighter fits for rotated objects but are more expensive
 * to compute intersections.
 *
 * The OBB is defined by:
 * - A center point
 * - Three orthonormal axes (stored as a rotation matrix or quaternion)
 * - Half-extents along each local axis
 */
class Obb {
   public:
    /**
     * @brief Default constructor. Creates a unit OBB at origin aligned with world axes.
     */
    Obb() noexcept;

    /**
     * @brief Constructs an OBB from center, half-extents, and orientation.
     * @param center The center point of the OBB
     * @param half_extents The half-size along each local axis
     * @param orientation The rotation quaternion
     */
    Obb(const Vec3f& center, const Vec3f& half_extents, const Quatf& orientation = Quatf::identity()) noexcept;

    /**
     * @brief Constructs an OBB from center, half-extents, and rotation matrix.
     * @param center The center point of the OBB
     * @param half_extents The half-size along each local axis
     * @param rotation 3x3 rotation matrix defining the orientation
     */
    Obb(const Vec3f& center, const Vec3f& half_extents, const Mat3f& rotation) noexcept;

    /** @brief Default destructor */
    ~Obb() noexcept = default;

    /** @brief Copy constructor */
    Obb(const Obb& other) noexcept = default;

    /** @brief Copy assignment operator */
    Obb& operator=(const Obb& other) noexcept = default;

   public:
    /// @name Static Factory Methods
    /// @{

    /**
     * @brief Creates an OBB from an AABB (axis-aligned).
     * @param aabb The AABB to convert
     * @return An OBB with identity orientation
     */
    [[nodiscard]] static Obb fromAabb(const Aabb& aabb) noexcept;

    /**
     * @brief Creates an OBB from min/max corners (axis-aligned).
     * @param min Minimum corner
     * @param max Maximum corner
     * @return An OBB with identity orientation
     */
    [[nodiscard]] static Obb fromMinMax(const Vec3f& min, const Vec3f& max) noexcept;
    /// @}

   public:
    /// @name Accessors
    /// @{

    /**
     * @brief Sets the center point.
     */
    void setCenter(const Vec3f& center) noexcept;

    /**
     * @brief Gets the center point.
     */
    [[nodiscard]] const Vec3f& center() const noexcept;

    /**
     * @brief Sets the half-extents.
     */
    void setHalfExtents(const Vec3f& half_extents) noexcept;

    /**
     * @brief Gets the half-extents.
     */
    [[nodiscard]] const Vec3f& halfExtents() const noexcept;

    /**
     * @brief Sets the orientation from a quaternion.
     */
    void setOrientation(const Quatf& orientation) noexcept;

    /**
     * @brief Gets the orientation as a quaternion.
     */
    [[nodiscard]] const Quatf& orientation() const noexcept;

    /**
     * @brief Gets the orientation as a 3x3 rotation matrix.
     */
    [[nodiscard]] Mat3f rotationMatrix() const noexcept;
    /// @}

   public:
    /// @name Local Axes
    /// @{

    /**
     * @brief Gets the local X axis (right) in world space.
     */
    [[nodiscard]] Vec3f axisX() const noexcept;

    /**
     * @brief Gets the local Y axis (up) in world space.
     */
    [[nodiscard]] Vec3f axisY() const noexcept;

    /**
     * @brief Gets the local Z axis (forward) in world space.
     */
    [[nodiscard]] Vec3f axisZ() const noexcept;

    /**
     * @brief Gets the axis by index (0=X, 1=Y, 2=Z).
     */
    [[nodiscard]] Vec3f axis(uint32_t index) const noexcept;
    /// @}

   public:
    /// @name Computed Properties
    /// @{

    /**
     * @brief Computes the full size (2 * half_extents).
     */
    [[nodiscard]] Vec3f size() const noexcept;

    /**
     * @brief Computes the volume of the OBB.
     */
    [[nodiscard]] float volume() const noexcept;

    /**
     * @brief Computes the surface area of the OBB.
     */
    [[nodiscard]] float surfaceArea() const noexcept;

    /**
     * @brief Gets the 8 corner points of the OBB.
     * @param corners Output array of 8 corner points
     */
    void getCorners(Vec3f corners[8]) const noexcept;

    /**
     * @brief Gets a corner by index (0-7).
     */
    [[nodiscard]] Vec3f corner(uint32_t index) const noexcept;

    /**
     * @brief Computes the AABB that bounds this OBB.
     */
    [[nodiscard]] Aabb getAabb() const noexcept;
    /// @}

   public:
    /// @name Modification Methods
    /// @{

    /**
     * @brief Translates the OBB by an offset.
     */
    void translate(const Vec3f& offset) noexcept;

    /**
     * @brief Rotates the OBB by a quaternion.
     */
    void rotate(const Quatf& rotation) noexcept;

    /**
     * @brief Scales the OBB uniformly.
     */
    void scale(float factor) noexcept;

    /**
     * @brief Scales the OBB non-uniformly.
     */
    void scale(const Vec3f& factors) noexcept;

    /**
     * @brief Transforms the OBB by a 4x4 matrix.
     */
    void transform(const Mat4f& matrix) noexcept;
    /// @}

   public:
    /// @name Query Methods
    /// @{

    /**
     * @brief Checks if this OBB is valid (positive extents).
     */
    [[nodiscard]] bool isValid() const noexcept;

    /**
     * @brief Checks if this OBB contains a point.
     */
    [[nodiscard]] bool contains(const Vec3f& point) const noexcept;

    /**
     * @brief Computes the closest point on this OBB to a given point.
     */
    [[nodiscard]] Vec3f closestPoint(const Vec3f& point) const noexcept;

    /**
     * @brief Computes the squared distance from a point to this OBB.
     */
    [[nodiscard]] float squaredDistanceToPoint(const Vec3f& point) const noexcept;

    /**
     * @brief Computes the distance from a point to this OBB.
     */
    [[nodiscard]] float distanceToPoint(const Vec3f& point) const noexcept;

    /**
     * @brief Checks if this OBB intersects another OBB.
     * Uses the Separating Axis Theorem (SAT).
     */
    [[nodiscard]] bool intersects(const Obb& other) const noexcept;

    /**
     * @brief Checks if this OBB intersects an AABB.
     */
    [[nodiscard]] bool intersects(const Aabb& aabb) const noexcept;
    /// @}

   public:
    /// @name Comparison Operators
    /// @{
    [[nodiscard]] bool operator==(const Obb& other) const noexcept;
    [[nodiscard]] bool operator!=(const Obb& other) const noexcept;

    [[nodiscard]] bool areSame(const Obb& other, float epsilon = kFloatEpsilon) const noexcept;
    /// @}

   public:
    friend std::ostream& operator<<(std::ostream& os, const Obb& obb);

   private:
    Vec3f center_{Vec3f::zero()};           ///< Center point
    Vec3f half_extents_{0.5f, 0.5f, 0.5f};  ///< Half-extents along local axes
    Quatf orientation_{Quatf::identity()};  ///< Orientation quaternion
};

}  // namespace vne::math

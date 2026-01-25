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
 * @file aabb.h
 * @brief Defines the Aabb class for axis-aligned bounding box operations.
 */

// Project includes
#include "vertexnova/math/constants.h"
#include "vertexnova/math/core/vec.h"

// Standard library includes
#include <ostream>

namespace vne::math {

/**
 * @class Aabb
 * @brief Represents an Axis-Aligned Bounding Box in 3D space.
 *
 * An AABB is a rectangular box whose edges are aligned with the coordinate axes.
 * This is one of the simplest and most commonly used bounding volumes for
 * collision detection and spatial queries.
 */
class Aabb {
   public:
    /**
     * @brief Default constructor, creates an invalid (inverted) AABB
     *
     * The min is set to max float values and max to min float values,
     * so any point will expand the box correctly.
     */
    Aabb() noexcept;

    /**
     * @brief Constructs an AABB from min and max corners
     * @param min The minimum corner (smallest x, y, z)
     * @param max The maximum corner (largest x, y, z)
     */
    Aabb(const Vec3f& min, const Vec3f& max) noexcept;

    /** @brief Default destructor */
    ~Aabb() noexcept = default;

    /** @brief Copy constructor */
    Aabb(const Aabb& other) noexcept = default;

    /** @brief Copy assignment operator */
    Aabb& operator=(const Aabb& other) noexcept = default;

   public:
    /// @name Static Factory Methods
    /// @{

    /**
     * @brief Creates an AABB from center and half-extents
     * @param center The center point of the AABB
     * @param half_extents The half-size in each axis direction
     * @return The constructed AABB
     */
    [[nodiscard]] static Aabb fromCenterAndHalfExtents(const Vec3f& center, const Vec3f& half_extents) noexcept;

    /**
     * @brief Creates an AABB from center and full size
     * @param center The center point of the AABB
     * @param size The full size in each axis direction
     * @return The constructed AABB
     */
    [[nodiscard]] static Aabb fromCenterAndSize(const Vec3f& center, const Vec3f& size) noexcept;
    /// @}

   public:
    /// @name Accessors
    /// @{

    /**
     * @brief Sets the minimum corner
     * @param min The new minimum corner
     */
    void setMin(const Vec3f& min) noexcept;

    /**
     * @brief Gets the minimum corner
     * @return The minimum corner
     */
    [[nodiscard]] const Vec3f& min() const noexcept;

    /**
     * @brief Sets the maximum corner
     * @param max The new maximum corner
     */
    void setMax(const Vec3f& max) noexcept;

    /**
     * @brief Gets the maximum corner
     * @return The maximum corner
     */
    [[nodiscard]] const Vec3f& max() const noexcept;
    /// @}

   public:
    /// @name Computed Properties
    /// @{

    /**
     * @brief Computes the center of the AABB
     * @return The center point
     */
    [[nodiscard]] Vec3f center() const noexcept;

    /**
     * @brief Computes the size (dimensions) of the AABB
     * @return The size vector (width, height, depth)
     */
    [[nodiscard]] Vec3f size() const noexcept;

    /**
     * @brief Computes the half-extents (half-size) of the AABB
     * @return The half-extents vector
     */
    [[nodiscard]] Vec3f halfExtents() const noexcept;

    /**
     * @brief Computes the volume of the AABB
     * @return The volume
     */
    [[nodiscard]] float volume() const noexcept;

    /**
     * @brief Computes the surface area of the AABB
     * @return The surface area
     */
    [[nodiscard]] float surfaceArea() const noexcept;

    /**
     * @brief Gets the corner point by index (0-7)
     * @param index Corner index
     * @return The corner point
     */
    [[nodiscard]] Vec3f corner(uint32_t index) const noexcept;
    /// @}

   public:
    /// @name Modification Methods
    /// @{

    /**
     * @brief Expands the AABB to include a point
     * @param point The point to include
     */
    void expand(const Vec3f& point) noexcept;

    /**
     * @brief Expands the AABB to include another AABB
     * @param other The AABB to include
     */
    void expand(const Aabb& other) noexcept;

    /**
     * @brief Grows the AABB by a uniform amount in all directions
     * @param amount The amount to grow
     */
    void grow(float amount) noexcept;

    /**
     * @brief Grows the AABB by different amounts in each axis
     * @param amount The amount to grow in each axis
     */
    void grow(const Vec3f& amount) noexcept;

    /**
     * @brief Translates the AABB by an offset
     * @param offset The translation offset
     */
    void translate(const Vec3f& offset) noexcept;

    /**
     * @brief Resets the AABB to invalid state
     */
    void reset() noexcept;
    /// @}

   public:
    /// @name Query Methods
    /// @{

    /**
     * @brief Checks if this AABB is valid (min <= max)
     * @return true if valid
     */
    [[nodiscard]] bool isValid() const noexcept;

    /**
     * @brief Checks if this AABB contains a point
     * @param point The point to test
     * @return true if the point is inside or on the surface
     */
    [[nodiscard]] bool contains(const Vec3f& point) const noexcept;

    /**
     * @brief Checks if this AABB fully contains another AABB
     * @param other The AABB to test
     * @return true if other is fully inside this AABB
     */
    [[nodiscard]] bool contains(const Aabb& other) const noexcept;

    /**
     * @brief Checks if this AABB intersects another AABB
     * @param other The AABB to test against
     * @return true if the AABBs overlap
     */
    [[nodiscard]] bool intersects(const Aabb& other) const noexcept;

    /**
     * @brief Computes the closest point on this AABB to a given point
     * @param point The point to find the closest to
     * @return The closest point on the AABB surface or inside
     */
    [[nodiscard]] Vec3f closestPoint(const Vec3f& point) const noexcept;

    /**
     * @brief Computes the squared distance from a point to this AABB
     * @param point The point to measure from
     * @return The squared distance (0 if inside)
     */
    [[nodiscard]] float squaredDistanceToPoint(const Vec3f& point) const noexcept;
    /// @}

   public:
    /// @name Comparison Operators
    /// @{
    [[nodiscard]] bool operator==(const Aabb& other) const noexcept;
    [[nodiscard]] bool operator!=(const Aabb& other) const noexcept;
    /// @}

   public:
    friend std::ostream& operator<<(std::ostream& os, const Aabb& aabb);

   private:
    Vec3f min_;  ///< Minimum corner of the AABB
    Vec3f max_;  ///< Maximum corner of the AABB
};

}  // namespace vne::math

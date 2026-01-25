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
 * @file sphere.h
 * @brief Defines the Sphere class for spherical bounding volume operations.
 */

// Project includes
#include "vertexnova/math/core/constants.h"
#include "vertexnova/math/core/vec.h"

// Standard library includes
#include <ostream>

namespace vne::math {

// Forward declarations
class Aabb;

/**
 * @class Sphere
 * @brief Represents a sphere in 3D space.
 *
 * A sphere is defined by a center point and a radius. Spheres are commonly
 * used as bounding volumes due to their simple intersection tests and
 * rotational invariance.
 */
class Sphere {
   public:
    /**
     * @brief Default constructor, creates an invalid sphere
     *
     * Creates a sphere at origin with negative radius (invalid state).
     */
    Sphere() noexcept;

    /**
     * @brief Constructs a sphere from center and radius
     * @param center The center point
     * @param radius The radius (should be positive)
     */
    Sphere(const Vec3f& center, float radius) noexcept;

    /** @brief Default destructor */
    ~Sphere() noexcept = default;

    /** @brief Copy constructor */
    Sphere(const Sphere& other) noexcept = default;

    /** @brief Copy assignment operator */
    Sphere& operator=(const Sphere& other) noexcept = default;

   public:
    /// @name Accessors
    /// @{

    /**
     * @brief Sets the center of the sphere
     * @param center The new center point
     */
    void setCenter(const Vec3f& center) noexcept;

    /**
     * @brief Gets the center of the sphere
     * @return The center point
     */
    [[nodiscard]] const Vec3f& center() const noexcept;

    /**
     * @brief Sets the radius of the sphere
     * @param radius The new radius
     */
    void setRadius(float radius) noexcept;

    /**
     * @brief Gets the radius of the sphere
     * @return The radius
     */
    [[nodiscard]] float radius() const noexcept;
    /// @}

   public:
    /// @name Computed Properties
    /// @{

    /**
     * @brief Computes the diameter of the sphere
     * @return The diameter (2 * radius)
     */
    [[nodiscard]] float diameter() const noexcept;

    /**
     * @brief Computes the volume of the sphere
     * @return The volume (4/3 * pi * r^3)
     */
    [[nodiscard]] float volume() const noexcept;

    /**
     * @brief Computes the surface area of the sphere
     * @return The surface area (4 * pi * r^2)
     */
    [[nodiscard]] float surfaceArea() const noexcept;
    /// @}

   public:
    /// @name Modification Methods
    /// @{

    /**
     * @brief Expands the sphere to include a point
     * @param point The point to include
     */
    void expand(const Vec3f& point) noexcept;

    /**
     * @brief Expands the sphere to include another sphere
     * @param other The sphere to include
     */
    void expand(const Sphere& other) noexcept;

    /**
     * @brief Grows the sphere radius by an amount
     * @param amount The amount to grow
     */
    void grow(float amount) noexcept;

    /**
     * @brief Translates the sphere by an offset
     * @param offset The translation offset
     */
    void translate(const Vec3f& offset) noexcept;
    /// @}

   public:
    /// @name Query Methods
    /// @{

    /**
     * @brief Checks if this sphere is valid (positive radius)
     * @return true if valid
     */
    [[nodiscard]] bool isValid() const noexcept;

    /**
     * @brief Checks if this sphere contains a point
     * @param point The point to test
     * @return true if the point is inside or on the surface
     */
    [[nodiscard]] bool contains(const Vec3f& point) const noexcept;

    /**
     * @brief Checks if this sphere fully contains another sphere
     * @param other The sphere to test
     * @return true if other is fully inside this sphere
     */
    [[nodiscard]] bool contains(const Sphere& other) const noexcept;

    /**
     * @brief Checks if this sphere intersects another sphere
     * @param other The sphere to test against
     * @return true if the spheres overlap
     */
    [[nodiscard]] bool intersects(const Sphere& other) const noexcept;

    /**
     * @brief Computes the closest point on this sphere to a given point
     * @param point The point to find the closest to
     * @return The closest point on the sphere surface
     */
    [[nodiscard]] Vec3f closestPoint(const Vec3f& point) const noexcept;

    /**
     * @brief Computes the distance from a point to the sphere surface
     * @param point The point to measure from
     * @return The distance (negative if inside)
     */
    [[nodiscard]] float signedDistanceToPoint(const Vec3f& point) const noexcept;

    /**
     * @brief Computes the distance from a point to the sphere surface
     * @param point The point to measure from
     * @return The absolute distance (0 if inside)
     */
    [[nodiscard]] float distanceToPoint(const Vec3f& point) const noexcept;
    /// @}

   public:
    /// @name Comparison Operators
    /// @{
    [[nodiscard]] bool operator==(const Sphere& other) const noexcept;
    [[nodiscard]] bool operator!=(const Sphere& other) const noexcept;
    /// @}

   public:
    friend std::ostream& operator<<(std::ostream& os, const Sphere& sphere);

   private:
    Vec3f center_;  ///< Center point of the sphere
    float radius_;  ///< Radius of the sphere
};

}  // namespace vne::math

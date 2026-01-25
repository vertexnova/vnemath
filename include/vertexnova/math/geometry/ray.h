#pragma once
/* ---------------------------------------------------------------------
 * Copyright (c) 2024 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Author:    Ajeet Singh Yadav
 * Created:   January 2025
 *
 * Autodoc:   yes
 * ----------------------------------------------------------------------
 */

/**
 * @file ray.h
 * @brief Defines the Ray class for ray-based operations in 3D space.
 */

// Project includes
#include "vertexnova/math/constants.h"
#include "vertexnova/math/vec3f.h"

// Standard library includes
#include <ostream>

namespace vne::math {

/**
 * @class Ray
 * @brief Represents a ray in 3D space.
 *
 * A ray is defined by an origin point and a direction, extending
 * infinitely in that direction. This is commonly used for raycasting,
 * picking, and intersection tests.
 */
class Ray {
   public:
    /**
     * @brief Default constructor, creates a ray at origin pointing along +Z
     */
    Ray() noexcept;

    /**
     * @brief Constructs a ray with the given origin and direction
     * @param origin The starting point of the ray
     * @param direction The direction of the ray (will be normalized)
     */
    Ray(const Vec3f& origin, const Vec3f& direction) noexcept;

    /** @brief Default destructor */
    ~Ray() noexcept = default;

    /** @brief Copy constructor */
    Ray(const Ray& other) noexcept = default;

    /** @brief Copy assignment operator */
    Ray& operator=(const Ray& other) noexcept = default;

   public:
    /**
     * @brief Gets a point along this ray at the given distance
     * @param distance The distance from origin along the ray
     * @return origin + direction * distance
     */
    [[nodiscard]] Vec3f getPoint(float distance) const noexcept;

    /**
     * @brief Computes the closest point on this ray to a given point
     * @param point The point to find the closest ray point to
     * @return The closest point on the ray
     */
    [[nodiscard]] Vec3f closestPoint(const Vec3f& point) const noexcept;

    /**
     * @brief Computes the closest point on this ray to a given point
     * @param point The point to find the closest ray point to
     * @param distance Output: the distance along the ray to the closest point
     * @return The closest point on the ray
     */
    [[nodiscard]] Vec3f closestPoint(const Vec3f& point, float& distance) const noexcept;

    /**
     * @brief Computes the distance from a point to this ray
     * @param point The point to measure distance from
     * @return The perpendicular distance from the point to the ray
     */
    [[nodiscard]] float distanceToPoint(const Vec3f& point) const noexcept;

   public:
    /**
     * @brief Compares this ray to another within a tolerance
     * @param other The other ray to compare against
     * @param eps The tolerance for comparison
     * @return true if rays are approximately equal
     */
    [[nodiscard]] bool areSame(const Ray& other, float eps = kFloatEpsilon) const noexcept;

   public:
    /**
     * @brief Sets the origin of this ray
     * @param origin The new origin point
     */
    void setOrigin(const Vec3f& origin) noexcept;

    /**
     * @brief Gets the origin of this ray
     * @return The origin point
     */
    [[nodiscard]] const Vec3f& origin() const noexcept;

    /**
     * @brief Sets the direction of this ray
     * @param direction The new direction (will be normalized)
     */
    void setDirection(const Vec3f& direction) noexcept;

    /**
     * @brief Gets the normalized direction of this ray
     * @return The direction vector
     */
    [[nodiscard]] const Vec3f& direction() const noexcept;

   public:
    /**
     * @brief Stream output operator
     * @param os The output stream
     * @param ray The ray to output
     * @return The output stream
     */
    friend std::ostream& operator<<(std::ostream& os, const Ray& ray);

   private:
    Vec3f origin_;     ///< The origin point of the ray
    Vec3f direction_;  ///< The normalized direction of the ray
};

}  // namespace vne::math

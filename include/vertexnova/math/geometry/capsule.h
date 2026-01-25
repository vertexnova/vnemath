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
 * @file capsule.h
 * @brief Defines the Capsule class for capsule (swept sphere) operations.
 */

#include "vertexnova/math/core/constants.h"
#include "vertexnova/math/core/vec.h"
#include "vertexnova/math/geometry/line_segment.h"

#include <ostream>

namespace vne::math {

// Forward declarations
class Aabb;
class Sphere;

/**
 * @class Capsule
 * @brief Represents a capsule (swept sphere / stadium) in 3D space.
 *
 * A capsule is defined by a line segment and a radius. It's the Minkowski
 * sum of a line segment and a sphere, resulting in a cylinder with
 * hemispherical caps.
 *
 * Common uses:
 * - Character collision (very common in games)
 * - Swept sphere collision detection
 * - Bone/limb collision in skeletal systems
 * - Fast approximation of elongated objects
 */
class Capsule {
   public:
    /**
     * @brief Default constructor. Creates a unit capsule along Y-axis.
     */
    Capsule() noexcept;

    /**
     * @brief Constructs a capsule from segment endpoints and radius.
     * @param start Start point of the central segment
     * @param end End point of the central segment
     * @param radius Radius of the capsule
     */
    Capsule(const Vec3f& start, const Vec3f& end, float radius) noexcept;

    /**
     * @brief Constructs a capsule from a line segment and radius.
     * @param segment The central line segment
     * @param radius Radius of the capsule
     */
    Capsule(const LineSegment& segment, float radius) noexcept;

    /** @brief Default destructor */
    ~Capsule() noexcept = default;

    /** @brief Copy constructor */
    Capsule(const Capsule& other) noexcept = default;

    /** @brief Copy assignment operator */
    Capsule& operator=(const Capsule& other) noexcept = default;

   public:
    /// @name Static Factory Methods
    /// @{

    /**
     * @brief Creates a capsule from center, height (total), and radius.
     * The capsule is oriented along the Y-axis.
     * @param center Center point of the capsule
     * @param height Total height including hemispherical caps
     * @param radius Radius of the capsule
     */
    [[nodiscard]] static Capsule fromCenterHeightRadius(const Vec3f& center, float height, float radius) noexcept;

    /**
     * @brief Creates a capsule from center, direction, segment length, and radius.
     * @param center Center point of the segment
     * @param direction Direction of the capsule axis (normalized)
     * @param segment_length Length of the central line segment
     * @param radius Radius of the capsule
     */
    [[nodiscard]] static Capsule fromCenterDirectionLengthRadius(const Vec3f& center,
                                                                 const Vec3f& direction,
                                                                 float segment_length,
                                                                 float radius) noexcept;
    /// @}

   public:
    /// @name Accessors
    /// @{

    /**
     * @brief Sets the start point.
     */
    void setStart(const Vec3f& start) noexcept;

    /**
     * @brief Gets the start point.
     */
    [[nodiscard]] const Vec3f& start() const noexcept;

    /**
     * @brief Sets the end point.
     */
    void setEnd(const Vec3f& end) noexcept;

    /**
     * @brief Gets the end point.
     */
    [[nodiscard]] const Vec3f& end() const noexcept;

    /**
     * @brief Sets the radius.
     */
    void setRadius(float radius) noexcept;

    /**
     * @brief Gets the radius.
     */
    [[nodiscard]] float radius() const noexcept;

    /**
     * @brief Gets the central line segment.
     */
    [[nodiscard]] LineSegment segment() const noexcept;
    /// @}

   public:
    /// @name Computed Properties
    /// @{

    /**
     * @brief Computes the center point of the capsule.
     */
    [[nodiscard]] Vec3f center() const noexcept;

    /**
     * @brief Computes the direction vector (from start to end).
     */
    [[nodiscard]] Vec3f direction() const noexcept;

    /**
     * @brief Computes the normalized direction vector.
     */
    [[nodiscard]] Vec3f normalizedDirection() const noexcept;

    /**
     * @brief Computes the length of the central segment.
     */
    [[nodiscard]] float segmentLength() const noexcept;

    /**
     * @brief Computes the total height (segment length + 2 * radius).
     */
    [[nodiscard]] float height() const noexcept;

    /**
     * @brief Computes the diameter (2 * radius).
     */
    [[nodiscard]] float diameter() const noexcept;

    /**
     * @brief Computes the volume of the capsule.
     * Volume = cylinder + 2 hemispheres = π*r²*h + (4/3)*π*r³
     */
    [[nodiscard]] float volume() const noexcept;

    /**
     * @brief Computes the surface area of the capsule.
     * Surface = cylinder lateral + sphere = 2*π*r*h + 4*π*r²
     */
    [[nodiscard]] float surfaceArea() const noexcept;

    /**
     * @brief Computes the AABB that bounds this capsule.
     */
    [[nodiscard]] Aabb getAabb() const noexcept;
    /// @}

   public:
    /// @name Modification Methods
    /// @{

    /**
     * @brief Translates the capsule by an offset.
     */
    void translate(const Vec3f& offset) noexcept;

    /**
     * @brief Grows the capsule radius by an amount.
     */
    void grow(float amount) noexcept;
    /// @}

   public:
    /// @name Query Methods
    /// @{

    /**
     * @brief Checks if this capsule is valid (positive radius and non-degenerate).
     */
    [[nodiscard]] bool isValid() const noexcept;

    /**
     * @brief Checks if the capsule is degenerate (zero-length segment, becomes sphere).
     */
    [[nodiscard]] bool isDegenerate(float epsilon = kFloatEpsilon) const noexcept;

    /**
     * @brief Checks if this capsule contains a point.
     */
    [[nodiscard]] bool contains(const Vec3f& point) const noexcept;

    /**
     * @brief Computes the closest point on this capsule surface to a given point.
     */
    [[nodiscard]] Vec3f closestPoint(const Vec3f& point) const noexcept;

    /**
     * @brief Computes the closest point on the central segment to a given point.
     */
    [[nodiscard]] Vec3f closestPointOnSegment(const Vec3f& point) const noexcept;

    /**
     * @brief Computes the squared distance from a point to this capsule.
     */
    [[nodiscard]] float squaredDistanceToPoint(const Vec3f& point) const noexcept;

    /**
     * @brief Computes the distance from a point to this capsule.
     */
    [[nodiscard]] float distanceToPoint(const Vec3f& point) const noexcept;

    /**
     * @brief Computes the signed distance (negative if inside).
     */
    [[nodiscard]] float signedDistanceToPoint(const Vec3f& point) const noexcept;

    /**
     * @brief Checks if this capsule intersects another capsule.
     */
    [[nodiscard]] bool intersects(const Capsule& other) const noexcept;

    /**
     * @brief Checks if this capsule intersects a sphere.
     */
    [[nodiscard]] bool intersects(const Sphere& sphere) const noexcept;
    /// @}

   public:
    /// @name Comparison Operators
    /// @{
    [[nodiscard]] bool operator==(const Capsule& other) const noexcept;
    [[nodiscard]] bool operator!=(const Capsule& other) const noexcept;

    [[nodiscard]] bool areSame(const Capsule& other, float epsilon = kFloatEpsilon) const noexcept;
    /// @}

   public:
    friend std::ostream& operator<<(std::ostream& os, const Capsule& capsule);

   private:
    Vec3f start_{Vec3f(0.0f, -0.5f, 0.0f)};  ///< Start point of segment
    Vec3f end_{Vec3f(0.0f, 0.5f, 0.0f)};     ///< End point of segment
    float radius_{0.5f};                     ///< Radius
};

}  // namespace vne::math

#pragma once
/* ---------------------------------------------------------------------
 * Copyright (c) 2024 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Author:    Ajeet Singh Yadav
 * Created:   August-2024
 *
 * Autodoc:   yes
 * ----------------------------------------------------------------------
 */

/**
 * @file vec2f.h
 * @brief Defines the Vec2f class for representing a two-dimensional vector
 *        with various mathematical operations.
 */

// Project includes
#include "constants.h"

// Third-party library includes
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/vec2.hpp>

// System library includes
#include <ostream>

namespace vne::math {

/**
 * @class Vec2f
 * @brief Represents a two-dimensional vector with float components.
 *
 * This class extends glm::vec2 and provides additional mathematical operations
 * commonly used in graphics and game development.
 */
class Vec2f : public glm::vec2 {
   public:
    /**
     * @brief Default constructor, initializes vector to (0, 0)
     */
    Vec2f() noexcept
        : glm::vec2(0.0f, 0.0f) {}

    /**
     * @brief Constructs a vector with specified x and y components
     * @param x_value The x component
     * @param y_value The y component
     */
    Vec2f(float x_value, float y_value) noexcept
        : glm::vec2(x_value, y_value) {}

    /**
     * @brief Constructs a vector with both components set to the same value
     * @param xy The value for both x and y components
     */
    Vec2f(const float xy) noexcept
        : glm::vec2(xy, xy) {}

    /**
     * @brief Copy constructor
     * @param v The vector to copy
     */
    Vec2f(const Vec2f& v) noexcept
        : glm::vec2(v) {}

    /**
     * @brief Constructs from a glm::vec2
     * @param v The glm::vec2 to copy
     */
    Vec2f(const glm::vec2& v) noexcept
        : glm::vec2(v.x, v.y) {}

   public:
    /**
     * @brief Gets a pointer to the underlying data
     * @return Pointer to the first component (x)
     */
    [[nodiscard]] float* getPtr() noexcept;

    /**
     * @brief Gets a const pointer to the underlying data
     * @return Const pointer to the first component (x)
     */
    [[nodiscard]] const float* getPtr() const noexcept;

   public:
    /**
     * @brief Returns a vector with absolute values of each component
     * @return Vector with abs(x) and abs(y)
     */
    [[nodiscard]] Vec2f abs() const noexcept;

    /**
     * @brief Calculates the Euclidean length (magnitude) of the vector
     * @return The length of the vector
     */
    [[nodiscard]] float length() const noexcept;

    /**
     * @brief Calculates the squared length of the vector
     * @return The squared length (avoids sqrt for performance)
     */
    [[nodiscard]] float lengthSquare() const noexcept;

    /**
     * @brief Returns a normalized (unit length) copy of this vector
     * @return Normalized vector
     * @throws Assertion failure if vector length is zero
     */
    [[nodiscard]] Vec2f normalize() const;

    /**
     * @brief Returns the component-wise minimum of this and another vector
     * @param v The other vector
     * @return Vector with smaller length
     */
    [[nodiscard]] Vec2f min(const Vec2f& v) const noexcept;

    /**
     * @brief Returns the component-wise maximum of this and another vector
     * @param v The other vector
     * @return Vector with larger length
     */
    [[nodiscard]] Vec2f max(const Vec2f& v) const noexcept;

    /**
     * @brief Returns the minimum component value
     * @return min(x, y)
     */
    [[nodiscard]] float minComponent() const noexcept;

    /**
     * @brief Returns the maximum component value
     * @return max(x, y)
     */
    [[nodiscard]] float maxComponent() const noexcept;

    /**
     * @brief Computes the dot product with another vector
     * @param v The other vector
     * @return The dot product (x*v.x + y*v.y)
     */
    [[nodiscard]] float dot(const Vec2f& v) const noexcept;

    /**
     * @brief Computes the 2D cross product (z-component of 3D cross)
     * @param v The other vector
     * @return The cross product (x*v.y - y*v.x)
     */
    [[nodiscard]] float cross(const Vec2f& v) const noexcept;

    /**
     * @brief Calculates the distance to another vector
     * @param v The other vector
     * @return The Euclidean distance between the two vectors
     */
    [[nodiscard]] float distance(const Vec2f& v) const noexcept;

    /**
     * @brief Rotates this vector around an axis by an angle
     * @param axis The rotation axis
     * @param angle The rotation angle in radians
     * @return The rotated vector
     */
    [[nodiscard]] Vec2f rotate(const Vec2f& axis, float angle) const noexcept;

    /**
     * @brief Reflects this vector about a normal
     * @param normal The surface normal (should be normalized)
     * @return The reflected vector
     */
    [[nodiscard]] Vec2f reflect(const Vec2f& normal) const noexcept;

    /**
     * @brief Refracts this vector through a surface
     * @param normal The surface normal
     * @param mu The ratio of indices of refraction
     * @return The refracted vector
     */
    [[nodiscard]] Vec2f refract(const Vec2f& normal, float mu) const noexcept;

    /**
     * @brief Projects this vector onto another vector
     * @param v The vector to project onto
     * @return The projection of this vector onto v
     */
    [[nodiscard]] Vec2f project(const Vec2f& v) const noexcept;

    /**
     * @brief Computes the rejection of this vector from another
     * @param v The vector to reject from
     * @return The component perpendicular to v
     */
    [[nodiscard]] Vec2f reject(const Vec2f& v) const noexcept;

    /**
     * @brief Decomposes this vector into parallel and perpendicular components
     * @param v The reference vector
     * @param proj Output: the projection onto v
     * @param perp Output: the perpendicular component
     */
    void decomposeVec(const Vec2f& v, Vec2f& proj, Vec2f& perp) const noexcept;

    /**
     * @brief Returns a vector perpendicular to this one
     * @return A perpendicular vector (-y, x)
     */
    [[nodiscard]] Vec2f perpendicular() const noexcept;

   public:
    /**
     * @brief Checks if two vectors are approximately equal
     * @param v The vector to compare against
     * @param eps The tolerance for comparison
     * @return true if vectors are within eps of each other
     */
    [[nodiscard]] bool areSame(const Vec2f& v, float eps = kFloatEpsilon) const noexcept;

    /**
     * @brief Checks if two vectors are parallel (same or opposite direction)
     * @param v The vector to compare against
     * @param eps The tolerance for the angle comparison
     * @return true if vectors are aligned
     */
    [[nodiscard]] bool areAligned(const Vec2f& v, float eps = kFloatEpsilon) const noexcept;

    /**
     * @brief Checks if this vector is approximately zero
     * @param eps The tolerance for comparison
     * @return true if all components are within eps of zero
     */
    [[nodiscard]] bool isZero(float eps = kFloatEpsilon) const noexcept;

    /**
     * @brief Checks if this vector is normalized (unit length)
     * @param eps The tolerance for comparison
     * @return true if length is within eps of 1.0
     */
    [[nodiscard]] bool isNormalized(float eps = kFloatEpsilon) const noexcept;

   public:
    /**
     * @brief Composes this vector from polar coordinates
     * @param radius The radial distance
     * @param angle The angle in radians
     * @return Reference to this vector
     */
    Vec2f& composePolar(float radius, float angle) noexcept;

    /**
     * @brief Decomposes this vector into polar coordinates
     * @param radius Output: the radial distance
     * @param angle Output: the angle in radians
     */
    void decomposePolar(float& radius, float& angle) const noexcept;

    /**
     * @brief Computes the angle of this vector from the positive x-axis
     * @return The angle in radians [0, 2π)
     */
    [[nodiscard]] float angle() const noexcept;

    /**
     * @brief Computes the angle between this vector and another
     * @param v The other vector
     * @return The angle in radians [0, 2π)
     */
    [[nodiscard]] float angle(const Vec2f& v) const noexcept;

    /**
     * @brief Computes the angle at this point in a triangle
     * @param p1 First point of the triangle
     * @param p2 Second point of the triangle
     * @return The angle in radians
     */
    [[nodiscard]] float angle(const Vec2f& p1, const Vec2f& p2) const noexcept;

   public:
    /**
     * @brief Computes the midpoint between this and another vector
     * @param point The other point
     * @return The midpoint
     */
    [[nodiscard]] Vec2f midPoint(const Vec2f& point) const noexcept;

    /**
     * @brief Linearly interpolates between this and another vector
     * @param point The target vector
     * @param factor The interpolation factor [0, 1]
     * @return The interpolated vector
     */
    [[nodiscard]] Vec2f lerp(Vec2f& point, float factor) const noexcept;

   public:
    /// @name Assignment Operators
    /// @{
    Vec2f& operator=(const Vec2f& v) noexcept;
    Vec2f& operator+=(const float& scalar) noexcept;
    Vec2f& operator-=(const float& scalar) noexcept;
    Vec2f& operator*=(const float& scalar) noexcept;
    Vec2f& operator/=(const float& scalar) noexcept;
    Vec2f& operator+=(const Vec2f& v) noexcept;
    Vec2f& operator-=(const Vec2f& v) noexcept;
    Vec2f& operator*=(const Vec2f& v) noexcept;
    Vec2f& operator/=(const Vec2f& v) noexcept;
    /// @}

    /// @name Arithmetic Operators
    /// @{
    [[nodiscard]] Vec2f operator+(const float& scalar) const noexcept;
    [[nodiscard]] Vec2f operator-(const float& scalar) const noexcept;
    [[nodiscard]] Vec2f operator*(const float& scalar) const noexcept;
    [[nodiscard]] Vec2f operator/(const float& scalar) const noexcept;
    [[nodiscard]] Vec2f operator+(const Vec2f& v) const noexcept;
    [[nodiscard]] Vec2f operator-(const Vec2f& v) const noexcept;
    [[nodiscard]] Vec2f operator*(const Vec2f& v) const noexcept;
    [[nodiscard]] Vec2f operator/(const Vec2f& v) const noexcept;
    /// @}

    /// @name Comparison Operators
    /// @{
    [[nodiscard]] bool operator==(const Vec2f& v) const noexcept;
    [[nodiscard]] bool operator!=(const Vec2f& v) const noexcept;
    [[nodiscard]] bool operator>(const Vec2f& v) const noexcept;
    [[nodiscard]] bool operator<(const Vec2f& v) const noexcept;
    /// @}

    /**
     * @brief Unary negation operator
     * @return Negated vector (-x, -y)
     */
    [[nodiscard]] Vec2f operator-() const noexcept;

    /// @name Subscript Operators
    /// @{
    [[nodiscard]] float& operator[](uint32_t index) noexcept;
    [[nodiscard]] float operator[](uint32_t index) const noexcept;
    /// @}

   public:
    /// @name Stream Operators
    /// @{
    friend std::ostream& operator<<(std::ostream& os, const Vec2f& vec);
    friend std::istream& operator>>(std::istream& is, Vec2f& vec);
    /// @}

   public:
    /// @name Static Factory Methods
    /// @{

    /**
     * @brief Returns the dimension of the vector
     * @return Always returns 2
     */
    [[nodiscard]] static uint32_t dim() noexcept;

    /**
     * @brief Returns the size of the vector
     * @return Always returns 2
     */
    [[nodiscard]] static uint32_t size() noexcept;

    /**
     * @brief Creates a zero vector
     * @return Vec2f(0, 0)
     */
    [[nodiscard]] static Vec2f zero() noexcept;

    /**
     * @brief Creates a vector with all components set to 1
     * @return Vec2f(1, 1)
     */
    [[nodiscard]] static Vec2f one() noexcept;

    /**
     * @brief Creates the x-axis unit vector
     * @return Vec2f(1, 0)
     */
    [[nodiscard]] static Vec2f xAxis() noexcept;

    /**
     * @brief Creates the y-axis unit vector
     * @return Vec2f(0, 1)
     */
    [[nodiscard]] static Vec2f yAxis() noexcept;

    /**
     * @brief Returns a normalized copy of a vector
     * @param v The vector to normalize
     * @return The normalized vector
     */
    [[nodiscard]] static Vec2f normalized(const Vec2f& v);

    /**
     * @brief Calculates the distance between two vectors
     * @param v1 First vector
     * @param v2 Second vector
     * @return The Euclidean distance
     */
    [[nodiscard]] static float distance(const Vec2f& v1, const Vec2f& v2) noexcept;

    /**
     * @brief Calculates the dot product of two vectors
     * @param v1 First vector
     * @param v2 Second vector
     * @return The dot product
     */
    [[nodiscard]] static float dot(const Vec2f& v1, const Vec2f& v2) noexcept;

    /**
     * @brief Calculates the 2D cross product of two vectors
     * @param v1 First vector
     * @param v2 Second vector
     * @return The cross product
     */
    [[nodiscard]] static float cross(const Vec2f& v1, const Vec2f& v2) noexcept;

    /**
     * @brief Calculates the midpoint between two vectors
     * @param p1 First point
     * @param p2 Second point
     * @return The midpoint
     */
    [[nodiscard]] static Vec2f midPoint(const Vec2f& p1, const Vec2f& p2) noexcept;

    /**
     * @brief Linearly interpolates between two vectors
     * @param p1 Start vector
     * @param p2 End vector
     * @param factor Interpolation factor [0, 1]
     * @return The interpolated vector
     */
    [[nodiscard]] static Vec2f lerp(const Vec2f& p1, const Vec2f& p2, float factor) noexcept;
    /// @}
};

}  // namespace vne::math

namespace {

[[nodiscard]] inline bool operator==(const vne::math::Vec2f& a, const glm::vec2& b) noexcept {
    return a.x == b.x && a.y == b.y;
}

[[nodiscard]] inline bool operator==(const glm::vec2& a, const vne::math::Vec2f& b) noexcept {
    return a.x == b.x && a.y == b.y;
}

}  // namespace

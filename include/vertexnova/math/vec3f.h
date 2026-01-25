#pragma once
/* ---------------------------------------------------------------------
 * Copyright (c) 2024 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Author:    Ajeet Singh Yadav
 * Created:   September-2024
 *
 * Autodoc:   yes
 * ----------------------------------------------------------------------
 */

/**
 * @file vec3f.h
 * @brief Defines the Vec3f class for representing a three-dimensional vector
 *        with various mathematical operations.
 */

// GLM Configuration
#ifndef GLM_ENABLE_EXPERIMENTAL
#define GLM_ENABLE_EXPERIMENTAL
#endif

// Project includes
#include "vec2f.h"

// Third-party library includes
#include <glm/vec3.hpp>

// Standard library includes
#include <ostream>

namespace vne::math {

/**
 * @class Vec3f
 * @brief Represents a three-dimensional vector with float components.
 *
 * This class extends glm::vec3 and provides additional mathematical operations
 * commonly used in graphics, physics, and game development.
 */
class Vec3f : public glm::vec3 {
   public:
    /**
     * @brief Default constructor, initializes vector to (0, 0, 0)
     */
    Vec3f() noexcept
        : glm::vec3(0.0f) {};

    /**
     * @brief Constructs a vector with specified x, y, and z components
     * @param x_value The x component
     * @param y_value The y component
     * @param z_value The z component
     */
    Vec3f(float x_value, float y_value, float z_value) noexcept
        : glm::vec3(x_value, y_value, z_value) {};

    /**
     * @brief Constructs a vector with all components set to the same value
     * @param xyz The value for all components
     */
    Vec3f(const float xyz) noexcept
        : glm::vec3(xyz) {};

    /**
     * @brief Copy constructor
     * @param v The vector to copy
     */
    Vec3f(const Vec3f& v) noexcept
        : glm::vec3(v) {};

    /**
     * @brief Constructs from a glm::vec3
     * @param v The glm::vec3 to copy
     */
    Vec3f(const glm::vec3& v) noexcept
        : glm::vec3(v.x, v.y, v.z) {};

    /**
     * @brief Constructs from a Vec2f with z = 0
     * @param v The 2D vector
     */
    Vec3f(const Vec2f& v) noexcept
        : glm::vec3(v.x, v.y, 0.0f) {};

    /**
     * @brief Constructs from a glm::vec2 with z = 0
     * @param v The 2D vector
     */
    Vec3f(const glm::vec2& v) noexcept
        : glm::vec3(v.x, v.y, 0.0f) {};

    /**
     * @brief Constructs from a Vec2f and a z value
     * @param v The 2D vector for x and y
     * @param z_value The z component
     */
    Vec3f(const Vec2f& v, float z_value) noexcept
        : glm::vec3(v, z_value) {};

    /**
     * @brief Constructs from a glm::vec2 and a z value
     * @param v The 2D vector for x and y
     * @param z_value The z component
     */
    Vec3f(const glm::vec2& v, float z_value) noexcept
        : glm::vec3(v, z_value) {};

    /**
     * @brief Returns the x and y components as a Vec2f
     * @return Vec2f containing (x, y)
     */
    [[nodiscard]] Vec2f xy() noexcept;

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
     * @return Vector with abs(x), abs(y), abs(z)
     */
    [[nodiscard]] Vec3f abs() const noexcept;

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
    [[nodiscard]] Vec3f normalize() const;

    /**
     * @brief Returns the vector with smaller length
     * @param v The other vector
     * @return Vector with smaller length
     */
    [[nodiscard]] Vec3f min(const Vec3f& v) const noexcept;

    /**
     * @brief Returns the vector with larger length
     * @param v The other vector
     * @return Vector with larger length
     */
    [[nodiscard]] Vec3f max(const Vec3f& v) const noexcept;

    /**
     * @brief Returns the minimum component value
     * @return min(x, y, z)
     */
    [[nodiscard]] float minComponent() const noexcept;

    /**
     * @brief Returns the maximum component value
     * @return max(x, y, z)
     */
    [[nodiscard]] float maxComponent() const noexcept;

    /**
     * @brief Computes the dot product with another vector
     * @param v The other vector
     * @return The dot product
     */
    [[nodiscard]] float dot(const Vec3f& v) const noexcept;

    /**
     * @brief Computes the cross product with another vector
     * @param v The other vector
     * @return The cross product vector
     */
    [[nodiscard]] Vec3f cross(const Vec3f& v) const noexcept;

    /**
     * @brief Calculates the distance to another vector
     * @param v The other vector
     * @return The Euclidean distance
     */
    [[nodiscard]] float distance(const Vec3f& v) const noexcept;

    /**
     * @brief Rotates this vector around an axis by an angle
     * @param axis The rotation axis (should be normalized)
     * @param angle The rotation angle in radians
     * @return The rotated vector
     */
    [[nodiscard]] Vec3f rotate(const Vec3f& axis, float angle) const noexcept;

    /**
     * @brief Reflects this vector about a normal
     * @param normal The surface normal (should be normalized)
     * @return The reflected vector
     */
    [[nodiscard]] Vec3f reflect(const Vec3f& normal) const noexcept;

    /**
     * @brief Refracts this vector through a surface
     * @param normal The surface normal
     * @param mu The ratio of indices of refraction
     * @return The refracted vector
     */
    [[nodiscard]] Vec3f refract(const Vec3f& normal, float mu) const noexcept;

    /**
     * @brief Projects this vector onto another vector
     * @param v The vector to project onto
     * @return The projection of this vector onto v
     */
    [[nodiscard]] Vec3f project(const Vec3f& v) const noexcept;

    /**
     * @brief Computes the rejection of this vector from another
     * @param v The vector to reject from
     * @return The component perpendicular to v
     */
    [[nodiscard]] Vec3f reject(const Vec3f& v) const noexcept;

    /**
     * @brief Decomposes this vector into parallel and perpendicular components
     * @param v The reference vector
     * @param proj Output: the projection onto v
     * @param perp Output: the perpendicular component
     */
    void decomposeVec(const Vec3f& v, Vec3f& proj, Vec3f& perp) const noexcept;

    /**
     * @brief Returns a vector perpendicular to this and another vector
     * @param v The other vector
     * @return A perpendicular vector (cross product)
     */
    [[nodiscard]] Vec3f perpendicular(const Vec3f& v) const noexcept;

   public:
    /**
     * @brief Checks if two vectors are approximately equal
     * @param v The vector to compare against
     * @param eps The tolerance for comparison
     * @return true if vectors are within eps of each other
     */
    [[nodiscard]] bool areSame(const Vec3f& v, float eps = kFloatEpsilon) const noexcept;

    /**
     * @brief Checks if two vectors are parallel
     * @param v The vector to compare against
     * @param eps The tolerance for the angle comparison
     * @return true if vectors are aligned
     */
    [[nodiscard]] bool areAligned(const Vec3f& v, float eps = kFloatEpsilon) const noexcept;

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

    /**
     * @brief Checks if three points are linearly dependent
     * @param p1 Second point
     * @param p2 Third point
     * @param eps The tolerance
     * @return true if points are collinear
     */
    [[nodiscard]] bool isLinearDependent(const Vec3f& p1, const Vec3f& p2, float eps = kFloatEpsilon) const noexcept;

    /**
     * @brief Checks if two vectors are linearly dependent
     * @param v The other vector
     * @param eps The tolerance
     * @return true if vectors are parallel
     */
    [[nodiscard]] bool isLinearDependent(const Vec3f& v, float eps = kFloatEpsilon) const noexcept;

   public:
    /**
     * @brief Composes this vector from spherical coordinates
     * @param rho The radial distance
     * @param theta The azimuthal angle (in xy plane from x-axis)
     * @param phi The polar angle (from z-axis)
     * @return Reference to this vector
     */
    Vec3f& composeSpherical(float rho, float theta, float phi) noexcept;

    /**
     * @brief Decomposes this vector into spherical coordinates
     * @param rho Output: the radial distance
     * @param theta Output: the azimuthal angle
     * @param phi Output: the polar angle
     */
    void decomposeSpherical(float& rho, float& theta, float& phi) const noexcept;

    /**
     * @brief Composes this vector from cylindrical coordinates
     * @param radius The radial distance in xy plane
     * @param angle The angle in xy plane
     * @param height The z coordinate
     * @return Reference to this vector
     */
    Vec3f& composeCylindrical(float radius, float angle, float height) noexcept;

    /**
     * @brief Decomposes this vector into cylindrical coordinates
     * @param radius Output: the radial distance
     * @param angle Output: the angle in radians
     * @param height Output: the z coordinate
     */
    void decomposeCylindrical(float& radius, float& angle, float& height) const noexcept;

    /**
     * @brief Computes the angle between this vector and another
     * @param v The other vector
     * @return The angle in radians
     */
    [[nodiscard]] float angle(const Vec3f& v) const noexcept;

    /**
     * @brief Computes the angle at this point in a triangle
     * @param p1 First point
     * @param p2 Second point
     * @return The angle in radians
     */
    [[nodiscard]] float angle(const Vec3f& p1, const Vec3f& p2) const noexcept;

   public:
    /**
     * @brief Computes the midpoint between this and another vector
     * @param point The other point
     * @return The midpoint
     */
    [[nodiscard]] Vec3f midPoint(const Vec3f& point) const noexcept;

    /**
     * @brief Linearly interpolates between this and another vector
     * @param point The target vector
     * @param factor The interpolation factor [0, 1]
     * @return The interpolated vector
     */
    [[nodiscard]] Vec3f lerp(Vec3f& point, float factor) const noexcept;

   public:
    /// @name Assignment Operators
    /// @{
    Vec3f& operator=(const Vec3f& v) noexcept;
    Vec3f& operator+=(float scalar) noexcept;
    Vec3f& operator-=(float scalar) noexcept;
    Vec3f& operator*=(float scalar) noexcept;
    Vec3f& operator/=(float scalar) noexcept;
    Vec3f& operator+=(const Vec3f& v) noexcept;
    Vec3f& operator-=(const Vec3f& v) noexcept;
    Vec3f& operator*=(const Vec3f& v) noexcept;
    Vec3f& operator/=(const Vec3f& v) noexcept;
    /// @}

    /// @name Arithmetic Operators
    /// @{
    [[nodiscard]] Vec3f operator+(float scalar) const noexcept;
    [[nodiscard]] Vec3f operator-(float scalar) const noexcept;
    [[nodiscard]] Vec3f operator*(float scalar) const noexcept;
    [[nodiscard]] Vec3f operator/(float scalar) const noexcept;
    [[nodiscard]] Vec3f operator+(const Vec3f& v) const noexcept;
    [[nodiscard]] Vec3f operator-(const Vec3f& v) const noexcept;
    [[nodiscard]] Vec3f operator*(const Vec3f& v) const noexcept;
    [[nodiscard]] Vec3f operator/(const Vec3f& v) const noexcept;
    /// @}

    /// @name Comparison Operators
    /// @{
    [[nodiscard]] bool operator==(const Vec3f& v) const noexcept;
    [[nodiscard]] bool operator!=(const Vec3f& v) const noexcept;
    [[nodiscard]] bool operator>(const Vec3f& v) const noexcept;
    [[nodiscard]] bool operator<(const Vec3f& v) const noexcept;
    /// @}

    /**
     * @brief Unary negation operator
     * @return Negated vector
     */
    [[nodiscard]] Vec3f operator-() const noexcept;

    /// @name Subscript Operators
    /// @{
    [[nodiscard]] float& operator[](uint32_t index) noexcept;
    [[nodiscard]] float operator[](uint32_t index) const noexcept;
    /// @}

   public:
    /// @name Stream Operators
    /// @{
    friend std::ostream& operator<<(std::ostream& os, const Vec3f& vec);
    friend std::istream& operator>>(std::istream& is, Vec3f& vec);
    /// @}

   public:
    /// @name Static Factory Methods
    /// @{

    /** @brief Returns the dimension (3) */
    [[nodiscard]] static uint32_t dim() noexcept;

    /** @brief Returns the size (3) */
    [[nodiscard]] static uint32_t size() noexcept;

    /** @brief Creates a zero vector (0, 0, 0) */
    [[nodiscard]] static Vec3f zero() noexcept;

    /** @brief Creates a one vector (1, 1, 1) */
    [[nodiscard]] static Vec3f one() noexcept;

    /** @brief Creates the x-axis unit vector (1, 0, 0) */
    [[nodiscard]] static Vec3f xAxis() noexcept;

    /** @brief Creates the y-axis unit vector (0, 1, 0) */
    [[nodiscard]] static Vec3f yAxis() noexcept;

    /** @brief Creates the z-axis unit vector (0, 0, 1) */
    [[nodiscard]] static Vec3f zAxis() noexcept;

    /** @brief Creates the up direction vector (0, 1, 0) */
    [[nodiscard]] static Vec3f up() noexcept;

    /** @brief Creates the down direction vector (0, -1, 0) */
    [[nodiscard]] static Vec3f down() noexcept;

    /** @brief Creates the left direction vector (-1, 0, 0) */
    [[nodiscard]] static Vec3f left() noexcept;

    /** @brief Creates the right direction vector (1, 0, 0) */
    [[nodiscard]] static Vec3f right() noexcept;

    /** @brief Creates the forward direction vector (0, 0, -1) */
    [[nodiscard]] static Vec3f forward() noexcept;

    /** @brief Creates the backward direction vector (0, 0, 1) */
    [[nodiscard]] static Vec3f backward() noexcept;

    /**
     * @brief Returns a normalized copy of a vector
     * @param v The vector to normalize
     * @return The normalized vector
     */
    [[nodiscard]] static Vec3f normalized(const Vec3f& v);

    /**
     * @brief Calculates the distance between two vectors
     * @param v1 First vector
     * @param v2 Second vector
     * @return The Euclidean distance
     */
    [[nodiscard]] static float distance(const Vec3f& v1, const Vec3f& v2) noexcept;

    /**
     * @brief Calculates the dot product of two vectors
     * @param v1 First vector
     * @param v2 Second vector
     * @return The dot product
     */
    [[nodiscard]] static float dot(const Vec3f& v1, const Vec3f& v2) noexcept;

    /**
     * @brief Calculates the cross product of two vectors
     * @param v1 First vector
     * @param v2 Second vector
     * @return The cross product
     */
    [[nodiscard]] static Vec3f cross(const Vec3f& v1, const Vec3f& v2) noexcept;

    /**
     * @brief Calculates the midpoint between two vectors
     * @param p1 First point
     * @param p2 Second point
     * @return The midpoint
     */
    [[nodiscard]] static Vec3f midPoint(const Vec3f& p1, const Vec3f& p2) noexcept;

    /**
     * @brief Linearly interpolates between two vectors
     * @param p1 Start vector
     * @param p2 End vector
     * @param factor Interpolation factor [0, 1]
     * @return The interpolated vector
     */
    [[nodiscard]] static Vec3f lerp(const Vec3f& p1, const Vec3f& p2, float factor) noexcept;
    /// @}
};

}  // namespace vne::math

namespace {

[[nodiscard]] inline bool operator==(const vne::math::Vec3f& a, const glm::vec3& b) noexcept {
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

[[nodiscard]] inline bool operator==(const glm::vec3& a, const vne::math::Vec3f& b) noexcept {
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

}  // namespace

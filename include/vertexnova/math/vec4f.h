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
 * @file vec4f.h
 * @brief Defines the Vec4f class for representing a four-dimensional vector
 *        with various mathematical operations.
 */

// Project includes
#include "vec3f.h"

// Third-party library includes
#include <glm/vec4.hpp>

// Standard library includes
#include <ostream>

namespace vne::math {

/**
 * @class Vec4f
 * @brief Represents a four-dimensional vector with float components.
 *
 * This class extends glm::vec4 and provides additional mathematical operations
 * commonly used in graphics for homogeneous coordinates and color representation.
 */
class Vec4f : public glm::vec4 {
   public:
    /** @brief Default constructor, initializes to (0, 0, 0, 0) */
    Vec4f() noexcept
        : glm::vec4(0.0f) {}

    /**
     * @brief Constructs a vector with specified components
     * @param x_value The x component
     * @param y_value The y component
     * @param z_value The z component
     * @param w_value The w component
     */
    Vec4f(float x_value, float y_value, float z_value, float w_value) noexcept
        : glm::vec4(x_value, y_value, z_value, w_value) {}

    /**
     * @brief Constructs a vector with all components set to the same value
     * @param xyzw The value for all components
     */
    Vec4f(float xyzw) noexcept
        : glm::vec4(xyzw) {}

    /** @brief Copy constructor */
    Vec4f(const Vec4f& v) noexcept
        : glm::vec4(v) {}

    /** @brief Constructs from a glm::vec4 */
    Vec4f(const glm::vec4& v) noexcept
        : glm::vec4(v.x, v.y, v.z, v.w) {}

    /** @brief Constructs from a Vec3f with w = 0 */
    Vec4f(const Vec3f& v) noexcept
        : glm::vec4(v.x, v.y, v.z, 0.0f) {}

    /** @brief Constructs from a glm::vec3 with w = 0 */
    Vec4f(const glm::vec3& v) noexcept
        : glm::vec4(v.x, v.y, v.z, 0.0f) {}

    /** @brief Constructs from a Vec2f with z = w = 0 */
    Vec4f(const Vec2f& v) noexcept
        : glm::vec4(v.x, v.y, 0.0f, 0.0f) {}

    /** @brief Constructs from a glm::vec2 with z = w = 0 */
    Vec4f(const glm::vec2& v) noexcept
        : glm::vec4(v.x, v.y, 0.0f, 0.0f) {}

    /**
     * @brief Constructs from a Vec3f and a w value
     * @param v The 3D vector for x, y, z
     * @param w_value The w component
     */
    Vec4f(const Vec3f& v, float w_value) noexcept
        : glm::vec4(v, w_value) {}

    /**
     * @brief Constructs from a glm::vec3 and a w value
     * @param v The 3D vector for x, y, z
     * @param w_value The w component
     */
    Vec4f(const glm::vec3& v, float w_value) noexcept
        : glm::vec4(v, w_value) {}

    /**
     * @brief Returns the x, y, z components as a Vec3f
     * @return Vec3f containing (x, y, z)
     */
    [[nodiscard]] Vec3f xyz() noexcept;

    /**
     * @brief Returns the x and y components as a Vec2f
     * @return Vec2f containing (x, y)
     */
    [[nodiscard]] Vec2f xy() noexcept;

   public:
    /** @brief Gets a pointer to the underlying data */
    [[nodiscard]] float* getPtr() noexcept;

    /** @brief Gets a const pointer to the underlying data */
    [[nodiscard]] const float* getPtr() const noexcept;

   public:
    /** @brief Returns a vector with absolute values of each component */
    [[nodiscard]] Vec4f abs() const noexcept;

    /** @brief Calculates the Euclidean length of the vector */
    [[nodiscard]] float length() const noexcept;

    /** @brief Calculates the squared length of the vector */
    [[nodiscard]] float lengthSquare() const noexcept;

    /**
     * @brief Returns a normalized copy of this vector
     * @throws Assertion failure if vector length is zero
     */
    [[nodiscard]] Vec4f normalize() const;

    /** @brief Returns the vector with smaller length */
    [[nodiscard]] Vec4f min(const Vec4f& v) const noexcept;

    /** @brief Returns the vector with larger length */
    [[nodiscard]] Vec4f max(const Vec4f& v) const noexcept;

    /** @brief Returns the minimum component value */
    [[nodiscard]] float minComponent() const noexcept;

    /** @brief Returns the maximum component value */
    [[nodiscard]] float maxComponent() const noexcept;

    /** @brief Computes the dot product with another vector */
    [[nodiscard]] float dot(const Vec4f& v) const noexcept;

    /** @brief Calculates the distance to another vector */
    [[nodiscard]] float distance(const Vec4f& v) const noexcept;

    /**
     * @brief Rotates this vector around an axis
     * @param axis The rotation axis (3D)
     * @param angle The rotation angle in radians
     * @return The rotated vector
     */
    [[nodiscard]] Vec4f rotate(const Vec3f& axis, float angle) const noexcept;

    /** @brief Reflects this vector about a normal */
    [[nodiscard]] Vec4f reflect(const Vec4f& normal) const noexcept;

    /** @brief Refracts this vector through a surface */
    [[nodiscard]] Vec4f refract(const Vec4f& normal, float mu) const noexcept;

    /** @brief Projects this vector onto another vector */
    [[nodiscard]] Vec4f project(const Vec4f& v) const noexcept;

    /** @brief Computes the rejection of this vector from another */
    [[nodiscard]] Vec4f reject(const Vec4f& v) const noexcept;

    /** @brief Decomposes into parallel and perpendicular components */
    void decomposeVec(const Vec4f& v, Vec4f& proj, Vec4f& perp) const noexcept;

   public:
    /** @brief Checks if two vectors are approximately equal */
    [[nodiscard]] bool areSame(const Vec4f& v, float eps = kFloatEpsilon) const noexcept;

    /** @brief Checks if two vectors are parallel */
    [[nodiscard]] bool areAligned(const Vec4f& v, float eps = kFloatEpsilon) const noexcept;

    /** @brief Checks if this vector is approximately zero */
    [[nodiscard]] bool isZero(float eps = kFloatEpsilon) const noexcept;

    /** @brief Checks if this vector is normalized */
    [[nodiscard]] bool isNormalized(float eps = kFloatEpsilon) const noexcept;

   public:
    /** @brief Computes the angle between this vector and another */
    [[nodiscard]] float angle(const Vec4f& v) const noexcept;

    /** @brief Computes the angle at this point in a triangle */
    [[nodiscard]] float angle(const Vec4f& p1, const Vec4f& p2) const noexcept;

   public:
    /** @brief Computes the midpoint between this and another vector */
    [[nodiscard]] Vec4f midPoint(const Vec4f& point) const noexcept;

    /** @brief Linearly interpolates between this and another vector */
    [[nodiscard]] Vec4f lerp(const Vec4f& point, float factor) const noexcept;

   public:
    /// @name Assignment Operators
    /// @{
    Vec4f& operator=(const Vec4f& v) noexcept;
    Vec4f& operator+=(float scalar) noexcept;
    Vec4f& operator-=(float scalar) noexcept;
    Vec4f& operator*=(float scalar) noexcept;
    Vec4f& operator/=(float scalar) noexcept;
    Vec4f& operator+=(const Vec4f& v) noexcept;
    Vec4f& operator-=(const Vec4f& v) noexcept;
    Vec4f& operator*=(const Vec4f& v) noexcept;
    Vec4f& operator/=(const Vec4f& v) noexcept;
    /// @}

    /// @name Arithmetic Operators
    /// @{
    [[nodiscard]] Vec4f operator+(float scalar) const noexcept;
    [[nodiscard]] Vec4f operator-(float scalar) const noexcept;
    [[nodiscard]] Vec4f operator*(float scalar) const noexcept;
    [[nodiscard]] Vec4f operator/(float scalar) const noexcept;
    [[nodiscard]] Vec4f operator+(const Vec4f& v) const noexcept;
    [[nodiscard]] Vec4f operator-(const Vec4f& v) const noexcept;
    [[nodiscard]] Vec4f operator*(const Vec4f& v) const noexcept;
    [[nodiscard]] Vec4f operator/(const Vec4f& v) const noexcept;
    /// @}

    /// @name Comparison Operators
    /// @{
    [[nodiscard]] bool operator==(const Vec4f& v) const noexcept;
    [[nodiscard]] bool operator!=(const Vec4f& v) const noexcept;
    [[nodiscard]] bool operator>(const Vec4f& v) const noexcept;
    [[nodiscard]] bool operator<(const Vec4f& v) const noexcept;
    /// @}

    /** @brief Unary negation operator */
    [[nodiscard]] Vec4f operator-() const noexcept;

    /// @name Subscript Operators
    /// @{
    [[nodiscard]] float& operator[](uint32_t index) noexcept;
    [[nodiscard]] float operator[](uint32_t index) const noexcept;
    /// @}

   public:
    /// @name Stream Operators
    /// @{
    friend std::ostream& operator<<(std::ostream& os, const Vec4f& vec);
    friend std::istream& operator>>(std::istream& is, Vec4f& vec);
    /// @}

   public:
    /// @name Static Factory Methods
    /// @{
    [[nodiscard]] static uint32_t dim() noexcept;
    [[nodiscard]] static uint32_t size() noexcept;
    [[nodiscard]] static Vec4f zero() noexcept;
    [[nodiscard]] static Vec4f one() noexcept;
    [[nodiscard]] static Vec4f xAxis() noexcept;
    [[nodiscard]] static Vec4f yAxis() noexcept;
    [[nodiscard]] static Vec4f zAxis() noexcept;
    [[nodiscard]] static Vec4f wAxis() noexcept;
    [[nodiscard]] static Vec4f normalized(const Vec4f& v);
    [[nodiscard]] static float distance(const Vec4f& v1, const Vec4f& v2) noexcept;
    [[nodiscard]] static float dot(const Vec4f& v1, const Vec4f& v2) noexcept;
    [[nodiscard]] static Vec4f midPoint(const Vec4f& p1, const Vec4f& p2) noexcept;
    [[nodiscard]] static Vec4f lerp(const Vec4f& p1, const Vec4f& p2, float t) noexcept;
    /// @}
};

}  // namespace vne::math

namespace {

[[nodiscard]] inline bool operator==(const vne::math::Vec4f& a, const glm::vec4& b) noexcept {
    return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
}

[[nodiscard]] inline bool operator==(const glm::vec4& a, const vne::math::Vec4f& b) noexcept {
    return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
}

}  // namespace

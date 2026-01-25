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
 * @file vec.h
 * @brief Templated vector class for N-dimensional vectors.
 *
 * This file provides a generic Vec<T, N> class that supports:
 * - Any arithmetic type (float, double, int, etc.)
 * - Any dimension (2, 3, 4, or higher)
 * - SIMD optimization via GLM backend for float/double
 * - C++20 concepts for type safety
 */

#include "types.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <istream>
#include <ostream>

// GLM for optimized operations (optional backend)
#include <glm/geometric.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace vne::math {

/**
 * @class Vec
 * @brief A generic N-dimensional vector class.
 *
 * @tparam T The scalar type (must satisfy Arithmetic concept)
 * @tparam N The number of dimensions
 *
 * @example
 * ```cpp
 * Vec3f pos(1.0f, 2.0f, 3.0f);
 * Vec3f dir = pos.normalized();
 * float len = pos.length();
 * ```
 */
template<typename T, size_t N>
    requires Arithmetic<T>
class Vec {
   public:
    using value_type = T;
    using size_type = size_t;
    static constexpr size_type dimensions = N;

    /// @brief Data storage
    std::array<T, N> data{};

   public:
    // ========================================================================
    // Constructors
    // ========================================================================

    /**
     * @brief Default constructor, initializes all components to zero.
     */
    constexpr Vec() noexcept = default;

    /**
     * @brief Constructs a vector with all components set to the same value.
     * @param scalar The value for all components
     */
    constexpr explicit Vec(T scalar) noexcept { data.fill(scalar); }

    /**
     * @brief Constructs a 2D vector from components.
     */
    constexpr Vec(T x, T y) noexcept
        requires(N == 2)
        : data{x, y} {}

    /**
     * @brief Constructs a 3D vector from components.
     */
    constexpr Vec(T x, T y, T z) noexcept
        requires(N == 3)
        : data{x, y, z} {}

    /**
     * @brief Constructs a 4D vector from components.
     */
    constexpr Vec(T x, T y, T z, T w) noexcept
        requires(N == 4)
        : data{x, y, z, w} {}

    /**
     * @brief Constructs a 3D vector from a 2D vector and a z component.
     */
    constexpr Vec(const Vec<T, 2>& xy, T z) noexcept
        requires(N == 3)
        : data{xy.data[0], xy.data[1], z} {}

    /**
     * @brief Constructs a 3D vector from a 2D vector with z = 0.
     */
    constexpr explicit Vec(const Vec<T, 2>& xy) noexcept
        requires(N == 3)
        : data{xy.data[0], xy.data[1], T(0)} {}

    /**
     * @brief Constructs a 4D vector from a 3D vector and a w component.
     */
    constexpr Vec(const Vec<T, 3>& xyz, T w) noexcept
        requires(N == 4)
        : data{xyz.data[0], xyz.data[1], xyz.data[2], w} {}

    /**
     * @brief Constructs a 4D vector from a 3D vector with w = 0.
     */
    constexpr explicit Vec(const Vec<T, 3>& xyz) noexcept
        requires(N == 4)
        : data{xyz.data[0], xyz.data[1], xyz.data[2], T(0)} {}

    /**
     * @brief Constructs a 4D vector from a 2D vector with z = w = 0.
     */
    constexpr explicit Vec(const Vec<T, 2>& xy) noexcept
        requires(N == 4)
        : data{xy.data[0], xy.data[1], T(0), T(0)} {}

    /**
     * @brief Constructs a 4D vector from a 2D vector and z, w components.
     */
    constexpr Vec(const Vec<T, 2>& xy, T z, T w) noexcept
        requires(N == 4)
        : data{xy.data[0], xy.data[1], z, w} {}

    /**
     * @brief Copy constructor.
     */
    constexpr Vec(const Vec& other) noexcept = default;

    /**
     * @brief Move constructor.
     */
    constexpr Vec(Vec&& other) noexcept = default;

    /**
     * @brief Copy assignment.
     */
    constexpr Vec& operator=(const Vec& other) noexcept = default;

    /**
     * @brief Move assignment.
     */
    constexpr Vec& operator=(Vec&& other) noexcept = default;

    /**
     * @brief Destructor.
     */
    ~Vec() noexcept = default;

    // ========================================================================
    // GLM Interoperability
    // ========================================================================

    /**
     * @brief Constructs from glm::vec2.
     */
    constexpr Vec(const glm::vec<2, T>& v) noexcept
        requires(N == 2 && (std::is_same_v<T, float> || std::is_same_v<T, double>))
        : data{v.x, v.y} {}

    /**
     * @brief Constructs from glm::vec3.
     */
    constexpr Vec(const glm::vec<3, T>& v) noexcept
        requires(N == 3 && (std::is_same_v<T, float> || std::is_same_v<T, double>))
        : data{v.x, v.y, v.z} {}

    /**
     * @brief Constructs from glm::vec4.
     */
    constexpr Vec(const glm::vec<4, T>& v) noexcept
        requires(N == 4 && (std::is_same_v<T, float> || std::is_same_v<T, double>))
        : data{v.x, v.y, v.z, v.w} {}

    /**
     * @brief Implicit conversion to glm::vec for seamless GLM interoperability.
     *
     * This is implicit (not explicit) to allow Vec to be used directly with
     * GLM functions without requiring casts.
     */
    [[nodiscard]] constexpr operator glm::vec<N, T>() const noexcept
        requires(N >= 2 && N <= 4 && (std::is_same_v<T, float> || std::is_same_v<T, double>))
    {
        if constexpr (N == 2) {
            return glm::vec<2, T>(data[0], data[1]);
        } else if constexpr (N == 3) {
            return glm::vec<3, T>(data[0], data[1], data[2]);
        } else {
            return glm::vec<4, T>(data[0], data[1], data[2], data[3]);
        }
    }

    /**
     * @brief Implicit conversion to glm::vec2 from 3D/4D vectors (takes xy).
     */
    [[nodiscard]] constexpr operator glm::vec<2, T>() const noexcept
        requires(N >= 3 && N <= 4 && (std::is_same_v<T, float> || std::is_same_v<T, double>))
    {
        return glm::vec<2, T>(data[0], data[1]);
    }

    /**
     * @brief Implicit conversion to glm::vec3 from 4D vectors (takes xyz).
     */
    [[nodiscard]] constexpr operator glm::vec<3, T>() const noexcept
        requires(N == 4 && (std::is_same_v<T, float> || std::is_same_v<T, double>))
    {
        return glm::vec<3, T>(data[0], data[1], data[2]);
    }

    // ========================================================================
    // Element Access
    // ========================================================================

    /**
     * @brief Accesses element by index.
     */
    [[nodiscard]] constexpr T& operator[](size_type i) noexcept { return data[i]; }

    /**
     * @brief Accesses element by index (const).
     */
    [[nodiscard]] constexpr const T& operator[](size_type i) const noexcept { return data[i]; }

    /**
     * @brief Returns a pointer to the underlying data.
     */
    [[nodiscard]] constexpr T* ptr() noexcept { return data.data(); }

    /**
     * @brief Returns a const pointer to the underlying data.
     */
    [[nodiscard]] constexpr const T* ptr() const noexcept { return data.data(); }

    /**
     * @brief Gets a pointer to the underlying data (alias for ptr).
     */
    [[nodiscard]] constexpr T* getPtr() noexcept { return data.data(); }

    /**
     * @brief Gets a const pointer to the underlying data (alias for ptr).
     */
    [[nodiscard]] constexpr const T* getPtr() const noexcept { return data.data(); }

    /// @name Named Accessors
    /// @{

    [[nodiscard]] constexpr T& x() noexcept
        requires(N >= 1)
    {
        return data[0];
    }

    [[nodiscard]] constexpr const T& x() const noexcept
        requires(N >= 1)
    {
        return data[0];
    }

    [[nodiscard]] constexpr T& y() noexcept
        requires(N >= 2)
    {
        return data[1];
    }

    [[nodiscard]] constexpr const T& y() const noexcept
        requires(N >= 2)
    {
        return data[1];
    }

    [[nodiscard]] constexpr T& z() noexcept
        requires(N >= 3)
    {
        return data[2];
    }

    [[nodiscard]] constexpr const T& z() const noexcept
        requires(N >= 3)
    {
        return data[2];
    }

    [[nodiscard]] constexpr T& w() noexcept
        requires(N >= 4)
    {
        return data[3];
    }

    [[nodiscard]] constexpr const T& w() const noexcept
        requires(N >= 4)
    {
        return data[3];
    }

    /// @}

    /// @name Swizzle Accessors
    /// @{

    [[nodiscard]] constexpr Vec<T, 2> xy() const noexcept
        requires(N >= 2)
    {
        return Vec<T, 2>(data[0], data[1]);
    }

    [[nodiscard]] constexpr Vec<T, 3> xyz() const noexcept
        requires(N >= 3)
    {
        return Vec<T, 3>(data[0], data[1], data[2]);
    }

    /// @}

    // ========================================================================
    // Geometric Operations
    // ========================================================================

    /**
     * @brief Calculates the squared length (magnitude) of the vector.
     * @return The squared length
     */
    [[nodiscard]] constexpr T lengthSquared() const noexcept {
        T sum = T(0);
        for (size_type i = 0; i < N; ++i) {
            sum += data[i] * data[i];
        }
        return sum;
    }

    /**
     * @brief Alias for lengthSquared.
     */
    [[nodiscard]] constexpr T lengthSquare() const noexcept { return lengthSquared(); }

    /**
     * @brief Calculates the length (magnitude) of the vector.
     * @return The length
     */
    [[nodiscard]] T length() const noexcept
        requires FloatingPoint<T>
    {
        // Use GLM for optimized implementation
        if constexpr (N >= 2 && N <= 4 && (std::is_same_v<T, float> || std::is_same_v<T, double>)) {
            return glm::length(static_cast<glm::vec<N, T>>(*this));
        } else {
            return std::sqrt(lengthSquared());
        }
    }

    /**
     * @brief Returns a normalized copy of this vector.
     * @return The normalized vector
     */
    [[nodiscard]] Vec normalized() const noexcept
        requires FloatingPoint<T>
    {
        T len = length();
        if (len > kEpsilon<T>) {
            return *this / len;
        }
        return Vec{};
    }

    /**
     * @brief Returns a normalized copy of this vector (alias for normalized).
     */
    [[nodiscard]] Vec normalize() const noexcept
        requires FloatingPoint<T>
    {
        return normalized();
    }

    /**
     * @brief Normalizes this vector in place.
     * @return Reference to this vector
     */
    Vec& normalizeInPlace() noexcept
        requires FloatingPoint<T>
    {
        T len = length();
        if (len > kEpsilon<T>) {
            *this /= len;
        }
        return *this;
    }

    /**
     * @brief Checks if this vector is normalized.
     * @param epsilon Tolerance for comparison
     * @return true if length is approximately 1
     */
    [[nodiscard]] constexpr bool isNormalized(T epsilon = kEpsilon<T>) const noexcept
        requires FloatingPoint<T>
    {
        return approxEqual(lengthSquared(), T(1), epsilon);
    }

    /**
     * @brief Returns a vector with absolute values of each component.
     */
    [[nodiscard]] constexpr Vec abs() const noexcept {
        Vec result;
        for (size_type i = 0; i < N; ++i) {
            result.data[i] = std::abs(data[i]);
        }
        return result;
    }

    /**
     * @brief Computes the dot product with another vector.
     * @param other The other vector
     * @return The dot product
     */
    [[nodiscard]] constexpr T dot(const Vec& other) const noexcept {
        T sum = T(0);
        for (size_type i = 0; i < N; ++i) {
            sum += data[i] * other.data[i];
        }
        return sum;
    }

    /**
     * @brief Computes the cross product with another vector (3D only).
     * @param other The other vector
     * @return The cross product
     */
    [[nodiscard]] constexpr Vec cross(const Vec& other) const noexcept
        requires(N == 3)
    {
        return Vec(data[1] * other.data[2] - data[2] * other.data[1],
                   data[2] * other.data[0] - data[0] * other.data[2],
                   data[0] * other.data[1] - data[1] * other.data[0]);
    }

    /**
     * @brief Computes the 2D cross product (z-component of 3D cross).
     * @param other The other vector
     * @return The cross product scalar
     */
    [[nodiscard]] constexpr T cross(const Vec& other) const noexcept
        requires(N == 2)
    {
        return data[0] * other.data[1] - data[1] * other.data[0];
    }

    /**
     * @brief Calculates the distance to another vector.
     * @param other The other vector
     * @return The distance
     */
    [[nodiscard]] T distance(const Vec& other) const noexcept
        requires FloatingPoint<T>
    {
        return (*this - other).length();
    }

    /**
     * @brief Calculates the squared distance to another vector.
     * @param other The other vector
     * @return The squared distance
     */
    [[nodiscard]] constexpr T distanceSquared(const Vec& other) const noexcept {
        return (*this - other).lengthSquared();
    }

    /**
     * @brief Reflects this vector around a normal.
     * @param normal The surface normal (should be normalized)
     * @return The reflected vector
     */
    [[nodiscard]] constexpr Vec reflect(const Vec& normal) const noexcept
        requires FloatingPoint<T>
    {
        return *this - normal * (T(2) * dot(normal));
    }

    /**
     * @brief Refracts this vector through a surface.
     * @param normal The surface normal (should be normalized)
     * @param eta The ratio of indices of refraction
     * @return The refracted vector
     */
    [[nodiscard]] Vec refract(const Vec& normal, T eta) const noexcept
        requires FloatingPoint<T>
    {
        if constexpr (N >= 2 && N <= 4) {
            return glm::refract(static_cast<glm::vec<N, T>>(*this), static_cast<glm::vec<N, T>>(normal), eta);
        } else {
            T d = dot(normal);
            T k = T(1) - eta * eta * (T(1) - d * d);
            if (k < T(0)) {
                return Vec{};
            }
            return *this * eta - normal * (eta * d + std::sqrt(k));
        }
    }

    /**
     * @brief Projects this vector onto another vector.
     * @param other The vector to project onto
     * @return The projected vector
     */
    [[nodiscard]] Vec project(const Vec& other) const noexcept
        requires FloatingPoint<T>
    {
        T other_len_sq = other.lengthSquared();
        if (other_len_sq < kEpsilon<T>) {
            return Vec{};
        }
        return other * (dot(other) / other_len_sq);
    }

    /**
     * @brief Computes the rejection from another vector.
     * @param other The vector to reject from
     * @return The perpendicular component
     */
    [[nodiscard]] Vec reject(const Vec& other) const noexcept
        requires FloatingPoint<T>
    {
        return *this - project(other);
    }

    /**
     * @brief Decomposes this vector into parallel and perpendicular components.
     * @param v The reference vector
     * @param proj Output: the projection onto v
     * @param perp Output: the perpendicular component
     */
    void decomposeVec(const Vec& v, Vec& proj, Vec& perp) const noexcept
        requires FloatingPoint<T>
    {
        proj = project(v);
        perp = *this - proj;
    }

    /**
     * @brief Returns a vector perpendicular to this one (2D).
     * @return A perpendicular vector (-y, x)
     */
    [[nodiscard]] constexpr Vec perpendicular() const noexcept
        requires(N == 2)
    {
        return Vec(-data[1], data[0]);
    }

    /**
     * @brief Returns a vector perpendicular to this and another vector (3D).
     * @param other The other vector
     * @return The cross product
     */
    [[nodiscard]] constexpr Vec perpendicular(const Vec& other) const noexcept
        requires(N == 3)
    {
        return cross(other);
    }

    /**
     * @brief Rotates this vector around an axis by an angle (3D).
     * @param axis The rotation axis (should be normalized)
     * @param angle The rotation angle in radians
     * @return The rotated vector
     */
    [[nodiscard]] Vec rotate(const Vec& axis, T angle) const noexcept
        requires(N == 3 && FloatingPoint<T>)
    {
        return glm::rotate(static_cast<glm::vec<3, T>>(*this), angle, static_cast<glm::vec<3, T>>(axis));
    }

    /**
     * @brief Rotates this vector around an axis by an angle (2D).
     * @param axis Unused for 2D
     * @param angle The rotation angle in radians
     * @return The rotated vector
     */
    [[nodiscard]] Vec rotate([[maybe_unused]] const Vec& axis, T angle) const noexcept
        requires(N == 2 && FloatingPoint<T>)
    {
        T c = std::cos(angle);
        T s = std::sin(angle);
        return Vec(data[0] * c - data[1] * s, data[0] * s + data[1] * c);
    }

    /**
     * @brief Rotates this 4D vector around a 3D axis.
     */
    [[nodiscard]] Vec rotate(const Vec<T, 3>& axis, T angle) const noexcept
        requires(N == 4 && FloatingPoint<T>)
    {
        Vec<T, 3> rotated = glm::rotate(static_cast<glm::vec<3, T>>(xyz()), angle, static_cast<glm::vec<3, T>>(axis));
        return Vec(rotated, data[3]);
    }

    // ========================================================================
    // Comparison Operations
    // ========================================================================

    /**
     * @brief Checks if two vectors are approximately equal.
     * @param other The other vector
     * @param epsilon Tolerance for comparison
     * @return true if approximately equal
     */
    [[nodiscard]] constexpr bool approxEquals(const Vec& other, T epsilon = kEpsilon<T>) const noexcept
        requires FloatingPoint<T>
    {
        for (size_type i = 0; i < N; ++i) {
            if (!approxEqual(data[i], other.data[i], epsilon)) {
                return false;
            }
        }
        return true;
    }

    /**
     * @brief Checks if two vectors are approximately equal.
     *
     * This is an alias for approxEquals() and uses absolute epsilon comparison.
     *
     * @note This differs from the scalar areSame() in math_utils.h which uses
     *       relative epsilon. For vectors, absolute epsilon is typically more
     *       appropriate as vector components are usually in a known range.
     *
     * @param other The other vector
     * @param epsilon Tolerance for comparison (absolute)
     * @return true if all components are within epsilon
     */
    [[nodiscard]] constexpr bool areSame(const Vec& other, T epsilon = kEpsilon<T>) const noexcept
        requires FloatingPoint<T>
    {
        return approxEquals(other, epsilon);
    }

    /**
     * @brief Checks if two vectors are parallel (aligned).
     * @param other The other vector
     * @param epsilon Tolerance for comparison
     * @return true if aligned
     */
    [[nodiscard]] bool areAligned(const Vec& other, T epsilon = kEpsilon<T>) const noexcept
        requires FloatingPoint<T>
    {
        Vec n1 = normalized();
        Vec n2 = other.normalized();
        T d = std::abs(n1.dot(n2));
        return approxEqual(d, T(1), epsilon);
    }

    /**
     * @brief Checks if this vector is approximately zero.
     *
     * Uses absolute epsilon comparison for each component.
     *
     * @note This uses approxZero() (absolute epsilon) rather than the
     *       isZero() from math_utils.h (relative epsilon).
     *
     * @param epsilon Tolerance for comparison (absolute)
     * @return true if all components are within epsilon of zero
     */
    [[nodiscard]] constexpr bool isZero(T epsilon = kEpsilon<T>) const noexcept
        requires FloatingPoint<T>
    {
        for (size_type i = 0; i < N; ++i) {
            if (!approxZero(data[i], epsilon)) {
                return false;
            }
        }
        return true;
    }

    /**
     * @brief Checks if vectors are linearly dependent (parallel).
     */
    [[nodiscard]] bool isLinearDependent(const Vec& other, T epsilon = kEpsilon<T>) const noexcept
        requires FloatingPoint<T>
    {
        return areAligned(other, epsilon);
    }

    /**
     * @brief Checks if three points are collinear (3D).
     */
    [[nodiscard]] bool isLinearDependent(const Vec& p1, const Vec& p2, T epsilon = kEpsilon<T>) const noexcept
        requires(N == 3 && FloatingPoint<T>)
    {
        Vec v1 = p1 - *this;
        Vec v2 = p2 - *this;
        return v1.cross(v2).lengthSquared() < epsilon * epsilon;
    }

    /**
     * @brief Equality comparison.
     */
    [[nodiscard]] constexpr bool operator==(const Vec& other) const noexcept = default;

    /**
     * @brief Inequality comparison.
     */
    [[nodiscard]] constexpr bool operator!=(const Vec& other) const noexcept = default;

    /**
     * @brief Greater than comparison (by length).
     */
    [[nodiscard]] bool operator>(const Vec& other) const noexcept
        requires FloatingPoint<T>
    {
        return lengthSquared() > other.lengthSquared();
    }

    /**
     * @brief Less than comparison (by length).
     */
    [[nodiscard]] bool operator<(const Vec& other) const noexcept
        requires FloatingPoint<T>
    {
        return lengthSquared() < other.lengthSquared();
    }

    // ========================================================================
    // Min/Max Operations
    // ========================================================================

    /**
     * @brief Returns the vector with smaller length.
     * @param other The other vector
     * @return The vector with smaller magnitude
     */
    [[nodiscard]] constexpr Vec min(const Vec& other) const noexcept {
        return lengthSquared() < other.lengthSquared() ? *this : other;
    }

    /**
     * @brief Returns the vector with larger length.
     * @param other The other vector
     * @return The vector with larger magnitude
     */
    [[nodiscard]] constexpr Vec max(const Vec& other) const noexcept {
        return lengthSquared() > other.lengthSquared() ? *this : other;
    }

    /**
     * @brief Returns the component-wise minimum of this and another vector.
     */
    [[nodiscard]] constexpr Vec componentMin(const Vec& other) const noexcept {
        Vec result;
        for (size_type i = 0; i < N; ++i) {
            result.data[i] = std::min(data[i], other.data[i]);
        }
        return result;
    }

    /**
     * @brief Returns the component-wise maximum of this and another vector.
     */
    [[nodiscard]] constexpr Vec componentMax(const Vec& other) const noexcept {
        Vec result;
        for (size_type i = 0; i < N; ++i) {
            result.data[i] = std::max(data[i], other.data[i]);
        }
        return result;
    }

    /**
     * @brief Returns the minimum component value.
     */
    [[nodiscard]] constexpr T minComponent() const noexcept {
        T result = data[0];
        for (size_type i = 1; i < N; ++i) {
            result = std::min(result, data[i]);
        }
        return result;
    }

    /**
     * @brief Returns the maximum component value.
     */
    [[nodiscard]] constexpr T maxComponent() const noexcept {
        T result = data[0];
        for (size_type i = 1; i < N; ++i) {
            result = std::max(result, data[i]);
        }
        return result;
    }

    // ========================================================================
    // Angle and Midpoint Operations
    // ========================================================================

    /**
     * @brief Computes the angle between this vector and another.
     * @param other The other vector
     * @return The angle in radians
     */
    [[nodiscard]] T angle(const Vec& other) const noexcept
        requires FloatingPoint<T>
    {
        T len_product = length() * other.length();
        if (len_product < kEpsilon<T>) {
            return T(0);
        }
        T cos_angle = clamp(dot(other) / len_product, T(-1), T(1));
        return std::acos(cos_angle);
    }

    /**
     * @brief Computes the angle at this point in a triangle.
     * @param p1 First point
     * @param p2 Second point
     * @return The angle in radians
     */
    [[nodiscard]] T angle(const Vec& p1, const Vec& p2) const noexcept
        requires FloatingPoint<T>
    {
        Vec v1 = p1 - *this;
        Vec v2 = p2 - *this;
        return v1.angle(v2);
    }

    /**
     * @brief Computes the angle of this 2D vector from the positive x-axis.
     * @return The angle in radians
     */
    [[nodiscard]] T angle() const noexcept
        requires(N == 2 && FloatingPoint<T>)
    {
        return std::atan2(data[1], data[0]);
    }

    /**
     * @brief Computes the midpoint between this and another vector.
     */
    [[nodiscard]] constexpr Vec midPoint(const Vec& other) const noexcept { return (*this + other) * T(0.5); }

    /**
     * @brief Linearly interpolates between this and another vector.
     */
    [[nodiscard]] constexpr Vec lerp(const Vec& other, T t) const noexcept
        requires FloatingPoint<T>
    {
        Vec result;
        for (size_type i = 0; i < N; ++i) {
            result.data[i] = data[i] + t * (other.data[i] - data[i]);
        }
        return result;
    }

    // ========================================================================
    // Coordinate System Conversions (2D)
    // ========================================================================

    /**
     * @brief Composes this vector from polar coordinates.
     * @param radius The radial distance
     * @param angle_val The angle in radians
     * @return Reference to this vector
     */
    Vec& composePolar(T radius, T angle_val) noexcept
        requires(N == 2 && FloatingPoint<T>)
    {
        data[0] = radius * std::cos(angle_val);
        data[1] = radius * std::sin(angle_val);
        return *this;
    }

    /**
     * @brief Decomposes this vector into polar coordinates.
     * @param radius Output: the radial distance
     * @param angle_val Output: the angle in radians
     */
    void decomposePolar(T& radius, T& angle_val) const noexcept
        requires(N == 2 && FloatingPoint<T>)
    {
        radius = length();
        angle_val = std::atan2(data[1], data[0]);
    }

    // ========================================================================
    // Coordinate System Conversions (3D)
    // ========================================================================

    /**
     * @brief Composes this vector from spherical coordinates.
     * @param rho The radial distance
     * @param theta The azimuthal angle (in xy plane)
     * @param phi The polar angle (from z-axis)
     * @return Reference to this vector
     */
    Vec& composeSpherical(T rho, T theta, T phi) noexcept
        requires(N == 3 && FloatingPoint<T>)
    {
        T sin_phi = std::sin(phi);
        data[0] = rho * sin_phi * std::cos(theta);
        data[1] = rho * sin_phi * std::sin(theta);
        data[2] = rho * std::cos(phi);
        return *this;
    }

    /**
     * @brief Decomposes this vector into spherical coordinates.
     * @param rho Output: the radial distance
     * @param theta Output: the azimuthal angle
     * @param phi Output: the polar angle
     */
    void decomposeSpherical(T& rho, T& theta, T& phi) const noexcept
        requires(N == 3 && FloatingPoint<T>)
    {
        rho = length();
        if (rho < kEpsilon<T>) {
            theta = T(0);
            phi = T(0);
            return;
        }
        theta = std::atan2(data[1], data[0]);
        phi = std::acos(clamp(data[2] / rho, T(-1), T(1)));
    }

    /**
     * @brief Composes this vector from cylindrical coordinates.
     * @param radius The radial distance in xy plane
     * @param angle_val The angle in xy plane
     * @param height The z coordinate
     * @return Reference to this vector
     */
    Vec& composeCylindrical(T radius, T angle_val, T height) noexcept
        requires(N == 3 && FloatingPoint<T>)
    {
        data[0] = radius * std::cos(angle_val);
        data[1] = radius * std::sin(angle_val);
        data[2] = height;
        return *this;
    }

    /**
     * @brief Decomposes this vector into cylindrical coordinates.
     * @param radius Output: the radial distance
     * @param angle_val Output: the angle in radians
     * @param height Output: the z coordinate
     */
    void decomposeCylindrical(T& radius, T& angle_val, T& height) const noexcept
        requires(N == 3 && FloatingPoint<T>)
    {
        radius = std::sqrt(data[0] * data[0] + data[1] * data[1]);
        angle_val = std::atan2(data[1], data[0]);
        height = data[2];
    }

    // ========================================================================
    // Arithmetic Operators
    // ========================================================================

    [[nodiscard]] constexpr Vec operator+(const Vec& other) const noexcept {
        Vec result;
        for (size_type i = 0; i < N; ++i) {
            result.data[i] = data[i] + other.data[i];
        }
        return result;
    }

    constexpr Vec& operator+=(const Vec& other) noexcept {
        for (size_type i = 0; i < N; ++i) {
            data[i] += other.data[i];
        }
        return *this;
    }

    [[nodiscard]] constexpr Vec operator+(T scalar) const noexcept {
        Vec result;
        for (size_type i = 0; i < N; ++i) {
            result.data[i] = data[i] + scalar;
        }
        return result;
    }

    constexpr Vec& operator+=(T scalar) noexcept {
        for (size_type i = 0; i < N; ++i) {
            data[i] += scalar;
        }
        return *this;
    }

    [[nodiscard]] constexpr Vec operator-(const Vec& other) const noexcept {
        Vec result;
        for (size_type i = 0; i < N; ++i) {
            result.data[i] = data[i] - other.data[i];
        }
        return result;
    }

    constexpr Vec& operator-=(const Vec& other) noexcept {
        for (size_type i = 0; i < N; ++i) {
            data[i] -= other.data[i];
        }
        return *this;
    }

    [[nodiscard]] constexpr Vec operator-(T scalar) const noexcept {
        Vec result;
        for (size_type i = 0; i < N; ++i) {
            result.data[i] = data[i] - scalar;
        }
        return result;
    }

    constexpr Vec& operator-=(T scalar) noexcept {
        for (size_type i = 0; i < N; ++i) {
            data[i] -= scalar;
        }
        return *this;
    }

    [[nodiscard]] constexpr Vec operator*(T scalar) const noexcept {
        Vec result;
        for (size_type i = 0; i < N; ++i) {
            result.data[i] = data[i] * scalar;
        }
        return result;
    }

    constexpr Vec& operator*=(T scalar) noexcept {
        for (size_type i = 0; i < N; ++i) {
            data[i] *= scalar;
        }
        return *this;
    }

    [[nodiscard]] constexpr Vec operator*(const Vec& other) const noexcept {
        Vec result;
        for (size_type i = 0; i < N; ++i) {
            result.data[i] = data[i] * other.data[i];
        }
        return result;
    }

    constexpr Vec& operator*=(const Vec& other) noexcept {
        for (size_type i = 0; i < N; ++i) {
            data[i] *= other.data[i];
        }
        return *this;
    }

    [[nodiscard]] constexpr Vec operator/(T scalar) const noexcept {
        Vec result;
        for (size_type i = 0; i < N; ++i) {
            result.data[i] = data[i] / scalar;
        }
        return result;
    }

    constexpr Vec& operator/=(T scalar) noexcept {
        for (size_type i = 0; i < N; ++i) {
            data[i] /= scalar;
        }
        return *this;
    }

    [[nodiscard]] constexpr Vec operator/(const Vec& other) const noexcept {
        Vec result;
        for (size_type i = 0; i < N; ++i) {
            result.data[i] = data[i] / other.data[i];
        }
        return result;
    }

    constexpr Vec& operator/=(const Vec& other) noexcept {
        for (size_type i = 0; i < N; ++i) {
            data[i] /= other.data[i];
        }
        return *this;
    }

    [[nodiscard]] constexpr Vec operator-() const noexcept {
        Vec result;
        for (size_type i = 0; i < N; ++i) {
            result.data[i] = -data[i];
        }
        return result;
    }

    // ========================================================================
    // Static Factory Methods
    // ========================================================================

    /**
     * @brief Returns the dimension of the vector.
     */
    [[nodiscard]] static constexpr uint32_t dim() noexcept { return static_cast<uint32_t>(N); }

    /**
     * @brief Returns the size of the vector.
     */
    [[nodiscard]] static constexpr uint32_t size() noexcept { return static_cast<uint32_t>(N); }

    /**
     * @brief Returns a zero vector.
     */
    [[nodiscard]] static constexpr Vec zero() noexcept { return Vec{}; }

    /**
     * @brief Returns a vector with all components set to one.
     */
    [[nodiscard]] static constexpr Vec one() noexcept { return Vec(T(1)); }

    /**
     * @brief Returns the X axis unit vector.
     */
    [[nodiscard]] static constexpr Vec xAxis() noexcept
        requires(N >= 1)
    {
        Vec v{};
        v.data[0] = T(1);
        return v;
    }

    /**
     * @brief Returns the Y axis unit vector.
     */
    [[nodiscard]] static constexpr Vec yAxis() noexcept
        requires(N >= 2)
    {
        Vec v{};
        v.data[1] = T(1);
        return v;
    }

    /**
     * @brief Returns the Z axis unit vector.
     */
    [[nodiscard]] static constexpr Vec zAxis() noexcept
        requires(N >= 3)
    {
        Vec v{};
        v.data[2] = T(1);
        return v;
    }

    /**
     * @brief Returns the W axis unit vector.
     */
    [[nodiscard]] static constexpr Vec wAxis() noexcept
        requires(N >= 4)
    {
        Vec v{};
        v.data[3] = T(1);
        return v;
    }

    /// @name Direction Aliases (3D)
    /// @{

    [[nodiscard]] static constexpr Vec up() noexcept
        requires(N == 3)
    {
        return yAxis();
    }

    [[nodiscard]] static constexpr Vec down() noexcept
        requires(N == 3)
    {
        return -yAxis();
    }

    [[nodiscard]] static constexpr Vec right() noexcept
        requires(N == 3)
    {
        return xAxis();
    }

    [[nodiscard]] static constexpr Vec left() noexcept
        requires(N == 3)
    {
        return -xAxis();
    }

    [[nodiscard]] static constexpr Vec forward() noexcept
        requires(N == 3)
    {
        return zAxis();
    }

    [[nodiscard]] static constexpr Vec backward() noexcept
        requires(N == 3)
    {
        return -zAxis();
    }

    /// @}

    // ========================================================================
    // Static Operations
    // ========================================================================

    /**
     * @brief Computes the dot product of two vectors.
     */
    [[nodiscard]] static constexpr T dot(const Vec& a, const Vec& b) noexcept { return a.dot(b); }

    /**
     * @brief Computes the cross product of two vectors (3D only).
     */
    [[nodiscard]] static constexpr Vec cross(const Vec& a, const Vec& b) noexcept
        requires(N == 3)
    {
        return a.cross(b);
    }

    /**
     * @brief Computes the 2D cross product.
     */
    [[nodiscard]] static constexpr T cross(const Vec& a, const Vec& b) noexcept
        requires(N == 2)
    {
        return a.cross(b);
    }

    /**
     * @brief Returns a normalized copy of the vector.
     */
    [[nodiscard]] static Vec normalized(const Vec& v) noexcept
        requires FloatingPoint<T>
    {
        return v.normalized();
    }

    /**
     * @brief Calculates the distance between two vectors.
     */
    [[nodiscard]] static T distance(const Vec& a, const Vec& b) noexcept
        requires FloatingPoint<T>
    {
        return a.distance(b);
    }

    /**
     * @brief Linear interpolation between two vectors.
     */
    [[nodiscard]] static constexpr Vec lerp(const Vec& a, const Vec& b, T t) noexcept
        requires FloatingPoint<T>
    {
        return a.lerp(b, t);
    }

    /**
     * @brief Calculates the midpoint between two vectors.
     */
    [[nodiscard]] static constexpr Vec midPoint(const Vec& a, const Vec& b) noexcept { return a.midPoint(b); }

    /**
     * @brief Returns the component-wise minimum of two vectors.
     */
    [[nodiscard]] static constexpr Vec min(const Vec& a, const Vec& b) noexcept { return a.componentMin(b); }

    /**
     * @brief Returns the component-wise maximum of two vectors.
     */
    [[nodiscard]] static constexpr Vec max(const Vec& a, const Vec& b) noexcept { return a.componentMax(b); }

    /**
     * @brief Returns the component-wise absolute value.
     */
    [[nodiscard]] static constexpr Vec abs(const Vec& v) noexcept { return v.abs(); }

    // ========================================================================
    // Stream I/O
    // ========================================================================

    friend std::ostream& operator<<(std::ostream& os, const Vec& v) {
        os << "(";
        for (size_type i = 0; i < N; ++i) {
            if (i > 0) {
                os << ", ";
            }
            os << v.data[i];
        }
        os << ")";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Vec& v) {
        for (size_type i = 0; i < N; ++i) {
            is >> v.data[i];
        }
        return is;
    }
};

// ============================================================================
// Free Function Operators
// ============================================================================

/**
 * @brief Scalar multiplication (scalar * vector).
 */
template<typename T, size_t N>
    requires Arithmetic<T>
[[nodiscard]] constexpr Vec<T, N> operator*(T scalar, const Vec<T, N>& v) noexcept {
    return v * scalar;
}

/**
 * @brief Scalar addition (scalar + vector).
 */
template<typename T, size_t N>
    requires Arithmetic<T>
[[nodiscard]] constexpr Vec<T, N> operator+(T scalar, const Vec<T, N>& v) noexcept {
    return v + scalar;
}

// ============================================================================
// GLM Comparison Operators
// ============================================================================

template<typename T>
    requires(std::is_same_v<T, float> || std::is_same_v<T, double>)
[[nodiscard]] inline bool operator==(const Vec<T, 2>& a, const glm::vec<2, T>& b) noexcept {
    return a.x() == b.x && a.y() == b.y;
}

template<typename T>
    requires(std::is_same_v<T, float> || std::is_same_v<T, double>)
[[nodiscard]] inline bool operator==(const glm::vec<2, T>& a, const Vec<T, 2>& b) noexcept {
    return a.x == b.x() && a.y == b.y();
}

template<typename T>
    requires(std::is_same_v<T, float> || std::is_same_v<T, double>)
[[nodiscard]] inline bool operator==(const Vec<T, 3>& a, const glm::vec<3, T>& b) noexcept {
    return a.x() == b.x && a.y() == b.y && a.z() == b.z;
}

template<typename T>
    requires(std::is_same_v<T, float> || std::is_same_v<T, double>)
[[nodiscard]] inline bool operator==(const glm::vec<3, T>& a, const Vec<T, 3>& b) noexcept {
    return a.x == b.x() && a.y == b.y() && a.z == b.z();
}

template<typename T>
    requires(std::is_same_v<T, float> || std::is_same_v<T, double>)
[[nodiscard]] inline bool operator==(const Vec<T, 4>& a, const glm::vec<4, T>& b) noexcept {
    return a.x() == b.x && a.y() == b.y && a.z() == b.z && a.w() == b.w;
}

template<typename T>
    requires(std::is_same_v<T, float> || std::is_same_v<T, double>)
[[nodiscard]] inline bool operator==(const glm::vec<4, T>& a, const Vec<T, 4>& b) noexcept {
    return a.x == b.x() && a.y == b.y() && a.z == b.z() && a.w == b.w();
}

}  // namespace vne::math

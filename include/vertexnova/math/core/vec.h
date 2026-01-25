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
#include <ostream>

// GLM for optimized operations (optional backend)
#include <glm/geometric.hpp>
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
     * @brief Constructs a 4D vector from a 3D vector and a w component.
     */
    constexpr Vec(const Vec<T, 3>& xyz, T w) noexcept
        requires(N == 4)
        : data{xyz.data[0], xyz.data[1], xyz.data[2], w} {}

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
     * @brief Converts to glm::vec.
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
     * @brief Normalizes this vector in place.
     * @return Reference to this vector
     */
    Vec& normalize() noexcept
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
     * @brief Equality comparison.
     */
    [[nodiscard]] constexpr bool operator==(const Vec& other) const noexcept = default;

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
        return -zAxis();
    }

    [[nodiscard]] static constexpr Vec backward() noexcept
        requires(N == 3)
    {
        return zAxis();
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
     * @brief Returns a normalized copy of the vector.
     */
    [[nodiscard]] static Vec normalized(const Vec& v) noexcept
        requires FloatingPoint<T>
    {
        return v.normalized();
    }

    /**
     * @brief Linear interpolation between two vectors.
     */
    [[nodiscard]] static constexpr Vec lerp(const Vec& a, const Vec& b, T t) noexcept
        requires FloatingPoint<T>
    {
        Vec result;
        for (size_type i = 0; i < N; ++i) {
            result.data[i] = a.data[i] + t * (b.data[i] - a.data[i]);
        }
        return result;
    }

    /**
     * @brief Returns the component-wise minimum of two vectors.
     */
    [[nodiscard]] static constexpr Vec min(const Vec& a, const Vec& b) noexcept {
        Vec result;
        for (size_type i = 0; i < N; ++i) {
            result.data[i] = std::min(a.data[i], b.data[i]);
        }
        return result;
    }

    /**
     * @brief Returns the component-wise maximum of two vectors.
     */
    [[nodiscard]] static constexpr Vec max(const Vec& a, const Vec& b) noexcept {
        Vec result;
        for (size_type i = 0; i < N; ++i) {
            result.data[i] = std::max(a.data[i], b.data[i]);
        }
        return result;
    }

    /**
     * @brief Returns the component-wise absolute value.
     */
    [[nodiscard]] static constexpr Vec abs(const Vec& v) noexcept {
        Vec result;
        for (size_type i = 0; i < N; ++i) {
            result.data[i] = std::abs(v.data[i]);
        }
        return result;
    }

    // ========================================================================
    // Stream Output
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

}  // namespace vne::math

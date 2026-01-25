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
 * @file quat.h
 * @brief Templated quaternion class for rotations.
 *
 * This file provides a generic Quat<T> class that supports:
 * - Any floating-point type (float, double)
 * - Quaternion arithmetic and interpolation
 * - Conversion to/from rotation matrices and Euler angles
 * - SIMD optimization via GLM backend
 */

#include "mat.h"
#include "vec.h"

#include <cmath>
#include <ostream>

// GLM for optimized operations
#include <glm/gtc/quaternion.hpp>

namespace vne::math {

/**
 * @class Quat
 * @brief A templated quaternion class for representing 3D rotations.
 *
 * @tparam T The scalar type (must satisfy FloatingPoint concept)
 *
 * The quaternion is stored in (x, y, z, w) order where:
 * - (x, y, z) is the vector/imaginary part
 * - w is the scalar/real part
 *
 * @example
 * ```cpp
 * Quatf q = Quatf::fromAxisAngle(Vec3f::yAxis(), degToRad(90.0f));
 * Vec3f rotated = q.rotate(Vec3f::forward());
 * Mat4f rotMatrix = q.toMatrix();
 * ```
 */
template<typename T>
    requires FloatingPoint<T>
class Quat {
   public:
    using value_type = T;

    /// @brief Quaternion components (x, y, z, w)
    T x{0};
    T y{0};
    T z{0};
    T w{1};

   public:
    // ========================================================================
    // Constructors
    // ========================================================================

    /**
     * @brief Default constructor, creates an identity quaternion (no rotation).
     */
    constexpr Quat() noexcept = default;

    /**
     * @brief Constructs a quaternion from components.
     * @param x X component (imaginary)
     * @param y Y component (imaginary)
     * @param z Z component (imaginary)
     * @param w W component (real/scalar)
     */
    constexpr Quat(T x, T y, T z, T w) noexcept
        : x(x)
        , y(y)
        , z(z)
        , w(w) {}

    /**
     * @brief Constructs from a scalar and vector part.
     * @param scalar The w component
     * @param vector The xyz components
     */
    constexpr Quat(T scalar, const Vec<T, 3>& vector) noexcept
        : x(vector.x())
        , y(vector.y())
        , z(vector.z())
        , w(scalar) {}

    /**
     * @brief Copy constructor.
     */
    constexpr Quat(const Quat& other) noexcept = default;

    /**
     * @brief Move constructor.
     */
    constexpr Quat(Quat&& other) noexcept = default;

    /**
     * @brief Copy assignment.
     */
    constexpr Quat& operator=(const Quat& other) noexcept = default;

    /**
     * @brief Move assignment.
     */
    constexpr Quat& operator=(Quat&& other) noexcept = default;

    /**
     * @brief Destructor.
     */
    ~Quat() noexcept = default;

    // ========================================================================
    // GLM Interoperability
    // ========================================================================

    /**
     * @brief Constructs from glm::quat.
     */
    constexpr Quat(const glm::qua<T>& q) noexcept
        : x(q.x)
        , y(q.y)
        , z(q.z)
        , w(q.w) {}

    /**
     * @brief Converts to glm::quat.
     */
    [[nodiscard]] constexpr operator glm::qua<T>() const noexcept { return glm::qua<T>(w, x, y, z); }

    // ========================================================================
    // Element Access
    // ========================================================================

    /**
     * @brief Gets the vector (imaginary) part.
     */
    [[nodiscard]] constexpr Vec<T, 3> vector() const noexcept { return Vec<T, 3>(x, y, z); }

    /**
     * @brief Gets the scalar (real) part.
     */
    [[nodiscard]] constexpr T scalar() const noexcept { return w; }

    // ========================================================================
    // Quaternion Properties
    // ========================================================================

    /**
     * @brief Calculates the squared length (norm) of the quaternion.
     */
    [[nodiscard]] constexpr T lengthSquared() const noexcept { return x * x + y * y + z * z + w * w; }

    /**
     * @brief Calculates the length (norm) of the quaternion.
     */
    [[nodiscard]] T length() const noexcept { return std::sqrt(lengthSquared()); }

    /**
     * @brief Returns a normalized copy of this quaternion.
     */
    [[nodiscard]] Quat normalized() const noexcept {
        T len = length();
        if (len > kEpsilon<T>) {
            T inv = T(1) / len;
            return Quat(x * inv, y * inv, z * inv, w * inv);
        }
        return identity();
    }

    /**
     * @brief Normalizes this quaternion in place.
     */
    Quat& normalize() noexcept {
        *this = normalized();
        return *this;
    }

    /**
     * @brief Checks if this quaternion is normalized.
     */
    [[nodiscard]] constexpr bool isNormalized(T epsilon = kEpsilon<T>) const noexcept {
        return approxEqual(lengthSquared(), T(1), epsilon);
    }

    /**
     * @brief Returns the conjugate of this quaternion.
     */
    [[nodiscard]] constexpr Quat conjugate() const noexcept { return Quat(-x, -y, -z, w); }

    /**
     * @brief Returns the inverse of this quaternion.
     */
    [[nodiscard]] Quat inverse() const noexcept {
        T len_sq = lengthSquared();
        if (len_sq > kEpsilon<T>) {
            T inv = T(1) / len_sq;
            return Quat(-x * inv, -y * inv, -z * inv, w * inv);
        }
        return identity();
    }

    // ========================================================================
    // Rotation Operations
    // ========================================================================

    /**
     * @brief Rotates a vector by this quaternion.
     * @param v The vector to rotate
     * @return The rotated vector
     */
    [[nodiscard]] Vec<T, 3> rotate(const Vec<T, 3>& v) const noexcept {
        // q * v * q^-1 optimized
        Vec<T, 3> qv(x, y, z);
        Vec<T, 3> uv = qv.cross(v);
        Vec<T, 3> uuv = qv.cross(uv);
        return v + ((uv * w) + uuv) * T(2);
    }

    /**
     * @brief Gets the rotation angle in radians.
     */
    [[nodiscard]] T angle() const noexcept { return T(2) * std::acos(clamp(w, T(-1), T(1))); }

    /**
     * @brief Gets the rotation axis.
     */
    [[nodiscard]] Vec<T, 3> axis() const noexcept {
        T s = std::sqrt(T(1) - w * w);
        if (s < kEpsilon<T>) {
            return Vec<T, 3>::yAxis();
        }
        return Vec<T, 3>(x / s, y / s, z / s);
    }

    // ========================================================================
    // Conversion Methods
    // ========================================================================

    /**
     * @brief Converts to a 3x3 rotation matrix.
     */
    [[nodiscard]] Mat<T, 3, 3> toMatrix3() const noexcept { return glm::mat3_cast(static_cast<glm::qua<T>>(*this)); }

    /**
     * @brief Converts to a 4x4 rotation matrix.
     */
    [[nodiscard]] Mat<T, 4, 4> toMatrix4() const noexcept { return glm::mat4_cast(static_cast<glm::qua<T>>(*this)); }

    /**
     * @brief Converts to Euler angles (pitch, yaw, roll in radians).
     * @return Vec3 with (pitch, yaw, roll)
     */
    [[nodiscard]] Vec<T, 3> toEuler() const noexcept { return glm::eulerAngles(static_cast<glm::qua<T>>(*this)); }

    // ========================================================================
    // Comparison
    // ========================================================================

    /**
     * @brief Checks if two quaternions are approximately equal.
     */
    [[nodiscard]] constexpr bool approxEquals(const Quat& other, T epsilon = kEpsilon<T>) const noexcept {
        return approxEqual(x, other.x, epsilon) && approxEqual(y, other.y, epsilon) && approxEqual(z, other.z, epsilon)
               && approxEqual(w, other.w, epsilon);
    }

    [[nodiscard]] constexpr bool operator==(const Quat& other) const noexcept = default;

    // ========================================================================
    // Arithmetic Operators
    // ========================================================================

    /**
     * @brief Quaternion multiplication (composition of rotations).
     */
    [[nodiscard]] constexpr Quat operator*(const Quat& other) const noexcept {
        return Quat(w * other.x + x * other.w + y * other.z - z * other.y,
                    w * other.y - x * other.z + y * other.w + z * other.x,
                    w * other.z + x * other.y - y * other.x + z * other.w,
                    w * other.w - x * other.x - y * other.y - z * other.z);
    }

    constexpr Quat& operator*=(const Quat& other) noexcept {
        *this = *this * other;
        return *this;
    }

    [[nodiscard]] constexpr Quat operator*(T scalar) const noexcept {
        return Quat(x * scalar, y * scalar, z * scalar, w * scalar);
    }

    constexpr Quat& operator*=(T scalar) noexcept {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        w *= scalar;
        return *this;
    }

    [[nodiscard]] constexpr Quat operator+(const Quat& other) const noexcept {
        return Quat(x + other.x, y + other.y, z + other.z, w + other.w);
    }

    constexpr Quat& operator+=(const Quat& other) noexcept {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
        return *this;
    }

    [[nodiscard]] constexpr Quat operator-() const noexcept { return Quat(-x, -y, -z, -w); }

    // ========================================================================
    // Static Factory Methods
    // ========================================================================

    /**
     * @brief Returns the identity quaternion (no rotation).
     */
    [[nodiscard]] static constexpr Quat identity() noexcept { return Quat(T(0), T(0), T(0), T(1)); }

    /**
     * @brief Creates a quaternion from an axis and angle.
     * @param axis The rotation axis (should be normalized)
     * @param angle The rotation angle in radians
     */
    [[nodiscard]] static Quat fromAxisAngle(const Vec<T, 3>& axis, T angle) noexcept {
        T half_angle = angle * T(0.5);
        T s = std::sin(half_angle);
        return Quat(axis.x() * s, axis.y() * s, axis.z() * s, std::cos(half_angle));
    }

    /**
     * @brief Creates a quaternion from Euler angles.
     * @param pitch Rotation around X axis in radians
     * @param yaw Rotation around Y axis in radians
     * @param roll Rotation around Z axis in radians
     */
    [[nodiscard]] static Quat fromEuler(T pitch, T yaw, T roll) noexcept {
        return glm::qua<T>(glm::vec<3, T>(pitch, yaw, roll));
    }

    /**
     * @brief Creates a quaternion from Euler angles.
     * @param euler Vec3 with (pitch, yaw, roll) in radians
     */
    [[nodiscard]] static Quat fromEuler(const Vec<T, 3>& euler) noexcept {
        return fromEuler(euler.x(), euler.y(), euler.z());
    }

    /**
     * @brief Creates a quaternion from a rotation matrix.
     */
    [[nodiscard]] static Quat fromMatrix(const Mat<T, 3, 3>& m) noexcept {
        return glm::quat_cast(static_cast<glm::mat<3, 3, T>>(m));
    }

    /**
     * @brief Creates a quaternion from a rotation matrix (4x4).
     */
    [[nodiscard]] static Quat fromMatrix(const Mat<T, 4, 4>& m) noexcept {
        return glm::quat_cast(static_cast<glm::mat<4, 4, T>>(m));
    }

    /**
     * @brief Creates a quaternion that rotates from one direction to another.
     * @param from The starting direction (should be normalized)
     * @param to The target direction (should be normalized)
     */
    [[nodiscard]] static Quat fromToRotation(const Vec<T, 3>& from, const Vec<T, 3>& to) noexcept {
        T d = Vec<T, 3>::dot(from, to);

        if (d >= T(1) - kEpsilon<T>) {
            return identity();
        }

        if (d <= T(-1) + kEpsilon<T>) {
            // Opposite directions - rotate 180 degrees around any perpendicular axis
            Vec<T, 3> axis = Vec<T, 3>::cross(Vec<T, 3>::xAxis(), from);
            if (axis.lengthSquared() < kEpsilon<T>) {
                axis = Vec<T, 3>::cross(Vec<T, 3>::yAxis(), from);
            }
            return fromAxisAngle(axis.normalized(), kPi<T>);
        }

        Vec<T, 3> axis = Vec<T, 3>::cross(from, to);
        T s = std::sqrt((T(1) + d) * T(2));
        T inv_s = T(1) / s;
        return Quat(axis.x() * inv_s, axis.y() * inv_s, axis.z() * inv_s, s * T(0.5));
    }

    /**
     * @brief Creates a quaternion that looks in a direction.
     * @param forward The forward direction (where the object should look)
     * @param up The up direction (hint for orientation)
     * @return A quaternion that rotates from default orientation to look at the target
     *
     * @note This uses a right-handed coordinate system where -Z is forward.
     */
    [[nodiscard]] static Quat lookRotation(const Vec<T, 3>& forward, const Vec<T, 3>& up) noexcept {
        // Use fromToRotation to rotate from default forward to target forward
        return fromToRotation(Vec<T, 3>::forward(), forward.normalized());
    }

    // ========================================================================
    // Static Interpolation
    // ========================================================================

    /**
     * @brief Linearly interpolates between two quaternions (not normalized).
     */
    [[nodiscard]] static constexpr Quat lerp(const Quat& a, const Quat& b, T t) noexcept {
        return Quat(vne::math::lerp(a.x, b.x, t),
                    vne::math::lerp(a.y, b.y, t),
                    vne::math::lerp(a.z, b.z, t),
                    vne::math::lerp(a.w, b.w, t));
    }

    /**
     * @brief Normalized linear interpolation (faster than slerp).
     */
    [[nodiscard]] static Quat nlerp(const Quat& a, const Quat& b, T t) noexcept { return lerp(a, b, t).normalized(); }

    /**
     * @brief Spherical linear interpolation.
     */
    [[nodiscard]] static Quat slerp(const Quat& a, const Quat& b, T t) noexcept {
        return glm::slerp(static_cast<glm::qua<T>>(a), static_cast<glm::qua<T>>(b), t);
    }

    /**
     * @brief Computes the dot product of two quaternions.
     */
    [[nodiscard]] static constexpr T dot(const Quat& a, const Quat& b) noexcept {
        return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
    }

    // ========================================================================
    // Stream Output
    // ========================================================================

    friend std::ostream& operator<<(std::ostream& os, const Quat& q) {
        return os << "Quat(" << q.x << ", " << q.y << ", " << q.z << ", " << q.w << ")";
    }
};

// ============================================================================
// Free Function Operators
// ============================================================================

/**
 * @brief Scalar multiplication (scalar * quaternion).
 */
template<typename T>
    requires FloatingPoint<T>
[[nodiscard]] constexpr Quat<T> operator*(T scalar, const Quat<T>& q) noexcept {
    return q * scalar;
}

}  // namespace vne::math

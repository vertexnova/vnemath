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
 * @file quaternion.h
 * @brief Defines the Quaternion class for 3D rotations.
 */

// Project includes
#include "mat4x4f.h"
#include "vec3f.h"

// Third-party library includes
#include <glm/gtc/quaternion.hpp>

namespace vne::math {

/**
 * @class Quaternion
 * @brief Represents a rotation in 3D space using quaternion mathematics.
 *
 * Quaternions provide an efficient and gimbal-lock-free way to represent
 * 3D rotations. This class extends glm::quat with additional utilities
 * for game and graphics development.
 */
class Quaternion : public glm::quat {
   public:
    /** @brief Default constructor, creates identity quaternion (no rotation) */
    Quaternion() noexcept;

    /**
     * @brief Constructs from a Vec4f (w, x, y, z)
     * @param vec Vector with quaternion components
     */
    Quaternion(const Vec4f& vec) noexcept;

    /**
     * @brief Constructs from a Vec3f with w = 1
     * @param vec Vector with x, y, z components
     */
    Quaternion(const Vec3f& vec) noexcept;

    /**
     * @brief Constructs from w and a vector (x, y, z)
     * @param w_param The w (scalar) component
     * @param vec The vector (x, y, z) components
     */
    Quaternion(float w_param, const Vec3f& vec) noexcept;

    /**
     * @brief Constructs from individual components
     * @param w_param The w (scalar) component
     * @param x_param The x component
     * @param y_param The y component
     * @param z_param The z component
     */
    Quaternion(float w_param, float x_param, float y_param, float z_param) noexcept;

    /**
     * @brief Constructs from Euler angles
     * @param pitch Rotation around X axis (radians)
     * @param yaw Rotation around Y axis (radians)
     * @param roll Rotation around Z axis (radians)
     */
    Quaternion(float pitch, float yaw, float roll) noexcept;

    /**
     * @brief Constructs from a rotation matrix
     * @param mat The 4x4 rotation matrix
     */
    Quaternion(const Mat4x4f& mat) noexcept;

    /** @brief Constructs from a glm::quat */
    Quaternion(const glm::quat& q) noexcept;

    /** @brief Copy constructor */
    Quaternion(const Quaternion& other) noexcept;

    /** @brief Copy assignment operator */
    Quaternion& operator=(const Quaternion& quat) noexcept;

   public:
    /** @brief Gets the w (scalar) component */
    [[nodiscard]] float getW() const noexcept;

    /** @brief Gets the vector (x, y, z) components */
    [[nodiscard]] Vec3f getVector() const noexcept;

   public:
    /// @name Euler Angle Conversion
    /// @{

    /**
     * @brief Sets the quaternion from Euler angles
     * @param pitch Rotation around X axis (radians)
     * @param yaw Rotation around Y axis (radians)
     * @param roll Rotation around Z axis (radians)
     */
    void setFromEulerAngles(float pitch, float yaw, float roll) noexcept;

    /**
     * @brief Converts to Euler angles
     * @return Vec3f containing (pitch, yaw, roll) in radians
     */
    [[nodiscard]] Vec3f getEulerAngles() const noexcept;
    /// @}

    /// @name Axis-Angle Conversion
    /// @{

    /**
     * @brief Sets the quaternion from a rotation matrix
     * @param mat The rotation matrix
     */
    void setFromRotationMatrix(const Mat4x4f& mat) noexcept;

    /**
     * @brief Sets the quaternion from axis-angle representation
     * @param angle The rotation angle in radians
     * @param axis The rotation axis (should be normalized)
     */
    void setFromAxisAngle(float angle, const Vec3f& axis) noexcept;

    /**
     * @brief Returns a normalized copy of this quaternion
     * @return The normalized quaternion
     */
    [[nodiscard]] Quaternion normalize() const noexcept;

    /**
     * @brief Rotates a vector by this quaternion
     * @param vec The vector to rotate
     * @return The rotated vector
     */
    [[nodiscard]] Vec3f rotateVector(const Vec3f& vec) const noexcept;

    /** @brief Resets to identity quaternion */
    void setIdentity() noexcept;

    /**
     * @brief Sets the quaternion to rotate from one direction to another
     * @param from The source direction
     * @param to The target direction
     */
    void makeRotate(const Vec3f& from, const Vec3f& to) noexcept;

    /**
     * @brief Sets the quaternion from angle and axis
     * @param angle The rotation angle in radians
     * @param axis The rotation axis
     */
    void setAngleAndAxis(const float angle, const Vec3f& axis) noexcept;

    /**
     * @brief Extracts the angle and axis from this quaternion
     * @param angle Output: the rotation angle
     * @param axis Output: the rotation axis
     */
    void getAngleAndAxis(float& angle, Vec3f& axis) const noexcept;

    /** @brief Gets the rotation angle in radians */
    [[nodiscard]] float getAngle() const noexcept;

    /** @brief Gets the rotation axis */
    [[nodiscard]] Vec3f getAxis() const noexcept;
    /// @}

    /// @name Basis Vectors
    /// @{
    [[nodiscard]] Vec3f getXAxis() const noexcept;
    [[nodiscard]] Vec3f getYAxis() const noexcept;
    [[nodiscard]] Vec3f getZAxis() const noexcept;
    /// @}

   public:
    /** @brief Resets to identity quaternion (alias for setIdentity) */
    void clear() noexcept;

    /** @brief Returns the conjugate of this quaternion */
    [[nodiscard]] Quaternion conjugate() const noexcept;

    /** @brief Returns the inverse of this quaternion */
    [[nodiscard]] Quaternion inverse() const noexcept;

    /**
     * @brief Computes the dot product with another quaternion
     * @param quat The other quaternion
     * @return The dot product
     */
    [[nodiscard]] float dot(const Quaternion& quat) const noexcept;

    /** @brief Returns the length (magnitude) of this quaternion */
    [[nodiscard]] float length() const noexcept;

    /** @brief Returns the squared length of this quaternion */
    [[nodiscard]] float lengthSquared() const noexcept;

    /**
     * @brief Spherical linear interpolation to another quaternion
     * @param to The target quaternion
     * @param factor Interpolation factor [0, 1]
     * @return The interpolated quaternion
     */
    [[nodiscard]] Quaternion slerp(const Quaternion& to, float factor) const noexcept;

   public:
    /// @name Assignment Operators
    /// @{
    Quaternion& operator*=(const float& scalar) noexcept;
    Quaternion& operator/=(const float& scalar) noexcept;
    Quaternion& operator+=(const Quaternion& quat) noexcept;
    Quaternion& operator-=(const Quaternion& quat) noexcept;
    Quaternion& operator*=(const Quaternion& quat) noexcept;
    /// @}

    /// @name Arithmetic Operators
    /// @{
    [[nodiscard]] Quaternion operator*(const float& scalar) const noexcept;
    [[nodiscard]] Quaternion operator/(const float& scalar) const noexcept;
    [[nodiscard]] Quaternion operator+(const Quaternion& quat) const noexcept;
    [[nodiscard]] Quaternion operator-(const Quaternion& quat) const noexcept;
    [[nodiscard]] Quaternion operator*(const Quaternion& quat) const noexcept;
    /// @}

    /// @name Comparison Operators
    /// @{
    [[nodiscard]] bool operator==(const Quaternion& quat) const noexcept;
    [[nodiscard]] bool operator!=(const Quaternion& quat) const noexcept;
    /// @}

    [[nodiscard]] Quaternion operator+() const noexcept;
    [[nodiscard]] Quaternion operator-() const noexcept;

    /// @name Subscript Operators
    /// @{
    [[nodiscard]] float& operator[](uint32_t index) noexcept;
    [[nodiscard]] float operator[](uint32_t index) const noexcept;
    /// @}

    /// @name Friend Operators
    /// @{
    friend Quaternion operator*(float scalar, const Quaternion& quat) noexcept;
    friend Vec3f operator*(const Quaternion& quat, const Vec3f& vec) noexcept;
    friend Vec3f operator*(const Vec3f& vec, const Quaternion& quat) noexcept;
    /// @}

   public:
    friend std::ostream& operator<<(std::ostream& os, const Quaternion& quat);

   public:
    /// @name Static Methods
    /// @{

    /**
     * @brief Spherical linear interpolation between two quaternions
     * @param from Start quaternion
     * @param to End quaternion
     * @param factor Interpolation factor [0, 1]
     * @return The interpolated quaternion
     */
    [[nodiscard]] static Quaternion slerp(const Quaternion& from, const Quaternion& to, float factor) noexcept;

    /** @brief Returns a normalized copy of a quaternion */
    [[nodiscard]] static Quaternion normalize(const Quaternion& quat) noexcept;

    /** @brief Returns the conjugate of a quaternion */
    [[nodiscard]] static Quaternion conjugate(const Quaternion& quat) noexcept;

    /** @brief Returns the inverse of a quaternion */
    [[nodiscard]] static Quaternion inverse(const Quaternion& quat) noexcept;

    /** @brief Computes the dot product of two quaternions */
    [[nodiscard]] static float dot(const Quaternion& quat1, const Quaternion& quat2) noexcept;
    /// @}
};

}  // namespace vne::math

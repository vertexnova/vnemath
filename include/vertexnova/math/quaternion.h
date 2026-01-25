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
 * @brief Represents a rotation in 3D space.
 */

// Project includes
#include "mat4x4f.h"
#include "vec3f.h"

// Third-party library includes
#include <glm/gtc/quaternion.hpp>

namespace vne::math {

class Quaternion : public glm::quat {
   public:
    Quaternion() noexcept;
    Quaternion(const Vec4f& vec) noexcept;
    Quaternion(const Vec3f& vec) noexcept;
    Quaternion(float w_param, const Vec3f& vec) noexcept;
    Quaternion(float w_param, float x_param, float y_param, float z_param) noexcept;
    Quaternion(float pitch, float yaw, float roll) noexcept;
    Quaternion(const Mat4x4f& mat) noexcept;
    Quaternion(const glm::quat& q) noexcept;
    Quaternion(const Quaternion& other) noexcept;
    Quaternion& operator=(const Quaternion& quat) noexcept;

   public:
    [[nodiscard]] float getW() const noexcept;
    [[nodiscard]] Vec3f getVector() const noexcept;

   public:
    void setFromEulerAngles(float pitch, float yaw, float roll) noexcept;
    [[nodiscard]] Vec3f getEulerAngles() const noexcept;
    void setFromRotationMatrix(const Mat4x4f& mat) noexcept;
    void setFromAxisAngle(float angle, const Vec3f& axis) noexcept;
    [[nodiscard]] Quaternion normalize() const noexcept;
    [[nodiscard]] Vec3f rotateVector(const Vec3f& vec) const noexcept;
    void setIdentity() noexcept;
    void makeRotate(const Vec3f& from, const Vec3f& to) noexcept;
    void setAngleAndAxis(const float angle, const Vec3f& axis) noexcept;
    void getAngleAndAxis(float& angle, Vec3f& axis) const noexcept;
    [[nodiscard]] float getAngle() const noexcept;
    [[nodiscard]] Vec3f getAxis() const noexcept;
    [[nodiscard]] Vec3f getXAxis() const noexcept;
    [[nodiscard]] Vec3f getYAxis() const noexcept;
    [[nodiscard]] Vec3f getZAxis() const noexcept;

   public:
    void clear() noexcept;
    [[nodiscard]] Quaternion conjugate() const noexcept;
    [[nodiscard]] Quaternion inverse() const noexcept;
    [[nodiscard]] float dot(const Quaternion& quat) const noexcept;
    [[nodiscard]] float length() const noexcept;
    [[nodiscard]] float lengthSquared() const noexcept;
    [[nodiscard]] Quaternion slerp(const Quaternion& to, float factor) const noexcept;

   public:
    Quaternion& operator*=(const float& scalar) noexcept;
    Quaternion& operator/=(const float& scalar) noexcept;
    Quaternion& operator+=(const Quaternion& quat) noexcept;
    Quaternion& operator-=(const Quaternion& quat) noexcept;
    Quaternion& operator*=(const Quaternion& quat) noexcept;
    [[nodiscard]] Quaternion operator*(const float& scalar) const noexcept;
    [[nodiscard]] Quaternion operator/(const float& scalar) const noexcept;
    [[nodiscard]] Quaternion operator+(const Quaternion& quat) const noexcept;
    [[nodiscard]] Quaternion operator-(const Quaternion& quat) const noexcept;
    [[nodiscard]] Quaternion operator*(const Quaternion& quat) const noexcept;
    [[nodiscard]] bool operator==(const Quaternion& quat) const noexcept;
    [[nodiscard]] bool operator!=(const Quaternion& quat) const noexcept;
    [[nodiscard]] Quaternion operator+() const noexcept;
    [[nodiscard]] Quaternion operator-() const noexcept;
    [[nodiscard]] float& operator[](uint32_t index) noexcept;
    [[nodiscard]] float operator[](uint32_t index) const noexcept;

    friend Quaternion operator*(float scalar, const Quaternion& quat) noexcept;
    friend Vec3f operator*(const Quaternion& quat, const Vec3f& vec) noexcept;
    friend Vec3f operator*(const Vec3f& vec, const Quaternion& quat) noexcept;

   public:
    friend std::ostream& operator<<(std::ostream& os, const Quaternion& quat);

   public:
    [[nodiscard]] static Quaternion slerp(const Quaternion& from, const Quaternion& to, float factor) noexcept;
    [[nodiscard]] static Quaternion normalize(const Quaternion& quat) noexcept;
    [[nodiscard]] static Quaternion conjugate(const Quaternion& quat) noexcept;
    [[nodiscard]] static Quaternion inverse(const Quaternion& quat) noexcept;
    [[nodiscard]] static float dot(const Quaternion& quat1, const Quaternion& quat2) noexcept;
};

// Legacy type alias for backward compatibility
using Quaternion_C = Quaternion;

}  // namespace vne::math

// Legacy namespace aliases
namespace VNE {
namespace Math {
using Quaternion_C = vne::math::Quaternion;
using Quaternion = vne::math::Quaternion;
}  // namespace Math
}  // namespace VNE

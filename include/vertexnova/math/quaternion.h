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
    Quaternion();
    Quaternion(const Vec4f& vec);
    Quaternion(const Vec3f& vec);
    Quaternion(float w_param, const Vec3f& vec);
    Quaternion(float w_param, float x_param, float y_param, float z_param);
    Quaternion(float pitch, float yaw, float roll);
    Quaternion(const Mat4x4f& mat);
    Quaternion(const glm::quat& q);
    Quaternion(const Quaternion& other);
    Quaternion& operator=(const Quaternion& quat);

   public:
    float getW() const;
    Vec3f getVector() const;

   public:
    void setFromEulerAngles(float pitch, float yaw, float roll);
    Vec3f getEulerAngles() const;
    void setFromRotationMatrix(const Mat4x4f& mat);
    void setFromAxisAngle(float angle, const Vec3f& axis);
    Quaternion normalize() const;
    Vec3f rotateVector(const Vec3f& vec) const;
    void setIdentity();
    void makeRotate(const Vec3f& from, const Vec3f& to);
    void setAngleAndAxis(const float angle, const Vec3f& axis);
    void getAngleAndAxis(float& angle, Vec3f& axis) const;
    float getAngle() const;
    Vec3f getAxis() const;
    Vec3f getXAxis() const;
    Vec3f getYAxis() const;
    Vec3f getZAxis() const;

   public:
    void clear();
    Quaternion conjugate() const;
    Quaternion inverse() const;
    float dot(const Quaternion& quat) const;
    float length() const;
    float lengthSquared() const;
    Quaternion slerp(const Quaternion& to, float factor) const;

   public:
    Quaternion& operator*=(const float& scalar);
    Quaternion& operator/=(const float& scalar);
    Quaternion& operator+=(const Quaternion& quat);
    Quaternion& operator-=(const Quaternion& quat);
    Quaternion& operator*=(const Quaternion& quat);
    Quaternion operator*(const float& scalar) const;
    Quaternion operator/(const float& scalar) const;
    Quaternion operator+(const Quaternion& quat) const;
    Quaternion operator-(const Quaternion& quat) const;
    Quaternion operator*(const Quaternion& quat) const;
    bool operator==(const Quaternion& quat) const;
    bool operator!=(const Quaternion& quat) const;
    Quaternion operator+() const;
    Quaternion operator-() const;
    float& operator[](uint32_t index);
    float operator[](uint32_t index) const;

    friend Quaternion operator*(float scalar, const Quaternion& quat);
    friend Vec3f operator*(const Quaternion& quat, const Vec3f& vec);
    friend Vec3f operator*(const Vec3f& vec, const Quaternion& quat);

   public:
    friend std::ostream& operator<<(std::ostream& os, const Quaternion& quat);

   public:
    static Quaternion slerp(const Quaternion& from, const Quaternion& to, float factor);
    static Quaternion normalize(const Quaternion& quat);
    static Quaternion conjugate(const Quaternion& quat);
    static Quaternion inverse(const Quaternion& quat);
    static float dot(const Quaternion& quat1, const Quaternion& quat2);
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

#ifndef VNE_MATH_QUATERNION_H
#define VNE_MATH_QUATERNION_H
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
#include "vec3f.h"
#include "mat4x4f.h"

// Third-party library includes
#include <glm/gtc/quaternion.hpp>

namespace VNE {
namespace Math {

class Quaternion_C : public glm::quat {
   public:
    Quaternion_C();
    Quaternion_C(const Vec4f_C& vec);
    Quaternion_C(const Vec3f_C& vec);
    Quaternion_C(float w_param, const Vec3f_C& vec);
    Quaternion_C(float w_param, float x_param, float y_param, float z_param);
    Quaternion_C(float pitch, float yaw, float roll);
    Quaternion_C(const Mat4x4f_C& mat);
    Quaternion_C(const glm::quat& q);
    Quaternion_C(const Quaternion_C& other);
    Quaternion_C& operator=(const Quaternion_C& quat);

   public:
    float GetW() const;
    Vec3f_C GetVector() const;

   public:
    void SetFromEulerAngles(float pitch, float yaw, float roll);
    Vec3f_C GetEulerAngles() const;
    void SetFromRotationMatrix(const Mat4x4f_C& mat);
    void SetFromAxisAngle(float angle, const Vec3f_C& axis);
    Quaternion_C Normalize() const;
    Vec3f_C RotateVector(const Vec3f_C& vec) const;
    void SetIdentity();
    void MakeRotate(const Vec3f_C& from, const Vec3f_C& to);
    void SetAngleAndAxis(const float angle, const Vec3f_C& axis);
    void GetAngleAndAxis(float& angle, Vec3f_C& axis) const;
    float GetAngle() const;
    Vec3f_C GetAxis() const;
    Vec3f_C GetXAxis() const;
    Vec3f_C GetYAxis() const;
    Vec3f_C GetZAxis() const;

   public:
    void Clear();
    Quaternion_C Conjugate() const;
    Quaternion_C Inverse() const;
    float Dot(const Quaternion_C& quat) const;
    float Length() const;
    float LengthSquared() const;
    Quaternion_C Slerp(const Quaternion_C& to, float factor) const;

   public:
    Quaternion_C& operator*=(const float& scalar);
    Quaternion_C& operator/=(const float& scalar);
    Quaternion_C& operator+=(const Quaternion_C& quat);
    Quaternion_C& operator-=(const Quaternion_C& quat);
    Quaternion_C& operator*=(const Quaternion_C& quat);
    Quaternion_C operator*(const float& scalar) const;
    Quaternion_C operator/(const float& scalar) const;
    Quaternion_C operator+(const Quaternion_C& quat) const;
    Quaternion_C operator-(const Quaternion_C& quat) const;
    Quaternion_C operator*(const Quaternion_C& quat) const;
    bool operator==(const Quaternion_C& quat) const;
    bool operator!=(const Quaternion_C& quat) const;
    Quaternion_C operator+() const;
    Quaternion_C operator-() const;
    float& operator[](uint32_t index);
    float operator[](uint32_t index) const;

    friend Quaternion_C operator*(float scalar, const Quaternion_C& quat);
    friend Vec3f_C operator*(const Quaternion_C& quat, const Vec3f_C& vec);
    friend Vec3f_C operator*(const Vec3f_C& vec, const Quaternion_C& quat);

   public:
    friend std::ostream& operator<<(std::ostream& os, const Quaternion_C& quat);

   public:
    static Quaternion_C Slerp(const Quaternion_C& from, const Quaternion_C& to, float factor);
    static Quaternion_C Normalize(const Quaternion_C& quat);
    static Quaternion_C Conjugate(const Quaternion_C& quat);
    static Quaternion_C Inverse(const Quaternion_C& quat);
    static float Dot(const Quaternion_C& quat1, const Quaternion_C& quat2);
};

}  // namespace Math
}  // namespace VNE

#endif  // VNE_MATH_QUATERNION_H

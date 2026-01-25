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

// Project includes
#include "vertexnova/math/quaternion.h"
#include "vertexnova/math/math_utils.h"
#include "vertexnova/common/macros.h"

// Third-party library includes
#include <glm/gtx/quaternion.hpp>

namespace VNE {
namespace Math {

//------------------------------------------------------------------------------
Quaternion_C::Quaternion_C()
    : glm::quat(1.0f, 0.0f, 0.0f, 0.0f) {}

//------------------------------------------------------------------------------
Quaternion_C::Quaternion_C(const Vec4f_C& vec)
    : glm::quat(vec.w, vec.x, vec.y, vec.z) {}

//------------------------------------------------------------------------------
Quaternion_C::Quaternion_C(const Vec3f_C& vec)
    : glm::quat(1.0f, vec.x, vec.y, vec.z) {}

//------------------------------------------------------------------------------
Quaternion_C::Quaternion_C(float w_param, const Vec3f_C& vec)
    : glm::quat(w_param, vec.x, vec.y, vec.z) {}

//------------------------------------------------------------------------------
Quaternion_C::Quaternion_C(float w_param, float x_param, float y_param, float z_param)
    : glm::quat(w_param, x_param, y_param, z_param) {}

//------------------------------------------------------------------------------
Quaternion_C::Quaternion_C(float pitch, float yaw, float roll) {
    SetFromEulerAngles(pitch, yaw, roll);
}

//------------------------------------------------------------------------------
Quaternion_C::Quaternion_C(const Mat4x4f_C& mat) {
    SetFromRotationMatrix(mat);
}

//------------------------------------------------------------------------------
Quaternion_C::Quaternion_C(const glm::quat& q)
    : glm::quat(q) {}

//------------------------------------------------------------------------------
Quaternion_C::Quaternion_C(const Quaternion_C& other)
    : glm::quat(other) {}

//------------------------------------------------------------------------------
Quaternion_C& Quaternion_C::operator=(const Quaternion_C& other) {
    if (this != &other) {
        w = other.w;
        x = other.x;
        y = other.y;
        z = other.z;
    }
    return *this;
}

//------------------------------------------------------------------------------
float Quaternion_C::GetW() const {
    return w;
}

//------------------------------------------------------------------------------
Vec3f_C Quaternion_C::GetVector() const {
    return Vec3f_C(x, y, z);
}

//------------------------------------------------------------------------------
void Quaternion_C::SetFromEulerAngles(float pitch, float yaw, float roll) {
    *this = glm::quat(glm::vec3(pitch, yaw, roll));
}

//------------------------------------------------------------------------------
Vec3f_C Quaternion_C::GetEulerAngles() const {
    return glm::eulerAngles(*this);
}

//------------------------------------------------------------------------------
void Quaternion_C::SetFromRotationMatrix(const Mat4x4f_C& mat) {
    *this = glm::toQuat(glm::mat4(mat));
}

//------------------------------------------------------------------------------
void Quaternion_C::SetFromAxisAngle(float angle, const Vec3f_C& axis) {
    *this = glm::angleAxis(angle, axis);
}

//------------------------------------------------------------------------------
Quaternion_C Quaternion_C::Normalize() const {
    return glm::normalize(*this);
}

//------------------------------------------------------------------------------
Vec3f_C Quaternion_C::RotateVector(const Vec3f_C& vec) const {
    return (*this) * vec;
}

//------------------------------------------------------------------------------
void Quaternion_C::SetIdentity() {
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
    w = 1.0f;
}

//------------------------------------------------------------------------------
void Quaternion_C::MakeRotate(const Vec3f_C& from, const Vec3f_C& to) {
    *this = glm::rotation(from, to);
}

//------------------------------------------------------------------------------
void Quaternion_C::SetAngleAndAxis(const float angle, const Vec3f_C& axis) {
    *this = glm::angleAxis(angle, axis);
}

//------------------------------------------------------------------------------
void Quaternion_C::GetAngleAndAxis(float& angle, Vec3f_C& axis) const {
    angle = GetAngle();
    axis = GetAxis();
}

//------------------------------------------------------------------------------
float Quaternion_C::GetAngle() const {
    return glm::angle(*this);
}

//------------------------------------------------------------------------------
Vec3f_C Quaternion_C::GetAxis() const {
    return glm::axis(*this);
}

//------------------------------------------------------------------------------
Vec3f_C Quaternion_C::GetXAxis() const {
    float fTy = 2.0f * y;
    float fTz = 2.0f * z;
    float fTwy = fTy * w;
    float fTwz = fTz * w;
    float fTxy = fTy * x;
    float fTxz = fTz * x;
    float fTyy = fTy * y;
    float fTzz = fTz * z;

    return Vec3f_C(1.0f - (fTyy + fTzz), fTxy + fTwz, fTxz - fTwy);
}

//------------------------------------------------------------------------------
Vec3f_C Quaternion_C::GetYAxis() const {
    float fTx = 2.0f * x;
    float fTz = 2.0f * z;
    float fTwx = fTx * w;
    float fTwz = fTz * w;
    float fTxy = fTx * y;
    float fTyz = fTz * y;
    float fTxx = fTx * x;
    float fTzz = fTz * z;

    return Vec3f_C(fTxy - fTwz, 1.0f - (fTxx + fTzz), fTyz + fTwx);
}

//------------------------------------------------------------------------------
Vec3f_C Quaternion_C::GetZAxis() const {
    float fTx = 2.0f * x;
    float fTy = 2.0f * y;
    float fTwx = fTx * w;
    float fTwy = fTy * w;
    float fTxz = fTx * z;
    float fTyz = fTy * z;
    float fTxx = fTx * x;
    float fTyy = fTy * y;

    return Vec3f_C(fTxz + fTwy, fTyz - fTwx, 1.0f - (fTxx + fTyy));
}

//------------------------------------------------------------------------------
void Quaternion_C::Clear() {
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
    w = 1.0f;
}

//------------------------------------------------------------------------------
Quaternion_C Quaternion_C::Conjugate() const {
    return glm::conjugate(*this);
}

//------------------------------------------------------------------------------
Quaternion_C Quaternion_C::Inverse() const {
    return glm::inverse(*this);
}

//------------------------------------------------------------------------------
float Quaternion_C::Dot(const Quaternion_C& quat) const {
    return glm::dot(glm::quat(*this), glm::quat(quat));
}

//------------------------------------------------------------------------------
float Quaternion_C::Length() const {
    return glm::length(glm::quat(*this));
}

//------------------------------------------------------------------------------
float Quaternion_C::LengthSquared() const {
    return glm::length2(glm::quat(*this));
}

//------------------------------------------------------------------------------
Quaternion_C& Quaternion_C::operator*=(const float& scalar) {
    w *= scalar;
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

//------------------------------------------------------------------------------
Quaternion_C& Quaternion_C::operator/=(const float& scalar) {
    VNE_ASSERT_MSG(!Math::IsZero(scalar, 1E-5f), "Quaternion_C zero denominator");
    w /= scalar;
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
}

//------------------------------------------------------------------------------
Quaternion_C& Quaternion_C::operator+=(const Quaternion_C& quat) {
    w += quat.w;
    x += quat.x;
    y += quat.y;
    z += quat.z;
    return *this;
}

//------------------------------------------------------------------------------
Quaternion_C& Quaternion_C::operator-=(const Quaternion_C& quat) {
    w -= quat.w;
    x -= quat.x;
    y -= quat.y;
    z -= quat.z;
    return *this;
}

//------------------------------------------------------------------------------
Quaternion_C& Quaternion_C::operator*=(const Quaternion_C& quat) {
    w = w * quat.w - x * quat.x - y * quat.y - z * quat.z;
    x = w * quat.x + x * quat.w + y * quat.z - z * quat.y;
    y = w * quat.y + y * quat.w + z * quat.x - x * quat.z;
    z = w * quat.z + z * quat.w + x * quat.y - y * quat.x;
    return *this;
}

//------------------------------------------------------------------------------
Quaternion_C Quaternion_C::operator*(const float& scalar) const {
    return Quaternion_C(w * scalar, x * scalar, y * scalar, z * scalar);
}

//------------------------------------------------------------------------------
Quaternion_C Quaternion_C::operator/(const float& scalar) const {
    VNE_ASSERT_MSG(!Math::IsZero(scalar, 1E-5f), "Quaternion_C zero denominator");
    return Quaternion_C(w / scalar, x / scalar, y / scalar, z / scalar);
}

//------------------------------------------------------------------------------
Quaternion_C Quaternion_C::operator+(const Quaternion_C& quat) const {
    return Quaternion_C(w + quat.w, x + quat.x, y + quat.y, z + quat.z);
}

//------------------------------------------------------------------------------
Quaternion_C Quaternion_C::operator-(const Quaternion_C& quat) const {
    return Quaternion_C(w - quat.w, x - quat.x, y - quat.y, z - quat.z);
}

//------------------------------------------------------------------------------
Quaternion_C Quaternion_C::operator*(const Quaternion_C& quat) const {
    float w_param = (this->w * quat.w) - Math::Vec3f_C::Dot(this->GetVector(), quat.GetVector());
    Vec3f_C vec = Math::Vec3f_C::Cross(this->GetVector(), quat.GetVector()) + (this->GetVector() * quat.w) + (quat.GetVector() * this->w);

    return Quaternion_C(w_param, vec);
}

//------------------------------------------------------------------------------
bool Quaternion_C::operator==(const Quaternion_C& quat) const {
    return (w == quat.w) && (x == quat.x) && (y == quat.y) && (z == quat.z);
}

//------------------------------------------------------------------------------
bool Quaternion_C::operator!=(const Quaternion_C& quat) const {
    return (w != quat.w) || (x != quat.x) || (y != quat.y) || (z != quat.z);
}

//------------------------------------------------------------------------------
Quaternion_C Quaternion_C::operator+() const {
    return Quaternion_C(w, x, y, z);
}

//------------------------------------------------------------------------------
Quaternion_C Quaternion_C::operator-() const {
    return Quaternion_C(-w, -x, -y, -z);
}

//------------------------------------------------------------------------------
float& Quaternion_C::operator[](uint32_t index) {
    VNE_ASSERT_MSG(index < 4, "Quaternion_C index out of bounds");
    return (&x)[index];
}

//------------------------------------------------------------------------------
float Quaternion_C::operator[](uint32_t index) const {
    VNE_ASSERT_MSG(index < 4, "Quaternion_C index out of bounds");
    return (&x)[index];
}

//------------------------------------------------------------------------------
Quaternion_C operator*(float scalar, const Quaternion_C& quat) {
    return Quaternion_C(quat.w * scalar, quat.x * scalar, quat.y * scalar, quat.z * scalar);
}

//------------------------------------------------------------------------------
Vec3f_C operator*(const Quaternion_C& q, const Vec3f_C& v) {
    Vec3f_C u = q.GetVector();
    Vec3f_C uv = u.Cross(v);
    Vec3f_C uuv = u.Cross(uv);
    return v + ((uv * q.w) + uuv) * 2.0f;
}

//------------------------------------------------------------------------------
Vec3f_C operator*(const Vec3f_C& vec, const Quaternion_C& quat) {
    return quat.Inverse() * vec;
}

//------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const Quaternion_C& quat) {
    return os << "[" << quat.w << ", " << quat.x << ", " << quat.y << ", " << quat.z << "]";
}

//------------------------------------------------------------------------------
Quaternion_C Quaternion_C::Slerp(const Quaternion_C& from, const Quaternion_C& to, float factor) {
    return glm::slerp(from, to, factor);
}

//------------------------------------------------------------------------------
Quaternion_C Quaternion_C::Normalize(const Quaternion_C& quat) {
    return glm::normalize(quat);
}

//------------------------------------------------------------------------------
Quaternion_C Quaternion_C::Conjugate(const Quaternion_C& quat) {
    return glm::conjugate(quat);
}

//------------------------------------------------------------------------------
Quaternion_C Quaternion_C::Inverse(const Quaternion_C& quat) {
    return glm::inverse(quat);
}

//------------------------------------------------------------------------------
float Quaternion_C::Dot(const Quaternion_C& quat1, const Quaternion_C& quat2) {
    return quat1.Dot(quat2);
}

}  // namespace Math
}  // namespace VNE

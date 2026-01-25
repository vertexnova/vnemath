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

namespace vne::math {

//------------------------------------------------------------------------------
Quaternion::Quaternion()
    : glm::quat(1.0f, 0.0f, 0.0f, 0.0f) {}

//------------------------------------------------------------------------------
Quaternion::Quaternion(const Vec4f& vec)
    : glm::quat(vec.w, vec.x, vec.y, vec.z) {}

//------------------------------------------------------------------------------
Quaternion::Quaternion(const Vec3f& vec)
    : glm::quat(1.0f, vec.x, vec.y, vec.z) {}

//------------------------------------------------------------------------------
Quaternion::Quaternion(float w_param, const Vec3f& vec)
    : glm::quat(w_param, vec.x, vec.y, vec.z) {}

//------------------------------------------------------------------------------
Quaternion::Quaternion(float w_param, float x_param, float y_param, float z_param)
    : glm::quat(w_param, x_param, y_param, z_param) {}

//------------------------------------------------------------------------------
Quaternion::Quaternion(float pitch, float yaw, float roll) {
    setFromEulerAngles(pitch, yaw, roll);
}

//------------------------------------------------------------------------------
Quaternion::Quaternion(const Mat4x4f& mat) {
    setFromRotationMatrix(mat);
}

//------------------------------------------------------------------------------
Quaternion::Quaternion(const glm::quat& q)
    : glm::quat(q) {}

//------------------------------------------------------------------------------
Quaternion::Quaternion(const Quaternion& other)
    : glm::quat(other) {}

//------------------------------------------------------------------------------
Quaternion& Quaternion::operator=(const Quaternion& other) {
    if (this != &other) {
        w = other.w;
        x = other.x;
        y = other.y;
        z = other.z;
    }
    return *this;
}

//------------------------------------------------------------------------------
float Quaternion::getW() const {
    return w;
}

//------------------------------------------------------------------------------
Vec3f Quaternion::getVector() const {
    return Vec3f(x, y, z);
}

//------------------------------------------------------------------------------
void Quaternion::setFromEulerAngles(float pitch, float yaw, float roll) {
    *this = glm::quat(glm::vec3(pitch, yaw, roll));
}

//------------------------------------------------------------------------------
Vec3f Quaternion::getEulerAngles() const {
    return glm::eulerAngles(*this);
}

//------------------------------------------------------------------------------
void Quaternion::setFromRotationMatrix(const Mat4x4f& mat) {
    *this = glm::toQuat(glm::mat4(mat));
}

//------------------------------------------------------------------------------
void Quaternion::setFromAxisAngle(float angle, const Vec3f& axis) {
    *this = glm::angleAxis(angle, axis);
}

//------------------------------------------------------------------------------
Quaternion Quaternion::normalize() const {
    return glm::normalize(*this);
}

//------------------------------------------------------------------------------
Vec3f Quaternion::rotateVector(const Vec3f& vec) const {
    return (*this) * vec;
}

//------------------------------------------------------------------------------
void Quaternion::setIdentity() {
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
    w = 1.0f;
}

//------------------------------------------------------------------------------
void Quaternion::makeRotate(const Vec3f& from, const Vec3f& to) {
    *this = glm::rotation(from, to);
}

//------------------------------------------------------------------------------
void Quaternion::setAngleAndAxis(const float angle, const Vec3f& axis) {
    *this = glm::angleAxis(angle, axis);
}

//------------------------------------------------------------------------------
void Quaternion::getAngleAndAxis(float& angle, Vec3f& axis) const {
    angle = getAngle();
    axis = getAxis();
}

//------------------------------------------------------------------------------
float Quaternion::getAngle() const {
    return glm::angle(*this);
}

//------------------------------------------------------------------------------
Vec3f Quaternion::getAxis() const {
    return glm::axis(*this);
}

//------------------------------------------------------------------------------
Vec3f Quaternion::getXAxis() const {
    float fTy = 2.0f * y;
    float fTz = 2.0f * z;
    float fTwy = fTy * w;
    float fTwz = fTz * w;
    float fTxy = fTy * x;
    float fTxz = fTz * x;
    float fTyy = fTy * y;
    float fTzz = fTz * z;

    return Vec3f(1.0f - (fTyy + fTzz), fTxy + fTwz, fTxz - fTwy);
}

//------------------------------------------------------------------------------
Vec3f Quaternion::getYAxis() const {
    float fTx = 2.0f * x;
    float fTz = 2.0f * z;
    float fTwx = fTx * w;
    float fTwz = fTz * w;
    float fTxy = fTx * y;
    float fTyz = fTz * y;
    float fTxx = fTx * x;
    float fTzz = fTz * z;

    return Vec3f(fTxy - fTwz, 1.0f - (fTxx + fTzz), fTyz + fTwx);
}

//------------------------------------------------------------------------------
Vec3f Quaternion::getZAxis() const {
    float fTx = 2.0f * x;
    float fTy = 2.0f * y;
    float fTwx = fTx * w;
    float fTwy = fTy * w;
    float fTxz = fTx * z;
    float fTyz = fTy * z;
    float fTxx = fTx * x;
    float fTyy = fTy * y;

    return Vec3f(fTxz + fTwy, fTyz - fTwx, 1.0f - (fTxx + fTyy));
}

//------------------------------------------------------------------------------
void Quaternion::clear() {
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
    w = 1.0f;
}

//------------------------------------------------------------------------------
Quaternion Quaternion::conjugate() const {
    return glm::conjugate(*this);
}

//------------------------------------------------------------------------------
Quaternion Quaternion::inverse() const {
    return glm::inverse(*this);
}

//------------------------------------------------------------------------------
float Quaternion::dot(const Quaternion& quat) const {
    return glm::dot(glm::quat(*this), glm::quat(quat));
}

//------------------------------------------------------------------------------
float Quaternion::length() const {
    return glm::length(glm::quat(*this));
}

//------------------------------------------------------------------------------
float Quaternion::lengthSquared() const {
    return glm::length2(glm::quat(*this));
}

//------------------------------------------------------------------------------
Quaternion& Quaternion::operator*=(const float& scalar) {
    w *= scalar;
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

//------------------------------------------------------------------------------
Quaternion& Quaternion::operator/=(const float& scalar) {
    VNE_ASSERT_MSG(!vne::math::isZero(scalar, 1E-5f), "Quaternion zero denominator");
    w /= scalar;
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
}

//------------------------------------------------------------------------------
Quaternion& Quaternion::operator+=(const Quaternion& quat) {
    w += quat.w;
    x += quat.x;
    y += quat.y;
    z += quat.z;
    return *this;
}

//------------------------------------------------------------------------------
Quaternion& Quaternion::operator-=(const Quaternion& quat) {
    w -= quat.w;
    x -= quat.x;
    y -= quat.y;
    z -= quat.z;
    return *this;
}

//------------------------------------------------------------------------------
Quaternion& Quaternion::operator*=(const Quaternion& quat) {
    w = w * quat.w - x * quat.x - y * quat.y - z * quat.z;
    x = w * quat.x + x * quat.w + y * quat.z - z * quat.y;
    y = w * quat.y + y * quat.w + z * quat.x - x * quat.z;
    z = w * quat.z + z * quat.w + x * quat.y - y * quat.x;
    return *this;
}

//------------------------------------------------------------------------------
Quaternion Quaternion::operator*(const float& scalar) const {
    return Quaternion(w * scalar, x * scalar, y * scalar, z * scalar);
}

//------------------------------------------------------------------------------
Quaternion Quaternion::operator/(const float& scalar) const {
    VNE_ASSERT_MSG(!vne::math::isZero(scalar, 1E-5f), "Quaternion zero denominator");
    return Quaternion(w / scalar, x / scalar, y / scalar, z / scalar);
}

//------------------------------------------------------------------------------
Quaternion Quaternion::operator+(const Quaternion& quat) const {
    return Quaternion(w + quat.w, x + quat.x, y + quat.y, z + quat.z);
}

//------------------------------------------------------------------------------
Quaternion Quaternion::operator-(const Quaternion& quat) const {
    return Quaternion(w - quat.w, x - quat.x, y - quat.y, z - quat.z);
}

//------------------------------------------------------------------------------
Quaternion Quaternion::operator*(const Quaternion& quat) const {
    float w_param = (this->w * quat.w) - Vec3f::dot(this->getVector(), quat.getVector());
    Vec3f vec =
        Vec3f::cross(this->getVector(), quat.getVector()) + (this->getVector() * quat.w) + (quat.getVector() * this->w);

    return Quaternion(w_param, vec);
}

//------------------------------------------------------------------------------
bool Quaternion::operator==(const Quaternion& quat) const {
    return (w == quat.w) && (x == quat.x) && (y == quat.y) && (z == quat.z);
}

//------------------------------------------------------------------------------
bool Quaternion::operator!=(const Quaternion& quat) const {
    return (w != quat.w) || (x != quat.x) || (y != quat.y) || (z != quat.z);
}

//------------------------------------------------------------------------------
Quaternion Quaternion::operator+() const {
    return Quaternion(w, x, y, z);
}

//------------------------------------------------------------------------------
Quaternion Quaternion::operator-() const {
    return Quaternion(-w, -x, -y, -z);
}

//------------------------------------------------------------------------------
float& Quaternion::operator[](uint32_t index) {
    VNE_ASSERT_MSG(index < 4, "Quaternion index out of bounds");
    return (&x)[index];
}

//------------------------------------------------------------------------------
float Quaternion::operator[](uint32_t index) const {
    VNE_ASSERT_MSG(index < 4, "Quaternion index out of bounds");
    return (&x)[index];
}

//------------------------------------------------------------------------------
Quaternion operator*(float scalar, const Quaternion& quat) {
    return Quaternion(quat.w * scalar, quat.x * scalar, quat.y * scalar, quat.z * scalar);
}

//------------------------------------------------------------------------------
Vec3f operator*(const Quaternion& q, const Vec3f& v) {
    Vec3f u = q.getVector();
    Vec3f uv = u.cross(v);
    Vec3f uuv = u.cross(uv);
    return v + ((uv * q.w) + uuv) * 2.0f;
}

//------------------------------------------------------------------------------
Vec3f operator*(const Vec3f& vec, const Quaternion& quat) {
    return quat.inverse() * vec;
}

//------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const Quaternion& quat) {
    return os << "[" << quat.w << ", " << quat.x << ", " << quat.y << ", " << quat.z << "]";
}

//------------------------------------------------------------------------------
Quaternion Quaternion::slerp(const Quaternion& from, const Quaternion& to, float factor) {
    return glm::slerp(from, to, factor);
}

//------------------------------------------------------------------------------
Quaternion Quaternion::normalize(const Quaternion& quat) {
    return glm::normalize(quat);
}

//------------------------------------------------------------------------------
Quaternion Quaternion::conjugate(const Quaternion& quat) {
    return glm::conjugate(quat);
}

//------------------------------------------------------------------------------
Quaternion Quaternion::inverse(const Quaternion& quat) {
    return glm::inverse(quat);
}

//------------------------------------------------------------------------------
float Quaternion::dot(const Quaternion& quat1, const Quaternion& quat2) {
    return quat1.dot(quat2);
}

}  // namespace vne::math

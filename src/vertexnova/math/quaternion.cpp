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

// Corresponding header
#include "vertexnova/math/quaternion.h"

// Project headers
#include "vertexnova/common/macros.h"
#include "vertexnova/math/math_utils.h"

// Third-party headers
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
    return {x, y, z};
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
    float f_ty = 2.0f * y;
    float f_tz = 2.0f * z;
    float f_twy = f_ty * w;
    float f_twz = f_tz * w;
    float f_txy = f_ty * x;
    float f_txz = f_tz * x;
    float f_tyy = f_ty * y;
    float f_tzz = f_tz * z;

    return {1.0f - (f_tyy + f_tzz), f_txy + f_twz, f_txz - f_twy};
}

//------------------------------------------------------------------------------
Vec3f Quaternion::getYAxis() const {
    float f_tx = 2.0f * x;
    float f_tz = 2.0f * z;
    float f_twx = f_tx * w;
    float f_twz = f_tz * w;
    float f_txy = f_tx * y;
    float f_tyz = f_tz * y;
    float f_txx = f_tx * x;
    float f_tzz = f_tz * z;

    return {f_txy - f_twz, 1.0f - (f_txx + f_tzz), f_tyz + f_twx};
}

//------------------------------------------------------------------------------
Vec3f Quaternion::getZAxis() const {
    float f_tx = 2.0f * x;
    float f_ty = 2.0f * y;
    float f_twx = f_tx * w;
    float f_twy = f_ty * w;
    float f_txz = f_tx * z;
    float f_tyz = f_ty * z;
    float f_txx = f_tx * x;
    float f_tyy = f_ty * y;

    return {f_txz + f_twy, f_tyz - f_twx, 1.0f - (f_txx + f_tyy)};
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
    VNE_ASSERT_MSG(!vne::math::isZero(scalar, kZeroTolerance), "Quaternion zero denominator");
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
    return {w * scalar, x * scalar, y * scalar, z * scalar};
}

//------------------------------------------------------------------------------
Quaternion Quaternion::operator/(const float& scalar) const {
    VNE_ASSERT_MSG(!vne::math::isZero(scalar, kZeroTolerance), "Quaternion zero denominator");
    return {w / scalar, x / scalar, y / scalar, z / scalar};
}

//------------------------------------------------------------------------------
Quaternion Quaternion::operator+(const Quaternion& quat) const {
    return {w + quat.w, x + quat.x, y + quat.y, z + quat.z};
}

//------------------------------------------------------------------------------
Quaternion Quaternion::operator-(const Quaternion& quat) const {
    return {w - quat.w, x - quat.x, y - quat.y, z - quat.z};
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
    return {w, x, y, z};
}

//------------------------------------------------------------------------------
Quaternion Quaternion::operator-() const {
    return {-w, -x, -y, -z};
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
    return {quat.w * scalar, quat.x * scalar, quat.y * scalar, quat.z * scalar};
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

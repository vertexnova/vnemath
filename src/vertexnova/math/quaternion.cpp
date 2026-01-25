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
Quaternion::Quaternion() noexcept
    : glm::quat(1.0f, 0.0f, 0.0f, 0.0f) {}

//------------------------------------------------------------------------------
Quaternion::Quaternion(const Vec4f& vec) noexcept
    : glm::quat(vec.w, vec.x, vec.y, vec.z) {}

//------------------------------------------------------------------------------
Quaternion::Quaternion(const Vec3f& vec) noexcept
    : glm::quat(1.0f, vec.x, vec.y, vec.z) {}

//------------------------------------------------------------------------------
Quaternion::Quaternion(float w_param, const Vec3f& vec) noexcept
    : glm::quat(w_param, vec.x, vec.y, vec.z) {}

//------------------------------------------------------------------------------
Quaternion::Quaternion(float w_param, float x_param, float y_param, float z_param) noexcept
    : glm::quat(w_param, x_param, y_param, z_param) {}

//------------------------------------------------------------------------------
Quaternion::Quaternion(float pitch, float yaw, float roll) noexcept {
    setFromEulerAngles(pitch, yaw, roll);
}

//------------------------------------------------------------------------------
Quaternion::Quaternion(const Mat4x4f& mat) noexcept {
    setFromRotationMatrix(mat);
}

//------------------------------------------------------------------------------
Quaternion::Quaternion(const glm::quat& q) noexcept
    : glm::quat(q) {}

//------------------------------------------------------------------------------
Quaternion::Quaternion(const Quaternion& other) noexcept
    : glm::quat(other) {}

//------------------------------------------------------------------------------
Quaternion& Quaternion::operator=(const Quaternion& other) noexcept {
    if (this != &other) {
        w = other.w;
        x = other.x;
        y = other.y;
        z = other.z;
    }
    return *this;
}

//------------------------------------------------------------------------------
float Quaternion::getW() const noexcept {
    return w;
}

//------------------------------------------------------------------------------
Vec3f Quaternion::getVector() const noexcept {
    return {x, y, z};
}

//------------------------------------------------------------------------------
void Quaternion::setFromEulerAngles(float pitch, float yaw, float roll) noexcept {
    *this = glm::quat(glm::vec3(pitch, yaw, roll));
}

//------------------------------------------------------------------------------
Vec3f Quaternion::getEulerAngles() const noexcept {
    return glm::eulerAngles(*this);
}

//------------------------------------------------------------------------------
void Quaternion::setFromRotationMatrix(const Mat4x4f& mat) noexcept {
    *this = glm::toQuat(glm::mat4(mat));
}

//------------------------------------------------------------------------------
void Quaternion::setFromAxisAngle(float angle, const Vec3f& axis) noexcept {
    *this = glm::angleAxis(angle, axis);
}

//------------------------------------------------------------------------------
Quaternion Quaternion::normalize() const noexcept {
    return glm::normalize(*this);
}

//------------------------------------------------------------------------------
Vec3f Quaternion::rotateVector(const Vec3f& vec) const noexcept {
    return (*this) * vec;
}

//------------------------------------------------------------------------------
void Quaternion::setIdentity() noexcept {
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
    w = 1.0f;
}

//------------------------------------------------------------------------------
void Quaternion::makeRotate(const Vec3f& from, const Vec3f& to) noexcept {
    *this = glm::rotation(from, to);
}

//------------------------------------------------------------------------------
void Quaternion::setAngleAndAxis(const float angle, const Vec3f& axis) noexcept {
    *this = glm::angleAxis(angle, axis);
}

//------------------------------------------------------------------------------
void Quaternion::getAngleAndAxis(float& angle, Vec3f& axis) const noexcept {
    angle = getAngle();
    axis = getAxis();
}

//------------------------------------------------------------------------------
float Quaternion::getAngle() const noexcept {
    return glm::angle(*this);
}

//------------------------------------------------------------------------------
Vec3f Quaternion::getAxis() const noexcept {
    return glm::axis(*this);
}

//------------------------------------------------------------------------------
Vec3f Quaternion::getXAxis() const noexcept {
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
Vec3f Quaternion::getYAxis() const noexcept {
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
Vec3f Quaternion::getZAxis() const noexcept {
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
void Quaternion::clear() noexcept {
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
    w = 1.0f;
}

//------------------------------------------------------------------------------
Quaternion Quaternion::conjugate() const noexcept {
    return glm::conjugate(*this);
}

//------------------------------------------------------------------------------
Quaternion Quaternion::inverse() const noexcept {
    return glm::inverse(*this);
}

//------------------------------------------------------------------------------
float Quaternion::dot(const Quaternion& quat) const noexcept {
    return glm::dot(glm::quat(*this), glm::quat(quat));
}

//------------------------------------------------------------------------------
float Quaternion::length() const noexcept {
    return glm::length(glm::quat(*this));
}

//------------------------------------------------------------------------------
float Quaternion::lengthSquared() const noexcept {
    return glm::length2(glm::quat(*this));
}

//------------------------------------------------------------------------------
Quaternion Quaternion::slerp(const Quaternion& to, float factor) const noexcept {
    return glm::slerp(*this, to, factor);
}

//------------------------------------------------------------------------------
Quaternion& Quaternion::operator*=(const float& scalar) noexcept {
    w *= scalar;
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

//------------------------------------------------------------------------------
Quaternion& Quaternion::operator/=(const float& scalar) noexcept {
    VNE_ASSERT_MSG(!vne::math::isZero(scalar, kZeroTolerance), "Quaternion zero denominator");
    w /= scalar;
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
}

//------------------------------------------------------------------------------
Quaternion& Quaternion::operator+=(const Quaternion& quat) noexcept {
    w += quat.w;
    x += quat.x;
    y += quat.y;
    z += quat.z;
    return *this;
}

//------------------------------------------------------------------------------
Quaternion& Quaternion::operator-=(const Quaternion& quat) noexcept {
    w -= quat.w;
    x -= quat.x;
    y -= quat.y;
    z -= quat.z;
    return *this;
}

//------------------------------------------------------------------------------
Quaternion& Quaternion::operator*=(const Quaternion& quat) noexcept {
    w = w * quat.w - x * quat.x - y * quat.y - z * quat.z;
    x = w * quat.x + x * quat.w + y * quat.z - z * quat.y;
    y = w * quat.y + y * quat.w + z * quat.x - x * quat.z;
    z = w * quat.z + z * quat.w + x * quat.y - y * quat.x;
    return *this;
}

//------------------------------------------------------------------------------
Quaternion Quaternion::operator*(const float& scalar) const noexcept {
    return {w * scalar, x * scalar, y * scalar, z * scalar};
}

//------------------------------------------------------------------------------
Quaternion Quaternion::operator/(const float& scalar) const noexcept {
    VNE_ASSERT_MSG(!vne::math::isZero(scalar, kZeroTolerance), "Quaternion zero denominator");
    return {w / scalar, x / scalar, y / scalar, z / scalar};
}

//------------------------------------------------------------------------------
Quaternion Quaternion::operator+(const Quaternion& quat) const noexcept {
    return {w + quat.w, x + quat.x, y + quat.y, z + quat.z};
}

//------------------------------------------------------------------------------
Quaternion Quaternion::operator-(const Quaternion& quat) const noexcept {
    return {w - quat.w, x - quat.x, y - quat.y, z - quat.z};
}

//------------------------------------------------------------------------------
Quaternion Quaternion::operator*(const Quaternion& quat) const noexcept {
    float w_param = (this->w * quat.w) - Vec3f::dot(this->getVector(), quat.getVector());
    Vec3f vec =
        Vec3f::cross(this->getVector(), quat.getVector()) + (this->getVector() * quat.w) + (quat.getVector() * this->w);

    return Quaternion(w_param, vec);
}

//------------------------------------------------------------------------------
bool Quaternion::operator==(const Quaternion& quat) const noexcept {
    return (w == quat.w) && (x == quat.x) && (y == quat.y) && (z == quat.z);
}

//------------------------------------------------------------------------------
bool Quaternion::operator!=(const Quaternion& quat) const noexcept {
    return (w != quat.w) || (x != quat.x) || (y != quat.y) || (z != quat.z);
}

//------------------------------------------------------------------------------
Quaternion Quaternion::operator+() const noexcept {
    return {w, x, y, z};
}

//------------------------------------------------------------------------------
Quaternion Quaternion::operator-() const noexcept {
    return {-w, -x, -y, -z};
}

//------------------------------------------------------------------------------
float& Quaternion::operator[](uint32_t index) noexcept {
    VNE_ASSERT_MSG(index < 4, "Quaternion index out of bounds");
    return (&x)[index];
}

//------------------------------------------------------------------------------
float Quaternion::operator[](uint32_t index) const noexcept {
    VNE_ASSERT_MSG(index < 4, "Quaternion index out of bounds");
    return (&x)[index];
}

//------------------------------------------------------------------------------
Quaternion operator*(float scalar, const Quaternion& quat) noexcept {
    return {quat.w * scalar, quat.x * scalar, quat.y * scalar, quat.z * scalar};
}

//------------------------------------------------------------------------------
Vec3f operator*(const Quaternion& q, const Vec3f& v) noexcept {
    Vec3f u = q.getVector();
    Vec3f uv = u.cross(v);
    Vec3f uuv = u.cross(uv);
    return v + ((uv * q.w) + uuv) * 2.0f;
}

//------------------------------------------------------------------------------
Vec3f operator*(const Vec3f& vec, const Quaternion& quat) noexcept {
    return quat.inverse() * vec;
}

//------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const Quaternion& quat) {
    return os << "[" << quat.w << ", " << quat.x << ", " << quat.y << ", " << quat.z << "]";
}

//------------------------------------------------------------------------------
Quaternion Quaternion::slerp(const Quaternion& from, const Quaternion& to, float factor) noexcept {
    return glm::slerp(from, to, factor);
}

//------------------------------------------------------------------------------
Quaternion Quaternion::normalize(const Quaternion& quat) noexcept {
    return glm::normalize(quat);
}

//------------------------------------------------------------------------------
Quaternion Quaternion::conjugate(const Quaternion& quat) noexcept {
    return glm::conjugate(quat);
}

//------------------------------------------------------------------------------
Quaternion Quaternion::inverse(const Quaternion& quat) noexcept {
    return glm::inverse(quat);
}

//------------------------------------------------------------------------------
float Quaternion::dot(const Quaternion& quat1, const Quaternion& quat2) noexcept {
    return quat1.dot(quat2);
}

}  // namespace vne::math

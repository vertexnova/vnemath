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
#include "vertexnova/math/mat4x4f.h"

// Project headers
#include "vertexnova/common/macros.h"
#include "vertexnova/math/math_utils.h"

// Third-party headers
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/transform.hpp>

namespace vne::math {

//------------------------------------------------------------------------------
Mat4x4f::Mat4x4f() noexcept
    : glm::mat4() {}

//------------------------------------------------------------------------------
Mat4x4f::Mat4x4f(const Vec4f& col0, const Vec4f& col1, const Vec4f& col2, const Vec4f& col3) noexcept
    : glm::mat4(col0, col1, col2, col3) {}

//------------------------------------------------------------------------------
Mat4x4f::Mat4x4f(const glm::mat4& other) noexcept
    : glm::mat4(other) {}

//------------------------------------------------------------------------------
Mat4x4f::Mat4x4f(const Mat4x4f& other) noexcept
    : glm::mat4(other) {}

//------------------------------------------------------------------------------
Mat4x4f::Mat4x4f(const glm::mat3& other) noexcept
    : glm::mat4(other) {}

//------------------------------------------------------------------------------
Mat4x4f::Mat4x4f(const Mat3x3f& other) noexcept
    : glm::mat4(other) {}

//------------------------------------------------------------------------------
Mat4x4f::Mat4x4f(float scalar) noexcept
    : glm::mat4(scalar) {}

//------------------------------------------------------------------------------
Mat4x4f::Mat4x4f(float x0,
                 float y0,
                 float z0,
                 float w0,
                 float x1,
                 float y1,
                 float z1,
                 float w1,
                 float x2,
                 float y2,
                 float z2,
                 float w2,
                 float x3,
                 float y3,
                 float z3,
                 float w3) noexcept
    : glm::mat4(x0, y0, z0, w0, x1, y1, z1, w1, x2, y2, z2, w2, x3, y3, z3, w3) {}

//------------------------------------------------------------------------------
Mat4x4f& Mat4x4f::operator=(const Mat4x4f& other) noexcept {
    if (this != &other) {
        glm::mat4::operator=(other);
    }
    return *this;
}

//------------------------------------------------------------------------------
Mat4x4f Mat4x4f::transform(const Vec3f& x_axis, const Vec3f& y_axis, const Vec3f& z_axis) noexcept {
    return Mat4x4f(Vec4f(x_axis, 0.0f), Vec4f(y_axis, 0.0f), Vec4f(z_axis, 0.0f), Vec4f(0.0f, 0.0f, 0.0f, 1.0f));
}

//------------------------------------------------------------------------------
Mat4x4f Mat4x4f::transform(const Vec3f& x_axis, const Vec3f& y_axis, const Vec3f& z_axis, const Vec3f& offset) noexcept {
    return Mat4x4f(Vec4f(x_axis, 0.0f), Vec4f(y_axis, 0.0f), Vec4f(z_axis, 0.0f), Vec4f(offset, 1.0f));
}

//------------------------------------------------------------------------------
Mat4x4f Mat4x4f::transform(const Vec3f& forward, const Vec3f& up) noexcept {
    Vec3f x_axis = Vec3f::normalized(forward);
    Vec3f y_axis = Vec3f::normalized(up.cross(x_axis));
    Vec3f z_axis = x_axis.cross(y_axis);

    return transform(x_axis, y_axis, z_axis);
}

//------------------------------------------------------------------------------
Mat4x4f Mat4x4f::transform(const Vec3f& offset) noexcept {
    return Mat4x4f(Vec4f(1.0f, 0.0f, 0.0f, 0.0f),
                   Vec4f(0.0f, 1.0f, 0.0f, 0.0f),
                   Vec4f(0.0f, 0.0f, 1.0f, 0.0f),
                   Vec4f(offset, 1.0f));
}

//------------------------------------------------------------------------------
float Mat4x4f::determinant() const noexcept {
    return glm::determinant(*this);
}

//------------------------------------------------------------------------------
Mat4x4f Mat4x4f::transpose() const noexcept {
    return glm::transpose(*this);
}

//------------------------------------------------------------------------------
Mat4x4f Mat4x4f::inverse() const noexcept {
    return glm::inverse(*this);
}

//------------------------------------------------------------------------------
Mat4x4f Mat4x4f::normalMatrix() const noexcept {
    return glm::transpose(glm::inverse(*this));
}

//------------------------------------------------------------------------------
Mat4x4f Mat4x4f::inverseTransposed() const noexcept {
    glm::mat4 temp = *this;
    return glm::inverseTranspose(temp);
}

//------------------------------------------------------------------------------
bool Mat4x4f::areSame(const Mat4x4f& other, float eps) const noexcept {
    const int matrix_length = static_cast<int>(Mat4x4f::length());
    for (int i = 0; i < matrix_length; ++i) {
        for (int j = 0; j < matrix_length; ++j) {
            if (!vne::math::areSame((*this)[i][j], other[i][j], eps)) {
                return false;
            }
        }
    }
    return true;
}

//------------------------------------------------------------------------------
bool Mat4x4f::isOrthogonal(float eps) const noexcept {
    if (vne::math::areSame(xAxis().lengthSquare(), 1.0f, eps) && vne::math::areSame(yAxis().lengthSquare(), 1.0f, eps)
        && vne::math::areSame(zAxis().lengthSquare(), 1.0f, eps)) {
        if (vne::math::isZero(xAxis().dot(yAxis()), eps) && vne::math::isZero(yAxis().dot(zAxis()), eps)
            && vne::math::isZero(zAxis().dot(xAxis()), eps)) {
            return true;
        }
    }
    return false;
}

//------------------------------------------------------------------------------
Mat4x4f Mat4x4f::operator+(const Mat4x4f& other) const noexcept {
    return Mat4x4f(static_cast<glm::mat4>(*this) + static_cast<glm::mat4>(other));
}

//------------------------------------------------------------------------------
Mat4x4f& Mat4x4f::operator+=(const Mat4x4f& other) noexcept {
    *this = *this + other;
    return *this;
}

//------------------------------------------------------------------------------
Mat4x4f Mat4x4f::operator-(const Mat4x4f& other) const noexcept {
    return Mat4x4f(static_cast<glm::mat4>(*this) - static_cast<glm::mat4>(other));
}

//------------------------------------------------------------------------------
Mat4x4f& Mat4x4f::operator-=(const Mat4x4f& other) noexcept {
    *this = *this - other;
    return *this;
}

//------------------------------------------------------------------------------
Mat4x4f Mat4x4f::operator*(const Mat4x4f& other) const noexcept {
    return Mat4x4f(static_cast<glm::mat4>(*this) * static_cast<glm::mat4>(other));
}

//------------------------------------------------------------------------------
Mat4x4f& Mat4x4f::operator*=(const Mat4x4f& other) noexcept {
    *this = *this * other;
    return *this;
}

//------------------------------------------------------------------------------
Mat4x4f Mat4x4f::operator*(float scalar) const noexcept {
    return Mat4x4f(static_cast<glm::mat4>(*this) * scalar);
}

//------------------------------------------------------------------------------
Mat4x4f& Mat4x4f::operator*=(float scalar) noexcept {
    *this = *this * scalar;
    return *this;
}

//------------------------------------------------------------------------------
Mat4x4f Mat4x4f::operator/(float scalar) const noexcept {
    VNE_ASSERT_MSG(!vne::math::isZero(scalar, kZeroTolerance), "Vec3f zero denominator");
    return Mat4x4f(static_cast<glm::mat4>(*this) / scalar);
}

//------------------------------------------------------------------------------
Mat4x4f& Mat4x4f::operator/=(float scalar) noexcept {
    VNE_ASSERT_MSG(!vne::math::isZero(scalar, kZeroTolerance), "Vec3f zero denominator");
    *this = *this / scalar;
    return *this;
}

//------------------------------------------------------------------------------
Vec4f Mat4x4f::getColumn(uint32_t idx) const noexcept {
    VNE_ASSERT_MSG(idx < length(), "Mat4x4f index out of bounds");
    return Vec4f((*this)[static_cast<int>(idx)]);
}

//------------------------------------------------------------------------------
Vec4f Mat4x4f::getRow(uint32_t idx) const noexcept {
    VNE_ASSERT_MSG(idx < length(), "Mat4x4f index out of bounds");
    Vec4f row;
    row.x = (*this)[0][static_cast<int>(idx)];
    row.y = (*this)[1][static_cast<int>(idx)];
    row.z = (*this)[2][static_cast<int>(idx)];
    row.w = (*this)[3][static_cast<int>(idx)];
    return row;
}

//------------------------------------------------------------------------------
Vec3f Mat4x4f::xAxis() const noexcept {
    return getColumn(0).xyz();
}

//------------------------------------------------------------------------------
Vec3f Mat4x4f::yAxis() const noexcept {
    return getColumn(1).xyz();
}

//------------------------------------------------------------------------------
Vec3f Mat4x4f::zAxis() const noexcept {
    return getColumn(2).xyz();
}

//------------------------------------------------------------------------------
Vec3f Mat4x4f::translation() const noexcept {
    return getColumn(3).xyz();
}

//------------------------------------------------------------------------------
Handedness Mat4x4f::handedness() noexcept {
    Vec3f x = Vec3f::normalized(xAxis());
    Vec3f y = Vec3f::normalized(yAxis());
    Vec3f z = Vec3f::normalized(zAxis());

    Vec3f x_cross_y = Vec3f::cross(x, y);

    if (Vec3f::dot(z, x_cross_y) > kZeroTolerance) {
        return Handedness::eRight;
    } else {
        return Handedness::eLeft;
    }
}

//------------------------------------------------------------------------------
Vec3f Mat4x4f::transformVector(const Vec3f& vec) const noexcept {
    Vec4f result = (*this) * Vec4f(vec, 0.0f);
    return result.xyz();
}

//------------------------------------------------------------------------------
Vec3f Mat4x4f::transformPoint(const Vec3f& point) const noexcept {
    Vec4f result = (*this) * Vec4f(point, 1.0f);
    return result.xyz();
}

//------------------------------------------------------------------------------
Vec3f Mat4x4f::transformNormal(const Vec3f& normal) const noexcept {
    if (isOrthogonal()) {
        return Vec3f::normalized(transformVector(normal));
    } else {
        Vec4f result = normalMatrix() * Vec4f(normal, 0.0f);
        return Vec3f::normalized(result.xyz());
    }
}

//------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const Mat4x4f& mat) {
    os << "[" << mat.getColumn(0) << "," << "\n " << mat.getColumn(1) << "," << "\n " << mat.getColumn(2) << ","
       << "\n " << mat.getColumn(3) << "]";

    return os;
}

//------------------------------------------------------------------------------
uint32_t Mat4x4f::length() noexcept {
    return 4;
}

//------------------------------------------------------------------------------
Mat4x4f Mat4x4f::identity() noexcept {
    return glm::identity<glm::mat4>();
}

//------------------------------------------------------------------------------
Mat4x4f Mat4x4f::zero() noexcept {
    return glm::zero<glm::mat4>();
}

//------------------------------------------------------------------------------
Mat4x4f Mat4x4f::lerp(const Mat4x4f& from, const Mat4x4f& to, float t) noexcept {
    Mat4x4f result;
    for (int i = 0; i < static_cast<int>(length()); ++i) {
        result[i] = Vec4f::lerp(Vec4f(from[i]), Vec4f(to[i]), t);
    }
    return result;
}

//------------------------------------------------------------------------------
Mat4x4f Mat4x4f::rotate(float angle, const Vec3f& axis) noexcept {
    return glm::rotate(angle, axis);
}

//------------------------------------------------------------------------------
Mat4x4f Mat4x4f::rotateX(float angle) noexcept {
    return glm::rotate(angle, Vec3f::xAxis());
}

//------------------------------------------------------------------------------
Mat4x4f Mat4x4f::rotateY(float angle) noexcept {
    return glm::rotate(angle, Vec3f::yAxis());
}

//------------------------------------------------------------------------------
Mat4x4f Mat4x4f::rotateZ(float angle) noexcept {
    return glm::rotate(angle, Vec3f::zAxis());
}

//------------------------------------------------------------------------------
Mat4x4f Mat4x4f::rotateXYZ(float x_angle, float y_angle, float z_angle) noexcept {
    return rotateZ(z_angle) * rotateY(y_angle) * rotateX(x_angle);
}

//------------------------------------------------------------------------------
Mat4x4f Mat4x4f::rotateXYZ(float angle) noexcept {
    return rotateZ(angle) * rotateY(angle) * rotateX(angle);
}

//------------------------------------------------------------------------------
Mat4x4f Mat4x4f::rotateZYX(float x_angle, float y_angle, float z_angle) noexcept {
    return rotateX(x_angle) * rotateY(y_angle) * rotateZ(z_angle);
}

//------------------------------------------------------------------------------
Mat4x4f Mat4x4f::rotateZYX(float angle) noexcept {
    return rotateX(angle) * rotateY(angle) * rotateZ(angle);
}

//------------------------------------------------------------------------------
Mat4x4f Mat4x4f::translate(const Vec3f& offset) noexcept {
    return glm::translate(offset);
}

//------------------------------------------------------------------------------
Mat4x4f Mat4x4f::translate(float tx, float ty, float tz) noexcept {
    return glm::translate(Vec3f(tx, ty, tz));
}

//------------------------------------------------------------------------------
Mat4x4f Mat4x4f::translate(float t) noexcept {
    return glm::translate(Vec3f(t));
}

//------------------------------------------------------------------------------
Mat4x4f Mat4x4f::scale(const Vec3f& scale) noexcept {
    return glm::scale(scale);
}

//------------------------------------------------------------------------------
Mat4x4f Mat4x4f::scale(float sx, float sy, float sz) noexcept {
    return glm::scale(Vec3f(sx, sy, sz));
}

//------------------------------------------------------------------------------
Mat4x4f Mat4x4f::scale(float s) noexcept {
    return glm::scale(Vec3f(s));
}

//------------------------------------------------------------------------------
Mat4x4f Mat4x4f::lookAt(const Vec3f& eye, const Vec3f& center, const Vec3f& up) noexcept {
    return glm::lookAt(eye, center, up);
}

//------------------------------------------------------------------------------
Mat4x4f Mat4x4f::frustum(float left, float right, float bottom, float top, float z_near, float z_far) noexcept {
    return glm::frustum(left, right, bottom, top, z_near, z_far);
}

//------------------------------------------------------------------------------
Mat4x4f Mat4x4f::perspective(float fovy, float aspect_ratio, float z_near, float z_far) noexcept {
    return glm::perspective(fovy, aspect_ratio, z_near, z_far);
}

//------------------------------------------------------------------------------
Mat4x4f Mat4x4f::ortho(float left, float right, float bottom, float top, float z_near, float z_far) noexcept {
    return glm::ortho(left, right, bottom, top, z_near, z_far);
}

}  // namespace vne::math

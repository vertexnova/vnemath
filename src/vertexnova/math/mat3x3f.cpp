/* ---------------------------------------------------------------------
 * Copyright (c) 2024 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Author:    Ajeet Singh Yadav
 * Created:   September 2024
 *
 * Autodoc:   yes
 * ----------------------------------------------------------------------
 */

// Corresponding header
#include "vertexnova/math/mat3x3f.h"

// Project headers
#include "vertexnova/common/macros.h"
#include "vertexnova/math/math_utils.h"

// Third-party headers
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/transform.hpp>

namespace {
constexpr uint32_t kLength = 3;
}  // namespace

namespace vne::math {

//------------------------------------------------------------------------------
Mat3x3f::Mat3x3f() noexcept
    : glm::mat3() {}

//------------------------------------------------------------------------------
Mat3x3f::Mat3x3f(const Vec3f& col0, const Vec3f& col1, const Vec3f& col2) noexcept
    : glm::mat3(col0, col1, col2) {}

//------------------------------------------------------------------------------
Mat3x3f::Mat3x3f(const glm::mat3& other) noexcept
    : glm::mat3(other) {}

//------------------------------------------------------------------------------
Mat3x3f::Mat3x3f(const Mat3x3f& other) noexcept
    : glm::mat3(other) {}

//------------------------------------------------------------------------------
Mat3x3f::Mat3x3f(float scalar) noexcept
    : glm::mat3(scalar) {}

//------------------------------------------------------------------------------
Mat3x3f::Mat3x3f(float x0, float y0, float z0, float x1, float y1, float z1, float x2, float y2, float z2) noexcept
    : glm::mat3(x0, y0, z0, x1, y1, z1, x2, y2, z2) {}

//------------------------------------------------------------------------------
Mat3x3f& Mat3x3f::operator=(const Mat3x3f& other) noexcept {
    if (this != &other) {
        glm::mat3::operator=(other);
    }
    return *this;
}

//------------------------------------------------------------------------------
Mat3x3f Mat3x3f::rotationMatrix(const Vec3f& x_axis, const Vec3f& y_axis, const Vec3f& z_axis) noexcept {
    return Mat3x3f(x_axis, y_axis, z_axis);
}

//------------------------------------------------------------------------------
float Mat3x3f::determinant() const noexcept {
    return glm::determinant(*this);
}

//------------------------------------------------------------------------------
float Mat3x3f::trace() const noexcept {
    return (*this)[0][0] + (*this)[1][1] + (*this)[2][2];
}

//------------------------------------------------------------------------------
Mat3x3f Mat3x3f::transpose() const noexcept {
    return Mat3x3f(glm::transpose(static_cast<glm::mat3>(*this)));
}

//------------------------------------------------------------------------------
Mat3x3f Mat3x3f::inverse() const noexcept {
    return Mat3x3f(glm::inverse(static_cast<glm::mat3>(*this)));
}

//------------------------------------------------------------------------------
Mat3x3f Mat3x3f::normalMatrix() const noexcept {
    return Mat3x3f(glm::transpose(glm::inverse(static_cast<glm::mat3>(*this))));
}

//------------------------------------------------------------------------------
Mat3x3f Mat3x3f::inverseTransposed() const noexcept {
    return Mat3x3f(glm::inverseTranspose(static_cast<glm::mat3>(*this)));
}

//------------------------------------------------------------------------------
bool Mat3x3f::areSame(const Mat3x3f& other, float eps) const noexcept {
    int matrix_length = static_cast<int>(Mat3x3f::length());
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
bool Mat3x3f::isOrthogonal(float eps) const noexcept {
    return vne::math::areSame(xAxis().lengthSquare(), 1.0f, eps)
           && vne::math::areSame(yAxis().lengthSquare(), 1.0f, eps)
           && vne::math::areSame(zAxis().lengthSquare(), 1.0f, eps) && vne::math::isZero(xAxis().dot(yAxis()), eps)
           && vne::math::isZero(yAxis().dot(zAxis()), eps) && vne::math::isZero(zAxis().dot(xAxis()), eps);
}

//------------------------------------------------------------------------------
Mat3x3f Mat3x3f::operator+(const Mat3x3f& other) const noexcept {
    return Mat3x3f(static_cast<glm::mat3>(*this) + static_cast<glm::mat3>(other));
}

//------------------------------------------------------------------------------
Mat3x3f& Mat3x3f::operator+=(const Mat3x3f& other) noexcept {
    *this = *this + other;
    return *this;
}

//------------------------------------------------------------------------------
Mat3x3f Mat3x3f::operator-(const Mat3x3f& other) const noexcept {
    return Mat3x3f(static_cast<glm::mat3>(*this) - static_cast<glm::mat3>(other));
}

//------------------------------------------------------------------------------
Mat3x3f& Mat3x3f::operator-=(const Mat3x3f& other) noexcept {
    *this = *this - other;
    return *this;
}

//------------------------------------------------------------------------------
Mat3x3f Mat3x3f::operator*(const Mat3x3f& other) const noexcept {
    return Mat3x3f(static_cast<glm::mat3>(*this) * static_cast<glm::mat3>(other));
}

//------------------------------------------------------------------------------
Mat3x3f& Mat3x3f::operator*=(const Mat3x3f& other) noexcept {
    *this = *this * other;
    return *this;
}

//------------------------------------------------------------------------------
Mat3x3f Mat3x3f::operator*(float scalar) const noexcept {
    return Mat3x3f(static_cast<glm::mat3>(*this) * scalar);
}

//------------------------------------------------------------------------------
Mat3x3f& Mat3x3f::operator*=(float scalar) noexcept {
    *this = *this * scalar;
    return *this;
}

//------------------------------------------------------------------------------
Mat3x3f Mat3x3f::operator/(float scalar) const noexcept {
    VNE_ASSERT_MSG(!vne::math::isZero(scalar, kZeroTolerance), "Vec3f zero denominator");
    return Mat3x3f(static_cast<glm::mat3>(*this) / scalar);
}

//------------------------------------------------------------------------------
Mat3x3f& Mat3x3f::operator/=(float scalar) noexcept {
    VNE_ASSERT_MSG(!vne::math::isZero(scalar, kZeroTolerance), "Vec3f zero denominator");
    *this = *this / scalar;
    return *this;
}

//------------------------------------------------------------------------------
Vec3f Mat3x3f::getColumn(uint32_t idx) const noexcept {
    VNE_ASSERT_MSG(idx < length(), "Mat3x3f index out of bounds");
    return Vec3f((*this)[static_cast<int>(idx)]);
}

//------------------------------------------------------------------------------
Vec3f Mat3x3f::getRow(uint32_t idx) const noexcept {
    VNE_ASSERT_MSG(idx < length(), "Mat3x3f index out of bounds");
    Vec3f row;
    row.x = (*this)[0][static_cast<int>(idx)];
    row.y = (*this)[1][static_cast<int>(idx)];
    row.z = (*this)[2][static_cast<int>(idx)];
    return row;
}

//------------------------------------------------------------------------------
Vec3f Mat3x3f::xAxis() const noexcept {
    return getColumn(0);
}

//------------------------------------------------------------------------------
Vec3f Mat3x3f::yAxis() const noexcept {
    return getColumn(1);
}

//------------------------------------------------------------------------------
Vec3f Mat3x3f::zAxis() const noexcept {
    return getColumn(2);
}

//------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const Mat3x3f& mat) {
    os << "[" << mat.getColumn(0) << "," << "\n " << mat.getColumn(1) << "," << "\n " << mat.getColumn(2) << "]";
    return os;
}

//------------------------------------------------------------------------------
uint32_t Mat3x3f::length() noexcept {
    return kLength;
}

//------------------------------------------------------------------------------
Mat3x3f Mat3x3f::identity() noexcept {
    return Mat3x3f(glm::identity<glm::mat3>());
}

//------------------------------------------------------------------------------
Mat3x3f Mat3x3f::zero() noexcept {
    return Mat3x3f(glm::zero<glm::mat3>());
}

//------------------------------------------------------------------------------
Mat3x3f Mat3x3f::lerp(const Mat3x3f& from, const Mat3x3f& to, float t) noexcept {
    Mat3x3f result;
    for (int i = 0; i < static_cast<int>(length()); ++i) {
        result[i] = Vec3f::lerp(Vec3f(from[i]), Vec3f(to[i]), t);
    }
    return result;
}

//------------------------------------------------------------------------------
Mat3x3f Mat3x3f::rotate(float angle, const Vec3f& axis) noexcept {
    return Mat3x3f(glm::rotate(angle, axis));
}

//------------------------------------------------------------------------------
Mat3x3f Mat3x3f::rotateX(float angle) noexcept {
    return Mat3x3f(glm::rotate(angle, Vec3f::xAxis()));
}

//------------------------------------------------------------------------------
Mat3x3f Mat3x3f::rotateY(float angle) noexcept {
    return Mat3x3f(glm::rotate(angle, Vec3f::yAxis()));
}

//------------------------------------------------------------------------------
Mat3x3f Mat3x3f::rotateZ(float angle) noexcept {
    return Mat3x3f(glm::rotate(angle, Vec3f::zAxis()));
}

//------------------------------------------------------------------------------
Mat3x3f Mat3x3f::rotateXYZ(float x_angle, float y_angle, float z_angle) noexcept {
    return rotateZ(z_angle) * rotateY(y_angle) * rotateX(x_angle);
}

//------------------------------------------------------------------------------
Mat3x3f Mat3x3f::rotateXYZ(float angle) noexcept {
    return rotateZ(angle) * rotateY(angle) * rotateX(angle);
}

//------------------------------------------------------------------------------
Mat3x3f Mat3x3f::rotateZYX(float x_angle, float y_angle, float z_angle) noexcept {
    return rotateX(x_angle) * rotateY(y_angle) * rotateZ(z_angle);
}

//------------------------------------------------------------------------------
Mat3x3f Mat3x3f::rotateZYX(float angle) noexcept {
    return rotateX(angle) * rotateY(angle) * rotateZ(angle);
}

//------------------------------------------------------------------------------
Mat3x3f Mat3x3f::scale(const Vec3f& scale) noexcept {
    return Mat3x3f(glm::scale(scale));
}

//------------------------------------------------------------------------------
Mat3x3f Mat3x3f::scale(float sx, float sy, float sz) noexcept {
    return Mat3x3f(glm::scale(Vec3f(sx, sy, sz)));
}

//------------------------------------------------------------------------------
Mat3x3f Mat3x3f::scale(float s) noexcept {
    return Mat3x3f(glm::scale(Vec3f(s)));
}

}  // namespace vne::math

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

// Project includes
#include "vertexnova/math/mat3x3f.h"
#include "vertexnova/common/macros.h"
#include "vertexnova/math/math_utils.h"

// Third-party library includes
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

namespace {
constexpr uint32_t LENGTH = 3;
}  // namespace

namespace VNE {
namespace Math {

//------------------------------------------------------------------------------
Mat3x3f_C::Mat3x3f_C()
    : glm::mat3() {}

//------------------------------------------------------------------------------
Mat3x3f_C::~Mat3x3f_C() {}

//------------------------------------------------------------------------------
Mat3x3f_C::Mat3x3f_C(const Vec3f_C& col0, const Vec3f_C& col1, const Vec3f_C& col2)
    : glm::mat3(col0, col1, col2) {}

//------------------------------------------------------------------------------
Mat3x3f_C::Mat3x3f_C(const glm::mat3& other)
    : glm::mat3(other) {}

//------------------------------------------------------------------------------
Mat3x3f_C::Mat3x3f_C(const Mat3x3f_C& other)
    : glm::mat3(other) {}

//------------------------------------------------------------------------------
Mat3x3f_C::Mat3x3f_C(float scalar)
    : glm::mat3(scalar) {}

//------------------------------------------------------------------------------
Mat3x3f_C::Mat3x3f_C(float x0, float y0, float z0, float x1, float y1, float z1, float x2, float y2, float z2)
    : glm::mat3(x0, y0, z0, x1, y1, z1, x2, y2, z2) {}

//------------------------------------------------------------------------------
Mat3x3f_C& Mat3x3f_C::operator=(const Mat3x3f_C& other) {
    if (this != &other) {
        glm::mat3::operator=(other);
    }
    return *this;
}

//------------------------------------------------------------------------------
Mat3x3f_C Mat3x3f_C::RotationMatrix(const Vec3f_C& x_axis, const Vec3f_C& y_axis, const Vec3f_C& z_axis) {
    return Mat3x3f_C(x_axis, y_axis, z_axis);
}

//------------------------------------------------------------------------------
float Mat3x3f_C::Determinant() const {
    return glm::determinant(*this);
}

//------------------------------------------------------------------------------
float Mat3x3f_C::Trace() const {
    return (*this)[0][0] + (*this)[1][1] + (*this)[2][2];
}

//------------------------------------------------------------------------------
Mat3x3f_C Mat3x3f_C::Transpose() const {
    return Mat3x3f_C(glm::transpose(static_cast<glm::mat3>(*this)));
}

//------------------------------------------------------------------------------
Mat3x3f_C Mat3x3f_C::Inverse() const {
    return Mat3x3f_C(glm::inverse(static_cast<glm::mat3>(*this)));
}

//------------------------------------------------------------------------------
Mat3x3f_C Mat3x3f_C::NormalMatrix() const {
    return Mat3x3f_C(glm::transpose(glm::inverse(static_cast<glm::mat3>(*this))));
}

//------------------------------------------------------------------------------
Mat3x3f_C Mat3x3f_C::InverseTransposed() const {
    return Mat3x3f_C(glm::inverseTranspose(static_cast<glm::mat3>(*this)));
}

//------------------------------------------------------------------------------
bool Mat3x3f_C::AreSame(const Mat3x3f_C& other, float eps) const {
    int length = static_cast<int>(Length());
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < length; ++j) {
            if (!Math::AreSame((*this)[i][j], other[i][j], eps)) {
                return false;
            }
        }
    }
    return true;
}

//------------------------------------------------------------------------------
bool Mat3x3f_C::IsOrthogonal(float eps) const {
    return Math::AreSame(XAxis().LengthSquare(), 1.0f, eps) && Math::AreSame(YAxis().LengthSquare(), 1.0f, eps)
           && Math::AreSame(ZAxis().LengthSquare(), 1.0f, eps) && Math::IsZero(XAxis().Dot(YAxis()), eps) && Math::IsZero(YAxis().Dot(ZAxis()), eps)
           && Math::IsZero(ZAxis().Dot(XAxis()), eps);
}

//------------------------------------------------------------------------------
Mat3x3f_C Mat3x3f_C::operator+(const Mat3x3f_C& other) const {
    return Mat3x3f_C(static_cast<glm::mat3>(*this) + static_cast<glm::mat3>(other));
}

//------------------------------------------------------------------------------
Mat3x3f_C& Mat3x3f_C::operator+=(const Mat3x3f_C& other) {
    *this = *this + other;
    return *this;
}

//------------------------------------------------------------------------------
Mat3x3f_C Mat3x3f_C::operator-(const Mat3x3f_C& other) const {
    return Mat3x3f_C(static_cast<glm::mat3>(*this) - static_cast<glm::mat3>(other));
}

//------------------------------------------------------------------------------
Mat3x3f_C& Mat3x3f_C::operator-=(const Mat3x3f_C& other) {
    *this = *this - other;
    return *this;
}

//------------------------------------------------------------------------------
Mat3x3f_C Mat3x3f_C::operator*(const Mat3x3f_C& other) const {
    return Mat3x3f_C(static_cast<glm::mat3>(*this) * static_cast<glm::mat3>(other));
}

//------------------------------------------------------------------------------
Mat3x3f_C& Mat3x3f_C::operator*=(const Mat3x3f_C& other) {
    *this = *this * other;
    return *this;
}

//------------------------------------------------------------------------------
Mat3x3f_C Mat3x3f_C::operator*(float scalar) const {
    return Mat3x3f_C(static_cast<glm::mat3>(*this) * scalar);
}

//------------------------------------------------------------------------------
Mat3x3f_C& Mat3x3f_C::operator*=(float scalar) {
    *this = *this * scalar;
    return *this;
}

//------------------------------------------------------------------------------
Mat3x3f_C Mat3x3f_C::operator/(float scalar) const {
    VNE_ASSERT_MSG(!Math::IsZero(scalar, 1E-5f), "Vec3f_C zero denominator");
    return Mat3x3f_C(static_cast<glm::mat3>(*this) / scalar);
}

//------------------------------------------------------------------------------
Mat3x3f_C& Mat3x3f_C::operator/=(float scalar) {
    VNE_ASSERT_MSG(!Math::IsZero(scalar, 1E-5f), "Vec3f_C zero denominator");
    *this = *this / scalar;
    return *this;
}

//------------------------------------------------------------------------------
Vec3f_C Mat3x3f_C::GetColumn(uint32_t idx) const {
    VNE_ASSERT_MSG(idx < Length(), "Mat3x3f_C index out of bounds");
    return Vec3f_C((*this)[static_cast<int>(idx)]);
}

//------------------------------------------------------------------------------
Vec3f_C Mat3x3f_C::GetRow(uint32_t idx) const {
    VNE_ASSERT_MSG(idx < Length(), "Mat3x3f_C index out of bounds");
    Vec3f_C row;
    row.x = (*this)[0][static_cast<int>(idx)];
    row.y = (*this)[1][static_cast<int>(idx)];
    row.z = (*this)[2][static_cast<int>(idx)];
    return row;
}

//------------------------------------------------------------------------------
Vec3f_C Mat3x3f_C::XAxis() const {
    return GetColumn(0);
}

//------------------------------------------------------------------------------
Vec3f_C Mat3x3f_C::YAxis() const {
    return GetColumn(1);
}

//------------------------------------------------------------------------------
Vec3f_C Mat3x3f_C::ZAxis() const {
    return GetColumn(2);
}

//------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const Mat3x3f_C& mat) {
    os << "[" << mat.GetColumn(0) << "," << "\n " << mat.GetColumn(1) << "," << "\n " << mat.GetColumn(2) << "]";
    return os;
}

//------------------------------------------------------------------------------
uint32_t Mat3x3f_C::Length() {
    return LENGTH;
}

//------------------------------------------------------------------------------
Mat3x3f_C Mat3x3f_C::Identity() {
    return Mat3x3f_C(glm::identity<glm::mat3>());
}

//------------------------------------------------------------------------------
Mat3x3f_C Mat3x3f_C::Zero() {
    return Mat3x3f_C(glm::zero<glm::mat3>());
}

//------------------------------------------------------------------------------
Mat3x3f_C Mat3x3f_C::Lerp(const Mat3x3f_C& from, const Mat3x3f_C& to, float t) {
    Mat3x3f_C result;
    for (int i = 0; i < static_cast<int>(Length()); ++i) {
        result[i] = Vec3f_C::Lerp(Vec3f_C(from[i]), Vec3f_C(to[i]), t);
    }
    return result;
}

//------------------------------------------------------------------------------
Mat3x3f_C Mat3x3f_C::Rotate(float angle, const Vec3f_C& axis) {
    return Mat3x3f_C(glm::rotate(angle, axis));
}

//------------------------------------------------------------------------------
Mat3x3f_C Mat3x3f_C::RotateX(float angle) {
    return Mat3x3f_C(glm::rotate(angle, Math::Vec3f_C::XAxis()));
}

//------------------------------------------------------------------------------
Mat3x3f_C Mat3x3f_C::RotateY(float angle) {
    return Mat3x3f_C(glm::rotate(angle, Math::Vec3f_C::YAxis()));
}

//------------------------------------------------------------------------------
Mat3x3f_C Mat3x3f_C::RotateZ(float angle) {
    return Mat3x3f_C(glm::rotate(angle, Math::Vec3f_C::ZAxis()));
}

//------------------------------------------------------------------------------
Mat3x3f_C Mat3x3f_C::RotateXYZ(float x_angle, float y_angle, float z_angle) {
    return RotateZ(z_angle) * RotateY(y_angle) * RotateX(x_angle);
}

//------------------------------------------------------------------------------
Mat3x3f_C Mat3x3f_C::RotateXYZ(float angle) {
    return RotateZ(angle) * RotateY(angle) * RotateX(angle);
}

//------------------------------------------------------------------------------
Mat3x3f_C Mat3x3f_C::RotateZYX(float x_angle, float y_angle, float z_angle) {
    return RotateX(x_angle) * RotateY(y_angle) * RotateZ(z_angle);
}

//------------------------------------------------------------------------------
Mat3x3f_C Mat3x3f_C::RotateZYX(float angle) {
    return RotateX(angle) * RotateY(angle) * RotateZ(angle);
}

//------------------------------------------------------------------------------
Mat3x3f_C Mat3x3f_C::Scale(const Vec3f_C& scale) {
    return Mat3x3f_C(glm::scale(scale));
}

//------------------------------------------------------------------------------
Mat3x3f_C Mat3x3f_C::Scale(float sx, float sy, float sz) {
    return Mat3x3f_C(glm::scale(Math::Vec3f_C(sx, sy, sz)));
}

//------------------------------------------------------------------------------
Mat3x3f_C Mat3x3f_C::Scale(float s) {
    return Mat3x3f_C(glm::scale(Math::Vec3f_C(s)));
}

}  // namespace Math
}  // namespace VNE

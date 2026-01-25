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
#include "vertexnova/math/mat4x4f.h"
#include "vertexnova/common/macros.h"
#include "vertexnova/math/math_utils.h"

// Third-party library includes
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

namespace VNE {
namespace Math {

//------------------------------------------------------------------------------
Mat4x4f_C::Mat4x4f_C()
    : glm::mat4() {}

//------------------------------------------------------------------------------
Mat4x4f_C::~Mat4x4f_C() {}

//------------------------------------------------------------------------------
Mat4x4f_C::Mat4x4f_C(const Vec4f_C& col0, const Vec4f_C& col1, const Vec4f_C& col2, const Vec4f_C& col3)
    : glm::mat4(col0, col1, col2, col3) {}

//------------------------------------------------------------------------------
Mat4x4f_C::Mat4x4f_C(const glm::mat4& other)
    : glm::mat4(other) {}

//------------------------------------------------------------------------------
Mat4x4f_C::Mat4x4f_C(const Mat4x4f_C& other)
    : glm::mat4(other) {}

//------------------------------------------------------------------------------
Mat4x4f_C::Mat4x4f_C(const glm::mat3& other)
    : glm::mat4(other) {}

//------------------------------------------------------------------------------
Mat4x4f_C::Mat4x4f_C(const Mat3x3f_C& other)
    : glm::mat4(other) {}

//------------------------------------------------------------------------------
Mat4x4f_C::Mat4x4f_C(float scalar)
    : glm::mat4(scalar) {}

//------------------------------------------------------------------------------
Mat4x4f_C::Mat4x4f_C(float x0,
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
                     float w3)
    : glm::mat4(x0, y0, z0, w0, x1, y1, z1, w1, x2, y2, z2, w2, x3, y3, z3, w3) {}

//------------------------------------------------------------------------------
Mat4x4f_C& Mat4x4f_C::operator=(const Mat4x4f_C& other) {
    if (this != &other) {
        glm::mat4::operator=(other);
    }
    return *this;
}

//------------------------------------------------------------------------------
Mat4x4f_C Mat4x4f_C::Transform(const Vec3f_C& x_axis, const Vec3f_C& y_axis, const Vec3f_C& z_axis) {
    return Mat4x4f_C(Vec4f_C(x_axis, 0.0f), Vec4f_C(y_axis, 0.0f), Vec4f_C(z_axis, 0.0f), Vec4f_C(0.0f, 0.0f, 0.0f, 1.0f));
}

//------------------------------------------------------------------------------
Mat4x4f_C Mat4x4f_C::Transform(const Vec3f_C& x_axis, const Vec3f_C& y_axis, const Vec3f_C& z_axis, const Vec3f_C& offset) {
    return Mat4x4f_C(Vec4f_C(x_axis, 0.0f), Vec4f_C(y_axis, 0.0f), Vec4f_C(z_axis, 0.0f), Vec4f_C(offset, 1.0f));
}

//------------------------------------------------------------------------------
Mat4x4f_C Mat4x4f_C::Transform(const Vec3f_C& forward, const Vec3f_C& up) {
    Vec3f_C x_axis = Vec3f_C::Normalized(forward);
    Vec3f_C y_axis = Vec3f_C::Normalized(up.Cross(x_axis));
    Vec3f_C z_axis = x_axis.Cross(y_axis);

    return Transform(x_axis, y_axis, z_axis);
}

//------------------------------------------------------------------------------
Mat4x4f_C Mat4x4f_C::Transform(const Vec3f_C& offset) {
    return Mat4x4f_C(Vec4f_C(1.0f, 0.0f, 0.0f, 0.0f), Vec4f_C(0.0f, 1.0f, 0.0f, 0.0f), Vec4f_C(0.0f, 0.0f, 1.0f, 0.0f), Vec4f_C(offset, 1.0f));
}

//------------------------------------------------------------------------------
float Mat4x4f_C::Determinant() const {
    return glm::determinant(*this);
}

//------------------------------------------------------------------------------
Mat4x4f_C Mat4x4f_C::Transpose() const {
    return glm::transpose(*this);
}

//------------------------------------------------------------------------------
Mat4x4f_C Mat4x4f_C::Inverse() const {
    return glm::inverse(*this);
}

//------------------------------------------------------------------------------
Mat4x4f_C Mat4x4f_C::NormalMatrix() const {
    return glm::transpose(glm::inverse(*this));
}

//------------------------------------------------------------------------------
Mat4x4f_C Mat4x4f_C::InverseTransposed() const {
    glm::mat4 temp = *this;
    return glm::inverseTranspose(temp);
}

//------------------------------------------------------------------------------
bool Mat4x4f_C::AreSame(const Mat4x4f_C& other, float eps) const {
    const int length = static_cast<int>(Length());
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
bool Mat4x4f_C::IsOrthogonal(float eps) const {
    if (Math::AreSame(XAxis().LengthSquare(), 1.0f, eps) && Math::AreSame(YAxis().LengthSquare(), 1.0f, eps)
        && Math::AreSame(ZAxis().LengthSquare(), 1.0f, eps)) {
        if (Math::IsZero(XAxis().Dot(YAxis()), eps) && Math::IsZero(YAxis().Dot(ZAxis()), eps) && Math::IsZero(ZAxis().Dot(XAxis()), eps)) {
            return true;
        }
    }
    return false;
}

//------------------------------------------------------------------------------
Mat4x4f_C Mat4x4f_C::operator+(const Mat4x4f_C& other) const {
    return Mat4x4f_C(static_cast<glm::mat4>(*this) + static_cast<glm::mat4>(other));
}

//------------------------------------------------------------------------------
Mat4x4f_C& Mat4x4f_C::operator+=(const Mat4x4f_C& other) {
    *this = *this + other;
    return *this;
}

//------------------------------------------------------------------------------
Mat4x4f_C Mat4x4f_C::operator-(const Mat4x4f_C& other) const {
    return Mat4x4f_C(static_cast<glm::mat4>(*this) - static_cast<glm::mat4>(other));
}

//------------------------------------------------------------------------------
Mat4x4f_C& Mat4x4f_C::operator-=(const Mat4x4f_C& other) {
    *this = *this - other;
    return *this;
}

//------------------------------------------------------------------------------
Mat4x4f_C Mat4x4f_C::operator*(const Mat4x4f_C& other) const {
    return Mat4x4f_C(static_cast<glm::mat4>(*this) * static_cast<glm::mat4>(other));
}

//------------------------------------------------------------------------------
Mat4x4f_C& Mat4x4f_C::operator*=(const Mat4x4f_C& other) {
    *this = *this * other;
    return *this;
}

//------------------------------------------------------------------------------
Mat4x4f_C Mat4x4f_C::operator*(float scalar) const {
    return Mat4x4f_C(static_cast<glm::mat4>(*this) * scalar);
}

//------------------------------------------------------------------------------
Mat4x4f_C& Mat4x4f_C::operator*=(float scalar) {
    *this = *this * scalar;
    return *this;
}

//------------------------------------------------------------------------------
Mat4x4f_C Mat4x4f_C::operator/(float scalar) const {
    VNE_ASSERT_MSG(!Math::IsZero(scalar, 1E-5f), "Vec3f_C zero denominator");
    return Mat4x4f_C(static_cast<glm::mat4>(*this) / scalar);
}

//------------------------------------------------------------------------------
Mat4x4f_C& Mat4x4f_C::operator/=(float scalar) {
    VNE_ASSERT_MSG(!Math::IsZero(scalar, 1E-5f), "Vec3f_C zero denominator");
    *this = *this / scalar;
    return *this;
}

//------------------------------------------------------------------------------
Vec4f_C Mat4x4f_C::GetColumn(uint32_t idx) const {
    VNE_ASSERT_MSG(idx < Length(), "Mat4x4f_C index out of bounds");
    return Vec4f_C((*this)[static_cast<int>(idx)]);
}

//------------------------------------------------------------------------------
Vec4f_C Mat4x4f_C::GetRow(uint32_t idx) const {
    VNE_ASSERT_MSG(idx < Length(), "Mat4x4f_C index out of bounds");
    Vec4f_C row;
    row.x = (*this)[0][static_cast<int>(idx)];
    row.y = (*this)[1][static_cast<int>(idx)];
    row.z = (*this)[2][static_cast<int>(idx)];
    row.w = (*this)[3][static_cast<int>(idx)];
    return row;
}

//------------------------------------------------------------------------------
Vec3f_C Mat4x4f_C::XAxis() const {
    return GetColumn(0).XYZ();
}

//------------------------------------------------------------------------------
Vec3f_C Mat4x4f_C::YAxis() const {
    return GetColumn(1).XYZ();
}

//------------------------------------------------------------------------------
Vec3f_C Mat4x4f_C::ZAxis() const {
    return GetColumn(2).XYZ();
}

//------------------------------------------------------------------------------
Vec3f_C Mat4x4f_C::Translation() const {
    return GetColumn(3).XYZ();
}

//------------------------------------------------------------------------------
Handness_TP Mat4x4f_C::Handedness() {
    Vec3f_C x = Vec3f_C::Normalized(XAxis());
    Vec3f_C y = Vec3f_C::Normalized(YAxis());
    Vec3f_C z = Vec3f_C::Normalized(ZAxis());

    Vec3f_C x_cross_y = Vec3f_C::Cross(x, y);

    if (Vec3f_C::Dot(z, x_cross_y) > 1E-5f) {
        return Handness_TP::RIGHT;
    } else {
        return Handness_TP::LEFT;
    }
}

//------------------------------------------------------------------------------
Vec3f_C Mat4x4f_C::TransformVector(const Vec3f_C& vec) const {
    Vec4f_C result = (*this) * Vec4f_C(vec, 0.0f);
    return result.XYZ();
}

//------------------------------------------------------------------------------
Vec3f_C Mat4x4f_C::TransformPoint(const Vec3f_C& point) const {
    Vec4f_C result = (*this) * Vec4f_C(point, 1.0f);
    return result.XYZ();
}

//------------------------------------------------------------------------------
Vec3f_C Mat4x4f_C::TransformNormal(const Vec3f_C& normal) const {
    if (IsOrthogonal()) {
        return Vec3f_C::Normalized(TransformVector(normal));
    } else {
        Vec4f_C result = NormalMatrix() * Vec4f_C(normal, 0.0f);
        return Vec3f_C::Normalized(result.XYZ());
    }
}

//------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const Mat4x4f_C& mat) {
    os << "[" << mat.GetColumn(0) << "," << "\n " << mat.GetColumn(1) << "," << "\n " << mat.GetColumn(2) << "," << "\n " << mat.GetColumn(3) << "]";

    return os;
}

//------------------------------------------------------------------------------
uint32_t Mat4x4f_C::Length() {
    return 4;
}

//------------------------------------------------------------------------------
Mat4x4f_C Mat4x4f_C::Identity() {
    return glm::identity<glm::mat4>();
}

//------------------------------------------------------------------------------
Mat4x4f_C Mat4x4f_C::Zero() {
    return glm::zero<glm::mat4>();
}

//------------------------------------------------------------------------------
Mat4x4f_C Mat4x4f_C::Lerp(const Mat4x4f_C& from, const Mat4x4f_C& to, float t) {
    Mat4x4f_C result;
    for (int i = 0; i < static_cast<int>(Length()); ++i) {
        result[i] = Vec4f_C::Lerp(Vec4f_C(from[i]), Vec4f_C(to[i]), t);
    }
    return result;
}

//------------------------------------------------------------------------------
Mat4x4f_C Mat4x4f_C::Rotate(float angle, const Vec3f_C& axis) {
    return glm::rotate(angle, axis);
}

//------------------------------------------------------------------------------
Mat4x4f_C Mat4x4f_C::RotateX(float angle) {
    return glm::rotate(angle, Math::Vec3f_C::XAxis());
}

//------------------------------------------------------------------------------
Mat4x4f_C Mat4x4f_C::RotateY(float angle) {
    return glm::rotate(angle, Math::Vec3f_C::YAxis());
}

//------------------------------------------------------------------------------
Mat4x4f_C Mat4x4f_C::RotateZ(float angle) {
    return glm::rotate(angle, Math::Vec3f_C::ZAxis());
}

//------------------------------------------------------------------------------
Mat4x4f_C Mat4x4f_C::RotateXYZ(float x_angle, float y_angle, float z_angle) {
    return RotateZ(z_angle) * RotateY(y_angle) * RotateX(x_angle);
}

//------------------------------------------------------------------------------
Mat4x4f_C Mat4x4f_C::RotateXYZ(float angle) {
    return RotateZ(angle) * RotateY(angle) * RotateX(angle);
}

//------------------------------------------------------------------------------
Mat4x4f_C Mat4x4f_C::RotateZYX(float x_angle, float y_angle, float z_angle) {
    return RotateX(x_angle) * RotateY(y_angle) * RotateZ(z_angle);
}

//------------------------------------------------------------------------------
Mat4x4f_C Mat4x4f_C::RotateZYX(float angle) {
    return RotateX(angle) * RotateY(angle) * RotateZ(angle);
}

//------------------------------------------------------------------------------
Mat4x4f_C Mat4x4f_C::Translate(const Vec3f_C& offset) {
    return glm::translate(offset);
}

//------------------------------------------------------------------------------
Mat4x4f_C Mat4x4f_C::Translate(float tx, float ty, float tz) {
    return glm::translate(Math::Vec3f_C(tx, ty, tz));
}

//------------------------------------------------------------------------------
Mat4x4f_C Mat4x4f_C::Translate(float t) {
    return glm::translate(Math::Vec3f_C(t));
}

//------------------------------------------------------------------------------
Mat4x4f_C Mat4x4f_C::Scale(const Vec3f_C& scale) {
    return glm::scale(scale);
}

//------------------------------------------------------------------------------
Mat4x4f_C Mat4x4f_C::Scale(float sx, float sy, float sz) {
    return glm::scale(Math::Vec3f_C(sx, sy, sz));
}

//------------------------------------------------------------------------------
Mat4x4f_C Mat4x4f_C::Scale(float s) {
    return glm::scale(Math::Vec3f_C(s));
}

//------------------------------------------------------------------------------
Mat4x4f_C Mat4x4f_C::LookAt(const Vec3f_C& eye, const Vec3f_C& center, const Vec3f_C& up) {
    return glm::lookAt(eye, center, up);
}

//------------------------------------------------------------------------------
Mat4x4f_C Mat4x4f_C::Frustum(float left, float right, float bottom, float top, float z_near, float z_far) {
    // CHECK_CONDITION_RETURN_FAILURE(left < right);
    // CHECK_CONDITION_RETURN_FAILURE(bottom < top);
    // CHECK_CONDITION_RETURN_FAILURE(z_far > z_near);
    // CHECK_CONDITION_RETURN_FAILURE(0.0f < z_near);
    // CHECK_CONDITION_RETURN_FAILURE(0.0f < z_far);

    return glm::frustum(left, right, bottom, top, z_near, z_far);
}

Mat4x4f_C Mat4x4f_C::Perspective(float fovy, float aspect_ratio, float z_near, float z_far) {
    // CHECK_CONDITION_RETURN_FAILURE(fovy >= 0.0f);
    // CHECK_CONDITION_RETURN_FAILURE(fovy <= Math::Pi<float>());
    // CHECK_CONDITION_RETURN_FAILURE(aspect_ratio > 0.0f);
    // CHECK_CONDITION_RETURN_FAILURE(z_far > z_near);
    // CHECK_CONDITION_RETURN_FAILURE(0.0f < z_near);
    // CHECK_CONDITION_RETURN_FAILURE(0.0f < z_far);

    return glm::perspective(fovy, aspect_ratio, z_near, z_far);
}

Mat4x4f_C Mat4x4f_C::Ortho(float left, float right, float bottom, float top, float z_near, float z_far) {
    // CHECK_CONDITION_RETURN_FAILURE(left < right);
    // CHECK_CONDITION_RETURN_FAILURE(bottom < top);
    // CHECK_CONDITION_RETURN_FAILURE(z_far > z_near);

    return glm::ortho(left, right, bottom, top, z_near, z_far);
}

}  // namespace Math
}  // namespace VNE

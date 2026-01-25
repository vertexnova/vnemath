/* ---------------------------------------------------------------------
 * Copyright (c) 2024 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Author:    Ajeet Singh Yadav
 * Created:   August 2024
 *
 * Autodoc:   yes
 * ----------------------------------------------------------------------
 */

// Project includes
#include "vertexnova/math/vec2f.h"
#include "vertexnova/math/math_utils.h"
#include "vertexnova/common/macros.h"

// Third-party library includes
#include <glm/gtx/projection.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/transform.hpp>

namespace VNE {
namespace Math {

//------------------------------------------------------------------------------
float* Vec2f_C::GetPtr() {
    return &x;
}

//------------------------------------------------------------------------------
const float* Vec2f_C::GetPtr() const {
    return &x;
}

//------------------------------------------------------------------------------
Vec2f_C Vec2f_C::Abs() const {
    return Vec2f_C(glm::abs(x), glm::abs(y));
}

//------------------------------------------------------------------------------
float Vec2f_C::Length() const {
    return glm::length(glm::vec2(*this));
}

//------------------------------------------------------------------------------
float Vec2f_C::LengthSquare() const {
    return glm::length2(glm::vec2(*this));
}

//------------------------------------------------------------------------------
Vec2f_C Vec2f_C::Normalize() const {
    VNE_ASSERT_MSG(!Math::IsZero(LengthSquare(), 1E-5f), "Zero denominator");
    glm::vec2 norm = glm::normalize(glm::vec2(*this));
    return norm;
}

//------------------------------------------------------------------------------
Vec2f_C Vec2f_C::Min(const Vec2f_C& v) const {
    return LengthSquare() < v.LengthSquare() ? *this : v;
}

//------------------------------------------------------------------------------
Vec2f_C Vec2f_C::Max(const Vec2f_C& v) const {
    return LengthSquare() > v.LengthSquare() ? *this : v;
}

//------------------------------------------------------------------------------
float Vec2f_C::MinComponent() const {
    return glm::min(x, y);
}

//------------------------------------------------------------------------------
float Vec2f_C::MaxComponent() const {
    return glm::max(x, y);
}

//------------------------------------------------------------------------------
float Vec2f_C::Dot(const Vec2f_C& v) const {
    return glm::dot<2, float, glm::qualifier::highp>(glm::vec2(*this), glm::vec2(v));
}

//------------------------------------------------------------------------------
float Vec2f_C::Cross(const Vec2f_C& v) const {
    return x * v.y - y * v.x;
}

//------------------------------------------------------------------------------
float Vec2f_C::Distance(const Vec2f_C& v) const {
    Vec2f_C diff = *this - v;
    return diff.Length();
}

//------------------------------------------------------------------------------
Vec2f_C Vec2f_C::Rotate(const Vec2f_C& axis, float angle) const {
    return glm::rotate(glm::vec2(axis), angle);
}

//------------------------------------------------------------------------------
Vec2f_C Vec2f_C::Reflect(const Vec2f_C& normal) const {
    return glm::reflect(glm::vec2(*this), glm::vec2(normal));
}

//------------------------------------------------------------------------------
Vec2f_C Vec2f_C::Refract(const Vec2f_C& normal, float mu) const {
    return glm::refract(glm::vec2(*this), glm::vec2(normal), mu);
}

//------------------------------------------------------------------------------
Vec2f_C Vec2f_C::Project(const Vec2f_C& v) const {
    return glm::proj(glm::vec2(*this), glm::vec2(v));
}

//------------------------------------------------------------------------------
Vec2f_C Vec2f_C::Reject(const Vec2f_C& v) const {
    return *this - Project(v);
}

//------------------------------------------------------------------------------
void Vec2f_C::DecomposeVec(const Vec2f_C& v, Vec2f_C& proj, Vec2f_C& perp) const {
    proj = this->Project(v);
    perp = *this - proj;
}

//------------------------------------------------------------------------------
Vec2f_C Vec2f_C::Perpendicular() const {
    return Vec2f_C(-y, x);
}

//------------------------------------------------------------------------------
bool Vec2f_C::AreSame(const Vec2f_C& v, float eps) const {
    return Math::AreSame(x, v.x, eps) && Math::AreSame(y, v.y, eps);
}

//------------------------------------------------------------------------------
bool Vec2f_C::AreAligned(const Vec2f_C& v, float eps) const {
    return Math::IsZero(this->Angle(v), eps);
}

//------------------------------------------------------------------------------
bool Vec2f_C::IsZero(float eps) const {
    return Math::IsZero(x, eps) && Math::IsZero(y, eps);
}

//------------------------------------------------------------------------------
bool Vec2f_C::IsNormalized(float eps) const {
    return Math::AreSame(LengthSquare(), 1.0f, eps);
}

//------------------------------------------------------------------------------
Vec2f_C& Vec2f_C::ComposePolar(float radius, float angle) {
    this->x = radius * Math::Cos(angle);
    this->y = radius * Math::Sin(angle);
    return *this;
}

//------------------------------------------------------------------------------
void Vec2f_C::DecomposePolar(float& radius, float& angle) const {
    radius = Length();
    angle = Math::ATan2(y, x);

    if (angle < 0) {
        angle += Math::TwoPi<float>();
    }
}

//------------------------------------------------------------------------------
float Vec2f_C::Angle() const {
    float angle = Math::ATan2(this->y, this->x);
    if (angle < 0) {
        angle += Math::TwoPi<float>();
    }
    return angle;
}

//------------------------------------------------------------------------------
float Vec2f_C::Angle(const Vec2f_C& v) const {
    float angle = Math::ATan2(x * v.y - y * v.x, x * v.x + y * v.y);
    if (angle < 0) {
        angle += Math::TwoPi<float>();
    }
    return angle;
}

//------------------------------------------------------------------------------
float Vec2f_C::Angle(const Vec2f_C& p1, const Vec2f_C& p2) const {
    Vec2f_C new_p1 = p1 - *this;
    Vec2f_C new_p2 = p2 - *this;
    return new_p1.Angle(new_p2);
}

//------------------------------------------------------------------------------
Vec2f_C Vec2f_C::MidPoint(const Vec2f_C& point) const {
    return Math::Vec2f_C(Math::MidPoint(x, point.x), Math::MidPoint(y, point.y));
}

//------------------------------------------------------------------------------
Vec2f_C Vec2f_C::Lerp(Vec2f_C& point, float factor) const {
    return Math::Vec2f_C(Math::Lerp(x, point.x, factor), Math::Lerp(y, point.y, factor));
}

//------------------------------------------------------------------------------
Vec2f_C& Vec2f_C::operator=(const Vec2f_C& v) {
    x = v.x;
    y = v.y;
    return *this;
}

//------------------------------------------------------------------------------
Vec2f_C& Vec2f_C::operator+=(const float& scalar) {
    x += scalar;
    y += scalar;
    return *this;
}

//------------------------------------------------------------------------------
Vec2f_C& Vec2f_C::operator-=(const float& scalar) {
    x -= scalar;
    y -= scalar;
    return *this;
}

//------------------------------------------------------------------------------
Vec2f_C& Vec2f_C::operator*=(const float& scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}

//------------------------------------------------------------------------------
Vec2f_C& Vec2f_C::operator/=(const float& scalar) {
    VNE_ASSERT_MSG(!Math::IsZero(scalar, 1E-5f), "Vec2f_C zero denominator");
    x /= scalar;
    y /= scalar;
    return *this;
}

//------------------------------------------------------------------------------
Vec2f_C& Vec2f_C::operator+=(const Vec2f_C& v) {
    x += v.x;
    y += v.y;
    return *this;
}

//------------------------------------------------------------------------------
Vec2f_C& Vec2f_C::operator-=(const Vec2f_C& v) {
    x -= v.x;
    y -= v.y;
    return *this;
}

//------------------------------------------------------------------------------
Vec2f_C& Vec2f_C::operator*=(const Vec2f_C& v) {
    x *= v.x;
    y *= v.y;
    return *this;
}

//------------------------------------------------------------------------------
Vec2f_C& Vec2f_C::operator/=(const Vec2f_C& v) {
    VNE_ASSERT_MSG(!Math::IsZero(v.x, 1E-5f), "Vec2f_C zero denominator");
    VNE_ASSERT_MSG(!Math::IsZero(v.y, 1E-5f), "Vec2f_C zero denominator");
    x /= v.x;
    y /= v.y;
    return *this;
}

//------------------------------------------------------------------------------
Vec2f_C Vec2f_C::operator+(const float& scalar) const {
    return Vec2f_C(x + scalar, y + scalar);
}

//------------------------------------------------------------------------------
Vec2f_C Vec2f_C::operator-(const float& scalar) const {
    return Vec2f_C(x - scalar, y - scalar);
}

//------------------------------------------------------------------------------
Vec2f_C Vec2f_C::operator*(const float& scalar) const {
    return Vec2f_C(x * scalar, y * scalar);
}

//------------------------------------------------------------------------------
Vec2f_C Vec2f_C::operator/(const float& scalar) const {
    VNE_ASSERT_MSG(!Math::IsZero(scalar, 1E-5f), "Vec2f_C zero denominator");
    return Vec2f_C(x / scalar, y / scalar);
}

//------------------------------------------------------------------------------
Vec2f_C Vec2f_C::operator+(const Vec2f_C& v) const {
    return Vec2f_C(x + v.x, y + v.y);
}

//------------------------------------------------------------------------------
Vec2f_C Vec2f_C::operator-(const Vec2f_C& v) const {
    return Vec2f_C(x - v.x, y - v.y);
}

//------------------------------------------------------------------------------
Vec2f_C Vec2f_C::operator*(const Vec2f_C& v) const {
    return Vec2f_C(x * v.x, y * v.y);
}

//------------------------------------------------------------------------------
Vec2f_C Vec2f_C::operator/(const Vec2f_C& v) const {
    VNE_ASSERT_MSG(!Math::IsZero(v.x, 1E-5f), "Vec2f_C zero denominator");
    VNE_ASSERT_MSG(!Math::IsZero(v.y, 1E-5f), "Vec2f_C zero denominator");
    return Vec2f_C(x / v.x, y / v.y);
}

//------------------------------------------------------------------------------
bool Vec2f_C::operator==(const Vec2f_C& v) const {
    return x == v.x && y == v.y;
}

//------------------------------------------------------------------------------
bool Vec2f_C::operator!=(const Vec2f_C& v) const {
    return x != v.x || y != v.y;
}

//------------------------------------------------------------------------------
bool Vec2f_C::operator>(const Vec2f_C& v) const {
    return LengthSquare() > v.LengthSquare();
}

//------------------------------------------------------------------------------
bool Vec2f_C::operator<(const Vec2f_C& v) const {
    return LengthSquare() < v.LengthSquare();
}

//------------------------------------------------------------------------------
Vec2f_C Vec2f_C::operator-() const {
    return Vec2f_C(-x, -y);
}

//------------------------------------------------------------------------------
float& Vec2f_C::operator[](uint32_t index) {
    VNE_ASSERT_MSG(index < 2, "Vec2f_C index out of bounds");
    return (&x)[index];
}

//------------------------------------------------------------------------------
float Vec2f_C::operator[](uint32_t index) const {
    VNE_ASSERT_MSG(index < 2, "Vec2f_C index out of bounds");
    return (&x)[index];
}

//------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const Vec2f_C& vec) {
    return os << "[" << vec.x << ", " << vec.y << "]";
}

//------------------------------------------------------------------------------
std::istream& operator>>(std::istream& is, Vec2f_C& vec) {
    is >> vec.x;
    is.ignore(2);
    is >> vec.y;
    return is;
}

//------------------------------------------------------------------------------
uint32_t Vec2f_C::Dim() {
    return 2;
}

//------------------------------------------------------------------------------
uint32_t Vec2f_C::Size() {
    return Dim();
}

//------------------------------------------------------------------------------
Vec2f_C Vec2f_C::Zero() {
    return Vec2f_C();
}

//------------------------------------------------------------------------------
Vec2f_C Vec2f_C::One() {
    return Vec2f_C(1.0f, 1.0f);
}

//------------------------------------------------------------------------------
Vec2f_C Vec2f_C::XAxis() {
    return Vec2f_C(1.0f, 0.0f);
}

//------------------------------------------------------------------------------
Vec2f_C Vec2f_C::YAxis() {
    return Vec2f_C(0.0f, 1.0f);
}

//------------------------------------------------------------------------------
Vec2f_C Vec2f_C::Normalized(const Vec2f_C& v) {
    Vec2f_C ret = v;
    return ret.Normalize();
}

//------------------------------------------------------------------------------
float Vec2f_C::Distance(const Vec2f_C& v1, const Vec2f_C& v2) {
    Vec2f_C v = v1 - v2;
    return v.Length();
}

//------------------------------------------------------------------------------
float Vec2f_C::Dot(const Vec2f_C& v1, const Vec2f_C& v2) {
    Vec2f_C ret = v1;
    return ret.Dot(v2);
}

//------------------------------------------------------------------------------
float Vec2f_C::Cross(const Vec2f_C& v1, const Vec2f_C& v2) {
    Vec2f_C ret = v1;
    return ret.Cross(v2);
}

//------------------------------------------------------------------------------
Vec2f_C Vec2f_C::MidPoint(const Vec2f_C& p1, const Vec2f_C& p2) {
    Vec2f_C out;
    out.x = Math::MidPoint(p1.x, p2.x);
    out.y = Math::MidPoint(p1.y, p2.y);
    return out;
}

//------------------------------------------------------------------------------
Vec2f_C Vec2f_C::Lerp(const Vec2f_C& p1, const Vec2f_C& p2, float factor) {
    Vec2f_C out;
    out.x = Math::Lerp(p1.x, p2.x, factor);
    out.y = Math::Lerp(p1.y, p2.y, factor);
    return out;
}

}  // namespace Math
}  // namespace VNE

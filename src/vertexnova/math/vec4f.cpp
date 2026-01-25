/* ---------------------------------------------------------------------
 * Copyright (c) 2024 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Author:    Ajeet Singh Yadav
 * Created:   August-2024
 *
 * Autodoc:   yes
 * ----------------------------------------------------------------------
 */

// Project includes
#include "vertexnova/math/vec4f.h"
#include "vertexnova/math/math_utils.h"
#include "vertexnova/common/macros.h"
// #include "geometry/plane.h"

// Third-party library includes
#include <glm/gtx/projection.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/transform.hpp>

namespace VNE {
namespace Math {

// Constructors
// Vec4f_C::Vec4f_C(const Plane_C& plane)
//     : glm::vec4(plane.normal, plane.d) {}

//------------------------------------------------------------------------------
Vec3f_C Vec4f_C::XYZ() {
    return Vec3f_C(x, y, z);
}

//------------------------------------------------------------------------------
Vec2f_C Vec4f_C::XY() {
    return Vec2f_C(x, y);
}

//------------------------------------------------------------------------------
float* Vec4f_C::GetPtr() {
    return &x;
}

//------------------------------------------------------------------------------
const float* Vec4f_C::GetPtr() const {
    return &x;
}

//------------------------------------------------------------------------------
Vec4f_C Vec4f_C::Abs() const {
    return Vec4f_C(glm::abs(x), glm::abs(y), glm::abs(z), glm::abs(w));
}

//------------------------------------------------------------------------------
float Vec4f_C::Length() const {
    return glm::length(static_cast<const glm::vec4&>(*this));
}

//------------------------------------------------------------------------------
float Vec4f_C::LengthSquare() const {
    return glm::length2(static_cast<const glm::vec4&>(*this));
}

//------------------------------------------------------------------------------
Vec4f_C Vec4f_C::Normalize() const {
    VNE_ASSERT_MSG(LengthSquare() != 0.0f, "Zero denominator");
    return glm::normalize(static_cast<const glm::vec4&>(*this));
}

//------------------------------------------------------------------------------
Vec4f_C Vec4f_C::Min(const Vec4f_C& v) const {
    return LengthSquare() < v.LengthSquare() ? *this : v;
}

//------------------------------------------------------------------------------
Vec4f_C Vec4f_C::Max(const Vec4f_C& v) const {
    return LengthSquare() > v.LengthSquare() ? *this : v;
}

//------------------------------------------------------------------------------
float Vec4f_C::MinComponent() const {
    return glm::min(x, glm::min(y, glm::min(z, w)));
}

//------------------------------------------------------------------------------
float Vec4f_C::MaxComponent() const {
    return glm::max(x, glm::max(y, glm::max(z, w)));
}

//------------------------------------------------------------------------------
float Vec4f_C::Dot(const Vec4f_C& v) const {
    return glm::dot(static_cast<const glm::vec4&>(*this), static_cast<const glm::vec4&>(v));
}

//------------------------------------------------------------------------------
float Vec4f_C::Distance(const Vec4f_C& v) const {
    return glm::distance(static_cast<const glm::vec4&>(*this), static_cast<const glm::vec4&>(v));
}

//------------------------------------------------------------------------------
Vec4f_C Vec4f_C::Rotate(const Vec3f_C& axis, float angle) const {
    return glm::rotate(static_cast<const glm::vec4&>(*this), angle, static_cast<const glm::vec3&>(axis));
}

//------------------------------------------------------------------------------
Vec4f_C Vec4f_C::Reflect(const Vec4f_C& normal) const {
    return glm::reflect(static_cast<const glm::vec4&>(*this), static_cast<const glm::vec4&>(normal));
}

//------------------------------------------------------------------------------
Vec4f_C Vec4f_C::Refract(const Vec4f_C& normal, float mu) const {
    return glm::refract(static_cast<const glm::vec4&>(*this), static_cast<const glm::vec4&>(normal), mu);
}

//------------------------------------------------------------------------------
Vec4f_C Vec4f_C::Project(const Vec4f_C& v) const {
    return glm::proj(static_cast<const glm::vec4&>(*this), static_cast<const glm::vec4&>(v));
}

//------------------------------------------------------------------------------
Vec4f_C Vec4f_C::Reject(const Vec4f_C& v) const {
    return *this - Project(v);
}

//------------------------------------------------------------------------------
void Vec4f_C::DecomposeVec(const Vec4f_C& v, Vec4f_C& proj, Vec4f_C& perp) const {
    proj = this->Project(v);
    perp = *this - proj;
}

//------------------------------------------------------------------------------
bool Vec4f_C::AreSame(const Vec4f_C& v, float eps) const {
    return Math::AreSame(x, v.x, eps) && Math::AreSame(y, v.y, eps) && Math::AreSame(z, v.z, eps) && Math::AreSame(w, v.w, eps);
}

//------------------------------------------------------------------------------
bool Vec4f_C::AreAligned(const Vec4f_C& v, float eps) const {
    return Math::IsZero(this->Angle(v), eps);
}

//------------------------------------------------------------------------------
bool Vec4f_C::IsZero(float eps) const {
    return Math::IsZero(x, eps) && Math::IsZero(y, eps) && Math::IsZero(z, eps) && Math::IsZero(w, eps);
}

//------------------------------------------------------------------------------
bool Vec4f_C::IsNormalized(float eps) const {
    return Math::AreSame(LengthSquare(), 1.0f, eps);
}

//------------------------------------------------------------------------------
float Vec4f_C::Angle(const Vec4f_C& v) const {
    VNE_ASSERT_MSG((!this->IsZero(1E-5f) && !v.IsZero(1E-5f)), "Length of one vector is zero.");
    return Math::ACos(this->Normalize().Dot(v.Normalize()));
}

//------------------------------------------------------------------------------
float Vec4f_C::Angle(const Vec4f_C& p1, const Vec4f_C& p2) const {
    return (p1 - *this).Angle(p2 - *this);
}

//------------------------------------------------------------------------------
Vec4f_C Vec4f_C::MidPoint(const Vec4f_C& point) const {
    return Vec4f_C(Math::MidPoint(x, point.x), Math::MidPoint(y, point.y), Math::MidPoint(z, point.z), Math::MidPoint(w, point.w));
}

//------------------------------------------------------------------------------
Vec4f_C Vec4f_C::Lerp(const Vec4f_C& point, float factor) const {
    return Vec4f_C(Math::Lerp(x, point.x, factor), Math::Lerp(y, point.y, factor), Math::Lerp(z, point.z, factor), Math::Lerp(w, point.w, factor));
}

//------------------------------------------------------------------------------
Vec4f_C& Vec4f_C::operator=(const Vec4f_C& v) {
    x = v.x;
    y = v.y;
    z = v.z;
    w = v.w;
    return *this;
}

//------------------------------------------------------------------------------
Vec4f_C& Vec4f_C::operator+=(float scalar) {
    x += scalar;
    y += scalar;
    z += scalar;
    w += scalar;
    return *this;
}

//------------------------------------------------------------------------------
Vec4f_C& Vec4f_C::operator-=(float scalar) {
    x -= scalar;
    y -= scalar;
    z -= scalar;
    w -= scalar;
    return *this;
}

//------------------------------------------------------------------------------
Vec4f_C& Vec4f_C::operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;
    return *this;
}

//------------------------------------------------------------------------------
Vec4f_C& Vec4f_C::operator/=(float scalar) {
    VNE_ASSERT_MSG(!Math::IsZero(scalar, 1E-5f), "Vec4f_C zero denominator");
    x /= scalar;
    y /= scalar;
    z /= scalar;
    w /= scalar;
    return *this;
}

//------------------------------------------------------------------------------
Vec4f_C& Vec4f_C::operator+=(const Vec4f_C& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;
    return *this;
}

//------------------------------------------------------------------------------
Vec4f_C& Vec4f_C::operator-=(const Vec4f_C& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    w -= v.w;
    return *this;
}

//------------------------------------------------------------------------------
Vec4f_C& Vec4f_C::operator*=(const Vec4f_C& v) {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    w *= v.w;
    return *this;
}

//------------------------------------------------------------------------------
Vec4f_C& Vec4f_C::operator/=(const Vec4f_C& v) {
    VNE_ASSERT_MSG(!Math::IsZero(v.x, 1E-5f), "Vec4f_C zero denominator");
    VNE_ASSERT_MSG(!Math::IsZero(v.y, 1E-5f), "Vec4f_C zero denominator");
    VNE_ASSERT_MSG(!Math::IsZero(v.z, 1E-5f), "Vec4f_C zero denominator");
    VNE_ASSERT_MSG(!Math::IsZero(v.w, 1E-5f), "Vec4f_C zero denominator");
    x /= v.x;
    y /= v.y;
    z /= v.z;
    w /= v.w;
    return *this;
}

//------------------------------------------------------------------------------
Vec4f_C Vec4f_C::operator+(float scalar) const {
    return Vec4f_C(x + scalar, y + scalar, z + scalar, w + scalar);
}

//------------------------------------------------------------------------------
Vec4f_C Vec4f_C::operator-(float scalar) const {
    return Vec4f_C(x - scalar, y - scalar, z - scalar, w - scalar);
}

//------------------------------------------------------------------------------
Vec4f_C Vec4f_C::operator*(float scalar) const {
    return Vec4f_C(x * scalar, y * scalar, z * scalar, w * scalar);
}

//------------------------------------------------------------------------------
Vec4f_C Vec4f_C::operator/(float scalar) const {
    VNE_ASSERT_MSG(!Math::IsZero(scalar, 1E-5f), "Vec4f_C zero denominator");
    return Vec4f_C(x / scalar, y / scalar, z / scalar, w / scalar);
}

//------------------------------------------------------------------------------
Vec4f_C Vec4f_C::operator+(const Vec4f_C& v) const {
    return Vec4f_C(x + v.x, y + v.y, z + v.z, w + v.w);
}

//------------------------------------------------------------------------------
Vec4f_C Vec4f_C::operator-(const Vec4f_C& v) const {
    return Vec4f_C(x - v.x, y - v.y, z - v.z, w - v.w);
}

//------------------------------------------------------------------------------
Vec4f_C Vec4f_C::operator*(const Vec4f_C& v) const {
    return Vec4f_C(x * v.x, y * v.y, z * v.z, w * v.w);
}

//------------------------------------------------------------------------------
Vec4f_C Vec4f_C::operator/(const Vec4f_C& v) const {
    VNE_ASSERT_MSG(!Math::IsZero(v.x, 1E-5f), "Vec4f_C zero denominator");
    VNE_ASSERT_MSG(!Math::IsZero(v.y, 1E-5f), "Vec4f_C zero denominator");
    VNE_ASSERT_MSG(!Math::IsZero(v.z, 1E-5f), "Vec4f_C zero denominator");
    VNE_ASSERT_MSG(!Math::IsZero(v.w, 1E-5f), "Vec4f_C zero denominator");
    return Vec4f_C(x / v.x, y / v.y, z / v.z, w / v.w);
}

//------------------------------------------------------------------------------
bool Vec4f_C::operator==(const Vec4f_C& v) const {
    return x == v.x && y == v.y && z == v.z && w == v.w;
}

//------------------------------------------------------------------------------
bool Vec4f_C::operator!=(const Vec4f_C& v) const {
    return !(*this == v);
}

//------------------------------------------------------------------------------
Vec4f_C Vec4f_C::operator-() const {
    return Vec4f_C(-x, -y, -z, -w);
}

//------------------------------------------------------------------------------
bool Vec4f_C::operator<(const Vec4f_C& v) const {
    return LengthSquare() < v.LengthSquare();
}

//------------------------------------------------------------------------------
bool Vec4f_C::operator>(const Vec4f_C& v) const {
    return LengthSquare() > v.LengthSquare();
}

//------------------------------------------------------------------------------
float& Vec4f_C::operator[](uint32_t index) {
    VNE_ASSERT_MSG(index < 4, "Vec4f_C index out of bounds");
    return (&x)[index];
}

//------------------------------------------------------------------------------
float Vec4f_C::operator[](uint32_t index) const {
    VNE_ASSERT_MSG(index < 4, "Vec4f_C index out of bounds");
    return (&x)[index];
}

//------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const Vec4f_C& v) {
    os << "[" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << "]";
    return os;
}

//------------------------------------------------------------------------------
uint32_t Vec4f_C::Dim() {
    return 4;
}

//------------------------------------------------------------------------------
uint32_t Vec4f_C::Size() {
    return Dim();
}

//------------------------------------------------------------------------------
Vec4f_C Vec4f_C::Zero() {
    return Vec4f_C(0.0f);
}

//------------------------------------------------------------------------------
Vec4f_C Vec4f_C::One() {
    return Vec4f_C(1.0f);
}

//------------------------------------------------------------------------------
Vec4f_C Vec4f_C::XAxis() {
    return Vec4f_C(1.0f, 0.0f, 0.0f, 0.0f);
}

//------------------------------------------------------------------------------
Vec4f_C Vec4f_C::YAxis() {
    return Vec4f_C(0.0f, 1.0f, 0.0f, 0.0f);
}

//------------------------------------------------------------------------------
Vec4f_C Vec4f_C::ZAxis() {
    return Vec4f_C(0.0f, 0.0f, 1.0f, 0.0f);
}

//------------------------------------------------------------------------------
Vec4f_C Vec4f_C::WAxis() {
    return Vec4f_C(0.0f, 0.0f, 0.0f, 1.0f);
}

//------------------------------------------------------------------------------
Vec4f_C Vec4f_C::Normalized(const Vec4f_C& v) {
    Vec4f_C ret = v;
    return ret.Normalize();
}

//------------------------------------------------------------------------------
float Vec4f_C::Distance(const Vec4f_C& v1, const Vec4f_C& v2) {
    Vec4f_C v = v1 - v2;
    return v.Length();
}

//------------------------------------------------------------------------------
float Vec4f_C::Dot(const Vec4f_C& v1, const Vec4f_C& v2) {
    Vec4f_C ret = v1;
    return ret.Dot(v2);
}

//------------------------------------------------------------------------------
Vec4f_C Vec4f_C::MidPoint(const Vec4f_C& p1, const Vec4f_C& p2) {
    Vec4f_C out;
    out.x = Math::MidPoint(p1.x, p2.x);
    out.y = Math::MidPoint(p1.y, p2.y);
    out.z = Math::MidPoint(p1.z, p2.z);
    out.w = Math::MidPoint(p1.w, p2.w);
    return out;
}

//------------------------------------------------------------------------------
Vec4f_C Vec4f_C::Lerp(const Vec4f_C& p1, const Vec4f_C& p2, float factor) {
    Vec4f_C out;
    out.x = Math::Lerp(p1.x, p2.x, factor);
    out.y = Math::Lerp(p1.y, p2.y, factor);
    out.z = Math::Lerp(p1.z, p2.z, factor);
    out.w = Math::Lerp(p1.w, p2.w, factor);
    return out;
}

}  // namespace Math
}  // namespace VNE

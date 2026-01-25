/* ---------------------------------------------------------------------
 * Copyright (c) 2024 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Author:    Ajeet Singh Yadav
 * Created:   July-2024
 *
 * Autodoc:   yes
 * ----------------------------------------------------------------------
 */

// Project includes
#include "vertexnova/math/vec3f.h"
#include "vertexnova/math/math_utils.h"

// Common library includes
#include "vertexnova/common/macros.h"

// Third-party library includes
#include <glm/gtx/projection.hpp>
#include <glm/gtx/rotate_vector.hpp>

namespace {
constexpr uint32_t DIMENSION = 3;
}  // namespace

namespace VNE {
namespace Math {

//------------------------------------------------------------------------------
Vec2f_C Vec3f_C::XY() {
    return Vec2f_C(x, y);
}

//------------------------------------------------------------------------------
float* Vec3f_C::GetPtr() {
    return &x;
}

//------------------------------------------------------------------------------
const float* Vec3f_C::GetPtr() const {
    return &x;
}

//------------------------------------------------------------------------------
Vec3f_C Vec3f_C::Abs() const {
    return Vec3f_C(glm::abs(x), glm::abs(y), glm::abs(z));
}

//------------------------------------------------------------------------------
float Vec3f_C::Length() const {
    return glm::length(glm::vec3(*this));
}

//------------------------------------------------------------------------------
float Vec3f_C::LengthSquare() const {
    return glm::length2(glm::vec3(*this));
}

//------------------------------------------------------------------------------
Vec3f_C Vec3f_C::Normalize() const {
    VNE_ASSERT_MSG(LengthSquare() != 0.0f, "Zero denominator");
    glm::vec3 norm = glm::normalize(glm::vec3(*this));
    return norm;
}

//------------------------------------------------------------------------------
Vec3f_C Vec3f_C::Min(const Vec3f_C& v) const {
    return LengthSquare() < v.LengthSquare() ? glm::vec3(*this) : glm::vec3(v);
}

//------------------------------------------------------------------------------
Vec3f_C Vec3f_C::Max(const Vec3f_C& v) const {
    return LengthSquare() > v.LengthSquare() ? glm::vec3(*this) : glm::vec3(v);
}

//------------------------------------------------------------------------------
float Vec3f_C::MinComponent() const {
    return glm::min(x, glm::min(y, z));
}

//------------------------------------------------------------------------------
float Vec3f_C::MaxComponent() const {
    return glm::max(x, glm::max(y, z));
}

//------------------------------------------------------------------------------
float Vec3f_C::Dot(const Vec3f_C& v) const {
    return glm::dot<3, float, glm::qualifier::highp>(glm::vec3(*this), glm::vec3(v));
}

//------------------------------------------------------------------------------
Vec3f_C Vec3f_C::Cross(const Vec3f_C& v) const {
    return glm::cross(glm::vec3(*this), glm::vec3(v));
}

//------------------------------------------------------------------------------
float Vec3f_C::Distance(const Vec3f_C& v) const {
    return glm::distance(glm::vec3(*this), glm::vec3(v));
}

//------------------------------------------------------------------------------
Vec3f_C Vec3f_C::Rotate(const Vec3f_C& axis, float angle) const {
    return glm::rotate(glm::vec3(*this), angle, glm::vec3(axis));
}

//------------------------------------------------------------------------------
Vec3f_C Vec3f_C::Reflect(const Vec3f_C& normal) const {
    return glm::reflect(glm::vec3(*this), glm::vec3(normal));
}

//------------------------------------------------------------------------------
Vec3f_C Vec3f_C::Refract(const Vec3f_C& normal, float mu) const {
    return glm::refract(glm::vec3(*this), glm::vec3(normal), mu);
}

//------------------------------------------------------------------------------
Vec3f_C Vec3f_C::Project(const Vec3f_C& v) const {
    return glm::proj(glm::vec3(*this), glm::vec3(v));
}

//------------------------------------------------------------------------------
Vec3f_C Vec3f_C::Reject(const Vec3f_C& v) const {
    return *this - Project(v);
}

//------------------------------------------------------------------------------
void Vec3f_C::DecomposeVec(const Vec3f_C& v, Vec3f_C& proj, Vec3f_C& perp) const {
    proj = this->Project(v);
    perp = *this - proj;
}

//------------------------------------------------------------------------------
Vec3f_C Vec3f_C::Perpendicular(const Vec3f_C& v) const {
    Vec3f_C perp = this->Cross(v);
    if (Math::IsZero(perp.LengthSquare(), 1E-5f)) {
        return Vec3f_C();
    } else {
        return perp.Normalize();
    }
}

//------------------------------------------------------------------------------
bool Vec3f_C::AreSame(const Vec3f_C& v, float eps) const {
    return Math::AreSame(x, v.x, eps) && Math::AreSame(y, v.y, eps) && Math::AreSame(z, v.z, eps);
}

//------------------------------------------------------------------------------
bool Vec3f_C::AreAligned(const Vec3f_C& v, float eps) const {
    return Math::IsZero(this->Angle(v), eps);
}

//------------------------------------------------------------------------------
bool Vec3f_C::IsZero(float eps) const {
    return Math::IsZero(x, eps) && Math::IsZero(y, eps) && Math::IsZero(z, eps);
}

//------------------------------------------------------------------------------
bool Vec3f_C::IsNormalized(float eps) const {
    return Math::AreSame(LengthSquare(), 1.0f, eps);
}

//------------------------------------------------------------------------------
bool Vec3f_C::IsLinearDependent(const Vec3f_C& p1, const Vec3f_C& p2, float eps) const {
    return (p1 - *this).Cross(p2 - *this).IsZero(eps);
}

//------------------------------------------------------------------------------
bool Vec3f_C::IsLinearDependent(const Vec3f_C& v, float eps) const {
    return this->Cross(v).IsZero(eps);
}

//------------------------------------------------------------------------------
Vec3f_C& Vec3f_C::ComposeSpherical(float rho, float theta, float phi) {
    this->x = rho * Math::Sin(phi) * Math::Cos(theta);
    this->y = rho * Math::Sin(phi) * Math::Sin(theta);
    this->z = rho * Math::Cos(phi);
    return *this;
}

//------------------------------------------------------------------------------
void Vec3f_C::DecomposeSpherical(float& rho, float& theta, float& phi) const {
    rho = Length();
    VNE_ASSERT_MSG(!Math::IsZero(rho, 1E-5f), "Length of the vector is zero.");
    phi = Math::ACos(z / rho);
    theta = Math::ATan2(y, x);
    if (theta < 0) {
        theta += Math::TwoPi<float>();
    }
}

//------------------------------------------------------------------------------
Vec3f_C& Vec3f_C::ComposeCylindrical(float radius, float angle, float height) {
    this->x = radius * Math::Cos(angle);
    this->y = radius * Math::Sin(angle);
    this->z = height;
    return *this;
}

//------------------------------------------------------------------------------
void Vec3f_C::DecomposeCylindrical(float& radius, float& angle, float& height) const {
    radius = Math::Sqrt(Math::Square<float>(this->x) + Math::Square<float>(this->y));
    angle = Math::ATan2(this->y, this->x);
    if (angle < 0) {
        angle += Math::TwoPi<float>();
    }
    height = this->z;
}

//------------------------------------------------------------------------------
float Vec3f_C::Angle(const Vec3f_C& v) const {
    VNE_ASSERT_MSG((!this->IsZero(1E-5f) && !v.IsZero(1E-5f)), "Length of one vector is zero.");
    return Math::ATan2(this->Cross(v).Length(), this->Dot(v));
}

//------------------------------------------------------------------------------
float Vec3f_C::Angle(const Vec3f_C& p1, const Vec3f_C& p2) const {
    Vec3f_C new_p1 = p1 - *this;
    Vec3f_C new_p2 = p2 - *this;
    return new_p1.Angle(new_p2);
}

//------------------------------------------------------------------------------
Vec3f_C Vec3f_C::MidPoint(const Vec3f_C& point) const {
    return Math::Vec3f_C(Math::MidPoint(x, point.x), Math::MidPoint(y, point.y), Math::MidPoint(z, point.z));
}

//------------------------------------------------------------------------------
Vec3f_C Vec3f_C::Lerp(Vec3f_C& point, float factor) const {
    return Math::Vec3f_C(Math::Lerp(x, point.x, factor), Math::Lerp(y, point.y, factor), Math::Lerp(z, point.z, factor));
}

//------------------------------------------------------------------------------
Vec3f_C& Vec3f_C::operator=(const Vec3f_C& v) {
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
}

//------------------------------------------------------------------------------
Vec3f_C& Vec3f_C::operator+=(float scalar) {
    x += scalar;
    y += scalar;
    z += scalar;
    return *this;
}

//------------------------------------------------------------------------------
Vec3f_C& Vec3f_C::operator-=(float scalar) {
    x -= scalar;
    y -= scalar;
    z -= scalar;
    return *this;
}

//------------------------------------------------------------------------------
Vec3f_C& Vec3f_C::operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

//------------------------------------------------------------------------------
Vec3f_C& Vec3f_C::operator/=(float scalar) {
    VNE_ASSERT_MSG(!Math::IsZero(scalar, 1E-5f), "Vec3f_C zero denominator");
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
}

//------------------------------------------------------------------------------
Vec3f_C& Vec3f_C::operator+=(const Vec3f_C& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

//------------------------------------------------------------------------------
Vec3f_C& Vec3f_C::operator-=(const Vec3f_C& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

//------------------------------------------------------------------------------
Vec3f_C& Vec3f_C::operator*=(const Vec3f_C& v) {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
}

//------------------------------------------------------------------------------
Vec3f_C& Vec3f_C::operator/=(const Vec3f_C& v) {
    VNE_ASSERT_MSG(!Math::IsZero(v.x, 1E-5f), "Vec3f_C zero denominator");
    VNE_ASSERT_MSG(!Math::IsZero(v.y, 1E-5f), "Vec3f_C zero denominator");
    VNE_ASSERT_MSG(!Math::IsZero(v.z, 1E-5f), "Vec3f_C zero denominator");
    x /= v.x;
    y /= v.y;
    z /= v.z;
    return *this;
}

//------------------------------------------------------------------------------
Vec3f_C Vec3f_C::operator+(float scalar) const {
    return Vec3f_C(x + scalar, y + scalar, z + scalar);
}

//------------------------------------------------------------------------------
Vec3f_C Vec3f_C::operator-(float scalar) const {
    return Vec3f_C(x - scalar, y - scalar, z - scalar);
}

//------------------------------------------------------------------------------
Vec3f_C Vec3f_C::operator*(float scalar) const {
    return Vec3f_C(x * scalar, y * scalar, z * scalar);
}

//------------------------------------------------------------------------------
Vec3f_C Vec3f_C::operator/(float scalar) const {
    VNE_ASSERT_MSG(!Math::IsZero(scalar, 1E-5f), "Vec3f_C zero denominator");
    return Vec3f_C(x / scalar, y / scalar, z / scalar);
}

//------------------------------------------------------------------------------
Vec3f_C Vec3f_C::operator+(const Vec3f_C& v) const {
    return Vec3f_C(x + v.x, y + v.y, z + v.z);
}

//------------------------------------------------------------------------------
Vec3f_C Vec3f_C::operator-(const Vec3f_C& v) const {
    return Vec3f_C(x - v.x, y - v.y, z - v.z);
}

//------------------------------------------------------------------------------
Vec3f_C Vec3f_C::operator*(const Vec3f_C& v) const {
    return Vec3f_C(x * v.x, y * v.y, z * v.z);
}

//------------------------------------------------------------------------------
Vec3f_C Vec3f_C::operator/(const Vec3f_C& v) const {
    VNE_ASSERT_MSG(!Math::IsZero(v.x, 1E-5f), "Vec3f_C zero denominator");
    VNE_ASSERT_MSG(!Math::IsZero(v.y, 1E-5f), "Vec3f_C zero denominator");
    VNE_ASSERT_MSG(!Math::IsZero(v.z, 1E-5f), "Vec3f_C zero denominator");
    return Vec3f_C(x / v.x, y / v.y, z / v.z);
}

//------------------------------------------------------------------------------
bool Vec3f_C::operator==(const Vec3f_C& v) const {
    return x == v.x && y == v.y && z == v.z;
}

//------------------------------------------------------------------------------
bool Vec3f_C::operator!=(const Vec3f_C& v) const {
    return x != v.x || y != v.y || z != v.z;
}

//------------------------------------------------------------------------------
bool Vec3f_C::operator>(const Vec3f_C& v) const {
    return LengthSquare() > v.LengthSquare();
}

//------------------------------------------------------------------------------
bool Vec3f_C::operator<(const Vec3f_C& v) const {
    return LengthSquare() < v.LengthSquare();
}

//------------------------------------------------------------------------------
Vec3f_C Vec3f_C::operator-() const {
    return Vec3f_C(-x, -y, -z);
}

//------------------------------------------------------------------------------
float& Vec3f_C::operator[](uint32_t index) {
    VNE_ASSERT_MSG(index < 3, "Vec3f_C index out of bounds");
    return (&x)[index];
}

//------------------------------------------------------------------------------
float Vec3f_C::operator[](uint32_t index) const {
    VNE_ASSERT_MSG(index < 3, "Vec3f_C index out of bounds");
    return (&x)[index];
}

//------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const Vec3f_C& vec) {
    return os << "[" << vec.x << ", " << vec.y << ", " << vec.z << "]";
}

//------------------------------------------------------------------------------
std::istream& operator>>(std::istream& is, Vec3f_C& vec) {
    is >> vec.x;
    is.ignore(2);
    is >> vec.y;
    is.ignore(2);
    is >> vec.z;
    return is;
}

//------------------------------------------------------------------------------
uint32_t Vec3f_C::Dim() {
    return DIMENSION;
}

//------------------------------------------------------------------------------
uint32_t Vec3f_C::Size() {
    return Dim();
}

//------------------------------------------------------------------------------
Vec3f_C Vec3f_C::Zero() {
    return Vec3f_C(0.0f);
}

//------------------------------------------------------------------------------
Vec3f_C Vec3f_C::One() {
    return Vec3f_C(1.0f);
}

//------------------------------------------------------------------------------
Vec3f_C Vec3f_C::XAxis() {
    return Vec3f_C(1.0f, 0.0f, 0.0f);
}

//------------------------------------------------------------------------------
Vec3f_C Vec3f_C::YAxis() {
    return Vec3f_C(0.0f, 1.0f, 0.0f);
}

//------------------------------------------------------------------------------
Vec3f_C Vec3f_C::ZAxis() {
    return Vec3f_C(0.0f, 0.0f, 1.0f);
}

//------------------------------------------------------------------------------
Vec3f_C Vec3f_C::Up() {
    return Vec3f_C(0.0f, 1.0f, 0.0f);
}

//------------------------------------------------------------------------------
Vec3f_C Vec3f_C::Down() {
    return Vec3f_C(0.0f, -1.0f, 0.0f);
}

//------------------------------------------------------------------------------
Vec3f_C Vec3f_C::Left() {
    return Vec3f_C(-1.0f, 0.0f, 0.0f);
}

//------------------------------------------------------------------------------
Vec3f_C Vec3f_C::Right() {
    return Vec3f_C(1.0f, 0.0f, 0.0f);
}

//------------------------------------------------------------------------------
Vec3f_C Vec3f_C::Forward() {
    return Vec3f_C(0.0f, 0.0f, 1.0f);
}

//------------------------------------------------------------------------------
Vec3f_C Vec3f_C::Backward() {
    return Vec3f_C(0.0f, 0.0f, -1.0f);
}

//------------------------------------------------------------------------------
Vec3f_C Vec3f_C::Normalized(const Vec3f_C& v) {
    Vec3f_C ret = v;
    return ret.Normalize();
}

//------------------------------------------------------------------------------
float Vec3f_C::Distance(const Vec3f_C& v1, const Vec3f_C& v2) {
    Vec3f_C v = v1 - v2;
    return v.Length();
}

//------------------------------------------------------------------------------
float Vec3f_C::Dot(const Vec3f_C& v1, const Vec3f_C& v2) {
    Vec3f_C ret = v1;
    return ret.Dot(v2);
}

//------------------------------------------------------------------------------
Vec3f_C Vec3f_C::Cross(const Vec3f_C& v1, const Vec3f_C& v2) {
    Vec3f_C ret = v1;
    return ret.Cross(v2);
}

//------------------------------------------------------------------------------
Vec3f_C Vec3f_C::MidPoint(const Vec3f_C& p1, const Vec3f_C& p2) {
    Vec3f_C out;
    out.x = Math::MidPoint(p1.x, p2.x);
    out.y = Math::MidPoint(p1.y, p2.y);
    out.z = Math::MidPoint(p1.z, p2.z);
    return out;
}

//------------------------------------------------------------------------------
Vec3f_C Vec3f_C::Lerp(const Vec3f_C& p1, const Vec3f_C& p2, float t) {
    Vec3f_C out;
    out.x = Math::Lerp(p1.x, p2.x, t);
    out.y = Math::Lerp(p1.y, p2.y, t);
    out.z = Math::Lerp(p1.z, p2.z, t);
    return out;
}

}  // namespace Math
}  // namespace VNE

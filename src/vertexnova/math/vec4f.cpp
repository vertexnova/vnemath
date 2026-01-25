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

namespace vne::math {

// Constructors
// Vec4f::Vec4f(const Plane_C& plane)
//     : glm::vec4(plane.normal, plane.d) {}

//------------------------------------------------------------------------------
Vec3f Vec4f::xyz() {
    return Vec3f(x, y, z);
}

//------------------------------------------------------------------------------
Vec2f Vec4f::xy() {
    return Vec2f(x, y);
}

//------------------------------------------------------------------------------
float* Vec4f::getPtr() {
    return &x;
}

//------------------------------------------------------------------------------
const float* Vec4f::getPtr() const {
    return &x;
}

//------------------------------------------------------------------------------
Vec4f Vec4f::abs() const {
    return Vec4f(glm::abs(x), glm::abs(y), glm::abs(z), glm::abs(w));
}

//------------------------------------------------------------------------------
float Vec4f::length() const {
    return glm::length(static_cast<const glm::vec4&>(*this));
}

//------------------------------------------------------------------------------
float Vec4f::lengthSquare() const {
    return glm::length2(static_cast<const glm::vec4&>(*this));
}

//------------------------------------------------------------------------------
Vec4f Vec4f::normalize() const {
    VNE_ASSERT_MSG(lengthSquare() != 0.0f, "Zero denominator");
    return glm::normalize(static_cast<const glm::vec4&>(*this));
}

//------------------------------------------------------------------------------
Vec4f Vec4f::min(const Vec4f& v) const {
    return lengthSquare() < v.lengthSquare() ? *this : v;
}

//------------------------------------------------------------------------------
Vec4f Vec4f::max(const Vec4f& v) const {
    return lengthSquare() > v.lengthSquare() ? *this : v;
}

//------------------------------------------------------------------------------
float Vec4f::minComponent() const {
    return glm::min(x, glm::min(y, glm::min(z, w)));
}

//------------------------------------------------------------------------------
float Vec4f::maxComponent() const {
    return glm::max(x, glm::max(y, glm::max(z, w)));
}

//------------------------------------------------------------------------------
float Vec4f::dot(const Vec4f& v) const {
    return glm::dot(static_cast<const glm::vec4&>(*this), static_cast<const glm::vec4&>(v));
}

//------------------------------------------------------------------------------
float Vec4f::distance(const Vec4f& v) const {
    return glm::distance(static_cast<const glm::vec4&>(*this), static_cast<const glm::vec4&>(v));
}

//------------------------------------------------------------------------------
Vec4f Vec4f::rotate(const Vec3f& axis, float angle) const {
    return glm::rotate(static_cast<const glm::vec4&>(*this), angle, static_cast<const glm::vec3&>(axis));
}

//------------------------------------------------------------------------------
Vec4f Vec4f::reflect(const Vec4f& normal) const {
    return glm::reflect(static_cast<const glm::vec4&>(*this), static_cast<const glm::vec4&>(normal));
}

//------------------------------------------------------------------------------
Vec4f Vec4f::refract(const Vec4f& normal, float mu) const {
    return glm::refract(static_cast<const glm::vec4&>(*this), static_cast<const glm::vec4&>(normal), mu);
}

//------------------------------------------------------------------------------
Vec4f Vec4f::project(const Vec4f& v) const {
    return glm::proj(static_cast<const glm::vec4&>(*this), static_cast<const glm::vec4&>(v));
}

//------------------------------------------------------------------------------
Vec4f Vec4f::reject(const Vec4f& v) const {
    return *this - project(v);
}

//------------------------------------------------------------------------------
void Vec4f::decomposeVec(const Vec4f& v, Vec4f& proj, Vec4f& perp) const {
    proj = this->project(v);
    perp = *this - proj;
}

//------------------------------------------------------------------------------
bool Vec4f::areSame(const Vec4f& v, float eps) const {
    return vne::math::areSame(x, v.x, eps) && vne::math::areSame(y, v.y, eps) && vne::math::areSame(z, v.z, eps)
           && vne::math::areSame(w, v.w, eps);
}

//------------------------------------------------------------------------------
bool Vec4f::areAligned(const Vec4f& v, float eps) const {
    return vne::math::isZero(this->angle(v), eps);
}

//------------------------------------------------------------------------------
bool Vec4f::isZero(float eps) const {
    return vne::math::isZero(x, eps) && vne::math::isZero(y, eps) && vne::math::isZero(z, eps)
           && vne::math::isZero(w, eps);
}

//------------------------------------------------------------------------------
bool Vec4f::isNormalized(float eps) const {
    return vne::math::areSame(lengthSquare(), 1.0f, eps);
}

//------------------------------------------------------------------------------
float Vec4f::angle(const Vec4f& v) const {
    VNE_ASSERT_MSG((!this->isZero(1E-5f) && !v.isZero(1E-5f)), "Length of one vector is zero.");
    return vne::math::acos(this->normalize().dot(v.normalize()));
}

//------------------------------------------------------------------------------
float Vec4f::angle(const Vec4f& p1, const Vec4f& p2) const {
    return (p1 - *this).angle(p2 - *this);
}

//------------------------------------------------------------------------------
Vec4f Vec4f::midPoint(const Vec4f& point) const {
    return Vec4f(vne::math::midPoint(x, point.x),
                 vne::math::midPoint(y, point.y),
                 vne::math::midPoint(z, point.z),
                 vne::math::midPoint(w, point.w));
}

//------------------------------------------------------------------------------
Vec4f Vec4f::lerp(const Vec4f& point, float factor) const {
    return Vec4f(vne::math::lerp(x, point.x, factor),
                 vne::math::lerp(y, point.y, factor),
                 vne::math::lerp(z, point.z, factor),
                 vne::math::lerp(w, point.w, factor));
}

//------------------------------------------------------------------------------
Vec4f& Vec4f::operator=(const Vec4f& v) {
    x = v.x;
    y = v.y;
    z = v.z;
    w = v.w;
    return *this;
}

//------------------------------------------------------------------------------
Vec4f& Vec4f::operator+=(float scalar) {
    x += scalar;
    y += scalar;
    z += scalar;
    w += scalar;
    return *this;
}

//------------------------------------------------------------------------------
Vec4f& Vec4f::operator-=(float scalar) {
    x -= scalar;
    y -= scalar;
    z -= scalar;
    w -= scalar;
    return *this;
}

//------------------------------------------------------------------------------
Vec4f& Vec4f::operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;
    return *this;
}

//------------------------------------------------------------------------------
Vec4f& Vec4f::operator/=(float scalar) {
    VNE_ASSERT_MSG(!vne::math::isZero(scalar, 1E-5f), "Vec4f zero denominator");
    x /= scalar;
    y /= scalar;
    z /= scalar;
    w /= scalar;
    return *this;
}

//------------------------------------------------------------------------------
Vec4f& Vec4f::operator+=(const Vec4f& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;
    return *this;
}

//------------------------------------------------------------------------------
Vec4f& Vec4f::operator-=(const Vec4f& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    w -= v.w;
    return *this;
}

//------------------------------------------------------------------------------
Vec4f& Vec4f::operator*=(const Vec4f& v) {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    w *= v.w;
    return *this;
}

//------------------------------------------------------------------------------
Vec4f& Vec4f::operator/=(const Vec4f& v) {
    VNE_ASSERT_MSG(!vne::math::isZero(v.x, 1E-5f), "Vec4f zero denominator");
    VNE_ASSERT_MSG(!vne::math::isZero(v.y, 1E-5f), "Vec4f zero denominator");
    VNE_ASSERT_MSG(!vne::math::isZero(v.z, 1E-5f), "Vec4f zero denominator");
    VNE_ASSERT_MSG(!vne::math::isZero(v.w, 1E-5f), "Vec4f zero denominator");
    x /= v.x;
    y /= v.y;
    z /= v.z;
    w /= v.w;
    return *this;
}

//------------------------------------------------------------------------------
Vec4f Vec4f::operator+(float scalar) const {
    return Vec4f(x + scalar, y + scalar, z + scalar, w + scalar);
}

//------------------------------------------------------------------------------
Vec4f Vec4f::operator-(float scalar) const {
    return Vec4f(x - scalar, y - scalar, z - scalar, w - scalar);
}

//------------------------------------------------------------------------------
Vec4f Vec4f::operator*(float scalar) const {
    return Vec4f(x * scalar, y * scalar, z * scalar, w * scalar);
}

//------------------------------------------------------------------------------
Vec4f Vec4f::operator/(float scalar) const {
    VNE_ASSERT_MSG(!vne::math::isZero(scalar, 1E-5f), "Vec4f zero denominator");
    return Vec4f(x / scalar, y / scalar, z / scalar, w / scalar);
}

//------------------------------------------------------------------------------
Vec4f Vec4f::operator+(const Vec4f& v) const {
    return Vec4f(x + v.x, y + v.y, z + v.z, w + v.w);
}

//------------------------------------------------------------------------------
Vec4f Vec4f::operator-(const Vec4f& v) const {
    return Vec4f(x - v.x, y - v.y, z - v.z, w - v.w);
}

//------------------------------------------------------------------------------
Vec4f Vec4f::operator*(const Vec4f& v) const {
    return Vec4f(x * v.x, y * v.y, z * v.z, w * v.w);
}

//------------------------------------------------------------------------------
Vec4f Vec4f::operator/(const Vec4f& v) const {
    VNE_ASSERT_MSG(!vne::math::isZero(v.x, 1E-5f), "Vec4f zero denominator");
    VNE_ASSERT_MSG(!vne::math::isZero(v.y, 1E-5f), "Vec4f zero denominator");
    VNE_ASSERT_MSG(!vne::math::isZero(v.z, 1E-5f), "Vec4f zero denominator");
    VNE_ASSERT_MSG(!vne::math::isZero(v.w, 1E-5f), "Vec4f zero denominator");
    return Vec4f(x / v.x, y / v.y, z / v.z, w / v.w);
}

//------------------------------------------------------------------------------
bool Vec4f::operator==(const Vec4f& v) const {
    return x == v.x && y == v.y && z == v.z && w == v.w;
}

//------------------------------------------------------------------------------
bool Vec4f::operator!=(const Vec4f& v) const {
    return !(*this == v);
}

//------------------------------------------------------------------------------
Vec4f Vec4f::operator-() const {
    return Vec4f(-x, -y, -z, -w);
}

//------------------------------------------------------------------------------
bool Vec4f::operator<(const Vec4f& v) const {
    return lengthSquare() < v.lengthSquare();
}

//------------------------------------------------------------------------------
bool Vec4f::operator>(const Vec4f& v) const {
    return lengthSquare() > v.lengthSquare();
}

//------------------------------------------------------------------------------
float& Vec4f::operator[](uint32_t index) {
    VNE_ASSERT_MSG(index < 4, "Vec4f index out of bounds");
    return (&x)[index];
}

//------------------------------------------------------------------------------
float Vec4f::operator[](uint32_t index) const {
    VNE_ASSERT_MSG(index < 4, "Vec4f index out of bounds");
    return (&x)[index];
}

//------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const Vec4f& v) {
    os << "[" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << "]";
    return os;
}

//------------------------------------------------------------------------------
uint32_t Vec4f::dim() {
    return 4;
}

//------------------------------------------------------------------------------
uint32_t Vec4f::size() {
    return dim();
}

//------------------------------------------------------------------------------
Vec4f Vec4f::zero() {
    return Vec4f(0.0f);
}

//------------------------------------------------------------------------------
Vec4f Vec4f::one() {
    return Vec4f(1.0f);
}

//------------------------------------------------------------------------------
Vec4f Vec4f::xAxis() {
    return Vec4f(1.0f, 0.0f, 0.0f, 0.0f);
}

//------------------------------------------------------------------------------
Vec4f Vec4f::yAxis() {
    return Vec4f(0.0f, 1.0f, 0.0f, 0.0f);
}

//------------------------------------------------------------------------------
Vec4f Vec4f::zAxis() {
    return Vec4f(0.0f, 0.0f, 1.0f, 0.0f);
}

//------------------------------------------------------------------------------
Vec4f Vec4f::wAxis() {
    return Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
}

//------------------------------------------------------------------------------
Vec4f Vec4f::normalized(const Vec4f& v) {
    Vec4f ret = v;
    return ret.normalize();
}

//------------------------------------------------------------------------------
float Vec4f::distance(const Vec4f& v1, const Vec4f& v2) {
    Vec4f v = v1 - v2;
    return v.length();
}

//------------------------------------------------------------------------------
float Vec4f::dot(const Vec4f& v1, const Vec4f& v2) {
    Vec4f ret = v1;
    return ret.dot(v2);
}

//------------------------------------------------------------------------------
Vec4f Vec4f::midPoint(const Vec4f& p1, const Vec4f& p2) {
    Vec4f out;
    out.x = vne::math::midPoint(p1.x, p2.x);
    out.y = vne::math::midPoint(p1.y, p2.y);
    out.z = vne::math::midPoint(p1.z, p2.z);
    out.w = vne::math::midPoint(p1.w, p2.w);
    return out;
}

//------------------------------------------------------------------------------
Vec4f Vec4f::lerp(const Vec4f& p1, const Vec4f& p2, float factor) {
    Vec4f out;
    out.x = vne::math::lerp(p1.x, p2.x, factor);
    out.y = vne::math::lerp(p1.y, p2.y, factor);
    out.z = vne::math::lerp(p1.z, p2.z, factor);
    out.w = vne::math::lerp(p1.w, p2.w, factor);
    return out;
}

}  // namespace vne::math

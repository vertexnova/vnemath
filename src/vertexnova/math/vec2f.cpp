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

// Corresponding header
#include "vertexnova/math/vec2f.h"

// Project headers
#include "vertexnova/common/macros.h"
#include "vertexnova/math/math_utils.h"

// Third-party headers
#include <glm/gtx/projection.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/transform.hpp>

namespace vne::math {

//------------------------------------------------------------------------------
float* Vec2f::getPtr() {
    return &x;
}

//------------------------------------------------------------------------------
const float* Vec2f::getPtr() const {
    return &x;
}

//------------------------------------------------------------------------------
Vec2f Vec2f::abs() const {
    return {glm::abs(x), glm::abs(y)};
}

//------------------------------------------------------------------------------
float Vec2f::length() const {
    return glm::length(glm::vec2(*this));
}

//------------------------------------------------------------------------------
float Vec2f::lengthSquare() const {
    return glm::length2(glm::vec2(*this));
}

//------------------------------------------------------------------------------
Vec2f Vec2f::normalize() const {
    VNE_ASSERT_MSG(!vne::math::isZero(lengthSquare(), kZeroTolerance), "Zero denominator");
    glm::vec2 norm = glm::normalize(glm::vec2(*this));
    return norm;
}

//------------------------------------------------------------------------------
Vec2f Vec2f::min(const Vec2f& v) const {
    return lengthSquare() < v.lengthSquare() ? *this : v;
}

//------------------------------------------------------------------------------
Vec2f Vec2f::max(const Vec2f& v) const {
    return lengthSquare() > v.lengthSquare() ? *this : v;
}

//------------------------------------------------------------------------------
float Vec2f::minComponent() const {
    return glm::min(x, y);
}

//------------------------------------------------------------------------------
float Vec2f::maxComponent() const {
    return glm::max(x, y);
}

//------------------------------------------------------------------------------
float Vec2f::dot(const Vec2f& v) const {
    return glm::dot<2, float, glm::qualifier::highp>(glm::vec2(*this), glm::vec2(v));
}

//------------------------------------------------------------------------------
float Vec2f::cross(const Vec2f& v) const {
    return x * v.y - y * v.x;
}

//------------------------------------------------------------------------------
float Vec2f::distance(const Vec2f& v) const {
    Vec2f diff = *this - v;
    return diff.length();
}

//------------------------------------------------------------------------------
Vec2f Vec2f::rotate(const Vec2f& axis, float angle_val) const {
    return glm::rotate(glm::vec2(axis), angle_val);
}

//------------------------------------------------------------------------------
Vec2f Vec2f::reflect(const Vec2f& normal) const {
    return glm::reflect(glm::vec2(*this), glm::vec2(normal));
}

//------------------------------------------------------------------------------
Vec2f Vec2f::refract(const Vec2f& normal, float mu) const {
    return glm::refract(glm::vec2(*this), glm::vec2(normal), mu);
}

//------------------------------------------------------------------------------
Vec2f Vec2f::project(const Vec2f& v) const {
    return glm::proj(glm::vec2(*this), glm::vec2(v));
}

//------------------------------------------------------------------------------
Vec2f Vec2f::reject(const Vec2f& v) const {
    return *this - project(v);
}

//------------------------------------------------------------------------------
void Vec2f::decomposeVec(const Vec2f& v, Vec2f& proj, Vec2f& perp) const {
    proj = this->project(v);
    perp = *this - proj;
}

//------------------------------------------------------------------------------
Vec2f Vec2f::perpendicular() const {
    return {-y, x};
}

//------------------------------------------------------------------------------
bool Vec2f::areSame(const Vec2f& v, float eps) const {
    return vne::math::areSame(x, v.x, eps) && vne::math::areSame(y, v.y, eps);
}

//------------------------------------------------------------------------------
bool Vec2f::areAligned(const Vec2f& v, float eps) const {
    return vne::math::isZero(this->angle(v), eps);
}

//------------------------------------------------------------------------------
bool Vec2f::isZero(float eps) const {
    return vne::math::isZero(x, eps) && vne::math::isZero(y, eps);
}

//------------------------------------------------------------------------------
bool Vec2f::isNormalized(float eps) const {
    return vne::math::areSame(lengthSquare(), 1.0f, eps);
}

//------------------------------------------------------------------------------
Vec2f& Vec2f::composePolar(float radius, float angle_val) {
    this->x = radius * cos(angle_val);
    this->y = radius * sin(angle_val);
    return *this;
}

//------------------------------------------------------------------------------
void Vec2f::decomposePolar(float& radius, float& angle_val) const {
    radius = length();
    angle_val = atan2(y, x);

    if (angle_val < 0) {
        angle_val += twoPi<float>();
    }
}

//------------------------------------------------------------------------------
float Vec2f::angle() const {
    float angle_val = atan2(this->y, this->x);
    if (angle_val < 0) {
        angle_val += twoPi<float>();
    }
    return angle_val;
}

//------------------------------------------------------------------------------
float Vec2f::angle(const Vec2f& v) const {
    float angle_val = atan2(x * v.y - y * v.x, x * v.x + y * v.y);
    if (angle_val < 0) {
        angle_val += twoPi<float>();
    }
    return angle_val;
}

//------------------------------------------------------------------------------
float Vec2f::angle(const Vec2f& p1, const Vec2f& p2) const {
    Vec2f new_p1 = p1 - *this;
    Vec2f new_p2 = p2 - *this;
    return new_p1.angle(new_p2);
}

//------------------------------------------------------------------------------
Vec2f Vec2f::midPoint(const Vec2f& point) const {
    return {vne::math::midPoint(x, point.x), vne::math::midPoint(y, point.y)};
}

//------------------------------------------------------------------------------
Vec2f Vec2f::lerp(Vec2f& point, float factor) const {
    return {vne::math::lerp(x, point.x, factor), vne::math::lerp(y, point.y, factor)};
}

//------------------------------------------------------------------------------
Vec2f& Vec2f::operator=(const Vec2f& v) {
    x = v.x;
    y = v.y;
    return *this;
}

//------------------------------------------------------------------------------
Vec2f& Vec2f::operator+=(const float& scalar) {
    x += scalar;
    y += scalar;
    return *this;
}

//------------------------------------------------------------------------------
Vec2f& Vec2f::operator-=(const float& scalar) {
    x -= scalar;
    y -= scalar;
    return *this;
}

//------------------------------------------------------------------------------
Vec2f& Vec2f::operator*=(const float& scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}

//------------------------------------------------------------------------------
Vec2f& Vec2f::operator/=(const float& scalar) {
    VNE_ASSERT_MSG(!vne::math::isZero(scalar, kZeroTolerance), "Vec2f zero denominator");
    x /= scalar;
    y /= scalar;
    return *this;
}

//------------------------------------------------------------------------------
Vec2f& Vec2f::operator+=(const Vec2f& v) {
    x += v.x;
    y += v.y;
    return *this;
}

//------------------------------------------------------------------------------
Vec2f& Vec2f::operator-=(const Vec2f& v) {
    x -= v.x;
    y -= v.y;
    return *this;
}

//------------------------------------------------------------------------------
Vec2f& Vec2f::operator*=(const Vec2f& v) {
    x *= v.x;
    y *= v.y;
    return *this;
}

//------------------------------------------------------------------------------
Vec2f& Vec2f::operator/=(const Vec2f& v) {
    VNE_ASSERT_MSG(!vne::math::isZero(v.x, kZeroTolerance), "Vec2f zero denominator");
    VNE_ASSERT_MSG(!vne::math::isZero(v.y, kZeroTolerance), "Vec2f zero denominator");
    x /= v.x;
    y /= v.y;
    return *this;
}

//------------------------------------------------------------------------------
Vec2f Vec2f::operator+(const float& scalar) const {
    return {x + scalar, y + scalar};
}

//------------------------------------------------------------------------------
Vec2f Vec2f::operator-(const float& scalar) const {
    return {x - scalar, y - scalar};
}

//------------------------------------------------------------------------------
Vec2f Vec2f::operator*(const float& scalar) const {
    return {x * scalar, y * scalar};
}

//------------------------------------------------------------------------------
Vec2f Vec2f::operator/(const float& scalar) const {
    VNE_ASSERT_MSG(!vne::math::isZero(scalar, kZeroTolerance), "Vec2f zero denominator");
    return {x / scalar, y / scalar};
}

//------------------------------------------------------------------------------
Vec2f Vec2f::operator+(const Vec2f& v) const {
    return {x + v.x, y + v.y};
}

//------------------------------------------------------------------------------
Vec2f Vec2f::operator-(const Vec2f& v) const {
    return {x - v.x, y - v.y};
}

//------------------------------------------------------------------------------
Vec2f Vec2f::operator*(const Vec2f& v) const {
    return {x * v.x, y * v.y};
}

//------------------------------------------------------------------------------
Vec2f Vec2f::operator/(const Vec2f& v) const {
    VNE_ASSERT_MSG(!vne::math::isZero(v.x, kZeroTolerance), "Vec2f zero denominator");
    VNE_ASSERT_MSG(!vne::math::isZero(v.y, kZeroTolerance), "Vec2f zero denominator");
    return {x / v.x, y / v.y};
}

//------------------------------------------------------------------------------
bool Vec2f::operator==(const Vec2f& v) const {
    return x == v.x && y == v.y;
}

//------------------------------------------------------------------------------
bool Vec2f::operator!=(const Vec2f& v) const {
    return x != v.x || y != v.y;
}

//------------------------------------------------------------------------------
bool Vec2f::operator>(const Vec2f& v) const {
    return lengthSquare() > v.lengthSquare();
}

//------------------------------------------------------------------------------
bool Vec2f::operator<(const Vec2f& v) const {
    return lengthSquare() < v.lengthSquare();
}

//------------------------------------------------------------------------------
Vec2f Vec2f::operator-() const {
    return {-x, -y};
}

//------------------------------------------------------------------------------
float& Vec2f::operator[](uint32_t index) {
    VNE_ASSERT_MSG(index < 2, "Vec2f index out of bounds");
    return (&x)[index];
}

//------------------------------------------------------------------------------
float Vec2f::operator[](uint32_t index) const {
    VNE_ASSERT_MSG(index < 2, "Vec2f index out of bounds");
    return (&x)[index];
}

//------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const Vec2f& vec) {
    return os << "[" << vec.x << ", " << vec.y << "]";
}

//------------------------------------------------------------------------------
std::istream& operator>>(std::istream& is, Vec2f& vec) {
    is >> vec.x;
    is.ignore(2);
    is >> vec.y;
    return is;
}

//------------------------------------------------------------------------------
uint32_t Vec2f::dim() {
    return 2;
}

//------------------------------------------------------------------------------
uint32_t Vec2f::size() {
    return dim();
}

//------------------------------------------------------------------------------
Vec2f Vec2f::zero() {
    return {};
}

//------------------------------------------------------------------------------
Vec2f Vec2f::one() {
    return {1.0f, 1.0f};
}

//------------------------------------------------------------------------------
Vec2f Vec2f::xAxis() {
    return {1.0f, 0.0f};
}

//------------------------------------------------------------------------------
Vec2f Vec2f::yAxis() {
    return {0.0f, 1.0f};
}

//------------------------------------------------------------------------------
Vec2f Vec2f::normalized(const Vec2f& v) {
    const Vec2f& ret = v;
    return ret.normalize();
}

//------------------------------------------------------------------------------
float Vec2f::distance(const Vec2f& v1, const Vec2f& v2) {
    Vec2f v = v1 - v2;
    return v.length();
}

//------------------------------------------------------------------------------
float Vec2f::dot(const Vec2f& v1, const Vec2f& v2) {
    const Vec2f& ret = v1;
    return ret.dot(v2);
}

//------------------------------------------------------------------------------
float Vec2f::cross(const Vec2f& v1, const Vec2f& v2) {
    const Vec2f& ret = v1;
    return ret.cross(v2);
}

//------------------------------------------------------------------------------
Vec2f Vec2f::midPoint(const Vec2f& p1, const Vec2f& p2) {
    Vec2f out;
    out.x = vne::math::midPoint(p1.x, p2.x);
    out.y = vne::math::midPoint(p1.y, p2.y);
    return out;
}

//------------------------------------------------------------------------------
Vec2f Vec2f::lerp(const Vec2f& p1, const Vec2f& p2, float factor) {
    Vec2f out;
    out.x = vne::math::lerp(p1.x, p2.x, factor);
    out.y = vne::math::lerp(p1.y, p2.y, factor);
    return out;
}

}  // namespace vne::math

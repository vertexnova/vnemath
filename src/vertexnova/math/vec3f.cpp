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
constexpr uint32_t kDimension = 3;
}  // namespace

namespace vne::math {

//------------------------------------------------------------------------------
Vec2f Vec3f::xy() {
    return {x, y};
}

//------------------------------------------------------------------------------
float* Vec3f::getPtr() {
    return &x;
}

//------------------------------------------------------------------------------
const float* Vec3f::getPtr() const {
    return &x;
}

//------------------------------------------------------------------------------
Vec3f Vec3f::abs() const {
    return {glm::abs(x), glm::abs(y), glm::abs(z)};
}

//------------------------------------------------------------------------------
float Vec3f::length() const {
    return glm::length(glm::vec3(*this));
}

//------------------------------------------------------------------------------
float Vec3f::lengthSquare() const {
    return glm::length2(glm::vec3(*this));
}

//------------------------------------------------------------------------------
Vec3f Vec3f::normalize() const {
    VNE_ASSERT_MSG(lengthSquare() != 0.0f, "Zero denominator");
    glm::vec3 norm = glm::normalize(glm::vec3(*this));
    return norm;
}

//------------------------------------------------------------------------------
Vec3f Vec3f::min(const Vec3f& v) const {
    return lengthSquare() < v.lengthSquare() ? glm::vec3(*this) : glm::vec3(v);
}

//------------------------------------------------------------------------------
Vec3f Vec3f::max(const Vec3f& v) const {
    return lengthSquare() > v.lengthSquare() ? glm::vec3(*this) : glm::vec3(v);
}

//------------------------------------------------------------------------------
float Vec3f::minComponent() const {
    return glm::min(x, glm::min(y, z));
}

//------------------------------------------------------------------------------
float Vec3f::maxComponent() const {
    return glm::max(x, glm::max(y, z));
}

//------------------------------------------------------------------------------
float Vec3f::dot(const Vec3f& v) const {
    return glm::dot<3, float, glm::qualifier::highp>(glm::vec3(*this), glm::vec3(v));
}

//------------------------------------------------------------------------------
Vec3f Vec3f::cross(const Vec3f& v) const {
    return glm::cross(glm::vec3(*this), glm::vec3(v));
}

//------------------------------------------------------------------------------
float Vec3f::distance(const Vec3f& v) const {
    return glm::distance(glm::vec3(*this), glm::vec3(v));
}

//------------------------------------------------------------------------------
Vec3f Vec3f::rotate(const Vec3f& axis, float angle) const {
    return glm::rotate(glm::vec3(*this), angle, glm::vec3(axis));
}

//------------------------------------------------------------------------------
Vec3f Vec3f::reflect(const Vec3f& normal) const {
    return glm::reflect(glm::vec3(*this), glm::vec3(normal));
}

//------------------------------------------------------------------------------
Vec3f Vec3f::refract(const Vec3f& normal, float mu) const {
    return glm::refract(glm::vec3(*this), glm::vec3(normal), mu);
}

//------------------------------------------------------------------------------
Vec3f Vec3f::project(const Vec3f& v) const {
    return glm::proj(glm::vec3(*this), glm::vec3(v));
}

//------------------------------------------------------------------------------
Vec3f Vec3f::reject(const Vec3f& v) const {
    return *this - project(v);
}

//------------------------------------------------------------------------------
void Vec3f::decomposeVec(const Vec3f& v, Vec3f& proj, Vec3f& perp) const {
    proj = this->project(v);
    perp = *this - proj;
}

//------------------------------------------------------------------------------
Vec3f Vec3f::perpendicular(const Vec3f& v) const {
    Vec3f perp = this->cross(v);
    if (vne::math::isZero(perp.lengthSquare(), kZeroTolerance)) {
        return {};
    } else {
        return perp.normalize();
    }
}

//------------------------------------------------------------------------------
bool Vec3f::areSame(const Vec3f& v, float eps) const {
    return vne::math::areSame(x, v.x, eps) && vne::math::areSame(y, v.y, eps) && vne::math::areSame(z, v.z, eps);
}

//------------------------------------------------------------------------------
bool Vec3f::areAligned(const Vec3f& v, float eps) const {
    return vne::math::isZero(this->angle(v), eps);
}

//------------------------------------------------------------------------------
bool Vec3f::isZero(float eps) const {
    return vne::math::isZero(x, eps) && vne::math::isZero(y, eps) && vne::math::isZero(z, eps);
}

//------------------------------------------------------------------------------
bool Vec3f::isNormalized(float eps) const {
    return vne::math::areSame(lengthSquare(), 1.0f, eps);
}

//------------------------------------------------------------------------------
bool Vec3f::isLinearDependent(const Vec3f& p1, const Vec3f& p2, float eps) const {
    return (p1 - *this).cross(p2 - *this).isZero(eps);
}

//------------------------------------------------------------------------------
bool Vec3f::isLinearDependent(const Vec3f& v, float eps) const {
    return this->cross(v).isZero(eps);
}

//------------------------------------------------------------------------------
Vec3f& Vec3f::composeSpherical(float rho, float theta, float phi) {
    this->x = rho * vne::math::sin(phi) * vne::math::cos(theta);
    this->y = rho * vne::math::sin(phi) * vne::math::sin(theta);
    this->z = rho * vne::math::cos(phi);
    return *this;
}

//------------------------------------------------------------------------------
void Vec3f::decomposeSpherical(float& rho, float& theta, float& phi) const {
    rho = length();
    VNE_ASSERT_MSG(!vne::math::isZero(rho, kZeroTolerance), "Length of the vector is zero.");
    phi = vne::math::acos(z / rho);
    theta = vne::math::atan2(y, x);
    if (theta < 0) {
        theta += vne::math::twoPi<float>();
    }
}

//------------------------------------------------------------------------------
Vec3f& Vec3f::composeCylindrical(float radius, float angle, float height) {
    this->x = radius * vne::math::cos(angle);
    this->y = radius * vne::math::sin(angle);
    this->z = height;
    return *this;
}

//------------------------------------------------------------------------------
void Vec3f::decomposeCylindrical(float& radius, float& angle, float& height) const {
    radius = vne::math::sqrt(vne::math::square<float>(this->x) + vne::math::square<float>(this->y));
    angle = vne::math::atan2(this->y, this->x);
    if (angle < 0) {
        angle += vne::math::twoPi<float>();
    }
    height = this->z;
}

//------------------------------------------------------------------------------
float Vec3f::angle(const Vec3f& v) const {
    VNE_ASSERT_MSG((!this->isZero(kZeroTolerance) && !v.isZero(kZeroTolerance)), "Length of one vector is zero.");
    return vne::math::atan2(this->cross(v).length(), this->dot(v));
}

//------------------------------------------------------------------------------
float Vec3f::angle(const Vec3f& p1, const Vec3f& p2) const {
    Vec3f new_p1 = p1 - *this;
    Vec3f new_p2 = p2 - *this;
    return new_p1.angle(new_p2);
}

//------------------------------------------------------------------------------
Vec3f Vec3f::midPoint(const Vec3f& point) const {
    return {vne::math::midPoint(x, point.x), vne::math::midPoint(y, point.y), vne::math::midPoint(z, point.z)};
}

//------------------------------------------------------------------------------
Vec3f Vec3f::lerp(Vec3f& point, float factor) const {
    return {vne::math::lerp(x, point.x, factor),
                 vne::math::lerp(y, point.y, factor),
                 vne::math::lerp(z, point.z, factor)};
}

//------------------------------------------------------------------------------
Vec3f& Vec3f::operator=(const Vec3f& v) {
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
}

//------------------------------------------------------------------------------
Vec3f& Vec3f::operator+=(float scalar) {
    x += scalar;
    y += scalar;
    z += scalar;
    return *this;
}

//------------------------------------------------------------------------------
Vec3f& Vec3f::operator-=(float scalar) {
    x -= scalar;
    y -= scalar;
    z -= scalar;
    return *this;
}

//------------------------------------------------------------------------------
Vec3f& Vec3f::operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

//------------------------------------------------------------------------------
Vec3f& Vec3f::operator/=(float scalar) {
    VNE_ASSERT_MSG(!vne::math::isZero(scalar, kZeroTolerance), "Vec3f zero denominator");
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
}

//------------------------------------------------------------------------------
Vec3f& Vec3f::operator+=(const Vec3f& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

//------------------------------------------------------------------------------
Vec3f& Vec3f::operator-=(const Vec3f& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

//------------------------------------------------------------------------------
Vec3f& Vec3f::operator*=(const Vec3f& v) {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
}

//------------------------------------------------------------------------------
Vec3f& Vec3f::operator/=(const Vec3f& v) {
    VNE_ASSERT_MSG(!vne::math::isZero(v.x, kZeroTolerance), "Vec3f zero denominator");
    VNE_ASSERT_MSG(!vne::math::isZero(v.y, kZeroTolerance), "Vec3f zero denominator");
    VNE_ASSERT_MSG(!vne::math::isZero(v.z, kZeroTolerance), "Vec3f zero denominator");
    x /= v.x;
    y /= v.y;
    z /= v.z;
    return *this;
}

//------------------------------------------------------------------------------
Vec3f Vec3f::operator+(float scalar) const {
    return {x + scalar, y + scalar, z + scalar};
}

//------------------------------------------------------------------------------
Vec3f Vec3f::operator-(float scalar) const {
    return {x - scalar, y - scalar, z - scalar};
}

//------------------------------------------------------------------------------
Vec3f Vec3f::operator*(float scalar) const {
    return {x * scalar, y * scalar, z * scalar};
}

//------------------------------------------------------------------------------
Vec3f Vec3f::operator/(float scalar) const {
    VNE_ASSERT_MSG(!vne::math::isZero(scalar, kZeroTolerance), "Vec3f zero denominator");
    return {x / scalar, y / scalar, z / scalar};
}

//------------------------------------------------------------------------------
Vec3f Vec3f::operator+(const Vec3f& v) const {
    return {x + v.x, y + v.y, z + v.z};
}

//------------------------------------------------------------------------------
Vec3f Vec3f::operator-(const Vec3f& v) const {
    return {x - v.x, y - v.y, z - v.z};
}

//------------------------------------------------------------------------------
Vec3f Vec3f::operator*(const Vec3f& v) const {
    return {x * v.x, y * v.y, z * v.z};
}

//------------------------------------------------------------------------------
Vec3f Vec3f::operator/(const Vec3f& v) const {
    VNE_ASSERT_MSG(!vne::math::isZero(v.x, kZeroTolerance), "Vec3f zero denominator");
    VNE_ASSERT_MSG(!vne::math::isZero(v.y, kZeroTolerance), "Vec3f zero denominator");
    VNE_ASSERT_MSG(!vne::math::isZero(v.z, kZeroTolerance), "Vec3f zero denominator");
    return {x / v.x, y / v.y, z / v.z};
}

//------------------------------------------------------------------------------
bool Vec3f::operator==(const Vec3f& v) const {
    return x == v.x && y == v.y && z == v.z;
}

//------------------------------------------------------------------------------
bool Vec3f::operator!=(const Vec3f& v) const {
    return x != v.x || y != v.y || z != v.z;
}

//------------------------------------------------------------------------------
bool Vec3f::operator>(const Vec3f& v) const {
    return lengthSquare() > v.lengthSquare();
}

//------------------------------------------------------------------------------
bool Vec3f::operator<(const Vec3f& v) const {
    return lengthSquare() < v.lengthSquare();
}

//------------------------------------------------------------------------------
Vec3f Vec3f::operator-() const {
    return {-x, -y, -z};
}

//------------------------------------------------------------------------------
float& Vec3f::operator[](uint32_t index) {
    VNE_ASSERT_MSG(index < 3, "Vec3f index out of bounds");
    return (&x)[index];
}

//------------------------------------------------------------------------------
float Vec3f::operator[](uint32_t index) const {
    VNE_ASSERT_MSG(index < 3, "Vec3f index out of bounds");
    return (&x)[index];
}

//------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const Vec3f& vec) {
    return os << "[" << vec.x << ", " << vec.y << ", " << vec.z << "]";
}

//------------------------------------------------------------------------------
std::istream& operator>>(std::istream& is, Vec3f& vec) {
    is >> vec.x;
    is.ignore(2);
    is >> vec.y;
    is.ignore(2);
    is >> vec.z;
    return is;
}

//------------------------------------------------------------------------------
uint32_t Vec3f::dim() {
    return kDimension;
}

//------------------------------------------------------------------------------
uint32_t Vec3f::size() {
    return dim();
}

//------------------------------------------------------------------------------
Vec3f Vec3f::zero() {
    return Vec3f(0.0f);
}

//------------------------------------------------------------------------------
Vec3f Vec3f::one() {
    return Vec3f(1.0f);
}

//------------------------------------------------------------------------------
Vec3f Vec3f::xAxis() {
    return {1.0f, 0.0f, 0.0f};
}

//------------------------------------------------------------------------------
Vec3f Vec3f::yAxis() {
    return {0.0f, 1.0f, 0.0f};
}

//------------------------------------------------------------------------------
Vec3f Vec3f::zAxis() {
    return {0.0f, 0.0f, 1.0f};
}

//------------------------------------------------------------------------------
Vec3f Vec3f::up() {
    return {0.0f, 1.0f, 0.0f};
}

//------------------------------------------------------------------------------
Vec3f Vec3f::down() {
    return {0.0f, -1.0f, 0.0f};
}

//------------------------------------------------------------------------------
Vec3f Vec3f::left() {
    return {-1.0f, 0.0f, 0.0f};
}

//------------------------------------------------------------------------------
Vec3f Vec3f::right() {
    return {1.0f, 0.0f, 0.0f};
}

//------------------------------------------------------------------------------
Vec3f Vec3f::forward() {
    return {0.0f, 0.0f, 1.0f};
}

//------------------------------------------------------------------------------
Vec3f Vec3f::backward() {
    return {0.0f, 0.0f, -1.0f};
}

//------------------------------------------------------------------------------
Vec3f Vec3f::normalized(const Vec3f& v) {
    const Vec3f& ret = v;
    return ret.normalize();
}

//------------------------------------------------------------------------------
float Vec3f::distance(const Vec3f& v1, const Vec3f& v2) {
    Vec3f v = v1 - v2;
    return v.length();
}

//------------------------------------------------------------------------------
float Vec3f::dot(const Vec3f& v1, const Vec3f& v2) {
    const Vec3f& ret = v1;
    return ret.dot(v2);
}

//------------------------------------------------------------------------------
Vec3f Vec3f::cross(const Vec3f& v1, const Vec3f& v2) {
    const Vec3f& ret = v1;
    return ret.cross(v2);
}

//------------------------------------------------------------------------------
Vec3f Vec3f::midPoint(const Vec3f& p1, const Vec3f& p2) {
    Vec3f out;
    out.x = vne::math::midPoint(p1.x, p2.x);
    out.y = vne::math::midPoint(p1.y, p2.y);
    out.z = vne::math::midPoint(p1.z, p2.z);
    return out;
}

//------------------------------------------------------------------------------
Vec3f Vec3f::lerp(const Vec3f& p1, const Vec3f& p2, float t) {
    Vec3f out;
    out.x = vne::math::lerp(p1.x, p2.x, t);
    out.y = vne::math::lerp(p1.y, p2.y, t);
    out.z = vne::math::lerp(p1.z, p2.z, t);
    return out;
}

}  // namespace vne::math

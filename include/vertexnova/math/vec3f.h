#pragma once
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

/**
 * @file vec3f.h
 * @brief Represents a three-dimensional vector in the space.
 */

// GLM Configuration
#ifndef GLM_ENABLE_EXPERIMENTAL
#define GLM_ENABLE_EXPERIMENTAL
#endif

// Project includes
#include "vec2f.h"

// Third-party library includes
#include <glm/vec3.hpp>

// Standard library includes
#include <ostream>

namespace vne::math {

class Vec3f : public glm::vec3 {
   public:
    Vec3f() noexcept
        : glm::vec3(0.0f) {}
    Vec3f(float x_value, float y_value, float z_value) noexcept
        : glm::vec3(x_value, y_value, z_value) {}
    Vec3f(const float xyz) noexcept
        : glm::vec3(xyz) {}
    Vec3f(const Vec3f& v) noexcept
        : glm::vec3(v) {}
    Vec3f(const glm::vec3& v) noexcept
        : glm::vec3(v.x, v.y, v.z) {}
    Vec3f(const Vec2f& v) noexcept
        : glm::vec3(v.x, v.y, 0.0f) {}
    Vec3f(const glm::vec2& v) noexcept
        : glm::vec3(v.x, v.y, 0.0f) {}
    Vec3f(const Vec2f& v, float z_value) noexcept
        : glm::vec3(v, z_value) {}
    Vec3f(const glm::vec2& v, float z_value) noexcept
        : glm::vec3(v, z_value) {}

    [[nodiscard]] Vec2f xy() noexcept;

   public:
    [[nodiscard]] float* getPtr() noexcept;
    [[nodiscard]] const float* getPtr() const noexcept;

   public:
    [[nodiscard]] Vec3f abs() const noexcept;
    [[nodiscard]] float length() const noexcept;
    [[nodiscard]] float lengthSquare() const noexcept;
    [[nodiscard]] Vec3f normalize() const;
    [[nodiscard]] Vec3f min(const Vec3f& v) const noexcept;
    [[nodiscard]] Vec3f max(const Vec3f& v) const noexcept;
    [[nodiscard]] float minComponent() const noexcept;
    [[nodiscard]] float maxComponent() const noexcept;
    [[nodiscard]] float dot(const Vec3f& v) const noexcept;
    [[nodiscard]] Vec3f cross(const Vec3f& v) const noexcept;
    [[nodiscard]] float distance(const Vec3f& v) const noexcept;
    [[nodiscard]] Vec3f rotate(const Vec3f& axis, float angle) const noexcept;
    [[nodiscard]] Vec3f reflect(const Vec3f& normal) const noexcept;
    [[nodiscard]] Vec3f refract(const Vec3f& normal, float mu) const noexcept;
    [[nodiscard]] Vec3f project(const Vec3f& v) const noexcept;
    [[nodiscard]] Vec3f reject(const Vec3f& v) const noexcept;
    void decomposeVec(const Vec3f& v, Vec3f& proj, Vec3f& perp) const noexcept;
    [[nodiscard]] Vec3f perpendicular(const Vec3f& v) const noexcept;

   public:
    [[nodiscard]] bool areSame(const Vec3f& v, float eps = kFloatEpsilon) const noexcept;
    [[nodiscard]] bool areAligned(const Vec3f& v, float eps = kFloatEpsilon) const noexcept;
    [[nodiscard]] bool isZero(float eps = kFloatEpsilon) const noexcept;
    [[nodiscard]] bool isNormalized(float eps = kFloatEpsilon) const noexcept;
    [[nodiscard]] bool isLinearDependent(const Vec3f& p1, const Vec3f& p2, float eps = kFloatEpsilon) const noexcept;
    [[nodiscard]] bool isLinearDependent(const Vec3f& v, float eps = kFloatEpsilon) const noexcept;

   public:
    Vec3f& composeSpherical(float rho, float theta, float phi) noexcept;
    void decomposeSpherical(float& rho, float& theta, float& phi) const noexcept;
    Vec3f& composeCylindrical(float radius, float angle, float height) noexcept;
    void decomposeCylindrical(float& radius, float& angle, float& height) const noexcept;
    [[nodiscard]] float angle(const Vec3f& v) const noexcept;
    [[nodiscard]] float angle(const Vec3f& p1, const Vec3f& p2) const noexcept;

   public:
    [[nodiscard]] Vec3f midPoint(const Vec3f& point) const noexcept;
    [[nodiscard]] Vec3f lerp(Vec3f& point, float factor) const noexcept;

   public:
    Vec3f& operator=(const Vec3f& v) noexcept;
    Vec3f& operator+=(float scalar) noexcept;
    Vec3f& operator-=(float scalar) noexcept;
    Vec3f& operator*=(float scalar) noexcept;
    Vec3f& operator/=(float scalar) noexcept;
    Vec3f& operator+=(const Vec3f& v) noexcept;
    Vec3f& operator-=(const Vec3f& v) noexcept;
    Vec3f& operator*=(const Vec3f& v) noexcept;
    Vec3f& operator/=(const Vec3f& v) noexcept;
    [[nodiscard]] Vec3f operator+(float scalar) const noexcept;
    [[nodiscard]] Vec3f operator-(float scalar) const noexcept;
    [[nodiscard]] Vec3f operator*(float scalar) const noexcept;
    [[nodiscard]] Vec3f operator/(float scalar) const noexcept;
    [[nodiscard]] Vec3f operator+(const Vec3f& v) const noexcept;
    [[nodiscard]] Vec3f operator-(const Vec3f& v) const noexcept;
    [[nodiscard]] Vec3f operator*(const Vec3f& v) const noexcept;
    [[nodiscard]] Vec3f operator/(const Vec3f& v) const noexcept;
    [[nodiscard]] bool operator==(const Vec3f& v) const noexcept;
    [[nodiscard]] bool operator!=(const Vec3f& v) const noexcept;
    [[nodiscard]] bool operator>(const Vec3f& v) const noexcept;
    [[nodiscard]] bool operator<(const Vec3f& v) const noexcept;
    [[nodiscard]] Vec3f operator-() const noexcept;
    [[nodiscard]] float& operator[](uint32_t index) noexcept;
    [[nodiscard]] float operator[](uint32_t index) const noexcept;

   public:
    friend std::ostream& operator<<(std::ostream& os, const Vec3f& vec);
    friend std::istream& operator>>(std::istream& is, Vec3f& vec);

   public:
    [[nodiscard]] static uint32_t dim() noexcept;
    [[nodiscard]] static uint32_t size() noexcept;
    [[nodiscard]] static Vec3f zero() noexcept;
    [[nodiscard]] static Vec3f one() noexcept;
    [[nodiscard]] static Vec3f xAxis() noexcept;
    [[nodiscard]] static Vec3f yAxis() noexcept;
    [[nodiscard]] static Vec3f zAxis() noexcept;
    [[nodiscard]] static Vec3f up() noexcept;
    [[nodiscard]] static Vec3f down() noexcept;
    [[nodiscard]] static Vec3f left() noexcept;
    [[nodiscard]] static Vec3f right() noexcept;
    [[nodiscard]] static Vec3f forward() noexcept;
    [[nodiscard]] static Vec3f backward() noexcept;
    [[nodiscard]] static Vec3f normalized(const Vec3f& v);
    [[nodiscard]] static float distance(const Vec3f& v1, const Vec3f& v2) noexcept;
    [[nodiscard]] static float dot(const Vec3f& v1, const Vec3f& v2) noexcept;
    [[nodiscard]] static Vec3f cross(const Vec3f& v1, const Vec3f& v2) noexcept;
    [[nodiscard]] static Vec3f midPoint(const Vec3f& p1, const Vec3f& p2) noexcept;
    [[nodiscard]] static Vec3f lerp(const Vec3f& p1, const Vec3f& p2, float factor) noexcept;
};

// Legacy type alias for backward compatibility
using Vec3f_C = Vec3f;

}  // namespace vne::math

// Legacy namespace aliases
namespace VNE {
namespace Math {
using Vec3f_C = vne::math::Vec3f;
using Vec3f = vne::math::Vec3f;
}  // namespace Math
}  // namespace VNE

namespace {

inline bool operator==(const vne::math::Vec3f& a, const glm::vec3& b) {
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

inline bool operator==(const glm::vec3& a, const vne::math::Vec3f& b) {
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

}  // namespace

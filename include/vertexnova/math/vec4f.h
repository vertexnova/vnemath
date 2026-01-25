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
 * @file vec4f.h
 * @brief Represents a four-dimensional vector.
 */

// Project includes
#include "vec3f.h"

// Third-party library includes
#include <glm/vec4.hpp>

// Standard library includes
#include <ostream>

namespace vne::math {

class Vec4f : public glm::vec4 {
   public:
    Vec4f() noexcept
        : glm::vec4(0.0f) {}
    Vec4f(float x_value, float y_value, float z_value, float w_value) noexcept
        : glm::vec4(x_value, y_value, z_value, w_value) {}
    Vec4f(float xyzw) noexcept
        : glm::vec4(xyzw) {}
    Vec4f(const Vec4f& v) noexcept
        : glm::vec4(v) {}
    Vec4f(const glm::vec4& v) noexcept
        : glm::vec4(v.x, v.y, v.z, v.w) {}
    Vec4f(const Vec3f& v) noexcept
        : glm::vec4(v.x, v.y, v.z, 0.0f) {}
    Vec4f(const glm::vec3& v) noexcept
        : glm::vec4(v.x, v.y, v.z, 0.0f) {}
    Vec4f(const Vec2f& v) noexcept
        : glm::vec4(v.x, v.y, 0.0f, 0.0f) {}
    Vec4f(const glm::vec2& v) noexcept
        : glm::vec4(v.x, v.y, 0.0f, 0.0f) {}
    Vec4f(const Vec3f& v, float w_value) noexcept
        : glm::vec4(v, w_value) {}
    Vec4f(const glm::vec3& v, float w_value) noexcept
        : glm::vec4(v, w_value) {}

    [[nodiscard]] Vec3f xyz() noexcept;
    [[nodiscard]] Vec2f xy() noexcept;

   public:
    [[nodiscard]] float* getPtr() noexcept;
    [[nodiscard]] const float* getPtr() const noexcept;

   public:
    [[nodiscard]] Vec4f abs() const noexcept;
    [[nodiscard]] float length() const noexcept;
    [[nodiscard]] float lengthSquare() const noexcept;
    [[nodiscard]] Vec4f normalize() const;
    [[nodiscard]] Vec4f min(const Vec4f& v) const noexcept;
    [[nodiscard]] Vec4f max(const Vec4f& v) const noexcept;
    [[nodiscard]] float minComponent() const noexcept;
    [[nodiscard]] float maxComponent() const noexcept;
    [[nodiscard]] float dot(const Vec4f& v) const noexcept;
    [[nodiscard]] float distance(const Vec4f& v) const noexcept;
    [[nodiscard]] Vec4f rotate(const Vec3f& axis, float angle) const noexcept;
    [[nodiscard]] Vec4f reflect(const Vec4f& normal) const noexcept;
    [[nodiscard]] Vec4f refract(const Vec4f& normal, float mu) const noexcept;
    [[nodiscard]] Vec4f project(const Vec4f& v) const noexcept;
    [[nodiscard]] Vec4f reject(const Vec4f& v) const noexcept;
    void decomposeVec(const Vec4f& v, Vec4f& proj, Vec4f& perp) const noexcept;

   public:
    [[nodiscard]] bool areSame(const Vec4f& v, float eps = kFloatEpsilon) const noexcept;
    [[nodiscard]] bool areAligned(const Vec4f& v, float eps = kFloatEpsilon) const noexcept;
    [[nodiscard]] bool isZero(float eps = kFloatEpsilon) const noexcept;
    [[nodiscard]] bool isNormalized(float eps = kFloatEpsilon) const noexcept;

   public:
    [[nodiscard]] float angle(const Vec4f& v) const noexcept;
    [[nodiscard]] float angle(const Vec4f& p1, const Vec4f& p2) const noexcept;

   public:
    [[nodiscard]] Vec4f midPoint(const Vec4f& point) const noexcept;
    [[nodiscard]] Vec4f lerp(const Vec4f& point, float factor) const noexcept;

   public:
    Vec4f& operator=(const Vec4f& v) noexcept;
    Vec4f& operator+=(float scalar) noexcept;
    Vec4f& operator-=(float scalar) noexcept;
    Vec4f& operator*=(float scalar) noexcept;
    Vec4f& operator/=(float scalar) noexcept;
    Vec4f& operator+=(const Vec4f& v) noexcept;
    Vec4f& operator-=(const Vec4f& v) noexcept;
    Vec4f& operator*=(const Vec4f& v) noexcept;
    Vec4f& operator/=(const Vec4f& v) noexcept;
    [[nodiscard]] Vec4f operator+(float scalar) const noexcept;
    [[nodiscard]] Vec4f operator-(float scalar) const noexcept;
    [[nodiscard]] Vec4f operator*(float scalar) const noexcept;
    [[nodiscard]] Vec4f operator/(float scalar) const noexcept;
    [[nodiscard]] Vec4f operator+(const Vec4f& v) const noexcept;
    [[nodiscard]] Vec4f operator-(const Vec4f& v) const noexcept;
    [[nodiscard]] Vec4f operator*(const Vec4f& v) const noexcept;
    [[nodiscard]] Vec4f operator/(const Vec4f& v) const noexcept;
    [[nodiscard]] bool operator==(const Vec4f& v) const noexcept;
    [[nodiscard]] bool operator!=(const Vec4f& v) const noexcept;
    [[nodiscard]] bool operator>(const Vec4f& v) const noexcept;
    [[nodiscard]] bool operator<(const Vec4f& v) const noexcept;
    [[nodiscard]] Vec4f operator-() const noexcept;
    [[nodiscard]] float& operator[](uint32_t index) noexcept;
    [[nodiscard]] float operator[](uint32_t index) const noexcept;

   public:
    friend std::ostream& operator<<(std::ostream& os, const Vec4f& vec);
    friend std::istream& operator>>(std::istream& is, Vec4f& vec);

   public:
    [[nodiscard]] static uint32_t dim() noexcept;
    [[nodiscard]] static uint32_t size() noexcept;
    [[nodiscard]] static Vec4f zero() noexcept;
    [[nodiscard]] static Vec4f one() noexcept;
    [[nodiscard]] static Vec4f xAxis() noexcept;
    [[nodiscard]] static Vec4f yAxis() noexcept;
    [[nodiscard]] static Vec4f zAxis() noexcept;
    [[nodiscard]] static Vec4f wAxis() noexcept;
    [[nodiscard]] static Vec4f normalized(const Vec4f& v);
    [[nodiscard]] static float distance(const Vec4f& v1, const Vec4f& v2) noexcept;
    [[nodiscard]] static float dot(const Vec4f& v1, const Vec4f& v2) noexcept;
    [[nodiscard]] static Vec4f midPoint(const Vec4f& p1, const Vec4f& p2) noexcept;
    [[nodiscard]] static Vec4f lerp(const Vec4f& p1, const Vec4f& p2, float t) noexcept;
};

}  // namespace vne::math

namespace {

[[nodiscard]] inline bool operator==(const vne::math::Vec4f& a, const glm::vec4& b) noexcept {
    return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
}

[[nodiscard]] inline bool operator==(const glm::vec4& a, const vne::math::Vec4f& b) noexcept {
    return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
}

}  // namespace

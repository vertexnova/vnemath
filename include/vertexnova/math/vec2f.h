#pragma once
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

/**
 * @file vec2f.h
 * @brief Defines the Vec2f class for representing a two-dimensional vector
 *        with various mathematical operations.
 */

// Project includes
#include "constants.h"

// Third-party library includes
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/vec2.hpp>

// System library includes
#include <ostream>

namespace vne::math {

/**
 * @class Vec2f
 * @brief Represents a two-dimensional vector with float components.
 */
class Vec2f : public glm::vec2 {
   public:
    Vec2f() noexcept
        : glm::vec2(0.0f, 0.0f) {}
    Vec2f(float x_value, float y_value) noexcept
        : glm::vec2(x_value, y_value) {}
    Vec2f(const float xy) noexcept
        : glm::vec2(xy, xy) {}
    Vec2f(const Vec2f& v) noexcept
        : glm::vec2(v) {}
    Vec2f(const glm::vec2& v) noexcept
        : glm::vec2(v.x, v.y) {}

   public:
    [[nodiscard]] float* getPtr() noexcept;
    [[nodiscard]] const float* getPtr() const noexcept;

   public:
    [[nodiscard]] Vec2f abs() const noexcept;
    [[nodiscard]] float length() const noexcept;
    [[nodiscard]] float lengthSquare() const noexcept;
    [[nodiscard]] Vec2f normalize() const;
    [[nodiscard]] Vec2f min(const Vec2f& v) const noexcept;
    [[nodiscard]] Vec2f max(const Vec2f& v) const noexcept;
    [[nodiscard]] float minComponent() const noexcept;
    [[nodiscard]] float maxComponent() const noexcept;
    [[nodiscard]] float dot(const Vec2f& v) const noexcept;
    [[nodiscard]] float cross(const Vec2f& v) const noexcept;
    [[nodiscard]] float distance(const Vec2f& v) const noexcept;
    [[nodiscard]] Vec2f rotate(const Vec2f& axis, float angle) const noexcept;
    [[nodiscard]] Vec2f reflect(const Vec2f& normal) const noexcept;
    [[nodiscard]] Vec2f refract(const Vec2f& normal, float mu) const noexcept;
    [[nodiscard]] Vec2f project(const Vec2f& v) const noexcept;
    [[nodiscard]] Vec2f reject(const Vec2f& v) const noexcept;
    void decomposeVec(const Vec2f& v, Vec2f& proj, Vec2f& perp) const noexcept;
    [[nodiscard]] Vec2f perpendicular() const noexcept;

   public:
    [[nodiscard]] bool areSame(const Vec2f& v, float eps = kFloatEpsilon) const noexcept;
    [[nodiscard]] bool areAligned(const Vec2f& v, float eps = kFloatEpsilon) const noexcept;
    [[nodiscard]] bool isZero(float eps = kFloatEpsilon) const noexcept;
    [[nodiscard]] bool isNormalized(float eps = kFloatEpsilon) const noexcept;

   public:
    Vec2f& composePolar(float radius, float angle) noexcept;
    void decomposePolar(float& radius, float& angle) const noexcept;
    [[nodiscard]] float angle() const noexcept;
    [[nodiscard]] float angle(const Vec2f& v) const noexcept;
    [[nodiscard]] float angle(const Vec2f& p1, const Vec2f& p2) const noexcept;

   public:
    [[nodiscard]] Vec2f midPoint(const Vec2f& point) const noexcept;
    [[nodiscard]] Vec2f lerp(Vec2f& point, float factor) const noexcept;

   public:
    Vec2f& operator=(const Vec2f& v) noexcept;
    Vec2f& operator+=(const float& scalar) noexcept;
    Vec2f& operator-=(const float& scalar) noexcept;
    Vec2f& operator*=(const float& scalar) noexcept;
    Vec2f& operator/=(const float& scalar) noexcept;
    Vec2f& operator+=(const Vec2f& v) noexcept;
    Vec2f& operator-=(const Vec2f& v) noexcept;
    Vec2f& operator*=(const Vec2f& v) noexcept;
    Vec2f& operator/=(const Vec2f& v) noexcept;
    [[nodiscard]] Vec2f operator+(const float& scalar) const noexcept;
    [[nodiscard]] Vec2f operator-(const float& scalar) const noexcept;
    [[nodiscard]] Vec2f operator*(const float& scalar) const noexcept;
    [[nodiscard]] Vec2f operator/(const float& scalar) const noexcept;
    [[nodiscard]] Vec2f operator+(const Vec2f& v) const noexcept;
    [[nodiscard]] Vec2f operator-(const Vec2f& v) const noexcept;
    [[nodiscard]] Vec2f operator*(const Vec2f& v) const noexcept;
    [[nodiscard]] Vec2f operator/(const Vec2f& v) const noexcept;
    [[nodiscard]] bool operator==(const Vec2f& v) const noexcept;
    [[nodiscard]] bool operator!=(const Vec2f& v) const noexcept;
    [[nodiscard]] bool operator>(const Vec2f& v) const noexcept;
    [[nodiscard]] bool operator<(const Vec2f& v) const noexcept;
    [[nodiscard]] Vec2f operator-() const noexcept;
    [[nodiscard]] float& operator[](uint32_t index) noexcept;
    [[nodiscard]] float operator[](uint32_t index) const noexcept;

   public:
    friend std::ostream& operator<<(std::ostream& os, const Vec2f& vec);
    friend std::istream& operator>>(std::istream& is, Vec2f& vec);

   public:
    [[nodiscard]] static uint32_t dim() noexcept;
    [[nodiscard]] static uint32_t size() noexcept;
    [[nodiscard]] static Vec2f zero() noexcept;
    [[nodiscard]] static Vec2f one() noexcept;
    [[nodiscard]] static Vec2f xAxis() noexcept;
    [[nodiscard]] static Vec2f yAxis() noexcept;
    [[nodiscard]] static Vec2f normalized(const Vec2f& v);
    [[nodiscard]] static float distance(const Vec2f& v1, const Vec2f& v2) noexcept;
    [[nodiscard]] static float dot(const Vec2f& v1, const Vec2f& v2) noexcept;
    [[nodiscard]] static float cross(const Vec2f& v1, const Vec2f& v2) noexcept;
    [[nodiscard]] static Vec2f midPoint(const Vec2f& p1, const Vec2f& p2) noexcept;
    [[nodiscard]] static Vec2f lerp(const Vec2f& p1, const Vec2f& p2, float factor) noexcept;
};

}  // namespace vne::math

namespace {

[[nodiscard]] inline bool operator==(const vne::math::Vec2f& a, const glm::vec2& b) noexcept {
    return a.x == b.x && a.y == b.y;
}

[[nodiscard]] inline bool operator==(const glm::vec2& a, const vne::math::Vec2f& b) noexcept {
    return a.x == b.x && a.y == b.y;
}

}  // namespace

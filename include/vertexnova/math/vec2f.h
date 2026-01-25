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
    Vec2f()
        : glm::vec2(0.0f, 0.0f) {}
    Vec2f(float x_value, float y_value)
        : glm::vec2(x_value, y_value) {}
    Vec2f(const float xy)
        : glm::vec2(xy, xy) {}
    Vec2f(const Vec2f& v)
        : glm::vec2(v) {}
    Vec2f(const glm::vec2& v)
        : glm::vec2(v.x, v.y) {}

   public:
    float* getPtr();
    const float* getPtr() const;

   public:
    Vec2f abs() const;
    float length() const;
    float lengthSquare() const;
    Vec2f normalize() const;
    Vec2f min(const Vec2f& v) const;
    Vec2f max(const Vec2f& v) const;
    float minComponent() const;
    float maxComponent() const;
    float dot(const Vec2f& v) const;
    float cross(const Vec2f& v) const;
    float distance(const Vec2f& v) const;
    Vec2f rotate(const Vec2f& axis, float angle) const;
    Vec2f reflect(const Vec2f& normal) const;
    Vec2f refract(const Vec2f& normal, float mu) const;
    Vec2f project(const Vec2f& v) const;
    Vec2f reject(const Vec2f& v) const;
    void decomposeVec(const Vec2f& v, Vec2f& proj, Vec2f& perp) const;
    Vec2f perpendicular() const;

   public:
    bool areSame(const Vec2f& v, float eps = kFloatEpsilon) const;
    bool areAligned(const Vec2f& v, float eps = kFloatEpsilon) const;
    bool isZero(float eps = kFloatEpsilon) const;
    bool isNormalized(float eps = kFloatEpsilon) const;

   public:
    Vec2f& composePolar(float radius, float angle);
    void decomposePolar(float& radius, float& angle) const;
    float angle() const;
    float angle(const Vec2f& v) const;
    float angle(const Vec2f& p1, const Vec2f& p2) const;

   public:
    Vec2f midPoint(const Vec2f& point) const;
    Vec2f lerp(Vec2f& point, float factor) const;

   public:
    Vec2f& operator=(const Vec2f& v);
    Vec2f& operator+=(const float& scalar);
    Vec2f& operator-=(const float& scalar);
    Vec2f& operator*=(const float& scalar);
    Vec2f& operator/=(const float& scalar);
    Vec2f& operator+=(const Vec2f& v);
    Vec2f& operator-=(const Vec2f& v);
    Vec2f& operator*=(const Vec2f& v);
    Vec2f& operator/=(const Vec2f& v);
    Vec2f operator+(const float& scalar) const;
    Vec2f operator-(const float& scalar) const;
    Vec2f operator*(const float& scalar) const;
    Vec2f operator/(const float& scalar) const;
    Vec2f operator+(const Vec2f& v) const;
    Vec2f operator-(const Vec2f& v) const;
    Vec2f operator*(const Vec2f& v) const;
    Vec2f operator/(const Vec2f& v) const;
    bool operator==(const Vec2f& v) const;
    bool operator!=(const Vec2f& v) const;
    bool operator>(const Vec2f& v) const;
    bool operator<(const Vec2f& v) const;
    Vec2f operator-() const;
    float& operator[](uint32_t index);
    float operator[](uint32_t index) const;

   public:
    friend std::ostream& operator<<(std::ostream& os, const Vec2f& vec);
    friend std::istream& operator>>(std::istream& is, Vec2f& vec);

   public:
    static uint32_t dim();
    static uint32_t size();
    static Vec2f zero();
    static Vec2f one();
    static Vec2f xAxis();
    static Vec2f yAxis();
    static Vec2f normalized(const Vec2f& v);
    static float distance(const Vec2f& v1, const Vec2f& v2);
    static float dot(const Vec2f& v1, const Vec2f& v2);
    static float cross(const Vec2f& v1, const Vec2f& v2);
    static Vec2f midPoint(const Vec2f& p1, const Vec2f& p2);
    static Vec2f lerp(const Vec2f& p1, const Vec2f& p2, float factor);
};

}  // namespace vne::math

namespace {

inline bool operator==(const vne::math::Vec2f& a, const glm::vec2& b) {
    return a.x == b.x && a.y == b.y;
}

inline bool operator==(const glm::vec2& a, const vne::math::Vec2f& b) {
    return a.x == b.x && a.y == b.y;
}

}  // namespace

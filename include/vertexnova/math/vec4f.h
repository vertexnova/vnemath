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
    Vec4f() : glm::vec4(0.0f) {}
    Vec4f(float x_value, float y_value, float z_value, float w_value)
        : glm::vec4(x_value, y_value, z_value, w_value) {}
    Vec4f(float xyzw) : glm::vec4(xyzw) {}
    Vec4f(const Vec4f& v) : glm::vec4(v) {}
    Vec4f(const glm::vec4& v) : glm::vec4(v.x, v.y, v.z, v.w) {}
    Vec4f(const Vec3f& v) : glm::vec4(v.x, v.y, v.z, 0.0f) {}
    Vec4f(const glm::vec3& v) : glm::vec4(v.x, v.y, v.z, 0.0f) {}
    Vec4f(const Vec2f& v) : glm::vec4(v.x, v.y, 0.0f, 0.0f) {}
    Vec4f(const glm::vec2& v) : glm::vec4(v.x, v.y, 0.0f, 0.0f) {}
    Vec4f(const Vec3f& v, float w_value) : glm::vec4(v, w_value) {}
    Vec4f(const glm::vec3& v, float w_value) : glm::vec4(v, w_value) {}

    Vec3f xyz();
    Vec2f xy();

   public:
    float* getPtr();
    const float* getPtr() const;

   public:
    Vec4f abs() const;
    float length() const;
    float lengthSquare() const;
    Vec4f normalize() const;
    Vec4f min(const Vec4f& v) const;
    Vec4f max(const Vec4f& v) const;
    float minComponent() const;
    float maxComponent() const;
    float dot(const Vec4f& v) const;
    float distance(const Vec4f& v) const;
    Vec4f rotate(const Vec3f& axis, float angle) const;
    Vec4f reflect(const Vec4f& normal) const;
    Vec4f refract(const Vec4f& normal, float mu) const;
    Vec4f project(const Vec4f& v) const;
    Vec4f reject(const Vec4f& v) const;
    void decomposeVec(const Vec4f& v, Vec4f& proj, Vec4f& perp) const;

   public:
    bool areSame(const Vec4f& v, float eps = kFloatEpsilon) const;
    bool areAligned(const Vec4f& v, float eps = kFloatEpsilon) const;
    bool isZero(float eps = kFloatEpsilon) const;
    bool isNormalized(float eps = kFloatEpsilon) const;

   public:
    float angle(const Vec4f& v) const;
    float angle(const Vec4f& p1, const Vec4f& p2) const;

   public:
    Vec4f midPoint(const Vec4f& point) const;
    Vec4f lerp(const Vec4f& point, float factor) const;

   public:
    Vec4f& operator=(const Vec4f& v);
    Vec4f& operator+=(float scalar);
    Vec4f& operator-=(float scalar);
    Vec4f& operator*=(float scalar);
    Vec4f& operator/=(float scalar);
    Vec4f& operator+=(const Vec4f& v);
    Vec4f& operator-=(const Vec4f& v);
    Vec4f& operator*=(const Vec4f& v);
    Vec4f& operator/=(const Vec4f& v);
    Vec4f operator+(float scalar) const;
    Vec4f operator-(float scalar) const;
    Vec4f operator*(float scalar) const;
    Vec4f operator/(float scalar) const;
    Vec4f operator+(const Vec4f& v) const;
    Vec4f operator-(const Vec4f& v) const;
    Vec4f operator*(const Vec4f& v) const;
    Vec4f operator/(const Vec4f& v) const;
    bool operator==(const Vec4f& v) const;
    bool operator!=(const Vec4f& v) const;
    bool operator>(const Vec4f& v) const;
    bool operator<(const Vec4f& v) const;
    Vec4f operator-() const;
    float& operator[](uint32_t index);
    float operator[](uint32_t index) const;

   public:
    friend std::ostream& operator<<(std::ostream& os, const Vec4f& vec);
    friend std::istream& operator>>(std::istream& is, Vec4f& vec);

   public:
    static uint32_t dim();
    static uint32_t size();
    static Vec4f zero();
    static Vec4f one();
    static Vec4f xAxis();
    static Vec4f yAxis();
    static Vec4f zAxis();
    static Vec4f wAxis();
    static Vec4f normalized(const Vec4f& v);
    static float distance(const Vec4f& v1, const Vec4f& v2);
    static float dot(const Vec4f& v1, const Vec4f& v2);
    static Vec4f midPoint(const Vec4f& p1, const Vec4f& p2);
    static Vec4f lerp(const Vec4f& p1, const Vec4f& p2, float t);
};

// Legacy type alias for backward compatibility
using Vec4f_C = Vec4f;

}  // namespace vne::math

// Legacy namespace aliases
namespace VNE {
namespace Math {
using Vec4f_C = vne::math::Vec4f;
using Vec4f = vne::math::Vec4f;
}  // namespace Math
}  // namespace VNE

namespace {

inline bool operator==(const vne::math::Vec4f& a, const glm::vec4& b) {
    return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
}

inline bool operator==(const glm::vec4& a, const vne::math::Vec4f& b) {
    return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
}

}  // namespace

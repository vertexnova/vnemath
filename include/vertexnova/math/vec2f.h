#ifndef VNE_MATH_VEC2F_H
#define VNE_MATH_VEC2F_H

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
 * @brief Defines the Vec2f_C class for representing a two-dimensional vector
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

namespace VNE {
namespace Math {

/**
 * @class Vec2f_C
 * @brief Represents a two-dimensional vector with float components.
 */
class Vec2f_C : public glm::vec2 {
   public:
    Vec2f_C() : glm::vec2(0.0f, 0.0f) {}
    Vec2f_C(float x_value, float y_value) : glm::vec2(x_value, y_value) {}
    Vec2f_C(const float xy) : glm::vec2(xy, xy) {}
    Vec2f_C(const Vec2f_C& v) : glm::vec2(v) {}
    Vec2f_C(const glm::vec2& v) : glm::vec2(v.x, v.y) {}

   public:
    float* GetPtr();
    const float* GetPtr() const;

   public:
    Vec2f_C Abs() const;
    float Length() const;
    float LengthSquare() const;
    Vec2f_C Normalize() const;
    Vec2f_C Min(const Vec2f_C& v) const;
    Vec2f_C Max(const Vec2f_C& v) const;
    float MinComponent() const;
    float MaxComponent() const;
    float Dot(const Vec2f_C& v) const;
    float Cross(const Vec2f_C& v) const;
    float Distance(const Vec2f_C& v) const;
    Vec2f_C Rotate(const Vec2f_C& axis, float angle) const;
    Vec2f_C Reflect(const Vec2f_C& normal) const;
    Vec2f_C Refract(const Vec2f_C& normal, float mu) const;
    Vec2f_C Project(const Vec2f_C& v) const;
    Vec2f_C Reject(const Vec2f_C& v) const;
    void DecomposeVec(const Vec2f_C& v, Vec2f_C& proj, Vec2f_C& perp) const;
    Vec2f_C Perpendicular() const;

   public:
    bool AreSame(const Vec2f_C& v, float eps = Math::FLOAT_EPSILON) const;
    bool AreAligned(const Vec2f_C& v, float eps = Math::FLOAT_EPSILON) const;
    bool IsZero(float eps = Math::FLOAT_EPSILON) const;
    bool IsNormalized(float eps = Math::FLOAT_EPSILON) const;

   public:
    Vec2f_C& ComposePolar(float radius, float angle);
    void DecomposePolar(float& radius, float& angle) const;
    float Angle() const;
    float Angle(const Vec2f_C& v) const;
    float Angle(const Vec2f_C& p1, const Vec2f_C& p2) const;

   public:
    Vec2f_C MidPoint(const Vec2f_C& point) const;
    Vec2f_C Lerp(Vec2f_C& point, float factor) const;

   public:
    Vec2f_C& operator=(const Vec2f_C& v);
    Vec2f_C& operator+=(const float& scalar);
    Vec2f_C& operator-=(const float& scalar);
    Vec2f_C& operator*=(const float& scalar);
    Vec2f_C& operator/=(const float& scalar);
    Vec2f_C& operator+=(const Vec2f_C& v);
    Vec2f_C& operator-=(const Vec2f_C& v);
    Vec2f_C& operator*=(const Vec2f_C& v);
    Vec2f_C& operator/=(const Vec2f_C& v);
    Vec2f_C operator+(const float& scalar) const;
    Vec2f_C operator-(const float& scalar) const;
    Vec2f_C operator*(const float& scalar) const;
    Vec2f_C operator/(const float& scalar) const;
    Vec2f_C operator+(const Vec2f_C& v) const;
    Vec2f_C operator-(const Vec2f_C& v) const;
    Vec2f_C operator*(const Vec2f_C& v) const;
    Vec2f_C operator/(const Vec2f_C& v) const;
    bool operator==(const Vec2f_C& v) const;
    bool operator!=(const Vec2f_C& v) const;
    bool operator>(const Vec2f_C& v) const;
    bool operator<(const Vec2f_C& v) const;
    Vec2f_C operator-() const;
    float& operator[](uint32_t index);
    float operator[](uint32_t index) const;

   public:
    friend std::ostream& operator<<(std::ostream& os, const Vec2f_C& vec);
    friend std::istream& operator>>(std::istream& is, Vec2f_C& vec);

   public:
    static uint32_t Dim();
    static uint32_t Size();
    static Vec2f_C Zero();
    static Vec2f_C One();
    static Vec2f_C XAxis();
    static Vec2f_C YAxis();
    static Vec2f_C Normalized(const Vec2f_C& v);
    static float Distance(const Vec2f_C& v1, const Vec2f_C& v2);
    static float Dot(const Vec2f_C& v1, const Vec2f_C& v2);
    static float Cross(const Vec2f_C& v1, const Vec2f_C& v2);
    static Vec2f_C MidPoint(const Vec2f_C& p1, const Vec2f_C& p2);
    static Vec2f_C Lerp(const Vec2f_C& p1, const Vec2f_C& p2, float factor);
};

}  // namespace Math
}  // namespace VNE

namespace {

inline bool operator==(const VNE::Math::Vec2f_C& a, const glm::vec2& b) {
    return a.x == b.x && a.y == b.y;
}

inline bool operator==(const glm::vec2& a, const VNE::Math::Vec2f_C& b) {
    return a.x == b.x && a.y == b.y;
}

}  // namespace

#endif  // VNE_MATH_VEC2F_H

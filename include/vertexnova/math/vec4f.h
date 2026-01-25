#ifndef VNE_MATH_VEC4F_H
#define VNE_MATH_VEC4F_H
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

namespace VNE {
namespace Math {

class Vec4f_C : public glm::vec4 {
   public:
    Vec4f_C() : glm::vec4(0.0f) {}
    Vec4f_C(float x_value, float y_value, float z_value, float w_value)
        : glm::vec4(x_value, y_value, z_value, w_value) {}
    Vec4f_C(float xyzw) : glm::vec4(xyzw) {}
    Vec4f_C(const Vec4f_C& v) : glm::vec4(v) {}
    Vec4f_C(const glm::vec4& v) : glm::vec4(v.x, v.y, v.z, v.w) {}
    Vec4f_C(const Vec3f_C& v) : glm::vec4(v.x, v.y, v.z, 0.0f) {}
    Vec4f_C(const glm::vec3& v) : glm::vec4(v.x, v.y, v.z, 0.0f) {}
    Vec4f_C(const Vec2f_C& v) : glm::vec4(v.x, v.y, 0.0f, 0.0f) {}
    Vec4f_C(const glm::vec2& v) : glm::vec4(v.x, v.y, 0.0f, 0.0f) {}
    Vec4f_C(const Vec3f_C& v, float w_value) : glm::vec4(v, w_value) {}
    Vec4f_C(const glm::vec3& v, float w_value) : glm::vec4(v, w_value) {}

    Vec3f_C XYZ();
    Vec2f_C XY();

   public:
    float* GetPtr();
    const float* GetPtr() const;

   public:
    Vec4f_C Abs() const;
    float Length() const;
    float LengthSquare() const;
    Vec4f_C Normalize() const;
    Vec4f_C Min(const Vec4f_C& v) const;
    Vec4f_C Max(const Vec4f_C& v) const;
    float MinComponent() const;
    float MaxComponent() const;
    float Dot(const Vec4f_C& v) const;
    float Distance(const Vec4f_C& v) const;
    Vec4f_C Rotate(const Vec3f_C& axis, float angle) const;
    Vec4f_C Reflect(const Vec4f_C& normal) const;
    Vec4f_C Refract(const Vec4f_C& normal, float mu) const;
    Vec4f_C Project(const Vec4f_C& v) const;
    Vec4f_C Reject(const Vec4f_C& v) const;
    void DecomposeVec(const Vec4f_C& v, Vec4f_C& proj, Vec4f_C& perp) const;

   public:
    bool AreSame(const Vec4f_C& v, float eps = Math::FLOAT_EPSILON) const;
    bool AreAligned(const Vec4f_C& v, float eps = Math::FLOAT_EPSILON) const;
    bool IsZero(float eps = Math::FLOAT_EPSILON) const;
    bool IsNormalized(float eps = Math::FLOAT_EPSILON) const;

   public:
    float Angle(const Vec4f_C& v) const;
    float Angle(const Vec4f_C& p1, const Vec4f_C& p2) const;

   public:
    Vec4f_C MidPoint(const Vec4f_C& point) const;
    Vec4f_C Lerp(const Vec4f_C& point, float factor) const;

   public:
    Vec4f_C& operator=(const Vec4f_C& v);
    Vec4f_C& operator+=(float scalar);
    Vec4f_C& operator-=(float scalar);
    Vec4f_C& operator*=(float scalar);
    Vec4f_C& operator/=(float scalar);
    Vec4f_C& operator+=(const Vec4f_C& v);
    Vec4f_C& operator-=(const Vec4f_C& v);
    Vec4f_C& operator*=(const Vec4f_C& v);
    Vec4f_C& operator/=(const Vec4f_C& v);
    Vec4f_C operator+(float scalar) const;
    Vec4f_C operator-(float scalar) const;
    Vec4f_C operator*(float scalar) const;
    Vec4f_C operator/(float scalar) const;
    Vec4f_C operator+(const Vec4f_C& v) const;
    Vec4f_C operator-(const Vec4f_C& v) const;
    Vec4f_C operator*(const Vec4f_C& v) const;
    Vec4f_C operator/(const Vec4f_C& v) const;
    bool operator==(const Vec4f_C& v) const;
    bool operator!=(const Vec4f_C& v) const;
    bool operator>(const Vec4f_C& v) const;
    bool operator<(const Vec4f_C& v) const;
    Vec4f_C operator-() const;
    float& operator[](uint32_t index);
    float operator[](uint32_t index) const;

   public:
    friend std::ostream& operator<<(std::ostream& os, const Vec4f_C& vec);
    friend std::istream& operator>>(std::istream& is, Vec4f_C& vec);

   public:
    static uint32_t Dim();
    static uint32_t Size();
    static Vec4f_C Zero();
    static Vec4f_C One();
    static Vec4f_C XAxis();
    static Vec4f_C YAxis();
    static Vec4f_C ZAxis();
    static Vec4f_C WAxis();
    static Vec4f_C Normalized(const Vec4f_C& v);
    static float Distance(const Vec4f_C& v1, const Vec4f_C& v2);
    static float Dot(const Vec4f_C& v1, const Vec4f_C& v2);
    static Vec4f_C MidPoint(const Vec4f_C& p1, const Vec4f_C& p2);
    static Vec4f_C Lerp(const Vec4f_C& p1, const Vec4f_C& p2, float t);
};

}  // namespace Math
}  // namespace VNE

namespace {

inline bool operator==(const VNE::Math::Vec4f_C& a, const glm::vec4& b) {
    return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
}

inline bool operator==(const glm::vec4& a, const VNE::Math::Vec4f_C& b) {
    return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
}

}  // namespace

#endif  // VNE_MATH_VEC4F_H

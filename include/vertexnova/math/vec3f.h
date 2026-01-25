#ifndef VNE_MATH_VEC3F_H
#define VNE_MATH_VEC3F_H
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
#define GLM_ENABLE_EXPERIMENTAL

// Project includes
#include "vec2f.h"

// Third-party library includes
#include <glm/vec3.hpp>

// Standard library includes
#include <ostream>

namespace VNE {
namespace Math {

class Vec3f_C : public glm::vec3 {
   public:
    Vec3f_C() : glm::vec3(0.0f) {};
    Vec3f_C(float x_value, float y_value, float z_value) : glm::vec3(x_value, y_value, z_value) {};
    Vec3f_C(const float xyz) : glm::vec3(xyz) {};
    Vec3f_C(const Vec3f_C& v) : glm::vec3(v) {};
    Vec3f_C(const glm::vec3& v) : glm::vec3(v.x, v.y, v.z) {};
    Vec3f_C(const Vec2f_C& v) : glm::vec3(v.x, v.y, 0.0f) {};
    Vec3f_C(const glm::vec2& v) : glm::vec3(v.x, v.y, 0.0f) {};
    Vec3f_C(const Vec2f_C& v, float z_value) : glm::vec3(v, z_value) {};
    Vec3f_C(const glm::vec2& v, float z_value) : glm::vec3(v, z_value) {};

    Vec2f_C XY();

   public:
    float* GetPtr();
    const float* GetPtr() const;

   public:
    Vec3f_C Abs() const;
    float Length() const;
    float LengthSquare() const;
    Vec3f_C Normalize() const;
    Vec3f_C Min(const Vec3f_C& v) const;
    Vec3f_C Max(const Vec3f_C& v) const;
    float MinComponent() const;
    float MaxComponent() const;
    float Dot(const Vec3f_C& v) const;
    Vec3f_C Cross(const Vec3f_C& v) const;
    float Distance(const Vec3f_C& v) const;
    Vec3f_C Rotate(const Vec3f_C& axis, float angle) const;
    Vec3f_C Reflect(const Vec3f_C& normal) const;
    Vec3f_C Refract(const Vec3f_C& normal, float mu) const;
    Vec3f_C Project(const Vec3f_C& v) const;
    Vec3f_C Reject(const Vec3f_C& v) const;
    void DecomposeVec(const Vec3f_C& v, Vec3f_C& proj, Vec3f_C& perp) const;
    Vec3f_C Perpendicular(const Vec3f_C& v) const;

   public:
    bool AreSame(const Vec3f_C& v, float eps = Math::FLOAT_EPSILON) const;
    bool AreAligned(const Vec3f_C& v, float eps = Math::FLOAT_EPSILON) const;
    bool IsZero(float eps = Math::FLOAT_EPSILON) const;
    bool IsNormalized(float eps = Math::FLOAT_EPSILON) const;
    bool IsLinearDependent(const Vec3f_C& p1, const Vec3f_C& p2, float eps = Math::FLOAT_EPSILON) const;
    bool IsLinearDependent(const Vec3f_C& v, float eps = Math::FLOAT_EPSILON) const;

   public:
    Vec3f_C& ComposeSpherical(float rho, float theta, float phi);
    void DecomposeSpherical(float& rho, float& theta, float& phi) const;
    Vec3f_C& ComposeCylindrical(float radius, float angle, float height);
    void DecomposeCylindrical(float& radius, float& angle, float& height) const;
    float Angle(const Vec3f_C& v) const;
    float Angle(const Vec3f_C& p1, const Vec3f_C& p2) const;

   public:
    Vec3f_C MidPoint(const Vec3f_C& point) const;
    Vec3f_C Lerp(Vec3f_C& point, float factor) const;

   public:
    Vec3f_C& operator=(const Vec3f_C& v);
    Vec3f_C& operator+=(float scalar);
    Vec3f_C& operator-=(float scalar);
    Vec3f_C& operator*=(float scalar);
    Vec3f_C& operator/=(float scalar);
    Vec3f_C& operator+=(const Vec3f_C& v);
    Vec3f_C& operator-=(const Vec3f_C& v);
    Vec3f_C& operator*=(const Vec3f_C& v);
    Vec3f_C& operator/=(const Vec3f_C& v);
    Vec3f_C operator+(float scalar) const;
    Vec3f_C operator-(float scalar) const;
    Vec3f_C operator*(float scalar) const;
    Vec3f_C operator/(float scalar) const;
    Vec3f_C operator+(const Vec3f_C& v) const;
    Vec3f_C operator-(const Vec3f_C& v) const;
    Vec3f_C operator*(const Vec3f_C& v) const;
    Vec3f_C operator/(const Vec3f_C& v) const;
    bool operator==(const Vec3f_C& v) const;
    bool operator!=(const Vec3f_C& v) const;
    bool operator>(const Vec3f_C& v) const;
    bool operator<(const Vec3f_C& v) const;
    Vec3f_C operator-() const;
    float& operator[](uint32_t index);
    float operator[](uint32_t index) const;

   public:
    friend std::ostream& operator<<(std::ostream& os, const Vec3f_C& vec);
    friend std::istream& operator>>(std::istream& is, Vec3f_C& vec);

   public:
    static uint32_t Dim();
    static uint32_t Size();
    static Vec3f_C Zero();
    static Vec3f_C One();
    static Vec3f_C XAxis();
    static Vec3f_C YAxis();
    static Vec3f_C ZAxis();
    static Vec3f_C Up();
    static Vec3f_C Down();
    static Vec3f_C Left();
    static Vec3f_C Right();
    static Vec3f_C Forward();
    static Vec3f_C Backward();
    static Vec3f_C Normalized(const Vec3f_C& v);
    static float Distance(const Vec3f_C& v1, const Vec3f_C& v2);
    static float Dot(const Vec3f_C& v1, const Vec3f_C& v2);
    static Vec3f_C Cross(const Vec3f_C& v1, const Vec3f_C& v2);
    static Vec3f_C MidPoint(const Vec3f_C& p1, const Vec3f_C& p2);
    static Vec3f_C Lerp(const Vec3f_C& p1, const Vec3f_C& p2, float factor);
};

}  // namespace Math
}  // namespace VNE

namespace {

inline bool operator==(const VNE::Math::Vec3f_C& a, const glm::vec3& b) {
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

inline bool operator==(const glm::vec3& a, const VNE::Math::Vec3f_C& b) {
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

}  // namespace

#endif  // VNE_MATH_VEC3F_H

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
    Vec3f()
        : glm::vec3(0.0f) {};
    Vec3f(float x_value, float y_value, float z_value)
        : glm::vec3(x_value, y_value, z_value) {};
    Vec3f(const float xyz)
        : glm::vec3(xyz) {};
    Vec3f(const Vec3f& v)
        : glm::vec3(v) {};
    Vec3f(const glm::vec3& v)
        : glm::vec3(v.x, v.y, v.z) {};
    Vec3f(const Vec2f& v)
        : glm::vec3(v.x, v.y, 0.0f) {};
    Vec3f(const glm::vec2& v)
        : glm::vec3(v.x, v.y, 0.0f) {};
    Vec3f(const Vec2f& v, float z_value)
        : glm::vec3(v, z_value) {};
    Vec3f(const glm::vec2& v, float z_value)
        : glm::vec3(v, z_value) {};

    Vec2f xy();

   public:
    float* getPtr();
    const float* getPtr() const;

   public:
    Vec3f abs() const;
    float length() const;
    float lengthSquare() const;
    Vec3f normalize() const;
    Vec3f min(const Vec3f& v) const;
    Vec3f max(const Vec3f& v) const;
    float minComponent() const;
    float maxComponent() const;
    float dot(const Vec3f& v) const;
    Vec3f cross(const Vec3f& v) const;
    float distance(const Vec3f& v) const;
    Vec3f rotate(const Vec3f& axis, float angle) const;
    Vec3f reflect(const Vec3f& normal) const;
    Vec3f refract(const Vec3f& normal, float mu) const;
    Vec3f project(const Vec3f& v) const;
    Vec3f reject(const Vec3f& v) const;
    void decomposeVec(const Vec3f& v, Vec3f& proj, Vec3f& perp) const;
    Vec3f perpendicular(const Vec3f& v) const;

   public:
    bool areSame(const Vec3f& v, float eps = kFloatEpsilon) const;
    bool areAligned(const Vec3f& v, float eps = kFloatEpsilon) const;
    bool isZero(float eps = kFloatEpsilon) const;
    bool isNormalized(float eps = kFloatEpsilon) const;
    bool isLinearDependent(const Vec3f& p1, const Vec3f& p2, float eps = kFloatEpsilon) const;
    bool isLinearDependent(const Vec3f& v, float eps = kFloatEpsilon) const;

   public:
    Vec3f& composeSpherical(float rho, float theta, float phi);
    void decomposeSpherical(float& rho, float& theta, float& phi) const;
    Vec3f& composeCylindrical(float radius, float angle, float height);
    void decomposeCylindrical(float& radius, float& angle, float& height) const;
    float angle(const Vec3f& v) const;
    float angle(const Vec3f& p1, const Vec3f& p2) const;

   public:
    Vec3f midPoint(const Vec3f& point) const;
    Vec3f lerp(Vec3f& point, float factor) const;

   public:
    Vec3f& operator=(const Vec3f& v);
    Vec3f& operator+=(float scalar);
    Vec3f& operator-=(float scalar);
    Vec3f& operator*=(float scalar);
    Vec3f& operator/=(float scalar);
    Vec3f& operator+=(const Vec3f& v);
    Vec3f& operator-=(const Vec3f& v);
    Vec3f& operator*=(const Vec3f& v);
    Vec3f& operator/=(const Vec3f& v);
    Vec3f operator+(float scalar) const;
    Vec3f operator-(float scalar) const;
    Vec3f operator*(float scalar) const;
    Vec3f operator/(float scalar) const;
    Vec3f operator+(const Vec3f& v) const;
    Vec3f operator-(const Vec3f& v) const;
    Vec3f operator*(const Vec3f& v) const;
    Vec3f operator/(const Vec3f& v) const;
    bool operator==(const Vec3f& v) const;
    bool operator!=(const Vec3f& v) const;
    bool operator>(const Vec3f& v) const;
    bool operator<(const Vec3f& v) const;
    Vec3f operator-() const;
    float& operator[](uint32_t index);
    float operator[](uint32_t index) const;

   public:
    friend std::ostream& operator<<(std::ostream& os, const Vec3f& vec);
    friend std::istream& operator>>(std::istream& is, Vec3f& vec);

   public:
    static uint32_t dim();
    static uint32_t size();
    static Vec3f zero();
    static Vec3f one();
    static Vec3f xAxis();
    static Vec3f yAxis();
    static Vec3f zAxis();
    static Vec3f up();
    static Vec3f down();
    static Vec3f left();
    static Vec3f right();
    static Vec3f forward();
    static Vec3f backward();
    static Vec3f normalized(const Vec3f& v);
    static float distance(const Vec3f& v1, const Vec3f& v2);
    static float dot(const Vec3f& v1, const Vec3f& v2);
    static Vec3f cross(const Vec3f& v1, const Vec3f& v2);
    static Vec3f midPoint(const Vec3f& p1, const Vec3f& p2);
    static Vec3f lerp(const Vec3f& p1, const Vec3f& p2, float factor);
};

}  // namespace vne::math

namespace {

inline bool operator==(const vne::math::Vec3f& a, const glm::vec3& b) {
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

inline bool operator==(const glm::vec3& a, const vne::math::Vec3f& b) {
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

}  // namespace

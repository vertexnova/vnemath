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
 * @file mat3x3f.h
 * @brief Represents a 3x3 matrix of floating-point values.
 */

// Project includes
#include "vec3f.h"

// Third-party library includes
#include <glm/mat3x3.hpp>

// Standard library includes
#include <ostream>

namespace vne::math {

class Mat3x3f : public glm::mat3 {
   public:
    Mat3x3f();
    ~Mat3x3f();
    Mat3x3f(const Vec3f& col0, const Vec3f& col1, const Vec3f& col2);
    explicit Mat3x3f(const glm::mat3& other);
    Mat3x3f(const Mat3x3f& other);
    explicit Mat3x3f(float scalar);
    Mat3x3f(float x0, float y0, float z0, float x1, float y1, float z1, float x2, float y2, float z2);
    Mat3x3f& operator=(const Mat3x3f& other);

   public:
    Mat3x3f rotationMatrix(const Vec3f& x_axis, const Vec3f& y_axis, const Vec3f& z_axis);

   public:
    float determinant() const;
    float trace() const;
    Mat3x3f transpose() const;
    Mat3x3f inverse() const;
    Mat3x3f normalMatrix() const;
    Mat3x3f inverseTransposed() const;

   public:
    Vec3f getColumn(uint32_t idx) const;
    Vec3f getRow(uint32_t idx) const;
    Vec3f xAxis() const;
    Vec3f yAxis() const;
    Vec3f zAxis() const;

   public:
    bool areSame(const Mat3x3f& other, float eps = kFloatEpsilon) const;
    bool isOrthogonal(float eps = kFloatEpsilon) const;

   public:
    Mat3x3f operator+(const Mat3x3f& other) const;
    Mat3x3f& operator+=(const Mat3x3f& other);
    Mat3x3f operator-(const Mat3x3f& other) const;
    Mat3x3f& operator-=(const Mat3x3f& other);
    Mat3x3f operator*(const Mat3x3f& other) const;
    Mat3x3f& operator*=(const Mat3x3f& other);
    Mat3x3f operator*(float scalar) const;
    Mat3x3f& operator*=(float scalar);
    Mat3x3f operator/(float scalar) const;
    Mat3x3f& operator/=(float scalar);

   public:
    friend std::ostream& operator<<(std::ostream& os, const Mat3x3f& mat);

   public:
    static uint32_t length();
    static Mat3x3f identity();
    static Mat3x3f zero();
    static Mat3x3f lerp(const Mat3x3f& from, const Mat3x3f& to, float t);
    static Mat3x3f rotate(float angle, const Vec3f& axis);
    static Mat3x3f rotateX(float angle);
    static Mat3x3f rotateY(float angle);
    static Mat3x3f rotateZ(float angle);
    static Mat3x3f rotateXYZ(float x_angle, float y_angle, float z_angle);
    static Mat3x3f rotateXYZ(float angle);
    static Mat3x3f rotateZYX(float x_angle, float y_angle, float z_angle);
    static Mat3x3f rotateZYX(float angle);
    static Mat3x3f scale(const Vec3f& scale);
    static Mat3x3f scale(float sx, float sy, float sz);
    static Mat3x3f scale(float s);
};

// Legacy type alias for backward compatibility
using Mat3x3f_C = Mat3x3f;

}  // namespace vne::math

// Legacy namespace aliases
namespace VNE {
namespace Math {
using Mat3x3f_C = vne::math::Mat3x3f;
using Mat3x3f = vne::math::Mat3x3f;
}  // namespace Math
}  // namespace VNE

namespace {

inline bool operator==(const glm::mat3& a, const vne::math::Mat3x3f& b) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (a[i][j] != b[i][j]) {
                return false;
            }
        }
    }
    return true;
}

}  // namespace

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
 * @file mat4x4f.h
 * @brief Represents a 4x4 matrix of floating-point values.
 */

// Project includes
#include "mat3x3f.h"
#include "vec3f.h"
#include "vec4f.h"

// Third-party library includes
#include <glm/mat4x4.hpp>

// Standard library includes
#include <ostream>

namespace vne::math {

enum class Handedness { eLeft = 0, eRight = 1 };

class Mat4x4f : public glm::mat4 {
   public:
    Mat4x4f();
    ~Mat4x4f();
    Mat4x4f(const Vec4f& col0, const Vec4f& col1, const Vec4f& col2, const Vec4f& col3);
    Mat4x4f(const glm::mat4& other);
    Mat4x4f(const Mat4x4f& other);
    Mat4x4f(const glm::mat3& other);
    Mat4x4f(const Mat3x3f& other);
    Mat4x4f(float scalar);
    Mat4x4f(float x0,
            float y0,
            float z0,
            float w0,
            float x1,
            float y1,
            float z1,
            float w1,
            float x2,
            float y2,
            float z2,
            float w2,
            float x3,
            float y3,
            float z3,
            float w3);
    Mat4x4f& operator=(const Mat4x4f& other);

   public:
    Mat4x4f transform(const Vec3f& x_axis, const Vec3f& y_axis, const Vec3f& z_axis);
    Mat4x4f transform(const Vec3f& x_axis, const Vec3f& y_axis, const Vec3f& z_axis, const Vec3f& offset);
    Mat4x4f transform(const Vec3f& forward, const Vec3f& up);
    Mat4x4f transform(const Vec3f& trans);

   public:
    float determinant() const;
    Mat4x4f transpose() const;
    Mat4x4f inverse() const;
    Mat4x4f normalMatrix() const;
    Mat4x4f inverseTransposed() const;

   public:
    Vec4f getColumn(uint32_t idx) const;
    Vec4f getRow(uint32_t idx) const;
    Vec3f xAxis() const;
    Vec3f yAxis() const;
    Vec3f zAxis() const;
    Vec3f translation() const;
    Handedness handedness();

   public:
    Vec3f transformVector(const Vec3f& vec) const;
    Vec3f transformPoint(const Vec3f& point) const;
    Vec3f transformNormal(const Vec3f& normal) const;

   public:
    bool areSame(const Mat4x4f& other, float eps = kFloatEpsilon) const;
    bool isOrthogonal(float eps = kFloatEpsilon) const;

   public:
    Mat4x4f operator+(const Mat4x4f& other) const;
    Mat4x4f& operator+=(const Mat4x4f& other);
    Mat4x4f operator-(const Mat4x4f& other) const;
    Mat4x4f& operator-=(const Mat4x4f& other);
    Mat4x4f operator*(const Mat4x4f& other) const;
    Mat4x4f& operator*=(const Mat4x4f& other);
    Mat4x4f operator*(float scalar) const;
    Mat4x4f& operator*=(float scalar);
    Mat4x4f operator/(float scalar) const;
    Mat4x4f& operator/=(float scalar);

   public:
    friend std::ostream& operator<<(std::ostream& os, const Mat4x4f& other);

   public:
    static uint32_t length();
    static Mat4x4f identity();
    static Mat4x4f zero();
    static Mat4x4f lerp(const Mat4x4f& from, const Mat4x4f& to, float t);

   public:
    static Mat4x4f rotate(float angle, const Vec3f& axis);
    static Mat4x4f rotateX(float angle);
    static Mat4x4f rotateY(float angle);
    static Mat4x4f rotateZ(float angle);
    static Mat4x4f rotateXYZ(float x_angle, float y_angle, float z_angle);
    static Mat4x4f rotateXYZ(float angle);
    static Mat4x4f rotateZYX(float x_angle, float y_angle, float z_angle);
    static Mat4x4f rotateZYX(float angle);
    static Mat4x4f translate(const Vec3f& trans);
    static Mat4x4f translate(float tx, float ty, float tz);
    static Mat4x4f translate(float t);
    static Mat4x4f scale(const Vec3f& scale);
    static Mat4x4f scale(float sx, float sy, float sz);
    static Mat4x4f scale(float s);
    static Mat4x4f lookAt(const Vec3f& eye, const Vec3f& center, const Vec3f& up);
    static Mat4x4f frustum(float left, float right, float bottom, float top, float z_near, float z_far);
    static Mat4x4f perspective(float fovy, float aspect_ratio, float z_near, float z_far);
    static Mat4x4f ortho(float left, float right, float bottom, float top, float z_near, float z_far);
};

// Legacy type aliases for backward compatibility
using Mat4x4f_C = Mat4x4f;
using Handness_TP = Handedness;

}  // namespace vne::math

// Legacy namespace aliases
namespace VNE {
namespace Math {
using Mat4x4f_C = vne::math::Mat4x4f;
using Mat4x4f = vne::math::Mat4x4f;
using Handness_TP = vne::math::Handedness;
}  // namespace Math
}  // namespace VNE

namespace {

inline bool operator==(const glm::mat4& a, const vne::math::Mat4x4f& b) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (a[i][j] != b[i][j]) {
                return false;
            }
        }
    }
    return true;
}

}  // namespace

#ifndef VNE_MATH_MAT4x4F_H
#define VNE_MATH_MAT4x4F_H
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
#include "vec3f.h"
#include "vec4f.h"
#include "mat3x3f.h"

// Third-party library includes
#include <glm/mat4x4.hpp>

// Standard library includes
#include <ostream>

namespace VNE {
namespace Math {

enum class Handness_TP { LEFT = 0, RIGHT = 1 };

class Mat4x4f_C : public glm::mat4 {
   public:
    Mat4x4f_C();
    ~Mat4x4f_C();
    Mat4x4f_C(const Vec4f_C& col0, const Vec4f_C& col1, const Vec4f_C& col2, const Vec4f_C& col3);
    Mat4x4f_C(const glm::mat4& other);
    Mat4x4f_C(const Mat4x4f_C& other);
    Mat4x4f_C(const glm::mat3& other);
    Mat4x4f_C(const Mat3x3f_C& other);
    Mat4x4f_C(float scalar);
    Mat4x4f_C(float x0, float y0, float z0, float w0, float x1, float y1, float z1, float w1,
              float x2, float y2, float z2, float w2, float x3, float y3, float z3, float w3);
    Mat4x4f_C& operator=(const Mat4x4f_C& other);

   public:
    Mat4x4f_C Transform(const Vec3f_C& x_axis, const Vec3f_C& y_axis, const Vec3f_C& z_axis);
    Mat4x4f_C Transform(const Vec3f_C& x_axis, const Vec3f_C& y_axis, const Vec3f_C& z_axis, const Vec3f_C& offset);
    Mat4x4f_C Transform(const Vec3f_C& forward, const Vec3f_C& up);
    Mat4x4f_C Transform(const Vec3f_C& trans);

   public:
    float Determinant() const;
    Mat4x4f_C Transpose() const;
    Mat4x4f_C Inverse() const;
    Mat4x4f_C NormalMatrix() const;
    Mat4x4f_C InverseTransposed() const;

   public:
    Vec4f_C GetColumn(uint32_t idx) const;
    Vec4f_C GetRow(uint32_t idx) const;
    Vec3f_C XAxis() const;
    Vec3f_C YAxis() const;
    Vec3f_C ZAxis() const;
    Vec3f_C Translation() const;
    Handness_TP Handedness();

   public:
    Vec3f_C TransformVector(const Vec3f_C& vec) const;
    Vec3f_C TransformPoint(const Vec3f_C& point) const;
    Vec3f_C TransformNormal(const Vec3f_C& normal) const;

   public:
    bool AreSame(const Mat4x4f_C& other, float eps = Math::FLOAT_EPSILON) const;
    bool IsOrthogonal(float eps = Math::FLOAT_EPSILON) const;

   public:
    Mat4x4f_C operator+(const Mat4x4f_C& other) const;
    Mat4x4f_C& operator+=(const Mat4x4f_C& other);
    Mat4x4f_C operator-(const Mat4x4f_C& other) const;
    Mat4x4f_C& operator-=(const Mat4x4f_C& other);
    Mat4x4f_C operator*(const Mat4x4f_C& other) const;
    Mat4x4f_C& operator*=(const Mat4x4f_C& other);
    Mat4x4f_C operator*(float scalar) const;
    Mat4x4f_C& operator*=(float scalar);
    Mat4x4f_C operator/(float scalar) const;
    Mat4x4f_C& operator/=(float scalar);

   public:
    friend std::ostream& operator<<(std::ostream& os, const Mat4x4f_C& other);

   public:
    static uint32_t Length();
    static Mat4x4f_C Identity();
    static Mat4x4f_C Zero();
    static Mat4x4f_C Lerp(const Mat4x4f_C& from, const Mat4x4f_C& to, float t);

   public:
    static Mat4x4f_C Rotate(float angle, const Vec3f_C& axis);
    static Mat4x4f_C RotateX(float angle);
    static Mat4x4f_C RotateY(float angle);
    static Mat4x4f_C RotateZ(float angle);
    static Mat4x4f_C RotateXYZ(float x_angle, float y_angle, float z_angle);
    static Mat4x4f_C RotateXYZ(float angle);
    static Mat4x4f_C RotateZYX(float x_angle, float y_angle, float z_angle);
    static Mat4x4f_C RotateZYX(float angle);
    static Mat4x4f_C Translate(const Vec3f_C& trans);
    static Mat4x4f_C Translate(float tx, float ty, float tz);
    static Mat4x4f_C Translate(float t);
    static Mat4x4f_C Scale(const Vec3f_C& scale);
    static Mat4x4f_C Scale(float sx, float sy, float sz);
    static Mat4x4f_C Scale(float s);
    static Mat4x4f_C LookAt(const Vec3f_C& eye, const Vec3f_C& center, const Vec3f_C& up);
    static Mat4x4f_C Frustum(float left, float right, float bottom, float top, float z_near, float z_far);
    static Mat4x4f_C Perspective(float fovy, float aspect_ratio, float z_near, float z_far);
    static Mat4x4f_C Ortho(float left, float right, float bottom, float top, float z_near, float z_far);
};

}  // namespace Math
}  // namespace VNE

namespace {

inline bool operator==(const glm::mat4& a, const VNE::Math::Mat4x4f_C& b) {
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

#endif  // VNE_MATH_MAT4x4F_H

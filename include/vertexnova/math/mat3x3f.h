#ifndef VNE_MATH_MAT3x3F_H
#define VNE_MATH_MAT3x3F_H
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

namespace VNE {
namespace Math {

class Mat3x3f_C : public glm::mat3 {
   public:
    Mat3x3f_C();
    ~Mat3x3f_C();
    Mat3x3f_C(const Vec3f_C& col0, const Vec3f_C& col1, const Vec3f_C& col2);
    explicit Mat3x3f_C(const glm::mat3& other);
    Mat3x3f_C(const Mat3x3f_C& other);
    explicit Mat3x3f_C(float scalar);
    Mat3x3f_C(float x0, float y0, float z0, float x1, float y1, float z1, float x2, float y2, float z2);
    Mat3x3f_C& operator=(const Mat3x3f_C& other);

   public:
    Mat3x3f_C RotationMatrix(const Vec3f_C& x_axis, const Vec3f_C& y_axis, const Vec3f_C& z_axis);

   public:
    float Determinant() const;
    float Trace() const;
    Mat3x3f_C Transpose() const;
    Mat3x3f_C Inverse() const;
    Mat3x3f_C NormalMatrix() const;
    Mat3x3f_C InverseTransposed() const;

   public:
    Vec3f_C GetColumn(uint32_t idx) const;
    Vec3f_C GetRow(uint32_t idx) const;
    Vec3f_C XAxis() const;
    Vec3f_C YAxis() const;
    Vec3f_C ZAxis() const;

   public:
    bool AreSame(const Mat3x3f_C& other, float eps = Math::FLOAT_EPSILON) const;
    bool IsOrthogonal(float eps = Math::FLOAT_EPSILON) const;

   public:
    Mat3x3f_C operator+(const Mat3x3f_C& other) const;
    Mat3x3f_C& operator+=(const Mat3x3f_C& other);
    Mat3x3f_C operator-(const Mat3x3f_C& other) const;
    Mat3x3f_C& operator-=(const Mat3x3f_C& other);
    Mat3x3f_C operator*(const Mat3x3f_C& other) const;
    Mat3x3f_C& operator*=(const Mat3x3f_C& other);
    Mat3x3f_C operator*(float scalar) const;
    Mat3x3f_C& operator*=(float scalar);
    Mat3x3f_C operator/(float scalar) const;
    Mat3x3f_C& operator/=(float scalar);

   public:
    friend std::ostream& operator<<(std::ostream& os, const Mat3x3f_C& mat);

   public:
    static uint32_t Length();
    static Mat3x3f_C Identity();
    static Mat3x3f_C Zero();
    static Mat3x3f_C Lerp(const Mat3x3f_C& from, const Mat3x3f_C& to, float t);
    static Mat3x3f_C Rotate(float angle, const Vec3f_C& axis);
    static Mat3x3f_C RotateX(float angle);
    static Mat3x3f_C RotateY(float angle);
    static Mat3x3f_C RotateZ(float angle);
    static Mat3x3f_C RotateXYZ(float x_angle, float y_angle, float z_angle);
    static Mat3x3f_C RotateXYZ(float angle);
    static Mat3x3f_C RotateZYX(float x_angle, float y_angle, float z_angle);
    static Mat3x3f_C RotateZYX(float angle);
    static Mat3x3f_C Scale(const Vec3f_C& scale);
    static Mat3x3f_C Scale(float sx, float sy, float sz);
    static Mat3x3f_C Scale(float s);
};

}  // namespace Math
}  // namespace VNE

namespace {

inline bool operator==(const glm::mat3& a, const VNE::Math::Mat3x3f_C& b) {
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

#endif  // VNE_MATH_MAT3x3F_H

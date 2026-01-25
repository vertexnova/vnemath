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
    Mat3x3f() noexcept;
    ~Mat3x3f() noexcept = default;
    Mat3x3f(const Vec3f& col0, const Vec3f& col1, const Vec3f& col2) noexcept;
    explicit Mat3x3f(const glm::mat3& other) noexcept;
    Mat3x3f(const Mat3x3f& other) noexcept;
    explicit Mat3x3f(float scalar) noexcept;
    Mat3x3f(float x0, float y0, float z0, float x1, float y1, float z1, float x2, float y2, float z2) noexcept;
    Mat3x3f& operator=(const Mat3x3f& other) noexcept;

   public:
    [[nodiscard]] Mat3x3f rotationMatrix(const Vec3f& x_axis, const Vec3f& y_axis, const Vec3f& z_axis) noexcept;

   public:
    [[nodiscard]] float determinant() const noexcept;
    [[nodiscard]] float trace() const noexcept;
    [[nodiscard]] Mat3x3f transpose() const noexcept;
    [[nodiscard]] Mat3x3f inverse() const noexcept;
    [[nodiscard]] Mat3x3f normalMatrix() const noexcept;
    [[nodiscard]] Mat3x3f inverseTransposed() const noexcept;

   public:
    [[nodiscard]] Vec3f getColumn(uint32_t idx) const noexcept;
    [[nodiscard]] Vec3f getRow(uint32_t idx) const noexcept;
    [[nodiscard]] Vec3f xAxis() const noexcept;
    [[nodiscard]] Vec3f yAxis() const noexcept;
    [[nodiscard]] Vec3f zAxis() const noexcept;

   public:
    [[nodiscard]] bool areSame(const Mat3x3f& other, float eps = kFloatEpsilon) const noexcept;
    [[nodiscard]] bool isOrthogonal(float eps = kFloatEpsilon) const noexcept;

   public:
    [[nodiscard]] Mat3x3f operator+(const Mat3x3f& other) const noexcept;
    Mat3x3f& operator+=(const Mat3x3f& other) noexcept;
    [[nodiscard]] Mat3x3f operator-(const Mat3x3f& other) const noexcept;
    Mat3x3f& operator-=(const Mat3x3f& other) noexcept;
    [[nodiscard]] Mat3x3f operator*(const Mat3x3f& other) const noexcept;
    Mat3x3f& operator*=(const Mat3x3f& other) noexcept;
    [[nodiscard]] Mat3x3f operator*(float scalar) const noexcept;
    Mat3x3f& operator*=(float scalar) noexcept;
    [[nodiscard]] Mat3x3f operator/(float scalar) const noexcept;
    Mat3x3f& operator/=(float scalar) noexcept;

   public:
    friend std::ostream& operator<<(std::ostream& os, const Mat3x3f& mat);

   public:
    [[nodiscard]] static uint32_t length() noexcept;
    [[nodiscard]] static Mat3x3f identity() noexcept;
    [[nodiscard]] static Mat3x3f zero() noexcept;
    [[nodiscard]] static Mat3x3f lerp(const Mat3x3f& from, const Mat3x3f& to, float t) noexcept;
    [[nodiscard]] static Mat3x3f rotate(float angle, const Vec3f& axis) noexcept;
    [[nodiscard]] static Mat3x3f rotateX(float angle) noexcept;
    [[nodiscard]] static Mat3x3f rotateY(float angle) noexcept;
    [[nodiscard]] static Mat3x3f rotateZ(float angle) noexcept;
    [[nodiscard]] static Mat3x3f rotateXYZ(float x_angle, float y_angle, float z_angle) noexcept;
    [[nodiscard]] static Mat3x3f rotateXYZ(float angle) noexcept;
    [[nodiscard]] static Mat3x3f rotateZYX(float x_angle, float y_angle, float z_angle) noexcept;
    [[nodiscard]] static Mat3x3f rotateZYX(float angle) noexcept;
    [[nodiscard]] static Mat3x3f scale(const Vec3f& scale) noexcept;
    [[nodiscard]] static Mat3x3f scale(float sx, float sy, float sz) noexcept;
    [[nodiscard]] static Mat3x3f scale(float s) noexcept;
};

}  // namespace vne::math

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

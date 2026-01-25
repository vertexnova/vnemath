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
 * @brief Defines the Mat4x4f class for 4x4 matrix operations.
 */

// Project includes
#include "mat3x3f.h"
#include "core/vec.h"

// Third-party library includes
#include <glm/mat4x4.hpp>

// Standard library includes
#include <ostream>

namespace vne::math {

// Note: Handedness enum is defined in core/types.h

/**
 * @class Mat4x4f
 * @brief Represents a 4x4 matrix of floating-point values.
 *
 * This class extends glm::mat4 and provides additional operations
 * for 3D transformations including rotation, translation, scaling,
 * and projection matrices. The matrix is stored in column-major order.
 */
class Mat4x4f : public glm::mat4 {
   public:
    /** @brief Default constructor, initializes to identity matrix */
    Mat4x4f() noexcept;

    /** @brief Default destructor */
    ~Mat4x4f() noexcept = default;

    /**
     * @brief Constructs a matrix from four column vectors
     * @param col0 First column
     * @param col1 Second column
     * @param col2 Third column
     * @param col3 Fourth column
     */
    Mat4x4f(const Vec4f& col0, const Vec4f& col1, const Vec4f& col2, const Vec4f& col3) noexcept;

    /** @brief Constructs from a glm::mat4 */
    Mat4x4f(const glm::mat4& other) noexcept;

    /** @brief Copy constructor */
    Mat4x4f(const Mat4x4f& other) noexcept;

    /** @brief Constructs from a glm::mat3 (upper-left 3x3) */
    Mat4x4f(const glm::mat3& other) noexcept;

    /** @brief Constructs from a Mat3x3f (upper-left 3x3) */
    Mat4x4f(const Mat3x3f& other) noexcept;

    /**
     * @brief Constructs a diagonal matrix
     * @param scalar Value for all diagonal elements
     */
    Mat4x4f(float scalar) noexcept;

    /**
     * @brief Constructs from individual elements
     */
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
            float w3) noexcept;

    /** @brief Copy assignment operator */
    Mat4x4f& operator=(const Mat4x4f& other) noexcept;

   public:
    /// @name Transform Matrix Construction
    /// @{

    /**
     * @brief Creates a transform matrix from axis vectors
     * @param x_axis The x-axis direction
     * @param y_axis The y-axis direction
     * @param z_axis The z-axis direction
     * @return The transform matrix
     */
    [[nodiscard]] Mat4x4f transform(const Vec3f& x_axis, const Vec3f& y_axis, const Vec3f& z_axis) noexcept;

    /**
     * @brief Creates a transform matrix from axis vectors and translation
     * @param x_axis The x-axis direction
     * @param y_axis The y-axis direction
     * @param z_axis The z-axis direction
     * @param offset The translation offset
     * @return The transform matrix
     */
    [[nodiscard]] Mat4x4f transform(const Vec3f& x_axis,
                                    const Vec3f& y_axis,
                                    const Vec3f& z_axis,
                                    const Vec3f& offset) noexcept;

    /**
     * @brief Creates a transform matrix from forward and up vectors
     * @param forward The forward direction
     * @param up The up direction
     * @return The transform matrix
     */
    [[nodiscard]] Mat4x4f transform(const Vec3f& forward, const Vec3f& up) noexcept;

    /**
     * @brief Creates a translation matrix
     * @param trans The translation vector
     * @return The transform matrix
     */
    [[nodiscard]] Mat4x4f transform(const Vec3f& trans) noexcept;
    /// @}

   public:
    /// @name Matrix Properties
    /// @{

    /** @brief Calculates the determinant of the matrix */
    [[nodiscard]] float determinant() const noexcept;

    /** @brief Returns the transpose of this matrix */
    [[nodiscard]] Mat4x4f transpose() const noexcept;

    /** @brief Returns the inverse of this matrix */
    [[nodiscard]] Mat4x4f inverse() const noexcept;

    /** @brief Returns the normal matrix (inverse transpose of upper-left 3x3) */
    [[nodiscard]] Mat4x4f normalMatrix() const noexcept;

    /** @brief Returns the inverse transposed matrix */
    [[nodiscard]] Mat4x4f inverseTransposed() const noexcept;
    /// @}

   public:
    /// @name Element Access
    /// @{

    /**
     * @brief Gets a column vector by index
     * @param idx Column index (0-3)
     * @return The column vector
     */
    [[nodiscard]] Vec4f getColumn(uint32_t idx) const noexcept;

    /**
     * @brief Gets a row vector by index
     * @param idx Row index (0-3)
     * @return The row vector
     */
    [[nodiscard]] Vec4f getRow(uint32_t idx) const noexcept;

    /** @brief Gets the x-axis (first 3 components of column 0) */
    [[nodiscard]] Vec3f xAxis() const noexcept;

    /** @brief Gets the y-axis (first 3 components of column 1) */
    [[nodiscard]] Vec3f yAxis() const noexcept;

    /** @brief Gets the z-axis (first 3 components of column 2) */
    [[nodiscard]] Vec3f zAxis() const noexcept;

    /** @brief Gets the translation (first 3 components of column 3) */
    [[nodiscard]] Vec3f translation() const noexcept;

    /** @brief Determines the handedness of this transformation */
    [[nodiscard]] Handedness handedness() noexcept;
    /// @}

   public:
    /// @name Vector Transformation
    /// @{

    /**
     * @brief Transforms a direction vector (w=0)
     * @param vec The direction vector
     * @return The transformed direction
     */
    [[nodiscard]] Vec3f transformVector(const Vec3f& vec) const noexcept;

    /**
     * @brief Transforms a point (w=1)
     * @param point The point to transform
     * @return The transformed point
     */
    [[nodiscard]] Vec3f transformPoint(const Vec3f& point) const noexcept;

    /**
     * @brief Transforms a normal vector using the normal matrix
     * @param normal The normal to transform
     * @return The transformed normal
     */
    [[nodiscard]] Vec3f transformNormal(const Vec3f& normal) const noexcept;
    /// @}

   public:
    /** @brief Checks if two matrices are approximately equal */
    [[nodiscard]] bool areSame(const Mat4x4f& other, float eps = kFloatEpsilon) const noexcept;

    /** @brief Checks if this matrix is orthogonal */
    [[nodiscard]] bool isOrthogonal(float eps = kFloatEpsilon) const noexcept;

   public:
    /// @name Arithmetic Operators
    /// @{
    [[nodiscard]] Mat4x4f operator+(const Mat4x4f& other) const noexcept;
    Mat4x4f& operator+=(const Mat4x4f& other) noexcept;
    [[nodiscard]] Mat4x4f operator-(const Mat4x4f& other) const noexcept;
    Mat4x4f& operator-=(const Mat4x4f& other) noexcept;
    [[nodiscard]] Mat4x4f operator*(const Mat4x4f& other) const noexcept;
    Mat4x4f& operator*=(const Mat4x4f& other) noexcept;
    [[nodiscard]] Mat4x4f operator*(float scalar) const noexcept;
    Mat4x4f& operator*=(float scalar) noexcept;
    [[nodiscard]] Mat4x4f operator/(float scalar) const noexcept;
    Mat4x4f& operator/=(float scalar) noexcept;
    /// @}

   public:
    friend std::ostream& operator<<(std::ostream& os, const Mat4x4f& other);

   public:
    /// @name Static Factory Methods
    /// @{

    /** @brief Returns the number of columns (4) */
    [[nodiscard]] static uint32_t length() noexcept;

    /** @brief Creates an identity matrix */
    [[nodiscard]] static Mat4x4f identity() noexcept;

    /** @brief Creates a zero matrix */
    [[nodiscard]] static Mat4x4f zero() noexcept;

    /** @brief Linearly interpolates between two matrices */
    [[nodiscard]] static Mat4x4f lerp(const Mat4x4f& from, const Mat4x4f& to, float t) noexcept;
    /// @}

   public:
    /// @name Rotation Factory Methods
    /// @{

    /** @brief Creates a rotation matrix around an arbitrary axis */
    [[nodiscard]] static Mat4x4f rotate(float angle, const Vec3f& axis) noexcept;

    /** @brief Creates a rotation matrix around the X axis */
    [[nodiscard]] static Mat4x4f rotateX(float angle) noexcept;

    /** @brief Creates a rotation matrix around the Y axis */
    [[nodiscard]] static Mat4x4f rotateY(float angle) noexcept;

    /** @brief Creates a rotation matrix around the Z axis */
    [[nodiscard]] static Mat4x4f rotateZ(float angle) noexcept;

    /** @brief Creates a rotation with XYZ Euler angles */
    [[nodiscard]] static Mat4x4f rotateXYZ(float x_angle, float y_angle, float z_angle) noexcept;

    /** @brief Creates a rotation with same angle for all axes (XYZ order) */
    [[nodiscard]] static Mat4x4f rotateXYZ(float angle) noexcept;

    /** @brief Creates a rotation with ZYX Euler angles */
    [[nodiscard]] static Mat4x4f rotateZYX(float x_angle, float y_angle, float z_angle) noexcept;

    /** @brief Creates a rotation with same angle for all axes (ZYX order) */
    [[nodiscard]] static Mat4x4f rotateZYX(float angle) noexcept;
    /// @}

   public:
    /// @name Translation Factory Methods
    /// @{
    [[nodiscard]] static Mat4x4f translate(const Vec3f& trans) noexcept;
    [[nodiscard]] static Mat4x4f translate(float tx, float ty, float tz) noexcept;
    [[nodiscard]] static Mat4x4f translate(float t) noexcept;
    /// @}

   public:
    /// @name Scale Factory Methods
    /// @{
    [[nodiscard]] static Mat4x4f scale(const Vec3f& scale) noexcept;
    [[nodiscard]] static Mat4x4f scale(float sx, float sy, float sz) noexcept;
    [[nodiscard]] static Mat4x4f scale(float s) noexcept;
    /// @}

   public:
    /// @name View and Projection Factory Methods
    /// @{

    /**
     * @brief Creates a look-at view matrix
     * @param eye The camera position
     * @param center The target position
     * @param up The up direction
     * @return The view matrix
     */
    [[nodiscard]] static Mat4x4f lookAt(const Vec3f& eye, const Vec3f& center, const Vec3f& up) noexcept;

    /**
     * @brief Creates a frustum projection matrix
     * @param left Left clipping plane
     * @param right Right clipping plane
     * @param bottom Bottom clipping plane
     * @param top Top clipping plane
     * @param z_near Near clipping plane
     * @param z_far Far clipping plane
     * @return The projection matrix
     */
    [[nodiscard]] static Mat4x4f frustum(
        float left, float right, float bottom, float top, float z_near, float z_far) noexcept;

    /**
     * @brief Creates a perspective projection matrix
     * @param fovy Field of view in radians
     * @param aspect_ratio Aspect ratio (width / height)
     * @param z_near Near clipping plane
     * @param z_far Far clipping plane
     * @return The projection matrix
     */
    [[nodiscard]] static Mat4x4f perspective(float fovy, float aspect_ratio, float z_near, float z_far) noexcept;

    /**
     * @brief Creates an orthographic projection matrix
     * @param left Left clipping plane
     * @param right Right clipping plane
     * @param bottom Bottom clipping plane
     * @param top Top clipping plane
     * @param z_near Near clipping plane
     * @param z_far Far clipping plane
     * @return The projection matrix
     */
    [[nodiscard]] static Mat4x4f ortho(
        float left, float right, float bottom, float top, float z_near, float z_far) noexcept;
    /// @}
};

}  // namespace vne::math

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

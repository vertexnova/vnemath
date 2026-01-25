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
 * @brief Defines the Mat3x3f class for 3x3 matrix operations.
 */

// Project includes
#include "constants.h"
#include "core/vec.h"

// Third-party library includes
#include <glm/mat3x3.hpp>

// Standard library includes
#include <ostream>

namespace vne::math {

/**
 * @class Mat3x3f
 * @brief Represents a 3x3 matrix of floating-point values.
 *
 * This class extends glm::mat3 and provides additional operations
 * for 3D rotations, scaling, and other transformations.
 * The matrix is stored in column-major order.
 */
class Mat3x3f : public glm::mat3 {
   public:
    /** @brief Default constructor, initializes to identity matrix */
    Mat3x3f() noexcept;

    /** @brief Default destructor */
    ~Mat3x3f() noexcept = default;

    /**
     * @brief Constructs a matrix from three column vectors
     * @param col0 First column
     * @param col1 Second column
     * @param col2 Third column
     */
    Mat3x3f(const Vec3f& col0, const Vec3f& col1, const Vec3f& col2) noexcept;

    /**
     * @brief Constructs from a glm::mat3
     * @param other The glm matrix to copy
     */
    explicit Mat3x3f(const glm::mat3& other) noexcept;

    /** @brief Copy constructor */
    Mat3x3f(const Mat3x3f& other) noexcept;

    /**
     * @brief Constructs a diagonal matrix
     * @param scalar Value for all diagonal elements
     */
    explicit Mat3x3f(float scalar) noexcept;

    /**
     * @brief Constructs from individual elements (row-major input)
     * @param x0 Element at row 0, column 0
     * @param y0 Element at row 0, column 1
     * @param z0 Element at row 0, column 2
     * @param x1 Element at row 1, column 0
     * @param y1 Element at row 1, column 1
     * @param z1 Element at row 1, column 2
     * @param x2 Element at row 2, column 0
     * @param y2 Element at row 2, column 1
     * @param z2 Element at row 2, column 2
     */
    Mat3x3f(float x0, float y0, float z0, float x1, float y1, float z1, float x2, float y2, float z2) noexcept;

    /** @brief Copy assignment operator */
    Mat3x3f& operator=(const Mat3x3f& other) noexcept;

   public:
    /**
     * @brief Creates a rotation matrix from axis vectors
     * @param x_axis The x-axis of the rotation
     * @param y_axis The y-axis of the rotation
     * @param z_axis The z-axis of the rotation
     * @return The rotation matrix
     */
    [[nodiscard]] Mat3x3f rotationMatrix(const Vec3f& x_axis, const Vec3f& y_axis, const Vec3f& z_axis) noexcept;

   public:
    /**
     * @brief Calculates the determinant of the matrix
     * @return The determinant value
     */
    [[nodiscard]] float determinant() const noexcept;

    /**
     * @brief Calculates the trace (sum of diagonal elements)
     * @return The trace value
     */
    [[nodiscard]] float trace() const noexcept;

    /**
     * @brief Returns the transpose of this matrix
     * @return The transposed matrix
     */
    [[nodiscard]] Mat3x3f transpose() const noexcept;

    /**
     * @brief Returns the inverse of this matrix
     * @return The inverse matrix
     */
    [[nodiscard]] Mat3x3f inverse() const noexcept;

    /**
     * @brief Returns the normal matrix (inverse transpose)
     * @return The normal matrix for transforming normals
     */
    [[nodiscard]] Mat3x3f normalMatrix() const noexcept;

    /**
     * @brief Returns the inverse transposed matrix
     * @return The inverse transpose
     */
    [[nodiscard]] Mat3x3f inverseTransposed() const noexcept;

   public:
    /**
     * @brief Gets a column vector by index
     * @param idx Column index (0-2)
     * @return The column vector
     */
    [[nodiscard]] Vec3f getColumn(uint32_t idx) const noexcept;

    /**
     * @brief Gets a row vector by index
     * @param idx Row index (0-2)
     * @return The row vector
     */
    [[nodiscard]] Vec3f getRow(uint32_t idx) const noexcept;

    /** @brief Gets the first column (x-axis) */
    [[nodiscard]] Vec3f xAxis() const noexcept;

    /** @brief Gets the second column (y-axis) */
    [[nodiscard]] Vec3f yAxis() const noexcept;

    /** @brief Gets the third column (z-axis) */
    [[nodiscard]] Vec3f zAxis() const noexcept;

   public:
    /**
     * @brief Checks if two matrices are approximately equal
     * @param other The matrix to compare against
     * @param eps The tolerance for comparison
     * @return true if all elements are within eps
     */
    [[nodiscard]] bool areSame(const Mat3x3f& other, float eps = kFloatEpsilon) const noexcept;

    /**
     * @brief Checks if this matrix is orthogonal
     * @param eps The tolerance for comparison
     * @return true if M * M^T = I
     */
    [[nodiscard]] bool isOrthogonal(float eps = kFloatEpsilon) const noexcept;

   public:
    /// @name Arithmetic Operators
    /// @{
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
    /// @}

   public:
    friend std::ostream& operator<<(std::ostream& os, const Mat3x3f& mat);

   public:
    /// @name Static Factory Methods
    /// @{

    /** @brief Returns the number of columns (3) */
    [[nodiscard]] static uint32_t length() noexcept;

    /** @brief Creates an identity matrix */
    [[nodiscard]] static Mat3x3f identity() noexcept;

    /** @brief Creates a zero matrix */
    [[nodiscard]] static Mat3x3f zero() noexcept;

    /**
     * @brief Linearly interpolates between two matrices
     * @param from Start matrix
     * @param to End matrix
     * @param t Interpolation factor [0, 1]
     * @return The interpolated matrix
     */
    [[nodiscard]] static Mat3x3f lerp(const Mat3x3f& from, const Mat3x3f& to, float t) noexcept;

    /**
     * @brief Creates a rotation matrix around an arbitrary axis
     * @param angle Rotation angle in radians
     * @param axis The rotation axis (should be normalized)
     * @return The rotation matrix
     */
    [[nodiscard]] static Mat3x3f rotate(float angle, const Vec3f& axis) noexcept;

    /** @brief Creates a rotation matrix around the X axis */
    [[nodiscard]] static Mat3x3f rotateX(float angle) noexcept;

    /** @brief Creates a rotation matrix around the Y axis */
    [[nodiscard]] static Mat3x3f rotateY(float angle) noexcept;

    /** @brief Creates a rotation matrix around the Z axis */
    [[nodiscard]] static Mat3x3f rotateZ(float angle) noexcept;

    /**
     * @brief Creates a rotation matrix with XYZ Euler angles
     * @param x_angle Rotation around X axis
     * @param y_angle Rotation around Y axis
     * @param z_angle Rotation around Z axis
     * @return The combined rotation matrix
     */
    [[nodiscard]] static Mat3x3f rotateXYZ(float x_angle, float y_angle, float z_angle) noexcept;

    /** @brief Creates a rotation with same angle for all axes */
    [[nodiscard]] static Mat3x3f rotateXYZ(float angle) noexcept;

    /**
     * @brief Creates a rotation matrix with ZYX Euler angles
     * @param x_angle Rotation around X axis
     * @param y_angle Rotation around Y axis
     * @param z_angle Rotation around Z axis
     * @return The combined rotation matrix
     */
    [[nodiscard]] static Mat3x3f rotateZYX(float x_angle, float y_angle, float z_angle) noexcept;

    /** @brief Creates a rotation with same angle for all axes (ZYX order) */
    [[nodiscard]] static Mat3x3f rotateZYX(float angle) noexcept;

    /**
     * @brief Creates a scale matrix from a vector
     * @param scale Scale factors for each axis
     * @return The scale matrix
     */
    [[nodiscard]] static Mat3x3f scale(const Vec3f& scale) noexcept;

    /**
     * @brief Creates a scale matrix from individual factors
     * @param sx Scale factor for X axis
     * @param sy Scale factor for Y axis
     * @param sz Scale factor for Z axis
     * @return The scale matrix
     */
    [[nodiscard]] static Mat3x3f scale(float sx, float sy, float sz) noexcept;

    /**
     * @brief Creates a uniform scale matrix
     * @param s Scale factor for all axes
     * @return The scale matrix
     */
    [[nodiscard]] static Mat3x3f scale(float s) noexcept;
    /// @}
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

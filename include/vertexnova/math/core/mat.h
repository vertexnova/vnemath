#pragma once
/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Author:    Ajeet Singh Yadav
 * Created:   January 2026
 *
 * Autodoc:   yes
 * ----------------------------------------------------------------------
 */

/**
 * @file mat.h
 * @brief Templated matrix class for R x C matrices.
 *
 * This file provides a generic Mat<T, R, C> class that supports:
 * - Any floating-point type (float, double)
 * - Any dimensions (2x2, 3x3, 4x4, or non-square)
 * - Graphics API-specific projection matrices
 * - SIMD optimization via GLM backend
 */

#include "vec.h"

#include <array>
#include <cmath>
#include <ostream>

// GLM for optimized operations
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat2x2.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>

namespace vne::math {

/**
 * @class Mat
 * @brief A generic R x C matrix class (column-major storage).
 *
 * @tparam T The scalar type (must satisfy FloatingPoint concept)
 * @tparam R The number of rows
 * @tparam C The number of columns
 *
 * @example
 * ```cpp
 * Mat4f model = Mat4f::translate(Vec3f(1, 0, 0));
 * Mat4f view = Mat4f::lookAt(eye, center, up);
 * Mat4f proj = Mat4f::perspective(fov, aspect, near, far, GraphicsApi::eVulkan);
 * ```
 */
template<typename T, size_t R, size_t C>
    requires FloatingPoint<T>
class Mat {
   public:
    using value_type = T;
    using size_type = size_t;
    using col_type = Vec<T, R>;
    static constexpr size_type rows = R;
    static constexpr size_type cols = C;

    /// @brief Column-major storage (C columns, each with R elements)
    std::array<col_type, C> columns{};

   public:
    // ========================================================================
    // Constructors
    // ========================================================================

    /**
     * @brief Default constructor, initializes to identity for square matrices.
     */
    constexpr Mat() noexcept {
        if constexpr (R == C) {
            for (size_type i = 0; i < R; ++i) {
                columns[i][i] = T(1);
            }
        }
    }

    /**
     * @brief Constructs a diagonal matrix with the given scalar.
     * @param scalar The value for diagonal elements
     */
    constexpr explicit Mat(T scalar) noexcept {
        for (size_type i = 0; i < std::min(R, C); ++i) {
            columns[i][i] = scalar;
        }
    }

    /**
     * @brief Constructs a 2x2 matrix from columns.
     */
    constexpr Mat(const Vec<T, 2>& col0, const Vec<T, 2>& col1) noexcept
        requires(R == 2 && C == 2)
        : columns{col0, col1} {}

    /**
     * @brief Constructs a 3x3 matrix from columns.
     */
    constexpr Mat(const Vec<T, 3>& col0, const Vec<T, 3>& col1, const Vec<T, 3>& col2) noexcept
        requires(R == 3 && C == 3)
        : columns{col0, col1, col2} {}

    /**
     * @brief Constructs a 4x4 matrix from columns.
     */
    constexpr Mat(const Vec<T, 4>& col0, const Vec<T, 4>& col1, const Vec<T, 4>& col2, const Vec<T, 4>& col3) noexcept
        requires(R == 4 && C == 4)
        : columns{col0, col1, col2, col3} {}

    /**
     * @brief Copy constructor.
     */
    constexpr Mat(const Mat& other) noexcept = default;

    /**
     * @brief Move constructor.
     */
    constexpr Mat(Mat&& other) noexcept = default;

    /**
     * @brief Copy assignment.
     */
    constexpr Mat& operator=(const Mat& other) noexcept = default;

    /**
     * @brief Move assignment.
     */
    constexpr Mat& operator=(Mat&& other) noexcept = default;

    /**
     * @brief Destructor.
     */
    ~Mat() noexcept = default;

    // ========================================================================
    // GLM Interoperability
    // ========================================================================

    /**
     * @brief Constructs from glm::mat.
     */
    constexpr Mat(const glm::mat<C, R, T>& m) noexcept
        requires(R >= 2 && R <= 4 && C >= 2 && C <= 4)
    {
        for (size_type c = 0; c < C; ++c) {
            for (size_type r = 0; r < R; ++r) {
                columns[c][r] = m[static_cast<int>(c)][static_cast<int>(r)];
            }
        }
    }

    /**
     * @brief Converts to glm::mat.
     */
    [[nodiscard]] constexpr operator glm::mat<C, R, T>() const noexcept
        requires(R >= 2 && R <= 4 && C >= 2 && C <= 4)
    {
        glm::mat<C, R, T> result;
        for (size_type c = 0; c < C; ++c) {
            for (size_type r = 0; r < R; ++r) {
                result[static_cast<int>(c)][static_cast<int>(r)] = columns[c][r];
            }
        }
        return result;
    }

    // ========================================================================
    // Element Access
    // ========================================================================

    /**
     * @brief Accesses column by index.
     */
    [[nodiscard]] constexpr col_type& operator[](size_type c) noexcept { return columns[c]; }

    /**
     * @brief Accesses column by index (const).
     */
    [[nodiscard]] constexpr const col_type& operator[](size_type c) const noexcept { return columns[c]; }

    /**
     * @brief Gets a column vector.
     */
    [[nodiscard]] constexpr col_type getColumn(size_type c) const noexcept { return columns[c]; }

    /**
     * @brief Gets a row vector.
     */
    [[nodiscard]] constexpr Vec<T, C> getRow(size_type r) const noexcept {
        Vec<T, C> row;
        for (size_type c = 0; c < C; ++c) {
            row[c] = columns[c][r];
        }
        return row;
    }

    /**
     * @brief Returns a pointer to the underlying data.
     */
    [[nodiscard]] constexpr T* ptr() noexcept { return columns[0].ptr(); }

    /**
     * @brief Returns a const pointer to the underlying data.
     */
    [[nodiscard]] constexpr const T* ptr() const noexcept { return columns[0].ptr(); }

    // ========================================================================
    // Matrix Properties (Square Matrices Only)
    // ========================================================================

    /**
     * @brief Calculates the determinant.
     */
    [[nodiscard]] T determinant() const noexcept
        requires(R == C && R >= 2 && R <= 4)
    {
        return glm::determinant(static_cast<glm::mat<C, R, T>>(*this));
    }

    /**
     * @brief Returns the transpose.
     */
    [[nodiscard]] Mat<T, C, R> transpose() const noexcept {
        Mat<T, C, R> result;
        for (size_type r = 0; r < R; ++r) {
            for (size_type c = 0; c < C; ++c) {
                result[r][c] = columns[c][r];
            }
        }
        return result;
    }

    /**
     * @brief Returns the inverse.
     */
    [[nodiscard]] Mat inverse() const noexcept
        requires(R == C && R >= 2 && R <= 4)
    {
        return glm::inverse(static_cast<glm::mat<C, R, T>>(*this));
    }

    /**
     * @brief Returns the inverse transpose (for normal transformation).
     */
    [[nodiscard]] Mat inverseTranspose() const noexcept
        requires(R == C && R >= 2 && R <= 4)
    {
        return glm::inverseTranspose(static_cast<glm::mat<C, R, T>>(*this));
    }

    // ========================================================================
    // Transform Extraction (4x4 Only)
    // ========================================================================

    /**
     * @brief Gets the translation component.
     */
    [[nodiscard]] constexpr Vec<T, 3> translation() const noexcept
        requires(R == 4 && C == 4)
    {
        return columns[3].xyz();
    }

    /**
     * @brief Gets the X-axis (right) vector.
     */
    [[nodiscard]] constexpr Vec<T, 3> xAxis() const noexcept
        requires(R == 4 && C == 4)
    {
        return columns[0].xyz();
    }

    /**
     * @brief Gets the Y-axis (up) vector.
     */
    [[nodiscard]] constexpr Vec<T, 3> yAxis() const noexcept
        requires(R == 4 && C == 4)
    {
        return columns[1].xyz();
    }

    /**
     * @brief Gets the Z-axis (forward) vector.
     */
    [[nodiscard]] constexpr Vec<T, 3> zAxis() const noexcept
        requires(R == 4 && C == 4)
    {
        return columns[2].xyz();
    }

    // ========================================================================
    // Vector Transformation (4x4 Only)
    // ========================================================================

    /**
     * @brief Transforms a direction vector (w=0).
     */
    [[nodiscard]] constexpr Vec<T, 3> transformVector(const Vec<T, 3>& v) const noexcept
        requires(R == 4 && C == 4)
    {
        return (*this * Vec<T, 4>(v, T(0))).xyz();
    }

    /**
     * @brief Transforms a point (w=1).
     */
    [[nodiscard]] constexpr Vec<T, 3> transformPoint(const Vec<T, 3>& p) const noexcept
        requires(R == 4 && C == 4)
    {
        return (*this * Vec<T, 4>(p, T(1))).xyz();
    }

    // ========================================================================
    // Comparison
    // ========================================================================

    /**
     * @brief Checks if two matrices are approximately equal.
     */
    [[nodiscard]] constexpr bool approxEquals(const Mat& other, T epsilon = defaultEpsilon<T>()) const noexcept {
        for (size_type c = 0; c < C; ++c) {
            if (!columns[c].approxEquals(other.columns[c], epsilon)) {
                return false;
            }
        }
        return true;
    }

    [[nodiscard]] constexpr bool operator==(const Mat& other) const noexcept = default;

    // ========================================================================
    // Arithmetic Operators
    // ========================================================================

    [[nodiscard]] constexpr Mat operator+(const Mat& other) const noexcept {
        Mat result;
        for (size_type c = 0; c < C; ++c) {
            result.columns[c] = columns[c] + other.columns[c];
        }
        return result;
    }

    constexpr Mat& operator+=(const Mat& other) noexcept {
        for (size_type c = 0; c < C; ++c) {
            columns[c] += other.columns[c];
        }
        return *this;
    }

    [[nodiscard]] constexpr Mat operator-(const Mat& other) const noexcept {
        Mat result;
        for (size_type c = 0; c < C; ++c) {
            result.columns[c] = columns[c] - other.columns[c];
        }
        return result;
    }

    constexpr Mat& operator-=(const Mat& other) noexcept {
        for (size_type c = 0; c < C; ++c) {
            columns[c] -= other.columns[c];
        }
        return *this;
    }

    [[nodiscard]] constexpr Mat operator*(T scalar) const noexcept {
        Mat result;
        for (size_type c = 0; c < C; ++c) {
            result.columns[c] = columns[c] * scalar;
        }
        return result;
    }

    constexpr Mat& operator*=(T scalar) noexcept {
        for (size_type c = 0; c < C; ++c) {
            columns[c] *= scalar;
        }
        return *this;
    }

    /**
     * @brief Matrix-vector multiplication.
     */
    [[nodiscard]] constexpr Vec<T, R> operator*(const Vec<T, C>& v) const noexcept {
        Vec<T, R> result;
        for (size_type r = 0; r < R; ++r) {
            T sum = T(0);
            for (size_type c = 0; c < C; ++c) {
                sum += columns[c][r] * v[c];
            }
            result[r] = sum;
        }
        return result;
    }

    /**
     * @brief Matrix-matrix multiplication.
     */
    template<size_t C2>
    [[nodiscard]] constexpr Mat<T, R, C2> operator*(const Mat<T, C, C2>& other) const noexcept {
        Mat<T, R, C2> result;
        for (size_type c2 = 0; c2 < C2; ++c2) {
            result.columns[c2] = *this * other.columns[c2];
        }
        return result;
    }

    /**
     * @brief Matrix-matrix multiplication assignment (square only).
     */
    constexpr Mat& operator*=(const Mat& other) noexcept
        requires(R == C)
    {
        *this = *this * other;
        return *this;
    }

    // ========================================================================
    // Static Factory Methods
    // ========================================================================

    /**
     * @brief Returns a zero matrix.
     */
    [[nodiscard]] static constexpr Mat zero() noexcept {
        Mat result;
        for (size_type c = 0; c < C; ++c) {
            result.columns[c] = col_type::zero();
        }
        return result;
    }

    /**
     * @brief Returns an identity matrix (square only).
     */
    [[nodiscard]] static constexpr Mat identity() noexcept
        requires(R == C)
    {
        return Mat();
    }

    // ========================================================================
    // Transformation Factories (4x4 Only)
    // ========================================================================

    /**
     * @brief Creates a translation matrix.
     */
    [[nodiscard]] static Mat translate(const Vec<T, 3>& t) noexcept
        requires(R == 4 && C == 4)
    {
        return glm::translate(glm::mat<4, 4, T>(1), static_cast<glm::vec<3, T>>(t));
    }

    /**
     * @brief Creates a translation matrix.
     */
    [[nodiscard]] static Mat translate(T x, T y, T z) noexcept
        requires(R == 4 && C == 4)
    {
        return translate(Vec<T, 3>(x, y, z));
    }

    /**
     * @brief Creates a uniform scale matrix.
     */
    [[nodiscard]] static Mat scale(T s) noexcept
        requires(R == 4 && C == 4)
    {
        return glm::scale(glm::mat<4, 4, T>(1), glm::vec<3, T>(s));
    }

    /**
     * @brief Creates a non-uniform scale matrix.
     */
    [[nodiscard]] static Mat scale(const Vec<T, 3>& s) noexcept
        requires(R == 4 && C == 4)
    {
        return glm::scale(glm::mat<4, 4, T>(1), static_cast<glm::vec<3, T>>(s));
    }

    /**
     * @brief Creates a non-uniform scale matrix.
     */
    [[nodiscard]] static Mat scale(T x, T y, T z) noexcept
        requires(R == 4 && C == 4)
    {
        return scale(Vec<T, 3>(x, y, z));
    }

    /**
     * @brief Creates a rotation matrix around an arbitrary axis.
     */
    [[nodiscard]] static Mat rotate(T angle, const Vec<T, 3>& axis) noexcept
        requires(R == 4 && C == 4)
    {
        return glm::rotate(glm::mat<4, 4, T>(1), angle, static_cast<glm::vec<3, T>>(axis));
    }

    /**
     * @brief Creates a rotation matrix around the X axis.
     */
    [[nodiscard]] static Mat rotateX(T angle) noexcept
        requires(R == 4 && C == 4)
    {
        return rotate(angle, Vec<T, 3>::xAxis());
    }

    /**
     * @brief Creates a rotation matrix around the Y axis.
     */
    [[nodiscard]] static Mat rotateY(T angle) noexcept
        requires(R == 4 && C == 4)
    {
        return rotate(angle, Vec<T, 3>::yAxis());
    }

    /**
     * @brief Creates a rotation matrix around the Z axis.
     */
    [[nodiscard]] static Mat rotateZ(T angle) noexcept
        requires(R == 4 && C == 4)
    {
        return rotate(angle, Vec<T, 3>::zAxis());
    }

    // ========================================================================
    // View Matrix Factories (4x4 Only)
    // ========================================================================

    /**
     * @brief Creates a right-handed look-at view matrix.
     */
    [[nodiscard]] static Mat lookAtRH(const Vec<T, 3>& eye, const Vec<T, 3>& center, const Vec<T, 3>& up) noexcept
        requires(R == 4 && C == 4)
    {
        return glm::lookAtRH(static_cast<glm::vec<3, T>>(eye),
                             static_cast<glm::vec<3, T>>(center),
                             static_cast<glm::vec<3, T>>(up));
    }

    /**
     * @brief Creates a left-handed look-at view matrix.
     */
    [[nodiscard]] static Mat lookAtLH(const Vec<T, 3>& eye, const Vec<T, 3>& center, const Vec<T, 3>& up) noexcept
        requires(R == 4 && C == 4)
    {
        return glm::lookAtLH(static_cast<glm::vec<3, T>>(eye),
                             static_cast<glm::vec<3, T>>(center),
                             static_cast<glm::vec<3, T>>(up));
    }

    /**
     * @brief Creates a look-at view matrix for the specified graphics API.
     */
    [[nodiscard]] static Mat lookAt(const Vec<T, 3>& eye,
                                    const Vec<T, 3>& center,
                                    const Vec<T, 3>& up,
                                    GraphicsApi api = GraphicsApi::eVulkan) noexcept
        requires(R == 4 && C == 4)
    {
        if (getHandedness(api) == Handedness::eLeft) {
            return lookAtLH(eye, center, up);
        }
        return lookAtRH(eye, center, up);
    }

    // ========================================================================
    // Projection Matrix Factories (4x4 Only)
    // ========================================================================

    /**
     * @brief Creates a right-handed perspective matrix with [0,1] depth range.
     */
    [[nodiscard]] static Mat perspectiveRH_ZO(T fovy, T aspect, T z_near, T z_far) noexcept
        requires(R == 4 && C == 4)
    {
        return glm::perspectiveRH_ZO(fovy, aspect, z_near, z_far);
    }

    /**
     * @brief Creates a right-handed perspective matrix with [-1,1] depth range.
     */
    [[nodiscard]] static Mat perspectiveRH_NO(T fovy, T aspect, T z_near, T z_far) noexcept
        requires(R == 4 && C == 4)
    {
        return glm::perspectiveRH_NO(fovy, aspect, z_near, z_far);
    }

    /**
     * @brief Creates a left-handed perspective matrix with [0,1] depth range.
     */
    [[nodiscard]] static Mat perspectiveLH_ZO(T fovy, T aspect, T z_near, T z_far) noexcept
        requires(R == 4 && C == 4)
    {
        return glm::perspectiveLH_ZO(fovy, aspect, z_near, z_far);
    }

    /**
     * @brief Creates a left-handed perspective matrix with [-1,1] depth range.
     */
    [[nodiscard]] static Mat perspectiveLH_NO(T fovy, T aspect, T z_near, T z_far) noexcept
        requires(R == 4 && C == 4)
    {
        return glm::perspectiveLH_NO(fovy, aspect, z_near, z_far);
    }

    /**
     * @brief Creates a perspective matrix for the specified graphics API.
     * @param fovy Field of view in radians
     * @param aspect Aspect ratio (width / height)
     * @param z_near Near clipping plane
     * @param z_far Far clipping plane
     * @param api Target graphics API
     * @return The projection matrix
     */
    [[nodiscard]] static Mat perspective(
        T fovy, T aspect, T z_near, T z_far, GraphicsApi api = GraphicsApi::eVulkan) noexcept
        requires(R == 4 && C == 4)
    {
        bool left_handed = getHandedness(api) == Handedness::eLeft;
        bool zero_to_one = getClipSpaceDepth(api) == ClipSpaceDepth::eZeroToOne;

        Mat result;
        if (left_handed) {
            result = zero_to_one ? perspectiveLH_ZO(fovy, aspect, z_near, z_far)
                                 : perspectiveLH_NO(fovy, aspect, z_near, z_far);
        } else {
            result = zero_to_one ? perspectiveRH_ZO(fovy, aspect, z_near, z_far)
                                 : perspectiveRH_NO(fovy, aspect, z_near, z_far);
        }

        // Apply Y-flip for APIs that need it (Vulkan, Metal, WebGPU)
        if (needsYFlip(api)) {
            result[1][1] *= T(-1);
        }

        return result;
    }

    /**
     * @brief Creates a right-handed orthographic matrix with [0,1] depth range.
     */
    [[nodiscard]] static Mat orthoRH_ZO(T left, T right, T bottom, T top, T z_near, T z_far) noexcept
        requires(R == 4 && C == 4)
    {
        return glm::orthoRH_ZO(left, right, bottom, top, z_near, z_far);
    }

    /**
     * @brief Creates a right-handed orthographic matrix with [-1,1] depth range.
     */
    [[nodiscard]] static Mat orthoRH_NO(T left, T right, T bottom, T top, T z_near, T z_far) noexcept
        requires(R == 4 && C == 4)
    {
        return glm::orthoRH_NO(left, right, bottom, top, z_near, z_far);
    }

    /**
     * @brief Creates a left-handed orthographic matrix with [0,1] depth range.
     */
    [[nodiscard]] static Mat orthoLH_ZO(T left, T right, T bottom, T top, T z_near, T z_far) noexcept
        requires(R == 4 && C == 4)
    {
        return glm::orthoLH_ZO(left, right, bottom, top, z_near, z_far);
    }

    /**
     * @brief Creates a left-handed orthographic matrix with [-1,1] depth range.
     */
    [[nodiscard]] static Mat orthoLH_NO(T left, T right, T bottom, T top, T z_near, T z_far) noexcept
        requires(R == 4 && C == 4)
    {
        return glm::orthoLH_NO(left, right, bottom, top, z_near, z_far);
    }

    /**
     * @brief Creates an orthographic matrix for the specified graphics API.
     */
    [[nodiscard]] static Mat ortho(
        T left, T right, T bottom, T top, T z_near, T z_far, GraphicsApi api = GraphicsApi::eVulkan) noexcept
        requires(R == 4 && C == 4)
    {
        bool left_handed = getHandedness(api) == Handedness::eLeft;
        bool zero_to_one = getClipSpaceDepth(api) == ClipSpaceDepth::eZeroToOne;

        Mat result;
        if (left_handed) {
            result = zero_to_one ? orthoLH_ZO(left, right, bottom, top, z_near, z_far)
                                 : orthoLH_NO(left, right, bottom, top, z_near, z_far);
        } else {
            result = zero_to_one ? orthoRH_ZO(left, right, bottom, top, z_near, z_far)
                                 : orthoRH_NO(left, right, bottom, top, z_near, z_far);
        }

        // Apply Y-flip for APIs that need it
        if (needsYFlip(api)) {
            result[1][1] *= T(-1);
        }

        return result;
    }

    // ========================================================================
    // Static Operations
    // ========================================================================

    /**
     * @brief Linear interpolation between two matrices.
     */
    [[nodiscard]] static constexpr Mat lerp(const Mat& a, const Mat& b, T t) noexcept {
        Mat result;
        for (size_type c = 0; c < C; ++c) {
            result.columns[c] = Vec<T, R>::lerp(a.columns[c], b.columns[c], t);
        }
        return result;
    }

    // ========================================================================
    // Stream Output
    // ========================================================================

    friend std::ostream& operator<<(std::ostream& os, const Mat& m) {
        os << "[";
        for (size_type c = 0; c < C; ++c) {
            if (c > 0) {
                os << ", ";
            }
            os << m.columns[c];
        }
        os << "]";
        return os;
    }
};

// ============================================================================
// Free Function Operators
// ============================================================================

/**
 * @brief Scalar multiplication (scalar * matrix).
 */
template<typename T, size_t R, size_t C>
    requires FloatingPoint<T>
[[nodiscard]] constexpr Mat<T, R, C> operator*(T scalar, const Mat<T, R, C>& m) noexcept {
    return m * scalar;
}

}  // namespace vne::math

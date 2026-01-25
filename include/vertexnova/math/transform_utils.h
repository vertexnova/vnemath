/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Transform decomposition and composition utilities.
 * ----------------------------------------------------------------------
 */

#pragma once

#include "core/constants.h"
#include "core/mat.h"
#include "core/quat.h"
#include "core/types.h"
#include "core/vec.h"

namespace vne::math {

/**
 * @struct TransformComponents
 * @brief Holds decomposed transformation components (Translation, Rotation, Scale).
 *
 * Used for extracting and combining transformation components from matrices.
 */
struct TransformComponents {
    Vec3f translation{Vec3f::zero()};        ///< Translation component
    Quatf rotation{Quatf::identity()};       ///< Rotation component
    Vec3f scale{1.0f, 1.0f, 1.0f};           ///< Scale component

    /**
     * @brief Default constructor. Creates identity transform.
     */
    constexpr TransformComponents() noexcept = default;

    /**
     * @brief Constructs with specified components.
     */
    constexpr TransformComponents(const Vec3f& t, const Quatf& r, const Vec3f& s) noexcept
        : translation(t)
        , rotation(r)
        , scale(s) {}

    /**
     * @brief Checks if this is an identity transform.
     */
    [[nodiscard]] bool isIdentity(float epsilon = kFloatEpsilon) const noexcept {
        return translation.lengthSquared() < epsilon * epsilon
               && rotation.approxEquals(Quatf::identity(), epsilon)
               && approxEqual(scale.x(), 1.0f, epsilon)
               && approxEqual(scale.y(), 1.0f, epsilon)
               && approxEqual(scale.z(), 1.0f, epsilon);
    }

    /**
     * @brief Checks if this transform has uniform scale.
     */
    [[nodiscard]] bool hasUniformScale(float epsilon = kFloatEpsilon) const noexcept {
        return approxEqual(scale.x(), scale.y(), epsilon)
               && approxEqual(scale.y(), scale.z(), epsilon);
    }
};

// ============================================================================
// Matrix Decomposition
// ============================================================================

/**
 * @brief Decomposes a 4x4 transformation matrix into TRS components.
 *
 * Extracts translation, rotation, and scale from an affine transformation matrix.
 * Assumes the matrix does not contain shear. Results are undefined for
 * non-affine or sheared matrices.
 *
 * The decomposition order is: M = T * R * S
 *
 * @param matrix The 4x4 transformation matrix to decompose
 * @return TransformComponents containing translation, rotation, and scale
 *
 * @note For matrices with shear, consider using decompose_affine() which
 *       handles the general affine case.
 */
[[nodiscard]] inline TransformComponents decompose(const Mat4f& matrix) noexcept {
    TransformComponents result;

    // Extract translation from the last column
    result.translation = Vec3f(matrix.getColumn(3).x(),
                               matrix.getColumn(3).y(),
                               matrix.getColumn(3).z());

    // Extract the upper-left 3x3 matrix
    Vec3f col0(matrix.getColumn(0).x(), matrix.getColumn(0).y(), matrix.getColumn(0).z());
    Vec3f col1(matrix.getColumn(1).x(), matrix.getColumn(1).y(), matrix.getColumn(1).z());
    Vec3f col2(matrix.getColumn(2).x(), matrix.getColumn(2).y(), matrix.getColumn(2).z());

    // Extract scale (length of each column)
    result.scale = Vec3f(col0.length(), col1.length(), col2.length());

    // Handle negative scale (reflection) - check determinant
    Vec3f cross = col0.cross(col1);
    if (cross.dot(col2) < 0.0f) {
        result.scale.x() = -result.scale.x();
    }

    // Normalize columns to extract rotation
    if (result.scale.x() != 0.0f) col0 = col0 / result.scale.x();
    if (result.scale.y() != 0.0f) col1 = col1 / result.scale.y();
    if (result.scale.z() != 0.0f) col2 = col2 / result.scale.z();

    // Build rotation matrix and convert to quaternion
    Mat3f rotation_matrix(col0, col1, col2);
    result.rotation = Quatf::fromMatrix(rotation_matrix);

    return result;
}

/**
 * @brief Composes a 4x4 transformation matrix from TRS components.
 *
 * Creates a matrix that applies transformations in the order: Scale, Rotate, Translate.
 *
 * @param translation Translation vector
 * @param rotation Rotation quaternion
 * @param scale Scale vector
 * @return The composed 4x4 transformation matrix
 */
[[nodiscard]] inline Mat4f compose(const Vec3f& translation,
                                   const Quatf& rotation,
                                   const Vec3f& scale) noexcept {
    // Get rotation as 3x3 matrix
    Mat3f rot_mat = rotation.toMatrix3();

    // Apply scale to rotation columns
    Vec3f col0 = Vec3f(rot_mat.getColumn(0).x(), rot_mat.getColumn(0).y(), rot_mat.getColumn(0).z()) * scale.x();
    Vec3f col1 = Vec3f(rot_mat.getColumn(1).x(), rot_mat.getColumn(1).y(), rot_mat.getColumn(1).z()) * scale.y();
    Vec3f col2 = Vec3f(rot_mat.getColumn(2).x(), rot_mat.getColumn(2).y(), rot_mat.getColumn(2).z()) * scale.z();

    // Build 4x4 matrix
    return Mat4f(
        Vec4f(col0.x(), col0.y(), col0.z(), 0.0f),
        Vec4f(col1.x(), col1.y(), col1.z(), 0.0f),
        Vec4f(col2.x(), col2.y(), col2.z(), 0.0f),
        Vec4f(translation.x(), translation.y(), translation.z(), 1.0f)
    );
}

/**
 * @brief Composes a 4x4 transformation matrix from TransformComponents.
 *
 * @param components The transform components
 * @return The composed 4x4 transformation matrix
 */
[[nodiscard]] inline Mat4f compose(const TransformComponents& components) noexcept {
    return compose(components.translation, components.rotation, components.scale);
}

// ============================================================================
// Transform Utilities
// ============================================================================

/**
 * @brief Extracts just the translation from a 4x4 matrix.
 *
 * @param matrix The transformation matrix
 * @return The translation vector
 */
[[nodiscard]] inline Vec3f extractTranslation(const Mat4f& matrix) noexcept {
    return Vec3f(matrix.getColumn(3).x(),
                 matrix.getColumn(3).y(),
                 matrix.getColumn(3).z());
}

/**
 * @brief Extracts just the scale from a 4x4 matrix.
 *
 * @param matrix The transformation matrix
 * @return The scale vector
 */
[[nodiscard]] inline Vec3f extractScale(const Mat4f& matrix) noexcept {
    Vec3f col0(matrix.getColumn(0).x(), matrix.getColumn(0).y(), matrix.getColumn(0).z());
    Vec3f col1(matrix.getColumn(1).x(), matrix.getColumn(1).y(), matrix.getColumn(1).z());
    Vec3f col2(matrix.getColumn(2).x(), matrix.getColumn(2).y(), matrix.getColumn(2).z());

    Vec3f scale(col0.length(), col1.length(), col2.length());

    // Check for negative scale (reflection)
    Vec3f cross = col0.cross(col1);
    if (cross.dot(col2) < 0.0f) {
        scale.x() = -scale.x();
    }

    return scale;
}

/**
 * @brief Extracts just the rotation from a 4x4 matrix.
 *
 * @param matrix The transformation matrix
 * @return The rotation quaternion
 */
[[nodiscard]] inline Quatf extractRotation(const Mat4f& matrix) noexcept {
    Vec3f col0(matrix.getColumn(0).x(), matrix.getColumn(0).y(), matrix.getColumn(0).z());
    Vec3f col1(matrix.getColumn(1).x(), matrix.getColumn(1).y(), matrix.getColumn(1).z());
    Vec3f col2(matrix.getColumn(2).x(), matrix.getColumn(2).y(), matrix.getColumn(2).z());

    // Get scale
    float sx = col0.length();
    float sy = col1.length();
    float sz = col2.length();

    // Check for reflection
    Vec3f cross = col0.cross(col1);
    if (cross.dot(col2) < 0.0f) {
        sx = -sx;
    }

    // Normalize
    if (sx != 0.0f) col0 = col0 / sx;
    if (sy != 0.0f) col1 = col1 / sy;
    if (sz != 0.0f) col2 = col2 / sz;

    Mat3f rotation_matrix(col0, col1, col2);
    return Quatf::fromMatrix(rotation_matrix);
}

/**
 * @brief Extracts the upper-left 3x3 rotation/scale matrix from a 4x4 matrix.
 *
 * @param matrix The 4x4 transformation matrix
 * @return The upper-left 3x3 matrix
 */
[[nodiscard]] inline Mat3f extractMat3(const Mat4f& matrix) noexcept {
    return Mat3f(
        Vec3f(matrix.getColumn(0).x(), matrix.getColumn(0).y(), matrix.getColumn(0).z()),
        Vec3f(matrix.getColumn(1).x(), matrix.getColumn(1).y(), matrix.getColumn(1).z()),
        Vec3f(matrix.getColumn(2).x(), matrix.getColumn(2).y(), matrix.getColumn(2).z())
    );
}

/**
 * @brief Creates a 4x4 translation matrix.
 *
 * @param translation The translation vector
 * @return The translation matrix
 */
[[nodiscard]] inline Mat4f makeTranslation(const Vec3f& translation) noexcept {
    return Mat4f(
        Vec4f(1.0f, 0.0f, 0.0f, 0.0f),
        Vec4f(0.0f, 1.0f, 0.0f, 0.0f),
        Vec4f(0.0f, 0.0f, 1.0f, 0.0f),
        Vec4f(translation.x(), translation.y(), translation.z(), 1.0f)
    );
}

/**
 * @brief Creates a 4x4 rotation matrix from a quaternion.
 *
 * @param rotation The rotation quaternion
 * @return The rotation matrix
 */
[[nodiscard]] inline Mat4f makeRotation(const Quatf& rotation) noexcept {
    Mat3f rot3 = rotation.toMatrix3();
    return Mat4f(
        Vec4f(rot3.getColumn(0).x(), rot3.getColumn(0).y(), rot3.getColumn(0).z(), 0.0f),
        Vec4f(rot3.getColumn(1).x(), rot3.getColumn(1).y(), rot3.getColumn(1).z(), 0.0f),
        Vec4f(rot3.getColumn(2).x(), rot3.getColumn(2).y(), rot3.getColumn(2).z(), 0.0f),
        Vec4f(0.0f, 0.0f, 0.0f, 1.0f)
    );
}

/**
 * @brief Creates a 4x4 uniform scale matrix.
 *
 * @param scale The uniform scale factor
 * @return The scale matrix
 */
[[nodiscard]] inline Mat4f makeScale(float scale) noexcept {
    return Mat4f(
        Vec4f(scale, 0.0f, 0.0f, 0.0f),
        Vec4f(0.0f, scale, 0.0f, 0.0f),
        Vec4f(0.0f, 0.0f, scale, 0.0f),
        Vec4f(0.0f, 0.0f, 0.0f, 1.0f)
    );
}

/**
 * @brief Creates a 4x4 non-uniform scale matrix.
 *
 * @param scale The scale vector
 * @return The scale matrix
 */
[[nodiscard]] inline Mat4f makeScale(const Vec3f& scale) noexcept {
    return Mat4f(
        Vec4f(scale.x(), 0.0f, 0.0f, 0.0f),
        Vec4f(0.0f, scale.y(), 0.0f, 0.0f),
        Vec4f(0.0f, 0.0f, scale.z(), 0.0f),
        Vec4f(0.0f, 0.0f, 0.0f, 1.0f)
    );
}

/**
 * @brief Interpolates between two transformation matrices.
 *
 * Decomposes both matrices, interpolates TRS components, then recomposes.
 * More accurate than simple matrix lerp for transformations.
 *
 * @param a First matrix
 * @param b Second matrix
 * @param t Interpolation factor [0, 1]
 * @return Interpolated transformation matrix
 */
[[nodiscard]] inline Mat4f lerpTransform(const Mat4f& a, const Mat4f& b, float t) noexcept {
    TransformComponents ca = decompose(a);
    TransformComponents cb = decompose(b);

    Vec3f translation = Vec3f::lerp(ca.translation, cb.translation, t);
    Quatf rotation = ca.rotation.slerp(cb.rotation, t);
    Vec3f scale = Vec3f::lerp(ca.scale, cb.scale, t);

    return compose(translation, rotation, scale);
}

}  // namespace vne::math

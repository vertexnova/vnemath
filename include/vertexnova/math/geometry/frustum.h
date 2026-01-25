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
 * @file frustum.h
 * @brief Defines the Frustum class for view frustum culling operations.
 */

// Project includes
#include "vertexnova/math/geometry/plane.h"

// Standard library includes
#include <ostream>

// Forward declarations
namespace vne::math {
class Mat4x4f;
class Aabb;
class Sphere;
}  // namespace vne::math

namespace vne::math {

/**
 * @class Frustum
 * @brief Represents a view frustum for culling operations.
 *
 * The view frustum is the volume of space containing everything visible
 * in the 3D scene. It is bounded by six planes: near, far, left, right,
 * top, and bottom. This is commonly used for frustum culling to avoid
 * rendering objects outside the view.
 */
class Frustum {
   public:
    /** @brief Default constructor, creates a clip-space frustum */
    Frustum() noexcept = default;

    /** @brief Default destructor */
    ~Frustum() noexcept = default;

    /** @brief Copy constructor */
    Frustum(const Frustum& other) noexcept = default;

    /** @brief Copy assignment operator */
    Frustum& operator=(const Frustum& other) noexcept = default;

   public:
    /**
     * @brief Extracts frustum planes from a matrix
     * @param mat The matrix to extract planes from
     *
     * The resulting frustum space depends on the input matrix:
     * - Projection matrix: frustum in view space
     * - View-projection matrix: frustum in world space
     * - Model-view-projection matrix: frustum in model space
     *
     * Reference: http://www.cs.otago.ac.nz/postgrads/alexis/planeExtraction.pdf
     */
    void extractFromMatrix(const Mat4x4f& mat) noexcept;

   public:
    /// @name Containment Tests
    /// @{

    /**
     * @brief Checks if a point is inside the frustum
     * @param point The point to test
     * @param eps Tolerance for plane tests
     * @return true if the point is inside all planes
     */
    [[nodiscard]] bool contains(const Vec3f& point, float eps = kFloatEpsilon) const noexcept;

    /**
     * @brief Checks if a sphere intersects the frustum
     * @param sphere The sphere to test
     * @return true if the sphere is at least partially inside
     */
    [[nodiscard]] bool intersects(const Sphere& sphere) const noexcept;

    /**
     * @brief Checks if an AABB intersects the frustum
     * @param aabb The AABB to test
     * @return true if the AABB is at least partially inside
     */
    [[nodiscard]] bool intersects(const Aabb& aabb) const noexcept;

    /**
     * @brief Checks if a sphere is completely inside the frustum
     * @param sphere The sphere to test
     * @return true if the sphere is fully contained
     */
    [[nodiscard]] bool containsFully(const Sphere& sphere) const noexcept;

    /**
     * @brief Checks if an AABB is completely inside the frustum
     * @param aabb The AABB to test
     * @return true if the AABB is fully contained
     */
    [[nodiscard]] bool containsFully(const Aabb& aabb) const noexcept;
    /// @}

   public:
    /// @name Plane Accessors
    /// @{
    [[nodiscard]] const Plane& nearPlane() const noexcept { return near_; }
    [[nodiscard]] const Plane& farPlane() const noexcept { return far_; }
    [[nodiscard]] const Plane& leftPlane() const noexcept { return left_; }
    [[nodiscard]] const Plane& rightPlane() const noexcept { return right_; }
    [[nodiscard]] const Plane& topPlane() const noexcept { return top_; }
    [[nodiscard]] const Plane& bottomPlane() const noexcept { return bottom_; }
    /// @}

   public:
    /// @name Comparison Operators
    /// @{
    [[nodiscard]] bool operator==(const Frustum& other) const noexcept;
    [[nodiscard]] bool operator!=(const Frustum& other) const noexcept;
    /// @}

   public:
    friend std::ostream& operator<<(std::ostream& os, const Frustum& frustum);

   private:
    Plane near_{Vec3f::forward(), 1.0f};  ///< Near clipping plane
    Plane far_{Vec3f::backward(), 1.0f};  ///< Far clipping plane
    Plane left_{Vec3f::right(), 1.0f};    ///< Left clipping plane
    Plane right_{Vec3f::left(), 1.0f};    ///< Right clipping plane
    Plane bottom_{Vec3f::up(), 1.0f};     ///< Bottom clipping plane
    Plane top_{Vec3f::down(), 1.0f};      ///< Top clipping plane
};

}  // namespace vne::math

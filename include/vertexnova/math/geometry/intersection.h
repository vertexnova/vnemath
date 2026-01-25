/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * High-performance intersection tests for ray casting and collision.
 * ----------------------------------------------------------------------
 */

#pragma once

#include "../core/types.h"
#include "../core/vec.h"
#include "aabb.h"
#include "plane.h"
#include "ray.h"
#include "sphere.h"
#include "triangle.h"

#include <optional>

namespace vne::math {

// ============================================================================
// Hit Result Structure
// ============================================================================

/**
 * @struct RayHit
 * @brief Result of a ray intersection test.
 */
struct RayHit {
    float distance = 0.0f;  ///< Distance along ray to hit point
    Vec3f point;            ///< World-space hit position
    Vec3f normal;           ///< Surface normal at hit point
    Vec2f uv;               ///< Texture coordinates (for triangles: barycentric u,v)

    /**
     * @brief Creates an empty/invalid hit.
     */
    static constexpr RayHit none() noexcept { return RayHit{-1.0f, Vec3f::zero(), Vec3f::zero(), Vec2f::zero()}; }

    /**
     * @brief Checks if this represents a valid hit.
     */
    [[nodiscard]] constexpr bool valid() const noexcept { return distance >= 0.0f; }

    /**
     * @brief Implicit conversion to bool.
     */
    [[nodiscard]] constexpr explicit operator bool() const noexcept { return valid(); }
};

// ============================================================================
// Ray-Plane Intersection
// ============================================================================

/**
 * @brief Intersects a ray with a plane.
 *
 * @param ray The ray
 * @param plane The plane
 * @param max_distance Maximum distance to check (default: infinity)
 * @return Hit result if intersection found
 */
[[nodiscard]] inline RayHit intersect(const Ray& ray,
                                      const Plane& plane,
                                      float max_distance = std::numeric_limits<float>::max()) noexcept {
    float denom = plane.normal.dot(ray.direction());

    // Check if ray is parallel to plane
    if (isZero(denom)) {
        return RayHit::none();
    }

    float t = -(plane.normal.dot(ray.origin()) + plane.d) / denom;

    // Check if intersection is in valid range
    if (t < 0.0f || t > max_distance) {
        return RayHit::none();
    }

    RayHit hit;
    hit.distance = t;
    hit.point = ray.getPoint(t);
    hit.normal = denom < 0.0f ? plane.normal : -plane.normal;  // Face towards ray
    return hit;
}

// ============================================================================
// Ray-Sphere Intersection
// ============================================================================

/**
 * @brief Intersects a ray with a sphere.
 *
 * Uses the geometric solution for better numerical stability.
 *
 * @param ray The ray
 * @param sphere The sphere
 * @param max_distance Maximum distance to check
 * @return Hit result if intersection found
 */
[[nodiscard]] inline RayHit intersect(const Ray& ray,
                                      const Sphere& sphere,
                                      float max_distance = std::numeric_limits<float>::max()) noexcept {
    Vec3f oc = ray.origin() - sphere.center();
    float b = oc.dot(ray.direction());
    float c = oc.dot(oc) - sphere.radius() * sphere.radius();

    // Ray origin outside sphere and pointing away
    if (c > 0.0f && b > 0.0f) {
        return RayHit::none();
    }

    float discriminant = b * b - c;
    if (discriminant < 0.0f) {
        return RayHit::none();
    }

    float sqrt_disc = std::sqrt(discriminant);

    // Find nearest intersection
    float t = -b - sqrt_disc;
    if (t < 0.0f) {
        t = -b + sqrt_disc;  // Inside sphere, use far intersection
    }

    if (t < 0.0f || t > max_distance) {
        return RayHit::none();
    }

    RayHit hit;
    hit.distance = t;
    hit.point = ray.getPoint(t);
    hit.normal = (hit.point - sphere.center()).normalized();
    return hit;
}

// ============================================================================
// Ray-AABB Intersection (Slab Method)
// ============================================================================

/**
 * @brief Intersects a ray with an axis-aligned bounding box.
 *
 * Uses the optimized slab method with IEEE floating-point handling.
 *
 * @param ray The ray
 * @param aabb The AABB
 * @param max_distance Maximum distance to check
 * @return Hit result if intersection found
 */
[[nodiscard]] inline RayHit intersect(const Ray& ray,
                                      const Aabb& aabb,
                                      float max_distance = std::numeric_limits<float>::max()) noexcept {
    Vec3f inv_dir(1.0f / ray.direction().x(), 1.0f / ray.direction().y(), 1.0f / ray.direction().z());

    Vec3f t0 = (aabb.min() - ray.origin()) * inv_dir.x();
    Vec3f t1 = (aabb.max() - ray.origin()) * inv_dir.x();

    // Handle negative direction components
    float tx_min = min(t0.x(), t1.x());
    float tx_max = max(t0.x(), t1.x());

    Vec3f t0y = (aabb.min() - ray.origin()) * inv_dir.y();
    Vec3f t1y = (aabb.max() - ray.origin()) * inv_dir.y();
    float ty_min = min(t0y.y(), t1y.y());
    float ty_max = max(t0y.y(), t1y.y());

    if (tx_min > ty_max || ty_min > tx_max) {
        return RayHit::none();
    }

    float t_min = max(tx_min, ty_min);
    float t_max = min(tx_max, ty_max);

    Vec3f t0z = (aabb.min() - ray.origin()) * inv_dir.z();
    Vec3f t1z = (aabb.max() - ray.origin()) * inv_dir.z();
    float tz_min = min(t0z.z(), t1z.z());
    float tz_max = max(t0z.z(), t1z.z());

    if (t_min > tz_max || tz_min > t_max) {
        return RayHit::none();
    }

    t_min = max(t_min, tz_min);
    t_max = min(t_max, tz_max);

    // Check if intersection is in valid range
    float t = t_min >= 0.0f ? t_min : t_max;
    if (t < 0.0f || t > max_distance) {
        return RayHit::none();
    }

    RayHit hit;
    hit.distance = t;
    hit.point = ray.getPoint(t);

    // Compute normal (face that was hit)
    Vec3f center = aabb.center();
    Vec3f local = hit.point - center;
    Vec3f half = aabb.halfExtents();

    // Find which face was hit by checking which component is closest to edge
    Vec3f abs_local(std::abs(local.x()) / half.x(), std::abs(local.y()) / half.y(), std::abs(local.z()) / half.z());

    if (abs_local.x() > abs_local.y() && abs_local.x() > abs_local.z()) {
        hit.normal = Vec3f(local.x() > 0 ? 1.0f : -1.0f, 0.0f, 0.0f);
    } else if (abs_local.y() > abs_local.z()) {
        hit.normal = Vec3f(0.0f, local.y() > 0 ? 1.0f : -1.0f, 0.0f);
    } else {
        hit.normal = Vec3f(0.0f, 0.0f, local.z() > 0 ? 1.0f : -1.0f);
    }

    return hit;
}

// ============================================================================
// Ray-Triangle Intersection (Möller–Trumbore Algorithm)
// ============================================================================

/**
 * @brief Intersects a ray with a triangle.
 *
 * Uses the Möller–Trumbore algorithm for fast ray-triangle intersection.
 * Returns barycentric coordinates in uv field.
 *
 * @param ray The ray
 * @param triangle The triangle
 * @param max_distance Maximum distance to check
 * @param cull_backface If true, only front-facing triangles are hit
 * @return Hit result if intersection found
 */
[[nodiscard]] inline RayHit intersect(const Ray& ray,
                                      const Triangle& triangle,
                                      float max_distance = std::numeric_limits<float>::max(),
                                      bool cull_backface = false) noexcept {
    constexpr float epsilon = 1e-8f;

    Vec3f edge1 = triangle.edge01();
    Vec3f edge2 = triangle.edge02();

    Vec3f h = ray.direction().cross(edge2);
    float a = edge1.dot(h);

    // Check if ray is parallel to triangle
    if (a > -epsilon && a < epsilon) {
        return RayHit::none();
    }

    // Backface culling
    if (cull_backface && a < 0.0f) {
        return RayHit::none();
    }

    float f = 1.0f / a;
    Vec3f s = ray.origin() - triangle.v0;
    float u = f * s.dot(h);

    if (u < 0.0f || u > 1.0f) {
        return RayHit::none();
    }

    Vec3f q = s.cross(edge1);
    float v = f * ray.direction().dot(q);

    if (v < 0.0f || u + v > 1.0f) {
        return RayHit::none();
    }

    float t = f * edge2.dot(q);

    if (t < epsilon || t > max_distance) {
        return RayHit::none();
    }

    RayHit hit;
    hit.distance = t;
    hit.point = ray.getPoint(t);
    hit.normal = a > 0.0f ? triangle.unitNormal() : -triangle.unitNormal();
    hit.uv = Vec2f(u, v);  // Barycentric coordinates (w = 1 - u - v)

    return hit;
}

// ============================================================================
// Fast Intersection Tests (bool only, for culling)
// ============================================================================

/**
 * @brief Fast ray-sphere intersection test (no hit info).
 */
[[nodiscard]] inline bool intersects(const Ray& ray,
                                     const Sphere& sphere,
                                     float max_distance = std::numeric_limits<float>::max()) noexcept {
    Vec3f oc = ray.origin() - sphere.center();
    float b = oc.dot(ray.direction());
    float c = oc.dot(oc) - sphere.radius() * sphere.radius();

    if (c > 0.0f && b > 0.0f) {
        return false;
    }

    float discriminant = b * b - c;
    if (discriminant < 0.0f) {
        return false;
    }

    float t = -b - std::sqrt(discriminant);
    if (t < 0.0f) {
        t = -b + std::sqrt(discriminant);
    }

    return t >= 0.0f && t <= max_distance;
}

/**
 * @brief Fast ray-AABB intersection test (no hit info).
 *
 * Optimized version that only checks for intersection existence.
 */
[[nodiscard]] inline bool intersects(const Ray& ray,
                                     const Aabb& aabb,
                                     float max_distance = std::numeric_limits<float>::max()) noexcept {
    Vec3f inv_dir(1.0f / ray.direction().x(), 1.0f / ray.direction().y(), 1.0f / ray.direction().z());

    float tx1 = (aabb.min().x() - ray.origin().x()) * inv_dir.x();
    float tx2 = (aabb.max().x() - ray.origin().x()) * inv_dir.x();
    float t_min = min(tx1, tx2);
    float t_max = max(tx1, tx2);

    float ty1 = (aabb.min().y() - ray.origin().y()) * inv_dir.y();
    float ty2 = (aabb.max().y() - ray.origin().y()) * inv_dir.y();
    t_min = max(t_min, min(ty1, ty2));
    t_max = min(t_max, max(ty1, ty2));

    float tz1 = (aabb.min().z() - ray.origin().z()) * inv_dir.z();
    float tz2 = (aabb.max().z() - ray.origin().z()) * inv_dir.z();
    t_min = max(t_min, min(tz1, tz2));
    t_max = min(t_max, max(tz1, tz2));

    return t_max >= max(0.0f, t_min) && t_min <= max_distance;
}

/**
 * @brief Fast ray-plane intersection test (no hit info).
 */
[[nodiscard]] inline bool intersects(const Ray& ray,
                                     const Plane& plane,
                                     float max_distance = std::numeric_limits<float>::max()) noexcept {
    float denom = plane.normal.dot(ray.direction());
    if (isZero(denom)) {
        return false;
    }

    float t = -(plane.normal.dot(ray.origin()) + plane.d) / denom;
    return t >= 0.0f && t <= max_distance;
}

/**
 * @brief Fast ray-triangle intersection test (no hit info).
 */
[[nodiscard]] inline bool intersects(const Ray& ray,
                                     const Triangle& triangle,
                                     float max_distance = std::numeric_limits<float>::max(),
                                     bool cull_backface = false) noexcept {
    return intersect(ray, triangle, max_distance, cull_backface).valid();
}

// ============================================================================
// Distance Functions
// ============================================================================

/**
 * @brief Computes the distance from a ray to a point.
 */
[[nodiscard]] inline float distance(const Ray& ray, const Vec3f& point) noexcept {
    return ray.distanceToPoint(point);
}

/**
 * @brief Computes the distance from a point to a plane.
 */
[[nodiscard]] inline float distance(const Vec3f& point, const Plane& plane) noexcept {
    return plane.signedDistance(point);
}

/**
 * @brief Computes the distance from a point to a sphere surface.
 */
[[nodiscard]] inline float distance(const Vec3f& point, const Sphere& sphere) noexcept {
    return sphere.signedDistanceToPoint(point);
}

/**
 * @brief Computes the distance from a point to an AABB.
 */
[[nodiscard]] inline float distance(const Vec3f& point, const Aabb& aabb) noexcept {
    return std::sqrt(aabb.squaredDistanceToPoint(point));
}

/**
 * @brief Computes the distance from a point to a triangle.
 */
[[nodiscard]] inline float distance(const Vec3f& point, const Triangle& triangle) noexcept {
    return triangle.distanceToPoint(point);
}

}  // namespace vne::math

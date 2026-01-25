/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 * ----------------------------------------------------------------------
 */

#include <gtest/gtest.h>
#include <vertexnova/math/geometry/intersection.h>

using namespace vne::math;

// ============================================================================
// Ray-Plane Intersection Tests
// ============================================================================

TEST(RayPlaneTest, DirectHit) {
    Ray ray(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.0f, 0.0f, -1.0f));
    Plane plane(Vec3f(0.0f, 0.0f, 1.0f), 5.0f);  // z = -5

    RayHit hit = intersect(ray, plane);
    EXPECT_TRUE(hit.valid());
    EXPECT_NEAR(hit.distance, 5.0f, 1e-5f);
    EXPECT_NEAR(hit.point.z(), -5.0f, 1e-5f);
}

TEST(RayPlaneTest, ParallelRay) {
    Ray ray(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(1.0f, 0.0f, 0.0f));
    Plane plane(Vec3f(0.0f, 0.0f, 1.0f), 5.0f);

    RayHit hit = intersect(ray, plane);
    EXPECT_FALSE(hit.valid());
}

TEST(RayPlaneTest, BehindRay) {
    Ray ray(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.0f, 0.0f, 1.0f));  // Pointing away
    Plane plane(Vec3f(0.0f, 0.0f, 1.0f), 5.0f);                 // z = -5, behind ray

    RayHit hit = intersect(ray, plane);
    EXPECT_FALSE(hit.valid());
}

// ============================================================================
// Ray-Sphere Intersection Tests
// ============================================================================

TEST(RaySphereTest, DirectHit) {
    Ray ray(Vec3f(0.0f, 0.0f, 10.0f), Vec3f(0.0f, 0.0f, -1.0f));
    Sphere sphere(Vec3f(0.0f, 0.0f, 0.0f), 2.0f);

    RayHit hit = intersect(ray, sphere);
    EXPECT_TRUE(hit.valid());
    EXPECT_NEAR(hit.distance, 8.0f, 1e-5f);  // 10 - 2 = 8
    EXPECT_NEAR(hit.point.z(), 2.0f, 1e-5f);
    EXPECT_NEAR(hit.normal.z(), 1.0f, 1e-5f);  // Normal points towards ray
}

TEST(RaySphereTest, Miss) {
    Ray ray(Vec3f(10.0f, 0.0f, 10.0f), Vec3f(0.0f, 0.0f, -1.0f));  // Offset in X
    Sphere sphere(Vec3f(0.0f, 0.0f, 0.0f), 2.0f);

    RayHit hit = intersect(ray, sphere);
    EXPECT_FALSE(hit.valid());
}

TEST(RaySphereTest, InsideSphere) {
    Ray ray(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.0f, 0.0f, 1.0f));  // From center
    Sphere sphere(Vec3f(0.0f, 0.0f, 0.0f), 2.0f);

    RayHit hit = intersect(ray, sphere);
    EXPECT_TRUE(hit.valid());
    EXPECT_NEAR(hit.distance, 2.0f, 1e-5f);  // Far intersection
}

TEST(RaySphereTest, Tangent) {
    Ray ray(Vec3f(2.0f, 0.0f, 10.0f), Vec3f(0.0f, 0.0f, -1.0f));  // Just touches edge
    Sphere sphere(Vec3f(0.0f, 0.0f, 0.0f), 2.0f);

    RayHit hit = intersect(ray, sphere);
    EXPECT_TRUE(hit.valid());
    EXPECT_NEAR(hit.point.x(), 2.0f, 1e-5f);
}

// ============================================================================
// Ray-AABB Intersection Tests
// ============================================================================

TEST(RayAabbTest, DirectHit) {
    Ray ray(Vec3f(0.0f, 0.0f, 10.0f), Vec3f(0.0f, 0.0f, -1.0f));
    Aabb aabb(Vec3f(-1.0f, -1.0f, -1.0f), Vec3f(1.0f, 1.0f, 1.0f));

    RayHit hit = intersect(ray, aabb);
    EXPECT_TRUE(hit.valid());
    EXPECT_NEAR(hit.distance, 9.0f, 1e-5f);  // 10 - 1 = 9
    EXPECT_NEAR(hit.point.z(), 1.0f, 1e-5f);
    EXPECT_NEAR(hit.normal.z(), 1.0f, 1e-5f);
}

TEST(RayAabbTest, Miss) {
    Ray ray(Vec3f(10.0f, 10.0f, 10.0f), Vec3f(0.0f, 0.0f, -1.0f));  // Way off
    Aabb aabb(Vec3f(-1.0f, -1.0f, -1.0f), Vec3f(1.0f, 1.0f, 1.0f));

    RayHit hit = intersect(ray, aabb);
    EXPECT_FALSE(hit.valid());
}

TEST(RayAabbTest, InsideBox) {
    Ray ray(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.0f, 0.0f, 1.0f));  // From center
    Aabb aabb(Vec3f(-1.0f, -1.0f, -1.0f), Vec3f(1.0f, 1.0f, 1.0f));

    RayHit hit = intersect(ray, aabb);
    EXPECT_TRUE(hit.valid());
    EXPECT_NEAR(hit.distance, 1.0f, 1e-5f);
}

TEST(RayAabbTest, EdgeHit) {
    // Hit from side
    Ray ray(Vec3f(10.0f, 0.0f, 0.0f), Vec3f(-1.0f, 0.0f, 0.0f));
    Aabb aabb(Vec3f(-1.0f, -1.0f, -1.0f), Vec3f(1.0f, 1.0f, 1.0f));

    RayHit hit = intersect(ray, aabb);
    EXPECT_TRUE(hit.valid());
    EXPECT_NEAR(hit.distance, 9.0f, 1e-5f);
    EXPECT_NEAR(hit.normal.x(), 1.0f, 1e-5f);  // +X face
}

// ============================================================================
// Ray-Triangle Intersection Tests
// ============================================================================

TEST(RayTriangleTest, DirectHit) {
    Triangle tri(Vec3f(-1.0f, -1.0f, 0.0f), Vec3f(1.0f, -1.0f, 0.0f), Vec3f(0.0f, 1.0f, 0.0f));

    Ray ray(Vec3f(0.0f, 0.0f, 10.0f), Vec3f(0.0f, 0.0f, -1.0f));

    RayHit hit = intersect(ray, tri);
    EXPECT_TRUE(hit.valid());
    EXPECT_NEAR(hit.distance, 10.0f, 1e-5f);
    EXPECT_NEAR(hit.point.z(), 0.0f, 1e-5f);
}

TEST(RayTriangleTest, Miss) {
    Triangle tri(Vec3f(-1.0f, -1.0f, 0.0f), Vec3f(1.0f, -1.0f, 0.0f), Vec3f(0.0f, 1.0f, 0.0f));

    Ray ray(Vec3f(10.0f, 10.0f, 10.0f), Vec3f(0.0f, 0.0f, -1.0f));  // Off to side

    RayHit hit = intersect(ray, tri);
    EXPECT_FALSE(hit.valid());
}

TEST(RayTriangleTest, BackfaceCulling) {
    Triangle tri(Vec3f(-1.0f, -1.0f, 0.0f), Vec3f(1.0f, -1.0f, 0.0f), Vec3f(0.0f, 1.0f, 0.0f));

    // Ray from behind
    Ray ray(Vec3f(0.0f, 0.0f, -10.0f), Vec3f(0.0f, 0.0f, 1.0f));

    // With culling: should miss
    RayHit hit_culled = intersect(ray, tri, std::numeric_limits<float>::max(), true);
    EXPECT_FALSE(hit_culled.valid());

    // Without culling: should hit
    RayHit hit_no_cull = intersect(ray, tri, std::numeric_limits<float>::max(), false);
    EXPECT_TRUE(hit_no_cull.valid());
}

TEST(RayTriangleTest, BarycentricCoords) {
    Triangle tri(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(1.0f, 0.0f, 0.0f), Vec3f(0.0f, 1.0f, 0.0f));

    // Ray through center
    Ray ray(Vec3f(0.25f, 0.25f, 10.0f), Vec3f(0.0f, 0.0f, -1.0f));

    RayHit hit = intersect(ray, tri);
    EXPECT_TRUE(hit.valid());

    // Check barycentric coords
    float u = hit.uv.x();
    float v = hit.uv.y();
    float w = 1.0f - u - v;

    EXPECT_GT(u, 0.0f);
    EXPECT_GT(v, 0.0f);
    EXPECT_GT(w, 0.0f);
    EXPECT_NEAR(u + v + w, 1.0f, 1e-5f);
}

// ============================================================================
// Fast Intersection Tests
// ============================================================================

TEST(FastIntersectionTest, Sphere) {
    Ray ray(Vec3f(0.0f, 0.0f, 10.0f), Vec3f(0.0f, 0.0f, -1.0f));
    Sphere sphere(Vec3f(0.0f, 0.0f, 0.0f), 2.0f);

    EXPECT_TRUE(intersects(ray, sphere));

    Ray miss_ray(Vec3f(10.0f, 0.0f, 10.0f), Vec3f(0.0f, 0.0f, -1.0f));
    EXPECT_FALSE(intersects(miss_ray, sphere));
}

TEST(FastIntersectionTest, Aabb) {
    Ray ray(Vec3f(0.0f, 0.0f, 10.0f), Vec3f(0.0f, 0.0f, -1.0f));
    Aabb aabb(Vec3f(-1.0f, -1.0f, -1.0f), Vec3f(1.0f, 1.0f, 1.0f));

    EXPECT_TRUE(intersects(ray, aabb));

    Ray miss_ray(Vec3f(10.0f, 10.0f, 10.0f), Vec3f(0.0f, 0.0f, -1.0f));
    EXPECT_FALSE(intersects(miss_ray, aabb));
}

TEST(FastIntersectionTest, MaxDistance) {
    Ray ray(Vec3f(0.0f, 0.0f, 10.0f), Vec3f(0.0f, 0.0f, -1.0f));
    Sphere sphere(Vec3f(0.0f, 0.0f, 0.0f), 2.0f);

    // Distance to sphere is 8, so max_distance of 5 should miss
    EXPECT_FALSE(intersects(ray, sphere, 5.0f));
    EXPECT_TRUE(intersects(ray, sphere, 10.0f));
}

// ============================================================================
// Distance Function Tests
// ============================================================================

TEST(DistanceTest, PointToPlane) {
    Plane plane(Vec3f(0.0f, 1.0f, 0.0f), 0.0f);  // Y = 0

    EXPECT_NEAR(distance(Vec3f(0.0f, 5.0f, 0.0f), plane), 5.0f, 1e-5f);
    EXPECT_NEAR(distance(Vec3f(0.0f, -3.0f, 0.0f), plane), -3.0f, 1e-5f);
}

TEST(DistanceTest, PointToSphere) {
    Sphere sphere(Vec3f(0.0f, 0.0f, 0.0f), 2.0f);

    // Outside
    EXPECT_NEAR(distance(Vec3f(5.0f, 0.0f, 0.0f), sphere), 3.0f, 1e-5f);

    // Inside
    EXPECT_NEAR(distance(Vec3f(1.0f, 0.0f, 0.0f), sphere), -1.0f, 1e-5f);
}

TEST(DistanceTest, PointToAabb) {
    Aabb aabb(Vec3f(-1.0f, -1.0f, -1.0f), Vec3f(1.0f, 1.0f, 1.0f));

    // Outside on one axis
    EXPECT_NEAR(distance(Vec3f(3.0f, 0.0f, 0.0f), aabb), 2.0f, 1e-5f);

    // Inside (returns 0)
    EXPECT_FLOAT_EQ(distance(Vec3f(0.0f, 0.0f, 0.0f), aabb), 0.0f);
}

TEST(DistanceTest, PointToTriangle) {
    Triangle tri(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(1.0f, 0.0f, 0.0f), Vec3f(0.0f, 1.0f, 0.0f));

    // Above triangle center
    EXPECT_NEAR(distance(Vec3f(0.25f, 0.25f, 1.0f), tri), 1.0f, 0.1f);
}

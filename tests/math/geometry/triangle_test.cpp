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

#include <gtest/gtest.h>

#include "vertexnova/math/geometry/triangle.h"

namespace vne::math {

// ============================================================================
// Triangle Tests
// ============================================================================

class TriangleTest : public ::testing::Test {
   protected:
    // Standard right triangle in XY plane
    Triangle tri_{Vec3f(0.0f, 0.0f, 0.0f), Vec3f(3.0f, 0.0f, 0.0f), Vec3f(0.0f, 4.0f, 0.0f)};

    // Equilateral triangle
    Triangle equi_{Vec3f(0.0f, 0.0f, 0.0f), Vec3f(1.0f, 0.0f, 0.0f), Vec3f(0.5f, 0.866025f, 0.0f)};

    // 3D triangle
    Triangle tri3d_{Vec3f(0.0f, 0.0f, 0.0f), Vec3f(1.0f, 0.0f, 0.0f), Vec3f(0.0f, 1.0f, 1.0f)};

    // Degenerate triangle (collinear points)
    Triangle degenerate_{Vec3f(0.0f, 0.0f, 0.0f), Vec3f(1.0f, 0.0f, 0.0f), Vec3f(2.0f, 0.0f, 0.0f)};

    static constexpr float kEps = 1e-5f;
};

// ============================================================================
// Constructor Tests
// ============================================================================

TEST_F(TriangleTest, DefaultConstructor) {
    Triangle t;
    // Just verify it compiles and doesn't crash
    SUCCEED();
}

TEST_F(TriangleTest, ParameterizedConstructor) {
    Triangle t(Vec3f(1.0f, 2.0f, 3.0f), Vec3f(4.0f, 5.0f, 6.0f), Vec3f(7.0f, 8.0f, 9.0f));
    EXPECT_EQ(t.v0, Vec3f(1.0f, 2.0f, 3.0f));
    EXPECT_EQ(t.v1, Vec3f(4.0f, 5.0f, 6.0f));
    EXPECT_EQ(t.v2, Vec3f(7.0f, 8.0f, 9.0f));
}

// ============================================================================
// Geometric Properties Tests
// ============================================================================

TEST_F(TriangleTest, Normal) {
    // Right triangle: (3,0,0) x (0,4,0) = (0,0,12)
    Vec3f n = tri_.normal();
    EXPECT_FLOAT_EQ(n.x(), 0.0f);
    EXPECT_FLOAT_EQ(n.y(), 0.0f);
    EXPECT_FLOAT_EQ(n.z(), 12.0f);
}

TEST_F(TriangleTest, UnitNormal) {
    Vec3f n = tri_.unitNormal();
    EXPECT_NEAR(n.length(), 1.0f, kEps);
    EXPECT_FLOAT_EQ(n.x(), 0.0f);
    EXPECT_FLOAT_EQ(n.y(), 0.0f);
    EXPECT_FLOAT_EQ(n.z(), 1.0f);
}

TEST_F(TriangleTest, Area) {
    // Right triangle with legs 3 and 4 has area = 6
    float area = tri_.area();
    EXPECT_NEAR(area, 6.0f, kEps);
}

TEST_F(TriangleTest, AreaEquilateral) {
    // Equilateral triangle with side 1: area = sqrt(3)/4 ≈ 0.433
    float area = equi_.area();
    EXPECT_NEAR(area, 0.433012f, 0.001f);
}

TEST_F(TriangleTest, AreaDegenerate) {
    // Degenerate triangle has zero area
    float area = degenerate_.area();
    EXPECT_NEAR(area, 0.0f, kEps);
}

TEST_F(TriangleTest, Centroid) {
    Vec3f c = tri_.centroid();
    EXPECT_NEAR(c.x(), 1.0f, kEps);  // (0+3+0)/3 = 1
    EXPECT_NEAR(c.y(), 4.0f / 3.0f, kEps);  // (0+0+4)/3 = 4/3
    EXPECT_NEAR(c.z(), 0.0f, kEps);
}

TEST_F(TriangleTest, Perimeter) {
    // Right triangle: sides are 3, 4, and 5
    float p = tri_.perimeter();
    EXPECT_NEAR(p, 12.0f, kEps);  // 3 + 4 + 5 = 12
}

TEST_F(TriangleTest, PerimeterEquilateral) {
    // Equilateral triangle with side ≈ 1
    float p = equi_.perimeter();
    EXPECT_NEAR(p, 3.0f, 0.01f);
}

// ============================================================================
// Edge Access Tests
// ============================================================================

TEST_F(TriangleTest, Edge01) {
    Vec3f e = tri_.edge01();
    EXPECT_EQ(e, Vec3f(3.0f, 0.0f, 0.0f));
}

TEST_F(TriangleTest, Edge02) {
    Vec3f e = tri_.edge02();
    EXPECT_EQ(e, Vec3f(0.0f, 4.0f, 0.0f));
}

TEST_F(TriangleTest, Edge12) {
    Vec3f e = tri_.edge12();
    EXPECT_EQ(e, Vec3f(-3.0f, 4.0f, 0.0f));
}

TEST_F(TriangleTest, Edge20) {
    Vec3f e = tri_.edge20();
    EXPECT_EQ(e, Vec3f(0.0f, -4.0f, 0.0f));
}

// ============================================================================
// Barycentric Coordinates Tests
// ============================================================================

TEST_F(TriangleTest, BarycentricVertex0) {
    Vec3f bary = tri_.barycentric(tri_.v0);
    EXPECT_NEAR(bary.x(), 1.0f, kEps);
    EXPECT_NEAR(bary.y(), 0.0f, kEps);
    EXPECT_NEAR(bary.z(), 0.0f, kEps);
}

TEST_F(TriangleTest, BarycentricVertex1) {
    Vec3f bary = tri_.barycentric(tri_.v1);
    EXPECT_NEAR(bary.x(), 0.0f, kEps);
    EXPECT_NEAR(bary.y(), 1.0f, kEps);
    EXPECT_NEAR(bary.z(), 0.0f, kEps);
}

TEST_F(TriangleTest, BarycentricVertex2) {
    Vec3f bary = tri_.barycentric(tri_.v2);
    EXPECT_NEAR(bary.x(), 0.0f, kEps);
    EXPECT_NEAR(bary.y(), 0.0f, kEps);
    EXPECT_NEAR(bary.z(), 1.0f, kEps);
}

TEST_F(TriangleTest, BarycentricCentroid) {
    Vec3f bary = tri_.barycentric(tri_.centroid());
    EXPECT_NEAR(bary.x(), 1.0f / 3.0f, kEps);
    EXPECT_NEAR(bary.y(), 1.0f / 3.0f, kEps);
    EXPECT_NEAR(bary.z(), 1.0f / 3.0f, kEps);
}

TEST_F(TriangleTest, BarycentricMidpoint01) {
    Vec3f mid = (tri_.v0 + tri_.v1) * 0.5f;
    Vec3f bary = tri_.barycentric(mid);
    EXPECT_NEAR(bary.x(), 0.5f, kEps);
    EXPECT_NEAR(bary.y(), 0.5f, kEps);
    EXPECT_NEAR(bary.z(), 0.0f, kEps);
}

TEST_F(TriangleTest, BarycentricDegenerate) {
    // Degenerate triangle should return (1/3, 1/3, 1/3)
    Vec3f bary = degenerate_.barycentric(Vec3f(1.0f, 0.0f, 0.0f));
    EXPECT_NEAR(bary.x(), 1.0f / 3.0f, kEps);
    EXPECT_NEAR(bary.y(), 1.0f / 3.0f, kEps);
    EXPECT_NEAR(bary.z(), 1.0f / 3.0f, kEps);
}

TEST_F(TriangleTest, PointFromBarycentric) {
    Vec3f bary(0.25f, 0.5f, 0.25f);
    Vec3f point = tri_.pointFromBarycentric(bary);
    Vec3f expected = tri_.v0 * 0.25f + tri_.v1 * 0.5f + tri_.v2 * 0.25f;
    EXPECT_TRUE(point.areSame(expected, kEps));
}

TEST_F(TriangleTest, InterpolateScalar) {
    Vec3f bary(0.5f, 0.3f, 0.2f);
    float result = Triangle::interpolate(bary, 10.0f, 20.0f, 30.0f);
    // 0.5*10 + 0.3*20 + 0.2*30 = 5 + 6 + 6 = 17
    EXPECT_NEAR(result, 17.0f, kEps);
}

TEST_F(TriangleTest, InterpolateVector) {
    Vec3f bary(0.5f, 0.3f, 0.2f);
    Vec3f a0(1.0f, 0.0f, 0.0f);
    Vec3f a1(0.0f, 1.0f, 0.0f);
    Vec3f a2(0.0f, 0.0f, 1.0f);
    Vec3f result = Triangle::interpolate(bary, a0, a1, a2);
    EXPECT_NEAR(result.x(), 0.5f, kEps);
    EXPECT_NEAR(result.y(), 0.3f, kEps);
    EXPECT_NEAR(result.z(), 0.2f, kEps);
}

// ============================================================================
// Containment Tests
// ============================================================================

TEST_F(TriangleTest, ContainsVertex) {
    EXPECT_TRUE(tri_.contains(tri_.v0));
    EXPECT_TRUE(tri_.contains(tri_.v1));
    EXPECT_TRUE(tri_.contains(tri_.v2));
}

TEST_F(TriangleTest, ContainsCentroid) {
    EXPECT_TRUE(tri_.contains(tri_.centroid()));
}

TEST_F(TriangleTest, ContainsEdgeMidpoint) {
    Vec3f mid = (tri_.v0 + tri_.v1) * 0.5f;
    EXPECT_TRUE(tri_.contains(mid));
}

TEST_F(TriangleTest, ContainsInteriorPoint) {
    // Point at (1, 1, 0) is inside the right triangle
    EXPECT_TRUE(tri_.contains(Vec3f(1.0f, 1.0f, 0.0f)));
}

TEST_F(TriangleTest, ContainsOutsidePoint) {
    // Point outside the triangle
    EXPECT_FALSE(tri_.contains(Vec3f(5.0f, 5.0f, 0.0f)));
    EXPECT_FALSE(tri_.contains(Vec3f(-1.0f, 0.0f, 0.0f)));
    EXPECT_FALSE(tri_.contains(Vec3f(0.0f, -1.0f, 0.0f)));
}

TEST_F(TriangleTest, ContainsWithEpsilon) {
    // Point just outside the triangle edge (barycentric coord slightly negative)
    // Move slightly outside the v0-v1 edge in the -Y direction
    Vec3f slightly_outside = Vec3f(1.0f, -0.0005f, 0.0f);  // Just below the v0-v1 edge

    // With large epsilon, should be considered inside
    EXPECT_TRUE(tri_.contains(slightly_outside, 0.001f));
    // With tiny epsilon, should be outside
    EXPECT_FALSE(tri_.contains(slightly_outside, 0.0001f));
}

TEST_F(TriangleTest, Contains2DVertex) {
    EXPECT_TRUE(tri_.contains2D(Vec2f(tri_.v0.x(), tri_.v0.y())));
    EXPECT_TRUE(tri_.contains2D(Vec2f(tri_.v1.x(), tri_.v1.y())));
    EXPECT_TRUE(tri_.contains2D(Vec2f(tri_.v2.x(), tri_.v2.y())));
}

TEST_F(TriangleTest, Contains2DInterior) {
    EXPECT_TRUE(tri_.contains2D(Vec2f(1.0f, 1.0f)));
}

TEST_F(TriangleTest, Contains2DOutside) {
    EXPECT_FALSE(tri_.contains2D(Vec2f(5.0f, 5.0f)));
    EXPECT_FALSE(tri_.contains2D(Vec2f(-1.0f, 0.0f)));
}

// ============================================================================
// Distance Query Tests
// ============================================================================

TEST_F(TriangleTest, ClosestPointToVertex) {
    Vec3f closest = tri_.closestPoint(tri_.v0);
    EXPECT_TRUE(closest.areSame(tri_.v0, kEps));
}

TEST_F(TriangleTest, ClosestPointToInterior) {
    Vec3f inside = Vec3f(1.0f, 1.0f, 0.0f);
    Vec3f closest = tri_.closestPoint(inside);
    EXPECT_TRUE(closest.areSame(inside, kEps));
}

TEST_F(TriangleTest, ClosestPointToCentroid) {
    Vec3f centroid = tri_.centroid();
    Vec3f closest = tri_.closestPoint(centroid);
    EXPECT_TRUE(closest.areSame(centroid, kEps));
}

TEST_F(TriangleTest, ClosestPointOutsideNearVertex) {
    // Point outside near v0
    Vec3f outside = Vec3f(-1.0f, -1.0f, 0.0f);
    Vec3f closest = tri_.closestPoint(outside);
    EXPECT_TRUE(closest.areSame(tri_.v0, kEps));
}

TEST_F(TriangleTest, ClosestPointOutsideNearEdge) {
    // Point outside near edge v0-v1
    Vec3f outside = Vec3f(1.5f, -1.0f, 0.0f);
    Vec3f closest = tri_.closestPoint(outside);
    // Should be on edge v0-v1
    EXPECT_NEAR(closest.y(), 0.0f, kEps);
    EXPECT_NEAR(closest.z(), 0.0f, kEps);
    EXPECT_GE(closest.x(), 0.0f);
    EXPECT_LE(closest.x(), 3.0f);
}

TEST_F(TriangleTest, ClosestPointAbovePlane) {
    // Point directly above centroid
    Vec3f above = tri_.centroid() + Vec3f(0.0f, 0.0f, 10.0f);
    Vec3f closest = tri_.closestPoint(above);
    EXPECT_TRUE(closest.areSame(tri_.centroid(), kEps));
}

TEST_F(TriangleTest, ClosestPointBelowPlane) {
    // Point directly below centroid
    Vec3f below = tri_.centroid() - Vec3f(0.0f, 0.0f, 10.0f);
    Vec3f closest = tri_.closestPoint(below);
    EXPECT_TRUE(closest.areSame(tri_.centroid(), kEps));
}

TEST_F(TriangleTest, DistanceToInteriorPoint) {
    Vec3f inside = Vec3f(1.0f, 1.0f, 0.0f);
    float dist = tri_.distanceToPoint(inside);
    EXPECT_NEAR(dist, 0.0f, kEps);
}

TEST_F(TriangleTest, DistanceToVertex) {
    float dist = tri_.distanceToPoint(tri_.v0);
    EXPECT_NEAR(dist, 0.0f, kEps);
}

TEST_F(TriangleTest, DistanceAbovePlane) {
    Vec3f above = tri_.centroid() + Vec3f(0.0f, 0.0f, 5.0f);
    float dist = tri_.distanceToPoint(above);
    EXPECT_NEAR(dist, 5.0f, kEps);
}

TEST_F(TriangleTest, SquaredDistanceToPoint) {
    Vec3f above = tri_.centroid() + Vec3f(0.0f, 0.0f, 3.0f);
    float dist_sq = tri_.squaredDistanceToPoint(above);
    EXPECT_NEAR(dist_sq, 9.0f, kEps);
}

TEST_F(TriangleTest, SquaredDistanceConsistency) {
    Vec3f point = Vec3f(5.0f, 5.0f, 5.0f);
    float dist = tri_.distanceToPoint(point);
    float dist_sq = tri_.squaredDistanceToPoint(point);
    EXPECT_NEAR(dist * dist, dist_sq, kEps);
}

// ============================================================================
// Validation Tests
// ============================================================================

TEST_F(TriangleTest, IsValid) {
    EXPECT_TRUE(tri_.isValid());
    EXPECT_TRUE(equi_.isValid());
    EXPECT_TRUE(tri3d_.isValid());
}

TEST_F(TriangleTest, IsDegenerate) {
    EXPECT_FALSE(tri_.isDegenerate());
    EXPECT_FALSE(equi_.isDegenerate());
    EXPECT_TRUE(degenerate_.isDegenerate());
}

TEST_F(TriangleTest, IsDegenerateWithEpsilon) {
    // Very small triangle with edges of length 0.0001
    // Normal = cross(edge01, edge02) has length = 0.0001 * 0.0001 = 1e-8
    // isDegenerate checks: normal.lengthSquared() < epsilon^2
    // So normal.lengthSquared = 1e-16
    Triangle tiny(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.0001f, 0.0f, 0.0f), Vec3f(0.0f, 0.0001f, 0.0f));

    // With epsilon = 0.01, epsilon^2 = 1e-4, and 1e-16 < 1e-4 → degenerate
    EXPECT_TRUE(tiny.isDegenerate(0.01f));

    // With epsilon = 1e-6, epsilon^2 = 1e-12, and 1e-16 < 1e-12 → still degenerate
    EXPECT_TRUE(tiny.isDegenerate(1e-6f));

    // With epsilon = 1e-9, epsilon^2 = 1e-18, and 1e-16 > 1e-18 → NOT degenerate
    EXPECT_FALSE(tiny.isDegenerate(1e-9f));
}

TEST_F(TriangleTest, IsValidConsistency) {
    EXPECT_EQ(tri_.isValid(), !tri_.isDegenerate());
    EXPECT_EQ(degenerate_.isValid(), !degenerate_.isDegenerate());
}

// ============================================================================
// Comparison Tests
// ============================================================================

TEST_F(TriangleTest, EqualityOperator) {
    Triangle t1(Vec3f(1.0f, 2.0f, 3.0f), Vec3f(4.0f, 5.0f, 6.0f), Vec3f(7.0f, 8.0f, 9.0f));
    Triangle t2(Vec3f(1.0f, 2.0f, 3.0f), Vec3f(4.0f, 5.0f, 6.0f), Vec3f(7.0f, 8.0f, 9.0f));
    Triangle t3(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(1.0f, 1.0f, 1.0f), Vec3f(2.0f, 2.0f, 2.0f));

    EXPECT_EQ(t1, t2);
    EXPECT_NE(t1, t3);
}

TEST_F(TriangleTest, AreSameExact) {
    Triangle t1(Vec3f(1.0f, 2.0f, 3.0f), Vec3f(4.0f, 5.0f, 6.0f), Vec3f(7.0f, 8.0f, 9.0f));
    Triangle t2(Vec3f(1.0f, 2.0f, 3.0f), Vec3f(4.0f, 5.0f, 6.0f), Vec3f(7.0f, 8.0f, 9.0f));
    EXPECT_TRUE(t1.areSame(t2, kEps));
}

TEST_F(TriangleTest, AreSameWithEpsilon) {
    Triangle t1(Vec3f(1.0f, 2.0f, 3.0f), Vec3f(4.0f, 5.0f, 6.0f), Vec3f(7.0f, 8.0f, 9.0f));
    Triangle t2(Vec3f(1.0001f, 2.0001f, 3.0001f), Vec3f(4.0001f, 5.0001f, 6.0001f),
                Vec3f(7.0001f, 8.0001f, 9.0001f));
    EXPECT_TRUE(t1.areSame(t2, 0.001f));
    EXPECT_FALSE(t1.areSame(t2, 0.00001f));
}

TEST_F(TriangleTest, AreSameDifferent) {
    Triangle t1(Vec3f(1.0f, 2.0f, 3.0f), Vec3f(4.0f, 5.0f, 6.0f), Vec3f(7.0f, 8.0f, 9.0f));
    Triangle t2(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(1.0f, 1.0f, 1.0f), Vec3f(2.0f, 2.0f, 2.0f));
    EXPECT_FALSE(t1.areSame(t2, kEps));
}

// ============================================================================
// Edge Case Tests
// ============================================================================

TEST_F(TriangleTest, ZeroAreaTriangle) {
    // All three vertices at same point
    Triangle zero(Vec3f(1.0f, 2.0f, 3.0f), Vec3f(1.0f, 2.0f, 3.0f), Vec3f(1.0f, 2.0f, 3.0f));
    EXPECT_NEAR(zero.area(), 0.0f, kEps);
    EXPECT_TRUE(zero.isDegenerate());
}

TEST_F(TriangleTest, CollinearPoints) {
    // Points on a line
    Triangle collinear(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(1.0f, 1.0f, 1.0f), Vec3f(2.0f, 2.0f, 2.0f));
    EXPECT_TRUE(collinear.isDegenerate());
    EXPECT_NEAR(collinear.area(), 0.0f, kEps);
}

TEST_F(TriangleTest, VeryLargeTriangle) {
    Triangle large(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(1000.0f, 0.0f, 0.0f), Vec3f(0.0f, 1000.0f, 0.0f));
    EXPECT_FALSE(large.isDegenerate());
    EXPECT_GT(large.area(), 0.0f);
    EXPECT_NEAR(large.area(), 500000.0f, 1.0f);
}

TEST_F(TriangleTest, NegativeCoordinates) {
    Triangle neg(Vec3f(-1.0f, -1.0f, -1.0f), Vec3f(-2.0f, -1.0f, -1.0f), Vec3f(-1.0f, -2.0f, -1.0f));
    EXPECT_FALSE(neg.isDegenerate());
    EXPECT_GT(neg.area(), 0.0f);
}

TEST_F(TriangleTest, 3DTriangleClosestPoint) {
    // Test closest point for true 3D triangle
    Vec3f closest = tri3d_.closestPoint(tri3d_.centroid());
    EXPECT_TRUE(closest.areSame(tri3d_.centroid(), kEps));
}

TEST_F(TriangleTest, PerimeterConsistency) {
    // Perimeter should be sum of edge lengths
    float edge01_len = tri_.edge01().length();
    float edge12_len = tri_.edge12().length();
    float edge20_len = tri_.edge20().length();
    float expected = edge01_len + edge12_len + edge20_len;
    EXPECT_NEAR(tri_.perimeter(), expected, kEps);
}

}  // namespace vne::math

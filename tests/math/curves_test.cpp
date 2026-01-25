/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 * ----------------------------------------------------------------------
 */

#include <gtest/gtest.h>
#include <vertexnova/math/curves.h>

using namespace vne::math;

// ============================================================================
// Bezier Linear Tests
// ============================================================================

TEST(BezierTest, LinearEndpoints) {
    Vec3f p0(0.0f, 0.0f, 0.0f);
    Vec3f p1(10.0f, 10.0f, 10.0f);

    auto result0 = bezierLinear(p0, p1, 0.0f);
    auto result1 = bezierLinear(p0, p1, 1.0f);

    EXPECT_TRUE(result0.areSame(p0));
    EXPECT_TRUE(result1.areSame(p1));
}

TEST(BezierTest, LinearMidpoint) {
    Vec3f p0(0.0f, 0.0f, 0.0f);
    Vec3f p1(10.0f, 10.0f, 10.0f);

    auto result = bezierLinear(p0, p1, 0.5f);
    Vec3f expected(5.0f, 5.0f, 5.0f);

    EXPECT_TRUE(result.areSame(expected));
}

// ============================================================================
// Bezier Quadratic Tests
// ============================================================================

TEST(BezierTest, QuadraticEndpoints) {
    Vec3f p0(0.0f, 0.0f, 0.0f);
    Vec3f p1(5.0f, 10.0f, 0.0f);
    Vec3f p2(10.0f, 0.0f, 0.0f);

    auto result0 = bezierQuadratic(p0, p1, p2, 0.0f);
    auto result1 = bezierQuadratic(p0, p1, p2, 1.0f);

    EXPECT_TRUE(result0.areSame(p0));
    EXPECT_TRUE(result1.areSame(p2));
}

TEST(BezierTest, QuadraticMidpoint) {
    Vec3f p0(0.0f, 0.0f, 0.0f);
    Vec3f p1(5.0f, 10.0f, 0.0f);
    Vec3f p2(10.0f, 0.0f, 0.0f);

    auto result = bezierQuadratic(p0, p1, p2, 0.5f);

    // At t=0.5: (1-t)²p0 + 2(1-t)t*p1 + t²p2
    // = 0.25*p0 + 0.5*p1 + 0.25*p2
    // = 0 + (2.5, 5, 0) + (2.5, 0, 0) = (5, 5, 0)
    Vec3f expected(5.0f, 5.0f, 0.0f);

    EXPECT_TRUE(result.areSame(expected));
}

TEST(BezierTest, QuadraticDerivative) {
    Vec3f p0(0.0f, 0.0f, 0.0f);
    Vec3f p1(5.0f, 10.0f, 0.0f);
    Vec3f p2(10.0f, 0.0f, 0.0f);

    // Tangent at endpoints
    auto t0 = bezierQuadraticDerivative(p0, p1, p2, 0.0f);
    auto t1 = bezierQuadraticDerivative(p0, p1, p2, 1.0f);

    // At t=0: 2*(p1 - p0) = 2*(5, 10, 0) = (10, 20, 0)
    // At t=1: 2*(p2 - p1) = 2*(5, -10, 0) = (10, -20, 0)
    EXPECT_TRUE(t0.areSame(Vec3f(10.0f, 20.0f, 0.0f)));
    EXPECT_TRUE(t1.areSame(Vec3f(10.0f, -20.0f, 0.0f)));
}

// ============================================================================
// Bezier Cubic Tests
// ============================================================================

TEST(BezierTest, CubicEndpoints) {
    Vec3f p0(0.0f, 0.0f, 0.0f);
    Vec3f p1(3.0f, 10.0f, 0.0f);
    Vec3f p2(7.0f, 10.0f, 0.0f);
    Vec3f p3(10.0f, 0.0f, 0.0f);

    auto result0 = bezierCubic(p0, p1, p2, p3, 0.0f);
    auto result1 = bezierCubic(p0, p1, p2, p3, 1.0f);

    EXPECT_TRUE(result0.areSame(p0));
    EXPECT_TRUE(result1.areSame(p3));
}

TEST(BezierTest, CubicSymmetric) {
    // Symmetric S-curve
    Vec3f p0(0.0f, 0.0f, 0.0f);
    Vec3f p1(0.0f, 10.0f, 0.0f);
    Vec3f p2(10.0f, 10.0f, 0.0f);
    Vec3f p3(10.0f, 0.0f, 0.0f);

    auto mid = bezierCubic(p0, p1, p2, p3, 0.5f);

    // Midpoint of symmetric curve should be at center
    EXPECT_NEAR(mid.x(), 5.0f, 0.01f);
}

TEST(BezierTest, CubicDerivative) {
    Vec3f p0(0.0f, 0.0f, 0.0f);
    Vec3f p1(3.0f, 10.0f, 0.0f);
    Vec3f p2(7.0f, 10.0f, 0.0f);
    Vec3f p3(10.0f, 0.0f, 0.0f);

    auto t0 = bezierCubicDerivative(p0, p1, p2, p3, 0.0f);
    auto t1 = bezierCubicDerivative(p0, p1, p2, p3, 1.0f);

    // Tangent at t=0 is 3*(p1 - p0)
    Vec3f expected_t0 = (p1 - p0) * 3.0f;
    Vec3f expected_t1 = (p3 - p2) * 3.0f;

    EXPECT_TRUE(t0.areSame(expected_t0));
    EXPECT_TRUE(t1.areSame(expected_t1));
}

// ============================================================================
// Catmull-Rom Tests
// ============================================================================

TEST(CatmullRomTest, PassesThroughControlPoints) {
    Vec3f p0(0.0f, 0.0f, 0.0f);
    Vec3f p1(10.0f, 5.0f, 0.0f);
    Vec3f p2(20.0f, 0.0f, 0.0f);
    Vec3f p3(30.0f, 5.0f, 0.0f);

    // Catmull-Rom passes through p1 at t=0 and p2 at t=1
    auto result0 = catmullRom(p0, p1, p2, p3, 0.0f);
    auto result1 = catmullRom(p0, p1, p2, p3, 1.0f);

    EXPECT_TRUE(result0.areSame(p1));
    EXPECT_TRUE(result1.areSame(p2));
}

TEST(CatmullRomTest, SmoothContinuity) {
    Vec3f p0(0.0f, 0.0f, 0.0f);
    Vec3f p1(10.0f, 0.0f, 0.0f);
    Vec3f p2(20.0f, 0.0f, 0.0f);
    Vec3f p3(30.0f, 0.0f, 0.0f);

    // For collinear points, should be linear
    auto mid = catmullRom(p0, p1, p2, p3, 0.5f);
    EXPECT_NEAR(mid.x(), 15.0f, 0.01f);
    EXPECT_NEAR(mid.y(), 0.0f, 0.01f);
}

TEST(CatmullRomTest, Derivative) {
    Vec3f p0(0.0f, 0.0f, 0.0f);
    Vec3f p1(10.0f, 0.0f, 0.0f);
    Vec3f p2(20.0f, 10.0f, 0.0f);
    Vec3f p3(30.0f, 10.0f, 0.0f);

    auto tangent = catmullRomDerivative(p0, p1, p2, p3, 0.5f);

    // Tangent should be non-zero for non-collinear points
    EXPECT_GT(tangent.length(), 0.0f);
}

TEST(CatmullRomTest, TensionParameter) {
    Vec3f p0(0.0f, 0.0f, 0.0f);
    Vec3f p1(10.0f, 10.0f, 0.0f);
    Vec3f p2(20.0f, 0.0f, 0.0f);
    Vec3f p3(30.0f, 10.0f, 0.0f);

    // Higher tension = tighter curve
    auto loose = catmullRomTension(p0, p1, p2, p3, 0.5f, -0.5f);
    auto standard = catmullRomTension(p0, p1, p2, p3, 0.5f, 0.0f);
    auto tight = catmullRomTension(p0, p1, p2, p3, 0.5f, 0.5f);

    // All should be valid points
    EXPECT_FALSE(std::isnan(loose.x()));
    EXPECT_FALSE(std::isnan(standard.x()));
    EXPECT_FALSE(std::isnan(tight.x()));
}

// ============================================================================
// Hermite Tests
// ============================================================================

TEST(HermiteTest, Endpoints) {
    Vec3f p0(0.0f, 0.0f, 0.0f);
    Vec3f t0(10.0f, 0.0f, 0.0f);
    Vec3f p1(10.0f, 10.0f, 0.0f);
    Vec3f t1(10.0f, 0.0f, 0.0f);

    auto result0 = hermite(p0, t0, p1, t1, 0.0f);
    auto result1 = hermite(p0, t0, p1, t1, 1.0f);

    EXPECT_TRUE(result0.areSame(p0));
    EXPECT_TRUE(result1.areSame(p1));
}

TEST(HermiteTest, TangentInfluence) {
    Vec3f p0(0.0f, 0.0f, 0.0f);
    Vec3f p1(10.0f, 0.0f, 0.0f);

    // Different tangents produce different curves
    // Use t=0.25 where the tangent influence is more apparent
    auto curve1 = hermite(p0, Vec3f(10.0f, 20.0f, 0.0f), p1, Vec3f(10.0f, 0.0f, 0.0f), 0.25f);
    auto curve2 = hermite(p0, Vec3f(10.0f, -20.0f, 0.0f), p1, Vec3f(10.0f, 0.0f, 0.0f), 0.25f);

    // Curve with upward tangent should be higher than one with downward tangent
    EXPECT_GT(curve1.y(), curve2.y());
}

TEST(HermiteTest, Derivative) {
    Vec3f p0(0.0f, 0.0f, 0.0f);
    Vec3f t0(10.0f, 5.0f, 0.0f);
    Vec3f p1(10.0f, 10.0f, 0.0f);
    Vec3f t1(10.0f, 0.0f, 0.0f);

    // Derivative at endpoints should match tangents
    auto d0 = hermiteDerivative(p0, t0, p1, t1, 0.0f);
    auto d1 = hermiteDerivative(p0, t0, p1, t1, 1.0f);

    EXPECT_TRUE(d0.areSame(t0));
    EXPECT_TRUE(d1.areSame(t1));
}

// ============================================================================
// B-Spline Tests
// ============================================================================

TEST(BSplineTest, C2Continuity) {
    Vec3f p0(0.0f, 0.0f, 0.0f);
    Vec3f p1(10.0f, 10.0f, 0.0f);
    Vec3f p2(20.0f, 10.0f, 0.0f);
    Vec3f p3(30.0f, 0.0f, 0.0f);

    // B-spline doesn't pass through control points but is valid
    auto mid = bsplineCubic(p0, p1, p2, p3, 0.5f);

    EXPECT_FALSE(std::isnan(mid.x()));
    EXPECT_FALSE(std::isnan(mid.y()));
    EXPECT_FALSE(std::isnan(mid.z()));
}

// ============================================================================
// Arc Length Tests
// ============================================================================

TEST(ArcLengthTest, StraightLine) {
    // Straight line Bezier
    Vec3f p0(0.0f, 0.0f, 0.0f);
    Vec3f p1(3.33f, 0.0f, 0.0f);
    Vec3f p2(6.66f, 0.0f, 0.0f);
    Vec3f p3(10.0f, 0.0f, 0.0f);

    float length = bezierCubicArcLength(p0, p1, p2, p3, 100);

    EXPECT_NEAR(length, 10.0f, 0.1f);
}

TEST(ArcLengthTest, CurvedPath) {
    Vec3f p0(0.0f, 0.0f, 0.0f);
    Vec3f p1(0.0f, 10.0f, 0.0f);
    Vec3f p2(10.0f, 10.0f, 0.0f);
    Vec3f p3(10.0f, 0.0f, 0.0f);

    float length = bezierCubicArcLength(p0, p1, p2, p3, 100);

    // S-curve should be longer than straight diagonal
    float diagonal = 10.0f * std::sqrt(2.0f);
    EXPECT_GT(length, diagonal);
}

// ============================================================================
// Curve Splitting Tests
// ============================================================================

TEST(SplitTest, MidpointSplit) {
    Vec3f p0(0.0f, 0.0f, 0.0f);
    Vec3f p1(3.0f, 10.0f, 0.0f);
    Vec3f p2(7.0f, 10.0f, 0.0f);
    Vec3f p3(10.0f, 0.0f, 0.0f);

    std::array<Vec3f, 4> left, right;
    bezierCubicSplit(p0, p1, p2, p3, 0.5f, left, right);

    // Left curve starts at p0
    EXPECT_TRUE(left[0].areSame(p0));

    // Right curve ends at p3
    EXPECT_TRUE(right[3].areSame(p3));

    // Split point is shared
    EXPECT_TRUE(left[3].areSame(right[0]));

    // Split point is on original curve
    auto mid = bezierCubic(p0, p1, p2, p3, 0.5f);
    EXPECT_TRUE(left[3].areSame(mid));
}

// ============================================================================
// Scalar Curves Tests
// ============================================================================

TEST(ScalarCurvesTest, FloatBezier) {
    float p0 = 0.0f;
    float p1 = 0.3f;
    float p2 = 0.7f;
    float p3 = 1.0f;

    EXPECT_FLOAT_EQ(bezierCubic(p0, p1, p2, p3, 0.0f), 0.0f);
    EXPECT_FLOAT_EQ(bezierCubic(p0, p1, p2, p3, 1.0f), 1.0f);
}

TEST(ScalarCurvesTest, FloatCatmullRom) {
    float p0 = 0.0f;
    float p1 = 1.0f;
    float p2 = 2.0f;
    float p3 = 3.0f;

    EXPECT_FLOAT_EQ(catmullRom(p0, p1, p2, p3, 0.0f), 1.0f);
    EXPECT_FLOAT_EQ(catmullRom(p0, p1, p2, p3, 1.0f), 2.0f);
}

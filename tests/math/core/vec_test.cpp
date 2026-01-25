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

#include "vertexnova/math/core/vec.h"

#include <sstream>

namespace vne::math {

// ============================================================================
// Vec2 Tests
// ============================================================================

class Vec2Test : public ::testing::Test {
   protected:
    Vec2f v1_{1.0f, 2.0f};
    Vec2f v2_{3.0f, 4.0f};
};

TEST_F(Vec2Test, DefaultConstructor) {
    Vec2f v;
    EXPECT_FLOAT_EQ(v.x(), 0.0f);
    EXPECT_FLOAT_EQ(v.y(), 0.0f);
}

TEST_F(Vec2Test, ScalarConstructor) {
    Vec2f v(5.0f);
    EXPECT_FLOAT_EQ(v.x(), 5.0f);
    EXPECT_FLOAT_EQ(v.y(), 5.0f);
}

TEST_F(Vec2Test, ComponentConstructor) {
    EXPECT_FLOAT_EQ(v1_.x(), 1.0f);
    EXPECT_FLOAT_EQ(v1_.y(), 2.0f);
}

TEST_F(Vec2Test, Dimensions) {
    EXPECT_EQ(Vec2f::dim(), 2u);
    EXPECT_EQ(Vec2f::size(), 2u);
}

TEST_F(Vec2Test, GetPtr) {
    float* ptr = v1_.getPtr();
    EXPECT_FLOAT_EQ(ptr[0], 1.0f);
    EXPECT_FLOAT_EQ(ptr[1], 2.0f);
}

TEST_F(Vec2Test, Addition) {
    Vec2f result = v1_ + v2_;
    EXPECT_FLOAT_EQ(result.x(), 4.0f);
    EXPECT_FLOAT_EQ(result.y(), 6.0f);

    Vec2f scalar_result = v1_ + 1.0f;
    EXPECT_FLOAT_EQ(scalar_result.x(), 2.0f);
    EXPECT_FLOAT_EQ(scalar_result.y(), 3.0f);
}

TEST_F(Vec2Test, Subtraction) {
    Vec2f result = v2_ - v1_;
    EXPECT_FLOAT_EQ(result.x(), 2.0f);
    EXPECT_FLOAT_EQ(result.y(), 2.0f);

    Vec2f scalar_result = v1_ - 1.0f;
    EXPECT_FLOAT_EQ(scalar_result.x(), 0.0f);
    EXPECT_FLOAT_EQ(scalar_result.y(), 1.0f);
}

TEST_F(Vec2Test, Multiplication) {
    Vec2f result = v1_ * 2.0f;
    EXPECT_FLOAT_EQ(result.x(), 2.0f);
    EXPECT_FLOAT_EQ(result.y(), 4.0f);

    Vec2f component_result = v1_ * v2_;
    EXPECT_FLOAT_EQ(component_result.x(), 3.0f);
    EXPECT_FLOAT_EQ(component_result.y(), 8.0f);
}

TEST_F(Vec2Test, Division) {
    Vec2f result = v2_ / 2.0f;
    EXPECT_FLOAT_EQ(result.x(), 1.5f);
    EXPECT_FLOAT_EQ(result.y(), 2.0f);

    Vec2f component_result = Vec2f(4.0f, 6.0f) / Vec2f(2.0f, 3.0f);
    EXPECT_FLOAT_EQ(component_result.x(), 2.0f);
    EXPECT_FLOAT_EQ(component_result.y(), 2.0f);
}

TEST_F(Vec2Test, DotProduct) {
    float dot = v1_.dot(v2_);
    EXPECT_FLOAT_EQ(dot, 11.0f);  // 1*3 + 2*4 = 11
    EXPECT_FLOAT_EQ(Vec2f::dot(v1_, v2_), 11.0f);
}

TEST_F(Vec2Test, CrossProduct2D) {
    float cross = v1_.cross(v2_);
    EXPECT_FLOAT_EQ(cross, -2.0f);  // 1*4 - 2*3 = -2
}

TEST_F(Vec2Test, Length) {
    Vec2f v(3.0f, 4.0f);
    EXPECT_FLOAT_EQ(v.length(), 5.0f);
    EXPECT_FLOAT_EQ(v.lengthSquare(), 25.0f);
    EXPECT_FLOAT_EQ(v.lengthSquared(), 25.0f);
}

TEST_F(Vec2Test, Normalized) {
    Vec2f v(3.0f, 4.0f);
    Vec2f n = v.normalized();
    EXPECT_FLOAT_EQ(n.x(), 0.6f);
    EXPECT_FLOAT_EQ(n.y(), 0.8f);
    EXPECT_TRUE(n.isNormalized());

    // Test normalize() alias
    Vec2f n2 = v.normalize();
    EXPECT_TRUE(n2.isNormalized());
}

TEST_F(Vec2Test, Abs) {
    Vec2f v(-1.0f, -2.0f);
    Vec2f a = v.abs();
    EXPECT_FLOAT_EQ(a.x(), 1.0f);
    EXPECT_FLOAT_EQ(a.y(), 2.0f);
}

TEST_F(Vec2Test, MinMax) {
    Vec2f a(1.0f, 2.0f);  // length = sqrt(5) ~= 2.24
    Vec2f b(3.0f, 4.0f);  // length = 5

    // min() returns the vector with smaller length
    Vec2f min_result = a.min(b);
    EXPECT_EQ(min_result, a);

    // max() returns the vector with larger length
    Vec2f max_result = a.max(b);
    EXPECT_EQ(max_result, b);

    // componentMin() and componentMax() are component-wise
    Vec2f c(1.0f, 4.0f);
    Vec2f d(3.0f, 2.0f);
    Vec2f comp_min = c.componentMin(d);
    EXPECT_FLOAT_EQ(comp_min.x(), 1.0f);
    EXPECT_FLOAT_EQ(comp_min.y(), 2.0f);

    Vec2f comp_max = c.componentMax(d);
    EXPECT_FLOAT_EQ(comp_max.x(), 3.0f);
    EXPECT_FLOAT_EQ(comp_max.y(), 4.0f);
}

TEST_F(Vec2Test, MinMaxComponent) {
    Vec2f v(1.0f, 3.0f);
    EXPECT_FLOAT_EQ(v.minComponent(), 1.0f);
    EXPECT_FLOAT_EQ(v.maxComponent(), 3.0f);
}

TEST_F(Vec2Test, Distance) {
    Vec2f a(0.0f, 0.0f);
    Vec2f b(3.0f, 4.0f);
    EXPECT_FLOAT_EQ(a.distance(b), 5.0f);
    EXPECT_FLOAT_EQ(Vec2f::distance(a, b), 5.0f);
}

TEST_F(Vec2Test, Reflect) {
    Vec2f incident(1.0f, -1.0f);
    Vec2f normal = Vec2f::yAxis();
    Vec2f reflected = incident.reflect(normal);
    EXPECT_NEAR(reflected.x(), 1.0f, 1e-5f);
    EXPECT_NEAR(reflected.y(), 1.0f, 1e-5f);
}

TEST_F(Vec2Test, Project) {
    Vec2f v(3.0f, 4.0f);
    Vec2f onto = Vec2f::xAxis();
    Vec2f proj = v.project(onto);
    EXPECT_FLOAT_EQ(proj.x(), 3.0f);
    EXPECT_FLOAT_EQ(proj.y(), 0.0f);
}

TEST_F(Vec2Test, Reject) {
    Vec2f v(3.0f, 4.0f);
    Vec2f from = Vec2f::xAxis();
    Vec2f rej = v.reject(from);
    EXPECT_FLOAT_EQ(rej.x(), 0.0f);
    EXPECT_FLOAT_EQ(rej.y(), 4.0f);
}

TEST_F(Vec2Test, DecomposeVec) {
    Vec2f v(3.0f, 4.0f);
    Vec2f ref = Vec2f::xAxis();
    Vec2f proj, perp;
    v.decomposeVec(ref, proj, perp);
    EXPECT_FLOAT_EQ(proj.x(), 3.0f);
    EXPECT_FLOAT_EQ(proj.y(), 0.0f);
    EXPECT_FLOAT_EQ(perp.x(), 0.0f);
    EXPECT_FLOAT_EQ(perp.y(), 4.0f);
}

TEST_F(Vec2Test, Perpendicular) {
    Vec2f v(1.0f, 0.0f);
    Vec2f perp = v.perpendicular();
    EXPECT_FLOAT_EQ(perp.x(), 0.0f);
    EXPECT_FLOAT_EQ(perp.y(), 1.0f);
}

TEST_F(Vec2Test, Rotate) {
    Vec2f v(1.0f, 0.0f);
    Vec2f rotated = v.rotate(Vec2f::zero(), kHalfPiT<float>);
    EXPECT_NEAR(rotated.x(), 0.0f, 1e-5f);
    EXPECT_NEAR(rotated.y(), 1.0f, 1e-5f);
}

TEST_F(Vec2Test, AreSame) {
    Vec2f a(1.0f, 2.0f);
    Vec2f b(1.0f + 1e-7f, 2.0f);
    EXPECT_TRUE(a.areSame(b, 1e-5f));
    EXPECT_TRUE(a.approxEquals(b, 1e-5f));
}

TEST_F(Vec2Test, AreAligned) {
    Vec2f a(1.0f, 0.0f);
    Vec2f b(2.0f, 0.0f);
    EXPECT_TRUE(a.areAligned(b));

    Vec2f c(-1.0f, 0.0f);
    EXPECT_TRUE(a.areAligned(c));
}

TEST_F(Vec2Test, IsZero) {
    Vec2f zero;
    EXPECT_TRUE(zero.isZero());

    Vec2f non_zero(0.001f, 0.0f);
    EXPECT_FALSE(non_zero.isZero());
}

TEST_F(Vec2Test, PolarCoordinates) {
    Vec2f v;
    v.composePolar(5.0f, kHalfPiT<float>);
    EXPECT_NEAR(v.x(), 0.0f, 1e-5f);
    EXPECT_NEAR(v.y(), 5.0f, 1e-5f);

    float radius, angle;
    v.decomposePolar(radius, angle);
    EXPECT_NEAR(radius, 5.0f, 1e-5f);
    EXPECT_NEAR(angle, kHalfPiT<float>, 1e-5f);
}

TEST_F(Vec2Test, Angle) {
    Vec2f a(1.0f, 0.0f);
    Vec2f b(0.0f, 1.0f);
    EXPECT_NEAR(a.angle(b), kHalfPiT<float>, 1e-5f);
    EXPECT_NEAR(a.angle(), 0.0f, 1e-5f);
}

TEST_F(Vec2Test, MidPoint) {
    Vec2f a(0.0f, 0.0f);
    Vec2f b(2.0f, 4.0f);
    Vec2f mid = a.midPoint(b);
    EXPECT_FLOAT_EQ(mid.x(), 1.0f);
    EXPECT_FLOAT_EQ(mid.y(), 2.0f);
}

TEST_F(Vec2Test, Lerp) {
    Vec2f result = v1_.lerp(v2_, 0.5f);
    EXPECT_FLOAT_EQ(result.x(), 2.0f);
    EXPECT_FLOAT_EQ(result.y(), 3.0f);
}

TEST_F(Vec2Test, StaticFactories) {
    EXPECT_EQ(Vec2f::zero(), Vec2f(0.0f, 0.0f));
    EXPECT_EQ(Vec2f::one(), Vec2f(1.0f, 1.0f));
    EXPECT_EQ(Vec2f::xAxis(), Vec2f(1.0f, 0.0f));
    EXPECT_EQ(Vec2f::yAxis(), Vec2f(0.0f, 1.0f));
}

TEST_F(Vec2Test, Comparison) {
    Vec2f a(1.0f, 0.0f);
    Vec2f b(0.0f, 2.0f);
    EXPECT_TRUE(b > a);  // by length
    EXPECT_TRUE(a < b);
    EXPECT_TRUE(v1_ == v1_);
    EXPECT_TRUE(v1_ != v2_);
}

TEST_F(Vec2Test, UnaryMinus) {
    Vec2f neg = -v1_;
    EXPECT_FLOAT_EQ(neg.x(), -1.0f);
    EXPECT_FLOAT_EQ(neg.y(), -2.0f);
}

TEST_F(Vec2Test, StreamOutput) {
    std::ostringstream os;
    os << v1_;
    EXPECT_EQ(os.str(), "(1, 2)");
}

// ============================================================================
// Vec3 Tests
// ============================================================================

class Vec3Test : public ::testing::Test {
   protected:
    Vec3f v1_{1.0f, 2.0f, 3.0f};
    Vec3f v2_{4.0f, 5.0f, 6.0f};
};

TEST_F(Vec3Test, DefaultConstructor) {
    Vec3f v;
    EXPECT_FLOAT_EQ(v.x(), 0.0f);
    EXPECT_FLOAT_EQ(v.y(), 0.0f);
    EXPECT_FLOAT_EQ(v.z(), 0.0f);
}

TEST_F(Vec3Test, ComponentConstructor) {
    EXPECT_FLOAT_EQ(v1_.x(), 1.0f);
    EXPECT_FLOAT_EQ(v1_.y(), 2.0f);
    EXPECT_FLOAT_EQ(v1_.z(), 3.0f);
}

TEST_F(Vec3Test, Dimensions) {
    EXPECT_EQ(Vec3f::dim(), 3u);
    EXPECT_EQ(Vec3f::size(), 3u);
}

TEST_F(Vec3Test, Vec2PlusZConstructor) {
    Vec3f v(Vec2f(1.0f, 2.0f), 3.0f);
    EXPECT_FLOAT_EQ(v.x(), 1.0f);
    EXPECT_FLOAT_EQ(v.y(), 2.0f);
    EXPECT_FLOAT_EQ(v.z(), 3.0f);
}

TEST_F(Vec3Test, Vec2Constructor) {
    Vec3f v(Vec2f(1.0f, 2.0f));
    EXPECT_FLOAT_EQ(v.x(), 1.0f);
    EXPECT_FLOAT_EQ(v.y(), 2.0f);
    EXPECT_FLOAT_EQ(v.z(), 0.0f);
}

TEST_F(Vec3Test, CrossProduct) {
    Vec3f a(1.0f, 0.0f, 0.0f);
    Vec3f b(0.0f, 1.0f, 0.0f);
    Vec3f result = a.cross(b);
    EXPECT_FLOAT_EQ(result.x(), 0.0f);
    EXPECT_FLOAT_EQ(result.y(), 0.0f);
    EXPECT_FLOAT_EQ(result.z(), 1.0f);

    EXPECT_EQ(Vec3f::cross(a, b), result);
}

TEST_F(Vec3Test, DotProduct) {
    float dot = v1_.dot(v2_);
    EXPECT_FLOAT_EQ(dot, 32.0f);  // 1*4 + 2*5 + 3*6 = 32
}

TEST_F(Vec3Test, Swizzle) {
    Vec2f xy = v1_.xy();
    EXPECT_FLOAT_EQ(xy.x(), 1.0f);
    EXPECT_FLOAT_EQ(xy.y(), 2.0f);
}

TEST_F(Vec3Test, DirectionAliases) {
    EXPECT_EQ(Vec3f::up(), Vec3f(0.0f, 1.0f, 0.0f));
    EXPECT_EQ(Vec3f::down(), Vec3f(0.0f, -1.0f, 0.0f));
    EXPECT_EQ(Vec3f::right(), Vec3f(1.0f, 0.0f, 0.0f));
    EXPECT_EQ(Vec3f::left(), Vec3f(-1.0f, 0.0f, 0.0f));
    EXPECT_EQ(Vec3f::forward(), Vec3f(0.0f, 0.0f, 1.0f));
    EXPECT_EQ(Vec3f::backward(), Vec3f(0.0f, 0.0f, -1.0f));
}

TEST_F(Vec3Test, Reflect) {
    Vec3f incident(1.0f, -1.0f, 0.0f);
    Vec3f normal = Vec3f::yAxis();
    Vec3f reflected = incident.reflect(normal);
    EXPECT_NEAR(reflected.x(), 1.0f, 1e-5f);
    EXPECT_NEAR(reflected.y(), 1.0f, 1e-5f);
    EXPECT_NEAR(reflected.z(), 0.0f, 1e-5f);
}

TEST_F(Vec3Test, Rotate) {
    Vec3f v(1.0f, 0.0f, 0.0f);
    Vec3f rotated = v.rotate(Vec3f::zAxis(), kHalfPiT<float>);
    EXPECT_NEAR(rotated.x(), 0.0f, 1e-5f);
    EXPECT_NEAR(rotated.y(), 1.0f, 1e-5f);
    EXPECT_NEAR(rotated.z(), 0.0f, 1e-5f);
}

TEST_F(Vec3Test, SphericalCoordinates) {
    Vec3f v;
    v.composeSpherical(5.0f, 0.0f, kHalfPiT<float>);
    EXPECT_NEAR(v.x(), 5.0f, 1e-5f);
    EXPECT_NEAR(v.y(), 0.0f, 1e-5f);
    EXPECT_NEAR(v.z(), 0.0f, 1e-5f);

    float rho, theta, phi;
    v.decomposeSpherical(rho, theta, phi);
    EXPECT_NEAR(rho, 5.0f, 1e-5f);
}

TEST_F(Vec3Test, CylindricalCoordinates) {
    Vec3f v;
    v.composeCylindrical(3.0f, 0.0f, 4.0f);
    EXPECT_NEAR(v.x(), 3.0f, 1e-5f);
    EXPECT_NEAR(v.y(), 0.0f, 1e-5f);
    EXPECT_NEAR(v.z(), 4.0f, 1e-5f);

    float radius, angle, height;
    v.decomposeCylindrical(radius, angle, height);
    EXPECT_NEAR(radius, 3.0f, 1e-5f);
    EXPECT_NEAR(height, 4.0f, 1e-5f);
}

TEST_F(Vec3Test, Perpendicular) {
    Vec3f a(1.0f, 0.0f, 0.0f);
    Vec3f b(0.0f, 1.0f, 0.0f);
    Vec3f perp = a.perpendicular(b);
    EXPECT_EQ(perp, Vec3f::zAxis());
}

TEST_F(Vec3Test, IsLinearDependent) {
    Vec3f a(1.0f, 0.0f, 0.0f);
    Vec3f b(2.0f, 0.0f, 0.0f);
    EXPECT_TRUE(a.isLinearDependent(b));

    Vec3f c(0.0f, 1.0f, 0.0f);
    EXPECT_FALSE(a.isLinearDependent(c));
}

TEST_F(Vec3Test, AngleTriangle) {
    Vec3f a(0.0f, 0.0f, 0.0f);
    Vec3f b(1.0f, 0.0f, 0.0f);
    Vec3f c(0.0f, 1.0f, 0.0f);
    EXPECT_NEAR(a.angle(b, c), kHalfPiT<float>, 1e-5f);
}

// ============================================================================
// Vec4 Tests
// ============================================================================

class Vec4Test : public ::testing::Test {
   protected:
    Vec4f v1_{1.0f, 2.0f, 3.0f, 4.0f};
};

TEST_F(Vec4Test, DefaultConstructor) {
    Vec4f v;
    EXPECT_FLOAT_EQ(v.x(), 0.0f);
    EXPECT_FLOAT_EQ(v.y(), 0.0f);
    EXPECT_FLOAT_EQ(v.z(), 0.0f);
    EXPECT_FLOAT_EQ(v.w(), 0.0f);
}

TEST_F(Vec4Test, ComponentConstructor) {
    EXPECT_FLOAT_EQ(v1_.x(), 1.0f);
    EXPECT_FLOAT_EQ(v1_.y(), 2.0f);
    EXPECT_FLOAT_EQ(v1_.z(), 3.0f);
    EXPECT_FLOAT_EQ(v1_.w(), 4.0f);
}

TEST_F(Vec4Test, Dimensions) {
    EXPECT_EQ(Vec4f::dim(), 4u);
    EXPECT_EQ(Vec4f::size(), 4u);
}

TEST_F(Vec4Test, Vec3PlusWConstructor) {
    Vec4f v(Vec3f(1.0f, 2.0f, 3.0f), 4.0f);
    EXPECT_FLOAT_EQ(v.x(), 1.0f);
    EXPECT_FLOAT_EQ(v.y(), 2.0f);
    EXPECT_FLOAT_EQ(v.z(), 3.0f);
    EXPECT_FLOAT_EQ(v.w(), 4.0f);
}

TEST_F(Vec4Test, Vec3Constructor) {
    Vec4f v(Vec3f(1.0f, 2.0f, 3.0f));
    EXPECT_FLOAT_EQ(v.x(), 1.0f);
    EXPECT_FLOAT_EQ(v.y(), 2.0f);
    EXPECT_FLOAT_EQ(v.z(), 3.0f);
    EXPECT_FLOAT_EQ(v.w(), 0.0f);
}

TEST_F(Vec4Test, Vec2Constructor) {
    Vec4f v(Vec2f(1.0f, 2.0f));
    EXPECT_FLOAT_EQ(v.x(), 1.0f);
    EXPECT_FLOAT_EQ(v.y(), 2.0f);
    EXPECT_FLOAT_EQ(v.z(), 0.0f);
    EXPECT_FLOAT_EQ(v.w(), 0.0f);
}

TEST_F(Vec4Test, Swizzle) {
    Vec3f xyz = v1_.xyz();
    EXPECT_FLOAT_EQ(xyz.x(), 1.0f);
    EXPECT_FLOAT_EQ(xyz.y(), 2.0f);
    EXPECT_FLOAT_EQ(xyz.z(), 3.0f);

    Vec2f xy = v1_.xy();
    EXPECT_FLOAT_EQ(xy.x(), 1.0f);
    EXPECT_FLOAT_EQ(xy.y(), 2.0f);
}

TEST_F(Vec4Test, StaticFactories) {
    EXPECT_EQ(Vec4f::zero(), Vec4f(0.0f, 0.0f, 0.0f, 0.0f));
    EXPECT_EQ(Vec4f::one(), Vec4f(1.0f, 1.0f, 1.0f, 1.0f));
    EXPECT_EQ(Vec4f::xAxis(), Vec4f(1.0f, 0.0f, 0.0f, 0.0f));
    EXPECT_EQ(Vec4f::yAxis(), Vec4f(0.0f, 1.0f, 0.0f, 0.0f));
    EXPECT_EQ(Vec4f::zAxis(), Vec4f(0.0f, 0.0f, 1.0f, 0.0f));
    EXPECT_EQ(Vec4f::wAxis(), Vec4f(0.0f, 0.0f, 0.0f, 1.0f));
}

TEST_F(Vec4Test, Rotate) {
    Vec4f v(1.0f, 0.0f, 0.0f, 1.0f);
    Vec4f rotated = v.rotate(Vec3f::zAxis(), kHalfPiT<float>);
    EXPECT_NEAR(rotated.x(), 0.0f, 1e-5f);
    EXPECT_NEAR(rotated.y(), 1.0f, 1e-5f);
    EXPECT_NEAR(rotated.z(), 0.0f, 1e-5f);
    EXPECT_FLOAT_EQ(rotated.w(), 1.0f);  // w unchanged
}

// ============================================================================
// Double Precision Tests
// ============================================================================

TEST(VecDoubleTest, Vec3dOperations) {
    Vec3d v1(1.0, 2.0, 3.0);
    Vec3d v2(4.0, 5.0, 6.0);

    Vec3d sum = v1 + v2;
    EXPECT_DOUBLE_EQ(sum.x(), 5.0);
    EXPECT_DOUBLE_EQ(sum.y(), 7.0);
    EXPECT_DOUBLE_EQ(sum.z(), 9.0);

    double dot = v1.dot(v2);
    EXPECT_DOUBLE_EQ(dot, 32.0);

    Vec3d cross = v1.cross(v2);
    EXPECT_DOUBLE_EQ(cross.x(), -3.0);
    EXPECT_DOUBLE_EQ(cross.y(), 6.0);
    EXPECT_DOUBLE_EQ(cross.z(), -3.0);
}

// ============================================================================
// Integer Vector Tests
// ============================================================================

TEST(VecIntTest, Vec3iOperations) {
    Vec3i v1(1, 2, 3);
    Vec3i v2(4, 5, 6);

    Vec3i sum = v1 + v2;
    EXPECT_EQ(sum.x(), 5);
    EXPECT_EQ(sum.y(), 7);
    EXPECT_EQ(sum.z(), 9);

    int dot = v1.dot(v2);
    EXPECT_EQ(dot, 32);

    // Cross product for integers
    Vec3i cross = v1.cross(v2);
    EXPECT_EQ(cross.x(), -3);
    EXPECT_EQ(cross.y(), 6);
    EXPECT_EQ(cross.z(), -3);
}

// ============================================================================
// GLM Interop Tests
// ============================================================================

TEST(VecGlmTest, ConvertVec2ToGlm) {
    Vec2f v(1.0f, 2.0f);
    glm::vec2 gv = static_cast<glm::vec2>(v);

    EXPECT_FLOAT_EQ(gv.x, 1.0f);
    EXPECT_FLOAT_EQ(gv.y, 2.0f);
}

TEST(VecGlmTest, ConvertVec2FromGlm) {
    glm::vec2 gv(1.0f, 2.0f);
    Vec2f v = gv;

    EXPECT_FLOAT_EQ(v.x(), 1.0f);
    EXPECT_FLOAT_EQ(v.y(), 2.0f);
}

TEST(VecGlmTest, ConvertVec3ToGlm) {
    Vec3f v(1.0f, 2.0f, 3.0f);
    glm::vec3 gv = static_cast<glm::vec3>(v);

    EXPECT_FLOAT_EQ(gv.x, 1.0f);
    EXPECT_FLOAT_EQ(gv.y, 2.0f);
    EXPECT_FLOAT_EQ(gv.z, 3.0f);
}

TEST(VecGlmTest, ConvertVec3FromGlm) {
    glm::vec3 gv(1.0f, 2.0f, 3.0f);
    Vec3f v = gv;

    EXPECT_FLOAT_EQ(v.x(), 1.0f);
    EXPECT_FLOAT_EQ(v.y(), 2.0f);
    EXPECT_FLOAT_EQ(v.z(), 3.0f);
}

TEST(VecGlmTest, ConvertVec4ToGlm) {
    Vec4f v(1.0f, 2.0f, 3.0f, 4.0f);
    glm::vec4 gv = static_cast<glm::vec4>(v);

    EXPECT_FLOAT_EQ(gv.x, 1.0f);
    EXPECT_FLOAT_EQ(gv.y, 2.0f);
    EXPECT_FLOAT_EQ(gv.z, 3.0f);
    EXPECT_FLOAT_EQ(gv.w, 4.0f);
}

TEST(VecGlmTest, ConvertVec4FromGlm) {
    glm::vec4 gv(1.0f, 2.0f, 3.0f, 4.0f);
    Vec4f v = gv;

    EXPECT_FLOAT_EQ(v.x(), 1.0f);
    EXPECT_FLOAT_EQ(v.y(), 2.0f);
    EXPECT_FLOAT_EQ(v.z(), 3.0f);
    EXPECT_FLOAT_EQ(v.w(), 4.0f);
}

TEST(VecGlmTest, GlmEquality) {
    Vec3f v(1.0f, 2.0f, 3.0f);
    glm::vec3 gv(1.0f, 2.0f, 3.0f);

    EXPECT_TRUE(v == gv);
    EXPECT_TRUE(gv == v);
}

}  // namespace vne::math

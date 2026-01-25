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

TEST_F(Vec2Test, Addition) {
    Vec2f result = v1_ + v2_;
    EXPECT_FLOAT_EQ(result.x(), 4.0f);
    EXPECT_FLOAT_EQ(result.y(), 6.0f);
}

TEST_F(Vec2Test, Subtraction) {
    Vec2f result = v2_ - v1_;
    EXPECT_FLOAT_EQ(result.x(), 2.0f);
    EXPECT_FLOAT_EQ(result.y(), 2.0f);
}

TEST_F(Vec2Test, ScalarMultiplication) {
    Vec2f result = v1_ * 2.0f;
    EXPECT_FLOAT_EQ(result.x(), 2.0f);
    EXPECT_FLOAT_EQ(result.y(), 4.0f);
}

TEST_F(Vec2Test, DotProduct) {
    float dot = v1_.dot(v2_);
    EXPECT_FLOAT_EQ(dot, 11.0f);  // 1*3 + 2*4 = 11
}

TEST_F(Vec2Test, Length) {
    Vec2f v(3.0f, 4.0f);
    EXPECT_FLOAT_EQ(v.length(), 5.0f);
}

TEST_F(Vec2Test, Normalized) {
    Vec2f v(3.0f, 4.0f);
    Vec2f n = v.normalized();
    EXPECT_FLOAT_EQ(n.x(), 0.6f);
    EXPECT_FLOAT_EQ(n.y(), 0.8f);
    EXPECT_TRUE(n.isNormalized());
}

TEST_F(Vec2Test, StaticFactories) {
    EXPECT_EQ(Vec2f::zero(), Vec2f(0.0f, 0.0f));
    EXPECT_EQ(Vec2f::one(), Vec2f(1.0f, 1.0f));
    EXPECT_EQ(Vec2f::xAxis(), Vec2f(1.0f, 0.0f));
    EXPECT_EQ(Vec2f::yAxis(), Vec2f(0.0f, 1.0f));
}

TEST_F(Vec2Test, Lerp) {
    Vec2f result = Vec2f::lerp(v1_, v2_, 0.5f);
    EXPECT_FLOAT_EQ(result.x(), 2.0f);
    EXPECT_FLOAT_EQ(result.y(), 3.0f);
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

TEST_F(Vec3Test, Vec2PlusZConstructor) {
    Vec3f v(Vec2f(1.0f, 2.0f), 3.0f);
    EXPECT_FLOAT_EQ(v.x(), 1.0f);
    EXPECT_FLOAT_EQ(v.y(), 2.0f);
    EXPECT_FLOAT_EQ(v.z(), 3.0f);
}

TEST_F(Vec3Test, CrossProduct) {
    Vec3f a(1.0f, 0.0f, 0.0f);
    Vec3f b(0.0f, 1.0f, 0.0f);
    Vec3f result = a.cross(b);
    EXPECT_FLOAT_EQ(result.x(), 0.0f);
    EXPECT_FLOAT_EQ(result.y(), 0.0f);
    EXPECT_FLOAT_EQ(result.z(), 1.0f);
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
    EXPECT_EQ(Vec3f::forward(), Vec3f(0.0f, 0.0f, -1.0f));
    EXPECT_EQ(Vec3f::backward(), Vec3f(0.0f, 0.0f, 1.0f));
}

TEST_F(Vec3Test, Reflect) {
    Vec3f incident(1.0f, -1.0f, 0.0f);
    Vec3f normal = Vec3f::yAxis();
    Vec3f reflected = incident.reflect(normal);
    EXPECT_FLOAT_EQ(reflected.x(), 1.0f);
    EXPECT_FLOAT_EQ(reflected.y(), 1.0f);
    EXPECT_FLOAT_EQ(reflected.z(), 0.0f);
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

TEST_F(Vec4Test, Vec3PlusWConstructor) {
    Vec4f v(Vec3f(1.0f, 2.0f, 3.0f), 4.0f);
    EXPECT_FLOAT_EQ(v.x(), 1.0f);
    EXPECT_FLOAT_EQ(v.y(), 2.0f);
    EXPECT_FLOAT_EQ(v.z(), 3.0f);
    EXPECT_FLOAT_EQ(v.w(), 4.0f);
}

TEST_F(Vec4Test, Swizzle) {
    Vec3f xyz = v1_.xyz();
    EXPECT_FLOAT_EQ(xyz.x(), 1.0f);
    EXPECT_FLOAT_EQ(xyz.y(), 2.0f);
    EXPECT_FLOAT_EQ(xyz.z(), 3.0f);
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
}

// ============================================================================
// GLM Interop Tests
// ============================================================================

TEST(VecGlmTest, ConvertToGlm) {
    Vec3f v(1.0f, 2.0f, 3.0f);
    glm::vec3 gv = static_cast<glm::vec3>(v);

    EXPECT_FLOAT_EQ(gv.x, 1.0f);
    EXPECT_FLOAT_EQ(gv.y, 2.0f);
    EXPECT_FLOAT_EQ(gv.z, 3.0f);
}

TEST(VecGlmTest, ConvertFromGlm) {
    glm::vec3 gv(1.0f, 2.0f, 3.0f);
    Vec3f v = gv;

    EXPECT_FLOAT_EQ(v.x(), 1.0f);
    EXPECT_FLOAT_EQ(v.y(), 2.0f);
    EXPECT_FLOAT_EQ(v.z(), 3.0f);
}

}  // namespace vne::math

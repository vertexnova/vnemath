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

#include "vertexnova/math/core/quat.h"

namespace vne::math {

// ============================================================================
// Basic Quaternion Tests
// ============================================================================

class QuatTest : public ::testing::Test {
   protected:
    Quatf identity_ = Quatf::identity();
};

TEST_F(QuatTest, DefaultConstructor) {
    Quatf q;
    EXPECT_FLOAT_EQ(q.x, 0.0f);
    EXPECT_FLOAT_EQ(q.y, 0.0f);
    EXPECT_FLOAT_EQ(q.z, 0.0f);
    EXPECT_FLOAT_EQ(q.w, 1.0f);
}

TEST_F(QuatTest, ComponentConstructor) {
    Quatf q(1.0f, 2.0f, 3.0f, 4.0f);
    EXPECT_FLOAT_EQ(q.x, 1.0f);
    EXPECT_FLOAT_EQ(q.y, 2.0f);
    EXPECT_FLOAT_EQ(q.z, 3.0f);
    EXPECT_FLOAT_EQ(q.w, 4.0f);
}

TEST_F(QuatTest, Identity) {
    EXPECT_TRUE(identity_.isNormalized());
    EXPECT_FLOAT_EQ(identity_.length(), 1.0f);
}

TEST_F(QuatTest, Length) {
    Quatf q(1.0f, 2.0f, 3.0f, 4.0f);
    float expected = std::sqrt(1.0f + 4.0f + 9.0f + 16.0f);
    EXPECT_FLOAT_EQ(q.length(), expected);
}

TEST_F(QuatTest, Normalized) {
    Quatf q(1.0f, 2.0f, 3.0f, 4.0f);
    Quatf n = q.normalized();
    EXPECT_TRUE(n.isNormalized());
}

TEST_F(QuatTest, Conjugate) {
    Quatf q(1.0f, 2.0f, 3.0f, 4.0f);
    Quatf c = q.conjugate();
    EXPECT_FLOAT_EQ(c.x, -1.0f);
    EXPECT_FLOAT_EQ(c.y, -2.0f);
    EXPECT_FLOAT_EQ(c.z, -3.0f);
    EXPECT_FLOAT_EQ(c.w, 4.0f);
}

TEST_F(QuatTest, Inverse) {
    Quatf q = Quatf::fromAxisAngle(Vec3f::yAxis(), kHalfPi<float>);
    Quatf inv = q.inverse();
    Quatf result = q * inv;
    EXPECT_TRUE(result.approxEquals(identity_, 1e-5f));
}

// ============================================================================
// Rotation Tests
// ============================================================================

TEST_F(QuatTest, FromAxisAngle) {
    Quatf q = Quatf::fromAxisAngle(Vec3f::yAxis(), kHalfPi<float>);
    EXPECT_TRUE(q.isNormalized());

    // Rotating X axis by 90 degrees around Y should give -Z
    Vec3f rotated = q.rotate(Vec3f::xAxis());
    EXPECT_NEAR(rotated.x(), 0.0f, 1e-5f);
    EXPECT_NEAR(rotated.y(), 0.0f, 1e-5f);
    EXPECT_NEAR(rotated.z(), -1.0f, 1e-5f);
}

TEST_F(QuatTest, RotateVector) {
    // 90 degree rotation around Z axis
    Quatf q = Quatf::fromAxisAngle(Vec3f::zAxis(), kHalfPi<float>);
    Vec3f v(1.0f, 0.0f, 0.0f);
    Vec3f rotated = q.rotate(v);

    EXPECT_NEAR(rotated.x(), 0.0f, 1e-5f);
    EXPECT_NEAR(rotated.y(), 1.0f, 1e-5f);
    EXPECT_NEAR(rotated.z(), 0.0f, 1e-5f);
}

TEST_F(QuatTest, AngleAndAxis) {
    float angle = kHalfPi<float>;
    Vec3f axis = Vec3f::yAxis();

    Quatf q = Quatf::fromAxisAngle(axis, angle);

    EXPECT_NEAR(q.angle(), angle, 1e-5f);
    EXPECT_TRUE(q.axis().approxEquals(axis, 1e-5f));
}

TEST_F(QuatTest, MultiplicationIsComposition) {
    // Rotate 90 degrees around Y, then 90 degrees around X
    Quatf qy = Quatf::fromAxisAngle(Vec3f::yAxis(), kHalfPi<float>);
    Quatf qx = Quatf::fromAxisAngle(Vec3f::xAxis(), kHalfPi<float>);

    Quatf combined = qx * qy;

    Vec3f v = Vec3f::forward();
    Vec3f step1 = qy.rotate(v);
    Vec3f step2 = qx.rotate(step1);
    Vec3f direct = combined.rotate(v);

    EXPECT_TRUE(step2.approxEquals(direct, 1e-5f));
}

// ============================================================================
// Conversion Tests
// ============================================================================

TEST_F(QuatTest, ToMatrix4) {
    Quatf q = Quatf::fromAxisAngle(Vec3f::yAxis(), kHalfPi<float>);
    Mat4f m = q.toMatrix4();

    // Both should rotate the same way
    Vec3f v(1.0f, 0.0f, 0.0f);
    Vec3f fromQuat = q.rotate(v);
    Vec3f fromMatrix = m.transformVector(v);

    EXPECT_TRUE(fromQuat.approxEquals(fromMatrix, 1e-5f));
}

TEST_F(QuatTest, FromMatrix) {
    Quatf original = Quatf::fromAxisAngle(Vec3f::yAxis(), degToRad(45.0f));
    Mat4f m = original.toMatrix4();
    Quatf fromMatrix = Quatf::fromMatrix(m);

    // Should rotate the same way (may differ by sign)
    Vec3f v(1.0f, 2.0f, 3.0f);
    Vec3f r1 = original.rotate(v);
    Vec3f r2 = fromMatrix.rotate(v);

    EXPECT_TRUE(r1.approxEquals(r2, 1e-5f));
}

TEST_F(QuatTest, EulerConversion) {
    Vec3f euler(degToRad(30.0f), degToRad(45.0f), degToRad(60.0f));
    Quatf q = Quatf::fromEuler(euler);
    Vec3f recovered = q.toEuler();

    EXPECT_NEAR(euler.x(), recovered.x(), 1e-5f);
    EXPECT_NEAR(euler.y(), recovered.y(), 1e-5f);
    EXPECT_NEAR(euler.z(), recovered.z(), 1e-5f);
}

// ============================================================================
// Interpolation Tests
// ============================================================================

TEST_F(QuatTest, Slerp) {
    Quatf q1 = Quatf::identity();
    Quatf q2 = Quatf::fromAxisAngle(Vec3f::yAxis(), kHalfPi<float>);

    Quatf mid = Quatf::slerp(q1, q2, 0.5f);
    EXPECT_TRUE(mid.isNormalized());

    // Midpoint should be half the rotation
    EXPECT_NEAR(mid.angle(), kHalfPi<float> / 2.0f, 1e-5f);
}

TEST_F(QuatTest, Nlerp) {
    Quatf q1 = Quatf::identity();
    Quatf q2 = Quatf::fromAxisAngle(Vec3f::yAxis(), kHalfPi<float>);

    Quatf mid = Quatf::nlerp(q1, q2, 0.5f);
    EXPECT_TRUE(mid.isNormalized());
}

TEST_F(QuatTest, DotProduct) {
    Quatf q1 = Quatf::identity();
    Quatf q2 = Quatf::identity();

    float dot = Quatf::dot(q1, q2);
    EXPECT_FLOAT_EQ(dot, 1.0f);
}

// ============================================================================
// Special Cases
// ============================================================================

TEST_F(QuatTest, FromToRotation) {
    Vec3f from = Vec3f::xAxis();
    Vec3f to = Vec3f::yAxis();

    Quatf q = Quatf::fromToRotation(from, to);
    Vec3f rotated = q.rotate(from);

    EXPECT_TRUE(rotated.approxEquals(to, 1e-5f));
}

TEST_F(QuatTest, FromToRotationSameDirection) {
    Vec3f dir = Vec3f::xAxis();
    Quatf q = Quatf::fromToRotation(dir, dir);

    EXPECT_TRUE(q.approxEquals(identity_, 1e-5f));
}

TEST_F(QuatTest, FromToRotationOppositeDirection) {
    Vec3f from = Vec3f::xAxis();
    Vec3f to = Vec3f::left();

    Quatf q = Quatf::fromToRotation(from, to);
    Vec3f rotated = q.rotate(from);

    EXPECT_TRUE(rotated.approxEquals(to, 1e-5f));
}

TEST_F(QuatTest, LookRotation) {
    // Test looking in a different direction
    Vec3f targetForward = Vec3f::xAxis();  // Look along X axis
    Vec3f up = Vec3f::up();

    Quatf q = Quatf::lookRotation(targetForward, up);
    EXPECT_TRUE(q.isNormalized());

    // The quaternion should rotate the default forward (-Z) to the target forward (X)
    Vec3f result = q.rotate(Vec3f::forward());
    EXPECT_TRUE(result.approxEquals(targetForward, 1e-4f));
}

// ============================================================================
// Double Precision Tests
// ============================================================================

TEST(QuatDoubleTest, BasicOperations) {
    Quatd q1 = Quatd::fromAxisAngle(Vec3d::yAxis(), kHalfPi<double>);
    Quatd q2 = Quatd::fromAxisAngle(Vec3d::xAxis(), kHalfPi<double>);

    Quatd combined = q2 * q1;
    EXPECT_TRUE(combined.isNormalized());
}

// ============================================================================
// GLM Interop Tests
// ============================================================================

TEST(QuatGlmTest, ConvertToGlm) {
    Quatf q = Quatf::fromAxisAngle(Vec3f::yAxis(), kHalfPi<float>);
    glm::quat gq = static_cast<glm::quat>(q);

    EXPECT_FLOAT_EQ(q.x, gq.x);
    EXPECT_FLOAT_EQ(q.y, gq.y);
    EXPECT_FLOAT_EQ(q.z, gq.z);
    EXPECT_FLOAT_EQ(q.w, gq.w);
}

TEST(QuatGlmTest, ConvertFromGlm) {
    glm::quat gq = glm::angleAxis(kHalfPi<float>, glm::vec3(0, 1, 0));
    Quatf q = gq;

    EXPECT_FLOAT_EQ(q.x, gq.x);
    EXPECT_FLOAT_EQ(q.y, gq.y);
    EXPECT_FLOAT_EQ(q.z, gq.z);
    EXPECT_FLOAT_EQ(q.w, gq.w);
}

}  // namespace vne::math

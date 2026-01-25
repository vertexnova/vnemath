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

TEST_F(QuatTest, Vec4Constructor) {
    Quatf q(Vec4f(1.0f, 0.0f, 0.0f, 3.0f));
    EXPECT_FLOAT_EQ(q.x, 1.0f);
    EXPECT_FLOAT_EQ(q.y, 0.0f);
    EXPECT_FLOAT_EQ(q.z, 0.0f);
    EXPECT_FLOAT_EQ(q.w, 3.0f);
}

TEST_F(QuatTest, Vec3Constructor) {
    Quatf q(Vec3f(0.707f, 0.0f, 0.707f));
    EXPECT_FLOAT_EQ(q.x, 0.707f);
    EXPECT_FLOAT_EQ(q.y, 0.0f);
    EXPECT_FLOAT_EQ(q.z, 0.707f);
    EXPECT_FLOAT_EQ(q.w, 1.0f);
}

TEST_F(QuatTest, ScalarVectorConstructor) {
    Quatf q(2.0f, Vec3f(1.0f, 2.0f, 3.0f));
    EXPECT_FLOAT_EQ(q.x, 1.0f);
    EXPECT_FLOAT_EQ(q.y, 2.0f);
    EXPECT_FLOAT_EQ(q.z, 3.0f);
    EXPECT_FLOAT_EQ(q.w, 2.0f);
}

TEST_F(QuatTest, GlmConstructor) {
    Quatf q(glm::quat(2.0f, 0.0f, 0.0f, 1.0f));
    EXPECT_FLOAT_EQ(q.w, 2.0f);
    EXPECT_FLOAT_EQ(q.x, 0.0f);
    EXPECT_FLOAT_EQ(q.y, 0.0f);
    EXPECT_FLOAT_EQ(q.z, 1.0f);
}

TEST_F(QuatTest, Identity) {
    EXPECT_TRUE(identity_.isNormalized());
    EXPECT_FLOAT_EQ(identity_.length(), 1.0f);
}

TEST_F(QuatTest, GetWAndGetVector) {
    Quatf q(13.0f, 12.0f, 5.0f, 1.0f);
    EXPECT_FLOAT_EQ(q.getW(), 1.0f);
    Vec3f vec = q.getVector();
    EXPECT_FLOAT_EQ(vec.x(), 13.0f);
    EXPECT_FLOAT_EQ(vec.y(), 12.0f);
    EXPECT_FLOAT_EQ(vec.z(), 5.0f);
}

TEST_F(QuatTest, Length) {
    Quatf q(1.0f, 2.0f, 3.0f, 4.0f);
    float expected = std::sqrt(1.0f + 4.0f + 9.0f + 16.0f);
    EXPECT_FLOAT_EQ(q.length(), expected);
}

TEST_F(QuatTest, LengthSquared) {
    Quatf q(0.0f, 12.0f, 5.0f, 0.0f);
    EXPECT_FLOAT_EQ(q.length(), 13.0f);
    EXPECT_FLOAT_EQ(q.lengthSquared(), 169.0f);
}

TEST_F(QuatTest, Normalized) {
    Quatf q(1.0f, 2.0f, 3.0f, 4.0f);
    Quatf n = q.normalized();
    EXPECT_TRUE(n.isNormalized());
    EXPECT_NEAR(n.length(), 1.0f, 1e-5f);
}

TEST_F(QuatTest, NormalizeInPlace) {
    Quatf q(2.0f, 3.0f, 4.0f, 5.0f);
    q.normalize();
    EXPECT_NEAR(q.length(), 1.0f, 1e-5f);
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

TEST_F(QuatTest, DotProduct) {
    Quatf q1(0.0f, 0.0f, 12.0f, 5.0f);
    Quatf q2(0.0f, 0.0f, 12.0f, 5.0f);
    EXPECT_FLOAT_EQ(q1.dot(q2), 169.0f);
    EXPECT_FLOAT_EQ(Quatf::dot(q1, q2), 169.0f);
}

TEST_F(QuatTest, Clear) {
    Quatf q(2.0f, 13.0f, 12.0f, 5.0f);
    q.clear();
    EXPECT_FLOAT_EQ(q.w, 1.0f);
    EXPECT_FLOAT_EQ(q.x, 0.0f);
    EXPECT_FLOAT_EQ(q.y, 0.0f);
    EXPECT_FLOAT_EQ(q.z, 0.0f);
}

TEST_F(QuatTest, SetIdentity) {
    Quatf q(2.0f, 3.0f, 4.0f, 5.0f);
    q.setIdentity();
    EXPECT_FLOAT_EQ(q.w, 1.0f);
    EXPECT_FLOAT_EQ(q.x, 0.0f);
    EXPECT_FLOAT_EQ(q.y, 0.0f);
    EXPECT_FLOAT_EQ(q.z, 0.0f);
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

TEST_F(QuatTest, SetFromAxisAngle) {
    Quatf q;
    q.setFromAxisAngle(kHalfPi<float>, Vec3f::zAxis());
    Vec3f rotated = q.rotateVector(Vec3f::xAxis());
    EXPECT_NEAR(rotated.x(), 0.0f, 1e-5f);
    EXPECT_NEAR(rotated.y(), 1.0f, 1e-5f);
    EXPECT_NEAR(rotated.z(), 0.0f, 1e-5f);
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

TEST_F(QuatTest, RotateVectorAlias) {
    Quatf q = Quatf::fromAxisAngle(Vec3f::zAxis(), kHalfPi<float>);
    Vec3f v(1.0f, 0.0f, 0.0f);
    Vec3f rotated = q.rotateVector(v);
    EXPECT_NEAR(rotated.x(), 0.0f, 1e-5f);
    EXPECT_NEAR(rotated.y(), 1.0f, 1e-5f);
    EXPECT_NEAR(rotated.z(), 0.0f, 1e-5f);
}

TEST_F(QuatTest, AngleAndAxis) {
    float angle = kHalfPi<float>;
    Vec3f axis = Vec3f::yAxis();

    Quatf q = Quatf::fromAxisAngle(axis, angle);

    EXPECT_NEAR(q.angle(), angle, 1e-5f);
    EXPECT_NEAR(q.getAngle(), angle, 1e-5f);
    EXPECT_TRUE(q.axis().approxEquals(axis, 1e-5f));
    EXPECT_TRUE(q.getAxis().approxEquals(axis, 1e-5f));
}

TEST_F(QuatTest, GetAngleAndAxis) {
    float angle = degToRad(60.0f);
    Vec3f axis = Vec3f(0.756477f, 0.147957f, -0.635297f).normalized();

    Quatf q;
    q.setAngleAndAxis(angle, axis);

    float out_angle;
    Vec3f out_axis;
    q.getAngleAndAxis(out_angle, out_axis);

    EXPECT_NEAR(angle, out_angle, 1e-5f);
    EXPECT_TRUE(out_axis.approxEquals(axis, 1e-5f));
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

TEST_F(QuatTest, MakeRotate) {
    Vec3f from = Vec3f::xAxis();
    Vec3f to = Vec3f::yAxis();

    Quatf q;
    q.makeRotate(from, to);

    Vec3f rotated = q.rotateVector(from);
    EXPECT_TRUE(rotated.approxEquals(to, 1e-5f));
}

// ============================================================================
// Basis Vector Tests
// ============================================================================

TEST_F(QuatTest, BasisVectors) {
    Quatf q(-0.0474207f, 0.756477f, 0.147957f, -0.635297f);

    Vec3f expected_x = q.rotate(Vec3f::xAxis());
    Vec3f expected_y = q.rotate(Vec3f::yAxis());
    Vec3f expected_z = q.rotate(Vec3f::zAxis());

    EXPECT_TRUE(q.getXAxis().approxEquals(expected_x, 1e-5f));
    EXPECT_TRUE(q.getYAxis().approxEquals(expected_y, 1e-5f));
    EXPECT_TRUE(q.getZAxis().approxEquals(expected_z, 1e-5f));
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

TEST_F(QuatTest, MatrixConstructor) {
    Mat4f rotation = Mat4f::rotateX(kHalfPi<float>);
    Quatf q(rotation);

    Vec3f euler = q.getEulerAngles();
    EXPECT_NEAR(euler.x(), kHalfPi<float>, 1e-5f);
    EXPECT_NEAR(euler.y(), 0.0f, 1e-5f);
    EXPECT_NEAR(euler.z(), 0.0f, 1e-5f);
}

TEST_F(QuatTest, EulerConversion) {
    Vec3f euler(degToRad(30.0f), degToRad(45.0f), degToRad(60.0f));
    Quatf q = Quatf::fromEuler(euler);
    Vec3f recovered = q.toEuler();

    EXPECT_NEAR(euler.x(), recovered.x(), 1e-5f);
    EXPECT_NEAR(euler.y(), recovered.y(), 1e-5f);
    EXPECT_NEAR(euler.z(), recovered.z(), 1e-5f);
}

TEST_F(QuatTest, SetFromEulerAngles) {
    Quatf q;
    q.setFromEulerAngles(kHalfPi<float>, kPi<float> / 4.0f, kPi<float> / 6.0f);

    Vec3f euler = q.getEulerAngles();
    EXPECT_NEAR(kHalfPi<float>, euler.x(), 1e-5f);
    EXPECT_NEAR(kPi<float> / 4.0f, euler.y(), 1e-5f);
    EXPECT_NEAR(kPi<float> / 6.0f, euler.z(), 1e-5f);
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

TEST_F(QuatTest, SlerpMember) {
    Quatf q1(0.0f, 0.0f, 0.0f, 1.0f);
    Quatf q2(1.0f, 0.0f, 0.0f, 0.0f);

    Quatf slerped = q1.slerp(q2, 0.5f);

    EXPECT_NEAR(slerped.w, 0.7071f, 1e-4f);
    EXPECT_NEAR(slerped.x, 0.7071f, 1e-4f);
    EXPECT_NEAR(slerped.y, 0.0f, 1e-4f);
    EXPECT_NEAR(slerped.z, 0.0f, 1e-4f);
}

TEST_F(QuatTest, Nlerp) {
    Quatf q1 = Quatf::identity();
    Quatf q2 = Quatf::fromAxisAngle(Vec3f::yAxis(), kHalfPi<float>);

    Quatf mid = Quatf::nlerp(q1, q2, 0.5f);
    EXPECT_TRUE(mid.isNormalized());
}

// ============================================================================
// Arithmetic Operator Tests
// ============================================================================

TEST_F(QuatTest, Addition) {
    Quatf q1(2.0f, 3.0f, 0.0f, 0.0f);
    Quatf q2(13.0f, 12.0f, 5.0f, 1.0f);
    Quatf result = q2 + q1;
    EXPECT_FLOAT_EQ(result.x, 15.0f);
    EXPECT_FLOAT_EQ(result.y, 15.0f);
    EXPECT_FLOAT_EQ(result.z, 5.0f);
    EXPECT_FLOAT_EQ(result.w, 1.0f);
}

TEST_F(QuatTest, AdditionAssignment) {
    Quatf q1(2.0f, 3.0f, 0.0f, 0.0f);
    Quatf q2(13.0f, 12.0f, 5.0f, 1.0f);
    q2 += q1;
    EXPECT_FLOAT_EQ(q2.x, 15.0f);
    EXPECT_FLOAT_EQ(q2.y, 15.0f);
}

TEST_F(QuatTest, Subtraction) {
    Quatf q1(0.0f, 2.0f, 3.0f, 0.0f);
    Quatf q2(13.0f, 12.0f, 5.0f, 1.0f);
    Quatf result = q2 - q1;
    EXPECT_FLOAT_EQ(result.x, 13.0f);
    EXPECT_FLOAT_EQ(result.y, 10.0f);
    EXPECT_FLOAT_EQ(result.z, 2.0f);
    EXPECT_FLOAT_EQ(result.w, 1.0f);
}

TEST_F(QuatTest, Multiplication) {
    Quatf q1(2.0f, 3.0f, 0.0f, 0.0f);
    Quatf q2(13.0f, 12.0f, 5.0f, 1.0f);
    Quatf result = q1 * q2;
    // Verify it compiles and produces valid quaternion
    EXPECT_TRUE(std::isfinite(result.w));
}

TEST_F(QuatTest, ScalarMultiplication) {
    Quatf q(2.0f, 3.0f, 0.0f, 0.0f);
    float scalar = 2.0f;
    Quatf result = q * scalar;
    EXPECT_FLOAT_EQ(result.x, 4.0f);
    EXPECT_FLOAT_EQ(result.y, 6.0f);
    EXPECT_FLOAT_EQ(result.z, 0.0f);
    EXPECT_FLOAT_EQ(result.w, 0.0f);

    Quatf result2 = scalar * q;
    EXPECT_FLOAT_EQ(result2.x, 4.0f);
    EXPECT_FLOAT_EQ(result2.y, 6.0f);
}

TEST_F(QuatTest, ScalarDivision) {
    Quatf q(2.0f, 4.2f, 1.0f, 3.0f);
    float scalar = 2.0f;
    Quatf result = q / scalar;
    EXPECT_FLOAT_EQ(result.x, 1.0f);
    EXPECT_FLOAT_EQ(result.y, 2.1f);
    EXPECT_FLOAT_EQ(result.z, 0.5f);
    EXPECT_FLOAT_EQ(result.w, 1.5f);
}

TEST_F(QuatTest, UnaryOperators) {
    Quatf q(1.0f, 2.0f, 3.2f, 1.1f);
    Quatf neg = -q;
    EXPECT_FLOAT_EQ(neg.x, -1.0f);
    EXPECT_FLOAT_EQ(neg.y, -2.0f);
    EXPECT_FLOAT_EQ(neg.z, -3.2f);
    EXPECT_FLOAT_EQ(neg.w, -1.1f);

    Quatf pos = +q;
    EXPECT_FLOAT_EQ(pos.x, q.x);
    EXPECT_FLOAT_EQ(pos.y, q.y);
}

// ============================================================================
// Comparison Tests
// ============================================================================

TEST_F(QuatTest, Equality) {
    Quatf q1(2.0f, 3.2f, 1.1f, 0.0f);
    Quatf q2(1.22f, 0.342f, 1.0f, 1.0f);
    EXPECT_TRUE(q1 != q2);

    Quatf q3 = q1;
    EXPECT_TRUE(q1 == q3);
}

TEST_F(QuatTest, ApproxEquals) {
    Quatf q1 = Quatf::identity();
    Quatf q2(0.0f, 0.0f, 0.0f, 1.0f + 1e-7f);
    EXPECT_TRUE(q1.approxEquals(q2, 1e-5f));
}

// ============================================================================
// Subscript Operator Tests
// ============================================================================

TEST_F(QuatTest, SubscriptOperator) {
    Quatf q(2.0f, 3.2f, 1.1f, 1.0f);
    EXPECT_FLOAT_EQ(q[0], q.x);
    EXPECT_FLOAT_EQ(q[1], q.y);
    EXPECT_FLOAT_EQ(q[2], q.z);
    EXPECT_FLOAT_EQ(q[3], q.w);

    // Modify via subscript
    q[0] = 5.0f;
    EXPECT_FLOAT_EQ(q.x, 5.0f);
}

TEST_F(QuatTest, SubscriptOperatorConst) {
    const Quatf q(2.0f, 3.0f, 4.0f, 1.0f);
    EXPECT_FLOAT_EQ(q[0], 2.0f);
    EXPECT_FLOAT_EQ(q[1], 3.0f);
    EXPECT_FLOAT_EQ(q[2], 4.0f);
    EXPECT_FLOAT_EQ(q[3], 1.0f);
}

// ============================================================================
// Vector Multiplication Tests
// ============================================================================

TEST_F(QuatTest, QuaternionVectorMultiplication) {
    Quatf q(13.0f, 12.0f, 5.0f, 1.0f);
    Vec3f v(3.0f, 4.0f, 5.0f);

    Vec3f result = q * v;
    Vec3f expected = q.rotate(v);
    EXPECT_TRUE(result.approxEquals(expected, 1e-5f));
}

TEST_F(QuatTest, VectorQuaternionMultiplication) {
    Quatf q(13.0f, 12.0f, 5.0f, 1.0f);
    Vec3f v(3.0f, 4.0f, 5.0f);

    Vec3f result = v * q;
    Vec3f expected = q.inverse().rotate(v);
    EXPECT_TRUE(result.approxEquals(expected, 1e-5f));
}

// ============================================================================
// Stream Output Test
// ============================================================================

TEST_F(QuatTest, StreamOutput) {
    std::ostringstream stream;
    Quatf q(0.0f, 0.0f, 1.0f, 2.0f);
    stream << q;
    EXPECT_EQ(stream.str(), "[2, 0, 0, 1]");
}

// ============================================================================
// Static Method Tests
// ============================================================================

TEST_F(QuatTest, StaticNormalize) {
    Quatf q(2.0f, 3.0f, 4.0f, 5.0f);
    Quatf n = Quatf::normalize(q);
    EXPECT_NEAR(n.length(), 1.0f, 1e-5f);
}

TEST_F(QuatTest, StaticConjugate) {
    Quatf q(3.0f, 4.0f, 5.0f, 2.0f);
    Quatf c = Quatf::conjugate(q);
    EXPECT_FLOAT_EQ(c.x, -3.0f);
    EXPECT_FLOAT_EQ(c.y, -4.0f);
    EXPECT_FLOAT_EQ(c.z, -5.0f);
    EXPECT_FLOAT_EQ(c.w, 2.0f);
}

TEST_F(QuatTest, StaticInverse) {
    Quatf q(3.0f, 4.0f, 5.0f, 2.0f);
    Quatf inv = Quatf::inverse(q);
    Quatf c = q.conjugate();
    float len_sq = q.lengthSquared();
    EXPECT_NEAR(inv.x, c.x / len_sq, 1e-5f);
    EXPECT_NEAR(inv.y, c.y / len_sq, 1e-5f);
    EXPECT_NEAR(inv.z, c.z / len_sq, 1e-5f);
    EXPECT_NEAR(inv.w, c.w / len_sq, 1e-5f);
}

// ============================================================================
// Special Cases Tests
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
    Vec3f targetForward = Vec3f::xAxis();
    Vec3f up = Vec3f::up();

    Quatf q = Quatf::lookRotation(targetForward, up);
    EXPECT_TRUE(q.isNormalized());

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

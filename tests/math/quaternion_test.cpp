/* ---------------------------------------------------------------------
 * Copyright (c) 2024 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Author:    Ajeet Singh Yadav
 * Created:   September-2024
 *
 * Autodoc:   yes
 * ----------------------------------------------------------------------
 */

#include <gtest/gtest.h>

#include "vertexnova/math/math_utils.h"
#include "vertexnova/math/quaternion.h"

using namespace VNE;

class QuaternionTest_C : public ::testing::Test {
    // Interface of test fixture base class
   protected:
    void SetUp() override {}

    void TearDown() override {}
};

/**
 * Test QuaternionTest_C constructors
 *
 */
TEST_F(QuaternionTest_C, TestQuaternionConstructors) {
    vne::math::Quaternion quat0 = vne::math::Quaternion();
    EXPECT_EQ(1.0f, quat0.w);
    EXPECT_EQ(0.0f, quat0.x);
    EXPECT_EQ(0.0f, quat0.y);
    EXPECT_EQ(0.0f, quat0.z);

    vne::math::Quaternion quat1 = vne::math::Quaternion(vne::math::Vec4f(1.0f, 0.0f, 0.0f, 3.0f));
    EXPECT_EQ(3.0f, quat1.w);
    EXPECT_EQ(1.0f, quat1.x);
    EXPECT_EQ(0.0f, quat1.y);
    EXPECT_EQ(0.0f, quat1.z);

    vne::math::Quaternion quat2 = vne::math::Quaternion(vne::math::Vec3f(0.707f, 0.0f, 0.707f));
    EXPECT_EQ(1.0f, quat2.w);
    EXPECT_EQ(0.707f, quat2.x);
    EXPECT_EQ(0.0f, quat2.y);
    EXPECT_EQ(0.707f, quat2.z);

    vne::math::Quaternion quat3 = vne::math::Quaternion(2.0f, 0.0f, 0.0f, 1.0f);
    EXPECT_EQ(2.0f, quat3.w);
    EXPECT_EQ(0.0f, quat3.x);
    EXPECT_EQ(0.0f, quat3.y);
    EXPECT_EQ(1.0f, quat3.z);

    vne::math::Quaternion quat4 = vne::math::Quaternion(glm::quat(2.0f, 0.0f, 0.0f, 1.0f));
    EXPECT_EQ(2.0f, quat4.w);
    EXPECT_EQ(0.0f, quat4.x);
    EXPECT_EQ(0.0f, quat4.y);
    EXPECT_EQ(1.0f, quat4.z);

    vne::math::Quaternion quat5 = vne::math::Quaternion(vne::math::quarterPi<float>(), vne::math::Vec3f(0.0f, 1.0f, 0.0f));
    EXPECT_TRUE(vne::math::areSame(0.785398f, quat5.w, 1E-5f));
    EXPECT_EQ(0.0f, quat5.x);
    EXPECT_EQ(1.0f, quat5.y);
    EXPECT_EQ(0.0f, quat5.z);
}

/**
 * Test Quaternion GetW() and GetVector()
 */
TEST_F(QuaternionTest_C, TestQuaternionGetVecAndW) {
    vne::math::Quaternion quat{1.0f, 13.0f, 12.0f, 5.0f};
    EXPECT_EQ(1.0f, quat.getW());
    EXPECT_EQ(vne::math::Vec3f(13.0f, 12.0f, 5.0f), quat.getVector());
}

/**
 * Test Quaternion angle and axis
 *
 * quat.getAngle()
 * quat.getAxis()
 * quat.SetAngleAxis(float, vne::math::Vec3f)
 * quat.getAngleAxis(float&, vne::math::Vec3f&)
 *
 */
TEST_F(QuaternionTest_C, TestQuaternionAngleAndAxis) {
    vne::math::Quaternion quat{-0.0474207f, 0.756477f, 0.147957f, -0.635297f};
    // Get angle
    EXPECT_EQ(2.0f * vne::math::acos(quat.w), quat.getAngle());
    // Get axis
    EXPECT_TRUE(quat.getVector().areSame(quat.getAxis() * vne::math::sin(0.5f * quat.getAngle()), 1E-5f));
    // Set angle and axis
    quat.clear();
    float angle = vne::math::degToRad(60.0f);
    vne::math::Vec3f axis{0.756477f, 0.147957f, -0.635297f};
    quat.setAngleAndAxis(angle, axis);
    EXPECT_TRUE(vne::math::areSame(quat.getW(), vne::math::cos(0.5f * quat.getAngle()), 1E-5f));
    EXPECT_TRUE(quat.getVector().areSame(quat.getAxis() * vne::math::sin(0.5f * quat.getAngle()), 1E-5f));
    // Get angle and axis
    float new_angle;
    vne::math::Vec3f new_axis;
    quat.getAngleAndAxis(new_angle, new_axis);
    EXPECT_TRUE(vne::math::areSame(angle, new_angle));
    EXPECT_TRUE(new_axis.areSame(axis));
}

/**
 * Test Quaternion X, Y, and Z axes
 *
 * quat.getXAxis()
 * quat.getYAxis()
 * quat.getZAxis()
 *
 */
TEST_F(QuaternionTest_C, TestQuaternionAxes) {
    vne::math::Quaternion quat{-0.0474207f, 0.756477f, 0.147957f, -0.635297f};

    // Expected X, Y, Z axes after rotation
    vne::math::Vec3f expected_x_axis = quat * vne::math::Vec3f(1.0f, 0.0f, 0.0f);
    vne::math::Vec3f expected_y_axis = quat * vne::math::Vec3f(0.0f, 1.0f, 0.0f);
    vne::math::Vec3f expected_z_axis = quat * vne::math::Vec3f(0.0f, 0.0f, 1.0f);

    // Test X Axis
    vne::math::Vec3f x_axis = quat.getXAxis();
    EXPECT_TRUE(expected_x_axis.areSame(x_axis, 1E-5f));

    // Test Y Axis
    vne::math::Vec3f y_axis = quat.getYAxis();
    EXPECT_TRUE(expected_y_axis.areSame(y_axis, 1E-5f));

    // Test Z Axis
    vne::math::Vec3f z_axis = quat.getZAxis();
    EXPECT_TRUE(expected_z_axis.areSame(z_axis, 1E-5f));
}

/**
 * Test Quaternion Clear()
 */
TEST_F(QuaternionTest_C, TestQuaternionClear) {
    vne::math::Quaternion quat{2.0f, 13.0f, 12.0f, 5.0f};

    quat.clear();
    EXPECT_EQ(1.0f, quat.getW());
    EXPECT_EQ(vne::math::Vec3f(), quat.getVector());
}

/**
 * Test Quaternion Length
 *
 * quat.length()
 * quat.lengthSquared()
 *
 */
TEST_F(QuaternionTest_C, TestQuaternionLength) {
    vne::math::Quaternion quat{0.0f, 12.0f, 5.0f, 0.0f};

    EXPECT_EQ(13.0f, quat.length());
    EXPECT_EQ(quat.length(), vne::math::sqrt(quat.lengthSquared()));
}

/**
 * Test Quaternion Conjugate
 *
 * quat.conjugate()
 *
 */
TEST_F(QuaternionTest_C, TestQuaternionConjugate) {
    vne::math::Quaternion quat{1.0f, 13.0f, 12.0f, 5.0f};

    EXPECT_EQ(vne::math::Quaternion(1.0f, -13.0f, -12.0f, -5.0f), quat.conjugate());
}

/**
 * Test Quaternion Inverse
 *
 * quat.inverse()
 *
 */
TEST_F(QuaternionTest_C, TestQuaternionInverse) {
    vne::math::Quaternion quat{1.0f, 13.0f, 12.0f, 5.0f};
    EXPECT_EQ(quat.conjugate() / quat.lengthSquared(), quat.inverse());

    vne::math::Quaternion quat1{0.0f, 0.0f, 1.0f, 0.0f};
    EXPECT_EQ(quat1.conjugate(), quat1.inverse());
}

/**
 * Test Quaternion Dot
 *
 * quat.dot()
 * Quaternion::dot(const Quaternion&, const Quaternion&)
 *
 */
TEST_F(QuaternionTest_C, TestQuaternionDot) {
    vne::math::Quaternion quat1{1.0f, 0.0f, 12.0f, 5.0f};
    vne::math::Quaternion quat2{1.0f, 0.0f, 12.0f, 5.0f};
    EXPECT_EQ(170.0f, quat1.dot(quat2));
    EXPECT_EQ(170.0f, vne::math::Quaternion::dot(quat1, quat2));
}

/**
 * Test Quaternion addition
 */
TEST_F(QuaternionTest_C, TestQuaternionAddition) {
    vne::math::Quaternion quat1{0.0f, 2.0f, 3.0f, 0.0f};
    vne::math::Quaternion quat2{1.0f, 13.0f, 12.0f, 5.0f};
    EXPECT_EQ(vne::math::Quaternion(1.0f, 15.0f, 15.0f, 5.0f), quat2 + quat1);
    EXPECT_EQ(quat2, quat2 += quat1);
}

/**
 * Test Quaternion subtraction
 */
TEST_F(QuaternionTest_C, TestQuaternionSubtraction) {
    vne::math::Quaternion quat1{0.0f, 0.0f, 2.0f, 3.0f};
    vne::math::Quaternion quat2{1.0f, 13.0f, 12.0f, 5.0f};
    EXPECT_EQ(vne::math::Quaternion(1.0f, 13.0f, 10.0f, 2.0f), quat2 - quat1);
    EXPECT_EQ(quat2, quat2 -= quat1);
}

/**
 * Test Quaternion -> quaternion to vector multiplication
 */
TEST_F(QuaternionTest_C, TestQuaternionxVector) {
    vne::math::Quaternion quat{1.0f, 13.0f, 12.0f, 5.0f};
    vne::math::Vec3f vec{3.0f, 4.0f, 5.0f};
    EXPECT_EQ(glm::quat(1.0f, 13.0f, 12.0f, 5.0f) * glm::vec3(3.0f, 4.0f, 5.0f), quat * vec);
    EXPECT_EQ(glm::vec3(3.0f, 4.0f, 5.0f) * glm::quat(1.0f, 13.0f, 12.0f, 5.0f), vec * quat);
}

/**
 * Test Quaternion multiplication
 */
TEST_F(QuaternionTest_C, TestQuaternionMultiplication) {
    vne::math::Quaternion quat1{0.0f, 2.0f, 3.0f, 0.0f};
    vne::math::Quaternion quat2{1.0f, 13.0f, 12.0f, 5.0f};
    float scalar = 2.0f;
    EXPECT_EQ(vne::math::Quaternion(-62.0f, 17.0f, -7.0f, -15.0f), quat1 * quat2);
    EXPECT_EQ(quat2, quat2 *= quat1);
    EXPECT_EQ(vne::math::Quaternion(0.0f, 4.0f, 6.0f, 0.0f), quat1 * scalar);
    EXPECT_EQ(vne::math::Quaternion(0.0f, 4.0f, 6.0f, 0.0f), scalar * quat1);
    EXPECT_EQ(quat1, quat1 *= scalar);
}

/**
 * Test Quaternion division
 */
TEST_F(QuaternionTest_C, TestQuaternionDivision) {
    float scalar = 2.0f;
    vne::math::Quaternion quat{3.0f, 2.0f, 4.2f, 1.0f};

    EXPECT_EQ(vne::math::Quaternion(1.5f, 1.0f, 2.1f, 0.5f), quat / scalar);

    EXPECT_EQ(quat, quat /= scalar);
    EXPECT_EQ(1.5f, quat.w);
    EXPECT_EQ(1.0f, quat.x);
    EXPECT_EQ(2.1f, quat.y);
    EXPECT_EQ(0.5f, quat.z);
#ifdef _DEBUG
    ASSERT_DEATH(quat / 0.0f, ".*");
#endif  // _DEBUG
}

/**
 * Test Quaternion comparison
 *
 */
TEST_F(QuaternionTest_C, TestQuaternionComparison) {
    vne::math::Quaternion quat1{0.0f, 2.0f, 3.2f, 1.1f};
    vne::math::Quaternion quat2{1.0f, 1.22f, 0.342f, 1.0f};
    EXPECT_TRUE(quat1 != quat2);

    vne::math::Quaternion equal_quat = quat2;
    EXPECT_TRUE(equal_quat == quat2);
    EXPECT_TRUE(equal_quat != quat1);
}

/**
 * Test Quaternion assignment
 */
TEST_F(QuaternionTest_C, TestQuaternionAssignment) {
    vne::math::Quaternion test_quat;
    vne::math::Quaternion quat{1.0f, 2.0f, 3.2f, 1.1f};
    EXPECT_EQ(quat, test_quat = quat);
}

/**
 * Test Quaternion specific component
 */
TEST_F(QuaternionTest_C, TestQuaternionComponent) {
    float value;
    vne::math::Quaternion quat{1.0f, 2.0f, 3.2f, 1.1f};
    EXPECT_EQ(quat.x, quat[0]);
    EXPECT_EQ(quat.y, quat[1]);
    EXPECT_EQ(quat.z, quat[2]);
    EXPECT_EQ(quat.w, quat[3]);
    EXPECT_EQ(quat.y, value = quat[1]);
    EXPECT_EQ(quat.w, value = quat[3]);
#ifdef _DEBUG
    ASSERT_DEATH(quat[4], ".*");
#endif  // _DEBUG
}

/**
 * Test Quaternion Unary operator
 */
TEST_F(QuaternionTest_C, TestQuaternionUniary) {
    vne::math::Quaternion quat{1.0f, 2.0f, 3.2f, 1.1f};
    EXPECT_EQ(quat * -1.0f, -quat);
    EXPECT_EQ(quat, +quat);
}

/**
 * Test Quaternion stream out
 *
 * std::cout << quat << std::endl;
 */
TEST_F(QuaternionTest_C, TestQuaternionStreamOut) {
    std::ostringstream stream;
    vne::math::Quaternion quat = vne::math::Quaternion(glm::quat(2.0f, 0.0f, 0.0f, 1.0f));
    stream << quat;
    EXPECT_EQ(stream.str(), "[2, 0, 0, 1]");
}

/**
 * Test Quaternion SetFromEulerAngles() and GetEulerAngles()
 */
TEST_F(QuaternionTest_C, TestQuaternionEulerAngles) {
    vne::math::Quaternion quat;
    quat.setFromEulerAngles(vne::math::pi<float>() / 2, vne::math::pi<float>() / 4, vne::math::pi<float>() / 6);

    vne::math::Vec3f euler_angles = quat.getEulerAngles();

    EXPECT_TRUE(vne::math::areSame(vne::math::pi<float>() / 2, euler_angles.x, 1E-5f));
    EXPECT_TRUE(vne::math::areSame(vne::math::pi<float>() / 4, euler_angles.y, 1E-5f));
    EXPECT_TRUE(vne::math::areSame(vne::math::pi<float>() / 6, euler_angles.z, 1E-5f));
}

/**
 * Test Quaternion SetFromRotationMatrix()
 */
TEST_F(QuaternionTest_C, TestQuaternionSetFromRotationMatrix) {
    vne::math::Mat4x4f rotation_matrix = vne::math::Mat4x4f::rotate(vne::math::pi<float>() / 2, vne::math::Vec3f(1.0f, 0.0f, 0.0f));

    vne::math::Quaternion quat;
    quat.setFromRotationMatrix(rotation_matrix);

    vne::math::Vec3f euler_angles = quat.getEulerAngles();
    EXPECT_TRUE(vne::math::areSame(vne::math::pi<float>() / 2, euler_angles.x, 1E-5f));
    EXPECT_TRUE(vne::math::areSame(0.0f, euler_angles.y, 1E-5f));
    EXPECT_TRUE(vne::math::areSame(0.0f, euler_angles.z, 1E-5f));
}

/**
 * Test Quaternion Normalize()
 */
TEST_F(QuaternionTest_C, TestQuaternionNormalize) {
    vne::math::Quaternion quat{2.0f, 3.0f, 4.0f, 5.0f};

    vne::math::Quaternion normalized_quat = quat.normalize();
    EXPECT_TRUE(vne::math::areSame(1.0f, normalized_quat.length(), 1E-5f));
}

/**
 * Test Quaternion RotateVector()
 */
TEST_F(QuaternionTest_C, TestQuaternionRotateVector) {
    vne::math::Quaternion quat;
    quat.setFromAxisAngle(vne::math::pi<float>() / 2, vne::math::Vec3f(0.0f, 0.0f, 1.0f));

    vne::math::Vec3f vec(1.0f, 0.0f, 0.0f);

    vne::math::Vec3f rotated_vec = quat.rotateVector(vec);
    EXPECT_TRUE(vne::math::areSame(0.0f, rotated_vec.x, 1E-5f));
    EXPECT_TRUE(vne::math::areSame(1.0f, rotated_vec.y, 1E-5f));
    EXPECT_TRUE(vne::math::areSame(0.0f, rotated_vec.z, 1E-5f));
}

/**
 * Test Quaternion SetIdentity()
 */
TEST_F(QuaternionTest_C, TestQuaternionSetIdentity) {
    vne::math::Quaternion quat{2.0f, 3.0f, 4.0f, 5.0f};

    quat.setIdentity();
    EXPECT_EQ(1.0f, quat.w);
    EXPECT_EQ(0.0f, quat.x);
    EXPECT_EQ(0.0f, quat.y);
    EXPECT_EQ(0.0f, quat.z);
}

/**
 * Test Quaternion MakeRotate()
 */
TEST_F(QuaternionTest_C, TestQuaternionMakeRotate) {
    vne::math::Vec3f from(1.0f, 0.0f, 0.0f);
    vne::math::Vec3f to(0.0f, 1.0f, 0.0f);

    vne::math::Quaternion quat;
    quat.makeRotate(from, to);

    vne::math::Vec3f rotated_vec = quat.rotateVector(from);
    EXPECT_TRUE(vne::math::areSame(to.x, rotated_vec.x, 1E-5f));
    EXPECT_TRUE(vne::math::areSame(to.y, rotated_vec.y, 1E-5f));
    EXPECT_TRUE(vne::math::areSame(to.z, rotated_vec.z, 1E-5f));
}

/**
 * Test Quaternion Slerp()
 */
TEST_F(QuaternionTest_C, TestQuaternionSlerp) {
    vne::math::Quaternion quat1{1.0f, 0.0f, 0.0f, 0.0f};
    vne::math::Quaternion quat2{0.0f, 1.0f, 0.0f, 0.0f};

    vne::math::Quaternion slerped_quat = vne::math::Quaternion::slerp(quat1, quat2, 0.5f);

    EXPECT_TRUE(vne::math::areSame(0.7071f, slerped_quat.w, 1E-4f));
    EXPECT_TRUE(vne::math::areSame(0.7071f, slerped_quat.x, 1E-4f));
    EXPECT_TRUE(vne::math::areSame(0.0f, slerped_quat.y, 1E-4f));
    EXPECT_TRUE(vne::math::areSame(0.0f, slerped_quat.z, 1E-4f));
}

/**
 * Test Quaternion Normalize (Static)
 */
TEST_F(QuaternionTest_C, TestQuaternionNormalizeStatic) {
    vne::math::Quaternion quat{2.0f, 3.0f, 4.0f, 5.0f};

    vne::math::Quaternion normalized_quat = vne::math::Quaternion::normalize(quat);
    EXPECT_TRUE(vne::math::areSame(1.0f, normalized_quat.length(), 1E-5f));
}

/**
 * Test Quaternion Conjugate (Static)
 */
TEST_F(QuaternionTest_C, TestQuaternionConjugateStatic) {
    vne::math::Quaternion quat{2.0f, 3.0f, 4.0f, 5.0f};

    vne::math::Quaternion conjugated_quat = vne::math::Quaternion::Conjugate(quat);
    EXPECT_EQ(vne::math::Quaternion(2.0f, -3.0f, -4.0f, -5.0f), conjugated_quat);
}

/**
 * Test Quaternion Inverse (Static)
 */
TEST_F(QuaternionTest_C, TestQuaternionInverseStatic) {
    vne::math::Quaternion quat{2.0f, 3.0f, 4.0f, 5.0f};

    vne::math::Quaternion inverse_quat = vne::math::Quaternion::Inverse(quat);
    EXPECT_EQ(quat.conjugate() / quat.lengthSquared(), inverse_quat);
}

/**
 * Test Quaternion operator[] const
 */
TEST_F(QuaternionTest_C, TestQuaternionIndexOperatorConst) {
    const vne::math::Quaternion quat{1.0f, 2.0f, 3.0f, 4.0f};

    // Valid index access
    EXPECT_EQ(2.0f, quat[0]);  // x
    EXPECT_EQ(3.0f, quat[1]);  // y
    EXPECT_EQ(4.0f, quat[2]);  // z
    EXPECT_EQ(1.0f, quat[3]);  // w

#ifdef _DEBUG
    // Invalid index access, should cause assertion failure
    EXPECT_DEATH(quat[4], "Quaternion index out of bounds");
#endif  // _DEBUG
}

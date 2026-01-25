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
    Math::Quaternion_C quat0 = Math::Quaternion_C();
    EXPECT_EQ(1.0f, quat0.w);
    EXPECT_EQ(0.0f, quat0.x);
    EXPECT_EQ(0.0f, quat0.y);
    EXPECT_EQ(0.0f, quat0.z);

    Math::Quaternion_C quat1 = Math::Quaternion_C(Math::Vec4f_C(1.0f, 0.0f, 0.0f, 3.0f));
    EXPECT_EQ(3.0f, quat1.w);
    EXPECT_EQ(1.0f, quat1.x);
    EXPECT_EQ(0.0f, quat1.y);
    EXPECT_EQ(0.0f, quat1.z);

    Math::Quaternion_C quat2 = Math::Quaternion_C(Math::Vec3f_C(0.707f, 0.0f, 0.707f));
    EXPECT_EQ(1.0f, quat2.w);
    EXPECT_EQ(0.707f, quat2.x);
    EXPECT_EQ(0.0f, quat2.y);
    EXPECT_EQ(0.707f, quat2.z);

    Math::Quaternion_C quat3 = Math::Quaternion_C(2.0f, 0.0f, 0.0f, 1.0f);
    EXPECT_EQ(2.0f, quat3.w);
    EXPECT_EQ(0.0f, quat3.x);
    EXPECT_EQ(0.0f, quat3.y);
    EXPECT_EQ(1.0f, quat3.z);

    Math::Quaternion_C quat4 = Math::Quaternion_C(glm::quat(2.0f, 0.0f, 0.0f, 1.0f));
    EXPECT_EQ(2.0f, quat4.w);
    EXPECT_EQ(0.0f, quat4.x);
    EXPECT_EQ(0.0f, quat4.y);
    EXPECT_EQ(1.0f, quat4.z);

    Math::Quaternion_C quat5 = Math::Quaternion_C(Math::QuarterPi<float>(), Math::Vec3f_C(0.0f, 1.0f, 0.0f));
    EXPECT_TRUE(Math::AreSame(0.785398f, quat5.w, 1E-5f));
    EXPECT_EQ(0.0f, quat5.x);
    EXPECT_EQ(1.0f, quat5.y);
    EXPECT_EQ(0.0f, quat5.z);
}

/**
 * Test Quaternion_C GetW() and GetVector()
 */
TEST_F(QuaternionTest_C, TestQuaternionGetVecAndW) {
    Math::Quaternion_C quat{1.0f, 13.0f, 12.0f, 5.0f};
    EXPECT_EQ(1.0f, quat.GetW());
    EXPECT_EQ(Math::Vec3f_C(13.0f, 12.0f, 5.0f), quat.GetVector());
}

/**
 * Test Quaternion_C angle and axis
 *
 * quat.GetAngle()
 * quat.GetAxis()
 * quat.SetAngleAxis(float, Math::Vec3f_C)
 * quat.GetAngleAxis(float&, Math::Vec3f_C&)
 *
 */
TEST_F(QuaternionTest_C, TestQuaternionAngleAndAxis) {
    Math::Quaternion_C quat{-0.0474207f, 0.756477f, 0.147957f, -0.635297f};
    // Get angle
    EXPECT_EQ(2.0f * Math::ACos(quat.w), quat.GetAngle());
    // Get axis
    EXPECT_TRUE(quat.GetVector().AreSame(quat.GetAxis() * Math::Sin(0.5f * quat.GetAngle()), 1E-5f));
    // Set angle and axis
    quat.Clear();
    float angle = Math::DegToRad(60.0f);
    Math::Vec3f_C axis{0.756477f, 0.147957f, -0.635297f};
    quat.SetAngleAndAxis(angle, axis);
    EXPECT_TRUE(Math::AreSame(quat.GetW(), Math::Cos(0.5f * quat.GetAngle()), 1E-5f));
    EXPECT_TRUE(quat.GetVector().AreSame(quat.GetAxis() * Math::Sin(0.5f * quat.GetAngle()), 1E-5f));
    // Get angle and axis
    float new_angle;
    Math::Vec3f_C new_axis;
    quat.GetAngleAndAxis(new_angle, new_axis);
    EXPECT_TRUE(Math::AreSame(angle, new_angle));
    EXPECT_TRUE(new_axis.AreSame(axis));
}

/**
 * Test Quaternion_C X, Y, and Z axes
 *
 * quat.GetXAxis()
 * quat.GetYAxis()
 * quat.GetZAxis()
 *
 */
TEST_F(QuaternionTest_C, TestQuaternionAxes) {
    Math::Quaternion_C quat{-0.0474207f, 0.756477f, 0.147957f, -0.635297f};

    // Expected X, Y, Z axes after rotation
    Math::Vec3f_C expected_x_axis = quat * Math::Vec3f_C(1.0f, 0.0f, 0.0f);
    Math::Vec3f_C expected_y_axis = quat * Math::Vec3f_C(0.0f, 1.0f, 0.0f);
    Math::Vec3f_C expected_z_axis = quat * Math::Vec3f_C(0.0f, 0.0f, 1.0f);

    // Test X Axis
    Math::Vec3f_C x_axis = quat.GetXAxis();
    EXPECT_TRUE(expected_x_axis.AreSame(x_axis, 1E-5f));

    // Test Y Axis
    Math::Vec3f_C y_axis = quat.GetYAxis();
    EXPECT_TRUE(expected_y_axis.AreSame(y_axis, 1E-5f));

    // Test Z Axis
    Math::Vec3f_C z_axis = quat.GetZAxis();
    EXPECT_TRUE(expected_z_axis.AreSame(z_axis, 1E-5f));
}

/**
 * Test Quaternion_C Clear()
 */
TEST_F(QuaternionTest_C, TestQuaternionClear) {
    Math::Quaternion_C quat{2.0f, 13.0f, 12.0f, 5.0f};

    quat.Clear();
    EXPECT_EQ(1.0f, quat.GetW());
    EXPECT_EQ(Math::Vec3f_C(), quat.GetVector());
}

/**
 * Test Quaternion_C Length
 *
 * quat.Length()
 * quat.LengthSquared()
 *
 */
TEST_F(QuaternionTest_C, TestQuaternionLength) {
    Math::Quaternion_C quat{0.0f, 12.0f, 5.0f, 0.0f};

    EXPECT_EQ(13.0f, quat.Length());
    EXPECT_EQ(quat.Length(), Math::Sqrt(quat.LengthSquared()));
}

/**
 * Test Quaternion_C Conjugate
 *
 * quat.Conjugate()
 *
 */
TEST_F(QuaternionTest_C, TestQuaternionConjugate) {
    Math::Quaternion_C quat{1.0f, 13.0f, 12.0f, 5.0f};

    EXPECT_EQ(Math::Quaternion_C(1.0f, -13.0f, -12.0f, -5.0f), quat.Conjugate());
}

/**
 * Test Quaternion_C Inverse
 *
 * quat.Inverse()
 *
 */
TEST_F(QuaternionTest_C, TestQuaternionInverse) {
    Math::Quaternion_C quat{1.0f, 13.0f, 12.0f, 5.0f};
    EXPECT_EQ(quat.Conjugate() / quat.LengthSquared(), quat.Inverse());

    Math::Quaternion_C quat1{0.0f, 0.0f, 1.0f, 0.0f};
    EXPECT_EQ(quat1.Conjugate(), quat1.Inverse());
}

/**
 * Test Quaternion_C Dot
 *
 * quat.Dot()
 * Quaternion_C::Dot(const Quaternion_C&, const Quaternion_C&)
 *
 */
TEST_F(QuaternionTest_C, TestQuaternionDot) {
    Math::Quaternion_C quat1{1.0f, 0.0f, 12.0f, 5.0f};
    Math::Quaternion_C quat2{1.0f, 0.0f, 12.0f, 5.0f};
    EXPECT_EQ(170.0f, quat1.Dot(quat2));
    EXPECT_EQ(170.0f, Math::Quaternion_C::Dot(quat1, quat2));
}

/**
 * Test Quaternion_C addition
 */
TEST_F(QuaternionTest_C, TestQuaternionAddition) {
    Math::Quaternion_C quat1{0.0f, 2.0f, 3.0f, 0.0f};
    Math::Quaternion_C quat2{1.0f, 13.0f, 12.0f, 5.0f};
    EXPECT_EQ(Math::Quaternion_C(1.0f, 15.0f, 15.0f, 5.0f), quat2 + quat1);
    EXPECT_EQ(quat2, quat2 += quat1);
}

/**
 * Test Quaternion_C subtraction
 */
TEST_F(QuaternionTest_C, TestQuaternionSubtraction) {
    Math::Quaternion_C quat1{0.0f, 0.0f, 2.0f, 3.0f};
    Math::Quaternion_C quat2{1.0f, 13.0f, 12.0f, 5.0f};
    EXPECT_EQ(Math::Quaternion_C(1.0f, 13.0f, 10.0f, 2.0f), quat2 - quat1);
    EXPECT_EQ(quat2, quat2 -= quat1);
}

/**
 * Test Quaternion_C -> quaternion to vector multiplication
 */
TEST_F(QuaternionTest_C, TestQuaternionxVector) {
    Math::Quaternion_C quat{1.0f, 13.0f, 12.0f, 5.0f};
    Math::Vec3f_C vec{3.0f, 4.0f, 5.0f};
    EXPECT_EQ(glm::quat(1.0f, 13.0f, 12.0f, 5.0f) * glm::vec3(3.0f, 4.0f, 5.0f), quat * vec);
    EXPECT_EQ(glm::vec3(3.0f, 4.0f, 5.0f) * glm::quat(1.0f, 13.0f, 12.0f, 5.0f), vec * quat);
}

/**
 * Test Quaternion_C multiplication
 */
TEST_F(QuaternionTest_C, TestQuaternionMultiplication) {
    Math::Quaternion_C quat1{0.0f, 2.0f, 3.0f, 0.0f};
    Math::Quaternion_C quat2{1.0f, 13.0f, 12.0f, 5.0f};
    float scalar = 2.0f;
    EXPECT_EQ(Math::Quaternion_C(-62.0f, 17.0f, -7.0f, -15.0f), quat1 * quat2);
    EXPECT_EQ(quat2, quat2 *= quat1);
    EXPECT_EQ(Math::Quaternion_C(0.0f, 4.0f, 6.0f, 0.0f), quat1 * scalar);
    EXPECT_EQ(Math::Quaternion_C(0.0f, 4.0f, 6.0f, 0.0f), scalar * quat1);
    EXPECT_EQ(quat1, quat1 *= scalar);
}

/**
 * Test Quaternion_C division
 */
TEST_F(QuaternionTest_C, TestQuaternionDivision) {
    float scalar = 2.0f;
    Math::Quaternion_C quat{3.0f, 2.0f, 4.2f, 1.0f};

    EXPECT_EQ(Math::Quaternion_C(1.5f, 1.0f, 2.1f, 0.5f), quat / scalar);

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
 * Test Quaternion_C comparison
 *
 */
TEST_F(QuaternionTest_C, TestQuaternionComparison) {
    Math::Quaternion_C quat1{0.0f, 2.0f, 3.2f, 1.1f};
    Math::Quaternion_C quat2{1.0f, 1.22f, 0.342f, 1.0f};
    EXPECT_TRUE(quat1 != quat2);

    Math::Quaternion_C equal_quat = quat2;
    EXPECT_TRUE(equal_quat == quat2);
    EXPECT_TRUE(equal_quat != quat1);
}

/**
 * Test Quaternion_C assignment
 */
TEST_F(QuaternionTest_C, TestQuaternionAssignment) {
    Math::Quaternion_C test_quat;
    Math::Quaternion_C quat{1.0f, 2.0f, 3.2f, 1.1f};
    EXPECT_EQ(quat, test_quat = quat);
}

/**
 * Test Quaternion_C specific component
 */
TEST_F(QuaternionTest_C, TestQuaternionComponent) {
    float value;
    Math::Quaternion_C quat{1.0f, 2.0f, 3.2f, 1.1f};
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
 * Test Quaternion_C Unary operator
 */
TEST_F(QuaternionTest_C, TestQuaternionUniary) {
    Math::Quaternion_C quat{1.0f, 2.0f, 3.2f, 1.1f};
    EXPECT_EQ(quat * -1.0f, -quat);
    EXPECT_EQ(quat, +quat);
}

/**
 * Test Quaternion_C stream out
 *
 * std::cout << quat << std::endl;
 */
TEST_F(QuaternionTest_C, TestQuaternionStreamOut) {
    std::ostringstream stream;
    Math::Quaternion_C quat = Math::Quaternion_C(glm::quat(2.0f, 0.0f, 0.0f, 1.0f));
    stream << quat;
    EXPECT_EQ(stream.str(), "[2, 0, 0, 1]");
}

/**
 * Test Quaternion_C SetFromEulerAngles() and GetEulerAngles()
 */
TEST_F(QuaternionTest_C, TestQuaternionEulerAngles) {
    Math::Quaternion_C quat;
    quat.SetFromEulerAngles(Math::Pi<float>() / 2, Math::Pi<float>() / 4, Math::Pi<float>() / 6);

    Math::Vec3f_C euler_angles = quat.GetEulerAngles();

    EXPECT_TRUE(Math::AreSame(Math::Pi<float>() / 2, euler_angles.x, 1E-5f));
    EXPECT_TRUE(Math::AreSame(Math::Pi<float>() / 4, euler_angles.y, 1E-5f));
    EXPECT_TRUE(Math::AreSame(Math::Pi<float>() / 6, euler_angles.z, 1E-5f));
}

/**
 * Test Quaternion_C SetFromRotationMatrix()
 */
TEST_F(QuaternionTest_C, TestQuaternionSetFromRotationMatrix) {
    Math::Mat4x4f_C rotation_matrix = Math::Mat4x4f_C::Rotate(Math::Pi<float>() / 2, Math::Vec3f_C(1.0f, 0.0f, 0.0f));

    Math::Quaternion_C quat;
    quat.SetFromRotationMatrix(rotation_matrix);

    Math::Vec3f_C euler_angles = quat.GetEulerAngles();
    EXPECT_TRUE(Math::AreSame(Math::Pi<float>() / 2, euler_angles.x, 1E-5f));
    EXPECT_TRUE(Math::AreSame(0.0f, euler_angles.y, 1E-5f));
    EXPECT_TRUE(Math::AreSame(0.0f, euler_angles.z, 1E-5f));
}

/**
 * Test Quaternion_C Normalize()
 */
TEST_F(QuaternionTest_C, TestQuaternionNormalize) {
    Math::Quaternion_C quat{2.0f, 3.0f, 4.0f, 5.0f};

    Math::Quaternion_C normalized_quat = quat.Normalize();
    EXPECT_TRUE(Math::AreSame(1.0f, normalized_quat.Length(), 1E-5f));
}

/**
 * Test Quaternion_C RotateVector()
 */
TEST_F(QuaternionTest_C, TestQuaternionRotateVector) {
    Math::Quaternion_C quat;
    quat.SetFromAxisAngle(Math::Pi<float>() / 2, Math::Vec3f_C(0.0f, 0.0f, 1.0f));

    Math::Vec3f_C vec(1.0f, 0.0f, 0.0f);

    Math::Vec3f_C rotated_vec = quat.RotateVector(vec);
    EXPECT_TRUE(Math::AreSame(0.0f, rotated_vec.x, 1E-5f));
    EXPECT_TRUE(Math::AreSame(1.0f, rotated_vec.y, 1E-5f));
    EXPECT_TRUE(Math::AreSame(0.0f, rotated_vec.z, 1E-5f));
}

/**
 * Test Quaternion_C SetIdentity()
 */
TEST_F(QuaternionTest_C, TestQuaternionSetIdentity) {
    Math::Quaternion_C quat{2.0f, 3.0f, 4.0f, 5.0f};

    quat.SetIdentity();
    EXPECT_EQ(1.0f, quat.w);
    EXPECT_EQ(0.0f, quat.x);
    EXPECT_EQ(0.0f, quat.y);
    EXPECT_EQ(0.0f, quat.z);
}

/**
 * Test Quaternion_C MakeRotate()
 */
TEST_F(QuaternionTest_C, TestQuaternionMakeRotate) {
    Math::Vec3f_C from(1.0f, 0.0f, 0.0f);
    Math::Vec3f_C to(0.0f, 1.0f, 0.0f);

    Math::Quaternion_C quat;
    quat.MakeRotate(from, to);

    Math::Vec3f_C rotated_vec = quat.RotateVector(from);
    EXPECT_TRUE(Math::AreSame(to.x, rotated_vec.x, 1E-5f));
    EXPECT_TRUE(Math::AreSame(to.y, rotated_vec.y, 1E-5f));
    EXPECT_TRUE(Math::AreSame(to.z, rotated_vec.z, 1E-5f));
}

/**
 * Test Quaternion_C Slerp()
 */
TEST_F(QuaternionTest_C, TestQuaternionSlerp) {
    Math::Quaternion_C quat1{1.0f, 0.0f, 0.0f, 0.0f};
    Math::Quaternion_C quat2{0.0f, 1.0f, 0.0f, 0.0f};

    Math::Quaternion_C slerped_quat = Math::Quaternion_C::Slerp(quat1, quat2, 0.5f);

    EXPECT_TRUE(Math::AreSame(0.7071f, slerped_quat.w, 1E-4f));
    EXPECT_TRUE(Math::AreSame(0.7071f, slerped_quat.x, 1E-4f));
    EXPECT_TRUE(Math::AreSame(0.0f, slerped_quat.y, 1E-4f));
    EXPECT_TRUE(Math::AreSame(0.0f, slerped_quat.z, 1E-4f));
}

/**
 * Test Quaternion_C Normalize (Static)
 */
TEST_F(QuaternionTest_C, TestQuaternionNormalizeStatic) {
    Math::Quaternion_C quat{2.0f, 3.0f, 4.0f, 5.0f};

    Math::Quaternion_C normalized_quat = Math::Quaternion_C::Normalize(quat);
    EXPECT_TRUE(Math::AreSame(1.0f, normalized_quat.Length(), 1E-5f));
}

/**
 * Test Quaternion_C Conjugate (Static)
 */
TEST_F(QuaternionTest_C, TestQuaternionConjugateStatic) {
    Math::Quaternion_C quat{2.0f, 3.0f, 4.0f, 5.0f};

    Math::Quaternion_C conjugated_quat = Math::Quaternion_C::Conjugate(quat);
    EXPECT_EQ(Math::Quaternion_C(2.0f, -3.0f, -4.0f, -5.0f), conjugated_quat);
}

/**
 * Test Quaternion_C Inverse (Static)
 */
TEST_F(QuaternionTest_C, TestQuaternionInverseStatic) {
    Math::Quaternion_C quat{2.0f, 3.0f, 4.0f, 5.0f};

    Math::Quaternion_C inverse_quat = Math::Quaternion_C::Inverse(quat);
    EXPECT_EQ(quat.Conjugate() / quat.LengthSquared(), inverse_quat);
}

/**
 * Test Quaternion_C operator[] const
 */
TEST_F(QuaternionTest_C, TestQuaternionIndexOperatorConst) {
    const Math::Quaternion_C quat{1.0f, 2.0f, 3.0f, 4.0f};

    // Valid index access
    EXPECT_EQ(2.0f, quat[0]);  // x
    EXPECT_EQ(3.0f, quat[1]);  // y
    EXPECT_EQ(4.0f, quat[2]);  // z
    EXPECT_EQ(1.0f, quat[3]);  // w

#ifdef _DEBUG
    // Invalid index access, should cause assertion failure
    EXPECT_DEATH(quat[4], "Quaternion_C index out of bounds");
#endif  // _DEBUG
}

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
#include "vertexnova/math/mat3x3f.h"

using namespace VNE;

class Mat3x3fTest_C : public ::testing::Test {
    // Interface of test fixture base class
   protected:
    void SetUp() override {
        mat = Math::Mat3x3f_C(0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f);
        mat2 = Math::Mat3x3f_C(-14.0f, -20.0f, -26.0f, -32.0f, -8.0f, -10.0f, -12.0f, -14.0f, -2.0f);
        mat3 = Math::Mat3x3f_C(2.0f, 3.0f, 1.0f, 5.0f, 1.0f, 0.0f, 3.0f, 1.0f, 2.0f);
    }

    void TearDown() override {}

   protected:
    Math::Mat3x3f_C mat;
    Math::Mat3x3f_C mat2;
    Math::Mat3x3f_C mat3;
};

/**
 * Test GetColumn(uint32_t idx)
 *
 * mat.GetColumn(0)
 *
 */
TEST_F(Mat3x3fTest_C, TestMat3x3fColumn) {
    Math::Mat3x3f_C out = Math::Mat3x3f_C(Math::Vec3f_C(1.0f), Math::Vec3f_C(2.0f), Math::Vec3f_C(3.0f));
    EXPECT_EQ(Math::Vec3f_C(1.0f), out.GetColumn(0));
    EXPECT_EQ(Math::Vec3f_C(2.0f), out.GetColumn(1));
    EXPECT_EQ(Math::Vec3f_C(3.0f), out.GetColumn(2));
}

/**
 * Test GetRow(uint32_t idx)
 *
 * mat.GetRow(0)
 *
 */
TEST_F(Mat3x3fTest_C, TestMat3x3fRow) {
    EXPECT_EQ(Math::Vec3f_C(0.0f, 3.0f, 6.0f), mat.GetRow(0));
    EXPECT_EQ(Math::Vec3f_C(1.0f, 4.0f, 7.0f), mat.GetRow(1));
    EXPECT_EQ(Math::Vec3f_C(2.0f, 5.0f, 8.0f), mat.GetRow(2));
}

/**
 * Test XAxis(), YAxis() and ZAxis()
 *
 * mat.XAxis()
 * mat.YAxis()
 * mat.ZAxis()
 *
 */
TEST_F(Mat3x3fTest_C, TestMat3x3fXYZAxes) {
    Math::Mat3x3f_C out = Math::Mat3x3f_C(Math::Vec3f_C(1.0f), Math::Vec3f_C(2.0f), Math::Vec3f_C(3.0f));
    EXPECT_EQ(Math::Vec3f_C(1.0f), out.XAxis());
    EXPECT_EQ(Math::Vec3f_C(2.0f), out.YAxis());
    EXPECT_EQ(Math::Vec3f_C(3.0f), out.ZAxis());
}

/**
 * Test Determinant()
 *
 * mat.Determinant()
 *
 */
TEST_F(Mat3x3fTest_C, TestMat3x3fDeterminant) {
    Math::Mat3x3f_C out = Math::Mat3x3f_C(Math::Vec3f_C(2.0f, 2.0f, 1.0f), Math::Vec3f_C(-3.0f, 0.0f, 4.0f), Math::Vec3f_C(1.0f, -1.0f, 5.0f));
    EXPECT_EQ(49.0f, out.Determinant());

    out = Math::Mat3x3f_C(Math::Vec3f_C(1.0f, -3.0f, 2.0f), Math::Vec3f_C(3.0f, -1.0f, 3.0f), Math::Vec3f_C(2.0f, -3.0f, 1.0f));
    EXPECT_EQ(-15.0f, out.Determinant());
}

/**
 * Test Trace()
 *
 * mat.Trace()
 *
 */
TEST_F(Mat3x3fTest_C, TestMat3x3fTrace) {
    Math::Mat3x3f_C out = Math::Mat3x3f_C(Math::Vec3f_C(-5.0f, 1.0f, -3.0f), Math::Vec3f_C(0.0f, 2.0f, 4.0f), Math::Vec3f_C(-1.0f, -1.0f, 1.0f));
    EXPECT_EQ(-40.0f, out.Determinant());
    EXPECT_EQ(-2.0f, out.Trace());
}

/**
 * Test Transpose()
 *
 * mat.Transpose()
 *
 */
TEST_F(Mat3x3fTest_C, TestMat3x3fTranspose) {
    Math::Mat3x3f_C out = Math::Mat3x3f_C(Math::Vec3f_C(3.0f, 4.0f, 3.0f), Math::Vec3f_C(2.0f, 0.0f, 0.0f), Math::Vec3f_C(0.0f, 1.0f, 2.0f));
    Math::Mat3x3f_C trans = out.Transpose();

    EXPECT_EQ(out.GetColumn(0), trans.GetRow(0));
    EXPECT_EQ(out.GetColumn(1), trans.GetRow(1));
    EXPECT_EQ(out.GetColumn(2), trans.GetRow(2));
}

/**
 * Test Inverse()
 *
 * mat.Inverse()
 *
 */
TEST_F(Mat3x3fTest_C, TestMat3x3fInverse) {
    Math::Mat3x3f_C out = Math::Mat3x3f_C(Math::Vec3f_C(3.0f, 2.0f, 0.0f), Math::Vec3f_C(0.0f, 0.0f, 1.0f), Math::Vec3f_C(2.0f, -2.0f, 1.0f));

    EXPECT_EQ(10.0f, out.Determinant());
    Math::Mat3x3f_C inv = out.Inverse();

    EXPECT_EQ(Math::Vec3f_C(0.2f, -0.2f, 0.2f), inv.GetColumn(0));
    EXPECT_EQ(Math::Vec3f_C(0.2f, 0.3f, -0.3f), inv.GetColumn(1));
    EXPECT_EQ(Math::Vec3f_C(0.0f, 1.0f, 0.0f), inv.GetColumn(2));
}

/**
 * Test InverseTransposed()
 *
 * mat.InverseTransposed()
 *
 */
TEST_F(Mat3x3fTest_C, TestMat3x3fInverseTransposed) {
    Math::Mat3x3f_C transform = Math::Mat3x3f_C(Math::Vec3f_C(-1.0f, 3.0f, 1.0f), Math::Vec3f_C(-3.0f, 6.0f, 0.0f), Math::Vec3f_C(1.0f, 0.0f, 1.0f));

    Math::Mat3x3f_C inv_transpose = transform.InverseTransposed();

    Math::Mat3x3f_C transpose = transform.Transpose();
    EXPECT_EQ(Math::Vec3f_C(-2.0f, -1.0f, 2.0f), inv_transpose.GetColumn(0));
    EXPECT_EQ(Math::Vec3f_C(1.0f, 2.0f / 3.0f, -1.0f), inv_transpose.GetColumn(1));
    EXPECT_EQ(Math::Vec3f_C(2.0f, 1.0f, -1.0f), inv_transpose.GetColumn(2));
}

/**
 * Test Assignment Operator
 */
TEST_F(Mat3x3fTest_C, TestMat3x3fAssignment) {
    Math::Mat3x3f_C local_mat = mat3;
    EXPECT_EQ(local_mat, mat3);
}

/**
 * Test Addition Operator
 */
TEST_F(Mat3x3fTest_C, TestMat3x3fAddition) {
    Math::Mat3x3f_C result = mat + mat3;
    EXPECT_EQ(result, Math::Mat3x3f_C(2.0f, 4.0f, 3.0f, 8.0f, 5.0f, 5.0f, 9.0f, 8.0f, 10.0f));
}

/**
 * Test Addition Assignment Operator
 */
TEST_F(Mat3x3fTest_C, TestMat3x3fAdditionAssignment) {
    Math::Mat3x3f_C local_mat = mat;
    local_mat += mat3;
    EXPECT_EQ(local_mat, Math::Mat3x3f_C(2.0f, 4.0f, 3.0f, 8.0f, 5.0f, 5.0f, 9.0f, 8.0f, 10.0f));
}

/**
 * Test Subtraction Operator
 */
TEST_F(Mat3x3fTest_C, TestMat3x3fSubtraction) {
    Math::Mat3x3f_C result = mat - mat3;
    EXPECT_EQ(result, Math::Mat3x3f_C(-2.0f, -2.0f, 1.0f, -2.0f, 3.0f, 5.0f, 3.0f, 6.0f, 6.0f));
}

/**
 * Test Subtraction Assignment Operator
 */
TEST_F(Mat3x3fTest_C, TestMat3x3fSubtractionAssignment) {
    Math::Mat3x3f_C local_mat = mat;
    local_mat -= mat3;
    EXPECT_EQ(local_mat, Math::Mat3x3f_C(-2.0f, -2.0f, 1.0f, -2.0f, 3.0f, 5.0f, 3.0f, 6.0f, 6.0f));
}

/**
 * Test Multiplication Operator
 */
TEST_F(Mat3x3fTest_C, TestMat3x3fMultiplication) {
    Math::Mat3x3f_C result = mat * mat3;  // coulumn major
    EXPECT_EQ(result, Math::Mat3x3f_C(15.0f, 21.0f, 27.0f, 3.0f, 9.0f, 15.0f, 15.0f, 21.0f, 27.0f));
}

/**
 * Test Multiplication Assignment Operator
 */
TEST_F(Mat3x3fTest_C, TestMat3x3fMultiplicationAssignment) {
    Math::Mat3x3f_C local_mat = mat;
    local_mat *= mat3;
    EXPECT_EQ(local_mat, Math::Mat3x3f_C(15.0f, 21.0f, 27.0f, 3.0f, 9.0f, 15.0f, 15.0f, 21.0f, 27.0f));
}

/**
 * Test Scalar Multiplication Operator
 *
 * mat * 2.0f
 */
TEST_F(Mat3x3fTest_C, TestMat3x3fScalarMultiplication) {
    Math::Mat3x3f_C result = mat * 2.0f;
    EXPECT_EQ(result, Math::Mat3x3f_C(0.0f, 2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f));
}

/**
 * Test Scalar Multiplication Assignment Operator
 *
 * mat *= 2.0f
 */
TEST_F(Mat3x3fTest_C, TestMat3x3fScalarMultiplicationAssignment) {
    mat *= 2.0f;
    EXPECT_EQ(mat, Math::Mat3x3f_C(0.0f, 2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f));
}

/**
 * Test Scalar Division Operator
 *
 * mat / 2.0f
 */
TEST_F(Mat3x3fTest_C, TestMat3x3fScalarDivision) {
    Math::Mat3x3f_C result = mat / 2.0f;
    EXPECT_EQ(result, Math::Mat3x3f_C(0.0f, 0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f));
}

/**
 * Test Scalar Division Assignment Operator
 *
 * mat /= 2.0f
 */
TEST_F(Mat3x3fTest_C, TestMat3x3fScalarDivisionAssignment) {
    mat /= 2.0f;
    EXPECT_EQ(mat, Math::Mat3x3f_C(0.0f, 0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f));
}

/**
 * Test Mat3x3f_C stream out
 *
 * std::cout << mat << std::endl;
 */
TEST_F(Mat3x3fTest_C, TestMat3x3fStreamOut) {
    std::ostringstream stream;
    stream << mat;
    EXPECT_EQ(stream.str(), "[[0, 1, 2],\n [3, 4, 5],\n [6, 7, 8]]");
}

/**
 * Test Mat3x3f_C Identity
 *
 * Math::Math4x4f_C::Identity()
 *
 */
TEST_F(Mat3x3fTest_C, TestMat3x3fIdentity) {
    EXPECT_EQ(Math::Mat3x3f_C(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f), Math::Mat3x3f_C::Identity());
}

/**
 * Test Mat3x3f_C Zero
 *
 * Math::Mat3x3f_C::Zero()
 *
 */
TEST_F(Mat3x3fTest_C, TestMat3x3fZero) {
    EXPECT_EQ(Math::Mat3x3f_C(0.0f), Math::Mat3x3f_C::Zero());
}

/**
 * Test Mat3x3f_C Lerp
 *
 * Math::Mat3x3f_C::Lerp(const Math::Mat3x3f_C&, const Math::Mat3x3f_C&, float)
 *
 */
TEST_F(Mat3x3fTest_C, TestMat3x3fLerp) {
    Math::Mat3x3f_C from = mat;
    Math::Mat3x3f_C to = mat3;
    EXPECT_EQ(Math::Mat3x3f_C(Math::Vec3f_C(1.0f, 2.0f, 1.5f), Math::Vec3f_C(4.0f, 2.5f, 2.5f), Math::Vec3f_C(4.5f, 4.0f, 5.0f)),
              Math::Mat3x3f_C::Lerp(from, to, 0.5f));
}

/**
 * Test RotationMatrix()
 *
 * mat.RotationMatrix(const Vec3f_C&, const Vec3f_C&, const Vec3f_C&)
 *
 */
TEST_F(Mat3x3fTest_C, TestMat3x3fRotationMatrix) {
    Math::Mat3x3f_C out;

    EXPECT_EQ(Math::Mat3x3f_C(Math::Vec3f_C::XAxis(), Math::Vec3f_C::YAxis(), Math::Vec3f_C::ZAxis()),
              out.RotationMatrix(Math::Vec3f_C::XAxis(), Math::Vec3f_C::YAxis(), Math::Vec3f_C::ZAxis()));
}

/**
 * Test Mat3x3f_C Scale
 *
 * Math::Mat3x3f_C::Scale(Math::Vec3f_C(1.0f, 2.0f, 3.0f))
 * Math::Mat3x3f_C::Scale(1.0f, 2.0f, 3.0f)
 * Math::Mat3x3f_C::Scale(1.0f)
 *
 */
TEST_F(Mat3x3fTest_C, TestMat3x3fScale) {
    Math::Mat3x3f_C out = Math::Mat3x3f_C::Identity();

    out[0][0] = 1.0f;
    out[1][1] = 2.0f;
    out[2][2] = 3.0f;
    EXPECT_EQ(out, Math::Mat3x3f_C::Scale(Math::Vec3f_C(1.0f, 2.0f, 3.0f)));

    out[0][0] = 4.0f;
    out[1][1] = 5.0f;
    out[2][2] = 6.0f;
    EXPECT_EQ(out, Math::Mat3x3f_C::Scale(4.0f, 5.0f, 6.0f));

    out[0][0] = out[1][1] = out[2][2] = 10.0f;
    EXPECT_EQ(out, Math::Mat3x3f_C::Scale(10.0f));
}

/**
 * Test Mat3x3f_C Rotate
 *
 * Math::Mat3x3f_C::Rotate(PI, Math::Vec3f_C(1.0f, 1.0f, 1.0f))
 *
 * Math::Mat3x3f_C::RotateX(PI)
 * Math::Mat3x3f_C::RotateY(PI)
 * Math::Mat3x3f_C::RotateZ(PI)
 * Math::Mat3x3f_C::RotateXYZ(PI)
 * Math::Mat3x3f_C::RotateZYX(PI)
 *
 * Math::Mat3x3f_C::RotateXYZ(PI, PI/2, PI/4)
 * Math::Mat3x3f_C::RotateZYX(PI, PI/2, PI/4)
 *
 */
TEST_F(Mat3x3fTest_C, TestMat3x3fRotate) {
    Math::Mat3x3f_C out = Math::Mat3x3f_C::Identity();

    out[0][0] = 1.0f;
    out[1][1] = -1.0f;
    out[2][2] = -1.0f;
    EXPECT_TRUE(out.AreSame(Math::Mat3x3f_C::Rotate(Math::Pi<float>(), Math::Vec3f_C(1.0f, 0.0f, 0.0f))));

    EXPECT_TRUE(out.AreSame(Math::Mat3x3f_C::RotateX(Math::Pi<float>())));

    out[0][0] = -1.0f;
    out[1][1] = 1.0f;
    out[2][2] = -1.0f;
    EXPECT_TRUE(out.AreSame(Math::Mat3x3f_C::RotateY(Math::Pi<float>())));

    out[0][0] = -1.0f;
    out[1][1] = -1.0f;
    out[2][2] = 1.0f;
    EXPECT_TRUE(out.AreSame(Math::Mat3x3f_C::RotateZ(Math::Pi<float>())));

    out[0][0] = 1.0f;
    out[1][1] = 1.0f;
    out[2][2] = 1.0f;
    EXPECT_TRUE(out.AreSame(Math::Mat3x3f_C::RotateXYZ(Math::Pi<float>())));
    EXPECT_TRUE(out.AreSame(Math::Mat3x3f_C::RotateZYX(Math::Pi<float>())));

    out = Math::Mat3x3f_C::Zero();
    out[1][0] = -static_cast<float>(SQRT_ONE_OVER_TWO);
    out[2][0] = -static_cast<float>(SQRT_ONE_OVER_TWO);
    out[1][1] = -static_cast<float>(SQRT_ONE_OVER_TWO);
    out[2][1] = static_cast<float>(SQRT_ONE_OVER_TWO);
    out[0][2] = -1.0f;

    EXPECT_TRUE(out.AreSame(Math::Mat3x3f_C::RotateXYZ(Math::QuarterPi<float>(), Math::HalfPi<float>(), Math::Pi<float>())));

    Math::Mat3x3f_C out1 = Math::Mat3x3f_C::RotateZYX(Math::QuarterPi<float>(), Math::HalfPi<float>(), Math::Pi<float>());
    EXPECT_FALSE(out.AreSame(out1));
}

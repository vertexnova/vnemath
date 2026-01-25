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

using namespace vne;

class Mat3x3fTest : public ::testing::Test {
    // Interface of test fixture base class
   protected:
    void SetUp() override {
        mat = vne::math::Mat3x3f(0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f);
        mat2 = vne::math::Mat3x3f(-14.0f, -20.0f, -26.0f, -32.0f, -8.0f, -10.0f, -12.0f, -14.0f, -2.0f);
        mat3 = vne::math::Mat3x3f(2.0f, 3.0f, 1.0f, 5.0f, 1.0f, 0.0f, 3.0f, 1.0f, 2.0f);
    }

    void TearDown() override {}

   protected:
    vne::math::Mat3x3f mat;
    vne::math::Mat3x3f mat2;
    vne::math::Mat3x3f mat3;
};

/**
 * Test GetColumn(uint32_t idx)
 *
 * mat.getColumn(0)
 *
 */
TEST_F(Mat3x3fTest, TestMat3x3fColumn) {
    vne::math::Mat3x3f out = vne::math::Mat3x3f(vne::math::Vec3f(1.0f), vne::math::Vec3f(2.0f), vne::math::Vec3f(3.0f));
    EXPECT_EQ(vne::math::Vec3f(1.0f), out.getColumn(0));
    EXPECT_EQ(vne::math::Vec3f(2.0f), out.getColumn(1));
    EXPECT_EQ(vne::math::Vec3f(3.0f), out.getColumn(2));
}

/**
 * Test GetRow(uint32_t idx)
 *
 * mat.getRow(0)
 *
 */
TEST_F(Mat3x3fTest, TestMat3x3fRow) {
    EXPECT_EQ(vne::math::Vec3f(0.0f, 3.0f, 6.0f), mat.getRow(0));
    EXPECT_EQ(vne::math::Vec3f(1.0f, 4.0f, 7.0f), mat.getRow(1));
    EXPECT_EQ(vne::math::Vec3f(2.0f, 5.0f, 8.0f), mat.getRow(2));
}

/**
 * Test XAxis(), YAxis() and ZAxis()
 *
 * mat.xAxis()
 * mat.yAxis()
 * mat.zAxis()
 *
 */
TEST_F(Mat3x3fTest, TestMat3x3fXYZAxes) {
    vne::math::Mat3x3f out = vne::math::Mat3x3f(vne::math::Vec3f(1.0f), vne::math::Vec3f(2.0f), vne::math::Vec3f(3.0f));
    EXPECT_EQ(vne::math::Vec3f(1.0f), out.xAxis());
    EXPECT_EQ(vne::math::Vec3f(2.0f), out.yAxis());
    EXPECT_EQ(vne::math::Vec3f(3.0f), out.zAxis());
}

/**
 * Test Determinant()
 *
 * mat.determinant()
 *
 */
TEST_F(Mat3x3fTest, TestMat3x3fDeterminant) {
    vne::math::Mat3x3f out = vne::math::Mat3x3f(vne::math::Vec3f(2.0f, 2.0f, 1.0f), vne::math::Vec3f(-3.0f, 0.0f, 4.0f), vne::math::Vec3f(1.0f, -1.0f, 5.0f));
    EXPECT_EQ(49.0f, out.determinant());

    out = vne::math::Mat3x3f(vne::math::Vec3f(1.0f, -3.0f, 2.0f), vne::math::Vec3f(3.0f, -1.0f, 3.0f), vne::math::Vec3f(2.0f, -3.0f, 1.0f));
    EXPECT_EQ(-15.0f, out.determinant());
}

/**
 * Test Trace()
 *
 * mat.trace()
 *
 */
TEST_F(Mat3x3fTest, TestMat3x3fTrace) {
    vne::math::Mat3x3f out = vne::math::Mat3x3f(vne::math::Vec3f(-5.0f, 1.0f, -3.0f), vne::math::Vec3f(0.0f, 2.0f, 4.0f), vne::math::Vec3f(-1.0f, -1.0f, 1.0f));
    EXPECT_EQ(-40.0f, out.determinant());
    EXPECT_EQ(-2.0f, out.trace());
}

/**
 * Test Transpose()
 *
 * mat.transpose()
 *
 */
TEST_F(Mat3x3fTest, TestMat3x3fTranspose) {
    vne::math::Mat3x3f out = vne::math::Mat3x3f(vne::math::Vec3f(3.0f, 4.0f, 3.0f), vne::math::Vec3f(2.0f, 0.0f, 0.0f), vne::math::Vec3f(0.0f, 1.0f, 2.0f));
    vne::math::Mat3x3f trans = out.transpose();

    EXPECT_EQ(out.getColumn(0), trans.getRow(0));
    EXPECT_EQ(out.getColumn(1), trans.getRow(1));
    EXPECT_EQ(out.getColumn(2), trans.getRow(2));
}

/**
 * Test Inverse()
 *
 * mat.inverse()
 *
 */
TEST_F(Mat3x3fTest, TestMat3x3fInverse) {
    vne::math::Mat3x3f out = vne::math::Mat3x3f(vne::math::Vec3f(3.0f, 2.0f, 0.0f), vne::math::Vec3f(0.0f, 0.0f, 1.0f), vne::math::Vec3f(2.0f, -2.0f, 1.0f));

    EXPECT_EQ(10.0f, out.determinant());
    vne::math::Mat3x3f inv = out.inverse();

    EXPECT_EQ(vne::math::Vec3f(0.2f, -0.2f, 0.2f), inv.getColumn(0));
    EXPECT_EQ(vne::math::Vec3f(0.2f, 0.3f, -0.3f), inv.getColumn(1));
    EXPECT_EQ(vne::math::Vec3f(0.0f, 1.0f, 0.0f), inv.getColumn(2));
}

/**
 * Test InverseTransposed()
 *
 * mat.inverseTransposed()
 *
 */
TEST_F(Mat3x3fTest, TestMat3x3fInverseTransposed) {
    vne::math::Mat3x3f transform = vne::math::Mat3x3f(vne::math::Vec3f(-1.0f, 3.0f, 1.0f), vne::math::Vec3f(-3.0f, 6.0f, 0.0f), vne::math::Vec3f(1.0f, 0.0f, 1.0f));

    vne::math::Mat3x3f inv_transpose = transform.inverseTransposed();

    vne::math::Mat3x3f transpose = transform.transpose();
    EXPECT_EQ(vne::math::Vec3f(-2.0f, -1.0f, 2.0f), inv_transpose.getColumn(0));
    EXPECT_EQ(vne::math::Vec3f(1.0f, 2.0f / 3.0f, -1.0f), inv_transpose.getColumn(1));
    EXPECT_EQ(vne::math::Vec3f(2.0f, 1.0f, -1.0f), inv_transpose.getColumn(2));
}

/**
 * Test Assignment Operator
 */
TEST_F(Mat3x3fTest, TestMat3x3fAssignment) {
    vne::math::Mat3x3f local_mat = mat3;
    EXPECT_EQ(local_mat, mat3);
}

/**
 * Test Addition Operator
 */
TEST_F(Mat3x3fTest, TestMat3x3fAddition) {
    vne::math::Mat3x3f result = mat + mat3;
    EXPECT_EQ(result, vne::math::Mat3x3f(2.0f, 4.0f, 3.0f, 8.0f, 5.0f, 5.0f, 9.0f, 8.0f, 10.0f));
}

/**
 * Test Addition Assignment Operator
 */
TEST_F(Mat3x3fTest, TestMat3x3fAdditionAssignment) {
    vne::math::Mat3x3f local_mat = mat;
    local_mat += mat3;
    EXPECT_EQ(local_mat, vne::math::Mat3x3f(2.0f, 4.0f, 3.0f, 8.0f, 5.0f, 5.0f, 9.0f, 8.0f, 10.0f));
}

/**
 * Test Subtraction Operator
 */
TEST_F(Mat3x3fTest, TestMat3x3fSubtraction) {
    vne::math::Mat3x3f result = mat - mat3;
    EXPECT_EQ(result, vne::math::Mat3x3f(-2.0f, -2.0f, 1.0f, -2.0f, 3.0f, 5.0f, 3.0f, 6.0f, 6.0f));
}

/**
 * Test Subtraction Assignment Operator
 */
TEST_F(Mat3x3fTest, TestMat3x3fSubtractionAssignment) {
    vne::math::Mat3x3f local_mat = mat;
    local_mat -= mat3;
    EXPECT_EQ(local_mat, vne::math::Mat3x3f(-2.0f, -2.0f, 1.0f, -2.0f, 3.0f, 5.0f, 3.0f, 6.0f, 6.0f));
}

/**
 * Test Multiplication Operator
 */
TEST_F(Mat3x3fTest, TestMat3x3fMultiplication) {
    vne::math::Mat3x3f result = mat * mat3;  // coulumn major
    EXPECT_EQ(result, vne::math::Mat3x3f(15.0f, 21.0f, 27.0f, 3.0f, 9.0f, 15.0f, 15.0f, 21.0f, 27.0f));
}

/**
 * Test Multiplication Assignment Operator
 */
TEST_F(Mat3x3fTest, TestMat3x3fMultiplicationAssignment) {
    vne::math::Mat3x3f local_mat = mat;
    local_mat *= mat3;
    EXPECT_EQ(local_mat, vne::math::Mat3x3f(15.0f, 21.0f, 27.0f, 3.0f, 9.0f, 15.0f, 15.0f, 21.0f, 27.0f));
}

/**
 * Test Scalar Multiplication Operator
 *
 * mat * 2.0f
 */
TEST_F(Mat3x3fTest, TestMat3x3fScalarMultiplication) {
    vne::math::Mat3x3f result = mat * 2.0f;
    EXPECT_EQ(result, vne::math::Mat3x3f(0.0f, 2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f));
}

/**
 * Test Scalar Multiplication Assignment Operator
 *
 * mat *= 2.0f
 */
TEST_F(Mat3x3fTest, TestMat3x3fScalarMultiplicationAssignment) {
    mat *= 2.0f;
    EXPECT_EQ(mat, vne::math::Mat3x3f(0.0f, 2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f));
}

/**
 * Test Scalar Division Operator
 *
 * mat / 2.0f
 */
TEST_F(Mat3x3fTest, TestMat3x3fScalarDivision) {
    vne::math::Mat3x3f result = mat / 2.0f;
    EXPECT_EQ(result, vne::math::Mat3x3f(0.0f, 0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f));
}

/**
 * Test Scalar Division Assignment Operator
 *
 * mat /= 2.0f
 */
TEST_F(Mat3x3fTest, TestMat3x3fScalarDivisionAssignment) {
    mat /= 2.0f;
    EXPECT_EQ(mat, vne::math::Mat3x3f(0.0f, 0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f));
}

/**
 * Test Mat3x3f stream out
 *
 * std::cout << mat << std::endl;
 */
TEST_F(Mat3x3fTest, TestMat3x3fStreamOut) {
    std::ostringstream stream;
    stream << mat;
    EXPECT_EQ(stream.str(), "[[0, 1, 2],\n [3, 4, 5],\n [6, 7, 8]]");
}

/**
 * Test Mat3x3f Identity
 *
 * vne::math::Math4x4f_C.identity()
 *
 */
TEST_F(Mat3x3fTest, TestMat3x3fIdentity) {
    EXPECT_EQ(vne::math::Mat3x3f(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f), vne::math::Mat3x3f::identity());
}

/**
 * Test Mat3x3f Zero
 *
 * vne::math::Mat3x3f::zero()
 *
 */
TEST_F(Mat3x3fTest, TestMat3x3fZero) {
    EXPECT_EQ(vne::math::Mat3x3f(0.0f), vne::math::Mat3x3f::zero());
}

/**
 * Test Mat3x3f Lerp
 *
 * vne::math::Mat3x3f::lerp(const vne::math::Mat3x3f&, const vne::math::Mat3x3f&, float)
 *
 */
TEST_F(Mat3x3fTest, TestMat3x3fLerp) {
    vne::math::Mat3x3f from = mat;
    vne::math::Mat3x3f to = mat3;
    EXPECT_EQ(vne::math::Mat3x3f(vne::math::Vec3f(1.0f, 2.0f, 1.5f), vne::math::Vec3f(4.0f, 2.5f, 2.5f), vne::math::Vec3f(4.5f, 4.0f, 5.0f)),
              vne::math::Mat3x3f::lerp(from, to, 0.5f));
}

/**
 * Test RotationMatrix()
 *
 * mat.rotationMatrix(const Vec3f&, const Vec3f&, const Vec3f&)
 *
 */
TEST_F(Mat3x3fTest, TestMat3x3fRotationMatrix) {
    vne::math::Mat3x3f out;

    EXPECT_EQ(vne::math::Mat3x3f(vne::math::Vec3f::xAxis(), vne::math::Vec3f::yAxis(), vne::math::Vec3f::zAxis()),
              out.rotationMatrix(vne::math::Vec3f::xAxis(), vne::math::Vec3f::yAxis(), vne::math::Vec3f::zAxis()));
}

/**
 * Test Mat3x3f Scale
 *
 * vne::math::Mat3x3f::scale(vne::math::Vec3f(1.0f, 2.0f, 3.0f))
 * vne::math::Mat3x3f::scale(1.0f, 2.0f, 3.0f)
 * vne::math::Mat3x3f::scale(1.0f)
 *
 */
TEST_F(Mat3x3fTest, TestMat3x3fScale) {
    vne::math::Mat3x3f out = vne::math::Mat3x3f::identity();

    out[0][0] = 1.0f;
    out[1][1] = 2.0f;
    out[2][2] = 3.0f;
    EXPECT_EQ(out, vne::math::Mat3x3f::scale(vne::math::Vec3f(1.0f, 2.0f, 3.0f)));

    out[0][0] = 4.0f;
    out[1][1] = 5.0f;
    out[2][2] = 6.0f;
    EXPECT_EQ(out, vne::math::Mat3x3f::scale(4.0f, 5.0f, 6.0f));

    out[0][0] = out[1][1] = out[2][2] = 10.0f;
    EXPECT_EQ(out, vne::math::Mat3x3f::scale(10.0f));
}

/**
 * Test Mat3x3f Rotate
 *
 * vne::math::Mat3x3f::rotate(PI, vne::math::Vec3f(1.0f, 1.0f, 1.0f))
 *
 * vne::math::Mat3x3f::rotateX(PI)
 * vne::math::Mat3x3f::rotateY(PI)
 * vne::math::Mat3x3f::rotateZ(PI)
 * vne::math::Mat3x3f::rotateXYZ(PI)
 * vne::math::Mat3x3f::rotateZYX(PI)
 *
 * vne::math::Mat3x3f::rotateXYZ(PI, PI/2, PI/4)
 * vne::math::Mat3x3f::rotateZYX(PI, PI/2, PI/4)
 *
 */
TEST_F(Mat3x3fTest, TestMat3x3fRotate) {
    vne::math::Mat3x3f out = vne::math::Mat3x3f::identity();

    out[0][0] = 1.0f;
    out[1][1] = -1.0f;
    out[2][2] = -1.0f;
    EXPECT_TRUE(out.areSame(vne::math::Mat3x3f::rotate(vne::math::pi<float>(), vne::math::Vec3f(1.0f, 0.0f, 0.0f))));

    EXPECT_TRUE(out.areSame(vne::math::Mat3x3f::rotateX(vne::math::pi<float>())));

    out[0][0] = -1.0f;
    out[1][1] = 1.0f;
    out[2][2] = -1.0f;
    EXPECT_TRUE(out.areSame(vne::math::Mat3x3f::rotateY(vne::math::pi<float>())));

    out[0][0] = -1.0f;
    out[1][1] = -1.0f;
    out[2][2] = 1.0f;
    EXPECT_TRUE(out.areSame(vne::math::Mat3x3f::rotateZ(vne::math::pi<float>())));

    out[0][0] = 1.0f;
    out[1][1] = 1.0f;
    out[2][2] = 1.0f;
    EXPECT_TRUE(out.areSame(vne::math::Mat3x3f::rotateXYZ(vne::math::pi<float>())));
    EXPECT_TRUE(out.areSame(vne::math::Mat3x3f::rotateZYX(vne::math::pi<float>())));

    out = vne::math::Mat3x3f::zero();
    out[1][0] = -static_cast<float>(SQRT_ONE_OVER_TWO);
    out[2][0] = -static_cast<float>(SQRT_ONE_OVER_TWO);
    out[1][1] = -static_cast<float>(SQRT_ONE_OVER_TWO);
    out[2][1] = static_cast<float>(SQRT_ONE_OVER_TWO);
    out[0][2] = -1.0f;

    EXPECT_TRUE(out.areSame(vne::math::Mat3x3f::rotateXYZ(vne::math::quarterPi<float>(), vne::math::halfPi<float>(), vne::math::pi<float>())));

    vne::math::Mat3x3f out1 = vne::math::Mat3x3f::rotateZYX(vne::math::quarterPi<float>(), vne::math::halfPi<float>(), vne::math::pi<float>());
    EXPECT_FALSE(out.areSame(out1));
}

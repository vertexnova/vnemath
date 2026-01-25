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
#include "vertexnova/math/mat4x4f.h"

using namespace VNE;

class Mat4x4fTest_C : public ::testing::Test {
    // Interface of test fixture base class
   protected:
    void SetUp() override {
        mat = Math::Mat4x4f_C(0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f);
        mat2 = Math::Mat4x4f_C(-14.0f, -20.0f, -26.0f, -32.0f, -8.0f, -10.0f, -12.0f, -14.0f, -2.0f, 0.0f, 2.0f, 4.0f, 4.0f, 10.0f, 16.0f, 22.0f);
        mat3 = Math::Mat4x4f_C(2.0f, 3.0f, 1.0f, 5.0f, 1.0f, 0.0f, 3.0f, 1.0f, 0.0f, 2.0f, -3.0f, 2.0f, 0.0f, 2.0f, 3.0f, 1.0f);
    }

    void TearDown() override {}

   protected:
    Math::Mat4x4f_C mat;
    Math::Mat4x4f_C mat2;
    Math::Mat4x4f_C mat3;
};

/**
 * Test GetColumn(uint32_t idx)
 *
 * mat.GetColumn(0)
 *
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fColumn) {
    Math::Mat4x4f_C out = Math::Mat4x4f_C(Math::Vec4f_C(1.0f), Math::Vec4f_C(2.0f), Math::Vec4f_C(3.0f), Math::Vec4f_C(4.0f));
    EXPECT_EQ(Math::Vec4f_C(1.0f), out.GetColumn(0));
    EXPECT_EQ(Math::Vec4f_C(2.0f), out.GetColumn(1));
    EXPECT_EQ(Math::Vec4f_C(3.0f), out.GetColumn(2));
    EXPECT_EQ(Math::Vec4f_C(4.0f), out.GetColumn(3));
#ifdef _DEBUG
    EXPECT_DEATH(out.GetColumn(4), ".*");
#endif  // _DEBUG
}

/**
 * Test GetRow(uint32_t idx)
 *
 * mat.GetRow(0)
 *
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fRow) {
    EXPECT_EQ(Math::Vec4f_C(0.0f, 4.0f, 8.0f, 12.0f), mat.GetRow(0));
    EXPECT_EQ(Math::Vec4f_C(1.0f, 5.0f, 9.0f, 13.0f), mat.GetRow(1));
    EXPECT_EQ(Math::Vec4f_C(2.0f, 6.0f, 10.0f, 14.0f), mat.GetRow(2));
    EXPECT_EQ(Math::Vec4f_C(3.0f, 7.0f, 11.0f, 15.0f), mat.GetRow(3));
#ifdef _DEBUG
    EXPECT_DEATH(mat.GetRow(4), ".*");
#endif  // _DEBUG
}

/**
 * Test XAxis(), YAxis(), ZAxis() and Translation()
 *
 * mat.XAxis()
 * mat.YAxis()
 * mat.ZAxis()
 * mat.Translation()
 *
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fXYZAxes) {
    Math::Mat4x4f_C out = Math::Mat4x4f_C(Math::Vec4f_C(1.0f), Math::Vec4f_C(2.0f), Math::Vec4f_C(3.0f), Math::Vec4f_C(4.0f));
    EXPECT_EQ(Math::Vec3f_C(1.0f), out.XAxis());
    EXPECT_EQ(Math::Vec3f_C(2.0f), out.YAxis());
    EXPECT_EQ(Math::Vec3f_C(3.0f), out.ZAxis());
    EXPECT_EQ(Math::Vec3f_C(4.0f), out.Translation());
}

/**
 * Test Determinant()
 *
 * mat.Determinant()
 *
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fDeterminant) {
    Math::Mat4x4f_C out = Math::Mat4x4f_C(Math::Vec4f_C(3.0f, 4.0f, 3.0f, 9.0f),
                                          Math::Vec4f_C(2.0f, 0.0f, 0.0f, 2.0f),
                                          Math::Vec4f_C(0.0f, 1.0f, 2.0f, 3.0f),
                                          Math::Vec4f_C(1.0f, 2.0f, 1.0f, 1.0f));
    EXPECT_EQ(24.0f, out.Determinant());

    out = Math::Mat4x4f_C(Math::Vec4f_C(4.0f, 0.0f, 0.0f, 0.0f),
                          Math::Vec4f_C(3.0f, 1.0f, -1.0f, 3.0f),
                          Math::Vec4f_C(2.0f, -3.0f, 3.0f, 1.0f),
                          Math::Vec4f_C(2.0f, 3.0f, 3.0f, 1.0f));
    EXPECT_EQ(-240.0f, out.Determinant());

    out = Math::Mat4x4f_C(Math::Vec4f_C(1.0f, 4.0f, 0.0f, 1.0f),
                          Math::Vec4f_C(2.0f, 7.0f, 0.0f, 2.0f),
                          Math::Vec4f_C(6.0f, 3.0f, 0.0f, 2.0f),
                          Math::Vec4f_C(6.0f, 2.0f, 0.0f, 9.0f));
    EXPECT_EQ(0.0f, out.Determinant());  // 3rd row is a zero vector

    out = Math::Mat4x4f_C(Math::Vec4f_C(2.0f, 6.0f, 0.0f, 1.0f),
                          Math::Vec4f_C(1.0f, 7.0f, 6.0f, 2.0f),
                          Math::Vec4f_C(2.0f, 6.0f, 0.0f, 1.0f),
                          Math::Vec4f_C(3.0f, 9.0f, 0.0f, 4.0f));
    EXPECT_EQ(0.0f, out.Determinant());  // 1st and 3rd columns are equal
}

/**
 * Test Transpose()
 *
 * mat.Transpose()
 *
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fTranspose) {
    Math::Mat4x4f_C out = Math::Mat4x4f_C(Math::Vec4f_C(3.0f, 4.0f, 3.0f, 9.0f),
                                          Math::Vec4f_C(2.0f, 0.0f, 0.0f, 2.0f),
                                          Math::Vec4f_C(0.0f, 1.0f, 2.0f, 3.0f),
                                          Math::Vec4f_C(1.0f, 2.0f, 1.0f, 1.0f));
    Math::Mat4x4f_C trans = out.Transpose();

    EXPECT_EQ(out.GetColumn(0), trans.GetRow(0));
    EXPECT_EQ(out.GetColumn(1), trans.GetRow(1));
    EXPECT_EQ(out.GetColumn(2), trans.GetRow(2));
    EXPECT_EQ(out.GetColumn(3), trans.GetRow(3));
}

/**
 * Test Inverse()
 *
 * mat.Inverse()
 *
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fInverse) {
    Math::Mat4x4f_C out = Math::Mat4x4f_C(Math::Vec4f_C(1.0f, 1.0f, 1.0f, -1.0f),
                                          Math::Vec4f_C(1.0f, 1.0f, -1.0f, 1.0f),
                                          Math::Vec4f_C(1.0f, -1.0f, 1.0f, 1.0f),
                                          Math::Vec4f_C(-1.0f, 1.0f, 1.0f, 1.0f));

    EXPECT_EQ(-16.0f, out.Determinant());
    Math::Mat4x4f_C inv = out.Inverse();

    EXPECT_EQ(out.GetColumn(0) / 4.0f, inv.GetColumn(0));
    EXPECT_EQ(out.GetColumn(1) / 4.0f, inv.GetColumn(1));
    EXPECT_EQ(out.GetColumn(2) / 4.0f, inv.GetColumn(2));
    EXPECT_EQ(out.GetColumn(3) / 4.0f, inv.GetColumn(3));
}

/**
 * Test InverseTransposed()
 *
 * mat.InverseTransposed()
 *
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fInverseTransposed) {
    Math::Mat4x4f_C transform = Math::Mat4x4f_C(Math::Vec4f_C(1.0f, 1.0f, 1.0f, -1.0f),
                                                Math::Vec4f_C(1.0f, 1.0f, -1.0f, 1.0f),
                                                Math::Vec4f_C(1.0f, -1.0f, 1.0f, 1.0f),
                                                Math::Vec4f_C(-1.0f, 1.0f, 1.0f, 1.0f));

    Math::Mat4x4f_C inv_transpose = transform.InverseTransposed();

    Math::Mat4x4f_C transpose = transform.Transpose();
    EXPECT_EQ(transpose.GetColumn(0) / 4.0f, inv_transpose.GetColumn(0));
    EXPECT_EQ(transpose.GetColumn(1) / 4.0f, inv_transpose.GetColumn(1));
    EXPECT_EQ(transpose.GetColumn(2) / 4.0f, inv_transpose.GetColumn(2));
    EXPECT_EQ(transpose.GetColumn(3) / 4.0f, inv_transpose.GetColumn(3));
}

/**
 * Test Mat4x4f_C Handness
 *
 * mat.Handness()
 *
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fHandness) {
    Math::Mat4x4f_C result = Math::Mat4x4f_C(Math::Vec4f_C(1.0f), Math::Vec4f_C(2.0f), Math::Vec4f_C(3.0f), Math::Vec4f_C(4.0f));
    EXPECT_EQ(Math::Handness_TP::LEFT, result.Handedness());

    result = Math::Mat4x4f_C(Math::Vec4f_C(0.9f, -0.0f, 0.3f, 0.0f),
                             Math::Vec4f_C(0.2f, 0.9f, -0.4f, 0.0f),
                             Math::Vec4f_C(-0.3f, 0.5f, 0.8f, 0.0f),
                             Math::Vec4f_C(0.0f, 0.0f, 0.0f, 1.0f));
    EXPECT_EQ(Math::Handness_TP::RIGHT, result.Handedness());
}

/**
 * Test TransformPoint()
 *
 * mat.TransformPoint(cont Math::Vec3f_C& )
 *
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fTransformPoint) {
    Math::Mat4x4f_C out = Math::Mat4x4f_C(Math::Vec4f_C(1.0f, 0.0f, 0.0f, 0.0f),
                                          Math::Vec4f_C(0.0f, 1.0f, 0.0f, 0.0f),
                                          Math::Vec4f_C(0.0f, 0.0f, 1.0f, 0.0f),
                                          Math::Vec4f_C(2.0f, 2.0f, 2.0f, 1.0f));

    Math::Vec3f_C point = Math::Vec3f_C(2.0f, 3.0f, 1.0f);

    EXPECT_EQ(Math::Vec3f_C(4.0f, 5.0f, 3.0f), out.TransformPoint(point));
}

/**
 * Test TransformVector()
 *
 * mat.TransformVector(cont Math::Vec3f_C& )
 *
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fTransformVector) {
    Math::Mat4x4f_C out = Math::Mat4x4f_C(Math::Vec4f_C(1.0f, 0.0f, 0.0f, 0.0f),
                                          Math::Vec4f_C(0.0f, 1.0f, 0.0f, 0.0f),
                                          Math::Vec4f_C(0.0f, 0.0f, 1.0f, 0.0f),
                                          Math::Vec4f_C(2.0f, 2.0f, 2.0f, 1.0f));

    Math::Vec3f_C vector = Math::Vec3f_C(2.0f, 3.0f, 1.0f);

    EXPECT_EQ(Math::Vec3f_C(2.0f, 3.0f, 1.0f), out.TransformVector(vector));

    out[0] = Math::Vec4f_C(2.0f, 0.0f, 0.0f, 0.0f);
    EXPECT_EQ(Math::Vec3f_C(4.0f, 3.0f, 1.0f), out.TransformVector(vector));
}

/**
 * Test TransformNormal()
 *
 * mat.TransformNormal(cont Math::Vec3f_C& )
 *
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fTransformNormal) {
    // Identity matrix
    Math::Mat4x4f_C out = Math::Mat4x4f_C(Math::Vec4f_C(1.0f, 0.0f, 0.0f, 0.0f),
                                          Math::Vec4f_C(0.0f, 1.0f, 0.0f, 0.0f),
                                          Math::Vec4f_C(0.0f, 0.0f, 1.0f, 0.0f),
                                          Math::Vec4f_C(2.0f, 3.0f, 4.0f, 1.0f));

    Math::Vec3f_C normal = Math::Vec3f_C(0.0f, 0.0f, 1.0f);

    EXPECT_EQ(normal, out.TransformNormal(normal));

    out[0] = Math::Vec4f_C(2.0f, 0.0f, 0.0f, 0.0f);
    EXPECT_EQ(normal, out.TransformNormal(normal));

    // Only Rotational matrix
    out = Math::Mat4x4f_C(Math::Vec4f_C(1.0f, 0.0f, 0.0f, 0.0f),
                          Math::Vec4f_C(0.0f, 0.866f, 0.5f, 0.0f),
                          Math::Vec4f_C(0.0f, -0.5f, 0.866f, 0.0f),
                          Math::Vec4f_C(0.0f, 0.0f, 0.0f, 1.0f));
    Math::Vec3f_C normal_out = Math::Vec3f_C(0.0f, -0.5f, 0.866f);
    EXPECT_TRUE(normal_out.AreSame(out.TransformNormal(normal), 1E-3f));

    // Scaling only
    out = Math::Mat4x4f_C(Math::Vec4f_C(2.0f, 0.0f, 0.0f, 0.0f),
                          Math::Vec4f_C(0.0f, 4.0f, 0.0f, 0.0f),
                          Math::Vec4f_C(0.0f, 0.0f, 5.0f, 0.0f),
                          Math::Vec4f_C(0.0f, 0.0f, 0.0f, 1.0f));
    normal = Math::Vec3f_C(0.0f, 0.6f, 0.8f);
    normal_out = Math::Vec3f_C(0, 0.683941f, 0.729537f);
    EXPECT_TRUE(normal_out.AreSame(out.TransformNormal(normal), 1E-5f));
}

/**
 * Test Mat4x4f_C stream out
 *
 * std::cout << mat << std::endl;
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fStreamOut) {
    std::ostringstream stream;
    stream << mat;
    EXPECT_EQ(stream.str(), "[[0, 1, 2, 3],\n [4, 5, 6, 7],\n [8, 9, 10, 11],\n [12, 13, 14, 15]]");
}

/**
 * Test Mat4x4f_C Identity
 *
 * Math::Math4x4f_C::Identity()
 *
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fIdentity) {
    Math::Mat4x4f_C mat4 = Math::Mat4x4f_C();
    EXPECT_EQ(Math::Mat4x4f_C(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f),
              Math::Mat4x4f_C::Identity());
}

/**
 * Test Mat4x4f_C Zero
 *
 * Math::Mat4x4f_C::Zero()
 *
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fZero) {
    EXPECT_EQ(Math::Mat4x4f_C(0.0f), Math::Mat4x4f_C::Zero());
}

/**
 * Test Mat4x4f_C Lerp
 *
 * Math::Mat4x4f_C::Lerp(const Math::Mat4x4f_C&, const Math::Mat4x4f_C&, float)
 *
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fLerp) {
    Math::Mat4x4f_C from = mat;
    Math::Mat4x4f_C to = mat3;
    EXPECT_EQ(Math::Mat4x4f_C(Math::Vec4f_C(1.0f, 2.0f, 1.5f, 4.0f),
                              Math::Vec4f_C(2.5f, 2.5f, 4.5f, 4.0f),
                              Math::Vec4f_C(4.0f, 5.5f, 3.5f, 6.5f),
                              Math::Vec4f_C(6.0f, 7.5f, 8.5f, 8.0f)),
              Math::Mat4x4f_C::Lerp(from, to, 0.5f));
}

/**
 * Test Transform()
 *
 * mat.Transform(const Vec3f_C&, const Vec3f_C&, const Vec3f_C&, const Vec3f_C&,
 * const Vec3f_C&) mat.Transform(const Vec3f_C&, const Vec3f_C&, const Vec3f_C&,
 * const Vec3f_C&) mat.Transform(const Vec3f_C&, const Vec3f_C&, const Vec3f_C&)
 * mat.Transform(const Vec3f_C&, const Vec3f_C&, const Vec3f_C&)
 *
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fTransform) {
    Math::Mat4x4f_C out;

    EXPECT_EQ(Math::Mat4x4f_C(Math::Vec4f_C::XAxis(), Math::Vec4f_C::YAxis(), Math::Vec4f_C::ZAxis(), Math::Vec4f_C(1.0f, 2.0f, 3.0f, 1.0f)),
              out.Transform(Math::Vec3f_C::XAxis(), Math::Vec3f_C::YAxis(), Math::Vec3f_C::ZAxis(), Math::Vec3f_C(1.0f, 2.0f, 3.0f)));

    EXPECT_EQ(Math::Mat4x4f_C(Math::Vec4f_C::XAxis(), Math::Vec4f_C::YAxis(), Math::Vec4f_C::ZAxis(), Math::Vec4f_C(0.0f, 0.0f, 0.0f, 1.0f)),
              out.Transform(Math::Vec3f_C::XAxis(), Math::Vec3f_C::YAxis(), Math::Vec3f_C::ZAxis()));

    EXPECT_EQ(Math::Mat4x4f_C(Math::Vec4f_C::ZAxis(), Math::Vec4f_C::XAxis(), Math::Vec4f_C::YAxis(), Math::Vec4f_C(0.0f, 0.0f, 0.0f, 1.0f)),
              out.Transform(Math::Vec3f_C::Forward(), Math::Vec3f_C::Up()));

    EXPECT_EQ(Math::Mat4x4f_C(Math::Vec4f_C::XAxis(), Math::Vec4f_C::YAxis(), Math::Vec4f_C::ZAxis(), Math::Vec4f_C(1.0f, 2.0f, 3.0f, 1.0f)),
              out.Transform(Math::Vec3f_C(1.0f, 2.0f, 3.0f)));
}

/**
 * Test Mat4x4f_C Translate
 *
 * Math::Mat4x4f_C::Translate(Math::Vec3f_C(1.0f, 2.0f, 3.0f))
 * Math::Mat4x4f_C::Translate(1.0f, 2.0f, 3.0f)
 * Math::Mat4x4f_C::Translate(1.0f)
 *
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fTranslate) {
    Math::Mat4x4f_C out = Math::Mat4x4f_C::Identity();

    out[3][0] = 1.0f;
    out[3][1] = 2.0f;
    out[3][2] = 3.0f;
    EXPECT_EQ(out, Math::Mat4x4f_C::Translate(Math::Vec3f_C(1.0f, 2.0f, 3.0f)));

    out[3][0] = 4.0f;
    out[3][1] = 5.0f;
    out[3][2] = 6.0f;
    EXPECT_EQ(out, Math::Mat4x4f_C::Translate(4.0f, 5.0f, 6.0f));

    out[3][0] = out[3][1] = out[3][2] = 10.0f;
    EXPECT_EQ(out, Math::Mat4x4f_C::Translate(10.0f));
}

/**
 * Test Mat4x4f_C Scale
 *
 * Math::Mat4x4f_C::Scale(Math::Vec3f_C(1.0f, 2.0f, 3.0f))
 * Math::Mat4x4f_C::Scale(1.0f, 2.0f, 3.0f)
 * Math::Mat4x4f_C::Scale(1.0f)
 *
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fScale) {
    Math::Mat4x4f_C out = Math::Mat4x4f_C::Identity();

    out[0][0] = 1.0f;
    out[1][1] = 2.0f;
    out[2][2] = 3.0f;
    EXPECT_EQ(out, Math::Mat4x4f_C::Scale(Math::Vec3f_C(1.0f, 2.0f, 3.0f)));

    out[0][0] = 4.0f;
    out[1][1] = 5.0f;
    out[2][2] = 6.0f;
    EXPECT_EQ(out, Math::Mat4x4f_C::Scale(4.0f, 5.0f, 6.0f));

    out[0][0] = out[1][1] = out[2][2] = 10.0f;
    EXPECT_EQ(out, Math::Mat4x4f_C::Scale(10.0f));
}

/**
 * Test Mat4x4f_C Rotate
 *
 * Math::Mat4x4f_C::Rotate(PI, Math::Vec3f_C(1.0f, 1.0f, 1.0f))
 *
 * Math::Mat4x4f_C::RotateX(PI)
 * Math::Mat4x4f_C::RotateY(PI)
 * Math::Mat4x4f_C::RotateZ(PI)
 * Math::Mat4x4f_C::RotateXYZ(PI)
 * Math::Mat4x4f_C::RotateZYX(PI)
 *
 * Math::Mat4x4f_C::RotateXYZ(PI, PI/2, PI/4)
 * Math::Mat4x4f_C::RotateZYX(PI, PI/2, PI/4)
 *
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fRotate) {
    Math::Mat4x4f_C out = Math::Mat4x4f_C::Identity();

    out[0][0] = 1.0f;
    out[1][1] = -1.0f;
    out[2][2] = -1.0f;
    EXPECT_TRUE(out.AreSame(Math::Mat4x4f_C::Rotate(Math::Pi<float>(), Math::Vec3f_C(1.0f, 0.0f, 0.0f))));

    EXPECT_TRUE(out.AreSame(Math::Mat4x4f_C::RotateX(Math::Pi<float>())));

    out[0][0] = -1.0f;
    out[1][1] = 1.0f;
    out[2][2] = -1.0f;
    EXPECT_TRUE(out.AreSame(Math::Mat4x4f_C::RotateY(Math::Pi<float>())));

    out[0][0] = -1.0f;
    out[1][1] = -1.0f;
    out[2][2] = 1.0f;
    EXPECT_TRUE(out.AreSame(Math::Mat4x4f_C::RotateZ(Math::Pi<float>())));

    out[0][0] = 1.0f;
    out[1][1] = 1.0f;
    out[2][2] = 1.0f;
    EXPECT_TRUE(out.AreSame(Math::Mat4x4f_C::RotateXYZ(Math::Pi<float>())));
    EXPECT_TRUE(out.AreSame(Math::Mat4x4f_C::RotateZYX(Math::Pi<float>())));

    out = Math::Mat4x4f_C::Zero();
    out[1][0] = -static_cast<float>(SQRT_ONE_OVER_TWO);
    out[2][0] = -static_cast<float>(SQRT_ONE_OVER_TWO);
    out[1][1] = -static_cast<float>(SQRT_ONE_OVER_TWO);
    out[2][1] = static_cast<float>(SQRT_ONE_OVER_TWO);
    out[0][2] = -1.0f;
    out[3][3] = 1.0f;
    EXPECT_TRUE(out.AreSame(Math::Mat4x4f_C::RotateXYZ(Math::QuarterPi<float>(), Math::HalfPi<float>(), Math::Pi<float>())));

    Math::Mat4x4f_C out1 = Math::Mat4x4f_C::RotateZYX(Math::QuarterPi<float>(), Math::HalfPi<float>(), Math::Pi<float>());
    EXPECT_FALSE(out.AreSame(out1));
}

/**
 * Test Mat4x4f_C LookAt
 *
 * Math::Mat4x4f_C::LookAt(Vec3f_C, Vec3f_C, Vec3f_C)
 *
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fLookAt) {
    Math::Vec3f_C eye{0.0f, 0.0f, 3.0f};
    Math::Vec3f_C center{0.0f, 0.0f, 2.0f};
    Math::Vec3f_C up{0.0f, 1.0f, 0.0f};

    // LookAt Matrix computation
    Math::Vec3f_C forward = Math::Vec3f_C::Normalized(eye - center);
    Math::Vec3f_C right = Math::Vec3f_C::Normalized(Math::Vec3f_C::Cross(up, forward));
    Math::Vec3f_C new_up = Math::Vec3f_C::Cross(forward, right);

    Math::Mat4x4f_C out = Math::Mat4x4f_C::LookAt(eye, center, up);

    EXPECT_EQ(right, out.XAxis());
    EXPECT_EQ(new_up, out.YAxis());
    EXPECT_EQ(forward, out.ZAxis());
    EXPECT_EQ(-eye, out.Translation());
}

/**
 * Test Mat4x4f_C Frustum
 *
 * Math::Mat4x4f_C::Frustum(left, right, bottom, top, z_near, z_far)
 *
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fFrustum) {
    float left = -0.5f;
    float right = 0.5f;
    float bottom = -0.5f;
    float top = 0.5f;
    float z_near = 1.0f;
    float z_far = 10.0f;

    Math::Mat4x4f_C out = Math::Mat4x4f_C::Frustum(left, right, bottom, top, z_near, z_far);

    // GetColumn 0
    EXPECT_EQ(2.0f * z_near / (right - left), out[0][0]);
    EXPECT_EQ(0.0f, out[1][0]);
    EXPECT_EQ((right + left) / (right - left), out[2][0]);
    EXPECT_EQ(0.0f, out[3][0]);

    // GetColumn 1
    EXPECT_EQ(0.0f, out[0][1]);
    EXPECT_EQ(2.0f * z_near / (top - bottom), out[1][1]);
    EXPECT_EQ((top + bottom) / (top - bottom), out[2][1]);
    EXPECT_EQ(0.0f, out[3][1]);

    // GetColumn 2
    EXPECT_EQ(0.0f, out[0][2]);
    EXPECT_EQ(0.0f, out[1][2]);
    EXPECT_EQ(-(z_far + z_near) / (z_far - z_near), out[2][2]);
    EXPECT_EQ(-2.0f * z_far * z_near / (z_far - z_near), out[3][2]);

    // GetColumn 3
    EXPECT_EQ(0.0f, out[0][3]);
    EXPECT_EQ(0.0f, out[1][3]);
    EXPECT_EQ(-1.0f, out[2][3]);
    EXPECT_EQ(0.0f, out[3][3]);
}

/**
 * Test Mat4x4f_C Perspective
 *
 * Math::Mat4x4f_C::Perspective(fovy, aspect_ratio, z_near, z_far)
 *
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fPerspective) {
    float fovy = Math::DegToRad(45.0f);
    float aspect_ratio = 16.0f / 9.0f;
    float z_near = 1.0f;
    float z_far = 10.0f;

    Math::Mat4x4f_C out = Math::Mat4x4f_C::Perspective(fovy, aspect_ratio, z_near, z_far);

    float tangent = Math::Tan(fovy / 2.0f);  // tangent of half fovy
    float height = z_near * tangent;         // half height of near plane
    float width = height * aspect_ratio;     // half width of near plane

    float left = -width;
    float right = width;

    float bottom = -height;
    float top = height;

    // GetColumn 0
    EXPECT_EQ(2.0f * z_near / (right - left), out[0][0]);
    EXPECT_EQ(0.0f, out[1][0]);
    EXPECT_EQ((right + left) / (right - left), out[2][0]);
    EXPECT_EQ(0.0f, out[3][0]);

    // GetColumn 1
    EXPECT_EQ(0.0f, out[0][1]);
    EXPECT_EQ(2.0f * z_near / (top - bottom), out[1][1]);
    EXPECT_EQ((top + bottom) / (top - bottom), out[2][1]);
    EXPECT_EQ(0.0f, out[3][1]);

    // GetColumn 2
    EXPECT_EQ(0.0f, out[0][2]);
    EXPECT_EQ(0.0f, out[1][2]);
    EXPECT_EQ(-(z_far + z_near) / (z_far - z_near), out[2][2]);
    EXPECT_EQ(-2.0f * z_far * z_near / (z_far - z_near), out[3][2]);

    // GetColumn 3
    EXPECT_EQ(0.0f, out[0][3]);
    EXPECT_EQ(0.0f, out[1][3]);
    EXPECT_EQ(-1.0f, out[2][3]);
    EXPECT_EQ(0.0f, out[3][3]);
}

/**
 * Test Mat4x4f_C Ortho
 *
 * Math::Mat4x4f_C::Ortho(left, right, bottom, top, z_near, z_far)
 *
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fOrtho) {
    float left = -0.5f;
    float right = 0.5f;
    float bottom = -0.5f;
    float top = 0.5f;
    float z_near = 1.0f;
    float z_far = 10.0f;

    Math::Mat4x4f_C out = Math::Mat4x4f_C::Ortho(left, right, bottom, top, z_near, z_far);

    // GetColumn 0
    EXPECT_EQ(2.0f / (right - left), out[0][0]);
    EXPECT_EQ(0.0f, out[1][0]);
    EXPECT_EQ(0.0f, out[2][0]);
    EXPECT_EQ(-(right + left) / (right - left), out[3][0]);

    // GetColumn 1
    EXPECT_EQ(0.0f, out[0][1]);
    EXPECT_EQ(2.0f / (top - bottom), out[1][1]);
    EXPECT_EQ(0.0f, out[2][1]);
    EXPECT_EQ(-(top + bottom) / (top - bottom), out[3][1]);

    // GetColumn 2
    EXPECT_EQ(0.0f, out[0][2]);
    EXPECT_EQ(0.0f, out[1][2]);
    EXPECT_EQ(-2.0f / (z_far - z_near), out[2][2]);
    EXPECT_EQ(-(z_far + z_near) / (z_far - z_near), out[3][2]);

    // GetColumn 3
    EXPECT_EQ(0.0f, out[0][3]);
    EXPECT_EQ(0.0f, out[1][3]);
    EXPECT_EQ(0.0f, out[2][3]);
    EXPECT_EQ(1.0f, out[3][3]);
}

/**
 * Test Addition Operator
 *
 * mat + mat3
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fAddition) {
    Math::Mat4x4f_C result = mat + mat3;
    EXPECT_EQ(result, Math::Mat4x4f_C(2.0f, 4.0f, 3.0f, 8.0f, 5.0f, 5.0f, 9.0f, 8.0f, 8.0f, 11.0f, 7.0f, 13.0f, 12.0f, 15.0f, 17.0f, 16.0f));
}

/**
 * Test Addition Assignment Operator
 *
 * mat += mat3
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fAdditionAssignment) {
    mat += mat3;
    EXPECT_EQ(mat, Math::Mat4x4f_C(2.0f, 4.0f, 3.0f, 8.0f, 5.0f, 5.0f, 9.0f, 8.0f, 8.0f, 11.0f, 7.0f, 13.0f, 12.0f, 15.0f, 17.0f, 16.0f));
}

/**
 * Test Subtraction Operator
 *
 * mat - mat3
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fSubtraction) {
    Math::Mat4x4f_C result = mat - mat3;
    EXPECT_EQ(result, Math::Mat4x4f_C(-2.0f, -2.0f, 1.0f, -2.0f, 3.0f, 5.0f, 3.0f, 6.0f, 8.0f, 7.0f, 13.0f, 9.0f, 12.0f, 11.0f, 11.0f, 14.0f));
}

/**
 * Test Subtraction Assignment Operator
 *
 * mat -= mat3
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fSubtractionAssignment) {
    mat -= mat3;
    EXPECT_EQ(mat, Math::Mat4x4f_C(-2.0f, -2.0f, 1.0f, -2.0f, 3.0f, 5.0f, 3.0f, 6.0f, 8.0f, 7.0f, 13.0f, 9.0f, 12.0f, 11.0f, 11.0f, 14.0f));
}

/**
 * Test Multiplication Operator
 *
 * mat * mat3
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fMultiplication) {
    Math::Mat4x4f_C result = mat * mat3;
    EXPECT_EQ(result,
              Math::Mat4x4f_C(80.0f, 91.0f, 102.0f, 113.0f, 36.0f, 41.0f, 46.0f, 51.0f, 8.0f, 9.0f, 10.0f, 11.0f, 44.0f, 50.0f, 56.0f, 62.0f));
}

/**
 * Test Multiplication Assignment Operator
 *
 * mat *= mat3
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fMultiplicationAssignment) {
    mat *= mat3;
    EXPECT_EQ(mat, Math::Mat4x4f_C(80.0f, 91.0f, 102.0f, 113.0f, 36.0f, 41.0f, 46.0f, 51.0f, 8.0f, 9.0f, 10.0f, 11.0f, 44.0f, 50.0f, 56.0f, 62.0f));
}

/**
 * Test Assignment Operator
 *
 * mat = mat3
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fAssignment) {
    mat = mat3;
    EXPECT_EQ(mat, mat3);
}
/**
 * Test Multiplication by Scalar Operator
 *
 * mat * scalar
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fMultiplicationByScalar) {
    Math::Mat4x4f_C local_mat = Math::Mat4x4f_C(0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f);
    float scalar = 2.0f;
    Math::Mat4x4f_C result = local_mat * scalar;
    EXPECT_EQ(result, Math::Mat4x4f_C(0.0f, 2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f, 18.0f, 20.0f, 22.0f, 24.0f, 26.0f, 28.0f, 30.0f));
}

/**
 * Test Multiplication Assignment by Scalar Operator
 *
 * mat *= scalar
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fMultiplicationAssignmentByScalar) {
    Math::Mat4x4f_C local_mat = Math::Mat4x4f_C(0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f);
    float scalar = 2.0f;
    local_mat *= scalar;
    EXPECT_EQ(local_mat, Math::Mat4x4f_C(0.0f, 2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f, 18.0f, 20.0f, 22.0f, 24.0f, 26.0f, 28.0f, 30.0f));
}

/**
 * Test Division by Scalar Operator
 *
 * mat / scalar
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fDivisionByScalar) {
    Math::Mat4x4f_C local_mat = Math::Mat4x4f_C(0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f);
    float scalar = 2.0f;
    Math::Mat4x4f_C result = local_mat / scalar;
    EXPECT_EQ(result, Math::Mat4x4f_C(0.0f, 0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f, 4.5f, 5.0f, 5.5f, 6.0f, 6.5f, 7.0f, 7.5f));
}

/**
 * Test Division Assignment by Scalar Operator
 *
 * mat /= scalar
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fDivisionAssignmentByScalar) {
    Math::Mat4x4f_C local_mat = Math::Mat4x4f_C(0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f);
    float scalar = 2.0f;
    local_mat /= scalar;
    EXPECT_EQ(local_mat, Math::Mat4x4f_C(0.0f, 0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f, 4.5f, 5.0f, 5.5f, 6.0f, 6.5f, 7.0f, 7.5f));
}

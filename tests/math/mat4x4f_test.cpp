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
        mat = vne::math::Mat4x4f(0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f);
        mat2 = vne::math::Mat4x4f(-14.0f, -20.0f, -26.0f, -32.0f, -8.0f, -10.0f, -12.0f, -14.0f, -2.0f, 0.0f, 2.0f, 4.0f, 4.0f, 10.0f, 16.0f, 22.0f);
        mat3 = vne::math::Mat4x4f(2.0f, 3.0f, 1.0f, 5.0f, 1.0f, 0.0f, 3.0f, 1.0f, 0.0f, 2.0f, -3.0f, 2.0f, 0.0f, 2.0f, 3.0f, 1.0f);
    }

    void TearDown() override {}

   protected:
    vne::math::Mat4x4f mat;
    vne::math::Mat4x4f mat2;
    vne::math::Mat4x4f mat3;
};

/**
 * Test GetColumn(uint32_t idx)
 *
 * mat.getColumn(0)
 *
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fColumn) {
    vne::math::Mat4x4f out = vne::math::Mat4x4f(vne::math::Vec4f(1.0f), vne::math::Vec4f(2.0f), vne::math::Vec4f(3.0f), vne::math::Vec4f(4.0f));
    EXPECT_EQ(vne::math::Vec4f(1.0f), out.getColumn(0));
    EXPECT_EQ(vne::math::Vec4f(2.0f), out.getColumn(1));
    EXPECT_EQ(vne::math::Vec4f(3.0f), out.getColumn(2));
    EXPECT_EQ(vne::math::Vec4f(4.0f), out.getColumn(3));
#ifdef _DEBUG
    EXPECT_DEATH(out.getColumn(4), ".*");
#endif  // _DEBUG
}

/**
 * Test GetRow(uint32_t idx)
 *
 * mat.getRow(0)
 *
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fRow) {
    EXPECT_EQ(vne::math::Vec4f(0.0f, 4.0f, 8.0f, 12.0f), mat.getRow(0));
    EXPECT_EQ(vne::math::Vec4f(1.0f, 5.0f, 9.0f, 13.0f), mat.getRow(1));
    EXPECT_EQ(vne::math::Vec4f(2.0f, 6.0f, 10.0f, 14.0f), mat.getRow(2));
    EXPECT_EQ(vne::math::Vec4f(3.0f, 7.0f, 11.0f, 15.0f), mat.getRow(3));
#ifdef _DEBUG
    EXPECT_DEATH(mat.getRow(4), ".*");
#endif  // _DEBUG
}

/**
 * Test XAxis(), YAxis(), ZAxis() and Translation()
 *
 * mat.xAxis()
 * mat.yAxis()
 * mat.zAxis()
 * mat.translation()
 *
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fXYZAxes) {
    vne::math::Mat4x4f out = vne::math::Mat4x4f(vne::math::Vec4f(1.0f), vne::math::Vec4f(2.0f), vne::math::Vec4f(3.0f), vne::math::Vec4f(4.0f));
    EXPECT_EQ(vne::math::Vec3f(1.0f), out.xAxis());
    EXPECT_EQ(vne::math::Vec3f(2.0f), out.yAxis());
    EXPECT_EQ(vne::math::Vec3f(3.0f), out.zAxis());
    EXPECT_EQ(vne::math::Vec3f(4.0f), out.translation());
}

/**
 * Test Determinant()
 *
 * mat.determinant()
 *
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fDeterminant) {
    vne::math::Mat4x4f out = vne::math::Mat4x4f(vne::math::Vec4f(3.0f, 4.0f, 3.0f, 9.0f),
                                          vne::math::Vec4f(2.0f, 0.0f, 0.0f, 2.0f),
                                          vne::math::Vec4f(0.0f, 1.0f, 2.0f, 3.0f),
                                          vne::math::Vec4f(1.0f, 2.0f, 1.0f, 1.0f));
    EXPECT_EQ(24.0f, out.determinant());

    out = vne::math::Mat4x4f(vne::math::Vec4f(4.0f, 0.0f, 0.0f, 0.0f),
                          vne::math::Vec4f(3.0f, 1.0f, -1.0f, 3.0f),
                          vne::math::Vec4f(2.0f, -3.0f, 3.0f, 1.0f),
                          vne::math::Vec4f(2.0f, 3.0f, 3.0f, 1.0f));
    EXPECT_EQ(-240.0f, out.determinant());

    out = vne::math::Mat4x4f(vne::math::Vec4f(1.0f, 4.0f, 0.0f, 1.0f),
                          vne::math::Vec4f(2.0f, 7.0f, 0.0f, 2.0f),
                          vne::math::Vec4f(6.0f, 3.0f, 0.0f, 2.0f),
                          vne::math::Vec4f(6.0f, 2.0f, 0.0f, 9.0f));
    EXPECT_EQ(0.0f, out.determinant());  // 3rd row is a zero vector

    out = vne::math::Mat4x4f(vne::math::Vec4f(2.0f, 6.0f, 0.0f, 1.0f),
                          vne::math::Vec4f(1.0f, 7.0f, 6.0f, 2.0f),
                          vne::math::Vec4f(2.0f, 6.0f, 0.0f, 1.0f),
                          vne::math::Vec4f(3.0f, 9.0f, 0.0f, 4.0f));
    EXPECT_EQ(0.0f, out.determinant());  // 1st and 3rd columns are equal
}

/**
 * Test Transpose()
 *
 * mat.transpose()
 *
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fTranspose) {
    vne::math::Mat4x4f out = vne::math::Mat4x4f(vne::math::Vec4f(3.0f, 4.0f, 3.0f, 9.0f),
                                          vne::math::Vec4f(2.0f, 0.0f, 0.0f, 2.0f),
                                          vne::math::Vec4f(0.0f, 1.0f, 2.0f, 3.0f),
                                          vne::math::Vec4f(1.0f, 2.0f, 1.0f, 1.0f));
    vne::math::Mat4x4f trans = out.transpose();

    EXPECT_EQ(out.getColumn(0), trans.getRow(0));
    EXPECT_EQ(out.getColumn(1), trans.getRow(1));
    EXPECT_EQ(out.getColumn(2), trans.getRow(2));
    EXPECT_EQ(out.getColumn(3), trans.getRow(3));
}

/**
 * Test Inverse()
 *
 * mat.inverse()
 *
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fInverse) {
    vne::math::Mat4x4f out = vne::math::Mat4x4f(vne::math::Vec4f(1.0f, 1.0f, 1.0f, -1.0f),
                                          vne::math::Vec4f(1.0f, 1.0f, -1.0f, 1.0f),
                                          vne::math::Vec4f(1.0f, -1.0f, 1.0f, 1.0f),
                                          vne::math::Vec4f(-1.0f, 1.0f, 1.0f, 1.0f));

    EXPECT_EQ(-16.0f, out.determinant());
    vne::math::Mat4x4f inv = out.inverse();

    EXPECT_EQ(out.getColumn(0) / 4.0f, inv.getColumn(0));
    EXPECT_EQ(out.getColumn(1) / 4.0f, inv.getColumn(1));
    EXPECT_EQ(out.getColumn(2) / 4.0f, inv.getColumn(2));
    EXPECT_EQ(out.getColumn(3) / 4.0f, inv.getColumn(3));
}

/**
 * Test InverseTransposed()
 *
 * mat.inverseTransposed()
 *
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fInverseTransposed) {
    vne::math::Mat4x4f transform = vne::math::Mat4x4f(vne::math::Vec4f(1.0f, 1.0f, 1.0f, -1.0f),
                                                vne::math::Vec4f(1.0f, 1.0f, -1.0f, 1.0f),
                                                vne::math::Vec4f(1.0f, -1.0f, 1.0f, 1.0f),
                                                vne::math::Vec4f(-1.0f, 1.0f, 1.0f, 1.0f));

    vne::math::Mat4x4f inv_transpose = transform.inverseTransposed();

    vne::math::Mat4x4f transpose = transform.transpose();
    EXPECT_EQ(transpose.getColumn(0) / 4.0f, inv_transpose.getColumn(0));
    EXPECT_EQ(transpose.getColumn(1) / 4.0f, inv_transpose.getColumn(1));
    EXPECT_EQ(transpose.getColumn(2) / 4.0f, inv_transpose.getColumn(2));
    EXPECT_EQ(transpose.getColumn(3) / 4.0f, inv_transpose.getColumn(3));
}

/**
 * Test Mat4x4f Handness
 *
 * mat.Handness()
 *
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fHandness) {
    vne::math::Mat4x4f result = vne::math::Mat4x4f(vne::math::Vec4f(1.0f), vne::math::Vec4f(2.0f), vne::math::Vec4f(3.0f), vne::math::Vec4f(4.0f));
    EXPECT_EQ(vne::math::Handedness::eLeft, result.handedness());

    result = vne::math::Mat4x4f(vne::math::Vec4f(0.9f, -0.0f, 0.3f, 0.0f),
                             vne::math::Vec4f(0.2f, 0.9f, -0.4f, 0.0f),
                             vne::math::Vec4f(-0.3f, 0.5f, 0.8f, 0.0f),
                             vne::math::Vec4f(0.0f, 0.0f, 0.0f, 1.0f));
    EXPECT_EQ(vne::math::Handedness::eRight, result.handedness());
}

/**
 * Test TransformPoint()
 *
 * mat.transformPoint(cont vne::math::Vec3f& )
 *
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fTransformPoint) {
    vne::math::Mat4x4f out = vne::math::Mat4x4f(vne::math::Vec4f(1.0f, 0.0f, 0.0f, 0.0f),
                                          vne::math::Vec4f(0.0f, 1.0f, 0.0f, 0.0f),
                                          vne::math::Vec4f(0.0f, 0.0f, 1.0f, 0.0f),
                                          vne::math::Vec4f(2.0f, 2.0f, 2.0f, 1.0f));

    vne::math::Vec3f point = vne::math::Vec3f(2.0f, 3.0f, 1.0f);

    EXPECT_EQ(vne::math::Vec3f(4.0f, 5.0f, 3.0f), out.transformPoint(point));
}

/**
 * Test TransformVector()
 *
 * mat.transformVector(cont vne::math::Vec3f& )
 *
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fTransformVector) {
    vne::math::Mat4x4f out = vne::math::Mat4x4f(vne::math::Vec4f(1.0f, 0.0f, 0.0f, 0.0f),
                                          vne::math::Vec4f(0.0f, 1.0f, 0.0f, 0.0f),
                                          vne::math::Vec4f(0.0f, 0.0f, 1.0f, 0.0f),
                                          vne::math::Vec4f(2.0f, 2.0f, 2.0f, 1.0f));

    vne::math::Vec3f vector = vne::math::Vec3f(2.0f, 3.0f, 1.0f);

    EXPECT_EQ(vne::math::Vec3f(2.0f, 3.0f, 1.0f), out.transformVector(vector));

    out[0] = vne::math::Vec4f(2.0f, 0.0f, 0.0f, 0.0f);
    EXPECT_EQ(vne::math::Vec3f(4.0f, 3.0f, 1.0f), out.transformVector(vector));
}

/**
 * Test TransformNormal()
 *
 * mat.transformNormal(cont vne::math::Vec3f& )
 *
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fTransformNormal) {
    // Identity matrix
    vne::math::Mat4x4f out = vne::math::Mat4x4f(vne::math::Vec4f(1.0f, 0.0f, 0.0f, 0.0f),
                                          vne::math::Vec4f(0.0f, 1.0f, 0.0f, 0.0f),
                                          vne::math::Vec4f(0.0f, 0.0f, 1.0f, 0.0f),
                                          vne::math::Vec4f(2.0f, 3.0f, 4.0f, 1.0f));

    vne::math::Vec3f normal = vne::math::Vec3f(0.0f, 0.0f, 1.0f);

    EXPECT_EQ(normal, out.transformNormal(normal));

    out[0] = vne::math::Vec4f(2.0f, 0.0f, 0.0f, 0.0f);
    EXPECT_EQ(normal, out.transformNormal(normal));

    // Only Rotational matrix
    out = vne::math::Mat4x4f(vne::math::Vec4f(1.0f, 0.0f, 0.0f, 0.0f),
                          vne::math::Vec4f(0.0f, 0.866f, 0.5f, 0.0f),
                          vne::math::Vec4f(0.0f, -0.5f, 0.866f, 0.0f),
                          vne::math::Vec4f(0.0f, 0.0f, 0.0f, 1.0f));
    vne::math::Vec3f normal_out = vne::math::Vec3f(0.0f, -0.5f, 0.866f);
    EXPECT_TRUE(normal_out.areSame(out.transformNormal(normal), 1E-3f));

    // Scaling only
    out = vne::math::Mat4x4f(vne::math::Vec4f(2.0f, 0.0f, 0.0f, 0.0f),
                          vne::math::Vec4f(0.0f, 4.0f, 0.0f, 0.0f),
                          vne::math::Vec4f(0.0f, 0.0f, 5.0f, 0.0f),
                          vne::math::Vec4f(0.0f, 0.0f, 0.0f, 1.0f));
    normal = vne::math::Vec3f(0.0f, 0.6f, 0.8f);
    normal_out = vne::math::Vec3f(0, 0.683941f, 0.729537f);
    EXPECT_TRUE(normal_out.areSame(out.transformNormal(normal), 1E-5f));
}

/**
 * Test Mat4x4f stream out
 *
 * std::cout << mat << std::endl;
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fStreamOut) {
    std::ostringstream stream;
    stream << mat;
    EXPECT_EQ(stream.str(), "[[0, 1, 2, 3],\n [4, 5, 6, 7],\n [8, 9, 10, 11],\n [12, 13, 14, 15]]");
}

/**
 * Test Mat4x4f Identity
 *
 * vne::math::Math4x4f_C.identity()
 *
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fIdentity) {
    vne::math::Mat4x4f mat4 = vne::math::Mat4x4f();
    EXPECT_EQ(vne::math::Mat4x4f(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f),
              vne::math::Mat4x4f::identity());
}

/**
 * Test Mat4x4f Zero
 *
 * vne::math::Mat4x4f::zero()
 *
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fZero) {
    EXPECT_EQ(vne::math::Mat4x4f(0.0f), vne::math::Mat4x4f::zero());
}

/**
 * Test Mat4x4f Lerp
 *
 * vne::math::Mat4x4f::lerp(const vne::math::Mat4x4f&, const vne::math::Mat4x4f&, float)
 *
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fLerp) {
    vne::math::Mat4x4f from = mat;
    vne::math::Mat4x4f to = mat3;
    EXPECT_EQ(vne::math::Mat4x4f(vne::math::Vec4f(1.0f, 2.0f, 1.5f, 4.0f),
                              vne::math::Vec4f(2.5f, 2.5f, 4.5f, 4.0f),
                              vne::math::Vec4f(4.0f, 5.5f, 3.5f, 6.5f),
                              vne::math::Vec4f(6.0f, 7.5f, 8.5f, 8.0f)),
              vne::math::Mat4x4f::lerp(from, to, 0.5f));
}

/**
 * Test Transform()
 *
 * mat.transform(const Vec3f&, const Vec3f&, const Vec3f&, const Vec3f&,
 * const Vec3f&) mat.transform(const Vec3f&, const Vec3f&, const Vec3f&,
 * const Vec3f&) mat.transform(const Vec3f&, const Vec3f&, const Vec3f&)
 * mat.transform(const Vec3f&, const Vec3f&, const Vec3f&)
 *
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fTransform) {
    vne::math::Mat4x4f out;

    EXPECT_EQ(vne::math::Mat4x4f(vne::math::Vec4f::xAxis(), vne::math::Vec4f::yAxis(), vne::math::Vec4f::zAxis(), vne::math::Vec4f(1.0f, 2.0f, 3.0f, 1.0f)),
              out.transform(vne::math::Vec3f::xAxis(), vne::math::Vec3f::yAxis(), vne::math::Vec3f::zAxis(), vne::math::Vec3f(1.0f, 2.0f, 3.0f)));

    EXPECT_EQ(vne::math::Mat4x4f(vne::math::Vec4f::xAxis(), vne::math::Vec4f::yAxis(), vne::math::Vec4f::zAxis(), vne::math::Vec4f(0.0f, 0.0f, 0.0f, 1.0f)),
              out.transform(vne::math::Vec3f::xAxis(), vne::math::Vec3f::yAxis(), vne::math::Vec3f::zAxis()));

    EXPECT_EQ(vne::math::Mat4x4f(vne::math::Vec4f::zAxis(), vne::math::Vec4f::xAxis(), vne::math::Vec4f::yAxis(), vne::math::Vec4f(0.0f, 0.0f, 0.0f, 1.0f)),
              out.transform(vne::math::Vec3f::forward(), vne::math::Vec3f::up()));

    EXPECT_EQ(vne::math::Mat4x4f(vne::math::Vec4f::xAxis(), vne::math::Vec4f::yAxis(), vne::math::Vec4f::zAxis(), vne::math::Vec4f(1.0f, 2.0f, 3.0f, 1.0f)),
              out.transform(vne::math::Vec3f(1.0f, 2.0f, 3.0f)));
}

/**
 * Test Mat4x4f Translate
 *
 * vne::math::Mat4x4f::translate(vne::math::Vec3f(1.0f, 2.0f, 3.0f))
 * vne::math::Mat4x4f::translate(1.0f, 2.0f, 3.0f)
 * vne::math::Mat4x4f::translate(1.0f)
 *
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fTranslate) {
    vne::math::Mat4x4f out = vne::math::Mat4x4f::identity();

    out[3][0] = 1.0f;
    out[3][1] = 2.0f;
    out[3][2] = 3.0f;
    EXPECT_EQ(out, vne::math::Mat4x4f::translate(vne::math::Vec3f(1.0f, 2.0f, 3.0f)));

    out[3][0] = 4.0f;
    out[3][1] = 5.0f;
    out[3][2] = 6.0f;
    EXPECT_EQ(out, vne::math::Mat4x4f::translate(4.0f, 5.0f, 6.0f));

    out[3][0] = out[3][1] = out[3][2] = 10.0f;
    EXPECT_EQ(out, vne::math::Mat4x4f::translate(10.0f));
}

/**
 * Test Mat4x4f Scale
 *
 * vne::math::Mat4x4f::scale(vne::math::Vec3f(1.0f, 2.0f, 3.0f))
 * vne::math::Mat4x4f::scale(1.0f, 2.0f, 3.0f)
 * vne::math::Mat4x4f::scale(1.0f)
 *
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fScale) {
    vne::math::Mat4x4f out = vne::math::Mat4x4f::identity();

    out[0][0] = 1.0f;
    out[1][1] = 2.0f;
    out[2][2] = 3.0f;
    EXPECT_EQ(out, vne::math::Mat4x4f::scale(vne::math::Vec3f(1.0f, 2.0f, 3.0f)));

    out[0][0] = 4.0f;
    out[1][1] = 5.0f;
    out[2][2] = 6.0f;
    EXPECT_EQ(out, vne::math::Mat4x4f::scale(4.0f, 5.0f, 6.0f));

    out[0][0] = out[1][1] = out[2][2] = 10.0f;
    EXPECT_EQ(out, vne::math::Mat4x4f::scale(10.0f));
}

/**
 * Test Mat4x4f Rotate
 *
 * vne::math::Mat4x4f::rotate(PI, vne::math::Vec3f(1.0f, 1.0f, 1.0f))
 *
 * vne::math::Mat4x4f::rotateX(PI)
 * vne::math::Mat4x4f::rotateY(PI)
 * vne::math::Mat4x4f::rotateZ(PI)
 * vne::math::Mat4x4f::rotateXYZ(PI)
 * vne::math::Mat4x4f::rotateZYX(PI)
 *
 * vne::math::Mat4x4f::rotateXYZ(PI, PI/2, PI/4)
 * vne::math::Mat4x4f::rotateZYX(PI, PI/2, PI/4)
 *
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fRotate) {
    vne::math::Mat4x4f out = vne::math::Mat4x4f::identity();

    out[0][0] = 1.0f;
    out[1][1] = -1.0f;
    out[2][2] = -1.0f;
    EXPECT_TRUE(out.areSame(vne::math::Mat4x4f::rotate(vne::math::pi<float>(), vne::math::Vec3f(1.0f, 0.0f, 0.0f))));

    EXPECT_TRUE(out.areSame(vne::math::Mat4x4f::rotateX(vne::math::pi<float>())));

    out[0][0] = -1.0f;
    out[1][1] = 1.0f;
    out[2][2] = -1.0f;
    EXPECT_TRUE(out.areSame(vne::math::Mat4x4f::rotateY(vne::math::pi<float>())));

    out[0][0] = -1.0f;
    out[1][1] = -1.0f;
    out[2][2] = 1.0f;
    EXPECT_TRUE(out.areSame(vne::math::Mat4x4f::rotateZ(vne::math::pi<float>())));

    out[0][0] = 1.0f;
    out[1][1] = 1.0f;
    out[2][2] = 1.0f;
    EXPECT_TRUE(out.areSame(vne::math::Mat4x4f::rotateXYZ(vne::math::pi<float>())));
    EXPECT_TRUE(out.areSame(vne::math::Mat4x4f::rotateZYX(vne::math::pi<float>())));

    out = vne::math::Mat4x4f::zero();
    out[1][0] = -static_cast<float>(SQRT_ONE_OVER_TWO);
    out[2][0] = -static_cast<float>(SQRT_ONE_OVER_TWO);
    out[1][1] = -static_cast<float>(SQRT_ONE_OVER_TWO);
    out[2][1] = static_cast<float>(SQRT_ONE_OVER_TWO);
    out[0][2] = -1.0f;
    out[3][3] = 1.0f;
    EXPECT_TRUE(out.areSame(vne::math::Mat4x4f::rotateXYZ(vne::math::quarterPi<float>(), vne::math::halfPi<float>(), vne::math::pi<float>())));

    vne::math::Mat4x4f out1 = vne::math::Mat4x4f::rotateZYX(vne::math::quarterPi<float>(), vne::math::halfPi<float>(), vne::math::pi<float>());
    EXPECT_FALSE(out.areSame(out1));
}

/**
 * Test Mat4x4f LookAt
 *
 * vne::math::Mat4x4f::lookAt(Vec3f, Vec3f, Vec3f)
 *
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fLookAt) {
    vne::math::Vec3f eye{0.0f, 0.0f, 3.0f};
    vne::math::Vec3f center{0.0f, 0.0f, 2.0f};
    vne::math::Vec3f up{0.0f, 1.0f, 0.0f};

    // LookAt Matrix computation
    vne::math::Vec3f forward = vne::math::Vec3f::normalized(eye - center);
    vne::math::Vec3f right = vne::math::Vec3f::normalized(vne::math::Vec3f::cross(up, forward));
    vne::math::Vec3f new_up = vne::math::Vec3f::cross(forward, right);

    vne::math::Mat4x4f out = vne::math::Mat4x4f::lookAt(eye, center, up);

    EXPECT_EQ(right, out.xAxis());
    EXPECT_EQ(new_up, out.yAxis());
    EXPECT_EQ(forward, out.zAxis());
    EXPECT_EQ(-eye, out.translation());
}

/**
 * Test Mat4x4f Frustum
 *
 * vne::math::Mat4x4f::frustum(left, right, bottom, top, z_near, z_far)
 *
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fFrustum) {
    float left = -0.5f;
    float right = 0.5f;
    float bottom = -0.5f;
    float top = 0.5f;
    float z_near = 1.0f;
    float z_far = 10.0f;

    vne::math::Mat4x4f out = vne::math::Mat4x4f::frustum(left, right, bottom, top, z_near, z_far);

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
 * Test Mat4x4f Perspective
 *
 * vne::math::Mat4x4f::perspective(fovy, aspect_ratio, z_near, z_far)
 *
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fPerspective) {
    float fovy = vne::math::degToRad(45.0f);
    float aspect_ratio = 16.0f / 9.0f;
    float z_near = 1.0f;
    float z_far = 10.0f;

    vne::math::Mat4x4f out = vne::math::Mat4x4f::perspective(fovy, aspect_ratio, z_near, z_far);

    float tangent = vne::math::tan(fovy / 2.0f);  // tangent of half fovy
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
 * Test Mat4x4f Ortho
 *
 * vne::math::Mat4x4f::ortho(left, right, bottom, top, z_near, z_far)
 *
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fOrtho) {
    float left = -0.5f;
    float right = 0.5f;
    float bottom = -0.5f;
    float top = 0.5f;
    float z_near = 1.0f;
    float z_far = 10.0f;

    vne::math::Mat4x4f out = vne::math::Mat4x4f::ortho(left, right, bottom, top, z_near, z_far);

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
    vne::math::Mat4x4f result = mat + mat3;
    EXPECT_EQ(result, vne::math::Mat4x4f(2.0f, 4.0f, 3.0f, 8.0f, 5.0f, 5.0f, 9.0f, 8.0f, 8.0f, 11.0f, 7.0f, 13.0f, 12.0f, 15.0f, 17.0f, 16.0f));
}

/**
 * Test Addition Assignment Operator
 *
 * mat += mat3
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fAdditionAssignment) {
    mat += mat3;
    EXPECT_EQ(mat, vne::math::Mat4x4f(2.0f, 4.0f, 3.0f, 8.0f, 5.0f, 5.0f, 9.0f, 8.0f, 8.0f, 11.0f, 7.0f, 13.0f, 12.0f, 15.0f, 17.0f, 16.0f));
}

/**
 * Test Subtraction Operator
 *
 * mat - mat3
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fSubtraction) {
    vne::math::Mat4x4f result = mat - mat3;
    EXPECT_EQ(result, vne::math::Mat4x4f(-2.0f, -2.0f, 1.0f, -2.0f, 3.0f, 5.0f, 3.0f, 6.0f, 8.0f, 7.0f, 13.0f, 9.0f, 12.0f, 11.0f, 11.0f, 14.0f));
}

/**
 * Test Subtraction Assignment Operator
 *
 * mat -= mat3
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fSubtractionAssignment) {
    mat -= mat3;
    EXPECT_EQ(mat, vne::math::Mat4x4f(-2.0f, -2.0f, 1.0f, -2.0f, 3.0f, 5.0f, 3.0f, 6.0f, 8.0f, 7.0f, 13.0f, 9.0f, 12.0f, 11.0f, 11.0f, 14.0f));
}

/**
 * Test Multiplication Operator
 *
 * mat * mat3
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fMultiplication) {
    vne::math::Mat4x4f result = mat * mat3;
    EXPECT_EQ(result,
              vne::math::Mat4x4f(80.0f, 91.0f, 102.0f, 113.0f, 36.0f, 41.0f, 46.0f, 51.0f, 8.0f, 9.0f, 10.0f, 11.0f, 44.0f, 50.0f, 56.0f, 62.0f));
}

/**
 * Test Multiplication Assignment Operator
 *
 * mat *= mat3
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fMultiplicationAssignment) {
    mat *= mat3;
    EXPECT_EQ(mat, vne::math::Mat4x4f(80.0f, 91.0f, 102.0f, 113.0f, 36.0f, 41.0f, 46.0f, 51.0f, 8.0f, 9.0f, 10.0f, 11.0f, 44.0f, 50.0f, 56.0f, 62.0f));
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
    vne::math::Mat4x4f local_mat = vne::math::Mat4x4f(0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f);
    float scalar = 2.0f;
    vne::math::Mat4x4f result = local_mat * scalar;
    EXPECT_EQ(result, vne::math::Mat4x4f(0.0f, 2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f, 18.0f, 20.0f, 22.0f, 24.0f, 26.0f, 28.0f, 30.0f));
}

/**
 * Test Multiplication Assignment by Scalar Operator
 *
 * mat *= scalar
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fMultiplicationAssignmentByScalar) {
    vne::math::Mat4x4f local_mat = vne::math::Mat4x4f(0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f);
    float scalar = 2.0f;
    local_mat *= scalar;
    EXPECT_EQ(local_mat, vne::math::Mat4x4f(0.0f, 2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f, 18.0f, 20.0f, 22.0f, 24.0f, 26.0f, 28.0f, 30.0f));
}

/**
 * Test Division by Scalar Operator
 *
 * mat / scalar
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fDivisionByScalar) {
    vne::math::Mat4x4f local_mat = vne::math::Mat4x4f(0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f);
    float scalar = 2.0f;
    vne::math::Mat4x4f result = local_mat / scalar;
    EXPECT_EQ(result, vne::math::Mat4x4f(0.0f, 0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f, 4.5f, 5.0f, 5.5f, 6.0f, 6.5f, 7.0f, 7.5f));
}

/**
 * Test Division Assignment by Scalar Operator
 *
 * mat /= scalar
 */
TEST_F(Mat4x4fTest_C, TestMat4x4fDivisionAssignmentByScalar) {
    vne::math::Mat4x4f local_mat = vne::math::Mat4x4f(0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f);
    float scalar = 2.0f;
    local_mat /= scalar;
    EXPECT_EQ(local_mat, vne::math::Mat4x4f(0.0f, 0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f, 4.5f, 5.0f, 5.5f, 6.0f, 6.5f, 7.0f, 7.5f));
}

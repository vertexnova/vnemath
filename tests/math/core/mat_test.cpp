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

#include "vertexnova/math/core/mat.h"

namespace vne::math {

// ============================================================================
// Mat4 Basic Tests
// ============================================================================

class Mat4Test : public ::testing::Test {
   protected:
    Mat4f identity_ = Mat4f::identity();
};

TEST_F(Mat4Test, DefaultConstructor) {
    Mat4f m;
    // Should be identity
    EXPECT_FLOAT_EQ(m[0][0], 1.0f);
    EXPECT_FLOAT_EQ(m[1][1], 1.0f);
    EXPECT_FLOAT_EQ(m[2][2], 1.0f);
    EXPECT_FLOAT_EQ(m[3][3], 1.0f);
    EXPECT_FLOAT_EQ(m[0][1], 0.0f);
}

TEST_F(Mat4Test, ScalarConstructor) {
    Mat4f m(2.0f);
    EXPECT_FLOAT_EQ(m[0][0], 2.0f);
    EXPECT_FLOAT_EQ(m[1][1], 2.0f);
    EXPECT_FLOAT_EQ(m[0][1], 0.0f);
}

TEST_F(Mat4Test, Identity) {
    EXPECT_TRUE(identity_.approxEquals(Mat4f::identity()));
}

TEST_F(Mat4Test, Zero) {
    Mat4f z = Mat4f::zero();
    for (size_t c = 0; c < 4; ++c) {
        for (size_t r = 0; r < 4; ++r) {
            EXPECT_FLOAT_EQ(z[c][r], 0.0f);
        }
    }
}

TEST_F(Mat4Test, MatrixMultiplication) {
    Mat4f m = identity_ * identity_;
    EXPECT_TRUE(m.approxEquals(identity_));
}

TEST_F(Mat4Test, VectorMultiplication) {
    Vec4f v(1.0f, 2.0f, 3.0f, 1.0f);
    Vec4f result = identity_ * v;
    EXPECT_FLOAT_EQ(result.x(), 1.0f);
    EXPECT_FLOAT_EQ(result.y(), 2.0f);
    EXPECT_FLOAT_EQ(result.z(), 3.0f);
    EXPECT_FLOAT_EQ(result.w(), 1.0f);
}

TEST_F(Mat4Test, Transpose) {
    Mat4f m(Vec4f(1, 2, 3, 4), Vec4f(5, 6, 7, 8), Vec4f(9, 10, 11, 12), Vec4f(13, 14, 15, 16));

    Mat4f t = m.transpose();
    EXPECT_FLOAT_EQ(t[0][1], m[1][0]);
    EXPECT_FLOAT_EQ(t[1][0], m[0][1]);
}

TEST_F(Mat4Test, Determinant) {
    EXPECT_FLOAT_EQ(identity_.determinant(), 1.0f);
    EXPECT_FLOAT_EQ(Mat4f::scale(2.0f).determinant(), 8.0f);  // 2^3
}

TEST_F(Mat4Test, Inverse) {
    Mat4f t = Mat4f::translate(1.0f, 2.0f, 3.0f);
    Mat4f inv = t.inverse();
    Mat4f result = t * inv;
    EXPECT_TRUE(result.approxEquals(identity_, 1e-5f));
}

// ============================================================================
// Transform Tests
// ============================================================================

TEST_F(Mat4Test, Translate) {
    Mat4f t = Mat4f::translate(1.0f, 2.0f, 3.0f);
    Vec3f pos = t.translation();
    EXPECT_FLOAT_EQ(pos.x(), 1.0f);
    EXPECT_FLOAT_EQ(pos.y(), 2.0f);
    EXPECT_FLOAT_EQ(pos.z(), 3.0f);
}

TEST_F(Mat4Test, Scale) {
    Mat4f s = Mat4f::scale(2.0f, 3.0f, 4.0f);
    Vec4f v(1.0f, 1.0f, 1.0f, 1.0f);
    Vec4f result = s * v;
    EXPECT_FLOAT_EQ(result.x(), 2.0f);
    EXPECT_FLOAT_EQ(result.y(), 3.0f);
    EXPECT_FLOAT_EQ(result.z(), 4.0f);
}

TEST_F(Mat4Test, RotateX) {
    Mat4f r = Mat4f::rotateX(kHalfPiT<float>);
    Vec4f v(0.0f, 1.0f, 0.0f, 0.0f);
    Vec4f result = r * v;
    EXPECT_NEAR(result.x(), 0.0f, 1e-5f);
    EXPECT_NEAR(result.y(), 0.0f, 1e-5f);
    EXPECT_NEAR(result.z(), 1.0f, 1e-5f);
}

TEST_F(Mat4Test, RotateY) {
    Mat4f r = Mat4f::rotateY(kHalfPiT<float>);
    Vec4f v(1.0f, 0.0f, 0.0f, 0.0f);
    Vec4f result = r * v;
    EXPECT_NEAR(result.x(), 0.0f, 1e-5f);
    EXPECT_NEAR(result.y(), 0.0f, 1e-5f);
    EXPECT_NEAR(result.z(), -1.0f, 1e-5f);
}

TEST_F(Mat4Test, TransformPoint) {
    Mat4f t = Mat4f::translate(5.0f, 0.0f, 0.0f);
    Vec3f p(0.0f, 0.0f, 0.0f);
    Vec3f result = t.transformPoint(p);
    EXPECT_FLOAT_EQ(result.x(), 5.0f);
}

TEST_F(Mat4Test, TransformVector) {
    Mat4f t = Mat4f::translate(5.0f, 0.0f, 0.0f);
    Vec3f v(1.0f, 0.0f, 0.0f);
    Vec3f result = t.transformVector(v);
    // Translation should not affect direction vectors
    EXPECT_FLOAT_EQ(result.x(), 1.0f);
}

// ============================================================================
// Graphics API Projection Tests
// ============================================================================

TEST(Mat4ProjectionTest, PerspectiveVulkan) {
    Mat4f proj = Mat4f::perspective(degToRad(45.0f), 1.0f, 0.1f, 100.0f, GraphicsApi::eVulkan);

    // Vulkan: depth [0,1], Y-flipped
    EXPECT_LT(proj[1][1], 0.0f);  // Y should be flipped
}

TEST(Mat4ProjectionTest, PerspectiveOpenGL) {
    Mat4f proj = Mat4f::perspective(degToRad(45.0f), 1.0f, 0.1f, 100.0f, GraphicsApi::eOpenGL);

    // OpenGL: depth [-1,1], Y not flipped
    EXPECT_GT(proj[1][1], 0.0f);  // Y should not be flipped
}

TEST(Mat4ProjectionTest, PerspectiveMetal) {
    Mat4f proj = Mat4f::perspective(degToRad(45.0f), 1.0f, 0.1f, 100.0f, GraphicsApi::eMetal);

    // Metal: depth [0,1], Y-flipped, left-handed
    EXPECT_LT(proj[1][1], 0.0f);  // Y should be flipped
}

TEST(Mat4ProjectionTest, OrthoVulkan) {
    Mat4f proj = Mat4f::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f, GraphicsApi::eVulkan);
    EXPECT_LT(proj[1][1], 0.0f);  // Y should be flipped
}

TEST(Mat4ProjectionTest, OrthoOpenGL) {
    Mat4f proj = Mat4f::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f, GraphicsApi::eOpenGL);
    EXPECT_GT(proj[1][1], 0.0f);  // Y should not be flipped
}

// ============================================================================
// View Matrix Tests
// ============================================================================

TEST(Mat4ViewTest, LookAtRH) {
    Vec3f eye(0.0f, 0.0f, 10.0f);
    Vec3f center(0.0f, 0.0f, 0.0f);
    Vec3f up(0.0f, 1.0f, 0.0f);

    Mat4f view = Mat4f::lookAtRH(eye, center, up);

    // Origin should be transformed to (0, 0, -10) in view space
    Vec3f transformed = view.transformPoint(Vec3f::zero());
    EXPECT_NEAR(transformed.x(), 0.0f, 1e-5f);
    EXPECT_NEAR(transformed.y(), 0.0f, 1e-5f);
    EXPECT_NEAR(transformed.z(), -10.0f, 1e-5f);
}

TEST(Mat4ViewTest, LookAtForGraphicsApi) {
    Vec3f eye(0.0f, 0.0f, 10.0f);
    Vec3f center(0.0f, 0.0f, 0.0f);
    Vec3f up(0.0f, 1.0f, 0.0f);

    Mat4f viewVulkan = Mat4f::lookAt(eye, center, up, GraphicsApi::eVulkan);
    Mat4f viewMetal = Mat4f::lookAt(eye, center, up, GraphicsApi::eMetal);

    // Vulkan is right-handed, Metal is left-handed
    // They should produce different results
    EXPECT_FALSE(viewVulkan.approxEquals(viewMetal));
}

// ============================================================================
// Double Precision Tests
// ============================================================================

TEST(Mat4DoubleTest, BasicOperations) {
    Mat4d m1 = Mat4d::translate(1.0, 2.0, 3.0);
    Mat4d m2 = Mat4d::scale(2.0);

    Mat4d result = m1 * m2;

    EXPECT_DOUBLE_EQ(result[3][0], 1.0);
    EXPECT_DOUBLE_EQ(result[3][1], 2.0);
    EXPECT_DOUBLE_EQ(result[3][2], 3.0);
}

// ============================================================================
// GLM Interop Tests
// ============================================================================

TEST(Mat4GlmTest, ConvertToGlm) {
    Mat4f m = Mat4f::translate(1.0f, 2.0f, 3.0f);
    glm::mat4 gm = static_cast<glm::mat4>(m);

    EXPECT_FLOAT_EQ(gm[3][0], 1.0f);
    EXPECT_FLOAT_EQ(gm[3][1], 2.0f);
    EXPECT_FLOAT_EQ(gm[3][2], 3.0f);
}

TEST(Mat4GlmTest, ConvertFromGlm) {
    glm::mat4 gm = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 2.0f, 3.0f));
    Mat4f m = gm;

    EXPECT_FLOAT_EQ(m[3][0], 1.0f);
    EXPECT_FLOAT_EQ(m[3][1], 2.0f);
    EXPECT_FLOAT_EQ(m[3][2], 3.0f);
}

}  // namespace vne::math

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
#include "vertexnova/math/vec4f.h"
// #include "vertexnova/math/geometry/plane.h"

using namespace vne;

class Vec4fTest : public ::testing::Test {
    // Interface of test fixture base class
   protected:
    void SetUp() override {
        neg_xyzw_vec__ = vne::math::Vec4f(-2.0f, 14.5f, -6.75f, 8.76f);
        zero_vec_ = vne::math::Vec4f();
        one_vec_ = vne::math::Vec4f(1.0f);
        xyzw_vec_ = vne::math::Vec4f(2.0f, 2.5f, 4.0f, 1.0f);
        x_axis_ = vne::math::Vec4f(1.0f, 0.0f, 0.0f, 0.0f);
        y_axis_ = vne::math::Vec4f(0.0f, 1.0f, 0.0f, 0.0f);
        z_axis_ = vne::math::Vec4f(0.0f, 0.0f, 1.0f, 0.0f);
        w_axis_ = vne::math::Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
        equal_vec_ = vne::math::Vec4f(567.345f);
        rand_xyzw_vec__ = vne::math::Vec4f(0.000034f, 0.000057f, 0.875f, 0.00874f);

        x_point = vne::math::Vec4f(1.0f, 0.0f, 0.0f, 0.0f);
        y_point = vne::math::Vec4f(0.0f, 1.0f, 0.0f, 0.0f);
        z_point = vne::math::Vec4f(0.0f, 0.0f, 1.0f, 0.0f);
        z_point = vne::math::Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
        xyzw_point = vne::math::Vec4f(3.5f, 1.0f, 1.5f, 3.4f);
    }

    void TearDown() override {}

   protected:
    vne::math::Vec4f zero_vec_;
    vne::math::Vec4f one_vec_;
    vne::math::Vec4f xyzw_vec_;
    vne::math::Vec4f x_axis_;
    vne::math::Vec4f y_axis_;
    vne::math::Vec4f z_axis_;
    vne::math::Vec4f w_axis_;
    vne::math::Vec4f equal_vec_;
    vne::math::Vec4f neg_xyzw_vec__;
    vne::math::Vec4f rand_xyzw_vec__;
    vne::math::Vec4f x_point;
    vne::math::Vec4f y_point;
    vne::math::Vec4f z_point;
    vne::math::Vec4f w_point;
    vne::math::Vec4f xyzw_point;
};

/**
 * Test Vec4f dimensions
 *
 * vne::math::Vec4f::dim()
 * vne::math::Vec4f::size()
 *
 */
TEST_F(Vec4fTest, TestVec4fDimensions) {
    ASSERT_EQ(4, vne::math::Vec4f::dim());
    ASSERT_EQ(4, vne::math::Vec4f::size());
    ASSERT_NE(5, vne::math::Vec4f::dim());
    ASSERT_NE(10, vne::math::Vec4f::size());
}

/**
 * Test Vec4f zero vector
 *
 * vne::math::Vec4f::zero()
 *
 */
TEST_F(Vec4fTest, TestVec4fZero) {
    ASSERT_EQ(glm::vec4(0.0f), zero_vec_);
    ASSERT_EQ(zero_vec_, vne::math::Vec4f::zero());
}

/**
 * Test Vec4f one vector
 *
 * vne::math::Vec4f::one()
 *
 */
TEST_F(Vec4fTest, TestVec4fOne) {
    ASSERT_EQ(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), one_vec_);
    ASSERT_EQ(one_vec_, vne::math::Vec4f::one());
}

/**
 * Test Vec4f x-axis
 *
 * vne::math::Vec4f::xAxis()
 *
 */
TEST_F(Vec4fTest, TestVec4fXAxis) {
    ASSERT_EQ(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f), x_axis_);
    ASSERT_EQ(x_axis_, vne::math::Vec4f::xAxis());
}

/**
 * Test Vec4f y-axis
 *
 * vne::math::Vec4f::yAxis()
 *
 */
TEST_F(Vec4fTest, TestVec4fYAxis) {
    ASSERT_EQ(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f), y_axis_);
    ASSERT_EQ(y_axis_, vne::math::Vec4f::yAxis());
}

/**
 * Test Vec4f z-axis
 *
 * vne::math::Vec4f::zAxis()
 *
 */
TEST_F(Vec4fTest, TestVec4fZAxis) {
    ASSERT_EQ(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f), z_axis_);
    ASSERT_EQ(z_axis_, vne::math::Vec4f::zAxis());
}

/**
 * Test Vec4f w-axis
 *
 * vne::math::Vec4f::wAxis()
 *
 */
TEST_F(Vec4fTest, TestVec4fWAxis) {
    ASSERT_EQ(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), w_axis_);
    ASSERT_EQ(w_axis_, vne::math::Vec4f::wAxis());
}

/**
 * Test Vec4f GetPtr
 *
 * vec.getPtr()
 *
 */
TEST_F(Vec4fTest, TestVec4fGetPtr) {
    ASSERT_EQ(xyzw_vec_.x, *(xyzw_vec_.getPtr()));
    ASSERT_EQ(xyzw_vec_.y, *(xyzw_vec_.getPtr() + 1));
    ASSERT_EQ(xyzw_vec_.z, *(xyzw_vec_.getPtr() + 2));
    ASSERT_EQ(xyzw_vec_.w, *(xyzw_vec_.getPtr() + 3));
}

/**
 * Test Vec4f XYZ
 *
 * vec.xyz()
 *
 */
TEST_F(Vec4fTest, TestVec4fXYZ) {
    ASSERT_EQ(vne::math::Vec3f(xyzw_vec_.x, xyzw_vec_.y, xyzw_vec_.z), xyzw_vec_.xyz());
}

/**
 * Test Vec4f XY
 *
 * vec.xy()
 *
 */
TEST_F(Vec4fTest, TestVec4fXY) {
    ASSERT_EQ(vne::math::Vec2f(xyzw_vec_.x, xyzw_vec_.y), xyzw_vec_.xy());
}

/**
 * Test coping the 3d vector into 4d vector
 *
 */
TEST_F(Vec4fTest, TestVec4fCopy3dVec) {
    vne::math::Vec4f vec_4d;
    vne::math::Vec3f vec_3d = xyzw_vec_.xyz();

    vec_4d = vec_3d;
    ASSERT_EQ(vne::math::Vec4f(xyzw_vec_.x, xyzw_vec_.y, xyzw_vec_.z, 0.0f), vec_4d);

    vec_4d = vne::math::Vec4f(vec_3d, 5.0f);
    ASSERT_EQ(vne::math::Vec4f(xyzw_vec_.x, xyzw_vec_.y, xyzw_vec_.z, 5.0f), vec_4d);

    vec_4d = glm::vec3(1.0f, 2.0f, 3.0f);
    ASSERT_EQ(vne::math::Vec4f(1.0f, 2.0f, 3.0f, 0.0f), vec_4d);

    vec_4d = vne::math::Vec4f(glm::vec3(1.0f, 2.0f, 3.0f), 4.0f);
    ASSERT_EQ(vne::math::Vec4f(1.0f, 2.0f, 3.0f, 4.0f), vec_4d);
}

/**
 * Test coping the 2d vector into 4d vector
 *
 */
TEST_F(Vec4fTest, TestVec4fCopy2dVec) {
    vne::math::Vec4f vec_4d;
    vne::math::Vec2f vec_2d = xyzw_vec_.xy();
    vec_4d = vec_2d;
    ASSERT_EQ(vne::math::Vec4f(xyzw_vec_.x, xyzw_vec_.y, 0.0f, 0.0f), vec_4d);
    vec_4d = glm::vec2(1.0f, 2.0f);
    ASSERT_EQ(vne::math::Vec4f(1.0f, 2.0f, 0.0f, 0.0f), vec_4d);
}

/**
 * Test coping the plane into 4d vector
 *
 */
// TEST_F(Vec4fTest, TestVec4fCopyPlane) {
//     vne::math::Plane_C plane;
//     vne::math::Vec4f vec = plane;
//     ASSERT_EQ(vec.x, 0.0f);
//     ASSERT_EQ(vec.y, 0.0f);
//     ASSERT_EQ(vec.z, 1.0f);
//     ASSERT_EQ(vec.w, 0.0f);
// }

/**
 * Test Vec4f Abs
 *
 * vec.abs()
 *
 */
TEST_F(Vec4fTest, TestVec4fAbs) {
    ASSERT_EQ(glm::abs(glm::vec4(neg_xyzw_vec__)), neg_xyzw_vec__.abs());
}

/**
 * Test Vec4f Length and LengthSquare
 */
TEST_F(Vec4fTest, TestVec4fLength) {
    ASSERT_EQ(glm::length(glm::vec4(0.0f)), zero_vec_.length());
    ASSERT_EQ(glm::length(glm::vec4(1.0f)), one_vec_.length());
    ASSERT_EQ(glm::length(glm::vec4(0.0f)), zero_vec_.lengthSquare());
    ASSERT_EQ(glm::length2(glm::vec4(1.0f)), one_vec_.lengthSquare());
    ASSERT_EQ(glm::length2(glm::vec4(xyzw_vec_)), xyzw_vec_.lengthSquare());
}

/**
 * Test Vec4f Normalize
 *
 * vec.normalize()
 *
 */
TEST_F(Vec4fTest, TestVec4fNormalize) {
    ASSERT_TRUE(x_axis_ == x_axis_.normalize());
    ASSERT_TRUE(y_axis_ == y_axis_.normalize());
    ASSERT_TRUE(x_axis_ == vne::math::Vec4f::normalized(x_axis_));
    ASSERT_TRUE(y_axis_ == vne::math::Vec4f::normalized(y_axis_));
    ASSERT_EQ(glm::normalize(glm::vec4(xyzw_vec_)), xyzw_vec_.normalize());
}

/**
 * Test Vec4f Min(...)
 *
 * vec1.min(vec2)
 *
 */
TEST_F(Vec4fTest, TestVec4fMin) {
    ASSERT_TRUE(zero_vec_ == one_vec_.min(zero_vec_));
    ASSERT_TRUE(xyzw_vec_ == neg_xyzw_vec__.min(xyzw_vec_));
}

/**
 * Test Vec4f Max(...)
 *
 * vec1.max(vec2)
 *
 */
TEST_F(Vec4fTest, TestVec4fMax) {
    ASSERT_TRUE(one_vec_ == one_vec_.max(zero_vec_));
    ASSERT_TRUE(neg_xyzw_vec__ == neg_xyzw_vec__.max(xyzw_vec_));
}

/**
 * Test Vec4f MinComponent(...)
 *
 * vec.minComponent()
 *
 */
TEST_F(Vec4fTest, TestVec4fMinComponent) {
    ASSERT_TRUE(neg_xyzw_vec__.z == neg_xyzw_vec__.minComponent());
}

/**
 * Test Vec4f MaxComponent(...)
 *
 * vec.maxComponent()
 *
 */
TEST_F(Vec4fTest, TestVec4fMaxComponent) {
    ASSERT_TRUE(neg_xyzw_vec__.y == neg_xyzw_vec__.maxComponent());
}

/**
 * Test Vec4f Dot(...)
 *
 * dot = vec1.dot(vec2)
 * dot = vne::math::Vec4f::dot(vec1, vec2)
 *
 */
TEST_F(Vec4fTest, TestVec4fDot) {
    ASSERT_EQ(0.0f, x_axis_.dot(y_axis_));
    ASSERT_EQ(2.0f, xyzw_vec_.dot(x_axis_));
    ASSERT_EQ(2.5f, xyzw_vec_.dot(y_axis_));
    ASSERT_EQ(4.0f, xyzw_vec_.dot(z_axis_));
    ASSERT_EQ(9.5f, xyzw_vec_.dot(one_vec_));
    ASSERT_EQ(9.5f, vne::math::Vec4f::dot(xyzw_vec_, one_vec_));
    ASSERT_FLOAT_EQ(vne::math::halfPi<float>(),
                    vne::math::acos(x_axis_.dot(y_axis_) / (x_axis_.length() * y_axis_.length())));
}

/**
 * Test Vec4f Distance calculation.
 *
 * dist = vec1.distance(vec2)
 * dist = vne::math::Vec4f::distance(vec1, vec2)
 *
 */
TEST_F(Vec4fTest, TestVec4fDistance) {
    ASSERT_FLOAT_EQ(static_cast<float>(SQRT_TWO), vne::math::Vec4f::distance(x_point, y_point));
    ASSERT_FLOAT_EQ(5.2019229f, vne::math::Vec4f::distance(vne::math::Vec4f::zero(), xyzw_point));
    ASSERT_FLOAT_EQ(4.5891175f, vne::math::Vec4f::distance(x_point, xyzw_point));
    ASSERT_FLOAT_EQ(5.1048999f, xyzw_point.distance(y_point));
}

/**
 * Test Vec4f Rotate function.
 *
 * vec.rotate(axis, angle)
 *
 */
TEST_F(Vec4fTest, TestVec4fRotate) {
    vne::math::Vec4f test_vec{1.0f};
    ASSERT_TRUE(vne::math::Vec4f(1.0f, -1.0f, 1.0f, 1.0f)
                    .areSame(test_vec.rotate(z_axis_.xyz(), -static_cast<float>(HALF_PI))));
    ASSERT_TRUE(
        vne::math::Vec4f(-1.0f, 1.0f, 1.0f, 1.0f).areSame(test_vec.rotate(z_axis_.xyz(), static_cast<float>(HALF_PI))));
    ASSERT_TRUE(vne::math::Vec4f(1.41421f, 1.0f, 0.0f, 1.0f)
                    .areSame(test_vec.rotate(y_axis_.xyz(), static_cast<float>(QUARTER_PI)), 1E-5f));
}

/**
 * Test Vec4f Reflect(...)
 *
 * vec.reflect(normal)
 *
 */
TEST_F(Vec4fTest, TestVec4fReflect) {
    vne::math::Vec4f test_vec;
    test_vec.x = -xyzw_vec_.x;
    test_vec.y = xyzw_vec_.y;
    test_vec.z = -xyzw_vec_.z;
    test_vec.w = -xyzw_vec_.w;
    ASSERT_TRUE(test_vec.areSame(-xyzw_vec_.reflect(y_axis_)));
}

/**
 * Test Vec4f Refract(...)
 *
 * vec.refract(normal, mu)
 *
 */
TEST_F(Vec4fTest, TestVec4fRefract) {
    xyzw_vec_.normalize();
    vne::math::Vec4f test_vec;
    test_vec.x = -xyzw_vec_.x;
    test_vec.y = xyzw_vec_.y;
    test_vec.z = -xyzw_vec_.z;
    test_vec.w = -xyzw_vec_.w;
    ASSERT_TRUE(test_vec.areSame(-xyzw_vec_.refract(y_axis_, 1.0f)));
    ASSERT_TRUE(y_axis_.areSame(-xyzw_vec_.refract(y_axis_, 0.0f)));
    vne::math::Vec4f out_vec{-0.191565f, 0.898521f, -0.383131f, -0.0957826f};
    vne::math::Vec4f direction = vne::math::Vec4f::normalized(xyzw_vec_);
    ASSERT_TRUE(out_vec.areSame(-direction.refract(y_axis_, 0.5f), 1E-5f));
}

/**
 * Test Vec4f Project(...)
 *
 * vec1.project(vec2)
 *
 */
TEST_F(Vec4fTest, TestVec4fProject) {
    ASSERT_EQ(zero_vec_, x_axis_.project(y_axis_));  // perpendicular vectors
    ASSERT_EQ(vne::math::Vec4f(0.0f, xyzw_vec_.y, 0.0f, 0.0f), xyzw_vec_.project(y_axis_));
    // Second vector could be any vector ( normal is not compulsory )
    ASSERT_EQ(vne::math::Vec4f(0, xyzw_vec_.y, 0.0f, 0.0f),
              xyzw_vec_.project(vne::math::Vec4f(0.0f, 3.0f, 0.0f, 0.0f)));
    // Perpendicular vector of xyzw_vec_ w.r.t. y_axis_
    ASSERT_EQ(vne::math::Vec4f(xyzw_vec_.x, 0.0f, xyzw_vec_.z, xyzw_vec_.w), xyzw_vec_ - xyzw_vec_.project(y_axis_));
}

/**
 * Test Vec4f Reject(...)
 *
 * vec1.reject(vec2)
 *
 */
TEST_F(Vec4fTest, TestVec4fReject) {
    // Perpendicular vector of xyzw_vec_ w.r.t. y_axis_
    ASSERT_EQ(vne::math::Vec4f(xyzw_vec_.x, 0.0f, xyzw_vec_.z, xyzw_vec_.w), xyzw_vec_ - xyzw_vec_.project(y_axis_));
    ASSERT_EQ(vne::math::Vec4f(xyzw_vec_.x, 0.0f, xyzw_vec_.z, xyzw_vec_.w), xyzw_vec_.reject(y_axis_));
}

/**
 * Test Vec4f DecomposeVec(...)
 *
 * p.decomposeVec(q, proj, perp)
 *
 */
TEST_F(Vec4fTest, TestVec4fDecomposeVec) {
    vne::math::Vec4f proj;
    vne::math::Vec4f perp;
    xyzw_vec_.decomposeVec(y_axis_, proj, perp);
    ASSERT_EQ(vne::math::Vec4f(0.0f, xyzw_vec_.y, 0.0f, 0.0f), proj);
    ASSERT_EQ(vne::math::Vec4f(xyzw_vec_.x, 0.0f, xyzw_vec_.z, xyzw_vec_.w), perp);
}

/**
 * Test Vec4f AreSame(...)
 *
 * vec1.areSame(vec2, eps)
 *
 */
TEST_F(Vec4fTest, TestVec4fAreSame) {
    ASSERT_TRUE(rand_xyzw_vec__.areSame(vne::math::Vec4f(0.000034001f, 0.00005705f, 0.8750001f, 0.008740001f), 1E-5f));
    ASSERT_FALSE(rand_xyzw_vec__.areSame(vne::math::Vec4f(0.000035f, 0.000056f, 0.874f, 0.00875f)));
    ASSERT_FALSE(equal_vec_.areSame(vne::math::Vec4f(567.3453f)));
    ASSERT_TRUE(equal_vec_.areSame(vne::math::Vec4f(567.34503f)));
    ASSERT_TRUE(equal_vec_.areSame(vne::math::Vec4f(567.3453f), 1E-3f));
}

/**
 * Test Vec4f AreAligned(...)
 *
 * vec1.areAligned(vec2, eps)
 *
 */
TEST_F(Vec4fTest, TestVec4fAreAligned) {
    ASSERT_FALSE(vne::math::Vec4f(1.0f).areSame(vne::math::Vec4f(2.0f)));
    ASSERT_TRUE(vne::math::Vec4f(1.0f).areAligned(vne::math::Vec4f(2.0f)));
    ASSERT_FALSE(vne::math::Vec4f(1.0f).areAligned(vne::math::Vec4f(2.05f, 2.0f, 2.0f, 2.0f)));
    ASSERT_TRUE(vne::math::Vec4f(1.0f).areAligned(vne::math::Vec4f(2.05f, 2.0499999f, 2.0499999f, 2.0499999f), 1E-4f));
}

/**
 * Test Vec4f IsZero(...)
 *
 * vec1.isZero(eps)
 *
 */
TEST_F(Vec4fTest, TestVec4fIsZero) {
    ASSERT_TRUE(zero_vec_.isZero());
    ASSERT_FALSE(rand_xyzw_vec__.isZero());
    ASSERT_FALSE(vne::math::Vec4f(1.0f).isZero(1E-5f));
}

/**
 * Test Vec4f IsNormalized(...)
 *
 * vec1.isNormalized(eps)
 *
 */
TEST_F(Vec4fTest, TestVec4fIsNormalized) {
    ASSERT_TRUE(x_axis_.isNormalized());
    ASSERT_TRUE(y_axis_.isNormalized());
    ASSERT_TRUE(w_axis_.isNormalized());
    ASSERT_FALSE(xyzw_vec_.isNormalized());
    ASSERT_TRUE(vne::math::Vec4f(0.5f).isNormalized());
}

/**
 * Test Vec4f Angle(...)
 *
 * vec1.angle(vec2)
 * p1.angle(p2, p3)
 *
 */
TEST_F(Vec4fTest, TestVec4fAngle) {
    ASSERT_TRUE(vne::math::areSame(vne::math::halfPi<float>(), x_axis_.angle(y_axis_)));

    ASSERT_TRUE(vne::math::areSame(60.0f, vne::math::radToDeg(x_axis_.angle(one_vec_))));

    ASSERT_TRUE(vne::math::areSame(vne::math::pi<float>() / 6.0f,
                                   vne::math::Vec4f(static_cast<float>(SQRT_THREE), 1.0f, 0.0f, 0.0f)
                                       .angle(vne::math::Vec4f(1.0f, static_cast<float>(SQRT_THREE), 0.0f, 0.0f))));

    ASSERT_TRUE(vne::math::areSame(vne::math::twoPi<float>() / 3.0f,
                                   vne::math::Vec4f(static_cast<float>(SQRT_THREE), 1.0f, 0.0f, 0.0f)
                                       .angle(vne::math::Vec4f(-static_cast<float>(SQRT_THREE), 1.0f, 0.0f, 0.0f))));

    ASSERT_TRUE(vne::math::areSame(
        63.5799f,
        vne::math::radToDeg(vne::math::Vec4f(4.0f, 0.0f, 7.0f, 1.0f).angle(vne::math::Vec4f(-2.0f, 1.0f, 3.0f, 1.0f))),
        1E-4f));
    ASSERT_TRUE(vne::math::areSame(
        135.608f,
        vne::math::radToDeg(
            (vne::math::Vec4f(3.0f, 4.0f, -7.0f, 0.0f).angle(vne::math::Vec4f(-2.0f, 1.0f, 3.0f, 0.0f)))),
        1E-4f));

    ASSERT_TRUE(vne::math::areSame(
        160.582f,
        vne::math::radToDeg((vne::math::Vec4f(0.0f).angle(vne::math::Vec4f(2.0f, 5.0f, 4.0f, 0.0f),
                                                          vne::math::Vec4f(-2.0f, -3.0f, -5.0f, 0.0f)))),
        1E-4f));
}

/**
 * Test Vec4f MidPoint(...)
 *
 * vne::math::Vec4f::midPoint(vec1, vec2)
 * vec1.midPoint(vec2)
 *
 */
TEST_F(Vec4fTest, TestVec4fMidPoint) {
    ASSERT_EQ(vne::math::Vec4f(0.5f, 0.5f, 0.0f, 0.0f), vne::math::Vec4f::midPoint(x_axis_, y_axis_));
    ASSERT_EQ(vne::math::Vec4f(0.5f, 0.5f, 0.0f, 0.0f), x_axis_.midPoint(y_axis_));
    ASSERT_EQ(vne::math::Vec4f(0.0f, 0.0f, 0.5f, 0.5f), z_axis_.midPoint(w_axis_));
}

/**
 * Test Vec4f Lerp(...)
 *
 * vne::math::Vec4f::lerp(vec1, vec2, t)
 * vec1.lerp(vec2, t)
 *
 */
TEST_F(Vec4fTest, TestVec4fLerp) {
    ASSERT_EQ(vne::math::Vec4f(0.5f, 0.5f, 0.0f, 0.0f), vne::math::Vec4f::lerp(x_axis_, y_axis_, 0.5f));
    ASSERT_EQ(x_axis_, vne::math::Vec4f::lerp(x_axis_, y_axis_, 0.0f));
    ASSERT_EQ(y_axis_, vne::math::Vec4f::lerp(x_axis_, y_axis_, 1.0f));
    ASSERT_EQ(y_axis_, x_axis_.lerp(y_axis_, 1.0f));
}

/**
 * Test Vec4f addition
 */
TEST_F(Vec4fTest, TestVec4fAddition) {
    float scalar = 2.0f;
    vne::math::Vec4f test_vec = zero_vec_;

    // Test vector addition
    ASSERT_EQ(glm::vec4(zero_vec_) + glm::vec4(one_vec_), glm::vec4(zero_vec_ + one_vec_));

    // Test += operator with a vector
    test_vec += one_vec_;
    ASSERT_EQ(glm::vec4(zero_vec_) + glm::vec4(1.0f), glm::vec4(test_vec));

    // Test vector-scalar addition
    ASSERT_EQ(glm::vec4(neg_xyzw_vec__) + glm::vec4(scalar), glm::vec4(neg_xyzw_vec__ + scalar));

    // Test += operator with a scalar
    test_vec += scalar;
    ASSERT_EQ(glm::vec4(zero_vec_ + one_vec_) + glm::vec4(scalar), glm::vec4(test_vec));

    // Test chain addition of vector and scalar
    ASSERT_EQ(glm::vec4(test_vec) + glm::vec4(xyzw_vec_) + glm::vec4(scalar), glm::vec4(test_vec + xyzw_vec_ + scalar));

    // Test chain addition with a random vector
    ASSERT_EQ(glm::vec4(test_vec) + glm::vec4(xyzw_vec_) + glm::vec4(scalar) + glm::vec4(rand_xyzw_vec__),
              glm::vec4(test_vec + xyzw_vec_ + scalar + rand_xyzw_vec__));
}

/**
 * Test Vec4f subtraction
 */
TEST_F(Vec4fTest, TestVec4fSubtraction) {
    float scalar = 2.45f;
    vne::math::Vec4f test_vec = zero_vec_;

    // Test vector subtraction
    ASSERT_EQ(glm::vec4(neg_xyzw_vec__) - glm::vec4(one_vec_), glm::vec4(neg_xyzw_vec__ - one_vec_));

    // Test -= operator with a vector
    test_vec -= neg_xyzw_vec__;
    ASSERT_EQ(glm::vec4(zero_vec_) - glm::vec4(neg_xyzw_vec__), glm::vec4(test_vec));

    // Test vector-scalar subtraction
    ASSERT_EQ(glm::vec4(neg_xyzw_vec__) - glm::vec4(scalar), glm::vec4(neg_xyzw_vec__ - scalar));

    // Test -= operator with a scalar
    test_vec -= scalar;
    ASSERT_EQ(glm::vec4(zero_vec_ - neg_xyzw_vec__) - glm::vec4(scalar), glm::vec4(test_vec));

    // Test chain subtraction of vector and scalar
    ASSERT_EQ(glm::vec4(test_vec) - glm::vec4(xyzw_vec_) + glm::vec4(scalar), glm::vec4(test_vec - xyzw_vec_ + scalar));
}

/**
 * Test Vec4f multiplication
 */
TEST_F(Vec4fTest, TestVec4fMultiplication) {
    float scalar = 0.000045f;
    vne::math::Vec4f test_vec = one_vec_;

    // Test vector multiplication
    ASSERT_EQ(glm::vec4(xyzw_vec_) * glm::vec4(test_vec), glm::vec4(xyzw_vec_ * test_vec));

    // Test *= operator with a vector
    test_vec *= xyzw_vec_;
    ASSERT_EQ(glm::vec4(one_vec_ * xyzw_vec_), glm::vec4(test_vec));

    // Test vector-scalar multiplication
    ASSERT_EQ(glm::vec4(test_vec) * glm::vec4(scalar), glm::vec4(test_vec * scalar));

    // Test *= operator with a scalar
    test_vec *= scalar;
    ASSERT_EQ(glm::vec4(one_vec_ * xyzw_vec_ * scalar), glm::vec4(test_vec));
}

/**
 * Test Vec4f division
 */
TEST_F(Vec4fTest, TestVec4fDivision) {
    float scalar = 45.345f;
    vne::math::Vec4f test_vec = one_vec_;

    // Test vector division
    ASSERT_EQ(glm::vec4(xyzw_vec_) / glm::vec4(test_vec), glm::vec4(xyzw_vec_ / test_vec));

    // Test /= operator with a vector
    test_vec /= xyzw_vec_;
    ASSERT_EQ(glm::vec4(one_vec_ / xyzw_vec_), glm::vec4(test_vec));

    // Test vector-scalar division
    ASSERT_EQ(glm::vec4(test_vec) / glm::vec4(scalar), glm::vec4(test_vec / scalar));

    // Test /= operator with a scalar
    test_vec /= scalar;
    ASSERT_EQ(glm::vec4(one_vec_ / xyzw_vec_ / scalar), glm::vec4(test_vec));
}

/**
 * Test Vec4f comparison
 */
TEST_F(Vec4fTest, TestVec4fComparison) {
    vne::math::Vec4f test_vec_equal = xyzw_vec_;
    vne::math::Vec4f test_vec_less = xyzw_vec_ - 2.0f;
    vne::math::Vec4f test_vec_greater = xyzw_vec_ + 2.0f;
    ASSERT_TRUE(xyzw_vec_ > test_vec_less);
    ASSERT_TRUE(xyzw_vec_ < test_vec_greater);
    ASSERT_TRUE(xyzw_vec_ == test_vec_equal);
    ASSERT_TRUE(xyzw_vec_ != test_vec_less);
    ASSERT_TRUE(xyzw_vec_ != test_vec_greater);
}

/**
 * Test Vec4f assignment
 */
TEST_F(Vec4fTest, TestVec4fAssignment) {
    vne::math::Vec4f test_vec;
    ASSERT_EQ(xyzw_vec_, test_vec = xyzw_vec_);
}

/**
 * Test Vec4f specific component
 */
TEST_F(Vec4fTest, TestVec4fComponent) {
    float value;
    ASSERT_EQ(xyzw_vec_.x, xyzw_vec_[0]);
    ASSERT_EQ(xyzw_vec_.y, xyzw_vec_[1]);
    ASSERT_EQ(xyzw_vec_.z, xyzw_vec_[2]);
    ASSERT_EQ(xyzw_vec_.w, xyzw_vec_[3]);
    ASSERT_EQ(xyzw_vec_.y, value = xyzw_vec_[1]);
    ASSERT_EQ(xyzw_vec_.w, value = xyzw_vec_[3]);
}

/**
 * Test Vec4f inverted vector
 */
TEST_F(Vec4fTest, TestVec4fInverted) {
    ASSERT_EQ(-glm::vec4(xyzw_vec_), -xyzw_vec_);
}

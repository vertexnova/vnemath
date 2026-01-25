/* ---------------------------------------------------------------------
 * Copyright (c) 2024 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Author:    Ajeet Singh Yadav
 * Created:   August-2024
 *
 * Autodoc:   yes
 * ----------------------------------------------------------------------
 */

// Testing framework
#include <gtest/gtest.h>

// Project headers
#include "vertexnova/math/math_utils.h"
#include "vertexnova/math/vec2f.h"

using namespace vne;

class Vec2fTest : public ::testing::Test {
    // Interface of test fixture base class
   protected:
    void SetUp() override {
        neg_xy_vec__ = vne::math::Vec2f(-2.0f, 14.5f);
        zero_vec_ = vne::math::Vec2f();
        one_vec_ = vne::math::Vec2f(1.0f, 1.0f);
        xy_vec_ = vne::math::Vec2f(3.0f, 4.0f);
        x_axis_ = vne::math::Vec2f(1.0f, 0.0f);
        y_axis_ = vne::math::Vec2f(0.0f, 1.0f);
        equal_vec_ = vne::math::Vec2f(567.345f);
        rand_xy_vec__ = vne::math::Vec2f(0.000034f, 0.000057f);

        x_point_ = vne::math::Vec2f(1.0f, 0.0f);
        y_point_ = vne::math::Vec2f(0.0f, 1.0f);
        xy_point__ = vne::math::Vec2f(1.0f, 1.0f);
    }

    void TearDown() override {}

   protected:
    vne::math::Vec2f zero_vec_;
    vne::math::Vec2f one_vec_;
    vne::math::Vec2f xy_vec_;
    vne::math::Vec2f x_axis_;
    vne::math::Vec2f y_axis_;
    vne::math::Vec2f equal_vec_;
    vne::math::Vec2f neg_xy_vec__;
    vne::math::Vec2f rand_xy_vec__;
    vne::math::Vec2f x_point_;
    vne::math::Vec2f y_point_;
    vne::math::Vec2f xy_point__;
};

/**
 * Test Vec2f dimensions
 *
 */
TEST_F(Vec2fTest, TestVec2fDimensions) {
    ASSERT_EQ(2, vne::math::Vec2f::dim());
    ASSERT_EQ(2, vne::math::Vec2f::size());
    ASSERT_NE(3, vne::math::Vec2f::dim());
    ASSERT_NE(6, vne::math::Vec2f::size());
}

/**
 * Test Vec2f zero vector
 */
TEST_F(Vec2fTest, TestVec2fZero) {
    ASSERT_EQ(glm::vec2(0.0f, 0.0f), zero_vec_);
    ASSERT_EQ(zero_vec_, vne::math::Vec2f::zero());
}

/**
 * Test Vec2f one vector
 */
TEST_F(Vec2fTest, TestVec2fOne) {
    ASSERT_EQ(glm::vec2(1.0f, 1.0f), one_vec_);
    ASSERT_EQ(one_vec_, vne::math::Vec2f::one());
}

/**
 * Test Vec2f x-axis
 */
TEST_F(Vec2fTest, TestVec2fXAxis) {
    ASSERT_EQ(glm::vec2(1.0f, 0.0f), x_axis_);
    ASSERT_EQ(x_axis_, vne::math::Vec2f::xAxis());
}

/**
 * Test Vec2f y-axis
 */
TEST_F(Vec2fTest, TestVec2fYAxis) {
    ASSERT_EQ(glm::vec2(0.0f, 1.0f), y_axis_);
    ASSERT_EQ(y_axis_, vne::math::Vec2f::yAxis());
}

/**
 * Test Vec2f Length and LengthSquare
 */
TEST_F(Vec2fTest, TestVec2fLength) {
    ASSERT_EQ(glm::length(glm::vec2(0.0f, 0.0f)), zero_vec_.length());
    ASSERT_EQ(glm::length(glm::vec2(1.0f, 1.0f)), one_vec_.length());
    ASSERT_EQ(glm::length(glm::vec2(0.0f, 0.0f)), zero_vec_.lengthSquare());
    ASSERT_EQ(glm::length2(glm::vec2(1.0f, 1.0f)), one_vec_.lengthSquare());
    ASSERT_EQ(glm::length2(glm::vec2(xy_vec_)), xy_vec_.lengthSquare());
}

/**
 * Test Vec2f GetPtr
 *
 * vec.getPtr()
 *
 */
TEST_F(Vec2fTest, TestVec2fGetPtr) {
    ASSERT_EQ(xy_vec_.x, *(xy_vec_.getPtr()));
    ASSERT_EQ(xy_vec_.y, *(xy_vec_.getPtr() + 1));
    ASSERT_EQ(x_axis_.x, *(x_axis_.getPtr()));
    ASSERT_EQ(x_axis_.y, *(x_axis_.getPtr() + 1));
}

/**
 * Test Vec2f Abs
 *
 * vec.abs()
 *
 */
TEST_F(Vec2fTest, TestVec2fAbs) {
    ASSERT_EQ(glm::abs(glm::vec2(neg_xy_vec__)), neg_xy_vec__.abs());
}

/**
 * Test Vec2f Normalize
 *
 * vec.normalize()
 *
 */
TEST_F(Vec2fTest, TestVec2fNormalize) {
    ASSERT_TRUE(x_axis_ == x_axis_.normalize());
    ASSERT_TRUE(y_axis_ == y_axis_.normalize());
    ASSERT_TRUE(x_axis_ == vne::math::Vec2f::normalized(x_axis_));
    ASSERT_TRUE(y_axis_ == vne::math::Vec2f::normalized(y_axis_));
    ASSERT_EQ(glm::normalize(glm::vec2(xy_vec_)), xy_vec_.normalize());
#ifdef _DEBUG
    ASSERT_DEATH(zero_vec_.normalize(), ".*");
#endif  // _DEBUG
}

/**
 * Test Vec2f Min(...)
 *
 * vec1.min(vec2)
 *
 */
TEST_F(Vec2fTest, TestVec2fMin) {
    ASSERT_TRUE(zero_vec_ == one_vec_.min(zero_vec_));
    ASSERT_TRUE(xy_vec_ == neg_xy_vec__.min(xy_vec_));
}

/**
 * Test Vec2f Max(...)
 *
 * vec1.max(vec2)
 *
 */
TEST_F(Vec2fTest, TestVec2fMax) {
    ASSERT_TRUE(one_vec_ == one_vec_.max(zero_vec_));
    ASSERT_TRUE(neg_xy_vec__ == neg_xy_vec__.max(xy_vec_));
}

/**
 * Test Vec2f MinComponent(...)
 *
 * vec.minComponent()
 *
 */
TEST_F(Vec2fTest, TestVec2fMinComponent) {
    ASSERT_TRUE(neg_xy_vec__.x == neg_xy_vec__.minComponent());
}

/**
 * Test Vec2f MaxComponent(...)
 *
 * vec.maxComponent()
 *
 */
TEST_F(Vec2fTest, TestVec2fMaxComponent) {
    ASSERT_TRUE(neg_xy_vec__.y == neg_xy_vec__.maxComponent());
}

/**
 * Test Vec2f Dot(...)
 *
 * dot = vec1.dot(vec2)
 * dot = vne::math::Vec2f::dot(vec1, vec2)
 *
 */
TEST_F(Vec2fTest, TestVec2fDot) {
    ASSERT_EQ(0.0f, x_axis_.dot(y_axis_));
    ASSERT_EQ(3.0f, xy_vec_.dot(x_axis_));
    ASSERT_EQ(4.0f, xy_vec_.dot(y_axis_));
    ASSERT_EQ(7.0f, xy_vec_.dot(one_vec_));
    ASSERT_EQ(7.0f, vne::math::Vec2f::dot(xy_vec_, one_vec_));
    ASSERT_FLOAT_EQ(vne::math::halfPi<float>(),
                    vne::math::acos(x_axis_.dot(y_axis_) / (x_axis_.length() * y_axis_.length())));
}

/**
 * Test Vec2f Cross product.
 *
 * cross = vec1.cross(vec2)
 * cross = vne::math::Vec2f::cross(vec1, vec2)
 *
 */
TEST_F(Vec2fTest, TestVec2fCross) {
    ASSERT_EQ(1.0f, x_axis_.cross(y_axis_));
    ASSERT_EQ(1.0f, vne::math::Vec2f::cross(x_axis_, y_axis_));
    ASSERT_EQ(glm::cross(glm::vec3(x_axis_, 0.0f), glm::vec3(y_axis_, 0.0f)).z,
              vne::math::Vec2f::cross(x_axis_, y_axis_));
}

/**
 * Test Vec2f Distance calculation.
 *
 * dist = vec1.distance(vec2)
 * dist = vne::math::Vec2f::distance(vec1, vec2)
 *
 */
TEST_F(Vec2fTest, TestVec2fDistance) {
    ASSERT_FLOAT_EQ(static_cast<float>(SQRT_TWO), vne::math::Vec2f::distance(x_point_, y_point_));
    ASSERT_FLOAT_EQ(static_cast<float>(SQRT_TWO), vne::math::Vec2f::distance(vne::math::Vec2f::zero(), xy_point__));
    ASSERT_FLOAT_EQ(1.0f, vne::math::Vec2f::distance(x_point_, xy_point__));
    ASSERT_FLOAT_EQ(1.0f, xy_point__.distance(y_point_));
}

/**
 * Test Vec2f Rotate function.
 *
 * vec.rotate(axis, angle)
 *
 */
TEST_F(Vec2fTest, TestVec2fRotate) {
    vne::math::Vec2f test_vec;

    ASSERT_TRUE(x_axis_.areSame(test_vec.rotate(y_axis_, static_cast<float>(-HALF_PI))));
    ASSERT_TRUE(y_axis_.areSame(test_vec.rotate(x_axis_, static_cast<float>(HALF_PI))));
    vne::math::Vec2f out_vec = vne::math::Vec2f(0.0f, 1.41421f);
    ASSERT_TRUE(out_vec.areSame(test_vec.rotate(one_vec_, static_cast<float>(QUARTER_PI)), 1E-5f));
}

/**
 * Test Vec2f Reflect(...)
 *
 * vec.reflect(normal)
 *
 */
TEST_F(Vec2fTest, TestVec2fReflect) {
    vne::math::Vec2f test_vec;
    test_vec.x = -xy_vec_.x;
    test_vec.y = xy_vec_.y;
    ASSERT_TRUE(test_vec.areSame(-xy_vec_.reflect(y_axis_)));
}

/**
 * Test Vec2f Refract(...)
 *
 * vec.refract(normal, mu)
 *
 */
TEST_F(Vec2fTest, TestVec2fRefract) {
    xy_vec_.normalize();
    vne::math::Vec2f test_vec;
    test_vec.x = -xy_vec_.x;
    test_vec.y = xy_vec_.y;
    ASSERT_TRUE(test_vec.areSame(-xy_vec_.refract(y_axis_, 1.0f)));
    ASSERT_TRUE(y_axis_.areSame(-xy_vec_.refract(y_axis_, 0.0f)));

    vne::math::Vec2f out_vec{-1.5f, 2.17945f};
    ASSERT_TRUE(out_vec.areSame(-xy_vec_.refract(y_axis_, 0.5f), 1E-5f));
}

/**
 * Test Vec2f Project(...)
 *
 * vec1.project(vec2)
 *
 */
TEST_F(Vec2fTest, TestVec2fProject) {
    ASSERT_EQ(zero_vec_, x_axis_.project(y_axis_));  // perpendicular vectors
    ASSERT_EQ(vne::math::Vec2f(0, xy_vec_.y), xy_vec_.project(y_axis_));
    // Second vector could be any vector ( normal is not compulsory )
    ASSERT_EQ(vne::math::Vec2f(0, xy_vec_.y), xy_vec_.project(vne::math::Vec2f(0.0f, 3.0f)));
    // Perpendicular vector of xy_vec_ w.r.t. y_axis_
    ASSERT_EQ(vne::math::Vec2f(xy_vec_.x, 0.0f), xy_vec_ - xy_vec_.project(y_axis_));
}

/**
 * Test Vec2f Reject(...)
 *
 * vec1.reject(vec2)
 *
 */
TEST_F(Vec2fTest, TestVec2fReject) {
    // Perpendicular vector of xy_vec_ w.r.t. y_axis_
    ASSERT_EQ(vne::math::Vec2f(xy_vec_.x, 0.0f), xy_vec_ - xy_vec_.project(y_axis_));
    ASSERT_EQ(vne::math::Vec2f(xy_vec_.x, 0.0f), xy_vec_.reject(y_axis_));
}

/**
 * Test Vec2f Decompose(...)
 *
 * p.Decompose(q, proj, perp)
 *
 */
TEST_F(Vec2fTest, TestVec2fDecomposeVec) {
    vne::math::Vec2f proj;
    vne::math::Vec2f perp;
    xy_vec_.decomposeVec(y_axis_, proj, perp);
    ASSERT_EQ(vne::math::Vec2f(0, xy_vec_.y), proj);
    ASSERT_EQ(vne::math::Vec2f(xy_vec_.x, 0.0f), perp);
}

/**
 * Test Vec2f Perpendicular(...)
 *
 * p.perpendicular()
 *
 */
TEST_F(Vec2fTest, TestVec2fPerpendicular) {
    ASSERT_EQ(y_axis_, x_axis_.perpendicular());
    ASSERT_EQ(-x_axis_, y_axis_.perpendicular());
    ASSERT_EQ(-y_axis_, -x_axis_.perpendicular());
    ASSERT_EQ(x_axis_, -y_axis_.perpendicular());
}

/**
 * Test Vec2f AreSame(...)
 *
 * vec1.areSame(vec2, eps)
 *
 */
TEST_F(Vec2fTest, TestVec2fAreSame) {
    ASSERT_TRUE(rand_xy_vec__.areSame(0.000034001f, 0.00005705f));
    ASSERT_TRUE(rand_xy_vec__.areSame(0.000035f, 0.000037f));
    ASSERT_FALSE(equal_vec_.areSame(vne::math::Vec2f(567.3453f)));
    ASSERT_TRUE(equal_vec_.areSame(vne::math::Vec2f(567.34503f)));
    ASSERT_TRUE(equal_vec_.areSame(vne::math::Vec2f(567.3453f), 1E-3f));
#ifdef _DEBUG
    ASSERT_DEATH(equal_vec_.areSame(vne::math::Vec2f(567.3453f), 0.0f),
                 ".* Assertion Failed: eps >= FLOAT_EPSILON :: eps cannot be "
                 "less than FLOAT_EPSILON.*");
#endif  // _DEBUG
}

/**
 * Test Vec2f AreAligned(...)
 *
 * vec1.areAligned(vec2, eps)
 *
 */
TEST_F(Vec2fTest, TestVec2fAreAligned) {
    ASSERT_FALSE(vne::math::Vec2f(1.0f, 1.0f).areSame(vne::math::Vec2f(2.0f, 2.0f)));
    ASSERT_TRUE(vne::math::Vec2f(1.0f, 1.0f).areAligned(vne::math::Vec2f(2.0f, 2.0f)));
    ASSERT_FALSE(vne::math::Vec2f(1.0f, 1.0f).areAligned(vne::math::Vec2f(2.05f, 2.0f)));
    ASSERT_TRUE(vne::math::Vec2f(1.0f, 1.0f).areAligned(vne::math::Vec2f(2.05f, 2.0499999f), 1E-4f));
}

/**
 * Test Vec2f IsZero(...)
 *
 * vec1.isZero(eps)
 *
 */
TEST_F(Vec2fTest, TestVec2fIsZero) {
    ASSERT_TRUE(zero_vec_.isZero());
    ASSERT_FALSE(rand_xy_vec__.isZero());
    ASSERT_TRUE(rand_xy_vec__.isZero(1E-4f));
#ifdef _DEBUG
    ASSERT_DEATH(zero_vec_.isZero(0.0f),
                 ".* Assertion Failed: eps >= FLOAT_EPSILON :: eps cannot be "
                 "less than FLOAT_EPSILON.*");
#endif  // _DEBUG
}

/**
 * Test Vec2f IsNormalized(...)
 *
 * vec1.isNormalized(eps)
 *
 */
TEST_F(Vec2fTest, TestVec2fIsNormalized) {
    ASSERT_TRUE(x_axis_.isNormalized());
    ASSERT_TRUE(y_axis_.isNormalized());
    ASSERT_FALSE(xy_vec_.isNormalized());
    ASSERT_TRUE(
        vne::math::Vec2f(static_cast<float>(SQRT_ONE_OVER_TWO), static_cast<float>(SQRT_ONE_OVER_TWO)).isNormalized());
}

/**
 * Test Vec2f ComposePolar(...)
 *
 * vec.composePolar(radius, angle)
 *
 */
TEST_F(Vec2fTest, TestVec2fComposePolar) {
    vne::math::Vec2f test_vec;
    ASSERT_TRUE(one_vec_.areSame(test_vec.composePolar(static_cast<float>(SQRT_TWO), vne::math::quarterPi<float>())));
}

/**
 * Test Vec2f DecomposePolar(...)
 *
 * vec.decomposePolar(radius, angle)
 *
 */
TEST_F(Vec2fTest, TestVec2fDecomposePolar) {
    float radius;
    float angle;
    one_vec_.decomposePolar(radius, angle);
    ASSERT_TRUE(vne::math::areSame(static_cast<float>(SQRT_TWO), radius));
    ASSERT_TRUE(vne::math::areSame(vne::math::quarterPi<float>(), angle));
    // For the negative angle
    vne::math::Vec2f test_vec{-1.0f, -1.0f};
    test_vec.decomposePolar(radius, angle);
    ASSERT_TRUE(vne::math::areSame(static_cast<float>(SQRT_TWO), radius));
    ASSERT_TRUE(vne::math::areSame(5.0f * vne::math::quarterPi<float>(), angle));
}

/**
 * Test Vec2f Angle(...)
 *
 * vec.angle()
 * vec1.angle(vec2)
 * vec1.angle(point1, point2)
 *
 */
TEST_F(Vec2fTest, TestVec2fAngle) {
    ASSERT_TRUE(vne::math::areSame(vne::math::halfPi<float>(), y_axis_.angle()));
    ASSERT_TRUE(vne::math::areSame(vne::math::halfPi<float>(), x_axis_.angle(y_axis_)));
    ASSERT_TRUE(vne::math::areSame(vne::math::quarterPi<float>(), one_vec_.angle()));
    ASSERT_TRUE(vne::math::areSame(vne::math::quarterPi<float>(), x_axis_.angle(one_vec_)));

    ASSERT_TRUE(vne::math::areSame(vne::math::pi<float>() / 6.0f,
                                   vne::math::Vec2f(static_cast<float>(SQRT_THREE), 1.0f)
                                       .angle(vne::math::Vec2f(1.0f, static_cast<float>(SQRT_THREE)))));
    ASSERT_TRUE(vne::math::areSame(vne::math::twoPi<float>() / 3.0f,
                                   vne::math::Vec2f(static_cast<float>(SQRT_THREE), 1.0f)
                                       .angle(vne::math::Vec2f(-static_cast<float>(SQRT_THREE), 1.0f))));
    ASSERT_TRUE(vne::math::areSame((3.0f / 8.0f) * vne::math::twoPi<float>(),
                                   vne::math::Vec2f(1.0f, 1.0f).angle(vne::math::Vec2f(-2.0f, 0.0f))));
    ASSERT_TRUE(vne::math::areSame(3.0f * vne::math::halfPi<float>(),
                                   vne::math::Vec2f(1.0f, 1.0f).angle(vne::math::Vec2f(1.0f, -1.0f))));

    ASSERT_TRUE(vne::math::areSame(
        3.0f * vne::math::halfPi<float>(),
        vne::math::Vec2f(2.0f, 0.0f).angle(vne::math::Vec2f(4.0f, 2.0f), vne::math::Vec2f(4.0f, -2.0f))));
}

/**
 * Test Vec2f MidPoint(...)
 *
 * vne::math::Vec2f::midPoint(vec1, vec2)
 * vec1.midPoint(vec2)
 *
 */
TEST_F(Vec2fTest, TestVec2fMidPoint) {
    ASSERT_EQ(vne::math::Vec2f(0.5f, 0.5f), vne::math::Vec2f::midPoint(x_axis_, y_axis_));
    ASSERT_EQ(vne::math::Vec2f(0.5f, 0.5f), x_axis_.midPoint(y_axis_));
}

/**
 * Test Vec2f Lerp(...)
 *
 * vne::math::Vec2f::lerp(vec1, vec2, t)
 * vec1.lerp(vec2, t)
 *
 */
TEST_F(Vec2fTest, TestVec2fLerp) {
    ASSERT_EQ(vne::math::Vec2f(0.5f, 0.5f), vne::math::Vec2f::lerp(x_axis_, y_axis_, 0.5f));
    ASSERT_EQ(x_axis_, vne::math::Vec2f::lerp(x_axis_, y_axis_, 0.0f));
    ASSERT_EQ(y_axis_, vne::math::Vec2f::lerp(x_axis_, y_axis_, 1.0f));
    ASSERT_EQ(y_axis_, x_axis_.lerp(y_axis_, 1.0f));
}

/**
 * Test Vec2f addition
 *
 */
TEST_F(Vec2fTest, TestVec2fAddition) {
    float scalar = 2.0f;
    vne::math::Vec2f test_vec = zero_vec_;

    // 1. Compare zero_vec_ + one_vec_
    ASSERT_EQ(glm::vec2(zero_vec_) + glm::vec2(one_vec_), glm::vec2(zero_vec_ + one_vec_));

    // 2. Test the += operation on test_vec
    test_vec += one_vec_;
    ASSERT_EQ(glm::vec2(one_vec_), glm::vec2(test_vec));  // Updated for clarity

    // 3. Compare neg_xy_vec__ + scalar
    ASSERT_EQ(glm::vec2(neg_xy_vec__) + glm::vec2(scalar, scalar), glm::vec2(neg_xy_vec__ + scalar));

    // 4. Test the += operation with scalar on test_vec
    test_vec += scalar;
    ASSERT_EQ(glm::vec2(one_vec_) + glm::vec2(scalar, scalar), glm::vec2(test_vec));  // Ensure correct scalar addition

    // 5. Chain operations: test_vec + xy_vec_ + scalar
    vne::math::Vec2f chained_vec = test_vec + xy_vec_ + scalar;
    ASSERT_EQ(glm::vec2(test_vec) + glm::vec2(xy_vec_) + glm::vec2(scalar, scalar), glm::vec2(chained_vec));

    // 6. Chain operations with random vector
    vne::math::Vec2f final_vec = test_vec + xy_vec_ + scalar + rand_xy_vec__;
    ASSERT_EQ(glm::vec2(test_vec) + glm::vec2(xy_vec_) + glm::vec2(scalar, scalar) + glm::vec2(rand_xy_vec__),
              glm::vec2(final_vec));
}

/**
 * Test Vec2f subtraction
 */
TEST_F(Vec2fTest, TestVec2fSubtraction) {
    float scalar = 2.45f;
    vne::math::Vec2f test_vec = zero_vec_;

    // 1. Subtract one_vec_ from neg_xy_vec__
    ASSERT_EQ(glm::vec2(neg_xy_vec__) - glm::vec2(one_vec_), glm::vec2(neg_xy_vec__ - one_vec_));

    // 2. Subtract neg_xy_vec__ from test_vec using -= operator
    test_vec -= neg_xy_vec__;
    ASSERT_EQ(glm::vec2(zero_vec_) - glm::vec2(neg_xy_vec__), glm::vec2(test_vec));

    // 3. Subtract scalar from neg_xy_vec__
    ASSERT_EQ(glm::vec2(neg_xy_vec__) - glm::vec2(scalar, scalar), glm::vec2(neg_xy_vec__ - scalar));

    // 4. Subtract scalar from test_vec using -= operator
    test_vec -= scalar;
    ASSERT_EQ(glm::vec2(zero_vec_) - glm::vec2(neg_xy_vec__) - glm::vec2(scalar, scalar), glm::vec2(test_vec));

    // 5. Subtract xy_vec_ and add scalar to test_vec
    ASSERT_EQ(glm::vec2(test_vec) - glm::vec2(xy_vec_) + glm::vec2(scalar, scalar),
              glm::vec2(test_vec - xy_vec_ + scalar));
}

/**
 * Test Vec2f multiplication
 */
TEST_F(Vec2fTest, TestVec2fMultiplication) {
    float scalar = 0.000045f;
    vne::math::Vec2f test_vec = one_vec_;

    // 1. Multiply xy_vec_ by test_vec
    ASSERT_EQ(glm::vec2(xy_vec_) * glm::vec2(test_vec), glm::vec2(xy_vec_ * test_vec));

    // 2. Multiply test_vec by xy_vec_ using *= operator
    test_vec *= xy_vec_;
    ASSERT_EQ(glm::vec2(one_vec_) * glm::vec2(xy_vec_), glm::vec2(test_vec));

    // 3. Multiply test_vec by scalar
    ASSERT_EQ(glm::vec2(test_vec) * glm::vec2(scalar, scalar), glm::vec2(test_vec * scalar));

    // 4. Multiply test_vec by scalar using *= operator
    test_vec *= scalar;
    ASSERT_EQ(glm::vec2(one_vec_) * glm::vec2(xy_vec_) * glm::vec2(scalar, scalar), glm::vec2(test_vec));
}

/**
 * Test Vec2f division
 */
TEST_F(Vec2fTest, TestVec2fDivision) {
    float scalar = 45.345f;
    vne::math::Vec2f test_vec = one_vec_;

    // 1. Divide xy_vec_ by test_vec
    ASSERT_EQ(glm::vec2(xy_vec_) / glm::vec2(test_vec), glm::vec2(xy_vec_ / test_vec));

    // 2. Divide test_vec by xy_vec_ using /= operator
    test_vec /= xy_vec_;
    ASSERT_EQ(glm::vec2(one_vec_) / glm::vec2(xy_vec_), glm::vec2(test_vec));

    // 3. Divide test_vec by scalar
    ASSERT_EQ(glm::vec2(test_vec) / glm::vec2(scalar, scalar), glm::vec2(test_vec / scalar));

    // 4. Divide test_vec by scalar using /= operator
    test_vec /= scalar;
    ASSERT_EQ(glm::vec2(one_vec_) / glm::vec2(xy_vec_) / glm::vec2(scalar, scalar), glm::vec2(test_vec));
}

/**
 * Test Vec2f comparison
 */
TEST_F(Vec2fTest, TestVec2fComparison) {
    vne::math::Vec2f test_vec_equal = xy_vec_;
    vne::math::Vec2f test_vec_less = xy_vec_ - 2.0f;
    vne::math::Vec2f test_vec_greater = xy_vec_ + 2.0f;
    ASSERT_TRUE(xy_vec_ > test_vec_less);
    ASSERT_TRUE(xy_vec_ < test_vec_greater);
    ASSERT_TRUE(xy_vec_ == test_vec_equal);
    ASSERT_TRUE(xy_vec_ != test_vec_less);
    ASSERT_TRUE(xy_vec_ != test_vec_greater);
}

/**
 * Test Vec2f assignment
 */
TEST_F(Vec2fTest, TestVec2fAssignment) {
    vne::math::Vec2f test_vec;
    ASSERT_EQ(xy_vec_, test_vec = xy_vec_);
}

/**
 * Test Vec2f specific component
 */
TEST_F(Vec2fTest, TestVec2fComponent) {
    float value;
    ASSERT_EQ(xy_vec_.x, xy_vec_[0]);
    ASSERT_EQ(xy_vec_.y, xy_vec_[1]);
    ASSERT_EQ(xy_vec_.y, value = xy_vec_[1]);
#ifdef _DEBUG
    ASSERT_DEATH(xy_vec_[2], ".*");
#endif  // _DEBUG
}
/**
 * Test Vec2f inverted vector
 */
TEST_F(Vec2fTest, TestVec2fInverted) {
    ASSERT_EQ(-glm::vec2(xy_vec_), -xy_vec_);
}

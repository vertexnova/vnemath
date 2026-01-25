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

// Testing framework
#include <gtest/gtest.h>

// Project headers
#include "vertexnova/math/math_utils.h"
#include "vertexnova/math/vec3f.h"

using namespace vne;

class Vec3fTest : public ::testing::Test {
    // Interface of test fixture base class
   protected:
    void SetUp() override {
        neg_xyz_vec__ = vne::math::Vec3f(-2.0f, 14.5f, -6.75f);
        zero_vec_ = vne::math::Vec3f();
        one_vec_ = vne::math::Vec3f(1.0f);
        xyz_vec_ = vne::math::Vec3f(2.0f, 2.5f, 4.0f);
        x_axis_ = vne::math::Vec3f(1.0f, 0.0f, 0.0f);
        y_axis_ = vne::math::Vec3f(0.0f, 1.0f, 0.0f);
        z_axis_ = vne::math::Vec3f(0.0f, 0.0f, 1.0f);
        equal_vec_ = vne::math::Vec3f(567.345f);
        rand_xyz_vec__ = vne::math::Vec3f(0.000034f, 0.000057f, 0.875f);

        x_point_ = vne::math::Vec3f(1.0f, 0.0f, 0.0f);
        y_point = vne::math::Vec3f(0.0f, 1.0f, 0.0f);
        z_point = vne::math::Vec3f(0.0f, 0.0f, 1.0f);
        xyz_point = vne::math::Vec3f(3.5f, 1.0f, 1.5f);
    }

    void TearDown() override {}

   protected:
    vne::math::Vec3f zero_vec_;
    vne::math::Vec3f one_vec_;
    vne::math::Vec3f xyz_vec_;
    vne::math::Vec3f x_axis_;
    vne::math::Vec3f y_axis_;
    vne::math::Vec3f z_axis_;
    vne::math::Vec3f equal_vec_;
    vne::math::Vec3f neg_xyz_vec__;
    vne::math::Vec3f rand_xyz_vec__;
    vne::math::Vec3f x_point_;
    vne::math::Vec3f y_point;
    vne::math::Vec3f z_point;
    vne::math::Vec3f xyz_point;
};

/**
 * Test Vec3f dimensions
 *
 * vne::math::Vec3f::dim()
 * vne::math::Vec3f::size()
 *
 */
TEST_F(Vec3fTest, TestVec3fDimensions) {
    ASSERT_EQ(3, vne::math::Vec3f::dim());
    ASSERT_EQ(3, vne::math::Vec3f::size());
    ASSERT_NE(4, vne::math::Vec3f::dim());
    ASSERT_NE(9, vne::math::Vec3f::size());
}

/**
 * Test Vec3f zero vector
 *
 * vne::math::Vec3f::zero()
 *
 */
TEST_F(Vec3fTest, TestVec3fZero) {
    ASSERT_EQ(glm::vec3(0.0f, 0.0f, 0.0f), zero_vec_);
    ASSERT_EQ(zero_vec_, vne::math::Vec3f::zero());
}

/**
 * Test Vec3f one vector
 *
 * vne::math::Vec3f::one()
 *
 */
TEST_F(Vec3fTest, TestVec3fOne) {
    ASSERT_EQ(glm::vec3(1.0f, 1.0f, 1.0f), one_vec_);
    ASSERT_EQ(one_vec_, vne::math::Vec3f::one());
}

/**
 * Test Vec3f x-axis
 *
 * vne::math::Vec3f::xAxis()
 *
 */
TEST_F(Vec3fTest, TestVec3fXAxis) {
    ASSERT_EQ(glm::vec3(1.0f, 0.0f, 0.0f), x_axis_);
    ASSERT_EQ(x_axis_, vne::math::Vec3f::xAxis());
}

/**
 * Test Vec3f y-axis
 *
 * vne::math::Vec3f::yAxis()
 *
 */
TEST_F(Vec3fTest, TestVec3fYAxis) {
    ASSERT_EQ(glm::vec3(0.0f, 1.0f, 0.0f), y_axis_);
    ASSERT_EQ(y_axis_, vne::math::Vec3f::yAxis());
}

/**
 * Test Vec3f z-axis
 *
 * vne::math::Vec3f::zAxis()
 *
 */
TEST_F(Vec3fTest, TestVec3fZAxis) {
    ASSERT_EQ(glm::vec3(0.0f, 0.0f, 1.0f), z_axis_);
    ASSERT_EQ(z_axis_, vne::math::Vec3f::zAxis());
}

/**
 * Test Vec3f up direction
 *
 * vne::math::Vec3f::up()
 *
 */
TEST_F(Vec3fTest, TestVec3fUp) {
    ASSERT_EQ(glm::vec3(0.0f, 1.0f, 0.0f), vne::math::Vec3f::up());
}

/**
 * Test Vec3f down direction
 *
 * vne::math::Vec3f::down()
 *
 */
TEST_F(Vec3fTest, TestVec3fDown) {
    ASSERT_EQ(glm::vec3(0.0f, -1.0f, 0.0f), vne::math::Vec3f::down());
}

/**
 * Test Vec3f left direction
 *
 * vne::math::Vec3f::left()
 *
 */
TEST_F(Vec3fTest, TestVec3fLeft) {
    ASSERT_EQ(glm::vec3(-1.0f, 0.0f, 0.0f), vne::math::Vec3f::left());
}

/**
 * Test Vec3f right direction
 *
 * vne::math::Vec3f::right()
 *
 */
TEST_F(Vec3fTest, TestVec3fRight) {
    ASSERT_EQ(glm::vec3(1.0f, 0.0f, 0.0f), vne::math::Vec3f::right());
}

/**
 * Test Vec3f forward direction
 *
 * vne::math::Vec3f::forward()
 *
 */
TEST_F(Vec3fTest, TestVec3fForward) {
    ASSERT_EQ(glm::vec3(0.0f, 0.0f, 1.0f), vne::math::Vec3f::forward());
}

/**
 * Test Vec3f backward direction
 *
 * vne::math::Vec3f::backward()
 *
 */
TEST_F(Vec3fTest, TestVec3fBackward) {
    ASSERT_EQ(glm::vec3(0.0f, 0.0f, -1.0f), vne::math::Vec3f::backward());
}

/**
 * Test Vec3f GetPtr
 *
 * vec.getPtr()
 *
 */
TEST_F(Vec3fTest, TestVec3fGetPtr) {
    ASSERT_EQ(xyz_vec_.x, *(xyz_vec_.getPtr()));
    ASSERT_EQ(xyz_vec_.y, *(xyz_vec_.getPtr() + 1));
    ASSERT_EQ(xyz_vec_.z, *(xyz_vec_.getPtr() + 2));
    ASSERT_EQ(x_axis_.x, *(x_axis_.getPtr()));
    ASSERT_EQ(x_axis_.y, *(x_axis_.getPtr() + 1));
    ASSERT_EQ(x_axis_.z, *(x_axis_.getPtr() + 2));
}

/**
 * Test Vec3f XY
 *
 * vec.xy()
 *
 */
TEST_F(Vec3fTest, TestVec3fXY) {
    ASSERT_EQ(vne::math::Vec2f(xyz_vec_.x, xyz_vec_.y), xyz_vec_.xy());
}

/**
 * Test coping the 2d vector into 3d vector
 *
 */
TEST_F(Vec3fTest, TestVec3fCopy2dVec) {
    vne::math::Vec3f vec_3d;
    vne::math::Vec2f vec_2d = xyz_vec_.xy();

    vec_3d = vec_2d;
    ASSERT_EQ(vne::math::Vec3f(xyz_vec_.x, xyz_vec_.y, 0.0f), vec_3d);

    vec_3d = vne::math::Vec3f(vec_3d, 5.0f);
    ASSERT_EQ(vne::math::Vec3f(xyz_vec_.x, xyz_vec_.y, 5.0f), vec_3d);

    vec_3d = glm::vec2(1.0f, 2.0f);
    ASSERT_EQ(vne::math::Vec3f(1.0f, 2.0f, 0.0f), vec_3d);

    vec_3d = vne::math::Vec3f(glm::vec2(1.0f, 2.0f), 3.0f);
    ASSERT_EQ(vne::math::Vec3f(1.0f, 2.0f, 3.0f), vec_3d);
}

/**
 * Test Vec3f Abs
 *
 * vec.abs()
 *
 */
TEST_F(Vec3fTest, TestVec3fAbs) {
    ASSERT_EQ(glm::abs(glm::vec3(neg_xyz_vec__)), neg_xyz_vec__.abs());
}

/**
 * Test Vec3f Length and LengthSquare
 */
TEST_F(Vec3fTest, TestVec3fLength) {
    ASSERT_EQ(glm::length(glm::vec3(0.0f)), zero_vec_.length());
    ASSERT_EQ(glm::length(glm::vec3(1.0f)), one_vec_.length());
    ASSERT_EQ(glm::length(glm::vec3(0.0f)), zero_vec_.lengthSquare());
    ASSERT_EQ(glm::length2(glm::vec3(1.0f)), one_vec_.lengthSquare());
    ASSERT_EQ(glm::length2(glm::vec3(xyz_vec_)), xyz_vec_.lengthSquare());
}

/**
 * Test Vec3f Normalize
 *
 * vec.normalize()
 *
 */
TEST_F(Vec3fTest, TestVec3fNormalize) {
    ASSERT_TRUE(x_axis_ == x_axis_.normalize());
    ASSERT_TRUE(y_axis_ == y_axis_.normalize());
    ASSERT_TRUE(x_axis_ == vne::math::Vec3f::normalized(x_axis_));
    ASSERT_TRUE(y_axis_ == vne::math::Vec3f::normalized(y_axis_));
    ASSERT_EQ(glm::normalize(glm::vec3(xyz_vec_)), xyz_vec_.normalize());
}

/**
 * Test Vec3f Min(...)
 *
 * vec1.min(vec2)
 *
 */
TEST_F(Vec3fTest, TestVec3fMin) {
    ASSERT_TRUE(zero_vec_ == one_vec_.min(zero_vec_));
    ASSERT_TRUE(xyz_vec_ == neg_xyz_vec__.min(xyz_vec_));
}

/**
 * Test Vec3f Max(...)
 *
 * vec1.max(vec2)
 *
 */
TEST_F(Vec3fTest, TestVec3fMax) {
    ASSERT_TRUE(one_vec_ == one_vec_.max(zero_vec_));
    ASSERT_TRUE(neg_xyz_vec__ == neg_xyz_vec__.max(xyz_vec_));
}

/**
 * Test Vec3f MinComponent(...)
 *
 * vec.minComponent()
 *
 */
TEST_F(Vec3fTest, TestVec3fMinComponent) {
    ASSERT_TRUE(neg_xyz_vec__.z == neg_xyz_vec__.minComponent());
}

/**
 * Test Vec3f MaxComponent(...)
 *
 * vec.maxComponent()
 *
 */
TEST_F(Vec3fTest, TestVec3fMaxComponent) {
    ASSERT_TRUE(neg_xyz_vec__.y == neg_xyz_vec__.maxComponent());
}

/**
 * Test Vec3f Dot(...)
 *
 * dot = vec1.dot(vec2)
 * dot = vne::math::Vec3f::dot(vec1, vec2)
 *
 */
TEST_F(Vec3fTest, TestVec3fDot) {
    ASSERT_EQ(0.0f, x_axis_.dot(y_axis_));
    ASSERT_EQ(2.0f, xyz_vec_.dot(x_axis_));
    ASSERT_EQ(2.5f, xyz_vec_.dot(y_axis_));
    ASSERT_EQ(4.0f, xyz_vec_.dot(z_axis_));
    ASSERT_EQ(8.5f, xyz_vec_.dot(one_vec_));
    ASSERT_EQ(8.5f, vne::math::Vec3f::dot(xyz_vec_, one_vec_));
    ASSERT_FLOAT_EQ(vne::math::halfPi<float>(),
                    vne::math::acos(x_axis_.dot(y_axis_) / (x_axis_.length() * y_axis_.length())));
}

/**
 * Test Vec3f Cross product.
 *
 * cross = vec1.cross(vec2)
 * cross = vne::math::Vec3f::cross(vec1, vec2)
 *
 */
TEST_F(Vec3fTest, TestVec3fCross) {
    ASSERT_EQ(z_axis_, x_axis_.cross(y_axis_));
    ASSERT_EQ(z_axis_, vne::math::Vec3f::cross(x_axis_, y_axis_));
    ASSERT_EQ(glm::cross(x_axis_, y_axis_), vne::math::Vec3f::cross(x_axis_, y_axis_));

    vne::math::Vec3f test_vec{3.5f, 1.0f, 1.5f};
    ASSERT_EQ(vne::math::Vec3f(-0.25f, 11.0f, -6.75f), vne::math::Vec3f::cross(xyz_vec_, test_vec));
}

/**
 * Test Vec3f Distance calculation.
 *
 * dist = vec1.distance(vec2)
 * dist = vne::math::Vec3f::distance(vec1, vec2)
 *
 */
TEST_F(Vec3fTest, TestVec3fDistance) {
    ASSERT_FLOAT_EQ(static_cast<float>(vne::math::kSqrtTwoDouble), vne::math::Vec3f::distance(x_point_, y_point));
    ASSERT_FLOAT_EQ(3.9370039f, vne::math::Vec3f::distance(vne::math::Vec3f::zero(), xyz_point));
    ASSERT_FLOAT_EQ(3.082207f, vne::math::Vec3f::distance(x_point_, xyz_point));
    ASSERT_FLOAT_EQ(3.8078866f, xyz_point.distance(y_point));
}

/**
 * Test Vec3f Rotate function.
 *
 * vec.rotate(axis, angle)
 *
 */
TEST_F(Vec3fTest, TestVec3fRotate) {
    vne::math::Vec3f test_vec{1.0f};
    ASSERT_TRUE(vne::math::Vec3f(1.0f, -1.0f, 1.0f).areSame(test_vec.rotate(z_axis_, -vne::math::kHalfPi)));
    ASSERT_TRUE(vne::math::Vec3f(-1.0f, 1.0f, 1.0f).areSame(test_vec.rotate(z_axis_, vne::math::kHalfPi)));
    ASSERT_TRUE(vne::math::Vec3f(1.41421f, 1.0f, 0.0f)
                    .areSame(test_vec.rotate(y_axis_, vne::math::kQuarterPi), 1E-5f));
}

/**
 * Test Vec3f Reflect(...)
 *
 * vec.reflect(normal)
 *
 */
TEST_F(Vec3fTest, TestVec3fReflect) {
    vne::math::Vec3f test_vec;
    test_vec.x = -xyz_vec_.x;
    test_vec.y = xyz_vec_.y;
    test_vec.z = -xyz_vec_.z;
    ASSERT_TRUE(test_vec.areSame(-xyz_vec_.reflect(y_axis_)));
}

/**
 * Test Vec3f Refract(...)
 *
 * vec.refract(normal, mu)
 *
 */
TEST_F(Vec3fTest, TestVec3fRefract) {
    xyz_vec_.normalize();
    vne::math::Vec3f test_vec;
    test_vec.x = -xyz_vec_.x;
    test_vec.y = xyz_vec_.y;
    test_vec.z = -xyz_vec_.z;
    ASSERT_TRUE(test_vec.areSame(-xyz_vec_.refract(y_axis_, 1.0f)));
    ASSERT_TRUE(y_axis_.areSame(-xyz_vec_.refract(y_axis_, 0.0f)));
    vne::math::Vec3f out_vec{-0.19518f, 0.899735f, -0.39036f};
    vne::math::Vec3f direction = vne::math::Vec3f::normalized(xyz_vec_);
    ASSERT_TRUE(out_vec.areSame(-direction.refract(y_axis_, 0.5f), 1E-5f));
}

/**
 * Test Vec3f Project(...)
 *
 * vec1.project(vec2)
 *
 */
TEST_F(Vec3fTest, TestVec3fProject) {
    ASSERT_EQ(zero_vec_, x_axis_.project(y_axis_));  // perpendicular vectors
    ASSERT_EQ(vne::math::Vec3f(0.0f, xyz_vec_.y, 0.0f), xyz_vec_.project(y_axis_));
    // Second vector could be any vector ( normal is not compulsory )
    ASSERT_EQ(vne::math::Vec3f(0, xyz_vec_.y, 0.0f), xyz_vec_.project(vne::math::Vec3f(0.0f, 3.0f, 0.0f)));
    // Perpendicular vector of xyz_vec_ w.r.t. y_axis_
    ASSERT_EQ(vne::math::Vec3f(xyz_vec_.x, 0.0f, xyz_vec_.z), xyz_vec_ - xyz_vec_.project(y_axis_));
}

/**
 * Test Vec3f Reject(...)
 *
 * vec1.reject(vec2)
 *
 */
TEST_F(Vec3fTest, TestVec3fReject) {
    // Perpendicular vector of xyz_vec_ w.r.t. y_axis_
    ASSERT_EQ(vne::math::Vec3f(xyz_vec_.x, 0.0f, xyz_vec_.z), xyz_vec_ - xyz_vec_.project(y_axis_));
    ASSERT_EQ(vne::math::Vec3f(xyz_vec_.x, 0.0f, xyz_vec_.z), xyz_vec_.reject(y_axis_));
}

/**
 * Test Vec3f DecomposeVec(...)
 *
 * p.decomposeVec(q, proj, perp)
 *
 */
TEST_F(Vec3fTest, TestVec3fDecomposeVec) {
    vne::math::Vec3f proj;
    vne::math::Vec3f perp;
    xyz_vec_.decomposeVec(y_axis_, proj, perp);
    ASSERT_EQ(vne::math::Vec3f(0, xyz_vec_.y, 0.0f), proj);
    ASSERT_EQ(vne::math::Vec3f(xyz_vec_.x, 0.0f, xyz_vec_.z), perp);
}

/**
 * Test Vec3f Perpendicular(...)
 *
 * p.perpendicular()
 *
 */
TEST_F(Vec3fTest, TestVec3fPerpendicular) {
    ASSERT_EQ(z_axis_, x_axis_.perpendicular(y_axis_));
    ASSERT_EQ(x_axis_, y_axis_.perpendicular(z_axis_));
    ASSERT_EQ(y_axis_, z_axis_.perpendicular(x_axis_));
    ASSERT_EQ(-y_axis_, x_axis_.perpendicular(z_axis_));
    ASSERT_EQ(zero_vec_, x_axis_.perpendicular(zero_vec_));
}

/**
 * Test Vec3f AreSame(...)
 *
 * vec1.areSame(vec2, eps)
 *
 */
TEST_F(Vec3fTest, TestVec3fAreSame) {
    ASSERT_TRUE(rand_xyz_vec__.areSame(vne::math::Vec3f(0.000034001f, 0.00005705f, 0.8750001f), 1E-5f));
    ASSERT_FALSE(rand_xyz_vec__.areSame(vne::math::Vec3f(0.000035f, 0.000056f, 0.874f)));
    ASSERT_FALSE(equal_vec_.areSame(vne::math::Vec3f(567.3453f)));
    ASSERT_TRUE(equal_vec_.areSame(vne::math::Vec3f(567.34503f)));
    ASSERT_TRUE(equal_vec_.areSame(vne::math::Vec3f(567.3453f), 1E-3f));
}

/**
 * Test Vec3f AreAligned(...)
 *
 * vec1.areAligned(vec2, eps)
 *
 */
TEST_F(Vec3fTest, TestVec3fAreAligned) {
    ASSERT_FALSE(vne::math::Vec3f(1.0f).areSame(vne::math::Vec3f(2.0f)));
    ASSERT_TRUE(vne::math::Vec3f(1.0f).areAligned(vne::math::Vec3f(2.0f)));
    ASSERT_FALSE(vne::math::Vec3f(1.0f).areAligned(vne::math::Vec3f(2.05f, 2.0f, 2.0f)));
    ASSERT_TRUE(vne::math::Vec3f(1.0f).areAligned(vne::math::Vec3f(2.05f, 2.0499999f, 2.0499999f), 1E-4f));
}

/**
 * Test Vec3f IsZero(...)
 *
 * vec1.isZero(eps)
 *
 */
TEST_F(Vec3fTest, TestVec3fIsZero) {
    ASSERT_TRUE(zero_vec_.isZero());
    ASSERT_FALSE(rand_xyz_vec__.isZero());
    ASSERT_FALSE(vne::math::Vec3f(1.0f).isZero(1E-5f));
}

/**
 * Test Vec3f IsNormalized(...)
 *
 * vec1.isNormalized(eps)
 *
 */
TEST_F(Vec3fTest, TestVec3fIsNormalized) {
    ASSERT_TRUE(x_axis_.isNormalized());
    ASSERT_TRUE(y_axis_.isNormalized());
    ASSERT_FALSE(xyz_vec_.isNormalized());
    ASSERT_TRUE(vne::math::Vec3f(static_cast<float>(vne::math::kSqrtOneOverThreeDouble)).isNormalized());
}

/**
 * Test Vec3f IsLinearDependent(...)
 *
 * vec1.isLinearDependent(vec2, eps)
 * p1.isLinearDependent(p2, p3, eps)
 *
 */
TEST_F(Vec3fTest, TestVec3fIsLinearDependent) {
    ASSERT_FALSE(x_axis_.isLinearDependent(y_axis_));
    ASSERT_FALSE(x_axis_.isLinearDependent(z_axis_));
    ASSERT_TRUE(vne::math::Vec3f(1.0f).isLinearDependent(vne::math::Vec3f(2.0f)));
    ASSERT_TRUE(vne::math::Vec3f(0.0f).isLinearDependent(vne::math::Vec3f(1.0f), vne::math::Vec3f(2.0f)));
}

/**
 * Test Vec3f ComposeSpherical(...)
 *
 * vec.composeSpherical(rho, theta, phi)
 *
 */
TEST_F(Vec3fTest, TestVec3fComposeSpherical) {
    vne::math::Vec3f test_vec;
    vne::math::Vec3f out_vec{2.0f, static_cast<float>(2.0 * vne::math::kSqrtThreeDouble), static_cast<float>(4.0 * vne::math::kSqrtThreeDouble)};
    ASSERT_TRUE(
        out_vec.areSame(test_vec.composeSpherical(8.0f, vne::math::pi<float>() / 3.0f, vne::math::pi<float>() / 6.0f)));
}

/**
 * Test Vec3f DecomposeSpherical(...)
 *
 * vec.decomposeSpherical(&rho, &theta, &phi)
 *
 */
TEST_F(Vec3fTest, TestVec3fDecomposeSpherical) {
    float rho;
    float theta;
    float phi;
    vne::math::Vec3f rect_vec{2.0f, static_cast<float>(2.0 * vne::math::kSqrtThreeDouble), static_cast<float>(4.0 * vne::math::kSqrtThreeDouble)};
    rect_vec.decomposeSpherical(rho, theta, phi);
    ASSERT_TRUE(vne::math::areSame(8.0f, rho));
    ASSERT_TRUE(vne::math::areSame(vne::math::pi<float>() / 3.0f, theta));
    ASSERT_TRUE(vne::math::areSame(vne::math::pi<float>() / 6.0f, phi));

    rect_vec = vne::math::Vec3f(-1.0f, 1.0f, vne::math::sqrt(6.0f));
    rect_vec.decomposeSpherical(rho, theta, phi);
    ASSERT_TRUE(vne::math::areSame(static_cast<float>(2.0 * vne::math::kSqrtTwoDouble), rho));
    ASSERT_TRUE(vne::math::areSame(3.0f * vne::math::quarterPi<float>(), theta));
    ASSERT_TRUE(vne::math::areSame(vne::math::pi<float>() / 6.0f, phi));
}

/**
 * Test Vec3f ComposeCylindrical(...)
 *
 * vec.composeCylindrical(r, theta, z)
 *
 */
TEST_F(Vec3fTest, TestVec3fComposeCylindrical) {
    vne::math::Vec3f test_vec;
    vne::math::Vec3f out_vec{-2.0f, static_cast<float>(2.0 * vne::math::kSqrtThreeDouble), -2.0f};
    ASSERT_TRUE(out_vec.areSame(test_vec.composeCylindrical(4.0f, vne::math::twoPi<float>() / 3.0f, -2.0f)));
}

/**
 * Test Vec3f DecomposeCylindrical(...)
 *
 * vec.decomposeCylindrical(&r, &theta, &z)
 *
 */
TEST_F(Vec3fTest, TestVec3fDecomposeCylindrical) {
    float r;
    float theta;
    float z;
    vne::math::Vec3f rect_vec{2.5f * static_cast<float>(vne::math::kSqrtThreeDouble), 2.5f, 4.0f};
    rect_vec.decomposeCylindrical(r, theta, z);
    ASSERT_TRUE(vne::math::areSame(5.0f, r));
    ASSERT_TRUE(vne::math::areSame(vne::math::pi<float>() / 6.0f, theta));
    ASSERT_TRUE(vne::math::areSame(4.0f, z));

    rect_vec = vne::math::Vec3f(1.0f, -3.0f, 5.0f);
    rect_vec.decomposeCylindrical(r, theta, z);
    ASSERT_TRUE(vne::math::areSame(vne::math::sqrt(10.0f), r));
    ASSERT_TRUE(vne::math::areSame(5.03414f, theta));
    ASSERT_TRUE(vne::math::areSame(5.0f, z));
}

/**
 * Test Vec3f Angle(...)
 *
 * vec1.angle(vec2)
 * p1.angle(p2, p3)
 *
 */
TEST_F(Vec3fTest, TestVec3fAngle) {
    ASSERT_TRUE(vne::math::areSame(vne::math::halfPi<float>(), x_axis_.angle(y_axis_)));

    ASSERT_TRUE(vne::math::areSame(54.7356071f, vne::math::radToDeg(x_axis_.angle(one_vec_))));

    ASSERT_TRUE(vne::math::areSame(vne::math::pi<float>() / 6.0f,
                                   vne::math::Vec3f(static_cast<float>(vne::math::kSqrtThreeDouble), 1.0f, 0.0f)
                                       .angle(vne::math::Vec3f(1.0f, static_cast<float>(vne::math::kSqrtThreeDouble), 0.0f))));

    ASSERT_TRUE(vne::math::areSame(vne::math::twoPi<float>() / 3.0f,
                                   vne::math::Vec3f(static_cast<float>(vne::math::kSqrtThreeDouble), 1.0f, 0.0f)
                                       .angle(vne::math::Vec3f(-static_cast<float>(vne::math::kSqrtThreeDouble), 1.0f, 0.0f))));

    ASSERT_TRUE(vne::math::areSame(
        64.4724f,
        vne::math::radToDeg(vne::math::Vec3f(4.0f, 0.0f, 7.0f).angle(vne::math::Vec3f(-2.0f, 1.0f, 3.0f))),
        1E-4f));
    ASSERT_TRUE(vne::math::areSame(
        135.608f,
        vne::math::radToDeg((vne::math::Vec3f(3.0f, 4.0f, -7.0f).angle(vne::math::Vec3f(-2.0f, 1.0f, 3.0f)))),
        1E-4f));

    ASSERT_TRUE(vne::math::areSame(
        160.582f,
        vne::math::radToDeg(
            (vne::math::Vec3f(0.0f).angle(vne::math::Vec3f(2.0f, 5.0f, 4.0f), vne::math::Vec3f(-2.0f, -3.0f, -5.0f)))),
        1E-4f));
}

/**
 * Test Vec3f MidPoint(...)
 *
 * vne::math::Vec3f::midPoint(vec1, vec2)
 * vec1.midPoint(vec2)
 *
 */
TEST_F(Vec3fTest, TestVec3fMidPoint) {
    ASSERT_EQ(vne::math::Vec3f(0.5f, 0.5f, 0.0f), vne::math::Vec3f::midPoint(x_axis_, y_axis_));
    ASSERT_EQ(vne::math::Vec3f(0.5f, 0.5f, 0.0f), x_axis_.midPoint(y_axis_));
}

/**
 * Test Vec3f Lerp(...)
 *
 * vne::math::Vec3f::lerp(vec1, vec2, t)
 * vec1.lerp(vec2, t)
 *
 */
TEST_F(Vec3fTest, TestVec3fLerp) {
    ASSERT_EQ(vne::math::Vec3f(0.5f, 0.5f, 0.0f), vne::math::Vec3f::lerp(x_axis_, y_axis_, 0.5f));
    ASSERT_EQ(x_axis_, vne::math::Vec3f::lerp(x_axis_, y_axis_, 0.0f));
    ASSERT_EQ(y_axis_, vne::math::Vec3f::lerp(x_axis_, y_axis_, 1.0f));
    ASSERT_EQ(y_axis_, x_axis_.lerp(y_axis_, 1.0f));
}
/**
 * Test Vec3f addition
 *
 */
TEST_F(Vec3fTest, TestVec3fAddition) {
    float scalar = 2.0f;
    vne::math::Vec3f test_vec = zero_vec_;

    // 1. Test vector addition
    ASSERT_EQ(glm::vec3(zero_vec_) + glm::vec3(one_vec_), glm::vec3(zero_vec_ + one_vec_));

    // 2. Test += operator with a vector
    test_vec += one_vec_;
    ASSERT_EQ(glm::vec3(zero_vec_) + glm::vec3(1.0f), glm::vec3(test_vec));

    // 3. Test vector-scalar addition
    ASSERT_EQ(glm::vec3(neg_xyz_vec__) + glm::vec3(scalar), glm::vec3(neg_xyz_vec__ + scalar));

    // 4. Test += operator with a scalar
    test_vec += scalar;
    ASSERT_EQ(glm::vec3(zero_vec_ + one_vec_) + glm::vec3(scalar), glm::vec3(test_vec));

    // 5. Test chain addition of vector and scalar
    ASSERT_EQ(glm::vec3(test_vec) + glm::vec3(xyz_vec_) + glm::vec3(scalar), glm::vec3(test_vec + xyz_vec_ + scalar));

    // 6. Test chain addition with a random vector
    ASSERT_EQ(glm::vec3(test_vec) + glm::vec3(xyz_vec_) + glm::vec3(scalar) + glm::vec3(rand_xyz_vec__),
              glm::vec3(test_vec + xyz_vec_ + scalar + rand_xyz_vec__));
}

/**
 * Test Vec3f subtraction
 */
TEST_F(Vec3fTest, TestVec3fSubtraction) {
    float scalar = 2.45f;
    vne::math::Vec3f test_vec = zero_vec_;

    // 1. Test vector subtraction
    ASSERT_EQ(glm::vec3(neg_xyz_vec__) - glm::vec3(one_vec_), glm::vec3(neg_xyz_vec__ - one_vec_));

    // 2. Test -= operator with a vector
    test_vec -= neg_xyz_vec__;
    ASSERT_EQ(glm::vec3(zero_vec_) - glm::vec3(neg_xyz_vec__), glm::vec3(test_vec));

    // 3. Test vector-scalar subtraction
    ASSERT_EQ(glm::vec3(neg_xyz_vec__) - glm::vec3(scalar), glm::vec3(neg_xyz_vec__ - scalar));

    // 4. Test -= operator with a scalar
    test_vec -= scalar;
    ASSERT_EQ(glm::vec3(zero_vec_ - neg_xyz_vec__) - glm::vec3(scalar), glm::vec3(test_vec));

    // 5. Test chain subtraction of vector and scalar
    ASSERT_EQ(glm::vec3(test_vec) - glm::vec3(xyz_vec_) + glm::vec3(scalar), glm::vec3(test_vec - xyz_vec_ + scalar));
}

/**
 * Test Vec3f multiplication
 */
TEST_F(Vec3fTest, TestVec3fMultiplication) {
    float scalar = 0.000045f;
    vne::math::Vec3f test_vec = one_vec_;

    // 1. Test vector multiplication
    ASSERT_EQ(glm::vec3(xyz_vec_) * glm::vec3(test_vec), glm::vec3(xyz_vec_ * test_vec));

    // 2. Test *= operator with a vector
    test_vec *= xyz_vec_;
    ASSERT_EQ(glm::vec3(one_vec_ * xyz_vec_), glm::vec3(test_vec));

    // 3. Test vector-scalar multiplication
    ASSERT_EQ(glm::vec3(test_vec) * scalar, glm::vec3(test_vec * scalar));

    // 4. Test *= operator with a scalar
    test_vec *= scalar;
    ASSERT_EQ(glm::vec3(one_vec_ * xyz_vec_ * scalar), glm::vec3(test_vec));
}

/**
 * Test Vec3f division
 */
TEST_F(Vec3fTest, TestVec3fDivision) {
    float scalar = 45.345f;
    vne::math::Vec3f test_vec = one_vec_;

    // 1. Test vector division
    ASSERT_EQ(glm::vec3(xyz_vec_) / glm::vec3(test_vec), glm::vec3(xyz_vec_ / test_vec));

    // 2. Test /= operator with a vector
    test_vec /= xyz_vec_;
    ASSERT_EQ(glm::vec3(one_vec_ / xyz_vec_), glm::vec3(test_vec));

    // 3. Test vector-scalar division
    ASSERT_EQ(glm::vec3(test_vec) / scalar, glm::vec3(test_vec / scalar));

    // 4. Test /= operator with a scalar
    test_vec /= scalar;
    ASSERT_EQ(glm::vec3(one_vec_ / xyz_vec_ / scalar), glm::vec3(test_vec));
}

/**
 * Test Vec3f comparison
 */
TEST_F(Vec3fTest, TestVec3fComparison) {
    vne::math::Vec3f test_vec_equal = xyz_vec_;
    vne::math::Vec3f test_vec_less = xyz_vec_ - 2.0f;
    vne::math::Vec3f test_vec_greater = xyz_vec_ + 2.0f;
    ASSERT_TRUE(xyz_vec_ > test_vec_less);
    ASSERT_TRUE(xyz_vec_ < test_vec_greater);
    ASSERT_TRUE(xyz_vec_ == test_vec_equal);
    ASSERT_TRUE(xyz_vec_ != test_vec_less);
    ASSERT_TRUE(xyz_vec_ != test_vec_greater);
}

/**
 * Test Vec3f assignment
 */
TEST_F(Vec3fTest, TestVec3fAssignment) {
    vne::math::Vec3f test_vec;
    ASSERT_EQ(xyz_vec_, test_vec = xyz_vec_);
}

/**
 * Test Vec3f specific component
 */
TEST_F(Vec3fTest, TestVec3fComponent) {
    float value;
    ASSERT_EQ(xyz_vec_.x, xyz_vec_[0]);
    ASSERT_EQ(xyz_vec_.y, xyz_vec_[1]);
    ASSERT_EQ(xyz_vec_.z, xyz_vec_[2]);
    ASSERT_EQ(xyz_vec_.y, value = xyz_vec_[1]);
}

/**
 * Test Vec3f inverted vector
 */
TEST_F(Vec3fTest, TestVec3fInverted) {
    ASSERT_EQ(-glm::vec3(xyz_vec_), -xyz_vec_);
}

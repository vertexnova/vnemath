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
#include "vertexnova/math/vec3f.h"

using namespace VNE;

class Vec3fTest_C : public ::testing::Test {
    // Interface of test fixture base class
   protected:
    void SetUp() override {
        neg_xyz_vec = vne::math::Vec3f(-2.0f, 14.5f, -6.75f);
        zero_vec = vne::math::Vec3f();
        one_vec = vne::math::Vec3f(1.0f);
        xyz_vec = vne::math::Vec3f(2.0f, 2.5f, 4.0f);
        x_axis = vne::math::Vec3f(1.0f, 0.0f, 0.0f);
        y_axis = vne::math::Vec3f(0.0f, 1.0f, 0.0f);
        z_axis = vne::math::Vec3f(0.0f, 0.0f, 1.0f);
        equal_vec = vne::math::Vec3f(567.345f);
        rand_xyz_vec = vne::math::Vec3f(0.000034f, 0.000057f, 0.875f);

        x_point = vne::math::Vec3f(1.0f, 0.0f, 0.0f);
        y_point = vne::math::Vec3f(0.0f, 1.0f, 0.0f);
        z_point = vne::math::Vec3f(0.0f, 0.0f, 1.0f);
        xyz_point = vne::math::Vec3f(3.5f, 1.0f, 1.5f);
    }

    void TearDown() override {}

   protected:
    vne::math::Vec3f zero_vec;
    vne::math::Vec3f one_vec;
    vne::math::Vec3f xyz_vec;
    vne::math::Vec3f x_axis;
    vne::math::Vec3f y_axis;
    vne::math::Vec3f z_axis;
    vne::math::Vec3f equal_vec;
    vne::math::Vec3f neg_xyz_vec;
    vne::math::Vec3f rand_xyz_vec;
    vne::math::Vec3f x_point;
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
TEST_F(Vec3fTest_C, TestVec3fDimensions) {
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
TEST_F(Vec3fTest_C, TestVec3fZero) {
    ASSERT_EQ(glm::vec3(0.0f, 0.0f, 0.0f), zero_vec);
    ASSERT_EQ(zero_vec, vne::math::Vec3f::zero());
}

/**
 * Test Vec3f one vector
 *
 * vne::math::Vec3f::one()
 *
 */
TEST_F(Vec3fTest_C, TestVec3fOne) {
    ASSERT_EQ(glm::vec3(1.0f, 1.0f, 1.0f), one_vec);
    ASSERT_EQ(one_vec, vne::math::Vec3f::one());
}

/**
 * Test Vec3f x-axis
 *
 * vne::math::Vec3f::xAxis()
 *
 */
TEST_F(Vec3fTest_C, TestVec3fXAxis) {
    ASSERT_EQ(glm::vec3(1.0f, 0.0f, 0.0f), x_axis);
    ASSERT_EQ(x_axis, vne::math::Vec3f::xAxis());
}

/**
 * Test Vec3f y-axis
 *
 * vne::math::Vec3f::yAxis()
 *
 */
TEST_F(Vec3fTest_C, TestVec3fYAxis) {
    ASSERT_EQ(glm::vec3(0.0f, 1.0f, 0.0f), y_axis);
    ASSERT_EQ(y_axis, vne::math::Vec3f::yAxis());
}

/**
 * Test Vec3f z-axis
 *
 * vne::math::Vec3f::zAxis()
 *
 */
TEST_F(Vec3fTest_C, TestVec3fZAxis) {
    ASSERT_EQ(glm::vec3(0.0f, 0.0f, 1.0f), z_axis);
    ASSERT_EQ(z_axis, vne::math::Vec3f::zAxis());
}

/**
 * Test Vec3f up direction
 *
 * vne::math::Vec3f::up()
 *
 */
TEST_F(Vec3fTest_C, TestVec3fUp) {
    ASSERT_EQ(glm::vec3(0.0f, 1.0f, 0.0f), vne::math::Vec3f::up());
}

/**
 * Test Vec3f down direction
 *
 * vne::math::Vec3f::down()
 *
 */
TEST_F(Vec3fTest_C, TestVec3fDown) {
    ASSERT_EQ(glm::vec3(0.0f, -1.0f, 0.0f), vne::math::Vec3f::down());
}

/**
 * Test Vec3f left direction
 *
 * vne::math::Vec3f::left()
 *
 */
TEST_F(Vec3fTest_C, TestVec3fLeft) {
    ASSERT_EQ(glm::vec3(-1.0f, 0.0f, 0.0f), vne::math::Vec3f::left());
}

/**
 * Test Vec3f right direction
 *
 * vne::math::Vec3f::right()
 *
 */
TEST_F(Vec3fTest_C, TestVec3fRight) {
    ASSERT_EQ(glm::vec3(1.0f, 0.0f, 0.0f), vne::math::Vec3f::right());
}

/**
 * Test Vec3f forward direction
 *
 * vne::math::Vec3f::forward()
 *
 */
TEST_F(Vec3fTest_C, TestVec3fForward) {
    ASSERT_EQ(glm::vec3(0.0f, 0.0f, 1.0f), vne::math::Vec3f::forward());
}

/**
 * Test Vec3f backward direction
 *
 * vne::math::Vec3f::backward()
 *
 */
TEST_F(Vec3fTest_C, TestVec3fBackward) {
    ASSERT_EQ(glm::vec3(0.0f, 0.0f, -1.0f), vne::math::Vec3f::backward());
}

/**
 * Test Vec3f GetPtr
 *
 * vec.getPtr()
 *
 */
TEST_F(Vec3fTest_C, TestVec3fGetPtr) {
    ASSERT_EQ(xyz_vec.x, *(xyz_vec.getPtr()));
    ASSERT_EQ(xyz_vec.y, *(xyz_vec.getPtr() + 1));
    ASSERT_EQ(xyz_vec.z, *(xyz_vec.getPtr() + 2));
    ASSERT_EQ(x_axis.x, *(x_axis.getPtr()));
    ASSERT_EQ(x_axis.y, *(x_axis.getPtr() + 1));
    ASSERT_EQ(x_axis.z, *(x_axis.getPtr() + 2));
}

/**
 * Test Vec3f XY
 *
 * vec.xy()
 *
 */
TEST_F(Vec3fTest_C, TestVec3fXY) {
    ASSERT_EQ(vne::math::Vec2f(xyz_vec.x, xyz_vec.y), xyz_vec.xy());
}

/**
 * Test coping the 2d vector into 3d vector
 *
 */
TEST_F(Vec3fTest_C, TestVec3fCopy2dVec) {
    vne::math::Vec3f vec_3d;
    vne::math::Vec2f vec_2d = xyz_vec.xy();

    vec_3d = vec_2d;
    ASSERT_EQ(vne::math::Vec3f(xyz_vec.x, xyz_vec.y, 0.0f), vec_3d);

    vec_3d = vne::math::Vec3f(vec_3d, 5.0f);
    ASSERT_EQ(vne::math::Vec3f(xyz_vec.x, xyz_vec.y, 5.0f), vec_3d);

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
TEST_F(Vec3fTest_C, TestVec3fAbs) {
    ASSERT_EQ(glm::abs(glm::vec3(neg_xyz_vec)), neg_xyz_vec.abs());
}

/**
 * Test Vec3f Length and LengthSquare
 */
TEST_F(Vec3fTest_C, TestVec3fLength) {
    ASSERT_EQ(glm::length(glm::vec3(0.0f)), zero_vec.length());
    ASSERT_EQ(glm::length(glm::vec3(1.0f)), one_vec.length());
    ASSERT_EQ(glm::length(glm::vec3(0.0f)), zero_vec.lengthSquare());
    ASSERT_EQ(glm::length2(glm::vec3(1.0f)), one_vec.lengthSquare());
    ASSERT_EQ(glm::length2(glm::vec3(xyz_vec)), xyz_vec.lengthSquare());
}

/**
 * Test Vec3f Normalize
 *
 * vec.normalize()
 *
 */
TEST_F(Vec3fTest_C, TestVec3fNormalize) {
    ASSERT_TRUE(x_axis == x_axis.normalize());
    ASSERT_TRUE(y_axis == y_axis.normalize());
    ASSERT_TRUE(x_axis == vne::math::Vec3f::normalized(x_axis));
    ASSERT_TRUE(y_axis == vne::math::Vec3f::normalized(y_axis));
    ASSERT_EQ(glm::normalize(glm::vec3(xyz_vec)), xyz_vec.normalize());
}

/**
 * Test Vec3f Min(...)
 *
 * vec1.min(vec2)
 *
 */
TEST_F(Vec3fTest_C, TestVec3fMin) {
    ASSERT_TRUE(zero_vec == one_vec.min(zero_vec));
    ASSERT_TRUE(xyz_vec == neg_xyz_vec.min(xyz_vec));
}

/**
 * Test Vec3f Max(...)
 *
 * vec1.max(vec2)
 *
 */
TEST_F(Vec3fTest_C, TestVec3fMax) {
    ASSERT_TRUE(one_vec == one_vec.max(zero_vec));
    ASSERT_TRUE(neg_xyz_vec == neg_xyz_vec.max(xyz_vec));
}

/**
 * Test Vec3f MinComponent(...)
 *
 * vec.minComponent()
 *
 */
TEST_F(Vec3fTest_C, TestVec3fMinComponent) {
    ASSERT_TRUE(neg_xyz_vec.z == neg_xyz_vec.minComponent());
}

/**
 * Test Vec3f MaxComponent(...)
 *
 * vec.maxComponent()
 *
 */
TEST_F(Vec3fTest_C, TestVec3fMaxComponent) {
    ASSERT_TRUE(neg_xyz_vec.y == neg_xyz_vec.maxComponent());
}

/**
 * Test Vec3f Dot(...)
 *
 * dot = vec1.dot(vec2)
 * dot = vne::math::Vec3f::dot(vec1, vec2)
 *
 */
TEST_F(Vec3fTest_C, TestVec3fDot) {
    ASSERT_EQ(0.0f, x_axis.dot(y_axis));
    ASSERT_EQ(2.0f, xyz_vec.dot(x_axis));
    ASSERT_EQ(2.5f, xyz_vec.dot(y_axis));
    ASSERT_EQ(4.0f, xyz_vec.dot(z_axis));
    ASSERT_EQ(8.5f, xyz_vec.dot(one_vec));
    ASSERT_EQ(8.5f, vne::math::Vec3f::dot(xyz_vec, one_vec));
    ASSERT_FLOAT_EQ(vne::math::halfPi<float>(), vne::math::acos(x_axis.dot(y_axis) / (x_axis.length() * y_axis.length())));
}

/**
 * Test Vec3f Cross product.
 *
 * cross = vec1.cross(vec2)
 * cross = vne::math::Vec3f::cross(vec1, vec2)
 *
 */
TEST_F(Vec3fTest_C, TestVec3fCross) {
    ASSERT_EQ(z_axis, x_axis.cross(y_axis));
    ASSERT_EQ(z_axis, vne::math::Vec3f::cross(x_axis, y_axis));
    ASSERT_EQ(glm::cross(x_axis, y_axis), vne::math::Vec3f::cross(x_axis, y_axis));

    vne::math::Vec3f test_vec{3.5f, 1.0f, 1.5f};
    ASSERT_EQ(vne::math::Vec3f(-0.25f, 11.0f, -6.75f), vne::math::Vec3f::cross(xyz_vec, test_vec));
}

/**
 * Test Vec3f Distance calculation.
 *
 * dist = vec1.distance(vec2)
 * dist = vne::math::Vec3f::distance(vec1, vec2)
 *
 */
TEST_F(Vec3fTest_C, TestVec3fDistance) {
    ASSERT_FLOAT_EQ(static_cast<float>(SQRT_TWO), vne::math::Vec3f::distance(x_point, y_point));
    ASSERT_FLOAT_EQ(3.9370039f, vne::math::Vec3f::distance(vne::math::Vec3f::zero(), xyz_point));
    ASSERT_FLOAT_EQ(3.082207f, vne::math::Vec3f::distance(x_point, xyz_point));
    ASSERT_FLOAT_EQ(3.8078866f, xyz_point.distance(y_point));
}

/**
 * Test Vec3f Rotate function.
 *
 * vec.rotate(axis, angle)
 *
 */
TEST_F(Vec3fTest_C, TestVec3fRotate) {
    vne::math::Vec3f test_vec{1.0f};
    ASSERT_TRUE(vne::math::Vec3f(1.0f, -1.0f, 1.0f).areSame(test_vec.rotate(z_axis, -static_cast<float>(HALF_PI))));
    ASSERT_TRUE(vne::math::Vec3f(-1.0f, 1.0f, 1.0f).areSame(test_vec.rotate(z_axis, static_cast<float>(HALF_PI))));
    ASSERT_TRUE(vne::math::Vec3f(1.41421f, 1.0f, 0.0f).areSame(test_vec.rotate(y_axis, static_cast<float>(QUARTER_PI)), 1E-5f));
}

/**
 * Test Vec3f Reflect(...)
 *
 * vec.reflect(normal)
 *
 */
TEST_F(Vec3fTest_C, TestVec3fReflect) {
    vne::math::Vec3f test_vec;
    test_vec.x = -xyz_vec.x;
    test_vec.y = xyz_vec.y;
    test_vec.z = -xyz_vec.z;
    ASSERT_TRUE(test_vec.areSame(-xyz_vec.reflect(y_axis)));
}

/**
 * Test Vec3f Refract(...)
 *
 * vec.refract(normal, mu)
 *
 */
TEST_F(Vec3fTest_C, TestVec3fRefract) {
    xyz_vec.normalize();
    vne::math::Vec3f test_vec;
    test_vec.x = -xyz_vec.x;
    test_vec.y = xyz_vec.y;
    test_vec.z = -xyz_vec.z;
    ASSERT_TRUE(test_vec.areSame(-xyz_vec.refract(y_axis, 1.0f)));
    ASSERT_TRUE(y_axis.areSame(-xyz_vec.refract(y_axis, 0.0f)));
    vne::math::Vec3f out_vec{-0.19518f, 0.899735f, -0.39036f};
    vne::math::Vec3f direction = vne::math::Vec3f::normalized(xyz_vec);
    ASSERT_TRUE(out_vec.areSame(-direction.refract(y_axis, 0.5f), 1E-5f));
}

/**
 * Test Vec3f Project(...)
 *
 * vec1.project(vec2)
 *
 */
TEST_F(Vec3fTest_C, TestVec3fProject) {
    ASSERT_EQ(zero_vec, x_axis.project(y_axis));  // perpendicular vectors
    ASSERT_EQ(vne::math::Vec3f(0.0f, xyz_vec.y, 0.0f), xyz_vec.project(y_axis));
    // Second vector could be any vector ( normal is not compulsory )
    ASSERT_EQ(vne::math::Vec3f(0, xyz_vec.y, 0.0f), xyz_vec.project(vne::math::Vec3f(0.0f, 3.0f, 0.0f)));
    // Perpendicular vector of xyz_vec w.r.t. y_axis
    ASSERT_EQ(vne::math::Vec3f(xyz_vec.x, 0.0f, xyz_vec.z), xyz_vec - xyz_vec.project(y_axis));
}

/**
 * Test Vec3f Reject(...)
 *
 * vec1.reject(vec2)
 *
 */
TEST_F(Vec3fTest_C, TestVec3fReject) {
    // Perpendicular vector of xyz_vec w.r.t. y_axis
    ASSERT_EQ(vne::math::Vec3f(xyz_vec.x, 0.0f, xyz_vec.z), xyz_vec - xyz_vec.project(y_axis));
    ASSERT_EQ(vne::math::Vec3f(xyz_vec.x, 0.0f, xyz_vec.z), xyz_vec.reject(y_axis));
}

/**
 * Test Vec3f DecomposeVec(...)
 *
 * p.decomposeVec(q, proj, perp)
 *
 */
TEST_F(Vec3fTest_C, TestVec3fDecomposeVec) {
    vne::math::Vec3f proj;
    vne::math::Vec3f perp;
    xyz_vec.decomposeVec(y_axis, proj, perp);
    ASSERT_EQ(vne::math::Vec3f(0, xyz_vec.y, 0.0f), proj);
    ASSERT_EQ(vne::math::Vec3f(xyz_vec.x, 0.0f, xyz_vec.z), perp);
}

/**
 * Test Vec3f Perpendicular(...)
 *
 * p.perpendicular()
 *
 */
TEST_F(Vec3fTest_C, TestVec3fPerpendicular) {
    ASSERT_EQ(z_axis, x_axis.perpendicular(y_axis));
    ASSERT_EQ(x_axis, y_axis.perpendicular(z_axis));
    ASSERT_EQ(y_axis, z_axis.perpendicular(x_axis));
    ASSERT_EQ(-y_axis, x_axis.perpendicular(z_axis));
    ASSERT_EQ(zero_vec, x_axis.perpendicular(zero_vec));
}

/**
 * Test Vec3f AreSame(...)
 *
 * vec1.areSame(vec2, eps)
 *
 */
TEST_F(Vec3fTest_C, TestVec3fAreSame) {
    ASSERT_TRUE(rand_xyz_vec.areSame(vne::math::Vec3f(0.000034001f, 0.00005705f, 0.8750001f), 1E-5f));
    ASSERT_FALSE(rand_xyz_vec.areSame(vne::math::Vec3f(0.000035f, 0.000056f, 0.874f)));
    ASSERT_FALSE(equal_vec.areSame(vne::math::Vec3f(567.3453f)));
    ASSERT_TRUE(equal_vec.areSame(vne::math::Vec3f(567.34503f)));
    ASSERT_TRUE(equal_vec.areSame(vne::math::Vec3f(567.3453f), 1E-3f));
}

/**
 * Test Vec3f AreAligned(...)
 *
 * vec1.areAligned(vec2, eps)
 *
 */
TEST_F(Vec3fTest_C, TestVec3fAreAligned) {
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
TEST_F(Vec3fTest_C, TestVec3fIsZero) {
    ASSERT_TRUE(zero_vec.isZero());
    ASSERT_FALSE(rand_xyz_vec.isZero());
    ASSERT_FALSE(vne::math::Vec3f(1.0f).isZero(1E-5f));
}

/**
 * Test Vec3f IsNormalized(...)
 *
 * vec1.isNormalized(eps)
 *
 */
TEST_F(Vec3fTest_C, TestVec3fIsNormalized) {
    ASSERT_TRUE(x_axis.isNormalized());
    ASSERT_TRUE(y_axis.isNormalized());
    ASSERT_FALSE(xyz_vec.isNormalized());
    ASSERT_TRUE(vne::math::Vec3f(static_cast<float>(SQRT_ONE_OVER_THREE)).isNormalized());
}

/**
 * Test Vec3f IsLinearDependent(...)
 *
 * vec1.isLinearDependent(vec2, eps)
 * p1.isLinearDependent(p2, p3, eps)
 *
 */
TEST_F(Vec3fTest_C, TestVec3fIsLinearDependent) {
    ASSERT_FALSE(x_axis.isLinearDependent(y_axis));
    ASSERT_FALSE(x_axis.isLinearDependent(z_axis));
    ASSERT_TRUE(vne::math::Vec3f(1.0f).isLinearDependent(vne::math::Vec3f(2.0f)));
    ASSERT_TRUE(vne::math::Vec3f(0.0f).isLinearDependent(vne::math::Vec3f(1.0f), vne::math::Vec3f(2.0f)));
}

/**
 * Test Vec3f ComposeSpherical(...)
 *
 * vec.composeSpherical(rho, theta, phi)
 *
 */
TEST_F(Vec3fTest_C, TestVec3fComposeSpherical) {
    vne::math::Vec3f test_vec;
    vne::math::Vec3f out_vec{2.0f, static_cast<float>(2.0 * SQRT_THREE), static_cast<float>(4.0 * SQRT_THREE)};
    ASSERT_TRUE(out_vec.areSame(test_vec.composeSpherical(8.0f, vne::math::pi<float>() / 3.0f, vne::math::pi<float>() / 6.0f)));
}

/**
 * Test Vec3f DecomposeSpherical(...)
 *
 * vec.decomposeSpherical(&rho, &theta, &phi)
 *
 */
TEST_F(Vec3fTest_C, TestVec3fDecomposeSpherical) {
    float rho;
    float theta;
    float phi;
    vne::math::Vec3f rect_vec{2.0f, static_cast<float>(2.0 * SQRT_THREE), static_cast<float>(4.0 * SQRT_THREE)};
    rect_vec.decomposeSpherical(rho, theta, phi);
    ASSERT_TRUE(vne::math::areSame(8.0f, rho));
    ASSERT_TRUE(vne::math::areSame(vne::math::pi<float>() / 3.0f, theta));
    ASSERT_TRUE(vne::math::areSame(vne::math::pi<float>() / 6.0f, phi));

    rect_vec = vne::math::Vec3f(-1.0f, 1.0f, vne::math::sqrt(6.0f));
    rect_vec.decomposeSpherical(rho, theta, phi);
    ASSERT_TRUE(vne::math::areSame(static_cast<float>(2.0 * SQRT_TWO), rho));
    ASSERT_TRUE(vne::math::areSame(3.0f * vne::math::quarterPi<float>(), theta));
    ASSERT_TRUE(vne::math::areSame(vne::math::pi<float>() / 6.0f, phi));
}

/**
 * Test Vec3f ComposeCylindrical(...)
 *
 * vec.composeCylindrical(r, theta, z)
 *
 */
TEST_F(Vec3fTest_C, TestVec3fComposeCylindrical) {
    vne::math::Vec3f test_vec;
    vne::math::Vec3f out_vec{-2.0f, static_cast<float>(2.0 * SQRT_THREE), -2.0f};
    ASSERT_TRUE(out_vec.areSame(test_vec.composeCylindrical(4.0f, vne::math::twoPi<float>() / 3.0f, -2.0f)));
}

/**
 * Test Vec3f DecomposeCylindrical(...)
 *
 * vec.decomposeCylindrical(&r, &theta, &z)
 *
 */
TEST_F(Vec3fTest_C, TestVec3fDecomposeCylindrical) {
    float r;
    float theta;
    float z;
    vne::math::Vec3f rect_vec{2.5f * static_cast<float>(SQRT_THREE), 2.5f, 4.0f};
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
TEST_F(Vec3fTest_C, TestVec3fAngle) {
    ASSERT_TRUE(vne::math::areSame(vne::math::halfPi<float>(), x_axis.angle(y_axis)));

    ASSERT_TRUE(vne::math::areSame(54.7356071f, vne::math::radToDeg(x_axis.angle(one_vec))));

    ASSERT_TRUE(
        vne::math::areSame(vne::math::pi<float>() / 6.0f,
                      vne::math::Vec3f(static_cast<float>(SQRT_THREE), 1.0f, 0.0f).angle(vne::math::Vec3f(1.0f, static_cast<float>(SQRT_THREE), 0.0f))));

    ASSERT_TRUE(
        vne::math::areSame(vne::math::twoPi<float>() / 3.0f,
                      vne::math::Vec3f(static_cast<float>(SQRT_THREE), 1.0f, 0.0f).angle(vne::math::Vec3f(-static_cast<float>(SQRT_THREE), 1.0f, 0.0f))));

    ASSERT_TRUE(vne::math::areSame(64.4724f, vne::math::radToDeg(vne::math::Vec3f(4.0f, 0.0f, 7.0f).angle(vne::math::Vec3f(-2.0f, 1.0f, 3.0f))), 1E-4f));
    ASSERT_TRUE(vne::math::areSame(135.608f, vne::math::radToDeg((vne::math::Vec3f(3.0f, 4.0f, -7.0f).angle(vne::math::Vec3f(-2.0f, 1.0f, 3.0f)))), 1E-4f));

    ASSERT_TRUE(vne::math::areSame(160.582f,
                              vne::math::radToDeg((vne::math::Vec3f(0.0f).angle(vne::math::Vec3f(2.0f, 5.0f, 4.0f), vne::math::Vec3f(-2.0f, -3.0f, -5.0f)))),
                              1E-4f));
}

/**
 * Test Vec3f MidPoint(...)
 *
 * vne::math::Vec3f::midPoint(vec1, vec2)
 * vec1.midPoint(vec2)
 *
 */
TEST_F(Vec3fTest_C, TestVec3fMidPoint) {
    ASSERT_EQ(vne::math::Vec3f(0.5f, 0.5f, 0.0f), vne::math::Vec3f::midPoint(x_axis, y_axis));
    ASSERT_EQ(vne::math::Vec3f(0.5f, 0.5f, 0.0f), x_axis.midPoint(y_axis));
}

/**
 * Test Vec3f Lerp(...)
 *
 * vne::math::Vec3f::lerp(vec1, vec2, t)
 * vec1.lerp(vec2, t)
 *
 */
TEST_F(Vec3fTest_C, TestVec3fLerp) {
    ASSERT_EQ(vne::math::Vec3f(0.5f, 0.5f, 0.0f), vne::math::Vec3f::lerp(x_axis, y_axis, 0.5f));
    ASSERT_EQ(x_axis, vne::math::Vec3f::lerp(x_axis, y_axis, 0.0f));
    ASSERT_EQ(y_axis, vne::math::Vec3f::lerp(x_axis, y_axis, 1.0f));
    ASSERT_EQ(y_axis, x_axis.lerp(y_axis, 1.0f));
}
/**
 * Test Vec3f addition
 *
 */
TEST_F(Vec3fTest_C, TestVec3fAddition) {
    float scalar = 2.0f;
    vne::math::Vec3f test_vec = zero_vec;

    // 1. Test vector addition
    ASSERT_EQ(glm::vec3(zero_vec) + glm::vec3(one_vec), glm::vec3(zero_vec + one_vec));

    // 2. Test += operator with a vector
    test_vec += one_vec;
    ASSERT_EQ(glm::vec3(zero_vec) + glm::vec3(1.0f), glm::vec3(test_vec));

    // 3. Test vector-scalar addition
    ASSERT_EQ(glm::vec3(neg_xyz_vec) + glm::vec3(scalar), glm::vec3(neg_xyz_vec + scalar));

    // 4. Test += operator with a scalar
    test_vec += scalar;
    ASSERT_EQ(glm::vec3(zero_vec + one_vec) + glm::vec3(scalar), glm::vec3(test_vec));

    // 5. Test chain addition of vector and scalar
    ASSERT_EQ(glm::vec3(test_vec) + glm::vec3(xyz_vec) + glm::vec3(scalar), glm::vec3(test_vec + xyz_vec + scalar));

    // 6. Test chain addition with a random vector
    ASSERT_EQ(glm::vec3(test_vec) + glm::vec3(xyz_vec) + glm::vec3(scalar) + glm::vec3(rand_xyz_vec),
              glm::vec3(test_vec + xyz_vec + scalar + rand_xyz_vec));
}

/**
 * Test Vec3f subtraction
 */
TEST_F(Vec3fTest_C, TestVec3fSubtraction) {
    float scalar = 2.45f;
    vne::math::Vec3f test_vec = zero_vec;

    // 1. Test vector subtraction
    ASSERT_EQ(glm::vec3(neg_xyz_vec) - glm::vec3(one_vec), glm::vec3(neg_xyz_vec - one_vec));

    // 2. Test -= operator with a vector
    test_vec -= neg_xyz_vec;
    ASSERT_EQ(glm::vec3(zero_vec) - glm::vec3(neg_xyz_vec), glm::vec3(test_vec));

    // 3. Test vector-scalar subtraction
    ASSERT_EQ(glm::vec3(neg_xyz_vec) - glm::vec3(scalar), glm::vec3(neg_xyz_vec - scalar));

    // 4. Test -= operator with a scalar
    test_vec -= scalar;
    ASSERT_EQ(glm::vec3(zero_vec - neg_xyz_vec) - glm::vec3(scalar), glm::vec3(test_vec));

    // 5. Test chain subtraction of vector and scalar
    ASSERT_EQ(glm::vec3(test_vec) - glm::vec3(xyz_vec) + glm::vec3(scalar), glm::vec3(test_vec - xyz_vec + scalar));
}

/**
 * Test Vec3f multiplication
 */
TEST_F(Vec3fTest_C, TestVec3fMultiplication) {
    float scalar = 0.000045f;
    vne::math::Vec3f test_vec = one_vec;

    // 1. Test vector multiplication
    ASSERT_EQ(glm::vec3(xyz_vec) * glm::vec3(test_vec), glm::vec3(xyz_vec * test_vec));

    // 2. Test *= operator with a vector
    test_vec *= xyz_vec;
    ASSERT_EQ(glm::vec3(one_vec * xyz_vec), glm::vec3(test_vec));

    // 3. Test vector-scalar multiplication
    ASSERT_EQ(glm::vec3(test_vec) * scalar, glm::vec3(test_vec * scalar));

    // 4. Test *= operator with a scalar
    test_vec *= scalar;
    ASSERT_EQ(glm::vec3(one_vec * xyz_vec * scalar), glm::vec3(test_vec));
}

/**
 * Test Vec3f division
 */
TEST_F(Vec3fTest_C, TestVec3fDivision) {
    float scalar = 45.345f;
    vne::math::Vec3f test_vec = one_vec;

    // 1. Test vector division
    ASSERT_EQ(glm::vec3(xyz_vec) / glm::vec3(test_vec), glm::vec3(xyz_vec / test_vec));

    // 2. Test /= operator with a vector
    test_vec /= xyz_vec;
    ASSERT_EQ(glm::vec3(one_vec / xyz_vec), glm::vec3(test_vec));

    // 3. Test vector-scalar division
    ASSERT_EQ(glm::vec3(test_vec) / scalar, glm::vec3(test_vec / scalar));

    // 4. Test /= operator with a scalar
    test_vec /= scalar;
    ASSERT_EQ(glm::vec3(one_vec / xyz_vec / scalar), glm::vec3(test_vec));
}

/**
 * Test Vec3f comparison
 */
TEST_F(Vec3fTest_C, TestVec3fComparison) {
    vne::math::Vec3f test_vec_equal = xyz_vec;
    vne::math::Vec3f test_vec_less = xyz_vec - 2.0f;
    vne::math::Vec3f test_vec_greater = xyz_vec + 2.0f;
    ASSERT_TRUE(xyz_vec > test_vec_less);
    ASSERT_TRUE(xyz_vec < test_vec_greater);
    ASSERT_TRUE(xyz_vec == test_vec_equal);
    ASSERT_TRUE(xyz_vec != test_vec_less);
    ASSERT_TRUE(xyz_vec != test_vec_greater);
}

/**
 * Test Vec3f assignment
 */
TEST_F(Vec3fTest_C, TestVec3fAssignment) {
    vne::math::Vec3f test_vec;
    ASSERT_EQ(xyz_vec, test_vec = xyz_vec);
}

/**
 * Test Vec3f specific component
 */
TEST_F(Vec3fTest_C, TestVec3fComponent) {
    float value;
    ASSERT_EQ(xyz_vec.x, xyz_vec[0]);
    ASSERT_EQ(xyz_vec.y, xyz_vec[1]);
    ASSERT_EQ(xyz_vec.z, xyz_vec[2]);
    ASSERT_EQ(xyz_vec.y, value = xyz_vec[1]);
}

/**
 * Test Vec3f inverted vector
 */
TEST_F(Vec3fTest_C, TestVec3fInverted) {
    ASSERT_EQ(-glm::vec3(xyz_vec), -xyz_vec);
}

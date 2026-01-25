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

using namespace VNE;

class Vec4fTest_C : public ::testing::Test {
    // Interface of test fixture base class
   protected:
    void SetUp() override {
        neg_xyzw_vec = vne::math::Vec4f(-2.0f, 14.5f, -6.75f, 8.76f);
        zero_vec = vne::math::Vec4f();
        one_vec = vne::math::Vec4f(1.0f);
        xyzw_vec = vne::math::Vec4f(2.0f, 2.5f, 4.0f, 1.0f);
        x_axis = vne::math::Vec4f(1.0f, 0.0f, 0.0f, 0.0f);
        y_axis = vne::math::Vec4f(0.0f, 1.0f, 0.0f, 0.0f);
        z_axis = vne::math::Vec4f(0.0f, 0.0f, 1.0f, 0.0f);
        w_axis = vne::math::Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
        equal_vec = vne::math::Vec4f(567.345f);
        rand_xyzw_vec = vne::math::Vec4f(0.000034f, 0.000057f, 0.875f, 0.00874f);

        x_point = vne::math::Vec4f(1.0f, 0.0f, 0.0f, 0.0f);
        y_point = vne::math::Vec4f(0.0f, 1.0f, 0.0f, 0.0f);
        z_point = vne::math::Vec4f(0.0f, 0.0f, 1.0f, 0.0f);
        z_point = vne::math::Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
        xyzw_point = vne::math::Vec4f(3.5f, 1.0f, 1.5f, 3.4f);
    }

    void TearDown() override {}

   protected:
    vne::math::Vec4f zero_vec;
    vne::math::Vec4f one_vec;
    vne::math::Vec4f xyzw_vec;
    vne::math::Vec4f x_axis;
    vne::math::Vec4f y_axis;
    vne::math::Vec4f z_axis;
    vne::math::Vec4f w_axis;
    vne::math::Vec4f equal_vec;
    vne::math::Vec4f neg_xyzw_vec;
    vne::math::Vec4f rand_xyzw_vec;
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
TEST_F(Vec4fTest_C, TestVec4fDimensions) {
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
TEST_F(Vec4fTest_C, TestVec4fZero) {
    ASSERT_EQ(glm::vec4(0.0f), zero_vec);
    ASSERT_EQ(zero_vec, vne::math::Vec4f::zero());
}

/**
 * Test Vec4f one vector
 *
 * vne::math::Vec4f::one()
 *
 */
TEST_F(Vec4fTest_C, TestVec4fOne) {
    ASSERT_EQ(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), one_vec);
    ASSERT_EQ(one_vec, vne::math::Vec4f::one());
}

/**
 * Test Vec4f x-axis
 *
 * vne::math::Vec4f::xAxis()
 *
 */
TEST_F(Vec4fTest_C, TestVec4fXAxis) {
    ASSERT_EQ(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f), x_axis);
    ASSERT_EQ(x_axis, vne::math::Vec4f::xAxis());
}

/**
 * Test Vec4f y-axis
 *
 * vne::math::Vec4f::yAxis()
 *
 */
TEST_F(Vec4fTest_C, TestVec4fYAxis) {
    ASSERT_EQ(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f), y_axis);
    ASSERT_EQ(y_axis, vne::math::Vec4f::yAxis());
}

/**
 * Test Vec4f z-axis
 *
 * vne::math::Vec4f::zAxis()
 *
 */
TEST_F(Vec4fTest_C, TestVec4fZAxis) {
    ASSERT_EQ(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f), z_axis);
    ASSERT_EQ(z_axis, vne::math::Vec4f::zAxis());
}

/**
 * Test Vec4f w-axis
 *
 * vne::math::Vec4f::wAxis()
 *
 */
TEST_F(Vec4fTest_C, TestVec4fWAxis) {
    ASSERT_EQ(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), w_axis);
    ASSERT_EQ(w_axis, vne::math::Vec4f::wAxis());
}

/**
 * Test Vec4f GetPtr
 *
 * vec.getPtr()
 *
 */
TEST_F(Vec4fTest_C, TestVec4fGetPtr) {
    ASSERT_EQ(xyzw_vec.x, *(xyzw_vec.getPtr()));
    ASSERT_EQ(xyzw_vec.y, *(xyzw_vec.getPtr() + 1));
    ASSERT_EQ(xyzw_vec.z, *(xyzw_vec.getPtr() + 2));
    ASSERT_EQ(xyzw_vec.w, *(xyzw_vec.getPtr() + 3));
}

/**
 * Test Vec4f XYZ
 *
 * vec.xyz()
 *
 */
TEST_F(Vec4fTest_C, TestVec4fXYZ) {
    ASSERT_EQ(vne::math::Vec3f(xyzw_vec.x, xyzw_vec.y, xyzw_vec.z), xyzw_vec.xyz());
}

/**
 * Test Vec4f XY
 *
 * vec.xy()
 *
 */
TEST_F(Vec4fTest_C, TestVec4fXY) {
    ASSERT_EQ(vne::math::Vec2f(xyzw_vec.x, xyzw_vec.y), xyzw_vec.xy());
}

/**
 * Test coping the 3d vector into 4d vector
 *
 */
TEST_F(Vec4fTest_C, TestVec4fCopy3dVec) {
    vne::math::Vec4f vec_4d;
    vne::math::Vec3f vec_3d = xyzw_vec.xyz();

    vec_4d = vec_3d;
    ASSERT_EQ(vne::math::Vec4f(xyzw_vec.x, xyzw_vec.y, xyzw_vec.z, 0.0f), vec_4d);

    vec_4d = vne::math::Vec4f(vec_3d, 5.0f);
    ASSERT_EQ(vne::math::Vec4f(xyzw_vec.x, xyzw_vec.y, xyzw_vec.z, 5.0f), vec_4d);

    vec_4d = glm::vec3(1.0f, 2.0f, 3.0f);
    ASSERT_EQ(vne::math::Vec4f(1.0f, 2.0f, 3.0f, 0.0f), vec_4d);

    vec_4d = vne::math::Vec4f(glm::vec3(1.0f, 2.0f, 3.0f), 4.0f);
    ASSERT_EQ(vne::math::Vec4f(1.0f, 2.0f, 3.0f, 4.0f), vec_4d);
}

/**
 * Test coping the 2d vector into 4d vector
 *
 */
TEST_F(Vec4fTest_C, TestVec4fCopy2dVec) {
    vne::math::Vec4f vec_4d;
    vne::math::Vec2f vec_2d = xyzw_vec.xy();
    vec_4d = vec_2d;
    ASSERT_EQ(vne::math::Vec4f(xyzw_vec.x, xyzw_vec.y, 0.0f, 0.0f), vec_4d);
    vec_4d = glm::vec2(1.0f, 2.0f);
    ASSERT_EQ(vne::math::Vec4f(1.0f, 2.0f, 0.0f, 0.0f), vec_4d);
}

/**
 * Test coping the plane into 4d vector
 *
 */
// TEST_F(Vec4fTest_C, TestVec4fCopyPlane) {
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
TEST_F(Vec4fTest_C, TestVec4fAbs) {
    ASSERT_EQ(glm::abs(glm::vec4(neg_xyzw_vec)), neg_xyzw_vec.abs());
}

/**
 * Test Vec4f Length and LengthSquare
 */
TEST_F(Vec4fTest_C, TestVec4fLength) {
    ASSERT_EQ(glm::length(glm::vec4(0.0f)), zero_vec.length());
    ASSERT_EQ(glm::length(glm::vec4(1.0f)), one_vec.length());
    ASSERT_EQ(glm::length(glm::vec4(0.0f)), zero_vec.lengthSquare());
    ASSERT_EQ(glm::length2(glm::vec4(1.0f)), one_vec.lengthSquare());
    ASSERT_EQ(glm::length2(glm::vec4(xyzw_vec)), xyzw_vec.lengthSquare());
}

/**
 * Test Vec4f Normalize
 *
 * vec.normalize()
 *
 */
TEST_F(Vec4fTest_C, TestVec4fNormalize) {
    ASSERT_TRUE(x_axis == x_axis.normalize());
    ASSERT_TRUE(y_axis == y_axis.normalize());
    ASSERT_TRUE(x_axis == vne::math::Vec4f::normalized(x_axis));
    ASSERT_TRUE(y_axis == vne::math::Vec4f::normalized(y_axis));
    ASSERT_EQ(glm::normalize(glm::vec4(xyzw_vec)), xyzw_vec.normalize());
}

/**
 * Test Vec4f Min(...)
 *
 * vec1.min(vec2)
 *
 */
TEST_F(Vec4fTest_C, TestVec4fMin) {
    ASSERT_TRUE(zero_vec == one_vec.min(zero_vec));
    ASSERT_TRUE(xyzw_vec == neg_xyzw_vec.min(xyzw_vec));
}

/**
 * Test Vec4f Max(...)
 *
 * vec1.max(vec2)
 *
 */
TEST_F(Vec4fTest_C, TestVec4fMax) {
    ASSERT_TRUE(one_vec == one_vec.max(zero_vec));
    ASSERT_TRUE(neg_xyzw_vec == neg_xyzw_vec.max(xyzw_vec));
}

/**
 * Test Vec4f MinComponent(...)
 *
 * vec.minComponent()
 *
 */
TEST_F(Vec4fTest_C, TestVec4fMinComponent) {
    ASSERT_TRUE(neg_xyzw_vec.z == neg_xyzw_vec.minComponent());
}

/**
 * Test Vec4f MaxComponent(...)
 *
 * vec.maxComponent()
 *
 */
TEST_F(Vec4fTest_C, TestVec4fMaxComponent) {
    ASSERT_TRUE(neg_xyzw_vec.y == neg_xyzw_vec.maxComponent());
}

/**
 * Test Vec4f Dot(...)
 *
 * dot = vec1.dot(vec2)
 * dot = vne::math::Vec4f::dot(vec1, vec2)
 *
 */
TEST_F(Vec4fTest_C, TestVec4fDot) {
    ASSERT_EQ(0.0f, x_axis.dot(y_axis));
    ASSERT_EQ(2.0f, xyzw_vec.dot(x_axis));
    ASSERT_EQ(2.5f, xyzw_vec.dot(y_axis));
    ASSERT_EQ(4.0f, xyzw_vec.dot(z_axis));
    ASSERT_EQ(9.5f, xyzw_vec.dot(one_vec));
    ASSERT_EQ(9.5f, vne::math::Vec4f::dot(xyzw_vec, one_vec));
    ASSERT_FLOAT_EQ(vne::math::halfPi<float>(), vne::math::acos(x_axis.dot(y_axis) / (x_axis.length() * y_axis.length())));
}

/**
 * Test Vec4f Distance calculation.
 *
 * dist = vec1.distance(vec2)
 * dist = vne::math::Vec4f::distance(vec1, vec2)
 *
 */
TEST_F(Vec4fTest_C, TestVec4fDistance) {
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
TEST_F(Vec4fTest_C, TestVec4fRotate) {
    vne::math::Vec4f test_vec{1.0f};
    ASSERT_TRUE(vne::math::Vec4f(1.0f, -1.0f, 1.0f, 1.0f).areSame(test_vec.rotate(z_axis.xyz(), -static_cast<float>(HALF_PI))));
    ASSERT_TRUE(vne::math::Vec4f(-1.0f, 1.0f, 1.0f, 1.0f).areSame(test_vec.rotate(z_axis.xyz(), static_cast<float>(HALF_PI))));
    ASSERT_TRUE(vne::math::Vec4f(1.41421f, 1.0f, 0.0f, 1.0f).areSame(test_vec.rotate(y_axis.xyz(), static_cast<float>(QUARTER_PI)), 1E-5f));
}

/**
 * Test Vec4f Reflect(...)
 *
 * vec.reflect(normal)
 *
 */
TEST_F(Vec4fTest_C, TestVec4fReflect) {
    vne::math::Vec4f test_vec;
    test_vec.x = -xyzw_vec.x;
    test_vec.y = xyzw_vec.y;
    test_vec.z = -xyzw_vec.z;
    test_vec.w = -xyzw_vec.w;
    ASSERT_TRUE(test_vec.areSame(-xyzw_vec.reflect(y_axis)));
}

/**
 * Test Vec4f Refract(...)
 *
 * vec.refract(normal, mu)
 *
 */
TEST_F(Vec4fTest_C, TestVec4fRefract) {
    xyzw_vec.normalize();
    vne::math::Vec4f test_vec;
    test_vec.x = -xyzw_vec.x;
    test_vec.y = xyzw_vec.y;
    test_vec.z = -xyzw_vec.z;
    test_vec.w = -xyzw_vec.w;
    ASSERT_TRUE(test_vec.areSame(-xyzw_vec.refract(y_axis, 1.0f)));
    ASSERT_TRUE(y_axis.areSame(-xyzw_vec.refract(y_axis, 0.0f)));
    vne::math::Vec4f out_vec{-0.191565f, 0.898521f, -0.383131f, -0.0957826f};
    vne::math::Vec4f direction = vne::math::Vec4f::normalized(xyzw_vec);
    ASSERT_TRUE(out_vec.areSame(-direction.refract(y_axis, 0.5f), 1E-5f));
}

/**
 * Test Vec4f Project(...)
 *
 * vec1.project(vec2)
 *
 */
TEST_F(Vec4fTest_C, TestVec4fProject) {
    ASSERT_EQ(zero_vec, x_axis.project(y_axis));  // perpendicular vectors
    ASSERT_EQ(vne::math::Vec4f(0.0f, xyzw_vec.y, 0.0f, 0.0f), xyzw_vec.project(y_axis));
    // Second vector could be any vector ( normal is not compulsory )
    ASSERT_EQ(vne::math::Vec4f(0, xyzw_vec.y, 0.0f, 0.0f), xyzw_vec.project(vne::math::Vec4f(0.0f, 3.0f, 0.0f, 0.0f)));
    // Perpendicular vector of xyzw_vec w.r.t. y_axis
    ASSERT_EQ(vne::math::Vec4f(xyzw_vec.x, 0.0f, xyzw_vec.z, xyzw_vec.w), xyzw_vec - xyzw_vec.project(y_axis));
}

/**
 * Test Vec4f Reject(...)
 *
 * vec1.reject(vec2)
 *
 */
TEST_F(Vec4fTest_C, TestVec4fReject) {
    // Perpendicular vector of xyzw_vec w.r.t. y_axis
    ASSERT_EQ(vne::math::Vec4f(xyzw_vec.x, 0.0f, xyzw_vec.z, xyzw_vec.w), xyzw_vec - xyzw_vec.project(y_axis));
    ASSERT_EQ(vne::math::Vec4f(xyzw_vec.x, 0.0f, xyzw_vec.z, xyzw_vec.w), xyzw_vec.reject(y_axis));
}

/**
 * Test Vec4f DecomposeVec(...)
 *
 * p.decomposeVec(q, proj, perp)
 *
 */
TEST_F(Vec4fTest_C, TestVec4fDecomposeVec) {
    vne::math::Vec4f proj;
    vne::math::Vec4f perp;
    xyzw_vec.decomposeVec(y_axis, proj, perp);
    ASSERT_EQ(vne::math::Vec4f(0.0f, xyzw_vec.y, 0.0f, 0.0f), proj);
    ASSERT_EQ(vne::math::Vec4f(xyzw_vec.x, 0.0f, xyzw_vec.z, xyzw_vec.w), perp);
}

/**
 * Test Vec4f AreSame(...)
 *
 * vec1.areSame(vec2, eps)
 *
 */
TEST_F(Vec4fTest_C, TestVec4fAreSame) {
    ASSERT_TRUE(rand_xyzw_vec.areSame(vne::math::Vec4f(0.000034001f, 0.00005705f, 0.8750001f, 0.008740001f), 1E-5f));
    ASSERT_FALSE(rand_xyzw_vec.areSame(vne::math::Vec4f(0.000035f, 0.000056f, 0.874f, 0.00875f)));
    ASSERT_FALSE(equal_vec.areSame(vne::math::Vec4f(567.3453f)));
    ASSERT_TRUE(equal_vec.areSame(vne::math::Vec4f(567.34503f)));
    ASSERT_TRUE(equal_vec.areSame(vne::math::Vec4f(567.3453f), 1E-3f));
}

/**
 * Test Vec4f AreAligned(...)
 *
 * vec1.areAligned(vec2, eps)
 *
 */
TEST_F(Vec4fTest_C, TestVec4fAreAligned) {
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
TEST_F(Vec4fTest_C, TestVec4fIsZero) {
    ASSERT_TRUE(zero_vec.isZero());
    ASSERT_FALSE(rand_xyzw_vec.isZero());
    ASSERT_FALSE(vne::math::Vec4f(1.0f).isZero(1E-5f));
}

/**
 * Test Vec4f IsNormalized(...)
 *
 * vec1.isNormalized(eps)
 *
 */
TEST_F(Vec4fTest_C, TestVec4fIsNormalized) {
    ASSERT_TRUE(x_axis.isNormalized());
    ASSERT_TRUE(y_axis.isNormalized());
    ASSERT_TRUE(w_axis.isNormalized());
    ASSERT_FALSE(xyzw_vec.isNormalized());
    ASSERT_TRUE(vne::math::Vec4f(0.5f).isNormalized());
}

/**
 * Test Vec4f Angle(...)
 *
 * vec1.angle(vec2)
 * p1.angle(p2, p3)
 *
 */
TEST_F(Vec4fTest_C, TestVec4fAngle) {
    ASSERT_TRUE(vne::math::areSame(vne::math::halfPi<float>(), x_axis.angle(y_axis)));

    ASSERT_TRUE(vne::math::areSame(60.0f, vne::math::radToDeg(x_axis.angle(one_vec))));

    ASSERT_TRUE(vne::math::areSame(
        vne::math::pi<float>() / 6.0f,
        vne::math::Vec4f(static_cast<float>(SQRT_THREE), 1.0f, 0.0f, 0.0f).angle(vne::math::Vec4f(1.0f, static_cast<float>(SQRT_THREE), 0.0f, 0.0f))));

    ASSERT_TRUE(vne::math::areSame(
        vne::math::twoPi<float>() / 3.0f,
        vne::math::Vec4f(static_cast<float>(SQRT_THREE), 1.0f, 0.0f, 0.0f).angle(vne::math::Vec4f(-static_cast<float>(SQRT_THREE), 1.0f, 0.0f, 0.0f))));

    ASSERT_TRUE(vne::math::areSame(63.5799f, vne::math::radToDeg(vne::math::Vec4f(4.0f, 0.0f, 7.0f, 1.0f).angle(vne::math::Vec4f(-2.0f, 1.0f, 3.0f, 1.0f))), 1E-4f));
    ASSERT_TRUE(
        vne::math::areSame(135.608f, vne::math::radToDeg((vne::math::Vec4f(3.0f, 4.0f, -7.0f, 0.0f).angle(vne::math::Vec4f(-2.0f, 1.0f, 3.0f, 0.0f)))), 1E-4f));

    ASSERT_TRUE(
        vne::math::areSame(160.582f,
                      vne::math::radToDeg((vne::math::Vec4f(0.0f).angle(vne::math::Vec4f(2.0f, 5.0f, 4.0f, 0.0f), vne::math::Vec4f(-2.0f, -3.0f, -5.0f, 0.0f)))),
                      1E-4f));
}

/**
 * Test Vec4f MidPoint(...)
 *
 * vne::math::Vec4f::midPoint(vec1, vec2)
 * vec1.midPoint(vec2)
 *
 */
TEST_F(Vec4fTest_C, TestVec4fMidPoint) {
    ASSERT_EQ(vne::math::Vec4f(0.5f, 0.5f, 0.0f, 0.0f), vne::math::Vec4f::midPoint(x_axis, y_axis));
    ASSERT_EQ(vne::math::Vec4f(0.5f, 0.5f, 0.0f, 0.0f), x_axis.midPoint(y_axis));
    ASSERT_EQ(vne::math::Vec4f(0.0f, 0.0f, 0.5f, 0.5f), z_axis.midPoint(w_axis));
}

/**
 * Test Vec4f Lerp(...)
 *
 * vne::math::Vec4f::lerp(vec1, vec2, t)
 * vec1.lerp(vec2, t)
 *
 */
TEST_F(Vec4fTest_C, TestVec4fLerp) {
    ASSERT_EQ(vne::math::Vec4f(0.5f, 0.5f, 0.0f, 0.0f), vne::math::Vec4f::lerp(x_axis, y_axis, 0.5f));
    ASSERT_EQ(x_axis, vne::math::Vec4f::lerp(x_axis, y_axis, 0.0f));
    ASSERT_EQ(y_axis, vne::math::Vec4f::lerp(x_axis, y_axis, 1.0f));
    ASSERT_EQ(y_axis, x_axis.lerp(y_axis, 1.0f));
}

/**
 * Test Vec4f addition
 */
TEST_F(Vec4fTest_C, TestVec4fAddition) {
    float scalar = 2.0f;
    vne::math::Vec4f test_vec = zero_vec;

    // Test vector addition
    ASSERT_EQ(glm::vec4(zero_vec) + glm::vec4(one_vec), glm::vec4(zero_vec + one_vec));

    // Test += operator with a vector
    test_vec += one_vec;
    ASSERT_EQ(glm::vec4(zero_vec) + glm::vec4(1.0f), glm::vec4(test_vec));

    // Test vector-scalar addition
    ASSERT_EQ(glm::vec4(neg_xyzw_vec) + glm::vec4(scalar), glm::vec4(neg_xyzw_vec + scalar));

    // Test += operator with a scalar
    test_vec += scalar;
    ASSERT_EQ(glm::vec4(zero_vec + one_vec) + glm::vec4(scalar), glm::vec4(test_vec));

    // Test chain addition of vector and scalar
    ASSERT_EQ(glm::vec4(test_vec) + glm::vec4(xyzw_vec) + glm::vec4(scalar), glm::vec4(test_vec + xyzw_vec + scalar));

    // Test chain addition with a random vector
    ASSERT_EQ(glm::vec4(test_vec) + glm::vec4(xyzw_vec) + glm::vec4(scalar) + glm::vec4(rand_xyzw_vec),
              glm::vec4(test_vec + xyzw_vec + scalar + rand_xyzw_vec));
}

/**
 * Test Vec4f subtraction
 */
TEST_F(Vec4fTest_C, TestVec4fSubtraction) {
    float scalar = 2.45f;
    vne::math::Vec4f test_vec = zero_vec;

    // Test vector subtraction
    ASSERT_EQ(glm::vec4(neg_xyzw_vec) - glm::vec4(one_vec), glm::vec4(neg_xyzw_vec - one_vec));

    // Test -= operator with a vector
    test_vec -= neg_xyzw_vec;
    ASSERT_EQ(glm::vec4(zero_vec) - glm::vec4(neg_xyzw_vec), glm::vec4(test_vec));

    // Test vector-scalar subtraction
    ASSERT_EQ(glm::vec4(neg_xyzw_vec) - glm::vec4(scalar), glm::vec4(neg_xyzw_vec - scalar));

    // Test -= operator with a scalar
    test_vec -= scalar;
    ASSERT_EQ(glm::vec4(zero_vec - neg_xyzw_vec) - glm::vec4(scalar), glm::vec4(test_vec));

    // Test chain subtraction of vector and scalar
    ASSERT_EQ(glm::vec4(test_vec) - glm::vec4(xyzw_vec) + glm::vec4(scalar), glm::vec4(test_vec - xyzw_vec + scalar));
}

/**
 * Test Vec4f multiplication
 */
TEST_F(Vec4fTest_C, TestVec4fMultiplication) {
    float scalar = 0.000045f;
    vne::math::Vec4f test_vec = one_vec;

    // Test vector multiplication
    ASSERT_EQ(glm::vec4(xyzw_vec) * glm::vec4(test_vec), glm::vec4(xyzw_vec * test_vec));

    // Test *= operator with a vector
    test_vec *= xyzw_vec;
    ASSERT_EQ(glm::vec4(one_vec * xyzw_vec), glm::vec4(test_vec));

    // Test vector-scalar multiplication
    ASSERT_EQ(glm::vec4(test_vec) * glm::vec4(scalar), glm::vec4(test_vec * scalar));

    // Test *= operator with a scalar
    test_vec *= scalar;
    ASSERT_EQ(glm::vec4(one_vec * xyzw_vec * scalar), glm::vec4(test_vec));
}

/**
 * Test Vec4f division
 */
TEST_F(Vec4fTest_C, TestVec4fDivision) {
    float scalar = 45.345f;
    vne::math::Vec4f test_vec = one_vec;

    // Test vector division
    ASSERT_EQ(glm::vec4(xyzw_vec) / glm::vec4(test_vec), glm::vec4(xyzw_vec / test_vec));

    // Test /= operator with a vector
    test_vec /= xyzw_vec;
    ASSERT_EQ(glm::vec4(one_vec / xyzw_vec), glm::vec4(test_vec));

    // Test vector-scalar division
    ASSERT_EQ(glm::vec4(test_vec) / glm::vec4(scalar), glm::vec4(test_vec / scalar));

    // Test /= operator with a scalar
    test_vec /= scalar;
    ASSERT_EQ(glm::vec4(one_vec / xyzw_vec / scalar), glm::vec4(test_vec));
}

/**
 * Test Vec4f comparison
 */
TEST_F(Vec4fTest_C, TestVec4fComparison) {
    vne::math::Vec4f test_vec_equal = xyzw_vec;
    vne::math::Vec4f test_vec_less = xyzw_vec - 2.0f;
    vne::math::Vec4f test_vec_greater = xyzw_vec + 2.0f;
    ASSERT_TRUE(xyzw_vec > test_vec_less);
    ASSERT_TRUE(xyzw_vec < test_vec_greater);
    ASSERT_TRUE(xyzw_vec == test_vec_equal);
    ASSERT_TRUE(xyzw_vec != test_vec_less);
    ASSERT_TRUE(xyzw_vec != test_vec_greater);
}

/**
 * Test Vec4f assignment
 */
TEST_F(Vec4fTest_C, TestVec4fAssignment) {
    vne::math::Vec4f test_vec;
    ASSERT_EQ(xyzw_vec, test_vec = xyzw_vec);
}

/**
 * Test Vec4f specific component
 */
TEST_F(Vec4fTest_C, TestVec4fComponent) {
    float value;
    ASSERT_EQ(xyzw_vec.x, xyzw_vec[0]);
    ASSERT_EQ(xyzw_vec.y, xyzw_vec[1]);
    ASSERT_EQ(xyzw_vec.z, xyzw_vec[2]);
    ASSERT_EQ(xyzw_vec.w, xyzw_vec[3]);
    ASSERT_EQ(xyzw_vec.y, value = xyzw_vec[1]);
    ASSERT_EQ(xyzw_vec.w, value = xyzw_vec[3]);
}

/**
 * Test Vec4f inverted vector
 */
TEST_F(Vec4fTest_C, TestVec4fInverted) {
    ASSERT_EQ(-glm::vec4(xyzw_vec), -xyzw_vec);
}

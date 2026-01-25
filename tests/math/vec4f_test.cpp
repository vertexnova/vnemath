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
        neg_xyzw_vec = Math::Vec4f_C(-2.0f, 14.5f, -6.75f, 8.76f);
        zero_vec = Math::Vec4f_C();
        one_vec = Math::Vec4f_C(1.0f);
        xyzw_vec = Math::Vec4f_C(2.0f, 2.5f, 4.0f, 1.0f);
        x_axis = Math::Vec4f_C(1.0f, 0.0f, 0.0f, 0.0f);
        y_axis = Math::Vec4f_C(0.0f, 1.0f, 0.0f, 0.0f);
        z_axis = Math::Vec4f_C(0.0f, 0.0f, 1.0f, 0.0f);
        w_axis = Math::Vec4f_C(0.0f, 0.0f, 0.0f, 1.0f);
        equal_vec = Math::Vec4f_C(567.345f);
        rand_xyzw_vec = Math::Vec4f_C(0.000034f, 0.000057f, 0.875f, 0.00874f);

        x_point = Math::Vec4f_C(1.0f, 0.0f, 0.0f, 0.0f);
        y_point = Math::Vec4f_C(0.0f, 1.0f, 0.0f, 0.0f);
        z_point = Math::Vec4f_C(0.0f, 0.0f, 1.0f, 0.0f);
        z_point = Math::Vec4f_C(0.0f, 0.0f, 0.0f, 1.0f);
        xyzw_point = Math::Vec4f_C(3.5f, 1.0f, 1.5f, 3.4f);
    }

    void TearDown() override {}

   protected:
    Math::Vec4f_C zero_vec;
    Math::Vec4f_C one_vec;
    Math::Vec4f_C xyzw_vec;
    Math::Vec4f_C x_axis;
    Math::Vec4f_C y_axis;
    Math::Vec4f_C z_axis;
    Math::Vec4f_C w_axis;
    Math::Vec4f_C equal_vec;
    Math::Vec4f_C neg_xyzw_vec;
    Math::Vec4f_C rand_xyzw_vec;
    Math::Vec4f_C x_point;
    Math::Vec4f_C y_point;
    Math::Vec4f_C z_point;
    Math::Vec4f_C w_point;
    Math::Vec4f_C xyzw_point;
};

/**
 * Test Vec4f_C dimensions
 *
 * Math::Vec4f_C::Dim()
 * Math::Vec4f_C::Size()
 *
 */
TEST_F(Vec4fTest_C, TestVec4fDimensions) {
    ASSERT_EQ(4, Math::Vec4f_C::Dim());
    ASSERT_EQ(4, Math::Vec4f_C::Size());
    ASSERT_NE(5, Math::Vec4f_C::Dim());
    ASSERT_NE(10, Math::Vec4f_C::Size());
}

/**
 * Test Vec4f_C zero vector
 *
 * Math::Vec4f_C::Zero()
 *
 */
TEST_F(Vec4fTest_C, TestVec4fZero) {
    ASSERT_EQ(glm::vec4(0.0f), zero_vec);
    ASSERT_EQ(zero_vec, Math::Vec4f_C::Zero());
}

/**
 * Test Vec4f_C one vector
 *
 * Math::Vec4f_C::One()
 *
 */
TEST_F(Vec4fTest_C, TestVec4fOne) {
    ASSERT_EQ(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), one_vec);
    ASSERT_EQ(one_vec, Math::Vec4f_C::One());
}

/**
 * Test Vec4f_C x-axis
 *
 * Math::Vec4f_C::XAxis()
 *
 */
TEST_F(Vec4fTest_C, TestVec4fXAxis) {
    ASSERT_EQ(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f), x_axis);
    ASSERT_EQ(x_axis, Math::Vec4f_C::XAxis());
}

/**
 * Test Vec4f_C y-axis
 *
 * Math::Vec4f_C::YAxis()
 *
 */
TEST_F(Vec4fTest_C, TestVec4fYAxis) {
    ASSERT_EQ(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f), y_axis);
    ASSERT_EQ(y_axis, Math::Vec4f_C::YAxis());
}

/**
 * Test Vec4f_C z-axis
 *
 * Math::Vec4f_C::ZAxis()
 *
 */
TEST_F(Vec4fTest_C, TestVec4fZAxis) {
    ASSERT_EQ(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f), z_axis);
    ASSERT_EQ(z_axis, Math::Vec4f_C::ZAxis());
}

/**
 * Test Vec4f_C w-axis
 *
 * Math::Vec4f_C::WAxis()
 *
 */
TEST_F(Vec4fTest_C, TestVec4fWAxis) {
    ASSERT_EQ(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), w_axis);
    ASSERT_EQ(w_axis, Math::Vec4f_C::WAxis());
}

/**
 * Test Vec4f_C GetPtr
 *
 * vec.GetPtr()
 *
 */
TEST_F(Vec4fTest_C, TestVec4fGetPtr) {
    ASSERT_EQ(xyzw_vec.x, *(xyzw_vec.GetPtr()));
    ASSERT_EQ(xyzw_vec.y, *(xyzw_vec.GetPtr() + 1));
    ASSERT_EQ(xyzw_vec.z, *(xyzw_vec.GetPtr() + 2));
    ASSERT_EQ(xyzw_vec.w, *(xyzw_vec.GetPtr() + 3));
}

/**
 * Test Vec4f_C XYZ
 *
 * vec.XYZ()
 *
 */
TEST_F(Vec4fTest_C, TestVec4fXYZ) {
    ASSERT_EQ(Math::Vec3f_C(xyzw_vec.x, xyzw_vec.y, xyzw_vec.z), xyzw_vec.XYZ());
}

/**
 * Test Vec4f_C XY
 *
 * vec.XY()
 *
 */
TEST_F(Vec4fTest_C, TestVec4fXY) {
    ASSERT_EQ(Math::Vec2f_C(xyzw_vec.x, xyzw_vec.y), xyzw_vec.XY());
}

/**
 * Test coping the 3d vector into 4d vector
 *
 */
TEST_F(Vec4fTest_C, TestVec4fCopy3dVec) {
    Math::Vec4f_C vec_4d;
    Math::Vec3f_C vec_3d = xyzw_vec.XYZ();

    vec_4d = vec_3d;
    ASSERT_EQ(Math::Vec4f_C(xyzw_vec.x, xyzw_vec.y, xyzw_vec.z, 0.0f), vec_4d);

    vec_4d = Math::Vec4f_C(vec_3d, 5.0f);
    ASSERT_EQ(Math::Vec4f_C(xyzw_vec.x, xyzw_vec.y, xyzw_vec.z, 5.0f), vec_4d);

    vec_4d = glm::vec3(1.0f, 2.0f, 3.0f);
    ASSERT_EQ(Math::Vec4f_C(1.0f, 2.0f, 3.0f, 0.0f), vec_4d);

    vec_4d = Math::Vec4f_C(glm::vec3(1.0f, 2.0f, 3.0f), 4.0f);
    ASSERT_EQ(Math::Vec4f_C(1.0f, 2.0f, 3.0f, 4.0f), vec_4d);
}

/**
 * Test coping the 2d vector into 4d vector
 *
 */
TEST_F(Vec4fTest_C, TestVec4fCopy2dVec) {
    Math::Vec4f_C vec_4d;
    Math::Vec2f_C vec_2d = xyzw_vec.XY();
    vec_4d = vec_2d;
    ASSERT_EQ(Math::Vec4f_C(xyzw_vec.x, xyzw_vec.y, 0.0f, 0.0f), vec_4d);
    vec_4d = glm::vec2(1.0f, 2.0f);
    ASSERT_EQ(Math::Vec4f_C(1.0f, 2.0f, 0.0f, 0.0f), vec_4d);
}

/**
 * Test coping the plane into 4d vector
 *
 */
// TEST_F(Vec4fTest_C, TestVec4fCopyPlane) {
//     Math::Plane_C plane;
//     Math::Vec4f_C vec = plane;
//     ASSERT_EQ(vec.x, 0.0f);
//     ASSERT_EQ(vec.y, 0.0f);
//     ASSERT_EQ(vec.z, 1.0f);
//     ASSERT_EQ(vec.w, 0.0f);
// }

/**
 * Test Vec4f_C Abs
 *
 * vec.Abs()
 *
 */
TEST_F(Vec4fTest_C, TestVec4fAbs) {
    ASSERT_EQ(glm::abs(glm::vec4(neg_xyzw_vec)), neg_xyzw_vec.Abs());
}

/**
 * Test Vec4f_C Length and LengthSquare
 */
TEST_F(Vec4fTest_C, TestVec4fLength) {
    ASSERT_EQ(glm::length(glm::vec4(0.0f)), zero_vec.Length());
    ASSERT_EQ(glm::length(glm::vec4(1.0f)), one_vec.Length());
    ASSERT_EQ(glm::length(glm::vec4(0.0f)), zero_vec.LengthSquare());
    ASSERT_EQ(glm::length2(glm::vec4(1.0f)), one_vec.LengthSquare());
    ASSERT_EQ(glm::length2(glm::vec4(xyzw_vec)), xyzw_vec.LengthSquare());
}

/**
 * Test Vec4f_C Normalize
 *
 * vec.Normalize()
 *
 */
TEST_F(Vec4fTest_C, TestVec4fNormalize) {
    ASSERT_TRUE(x_axis == x_axis.Normalize());
    ASSERT_TRUE(y_axis == y_axis.Normalize());
    ASSERT_TRUE(x_axis == Math::Vec4f_C::Normalized(x_axis));
    ASSERT_TRUE(y_axis == Math::Vec4f_C::Normalized(y_axis));
    ASSERT_EQ(glm::normalize(glm::vec4(xyzw_vec)), xyzw_vec.Normalize());
}

/**
 * Test Vec4f_C Min(...)
 *
 * vec1.Min(vec2)
 *
 */
TEST_F(Vec4fTest_C, TestVec4fMin) {
    ASSERT_TRUE(zero_vec == one_vec.Min(zero_vec));
    ASSERT_TRUE(xyzw_vec == neg_xyzw_vec.Min(xyzw_vec));
}

/**
 * Test Vec4f_C Max(...)
 *
 * vec1.Max(vec2)
 *
 */
TEST_F(Vec4fTest_C, TestVec4fMax) {
    ASSERT_TRUE(one_vec == one_vec.Max(zero_vec));
    ASSERT_TRUE(neg_xyzw_vec == neg_xyzw_vec.Max(xyzw_vec));
}

/**
 * Test Vec4f_C MinComponent(...)
 *
 * vec.MinComponent()
 *
 */
TEST_F(Vec4fTest_C, TestVec4fMinComponent) {
    ASSERT_TRUE(neg_xyzw_vec.z == neg_xyzw_vec.MinComponent());
}

/**
 * Test Vec4f_C MaxComponent(...)
 *
 * vec.MaxComponent()
 *
 */
TEST_F(Vec4fTest_C, TestVec4fMaxComponent) {
    ASSERT_TRUE(neg_xyzw_vec.y == neg_xyzw_vec.MaxComponent());
}

/**
 * Test Vec4f_C Dot(...)
 *
 * dot = vec1.Dot(vec2)
 * dot = Math::Vec4f_C::Dot(vec1, vec2)
 *
 */
TEST_F(Vec4fTest_C, TestVec4fDot) {
    ASSERT_EQ(0.0f, x_axis.Dot(y_axis));
    ASSERT_EQ(2.0f, xyzw_vec.Dot(x_axis));
    ASSERT_EQ(2.5f, xyzw_vec.Dot(y_axis));
    ASSERT_EQ(4.0f, xyzw_vec.Dot(z_axis));
    ASSERT_EQ(9.5f, xyzw_vec.Dot(one_vec));
    ASSERT_EQ(9.5f, Math::Vec4f_C::Dot(xyzw_vec, one_vec));
    ASSERT_FLOAT_EQ(Math::HalfPi<float>(), Math::ACos(x_axis.Dot(y_axis) / (x_axis.Length() * y_axis.Length())));
}

/**
 * Test Vec4f_C Distance calculation.
 *
 * dist = vec1.Distance(vec2)
 * dist = Math::Vec4f_C::Distance(vec1, vec2)
 *
 */
TEST_F(Vec4fTest_C, TestVec4fDistance) {
    ASSERT_FLOAT_EQ(static_cast<float>(SQRT_TWO), Math::Vec4f_C::Distance(x_point, y_point));
    ASSERT_FLOAT_EQ(5.2019229f, Math::Vec4f_C::Distance(Math::Vec4f_C::Zero(), xyzw_point));
    ASSERT_FLOAT_EQ(4.5891175f, Math::Vec4f_C::Distance(x_point, xyzw_point));
    ASSERT_FLOAT_EQ(5.1048999f, xyzw_point.Distance(y_point));
}

/**
 * Test Vec4f_C Rotate function.
 *
 * vec.Rotate(axis, angle)
 *
 */
TEST_F(Vec4fTest_C, TestVec4fRotate) {
    Math::Vec4f_C test_vec{1.0f};
    ASSERT_TRUE(Math::Vec4f_C(1.0f, -1.0f, 1.0f, 1.0f).AreSame(test_vec.Rotate(z_axis.XYZ(), -static_cast<float>(HALF_PI))));
    ASSERT_TRUE(Math::Vec4f_C(-1.0f, 1.0f, 1.0f, 1.0f).AreSame(test_vec.Rotate(z_axis.XYZ(), static_cast<float>(HALF_PI))));
    ASSERT_TRUE(Math::Vec4f_C(1.41421f, 1.0f, 0.0f, 1.0f).AreSame(test_vec.Rotate(y_axis.XYZ(), static_cast<float>(QUARTER_PI)), 1E-5f));
}

/**
 * Test Vec4f_C Reflect(...)
 *
 * vec.Reflect(normal)
 *
 */
TEST_F(Vec4fTest_C, TestVec4fReflect) {
    Math::Vec4f_C test_vec;
    test_vec.x = -xyzw_vec.x;
    test_vec.y = xyzw_vec.y;
    test_vec.z = -xyzw_vec.z;
    test_vec.w = -xyzw_vec.w;
    ASSERT_TRUE(test_vec.AreSame(-xyzw_vec.Reflect(y_axis)));
}

/**
 * Test Vec4f_C Refract(...)
 *
 * vec.Refract(normal, mu)
 *
 */
TEST_F(Vec4fTest_C, TestVec4fRefract) {
    xyzw_vec.Normalize();
    Math::Vec4f_C test_vec;
    test_vec.x = -xyzw_vec.x;
    test_vec.y = xyzw_vec.y;
    test_vec.z = -xyzw_vec.z;
    test_vec.w = -xyzw_vec.w;
    ASSERT_TRUE(test_vec.AreSame(-xyzw_vec.Refract(y_axis, 1.0f)));
    ASSERT_TRUE(y_axis.AreSame(-xyzw_vec.Refract(y_axis, 0.0f)));
    Math::Vec4f_C out_vec{-0.191565f, 0.898521f, -0.383131f, -0.0957826f};
    Math::Vec4f_C direction = Math::Vec4f_C::Normalized(xyzw_vec);
    ASSERT_TRUE(out_vec.AreSame(-direction.Refract(y_axis, 0.5f), 1E-5f));
}

/**
 * Test Vec4f_C Project(...)
 *
 * vec1.Project(vec2)
 *
 */
TEST_F(Vec4fTest_C, TestVec4fProject) {
    ASSERT_EQ(zero_vec, x_axis.Project(y_axis));  // perpendicular vectors
    ASSERT_EQ(Math::Vec4f_C(0.0f, xyzw_vec.y, 0.0f, 0.0f), xyzw_vec.Project(y_axis));
    // Second vector could be any vector ( normal is not compulsory )
    ASSERT_EQ(Math::Vec4f_C(0, xyzw_vec.y, 0.0f, 0.0f), xyzw_vec.Project(Math::Vec4f_C(0.0f, 3.0f, 0.0f, 0.0f)));
    // Perpendicular vector of xyzw_vec w.r.t. y_axis
    ASSERT_EQ(Math::Vec4f_C(xyzw_vec.x, 0.0f, xyzw_vec.z, xyzw_vec.w), xyzw_vec - xyzw_vec.Project(y_axis));
}

/**
 * Test Vec4f_C Reject(...)
 *
 * vec1.Reject(vec2)
 *
 */
TEST_F(Vec4fTest_C, TestVec4fReject) {
    // Perpendicular vector of xyzw_vec w.r.t. y_axis
    ASSERT_EQ(Math::Vec4f_C(xyzw_vec.x, 0.0f, xyzw_vec.z, xyzw_vec.w), xyzw_vec - xyzw_vec.Project(y_axis));
    ASSERT_EQ(Math::Vec4f_C(xyzw_vec.x, 0.0f, xyzw_vec.z, xyzw_vec.w), xyzw_vec.Reject(y_axis));
}

/**
 * Test Vec4f_C DecomposeVec(...)
 *
 * p.DecomposeVec(q, proj, perp)
 *
 */
TEST_F(Vec4fTest_C, TestVec4fDecomposeVec) {
    Math::Vec4f_C proj;
    Math::Vec4f_C perp;
    xyzw_vec.DecomposeVec(y_axis, proj, perp);
    ASSERT_EQ(Math::Vec4f_C(0.0f, xyzw_vec.y, 0.0f, 0.0f), proj);
    ASSERT_EQ(Math::Vec4f_C(xyzw_vec.x, 0.0f, xyzw_vec.z, xyzw_vec.w), perp);
}

/**
 * Test Vec4f_C AreSame(...)
 *
 * vec1.AreSame(vec2, eps)
 *
 */
TEST_F(Vec4fTest_C, TestVec4fAreSame) {
    ASSERT_TRUE(rand_xyzw_vec.AreSame(Math::Vec4f_C(0.000034001f, 0.00005705f, 0.8750001f, 0.008740001f), 1E-5f));
    ASSERT_FALSE(rand_xyzw_vec.AreSame(Math::Vec4f_C(0.000035f, 0.000056f, 0.874f, 0.00875f)));
    ASSERT_FALSE(equal_vec.AreSame(Math::Vec4f_C(567.3453f)));
    ASSERT_TRUE(equal_vec.AreSame(Math::Vec4f_C(567.34503f)));
    ASSERT_TRUE(equal_vec.AreSame(Math::Vec4f_C(567.3453f), 1E-3f));
}

/**
 * Test Vec4f_C AreAligned(...)
 *
 * vec1.AreAligned(vec2, eps)
 *
 */
TEST_F(Vec4fTest_C, TestVec4fAreAligned) {
    ASSERT_FALSE(Math::Vec4f_C(1.0f).AreSame(Math::Vec4f_C(2.0f)));
    ASSERT_TRUE(Math::Vec4f_C(1.0f).AreAligned(Math::Vec4f_C(2.0f)));
    ASSERT_FALSE(Math::Vec4f_C(1.0f).AreAligned(Math::Vec4f_C(2.05f, 2.0f, 2.0f, 2.0f)));
    ASSERT_TRUE(Math::Vec4f_C(1.0f).AreAligned(Math::Vec4f_C(2.05f, 2.0499999f, 2.0499999f, 2.0499999f), 1E-4f));
}

/**
 * Test Vec4f_C IsZero(...)
 *
 * vec1.IsZero(eps)
 *
 */
TEST_F(Vec4fTest_C, TestVec4fIsZero) {
    ASSERT_TRUE(zero_vec.IsZero());
    ASSERT_FALSE(rand_xyzw_vec.IsZero());
    ASSERT_FALSE(Math::Vec4f_C(1.0f).IsZero(1E-5f));
}

/**
 * Test Vec4f_C IsNormalized(...)
 *
 * vec1.IsNormalized(eps)
 *
 */
TEST_F(Vec4fTest_C, TestVec4fIsNormalized) {
    ASSERT_TRUE(x_axis.IsNormalized());
    ASSERT_TRUE(y_axis.IsNormalized());
    ASSERT_TRUE(w_axis.IsNormalized());
    ASSERT_FALSE(xyzw_vec.IsNormalized());
    ASSERT_TRUE(Math::Vec4f_C(0.5f).IsNormalized());
}

/**
 * Test Vec4f_C Angle(...)
 *
 * vec1.Angle(vec2)
 * p1.Angle(p2, p3)
 *
 */
TEST_F(Vec4fTest_C, TestVec4fAngle) {
    ASSERT_TRUE(Math::AreSame(Math::HalfPi<float>(), x_axis.Angle(y_axis)));

    ASSERT_TRUE(Math::AreSame(60.0f, Math::RadToDeg(x_axis.Angle(one_vec))));

    ASSERT_TRUE(Math::AreSame(
        Math::Pi<float>() / 6.0f,
        Math::Vec4f_C(static_cast<float>(SQRT_THREE), 1.0f, 0.0f, 0.0f).Angle(Math::Vec4f_C(1.0f, static_cast<float>(SQRT_THREE), 0.0f, 0.0f))));

    ASSERT_TRUE(Math::AreSame(
        Math::TwoPi<float>() / 3.0f,
        Math::Vec4f_C(static_cast<float>(SQRT_THREE), 1.0f, 0.0f, 0.0f).Angle(Math::Vec4f_C(-static_cast<float>(SQRT_THREE), 1.0f, 0.0f, 0.0f))));

    ASSERT_TRUE(Math::AreSame(63.5799f, Math::RadToDeg(Math::Vec4f_C(4.0f, 0.0f, 7.0f, 1.0f).Angle(Math::Vec4f_C(-2.0f, 1.0f, 3.0f, 1.0f))), 1E-4f));
    ASSERT_TRUE(
        Math::AreSame(135.608f, Math::RadToDeg((Math::Vec4f_C(3.0f, 4.0f, -7.0f, 0.0f).Angle(Math::Vec4f_C(-2.0f, 1.0f, 3.0f, 0.0f)))), 1E-4f));

    ASSERT_TRUE(
        Math::AreSame(160.582f,
                      Math::RadToDeg((Math::Vec4f_C(0.0f).Angle(Math::Vec4f_C(2.0f, 5.0f, 4.0f, 0.0f), Math::Vec4f_C(-2.0f, -3.0f, -5.0f, 0.0f)))),
                      1E-4f));
}

/**
 * Test Vec4f_C MidPoint(...)
 *
 * Math::Vec4f_C::MidPoint(vec1, vec2)
 * vec1.MidPoint(vec2)
 *
 */
TEST_F(Vec4fTest_C, TestVec4fMidPoint) {
    ASSERT_EQ(Math::Vec4f_C(0.5f, 0.5f, 0.0f, 0.0f), Math::Vec4f_C::MidPoint(x_axis, y_axis));
    ASSERT_EQ(Math::Vec4f_C(0.5f, 0.5f, 0.0f, 0.0f), x_axis.MidPoint(y_axis));
    ASSERT_EQ(Math::Vec4f_C(0.0f, 0.0f, 0.5f, 0.5f), z_axis.MidPoint(w_axis));
}

/**
 * Test Vec4f_C Lerp(...)
 *
 * Math::Vec4f_C::Lerp(vec1, vec2, t)
 * vec1.Lerp(vec2, t)
 *
 */
TEST_F(Vec4fTest_C, TestVec4fLerp) {
    ASSERT_EQ(Math::Vec4f_C(0.5f, 0.5f, 0.0f, 0.0f), Math::Vec4f_C::Lerp(x_axis, y_axis, 0.5f));
    ASSERT_EQ(x_axis, Math::Vec4f_C::Lerp(x_axis, y_axis, 0.0f));
    ASSERT_EQ(y_axis, Math::Vec4f_C::Lerp(x_axis, y_axis, 1.0f));
    ASSERT_EQ(y_axis, x_axis.Lerp(y_axis, 1.0f));
}

/**
 * Test Vec4f_C addition
 */
TEST_F(Vec4fTest_C, TestVec4fAddition) {
    float scalar = 2.0f;
    Math::Vec4f_C test_vec = zero_vec;

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
 * Test Vec4f_C subtraction
 */
TEST_F(Vec4fTest_C, TestVec4fSubtraction) {
    float scalar = 2.45f;
    Math::Vec4f_C test_vec = zero_vec;

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
 * Test Vec4f_C multiplication
 */
TEST_F(Vec4fTest_C, TestVec4fMultiplication) {
    float scalar = 0.000045f;
    Math::Vec4f_C test_vec = one_vec;

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
 * Test Vec4f_C division
 */
TEST_F(Vec4fTest_C, TestVec4fDivision) {
    float scalar = 45.345f;
    Math::Vec4f_C test_vec = one_vec;

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
 * Test Vec4f_C comparison
 */
TEST_F(Vec4fTest_C, TestVec4fComparison) {
    Math::Vec4f_C test_vec_equal = xyzw_vec;
    Math::Vec4f_C test_vec_less = xyzw_vec - 2.0f;
    Math::Vec4f_C test_vec_greater = xyzw_vec + 2.0f;
    ASSERT_TRUE(xyzw_vec > test_vec_less);
    ASSERT_TRUE(xyzw_vec < test_vec_greater);
    ASSERT_TRUE(xyzw_vec == test_vec_equal);
    ASSERT_TRUE(xyzw_vec != test_vec_less);
    ASSERT_TRUE(xyzw_vec != test_vec_greater);
}

/**
 * Test Vec4f_C assignment
 */
TEST_F(Vec4fTest_C, TestVec4fAssignment) {
    Math::Vec4f_C test_vec;
    ASSERT_EQ(xyzw_vec, test_vec = xyzw_vec);
}

/**
 * Test Vec4f_C specific component
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
 * Test Vec4f_C inverted vector
 */
TEST_F(Vec4fTest_C, TestVec4fInverted) {
    ASSERT_EQ(-glm::vec4(xyzw_vec), -xyzw_vec);
}

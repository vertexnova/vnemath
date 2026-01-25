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
        neg_xyz_vec = Math::Vec3f_C(-2.0f, 14.5f, -6.75f);
        zero_vec = Math::Vec3f_C();
        one_vec = Math::Vec3f_C(1.0f);
        xyz_vec = Math::Vec3f_C(2.0f, 2.5f, 4.0f);
        x_axis = Math::Vec3f_C(1.0f, 0.0f, 0.0f);
        y_axis = Math::Vec3f_C(0.0f, 1.0f, 0.0f);
        z_axis = Math::Vec3f_C(0.0f, 0.0f, 1.0f);
        equal_vec = Math::Vec3f_C(567.345f);
        rand_xyz_vec = Math::Vec3f_C(0.000034f, 0.000057f, 0.875f);

        x_point = Math::Vec3f_C(1.0f, 0.0f, 0.0f);
        y_point = Math::Vec3f_C(0.0f, 1.0f, 0.0f);
        z_point = Math::Vec3f_C(0.0f, 0.0f, 1.0f);
        xyz_point = Math::Vec3f_C(3.5f, 1.0f, 1.5f);
    }

    void TearDown() override {}

   protected:
    Math::Vec3f_C zero_vec;
    Math::Vec3f_C one_vec;
    Math::Vec3f_C xyz_vec;
    Math::Vec3f_C x_axis;
    Math::Vec3f_C y_axis;
    Math::Vec3f_C z_axis;
    Math::Vec3f_C equal_vec;
    Math::Vec3f_C neg_xyz_vec;
    Math::Vec3f_C rand_xyz_vec;
    Math::Vec3f_C x_point;
    Math::Vec3f_C y_point;
    Math::Vec3f_C z_point;
    Math::Vec3f_C xyz_point;
};

/**
 * Test Vec3f_C dimensions
 *
 * Math::Vec3f_C::Dim()
 * Math::Vec3f_C::Size()
 *
 */
TEST_F(Vec3fTest_C, TestVec3fDimensions) {
    ASSERT_EQ(3, Math::Vec3f_C::Dim());
    ASSERT_EQ(3, Math::Vec3f_C::Size());
    ASSERT_NE(4, Math::Vec3f_C::Dim());
    ASSERT_NE(9, Math::Vec3f_C::Size());
}

/**
 * Test Vec3f_C zero vector
 *
 * Math::Vec3f_C::Zero()
 *
 */
TEST_F(Vec3fTest_C, TestVec3fZero) {
    ASSERT_EQ(glm::vec3(0.0f, 0.0f, 0.0f), zero_vec);
    ASSERT_EQ(zero_vec, Math::Vec3f_C::Zero());
}

/**
 * Test Vec3f_C one vector
 *
 * Math::Vec3f_C::One()
 *
 */
TEST_F(Vec3fTest_C, TestVec3fOne) {
    ASSERT_EQ(glm::vec3(1.0f, 1.0f, 1.0f), one_vec);
    ASSERT_EQ(one_vec, Math::Vec3f_C::One());
}

/**
 * Test Vec3f_C x-axis
 *
 * Math::Vec3f_C::XAxis()
 *
 */
TEST_F(Vec3fTest_C, TestVec3fXAxis) {
    ASSERT_EQ(glm::vec3(1.0f, 0.0f, 0.0f), x_axis);
    ASSERT_EQ(x_axis, Math::Vec3f_C::XAxis());
}

/**
 * Test Vec3f_C y-axis
 *
 * Math::Vec3f_C::YAxis()
 *
 */
TEST_F(Vec3fTest_C, TestVec3fYAxis) {
    ASSERT_EQ(glm::vec3(0.0f, 1.0f, 0.0f), y_axis);
    ASSERT_EQ(y_axis, Math::Vec3f_C::YAxis());
}

/**
 * Test Vec3f_C z-axis
 *
 * Math::Vec3f_C::ZAxis()
 *
 */
TEST_F(Vec3fTest_C, TestVec3fZAxis) {
    ASSERT_EQ(glm::vec3(0.0f, 0.0f, 1.0f), z_axis);
    ASSERT_EQ(z_axis, Math::Vec3f_C::ZAxis());
}

/**
 * Test Vec3f_C up direction
 *
 * Math::Vec3f_C::Up()
 *
 */
TEST_F(Vec3fTest_C, TestVec3fUp) {
    ASSERT_EQ(glm::vec3(0.0f, 1.0f, 0.0f), Math::Vec3f_C::Up());
}

/**
 * Test Vec3f_C down direction
 *
 * Math::Vec3f_C::Down()
 *
 */
TEST_F(Vec3fTest_C, TestVec3fDown) {
    ASSERT_EQ(glm::vec3(0.0f, -1.0f, 0.0f), Math::Vec3f_C::Down());
}

/**
 * Test Vec3f_C left direction
 *
 * Math::Vec3f_C::Left()
 *
 */
TEST_F(Vec3fTest_C, TestVec3fLeft) {
    ASSERT_EQ(glm::vec3(-1.0f, 0.0f, 0.0f), Math::Vec3f_C::Left());
}

/**
 * Test Vec3f_C right direction
 *
 * Math::Vec3f_C::Right()
 *
 */
TEST_F(Vec3fTest_C, TestVec3fRight) {
    ASSERT_EQ(glm::vec3(1.0f, 0.0f, 0.0f), Math::Vec3f_C::Right());
}

/**
 * Test Vec3f_C forward direction
 *
 * Math::Vec3f_C::Forward()
 *
 */
TEST_F(Vec3fTest_C, TestVec3fForward) {
    ASSERT_EQ(glm::vec3(0.0f, 0.0f, 1.0f), Math::Vec3f_C::Forward());
}

/**
 * Test Vec3f_C backward direction
 *
 * Math::Vec3f_C::Backward()
 *
 */
TEST_F(Vec3fTest_C, TestVec3fBackward) {
    ASSERT_EQ(glm::vec3(0.0f, 0.0f, -1.0f), Math::Vec3f_C::Backward());
}

/**
 * Test Vec3f_C GetPtr
 *
 * vec.GetPtr()
 *
 */
TEST_F(Vec3fTest_C, TestVec3fGetPtr) {
    ASSERT_EQ(xyz_vec.x, *(xyz_vec.GetPtr()));
    ASSERT_EQ(xyz_vec.y, *(xyz_vec.GetPtr() + 1));
    ASSERT_EQ(xyz_vec.z, *(xyz_vec.GetPtr() + 2));
    ASSERT_EQ(x_axis.x, *(x_axis.GetPtr()));
    ASSERT_EQ(x_axis.y, *(x_axis.GetPtr() + 1));
    ASSERT_EQ(x_axis.z, *(x_axis.GetPtr() + 2));
}

/**
 * Test Vec3f_C XY
 *
 * vec.XY()
 *
 */
TEST_F(Vec3fTest_C, TestVec3fXY) {
    ASSERT_EQ(Math::Vec2f_C(xyz_vec.x, xyz_vec.y), xyz_vec.XY());
}

/**
 * Test coping the 2d vector into 3d vector
 *
 */
TEST_F(Vec3fTest_C, TestVec3fCopy2dVec) {
    Math::Vec3f_C vec_3d;
    Math::Vec2f_C vec_2d = xyz_vec.XY();

    vec_3d = vec_2d;
    ASSERT_EQ(Math::Vec3f_C(xyz_vec.x, xyz_vec.y, 0.0f), vec_3d);

    vec_3d = Math::Vec3f_C(vec_3d, 5.0f);
    ASSERT_EQ(Math::Vec3f_C(xyz_vec.x, xyz_vec.y, 5.0f), vec_3d);

    vec_3d = glm::vec2(1.0f, 2.0f);
    ASSERT_EQ(Math::Vec3f_C(1.0f, 2.0f, 0.0f), vec_3d);

    vec_3d = Math::Vec3f_C(glm::vec2(1.0f, 2.0f), 3.0f);
    ASSERT_EQ(Math::Vec3f_C(1.0f, 2.0f, 3.0f), vec_3d);
}

/**
 * Test Vec3f_C Abs
 *
 * vec.Abs()
 *
 */
TEST_F(Vec3fTest_C, TestVec3fAbs) {
    ASSERT_EQ(glm::abs(glm::vec3(neg_xyz_vec)), neg_xyz_vec.Abs());
}

/**
 * Test Vec3f_C Length and LengthSquare
 */
TEST_F(Vec3fTest_C, TestVec3fLength) {
    ASSERT_EQ(glm::length(glm::vec3(0.0f)), zero_vec.Length());
    ASSERT_EQ(glm::length(glm::vec3(1.0f)), one_vec.Length());
    ASSERT_EQ(glm::length(glm::vec3(0.0f)), zero_vec.LengthSquare());
    ASSERT_EQ(glm::length2(glm::vec3(1.0f)), one_vec.LengthSquare());
    ASSERT_EQ(glm::length2(glm::vec3(xyz_vec)), xyz_vec.LengthSquare());
}

/**
 * Test Vec3f_C Normalize
 *
 * vec.Normalize()
 *
 */
TEST_F(Vec3fTest_C, TestVec3fNormalize) {
    ASSERT_TRUE(x_axis == x_axis.Normalize());
    ASSERT_TRUE(y_axis == y_axis.Normalize());
    ASSERT_TRUE(x_axis == Math::Vec3f_C::Normalized(x_axis));
    ASSERT_TRUE(y_axis == Math::Vec3f_C::Normalized(y_axis));
    ASSERT_EQ(glm::normalize(glm::vec3(xyz_vec)), xyz_vec.Normalize());
}

/**
 * Test Vec3f_C Min(...)
 *
 * vec1.Min(vec2)
 *
 */
TEST_F(Vec3fTest_C, TestVec3fMin) {
    ASSERT_TRUE(zero_vec == one_vec.Min(zero_vec));
    ASSERT_TRUE(xyz_vec == neg_xyz_vec.Min(xyz_vec));
}

/**
 * Test Vec3f_C Max(...)
 *
 * vec1.Max(vec2)
 *
 */
TEST_F(Vec3fTest_C, TestVec3fMax) {
    ASSERT_TRUE(one_vec == one_vec.Max(zero_vec));
    ASSERT_TRUE(neg_xyz_vec == neg_xyz_vec.Max(xyz_vec));
}

/**
 * Test Vec3f_C MinComponent(...)
 *
 * vec.MinComponent()
 *
 */
TEST_F(Vec3fTest_C, TestVec3fMinComponent) {
    ASSERT_TRUE(neg_xyz_vec.z == neg_xyz_vec.MinComponent());
}

/**
 * Test Vec3f_C MaxComponent(...)
 *
 * vec.MaxComponent()
 *
 */
TEST_F(Vec3fTest_C, TestVec3fMaxComponent) {
    ASSERT_TRUE(neg_xyz_vec.y == neg_xyz_vec.MaxComponent());
}

/**
 * Test Vec3f_C Dot(...)
 *
 * dot = vec1.Dot(vec2)
 * dot = Math::Vec3f_C::Dot(vec1, vec2)
 *
 */
TEST_F(Vec3fTest_C, TestVec3fDot) {
    ASSERT_EQ(0.0f, x_axis.Dot(y_axis));
    ASSERT_EQ(2.0f, xyz_vec.Dot(x_axis));
    ASSERT_EQ(2.5f, xyz_vec.Dot(y_axis));
    ASSERT_EQ(4.0f, xyz_vec.Dot(z_axis));
    ASSERT_EQ(8.5f, xyz_vec.Dot(one_vec));
    ASSERT_EQ(8.5f, Math::Vec3f_C::Dot(xyz_vec, one_vec));
    ASSERT_FLOAT_EQ(Math::HalfPi<float>(), Math::ACos(x_axis.Dot(y_axis) / (x_axis.Length() * y_axis.Length())));
}

/**
 * Test Vec3f_C Cross product.
 *
 * cross = vec1.Cross(vec2)
 * cross = Math::Vec3f_C::Cross(vec1, vec2)
 *
 */
TEST_F(Vec3fTest_C, TestVec3fCross) {
    ASSERT_EQ(z_axis, x_axis.Cross(y_axis));
    ASSERT_EQ(z_axis, Math::Vec3f_C::Cross(x_axis, y_axis));
    ASSERT_EQ(glm::cross(x_axis, y_axis), Math::Vec3f_C::Cross(x_axis, y_axis));

    Math::Vec3f_C test_vec{3.5f, 1.0f, 1.5f};
    ASSERT_EQ(Math::Vec3f_C(-0.25f, 11.0f, -6.75f), Math::Vec3f_C::Cross(xyz_vec, test_vec));
}

/**
 * Test Vec3f_C Distance calculation.
 *
 * dist = vec1.Distance(vec2)
 * dist = Math::Vec3f_C::Distance(vec1, vec2)
 *
 */
TEST_F(Vec3fTest_C, TestVec3fDistance) {
    ASSERT_FLOAT_EQ(static_cast<float>(SQRT_TWO), Math::Vec3f_C::Distance(x_point, y_point));
    ASSERT_FLOAT_EQ(3.9370039f, Math::Vec3f_C::Distance(Math::Vec3f_C::Zero(), xyz_point));
    ASSERT_FLOAT_EQ(3.082207f, Math::Vec3f_C::Distance(x_point, xyz_point));
    ASSERT_FLOAT_EQ(3.8078866f, xyz_point.Distance(y_point));
}

/**
 * Test Vec3f_C Rotate function.
 *
 * vec.Rotate(axis, angle)
 *
 */
TEST_F(Vec3fTest_C, TestVec3fRotate) {
    Math::Vec3f_C test_vec{1.0f};
    ASSERT_TRUE(Math::Vec3f_C(1.0f, -1.0f, 1.0f).AreSame(test_vec.Rotate(z_axis, -static_cast<float>(HALF_PI))));
    ASSERT_TRUE(Math::Vec3f_C(-1.0f, 1.0f, 1.0f).AreSame(test_vec.Rotate(z_axis, static_cast<float>(HALF_PI))));
    ASSERT_TRUE(Math::Vec3f_C(1.41421f, 1.0f, 0.0f).AreSame(test_vec.Rotate(y_axis, static_cast<float>(QUARTER_PI)), 1E-5f));
}

/**
 * Test Vec3f_C Reflect(...)
 *
 * vec.Reflect(normal)
 *
 */
TEST_F(Vec3fTest_C, TestVec3fReflect) {
    Math::Vec3f_C test_vec;
    test_vec.x = -xyz_vec.x;
    test_vec.y = xyz_vec.y;
    test_vec.z = -xyz_vec.z;
    ASSERT_TRUE(test_vec.AreSame(-xyz_vec.Reflect(y_axis)));
}

/**
 * Test Vec3f_C Refract(...)
 *
 * vec.Refract(normal, mu)
 *
 */
TEST_F(Vec3fTest_C, TestVec3fRefract) {
    xyz_vec.Normalize();
    Math::Vec3f_C test_vec;
    test_vec.x = -xyz_vec.x;
    test_vec.y = xyz_vec.y;
    test_vec.z = -xyz_vec.z;
    ASSERT_TRUE(test_vec.AreSame(-xyz_vec.Refract(y_axis, 1.0f)));
    ASSERT_TRUE(y_axis.AreSame(-xyz_vec.Refract(y_axis, 0.0f)));
    Math::Vec3f_C out_vec{-0.19518f, 0.899735f, -0.39036f};
    Math::Vec3f_C direction = Math::Vec3f_C::Normalized(xyz_vec);
    ASSERT_TRUE(out_vec.AreSame(-direction.Refract(y_axis, 0.5f), 1E-5f));
}

/**
 * Test Vec3f_C Project(...)
 *
 * vec1.Project(vec2)
 *
 */
TEST_F(Vec3fTest_C, TestVec3fProject) {
    ASSERT_EQ(zero_vec, x_axis.Project(y_axis));  // perpendicular vectors
    ASSERT_EQ(Math::Vec3f_C(0.0f, xyz_vec.y, 0.0f), xyz_vec.Project(y_axis));
    // Second vector could be any vector ( normal is not compulsory )
    ASSERT_EQ(Math::Vec3f_C(0, xyz_vec.y, 0.0f), xyz_vec.Project(Math::Vec3f_C(0.0f, 3.0f, 0.0f)));
    // Perpendicular vector of xyz_vec w.r.t. y_axis
    ASSERT_EQ(Math::Vec3f_C(xyz_vec.x, 0.0f, xyz_vec.z), xyz_vec - xyz_vec.Project(y_axis));
}

/**
 * Test Vec3f_C Reject(...)
 *
 * vec1.Reject(vec2)
 *
 */
TEST_F(Vec3fTest_C, TestVec3fReject) {
    // Perpendicular vector of xyz_vec w.r.t. y_axis
    ASSERT_EQ(Math::Vec3f_C(xyz_vec.x, 0.0f, xyz_vec.z), xyz_vec - xyz_vec.Project(y_axis));
    ASSERT_EQ(Math::Vec3f_C(xyz_vec.x, 0.0f, xyz_vec.z), xyz_vec.Reject(y_axis));
}

/**
 * Test Vec3f_C DecomposeVec(...)
 *
 * p.DecomposeVec(q, proj, perp)
 *
 */
TEST_F(Vec3fTest_C, TestVec3fDecomposeVec) {
    Math::Vec3f_C proj;
    Math::Vec3f_C perp;
    xyz_vec.DecomposeVec(y_axis, proj, perp);
    ASSERT_EQ(Math::Vec3f_C(0, xyz_vec.y, 0.0f), proj);
    ASSERT_EQ(Math::Vec3f_C(xyz_vec.x, 0.0f, xyz_vec.z), perp);
}

/**
 * Test Vec3f_C Perpendicular(...)
 *
 * p.Perpendicular()
 *
 */
TEST_F(Vec3fTest_C, TestVec3fPerpendicular) {
    ASSERT_EQ(z_axis, x_axis.Perpendicular(y_axis));
    ASSERT_EQ(x_axis, y_axis.Perpendicular(z_axis));
    ASSERT_EQ(y_axis, z_axis.Perpendicular(x_axis));
    ASSERT_EQ(-y_axis, x_axis.Perpendicular(z_axis));
    ASSERT_EQ(zero_vec, x_axis.Perpendicular(zero_vec));
}

/**
 * Test Vec3f_C AreSame(...)
 *
 * vec1.AreSame(vec2, eps)
 *
 */
TEST_F(Vec3fTest_C, TestVec3fAreSame) {
    ASSERT_TRUE(rand_xyz_vec.AreSame(Math::Vec3f_C(0.000034001f, 0.00005705f, 0.8750001f), 1E-5f));
    ASSERT_FALSE(rand_xyz_vec.AreSame(Math::Vec3f_C(0.000035f, 0.000056f, 0.874f)));
    ASSERT_FALSE(equal_vec.AreSame(Math::Vec3f_C(567.3453f)));
    ASSERT_TRUE(equal_vec.AreSame(Math::Vec3f_C(567.34503f)));
    ASSERT_TRUE(equal_vec.AreSame(Math::Vec3f_C(567.3453f), 1E-3f));
}

/**
 * Test Vec3f_C AreAligned(...)
 *
 * vec1.AreAligned(vec2, eps)
 *
 */
TEST_F(Vec3fTest_C, TestVec3fAreAligned) {
    ASSERT_FALSE(Math::Vec3f_C(1.0f).AreSame(Math::Vec3f_C(2.0f)));
    ASSERT_TRUE(Math::Vec3f_C(1.0f).AreAligned(Math::Vec3f_C(2.0f)));
    ASSERT_FALSE(Math::Vec3f_C(1.0f).AreAligned(Math::Vec3f_C(2.05f, 2.0f, 2.0f)));
    ASSERT_TRUE(Math::Vec3f_C(1.0f).AreAligned(Math::Vec3f_C(2.05f, 2.0499999f, 2.0499999f), 1E-4f));
}

/**
 * Test Vec3f_C IsZero(...)
 *
 * vec1.IsZero(eps)
 *
 */
TEST_F(Vec3fTest_C, TestVec3fIsZero) {
    ASSERT_TRUE(zero_vec.IsZero());
    ASSERT_FALSE(rand_xyz_vec.IsZero());
    ASSERT_FALSE(Math::Vec3f_C(1.0f).IsZero(1E-5f));
}

/**
 * Test Vec3f_C IsNormalized(...)
 *
 * vec1.IsNormalized(eps)
 *
 */
TEST_F(Vec3fTest_C, TestVec3fIsNormalized) {
    ASSERT_TRUE(x_axis.IsNormalized());
    ASSERT_TRUE(y_axis.IsNormalized());
    ASSERT_FALSE(xyz_vec.IsNormalized());
    ASSERT_TRUE(Math::Vec3f_C(static_cast<float>(SQRT_ONE_OVER_THREE)).IsNormalized());
}

/**
 * Test Vec3f_C IsLinearDependent(...)
 *
 * vec1.IsLinearDependent(vec2, eps)
 * p1.IsLinearDependent(p2, p3, eps)
 *
 */
TEST_F(Vec3fTest_C, TestVec3fIsLinearDependent) {
    ASSERT_FALSE(x_axis.IsLinearDependent(y_axis));
    ASSERT_FALSE(x_axis.IsLinearDependent(z_axis));
    ASSERT_TRUE(Math::Vec3f_C(1.0f).IsLinearDependent(Math::Vec3f_C(2.0f)));
    ASSERT_TRUE(Math::Vec3f_C(0.0f).IsLinearDependent(Math::Vec3f_C(1.0f), Math::Vec3f_C(2.0f)));
}

/**
 * Test Vec3f_C ComposeSpherical(...)
 *
 * vec.ComposeSpherical(rho, theta, phi)
 *
 */
TEST_F(Vec3fTest_C, TestVec3fComposeSpherical) {
    Math::Vec3f_C test_vec;
    Math::Vec3f_C out_vec{2.0f, static_cast<float>(2.0 * SQRT_THREE), static_cast<float>(4.0 * SQRT_THREE)};
    ASSERT_TRUE(out_vec.AreSame(test_vec.ComposeSpherical(8.0f, Math::Pi<float>() / 3.0f, Math::Pi<float>() / 6.0f)));
}

/**
 * Test Vec3f_C DecomposeSpherical(...)
 *
 * vec.DecomposeSpherical(&rho, &theta, &phi)
 *
 */
TEST_F(Vec3fTest_C, TestVec3fDecomposeSpherical) {
    float rho;
    float theta;
    float phi;
    Math::Vec3f_C rect_vec{2.0f, static_cast<float>(2.0 * SQRT_THREE), static_cast<float>(4.0 * SQRT_THREE)};
    rect_vec.DecomposeSpherical(rho, theta, phi);
    ASSERT_TRUE(Math::AreSame(8.0f, rho));
    ASSERT_TRUE(Math::AreSame(Math::Pi<float>() / 3.0f, theta));
    ASSERT_TRUE(Math::AreSame(Math::Pi<float>() / 6.0f, phi));

    rect_vec = Math::Vec3f_C(-1.0f, 1.0f, Math::Sqrt(6.0f));
    rect_vec.DecomposeSpherical(rho, theta, phi);
    ASSERT_TRUE(Math::AreSame(static_cast<float>(2.0 * SQRT_TWO), rho));
    ASSERT_TRUE(Math::AreSame(3.0f * Math::QuarterPi<float>(), theta));
    ASSERT_TRUE(Math::AreSame(Math::Pi<float>() / 6.0f, phi));
}

/**
 * Test Vec3f_C ComposeCylindrical(...)
 *
 * vec.ComposeCylindrical(r, theta, z)
 *
 */
TEST_F(Vec3fTest_C, TestVec3fComposeCylindrical) {
    Math::Vec3f_C test_vec;
    Math::Vec3f_C out_vec{-2.0f, static_cast<float>(2.0 * SQRT_THREE), -2.0f};
    ASSERT_TRUE(out_vec.AreSame(test_vec.ComposeCylindrical(4.0f, Math::TwoPi<float>() / 3.0f, -2.0f)));
}

/**
 * Test Vec3f_C DecomposeCylindrical(...)
 *
 * vec.DecomposeCylindrical(&r, &theta, &z)
 *
 */
TEST_F(Vec3fTest_C, TestVec3fDecomposeCylindrical) {
    float r;
    float theta;
    float z;
    Math::Vec3f_C rect_vec{2.5f * static_cast<float>(SQRT_THREE), 2.5f, 4.0f};
    rect_vec.DecomposeCylindrical(r, theta, z);
    ASSERT_TRUE(Math::AreSame(5.0f, r));
    ASSERT_TRUE(Math::AreSame(Math::Pi<float>() / 6.0f, theta));
    ASSERT_TRUE(Math::AreSame(4.0f, z));

    rect_vec = Math::Vec3f_C(1.0f, -3.0f, 5.0f);
    rect_vec.DecomposeCylindrical(r, theta, z);
    ASSERT_TRUE(Math::AreSame(Math::Sqrt(10.0f), r));
    ASSERT_TRUE(Math::AreSame(5.03414f, theta));
    ASSERT_TRUE(Math::AreSame(5.0f, z));
}

/**
 * Test Vec3f_C Angle(...)
 *
 * vec1.Angle(vec2)
 * p1.Angle(p2, p3)
 *
 */
TEST_F(Vec3fTest_C, TestVec3fAngle) {
    ASSERT_TRUE(Math::AreSame(Math::HalfPi<float>(), x_axis.Angle(y_axis)));

    ASSERT_TRUE(Math::AreSame(54.7356071f, Math::RadToDeg(x_axis.Angle(one_vec))));

    ASSERT_TRUE(
        Math::AreSame(Math::Pi<float>() / 6.0f,
                      Math::Vec3f_C(static_cast<float>(SQRT_THREE), 1.0f, 0.0f).Angle(Math::Vec3f_C(1.0f, static_cast<float>(SQRT_THREE), 0.0f))));

    ASSERT_TRUE(
        Math::AreSame(Math::TwoPi<float>() / 3.0f,
                      Math::Vec3f_C(static_cast<float>(SQRT_THREE), 1.0f, 0.0f).Angle(Math::Vec3f_C(-static_cast<float>(SQRT_THREE), 1.0f, 0.0f))));

    ASSERT_TRUE(Math::AreSame(64.4724f, Math::RadToDeg(Math::Vec3f_C(4.0f, 0.0f, 7.0f).Angle(Math::Vec3f_C(-2.0f, 1.0f, 3.0f))), 1E-4f));
    ASSERT_TRUE(Math::AreSame(135.608f, Math::RadToDeg((Math::Vec3f_C(3.0f, 4.0f, -7.0f).Angle(Math::Vec3f_C(-2.0f, 1.0f, 3.0f)))), 1E-4f));

    ASSERT_TRUE(Math::AreSame(160.582f,
                              Math::RadToDeg((Math::Vec3f_C(0.0f).Angle(Math::Vec3f_C(2.0f, 5.0f, 4.0f), Math::Vec3f_C(-2.0f, -3.0f, -5.0f)))),
                              1E-4f));
}

/**
 * Test Vec3f_C MidPoint(...)
 *
 * Math::Vec3f_C::MidPoint(vec1, vec2)
 * vec1.MidPoint(vec2)
 *
 */
TEST_F(Vec3fTest_C, TestVec3fMidPoint) {
    ASSERT_EQ(Math::Vec3f_C(0.5f, 0.5f, 0.0f), Math::Vec3f_C::MidPoint(x_axis, y_axis));
    ASSERT_EQ(Math::Vec3f_C(0.5f, 0.5f, 0.0f), x_axis.MidPoint(y_axis));
}

/**
 * Test Vec3f_C Lerp(...)
 *
 * Math::Vec3f_C::Lerp(vec1, vec2, t)
 * vec1.Lerp(vec2, t)
 *
 */
TEST_F(Vec3fTest_C, TestVec3fLerp) {
    ASSERT_EQ(Math::Vec3f_C(0.5f, 0.5f, 0.0f), Math::Vec3f_C::Lerp(x_axis, y_axis, 0.5f));
    ASSERT_EQ(x_axis, Math::Vec3f_C::Lerp(x_axis, y_axis, 0.0f));
    ASSERT_EQ(y_axis, Math::Vec3f_C::Lerp(x_axis, y_axis, 1.0f));
    ASSERT_EQ(y_axis, x_axis.Lerp(y_axis, 1.0f));
}
/**
 * Test Vec3f_C addition
 *
 */
TEST_F(Vec3fTest_C, TestVec3fAddition) {
    float scalar = 2.0f;
    Math::Vec3f_C test_vec = zero_vec;

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
 * Test Vec3f_C subtraction
 */
TEST_F(Vec3fTest_C, TestVec3fSubtraction) {
    float scalar = 2.45f;
    Math::Vec3f_C test_vec = zero_vec;

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
 * Test Vec3f_C multiplication
 */
TEST_F(Vec3fTest_C, TestVec3fMultiplication) {
    float scalar = 0.000045f;
    Math::Vec3f_C test_vec = one_vec;

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
 * Test Vec3f_C division
 */
TEST_F(Vec3fTest_C, TestVec3fDivision) {
    float scalar = 45.345f;
    Math::Vec3f_C test_vec = one_vec;

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
 * Test Vec3f_C comparison
 */
TEST_F(Vec3fTest_C, TestVec3fComparison) {
    Math::Vec3f_C test_vec_equal = xyz_vec;
    Math::Vec3f_C test_vec_less = xyz_vec - 2.0f;
    Math::Vec3f_C test_vec_greater = xyz_vec + 2.0f;
    ASSERT_TRUE(xyz_vec > test_vec_less);
    ASSERT_TRUE(xyz_vec < test_vec_greater);
    ASSERT_TRUE(xyz_vec == test_vec_equal);
    ASSERT_TRUE(xyz_vec != test_vec_less);
    ASSERT_TRUE(xyz_vec != test_vec_greater);
}

/**
 * Test Vec3f_C assignment
 */
TEST_F(Vec3fTest_C, TestVec3fAssignment) {
    Math::Vec3f_C test_vec;
    ASSERT_EQ(xyz_vec, test_vec = xyz_vec);
}

/**
 * Test Vec3f_C specific component
 */
TEST_F(Vec3fTest_C, TestVec3fComponent) {
    float value;
    ASSERT_EQ(xyz_vec.x, xyz_vec[0]);
    ASSERT_EQ(xyz_vec.y, xyz_vec[1]);
    ASSERT_EQ(xyz_vec.z, xyz_vec[2]);
    ASSERT_EQ(xyz_vec.y, value = xyz_vec[1]);
}

/**
 * Test Vec3f_C inverted vector
 */
TEST_F(Vec3fTest_C, TestVec3fInverted) {
    ASSERT_EQ(-glm::vec3(xyz_vec), -xyz_vec);
}

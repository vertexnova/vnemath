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

#include <gtest/gtest.h>

#include "vertexnova/math/math_utils.h"
#include "vertexnova/math/vec2f.h"

using namespace VNE;

class Vec2fTest_C : public ::testing::Test {
    // Interface of test fixture base class
   protected:
    void SetUp() override {
        neg_xy_vec = Math::Vec2f_C(-2.0f, 14.5f);
        zero_vec = Math::Vec2f_C();
        one_vec = Math::Vec2f_C(1.0f, 1.0f);
        xy_vec = Math::Vec2f_C(3.0f, 4.0f);
        x_axis = Math::Vec2f_C(1.0f, 0.0f);
        y_axis = Math::Vec2f_C(0.0f, 1.0f);
        equal_vec = Math::Vec2f_C(567.345f);
        rand_xy_vec = Math::Vec2f_C(0.000034f, 0.000057f);

        x_point = Math::Vec2f_C(1.0f, 0.0f);
        y_point = Math::Vec2f_C(0.0f, 1.0f);
        xy_point = Math::Vec2f_C(1.0f, 1.0f);
    }

    void TearDown() override {}

   protected:
    Math::Vec2f_C zero_vec;
    Math::Vec2f_C one_vec;
    Math::Vec2f_C xy_vec;
    Math::Vec2f_C x_axis;
    Math::Vec2f_C y_axis;
    Math::Vec2f_C equal_vec;
    Math::Vec2f_C neg_xy_vec;
    Math::Vec2f_C rand_xy_vec;
    Math::Vec2f_C x_point;
    Math::Vec2f_C y_point;
    Math::Vec2f_C xy_point;
};

/**
 * Test Vec2f_C dimensions
 *
 */
TEST_F(Vec2fTest_C, TestVec2fDimensions) {
    ASSERT_EQ(2, Math::Vec2f_C::Dim());
    ASSERT_EQ(2, Math::Vec2f_C::Size());
    ASSERT_NE(3, Math::Vec2f_C::Dim());
    ASSERT_NE(6, Math::Vec2f_C::Size());
}

/**
 * Test Vec2f_C zero vector
 */
TEST_F(Vec2fTest_C, TestVec2fZero) {
    ASSERT_EQ(glm::vec2(0.0f, 0.0f), zero_vec);
    ASSERT_EQ(zero_vec, Math::Vec2f_C::Zero());
}

/**
 * Test Vec2f_C one vector
 */
TEST_F(Vec2fTest_C, TestVec2fOne) {
    ASSERT_EQ(glm::vec2(1.0f, 1.0f), one_vec);
    ASSERT_EQ(one_vec, Math::Vec2f_C::One());
}

/**
 * Test Vec2f_C x-axis
 */
TEST_F(Vec2fTest_C, TestVec2fXAxis) {
    ASSERT_EQ(glm::vec2(1.0f, 0.0f), x_axis);
    ASSERT_EQ(x_axis, Math::Vec2f_C::XAxis());
}

/**
 * Test Vec2f_C y-axis
 */
TEST_F(Vec2fTest_C, TestVec2fYAxis) {
    ASSERT_EQ(glm::vec2(0.0f, 1.0f), y_axis);
    ASSERT_EQ(y_axis, Math::Vec2f_C::YAxis());
}

/**
 * Test Vec2f_C Length and LengthSquare
 */
TEST_F(Vec2fTest_C, TestVec2fLength) {
    ASSERT_EQ(glm::length(glm::vec2(0.0f, 0.0f)), zero_vec.Length());
    ASSERT_EQ(glm::length(glm::vec2(1.0f, 1.0f)), one_vec.Length());
    ASSERT_EQ(glm::length(glm::vec2(0.0f, 0.0f)), zero_vec.LengthSquare());
    ASSERT_EQ(glm::length2(glm::vec2(1.0f, 1.0f)), one_vec.LengthSquare());
    ASSERT_EQ(glm::length2(glm::vec2(xy_vec)), xy_vec.LengthSquare());
}

/**
 * Test Vec2f_C GetPtr
 *
 * vec.GetPtr()
 *
 */
TEST_F(Vec2fTest_C, TestVec2fGetPtr) {
    ASSERT_EQ(xy_vec.x, *(xy_vec.GetPtr()));
    ASSERT_EQ(xy_vec.y, *(xy_vec.GetPtr() + 1));
    ASSERT_EQ(x_axis.x, *(x_axis.GetPtr()));
    ASSERT_EQ(x_axis.y, *(x_axis.GetPtr() + 1));
}

/**
 * Test Vec2f_C Abs
 *
 * vec.Abs()
 *
 */
TEST_F(Vec2fTest_C, TestVec2fAbs) {
    ASSERT_EQ(glm::abs(glm::vec2(neg_xy_vec)), neg_xy_vec.Abs());
}

/**
 * Test Vec2f_C Normalize
 *
 * vec.Normalize()
 *
 */
TEST_F(Vec2fTest_C, TestVec2fNormalize) {
    ASSERT_TRUE(x_axis == x_axis.Normalize());
    ASSERT_TRUE(y_axis == y_axis.Normalize());
    ASSERT_TRUE(x_axis == Math::Vec2f_C::Normalized(x_axis));
    ASSERT_TRUE(y_axis == Math::Vec2f_C::Normalized(y_axis));
    ASSERT_EQ(glm::normalize(glm::vec2(xy_vec)), xy_vec.Normalize());
#ifdef _DEBUG
    ASSERT_DEATH(zero_vec.Normalize(), ".*");
#endif  // _DEBUG
}

/**
 * Test Vec2f_C Min(...)
 *
 * vec1.Min(vec2)
 *
 */
TEST_F(Vec2fTest_C, TestVec2fMin) {
    ASSERT_TRUE(zero_vec == one_vec.Min(zero_vec));
    ASSERT_TRUE(xy_vec == neg_xy_vec.Min(xy_vec));
}

/**
 * Test Vec2f_C Max(...)
 *
 * vec1.Max(vec2)
 *
 */
TEST_F(Vec2fTest_C, TestVec2fMax) {
    ASSERT_TRUE(one_vec == one_vec.Max(zero_vec));
    ASSERT_TRUE(neg_xy_vec == neg_xy_vec.Max(xy_vec));
}

/**
 * Test Vec2f_C MinComponent(...)
 *
 * vec.MinComponent()
 *
 */
TEST_F(Vec2fTest_C, TestVec2fMinComponent) {
    ASSERT_TRUE(neg_xy_vec.x == neg_xy_vec.MinComponent());
}

/**
 * Test Vec2f_C MaxComponent(...)
 *
 * vec.MaxComponent()
 *
 */
TEST_F(Vec2fTest_C, TestVec2fMaxComponent) {
    ASSERT_TRUE(neg_xy_vec.y == neg_xy_vec.MaxComponent());
}

/**
 * Test Vec2f_C Dot(...)
 *
 * dot = vec1.Dot(vec2)
 * dot = Math::Vec2f_C::Dot(vec1, vec2)
 *
 */
TEST_F(Vec2fTest_C, TestVec2fDot) {
    ASSERT_EQ(0.0f, x_axis.Dot(y_axis));
    ASSERT_EQ(3.0f, xy_vec.Dot(x_axis));
    ASSERT_EQ(4.0f, xy_vec.Dot(y_axis));
    ASSERT_EQ(7.0f, xy_vec.Dot(one_vec));
    ASSERT_EQ(7.0f, Math::Vec2f_C::Dot(xy_vec, one_vec));
    ASSERT_FLOAT_EQ(Math::HalfPi<float>(), Math::ACos(x_axis.Dot(y_axis) / (x_axis.Length() * y_axis.Length())));
}

/**
 * Test Vec2f_C Cross product.
 *
 * cross = vec1.Cross(vec2)
 * cross = Math::Vec2f_C::Cross(vec1, vec2)
 *
 */
TEST_F(Vec2fTest_C, TestVec2fCross) {
    ASSERT_EQ(1.0f, x_axis.Cross(y_axis));
    ASSERT_EQ(1.0f, Math::Vec2f_C::Cross(x_axis, y_axis));
    ASSERT_EQ(glm::cross(glm::vec3(x_axis, 0.0f), glm::vec3(y_axis, 0.0f)).z, Math::Vec2f_C::Cross(x_axis, y_axis));
}

/**
 * Test Vec2f_C Distance calculation.
 *
 * dist = vec1.Distance(vec2)
 * dist = Math::Vec2f_C::Distance(vec1, vec2)
 *
 */
TEST_F(Vec2fTest_C, TestVec2fDistance) {
    ASSERT_FLOAT_EQ(static_cast<float>(SQRT_TWO), Math::Vec2f_C::Distance(x_point, y_point));
    ASSERT_FLOAT_EQ(static_cast<float>(SQRT_TWO), Math::Vec2f_C::Distance(Math::Vec2f_C::Zero(), xy_point));
    ASSERT_FLOAT_EQ(1.0f, Math::Vec2f_C::Distance(x_point, xy_point));
    ASSERT_FLOAT_EQ(1.0f, xy_point.Distance(y_point));
}

/**
 * Test Vec2f_C Rotate function.
 *
 * vec.Rotate(axis, angle)
 *
 */
TEST_F(Vec2fTest_C, TestVec2fRotate) {
    Math::Vec2f_C test_vec;

    ASSERT_TRUE(x_axis.AreSame(test_vec.Rotate(y_axis, static_cast<float>(-HALF_PI))));
    ASSERT_TRUE(y_axis.AreSame(test_vec.Rotate(x_axis, static_cast<float>(HALF_PI))));
    Math::Vec2f_C out_vec = Math::Vec2f_C(0.0f, 1.41421f);
    ASSERT_TRUE(out_vec.AreSame(test_vec.Rotate(one_vec, static_cast<float>(QUARTER_PI)), 1E-5f));
}

/**
 * Test Vec2f_C Reflect(...)
 *
 * vec.Reflect(normal)
 *
 */
TEST_F(Vec2fTest_C, TestVec2fReflect) {
    Math::Vec2f_C test_vec;
    test_vec.x = -xy_vec.x;
    test_vec.y = xy_vec.y;
    ASSERT_TRUE(test_vec.AreSame(-xy_vec.Reflect(y_axis)));
}

/**
 * Test Vec2f_C Refract(...)
 *
 * vec.Refract(normal, mu)
 *
 */
TEST_F(Vec2fTest_C, TestVec2fRefract) {
    xy_vec.Normalize();
    Math::Vec2f_C test_vec;
    test_vec.x = -xy_vec.x;
    test_vec.y = xy_vec.y;
    ASSERT_TRUE(test_vec.AreSame(-xy_vec.Refract(y_axis, 1.0f)));
    ASSERT_TRUE(y_axis.AreSame(-xy_vec.Refract(y_axis, 0.0f)));

    Math::Vec2f_C out_vec{-1.5f, 2.17945f};
    ASSERT_TRUE(out_vec.AreSame(-xy_vec.Refract(y_axis, 0.5f), 1E-5f));
}

/**
 * Test Vec2f_C Project(...)
 *
 * vec1.Project(vec2)
 *
 */
TEST_F(Vec2fTest_C, TestVec2fProject) {
    ASSERT_EQ(zero_vec, x_axis.Project(y_axis));  // perpendicular vectors
    ASSERT_EQ(Math::Vec2f_C(0, xy_vec.y), xy_vec.Project(y_axis));
    // Second vector could be any vector ( normal is not compulsory )
    ASSERT_EQ(Math::Vec2f_C(0, xy_vec.y), xy_vec.Project(Math::Vec2f_C(0.0f, 3.0f)));
    // Perpendicular vector of xy_vec w.r.t. y_axis
    ASSERT_EQ(Math::Vec2f_C(xy_vec.x, 0.0f), xy_vec - xy_vec.Project(y_axis));
}

/**
 * Test Vec2f_C Reject(...)
 *
 * vec1.Reject(vec2)
 *
 */
TEST_F(Vec2fTest_C, TestVec2fReject) {
    // Perpendicular vector of xy_vec w.r.t. y_axis
    ASSERT_EQ(Math::Vec2f_C(xy_vec.x, 0.0f), xy_vec - xy_vec.Project(y_axis));
    ASSERT_EQ(Math::Vec2f_C(xy_vec.x, 0.0f), xy_vec.Reject(y_axis));
}

/**
 * Test Vec2f_C Decompose(...)
 *
 * p.Decompose(q, proj, perp)
 *
 */
TEST_F(Vec2fTest_C, TestVec2fDecomposeVec) {
    Math::Vec2f_C proj;
    Math::Vec2f_C perp;
    xy_vec.DecomposeVec(y_axis, proj, perp);
    ASSERT_EQ(Math::Vec2f_C(0, xy_vec.y), proj);
    ASSERT_EQ(Math::Vec2f_C(xy_vec.x, 0.0f), perp);
}

/**
 * Test Vec2f_C Perpendicular(...)
 *
 * p.Perpendicular()
 *
 */
TEST_F(Vec2fTest_C, TestVec2fPerpendicular) {
    ASSERT_EQ(y_axis, x_axis.Perpendicular());
    ASSERT_EQ(-x_axis, y_axis.Perpendicular());
    ASSERT_EQ(-y_axis, -x_axis.Perpendicular());
    ASSERT_EQ(x_axis, -y_axis.Perpendicular());
}

/**
 * Test Vec2f_C AreSame(...)
 *
 * vec1.AreSame(vec2, eps)
 *
 */
TEST_F(Vec2fTest_C, TestVec2fAreSame) {
    ASSERT_TRUE(rand_xy_vec.AreSame(0.000034001f, 0.00005705f));
    ASSERT_TRUE(rand_xy_vec.AreSame(0.000035f, 0.000037f));
    ASSERT_FALSE(equal_vec.AreSame(Math::Vec2f_C(567.3453f)));
    ASSERT_TRUE(equal_vec.AreSame(Math::Vec2f_C(567.34503f)));
    ASSERT_TRUE(equal_vec.AreSame(Math::Vec2f_C(567.3453f), 1E-3f));
#ifdef _DEBUG
    ASSERT_DEATH(equal_vec.AreSame(Math::Vec2f_C(567.3453f), 0.0f),
                 ".* Assertion Failed: eps >= FLOAT_EPSILON :: eps cannot be "
                 "less than FLOAT_EPSILON.*");
#endif  // _DEBUG
}

/**
 * Test Vec2f_C AreAligned(...)
 *
 * vec1.AreAligned(vec2, eps)
 *
 */
TEST_F(Vec2fTest_C, TestVec2fAreAligned) {
    ASSERT_FALSE(Math::Vec2f_C(1.0f, 1.0f).AreSame(Math::Vec2f_C(2.0f, 2.0f)));
    ASSERT_TRUE(Math::Vec2f_C(1.0f, 1.0f).AreAligned(Math::Vec2f_C(2.0f, 2.0f)));
    ASSERT_FALSE(Math::Vec2f_C(1.0f, 1.0f).AreAligned(Math::Vec2f_C(2.05f, 2.0f)));
    ASSERT_TRUE(Math::Vec2f_C(1.0f, 1.0f).AreAligned(Math::Vec2f_C(2.05f, 2.0499999f), 1E-4f));
}

/**
 * Test Vec2f_C IsZero(...)
 *
 * vec1.IsZero(eps)
 *
 */
TEST_F(Vec2fTest_C, TestVec2fIsZero) {
    ASSERT_TRUE(zero_vec.IsZero());
    ASSERT_FALSE(rand_xy_vec.IsZero());
    ASSERT_TRUE(rand_xy_vec.IsZero(1E-4f));
#ifdef _DEBUG
    ASSERT_DEATH(zero_vec.IsZero(0.0f),
                 ".* Assertion Failed: eps >= FLOAT_EPSILON :: eps cannot be "
                 "less than FLOAT_EPSILON.*");
#endif  // _DEBUG
}

/**
 * Test Vec2f_C IsNormalized(...)
 *
 * vec1.IsNormalized(eps)
 *
 */
TEST_F(Vec2fTest_C, TestVec2fIsNormalized) {
    ASSERT_TRUE(x_axis.IsNormalized());
    ASSERT_TRUE(y_axis.IsNormalized());
    ASSERT_FALSE(xy_vec.IsNormalized());
    ASSERT_TRUE(Math::Vec2f_C(static_cast<float>(SQRT_ONE_OVER_TWO), static_cast<float>(SQRT_ONE_OVER_TWO)).IsNormalized());
}

/**
 * Test Vec2f_C ComposePolar(...)
 *
 * vec.ComposePolar(radius, angle)
 *
 */
TEST_F(Vec2fTest_C, TestVec2fComposePolar) {
    Math::Vec2f_C test_vec;
    ASSERT_TRUE(one_vec.AreSame(test_vec.ComposePolar(static_cast<float>(SQRT_TWO), Math::QuarterPi<float>())));
}

/**
 * Test Vec2f_C DecomposePolar(...)
 *
 * vec.DecomposePolar(radius, angle)
 *
 */
TEST_F(Vec2fTest_C, TestVec2fDecomposePolar) {
    float radius;
    float angle;
    one_vec.DecomposePolar(radius, angle);
    ASSERT_TRUE(Math::AreSame(static_cast<float>(SQRT_TWO), radius));
    ASSERT_TRUE(Math::AreSame(Math::QuarterPi<float>(), angle));
    // For the negative angle
    Math::Vec2f_C test_vec{-1.0f, -1.0f};
    test_vec.DecomposePolar(radius, angle);
    ASSERT_TRUE(Math::AreSame(static_cast<float>(SQRT_TWO), radius));
    ASSERT_TRUE(Math::AreSame(5.0f * Math::QuarterPi<float>(), angle));
}

/**
 * Test Vec2f_C Angle(...)
 *
 * vec.Angle()
 * vec1.Angle(vec2)
 * vec1.Angle(point1, point2)
 *
 */
TEST_F(Vec2fTest_C, TestVec2fAngle) {
    ASSERT_TRUE(Math::AreSame(Math::HalfPi<float>(), y_axis.Angle()));
    ASSERT_TRUE(Math::AreSame(Math::HalfPi<float>(), x_axis.Angle(y_axis)));
    ASSERT_TRUE(Math::AreSame(Math::QuarterPi<float>(), one_vec.Angle()));
    ASSERT_TRUE(Math::AreSame(Math::QuarterPi<float>(), x_axis.Angle(one_vec)));

    ASSERT_TRUE(Math::AreSame(Math::Pi<float>() / 6.0f,
                              Math::Vec2f_C(static_cast<float>(SQRT_THREE), 1.0f).Angle(Math::Vec2f_C(1.0f, static_cast<float>(SQRT_THREE)))));
    ASSERT_TRUE(Math::AreSame(Math::TwoPi<float>() / 3.0f,
                              Math::Vec2f_C(static_cast<float>(SQRT_THREE), 1.0f).Angle(Math::Vec2f_C(-static_cast<float>(SQRT_THREE), 1.0f))));
    ASSERT_TRUE(Math::AreSame((3.0f / 8.0f) * Math::TwoPi<float>(), Math::Vec2f_C(1.0f, 1.0f).Angle(Math::Vec2f_C(-2.0f, 0.0f))));
    ASSERT_TRUE(Math::AreSame(3.0f * Math::HalfPi<float>(), Math::Vec2f_C(1.0f, 1.0f).Angle(Math::Vec2f_C(1.0f, -1.0f))));

    ASSERT_TRUE(Math::AreSame(3.0f * Math::HalfPi<float>(), Math::Vec2f_C(2.0f, 0.0f).Angle(Math::Vec2f_C(4.0f, 2.0f), Math::Vec2f_C(4.0f, -2.0f))));
}

/**
 * Test Vec2f_C MidPoint(...)
 *
 * Math::Vec2f_C::MidPoint(vec1, vec2)
 * vec1.MidPoint(vec2)
 *
 */
TEST_F(Vec2fTest_C, TestVec2fMidPoint) {
    ASSERT_EQ(Math::Vec2f_C(0.5f, 0.5f), Math::Vec2f_C::MidPoint(x_axis, y_axis));
    ASSERT_EQ(Math::Vec2f_C(0.5f, 0.5f), x_axis.MidPoint(y_axis));
}

/**
 * Test Vec2f_C Lerp(...)
 *
 * Math::Vec2f_C::Lerp(vec1, vec2, t)
 * vec1.Lerp(vec2, t)
 *
 */
TEST_F(Vec2fTest_C, TestVec2fLerp) {
    ASSERT_EQ(Math::Vec2f_C(0.5f, 0.5f), Math::Vec2f_C::Lerp(x_axis, y_axis, 0.5f));
    ASSERT_EQ(x_axis, Math::Vec2f_C::Lerp(x_axis, y_axis, 0.0f));
    ASSERT_EQ(y_axis, Math::Vec2f_C::Lerp(x_axis, y_axis, 1.0f));
    ASSERT_EQ(y_axis, x_axis.Lerp(y_axis, 1.0f));
}

/**
 * Test Vec2f_C addition
 *
 */
TEST_F(Vec2fTest_C, TestVec2fAddition) {
    float scalar = 2.0f;
    Math::Vec2f_C test_vec = zero_vec;

    // 1. Compare zero_vec + one_vec
    ASSERT_EQ(glm::vec2(zero_vec) + glm::vec2(one_vec), glm::vec2(zero_vec + one_vec));

    // 2. Test the += operation on test_vec
    test_vec += one_vec;
    ASSERT_EQ(glm::vec2(one_vec), glm::vec2(test_vec));  // Updated for clarity

    // 3. Compare neg_xy_vec + scalar
    ASSERT_EQ(glm::vec2(neg_xy_vec) + glm::vec2(scalar, scalar), glm::vec2(neg_xy_vec + scalar));

    // 4. Test the += operation with scalar on test_vec
    test_vec += scalar;
    ASSERT_EQ(glm::vec2(one_vec) + glm::vec2(scalar, scalar), glm::vec2(test_vec));  // Ensure correct scalar addition

    // 5. Chain operations: test_vec + xy_vec + scalar
    Math::Vec2f_C chained_vec = test_vec + xy_vec + scalar;
    ASSERT_EQ(glm::vec2(test_vec) + glm::vec2(xy_vec) + glm::vec2(scalar, scalar), glm::vec2(chained_vec));

    // 6. Chain operations with random vector
    Math::Vec2f_C final_vec = test_vec + xy_vec + scalar + rand_xy_vec;
    ASSERT_EQ(glm::vec2(test_vec) + glm::vec2(xy_vec) + glm::vec2(scalar, scalar) + glm::vec2(rand_xy_vec), glm::vec2(final_vec));
}

/**
 * Test Vec2f_C subtraction
 */
TEST_F(Vec2fTest_C, TestVec2fSubtraction) {
    float scalar = 2.45f;
    Math::Vec2f_C test_vec = zero_vec;

    // 1. Subtract one_vec from neg_xy_vec
    ASSERT_EQ(glm::vec2(neg_xy_vec) - glm::vec2(one_vec), glm::vec2(neg_xy_vec - one_vec));

    // 2. Subtract neg_xy_vec from test_vec using -= operator
    test_vec -= neg_xy_vec;
    ASSERT_EQ(glm::vec2(zero_vec) - glm::vec2(neg_xy_vec), glm::vec2(test_vec));

    // 3. Subtract scalar from neg_xy_vec
    ASSERT_EQ(glm::vec2(neg_xy_vec) - glm::vec2(scalar, scalar), glm::vec2(neg_xy_vec - scalar));

    // 4. Subtract scalar from test_vec using -= operator
    test_vec -= scalar;
    ASSERT_EQ(glm::vec2(zero_vec) - glm::vec2(neg_xy_vec) - glm::vec2(scalar, scalar), glm::vec2(test_vec));

    // 5. Subtract xy_vec and add scalar to test_vec
    ASSERT_EQ(glm::vec2(test_vec) - glm::vec2(xy_vec) + glm::vec2(scalar, scalar), glm::vec2(test_vec - xy_vec + scalar));
}

/**
 * Test Vec2f_C multiplication
 */
TEST_F(Vec2fTest_C, TestVec2fMultiplication) {
    float scalar = 0.000045f;
    Math::Vec2f_C test_vec = one_vec;

    // 1. Multiply xy_vec by test_vec
    ASSERT_EQ(glm::vec2(xy_vec) * glm::vec2(test_vec), glm::vec2(xy_vec * test_vec));

    // 2. Multiply test_vec by xy_vec using *= operator
    test_vec *= xy_vec;
    ASSERT_EQ(glm::vec2(one_vec) * glm::vec2(xy_vec), glm::vec2(test_vec));

    // 3. Multiply test_vec by scalar
    ASSERT_EQ(glm::vec2(test_vec) * glm::vec2(scalar, scalar), glm::vec2(test_vec * scalar));

    // 4. Multiply test_vec by scalar using *= operator
    test_vec *= scalar;
    ASSERT_EQ(glm::vec2(one_vec) * glm::vec2(xy_vec) * glm::vec2(scalar, scalar), glm::vec2(test_vec));
}

/**
 * Test Vec2f_C division
 */
TEST_F(Vec2fTest_C, TestVec2fDivision) {
    float scalar = 45.345f;
    Math::Vec2f_C test_vec = one_vec;

    // 1. Divide xy_vec by test_vec
    ASSERT_EQ(glm::vec2(xy_vec) / glm::vec2(test_vec), glm::vec2(xy_vec / test_vec));

    // 2. Divide test_vec by xy_vec using /= operator
    test_vec /= xy_vec;
    ASSERT_EQ(glm::vec2(one_vec) / glm::vec2(xy_vec), glm::vec2(test_vec));

    // 3. Divide test_vec by scalar
    ASSERT_EQ(glm::vec2(test_vec) / glm::vec2(scalar, scalar), glm::vec2(test_vec / scalar));

    // 4. Divide test_vec by scalar using /= operator
    test_vec /= scalar;
    ASSERT_EQ(glm::vec2(one_vec) / glm::vec2(xy_vec) / glm::vec2(scalar, scalar), glm::vec2(test_vec));
}

/**
 * Test Vec2f_C comparison
 */
TEST_F(Vec2fTest_C, TestVec2fComparison) {
    Math::Vec2f_C test_vec_equal = xy_vec;
    Math::Vec2f_C test_vec_less = xy_vec - 2.0f;
    Math::Vec2f_C test_vec_greater = xy_vec + 2.0f;
    ASSERT_TRUE(xy_vec > test_vec_less);
    ASSERT_TRUE(xy_vec < test_vec_greater);
    ASSERT_TRUE(xy_vec == test_vec_equal);
    ASSERT_TRUE(xy_vec != test_vec_less);
    ASSERT_TRUE(xy_vec != test_vec_greater);
}

/**
 * Test Vec2f_C assignment
 */
TEST_F(Vec2fTest_C, TestVec2fAssignment) {
    Math::Vec2f_C test_vec;
    ASSERT_EQ(xy_vec, test_vec = xy_vec);
}

/**
 * Test Vec2f_C specific component
 */
TEST_F(Vec2fTest_C, TestVec2fComponent) {
    float value;
    ASSERT_EQ(xy_vec.x, xy_vec[0]);
    ASSERT_EQ(xy_vec.y, xy_vec[1]);
    ASSERT_EQ(xy_vec.y, value = xy_vec[1]);
#ifdef _DEBUG
    ASSERT_DEATH(xy_vec[2], ".*");
#endif  // _DEBUG
}
/**
 * Test Vec2f_C inverted vector
 */
TEST_F(Vec2fTest_C, TestVec2fInverted) {
    ASSERT_EQ(-glm::vec2(xy_vec), -xy_vec);
}

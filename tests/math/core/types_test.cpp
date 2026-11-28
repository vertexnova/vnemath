/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 * ----------------------------------------------------------------------
 */

#include <gtest/gtest.h>

#include "vertexnova/math/core/types.h"
#include "vertexnova/math/core/vec.h"

#include <cmath>
#include <limits>

using namespace vne::math;

TEST(TypesTest, KEpsilonSpecializations) {
    EXPECT_FLOAT_EQ(kEpsilon<float>, 1e-6f);
    EXPECT_DOUBLE_EQ(kEpsilon<double>, 1e-12);
}

TEST(TypesTest, DefaultEpsilonMatchesKEpsilonForFloat) {
    EXPECT_FLOAT_EQ(defaultEpsilon<float>(), kEpsilon<float>);
    EXPECT_DOUBLE_EQ(defaultEpsilon<double>(), kEpsilon<double>);
}

TEST(TypesTest, DefaultEpsilonIsZeroForIntegral) {
    EXPECT_EQ(defaultEpsilon<int>(), 0);
}

TEST(TypesTest, ApproxEqualWithinAbsoluteEpsilon) {
    EXPECT_TRUE(approxEqual(1.0f, 1.0f + 5e-7f));
    EXPECT_FALSE(approxEqual(1.0f, 1.0f + 2e-6f));
    EXPECT_TRUE(approxEqual(1.0, 1.0 + 5e-13, 1e-12));
    EXPECT_FALSE(approxEqual(1.0, 1.0 + 2e-12, 1e-12));
}

TEST(TypesTest, ApproxEqualWithCustomEpsilon) {
    EXPECT_TRUE(approxEqual(10.0f, 10.5f, 1.0f));
    EXPECT_FALSE(approxEqual(10.0f, 11.5f, 1.0f));
}

TEST(TypesTest, ZeroVectorNormalizedIsZero) {
    Vec3f zero = Vec3f::zero().normalized();
    EXPECT_TRUE(std::isfinite(zero.x()));
    EXPECT_TRUE(std::isfinite(zero.y()));
    EXPECT_TRUE(std::isfinite(zero.z()));
    EXPECT_TRUE(zero.areSame(Vec3f::zero()));
}

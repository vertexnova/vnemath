/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 * ----------------------------------------------------------------------
 */

#include <gtest/gtest.h>

#include "vertexnova/math/core/constants.h"
#include "vertexnova/math/core/types.h"

#include <cmath>

using namespace vne::math;

TEST(ConstantsTest, PiMatchesTemplatedPi) {
    EXPECT_NEAR(static_cast<double>(kPi), static_cast<double>(kPiT<float>), 1e-6);
    EXPECT_NEAR(kPiDouble, kPiT<double>, 1e-15);
}

TEST(ConstantsTest, TwoPiAndHalfPiConsistent) {
    EXPECT_NEAR(static_cast<double>(kTwoPi), static_cast<double>(2.0f * kPi), 1e-6);
    EXPECT_NEAR(static_cast<double>(kHalfPi), static_cast<double>(0.5f * kPi), 1e-6);
    EXPECT_NEAR(static_cast<double>(kQuarterPi), static_cast<double>(0.25f * kPi), 1e-6);
}

TEST(ConstantsTest, ReciprocalPi) {
    EXPECT_NEAR(static_cast<double>(kOneOverPi), 1.0 / static_cast<double>(kPi), 1e-6);
    EXPECT_NEAR(static_cast<double>(kOneOverTwoPi), 1.0 / static_cast<double>(kTwoPi), 1e-6);
}

TEST(ConstantsTest, SqrtConstants) {
    EXPECT_NEAR(static_cast<double>(kSqrtTwo), std::sqrt(2.0), 1e-6);
    EXPECT_NEAR(static_cast<double>(kSqrtThree), std::sqrt(3.0), 1e-6);
    EXPECT_NEAR(static_cast<double>(kSqrtOneOverTwo), 1.0 / std::sqrt(2.0), 1e-6);
}

TEST(ConstantsTest, EulerConstants) {
    EXPECT_NEAR(static_cast<double>(kE), std::exp(1.0), 1e-6);
    EXPECT_NEAR(static_cast<double>(kLn2), std::log(2.0), 1e-6);
    EXPECT_NEAR(static_cast<double>(kLn10), std::log(10.0), 1e-6);
}

TEST(ConstantsTest, FloatLimitsMatchStd) {
    EXPECT_EQ(kFloatInfinity, std::numeric_limits<float>::infinity());
    EXPECT_EQ(kFloatEpsilon, std::numeric_limits<float>::epsilon());
    EXPECT_EQ(kFloatMax, std::numeric_limits<float>::max());
    EXPECT_TRUE(std::isnan(kFloatNan));
}

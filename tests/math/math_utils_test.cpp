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
#include "vertexnova/math/core/math_utils.h"

// Third-party headers
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/extended_min_max.hpp>

using namespace vne;

class MathUtilsTest : public ::testing::Test {
    // Interface of test fixture base class
   protected:
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////
//                              Constants                                 //
// /////////////////////////////////////////////////////////////////////////

/**
 * Test Math pi constants
 */
TEST_F(MathUtilsTest, TestMathPIConstant) {
    ASSERT_FLOAT_EQ(glm::pi<float>(), vne::math::kPiT<float>);
    ASSERT_DOUBLE_EQ(glm::pi<double>(), vne::math::kPiT<double>);
    ASSERT_FLOAT_EQ(glm::two_pi<float>(), vne::math::kTwoPiT<float>);
    ASSERT_DOUBLE_EQ(glm::two_pi<double>(), vne::math::kTwoPiT<double>);
    ASSERT_FLOAT_EQ(glm::half_pi<float>(), vne::math::kHalfPiT<float>);
    ASSERT_DOUBLE_EQ(glm::half_pi<double>(), vne::math::kHalfPiT<double>);
    ASSERT_FLOAT_EQ(glm::quarter_pi<float>(), vne::math::kQuarterPiT<float>);
    ASSERT_DOUBLE_EQ(glm::quarter_pi<double>(), vne::math::kQuarterPiT<double>);
    ASSERT_FLOAT_EQ(glm::one_over_pi<float>(), vne::math::kOneOverPiT<float>);
    ASSERT_DOUBLE_EQ(glm::one_over_pi<double>(), vne::math::kOneOverPiT<double>);
    ASSERT_FLOAT_EQ(glm::one_over_two_pi<float>(), vne::math::kOneOverTwoPiT<float>);
    ASSERT_DOUBLE_EQ(glm::one_over_two_pi<double>(), vne::math::kOneOverTwoPiT<double>);
}

/**
 * Test Math Epsilon constants
 */
TEST_F(MathUtilsTest, TestMathGetEps) {
    // kEpsilon<T> is a comparison tolerance for math operations (1e-6 for float, 1e-12 for double)
    // kFloatEpsilon and kDoubleEpsilon are machine epsilon (std::numeric_limits<T>::epsilon())
    // These are different concepts and should not be equal
    ASSERT_FLOAT_EQ(vne::math::kEpsilon<float>, 1e-6f);
    ASSERT_DOUBLE_EQ(vne::math::kEpsilon<double>, 1e-12);
    ASSERT_FLOAT_EQ(vne::math::kFloatEpsilon, std::numeric_limits<float>::epsilon());
    ASSERT_DOUBLE_EQ(vne::math::kDoubleEpsilon, std::numeric_limits<double>::epsilon());
}

////////////////////////////////////////////////////////////////////////////
//                        Basic Operations                                 //
// /////////////////////////////////////////////////////////////////////////

/**
 * Test vne::math::radToDeg<T>(...)
 */
TEST_F(MathUtilsTest, TestMathRadToDeg) {
    ASSERT_FLOAT_EQ(glm::degrees(3.14f), vne::math::radToDeg<float>(3.14f));
    ASSERT_DOUBLE_EQ(glm::degrees(3.14), vne::math::radToDeg<double>(3.14));
    ASSERT_DOUBLE_EQ(glm::degrees(3.0), vne::math::radToDeg<double>(3));
    ASSERT_FLOAT_EQ(glm::degrees(glm::two_pi<float>()), vne::math::radToDeg<float>(vne::math::kTwoPiT<float>));
    ASSERT_FLOAT_EQ(360, vne::math::radToDeg<float>(vne::math::kTwoPiT<float>));
    ASSERT_DOUBLE_EQ(360.0, static_cast<double>(vne::math::radToDeg<float>(vne::math::kTwoPiT<float>)));
    ASSERT_NEAR(static_cast<double>(glm::degrees(1.57f)), static_cast<double>(vne::math::radToDeg<float>(1.57f)), 1E-4);
}

/**
 * Test vne::math::degToRad<T>(...)
 */
TEST_F(MathUtilsTest, DegToRadMatchesGlm) {
    ASSERT_FLOAT_EQ(glm::radians(90.0f), vne::math::degToRad<float>(90));
    ASSERT_FLOAT_EQ(glm::radians(90.0f), vne::math::degToRad<float>(90.0f));
    ASSERT_DOUBLE_EQ(glm::radians(90.0), vne::math::degToRad<double>(90));
    ASSERT_NE(glm::radians(90.0f), vne::math::degToRad<double>(90));
    ASSERT_FLOAT_EQ(glm::radians(45.35f), vne::math::degToRad<float>(45.35f));
    ASSERT_DOUBLE_EQ(glm::radians(45.305), vne::math::degToRad<double>(45.305));
}

/**
 * Test vne::math::abs<T>(...)
 */
TEST_F(MathUtilsTest, TestMathAbs) {
    ASSERT_EQ(glm::abs(-13), vne::math::abs(-13));
    ASSERT_EQ(13, vne::math::abs(-13));
    ASSERT_EQ(glm::abs(-14.98f), vne::math::abs(-14.98f));
    ASSERT_EQ(glm::abs(-18.9889), vne::math::abs(-18.9889));
    ASSERT_EQ(glm::abs(2000.2), vne::math::abs(2000.2));
    ASSERT_EQ(glm::abs(2021), vne::math::abs(-2021));
}

/**
 * Test vne::math::sign<T>(...)
 */
TEST_F(MathUtilsTest, TestMathSign) {
    ASSERT_EQ(glm::sign(-23.5f), vne::math::sign(-23.5f));
    ASSERT_EQ(glm::sign(9), vne::math::sign(9));
    ASSERT_EQ(glm::sign(0.0), vne::math::sign(0.0));
    ASSERT_EQ(-1, vne::math::sign(0.00005, 0.0001));
}

/**
 * Test vne::math::min<T>(...)
 */
TEST_F(MathUtilsTest, TestMathMin) {
    // For two values
    ASSERT_EQ(glm::min(1, 3), vne::math::min<int>(1, 3));
    ASSERT_EQ(glm::min(4.0f, 3.1f), vne::math::min<float>(4.0f, 3.1f));
    ASSERT_EQ(glm::min(24.56, 24.5555), vne::math::min<double>(24.56, 24.5555));
    // For Three values
    ASSERT_EQ(1, vne::math::min<int>(1, 13, 4));
    ASSERT_EQ(0, vne::math::min<int>(static_cast<int>(4.0f), static_cast<int>(3.1f), static_cast<int>(0.05f)));
    ASSERT_EQ(0.05f, vne::math::min<float>(4.0f, 3.1f, 0.05f));
    ASSERT_EQ(16.07, vne::math::min<double>(24.56, 24.5555, 16.07));
}

/**
 * Test vne::math::max<T>(...)
 */
TEST_F(MathUtilsTest, TestMathMax) {
    // For two values
    ASSERT_EQ(glm::max(1, 3), vne::math::max<int>(1, 3));
    ASSERT_EQ(glm::max(4.0f, 3.1f), vne::math::max<float>(4.0f, 3.1f));
    ASSERT_NE(glm::max(24.56, 24.5555), vne::math::max<float>(24.56f, 24.5555f));
    ASSERT_EQ(glm::max(24.56, 24.5555), vne::math::max<double>(24.56, 24.5555));
    // For Three values
    ASSERT_EQ(13, vne::math::max<int>(1, 13, 4));
    ASSERT_EQ(4, vne::math::max<int>(static_cast<int>(4.0f), static_cast<int>(3.1f), static_cast<int>(0.05f)));
    ASSERT_EQ(4, vne::math::max<float>(4.0f, 3.1f, 0.05f));
    ASSERT_EQ(24.56, vne::math::max<double>(24.56, 24.5555, 16.07));
}

/**
 * Test vne::math::clamp<T>(...)
 */
TEST_F(MathUtilsTest, TestMathClamp) {
    ASSERT_EQ(glm::clamp(1, 2, 3), vne::math::clamp<int>(1, 2, 3));
    ASSERT_EQ(2, vne::math::clamp<int>(1, 2, 3));
    ASSERT_EQ(glm::clamp(4, 2, 3), vne::math::clamp<int>(4, 2, 3));
    ASSERT_EQ(3, vne::math::clamp<int>(4, 2, 3));
    ASSERT_EQ(glm::clamp(4, 2, 7), vne::math::clamp<int>(4, 2, 7));
    ASSERT_EQ(4, vne::math::clamp<int>(4, 2, 7));
    ASSERT_EQ(glm::clamp(15.5f, 0.05f, 13.34f), vne::math::clamp<float>(15.5f, 0.05f, 13.34f));
    ASSERT_EQ(glm::clamp(20.34, 15.67, 30.89), vne::math::clamp<double>(20.34, 15.67, 30.89));
}

/**
 * Test vne::math::saturate<T>(...)
 */
TEST_F(MathUtilsTest, TestMathSaturate) {
    ASSERT_EQ(glm::clamp(-1, 0, 1), vne::math::saturate<int>(-1));
    ASSERT_EQ(glm::clamp(1, 0, 1), vne::math::saturate<int>(1));
    ASSERT_EQ(glm::clamp(4, 0, 1), vne::math::saturate<int>(4));
    ASSERT_EQ(glm::clamp(15.5f, 0.0f, 1.0f), vne::math::saturate<float>(15.5f));
    ASSERT_EQ(glm::clamp(20.34, 0.0, 1.0), vne::math::saturate<double>(20.34));
}

/**
 * Test vne::math::arrangeMinMax<T>(...)
 */
TEST_F(MathUtilsTest, TestMathArrangeMinMax) {
    int min_i = 3;
    int max_i = 1;
    vne::math::arrangeMinMax(&min_i, &max_i);
    ASSERT_EQ(1, min_i);
    ASSERT_EQ(3, max_i);

    float min_f = 10.34f;
    float max_f = 10.35f;
    vne::math::arrangeMinMax(&min_f, &max_f);
    ASSERT_FLOAT_EQ(10.34f, min_f);
    ASSERT_FLOAT_EQ(10.35f, max_f);

    double min_d = 20.45;
    double max_d = 20.0;
    vne::math::arrangeMinMax<double>(&min_d, &max_d);
    ASSERT_DOUBLE_EQ(20.0, min_d);
    ASSERT_DOUBLE_EQ(20.45, max_d);
}

/**
 * Test vne::math::isInBetween<T>(...)
 */
TEST_F(MathUtilsTest, TestMathIsInBetween) {
    ASSERT_FALSE(vne::math::isInBetween(1, 2, 3));
    ASSERT_TRUE(vne::math::isInBetween(2, 1, 3));
    ASSERT_TRUE(vne::math::isInBetween(2, 3, 1));
    ASSERT_TRUE(vne::math::isInBetween(0.0834f, 0.0f, 1.0f));
    ASSERT_TRUE(vne::math::isInBetween(vne::math::kDoubleMax,
                                       vne::math::kDoubleMin,
                                       vne::math::kDoubleInfinity,
                                       vne::math::kDoubleEpsilon));
}

/**
 * Test vne::math::square<T>(...)
 */
TEST_F(MathUtilsTest, TestMathSquare) {
    ASSERT_EQ(4, vne::math::square<int>(2));
    ASSERT_FLOAT_EQ(5.0625f, vne::math::square<float>(2.25f));
    ASSERT_DOUBLE_EQ(185.640625, vne::math::square<double>(13.625));
    ASSERT_NEAR(static_cast<double>(vne::math::square<float>(125.678f)), vne::math::square<double>(125.678), 1E-3);
    ASSERT_NEAR(152415765.27968, vne::math::square<double>(12345.678), 1E-5);
}

/**
 * Test vne::math::cube<T>(...)
 */
TEST_F(MathUtilsTest, TestMathCube) {
    ASSERT_EQ(27, vne::math::cube<int>(3));
    ASSERT_EQ(216, vne::math::cube<int>(6));
    ASSERT_EQ(1111 * 1111 * 1111, vne::math::cube<long int>(1111));
    ASSERT_FLOAT_EQ(2460.375f, vne::math::cube<float>(13.5f));
    ASSERT_DOUBLE_EQ(2460.375, vne::math::cube<double>(13.5));
}

/**
 * Test vne::math::invSqrt<T>(...)
 */
TEST_F(MathUtilsTest, TestMathInvSqrt) {
    ASSERT_FLOAT_EQ(glm::inversesqrt(0.0f), vne::math::invSqrt<float>(0));
    ASSERT_TRUE(std::isnan(glm::inversesqrt(-1.0f)));
    ASSERT_TRUE(std::isnan(vne::math::invSqrt<float>(-1.0f)));
    ASSERT_FLOAT_EQ(glm::inversesqrt(2.0f), vne::math::invSqrt<float>(2));
    ASSERT_FLOAT_EQ(glm::inversesqrt(3.0f), vne::math::invSqrt<float>(3));
    ASSERT_FLOAT_EQ(glm::inversesqrt(25.0f), vne::math::invSqrt(static_cast<float>(25)));
    ASSERT_DOUBLE_EQ(glm::inversesqrt(0.625), vne::math::invSqrt<double>(0.625));
}

/**
 * Test vne::math::areSame(...)
 */
TEST_F(MathUtilsTest, TestMathAreSame) {
    // Test for the float type values
    ASSERT_TRUE(vne::math::areSame(32.34f, 32.3400002f));
    ASSERT_TRUE(vne::math::areSame(32.34f, 32.3400002f, vne::math::kFloatEpsilon));
    ASSERT_FALSE(vne::math::areSame(32.34f, 32.34002f, vne::math::kFloatEpsilon));
    ASSERT_TRUE(vne::math::areSame(9999.653456f, 9999.653466f, vne::math::kFloatEpsilon));
    ASSERT_FALSE(vne::math::areSame(0.653456f, 0.653466f, vne::math::kFloatEpsilon));
    ASSERT_TRUE(vne::math::areSame(0.653456f, 0.653466f, 1E-4f));
    // Test for the double type values
    ASSERT_FALSE(vne::math::areSame(32.34, 32.3400002, vne::math::kDoubleEpsilon));
    ASSERT_TRUE(vne::math::areSame(32.34, 32.34000000000000002, vne::math::kDoubleEpsilon));
    ASSERT_TRUE(vne::math::areSame(32.34, 32.34000000000000002));
    ASSERT_FALSE(vne::math::areSame(9999.653456, 9999.653466, vne::math::kDoubleEpsilon));
    ASSERT_TRUE(vne::math::areSame(99999999999.653456, 99999999999.653466, vne::math::kDoubleEpsilon));
    ASSERT_FALSE(vne::math::areSame(0.653456, 0.653466, vne::math::kDoubleEpsilon));
    ASSERT_TRUE(vne::math::areSame(0.653456, 0.653466, 1E-4));
    // Test for the int type values
    int val1_i = -32;
    int val2_i = 32;
    ASSERT_TRUE(vne::math::areSame(val1_i, val1_i));
    ASSERT_TRUE(vne::math::areSame(val1_i, val1_i, 0));
    ASSERT_TRUE(vne::math::areSame(val1_i, val1_i, 1));
    ASSERT_TRUE(vne::math::areSame(val1_i, val1_i, 100000));
    ASSERT_FALSE(vne::math::areSame(val1_i, val2_i));
    // Test for the unsigned int
    unsigned int val1_ui = 254;
    unsigned int val2_ui = 255;
    unsigned int eps_ui = 0;
    ASSERT_TRUE(vne::math::areSame(val1_ui, val1_ui));
    ASSERT_TRUE(vne::math::areSame(val1_ui, val1_ui, eps_ui));
    ASSERT_FALSE(vne::math::areSame(val1_ui, val2_ui));
    // Test for the char
    char val1_c = 'A';
    char val2_c = 'B';
    char eps_c = 0;
    ASSERT_TRUE(vne::math::areSame(val1_c, val1_c));
    ASSERT_TRUE(vne::math::areSame(val1_c, val1_c, eps_c));
    ASSERT_FALSE(vne::math::areSame(val1_c, val2_c));
    // Test for the unsigned char
    unsigned char val1_uc = 'C';
    unsigned char val2_uc = 'D';
    unsigned char eps_uc = 2;
    ASSERT_TRUE(vne::math::areSame(val1_uc, val1_uc));
    ASSERT_TRUE(vne::math::areSame(val1_uc, val1_uc, eps_uc));
    ASSERT_FALSE(vne::math::areSame(val1_uc, val2_uc));
    // Test for the long int
    long val1_l = 34456l;
    long val2_l = 34457l;
    long eps_l = 22l;
    ASSERT_TRUE(vne::math::areSame(val1_l, val1_l));
    ASSERT_TRUE(vne::math::areSame(val1_l, val1_l, eps_l));
    ASSERT_FALSE(vne::math::areSame(val1_l, val2_l));
    // Test for the unsigned long
    unsigned long val1_ul = 29873ul;
    unsigned long val2_ul = static_cast<unsigned long>(-22);  // This will result in a large positive number
    unsigned long val3_ul =
        4294967274ul;  // This is the unsigned long equivalent of -22 when using 32-bit unsigned long

    ASSERT_TRUE(vne::math::areSame(val1_ul, val1_ul));
    ASSERT_TRUE(vne::math::areSame(val1_ul, val1_ul, val3_ul));
    ASSERT_FALSE(vne::math::areSame(val1_ul, val2_ul));
}

/**
 * Test vne::math::isZero(...)
 */
TEST_F(MathUtilsTest, TestMathIsZero) {
    ASSERT_TRUE(vne::math::isZero(0.00000003f));
    ASSERT_TRUE(vne::math::isZero(0.00000003f, vne::math::kFloatEpsilon));
    ASSERT_FALSE(vne::math::isZero(0.00003f, vne::math::kFloatEpsilon));
    ASSERT_FALSE(vne::math::isZero(0.00000003, vne::math::kDoubleEpsilon));
    ASSERT_TRUE(vne::math::isZero(0.00000000000000003, vne::math::kDoubleEpsilon));
    ASSERT_TRUE(vne::math::isZero(0.00000003, 1E-7));
    ASSERT_TRUE(vne::math::isZero(0));
    ASSERT_TRUE(vne::math::isZero(0u));
    ASSERT_TRUE(vne::math::isZero(0L));
    ASSERT_TRUE(vne::math::isZero(0UL));
    ASSERT_TRUE(vne::math::isZero(0UL, 1UL));
    ASSERT_FALSE(vne::math::isZero(1u));
}
////////////////////////////////////////////////////////////////////////////
//                             Interpolations                              //
// /////////////////////////////////////////////////////////////////////////

/**
 * Test vne::math::midPoint(...)
 */
TEST_F(MathUtilsTest, TestMathMidPoint) {
    ASSERT_EQ(3, vne::math::midPoint(2, 4));
    ASSERT_EQ(3, vne::math::midPoint(2, 5));
    ASSERT_EQ(3, vne::math::midPoint(4, 2));
    ASSERT_EQ(4, vne::math::midPoint(5, 2));
    ASSERT_EQ(4, vne::math::midPoint(2, 6));
    ASSERT_EQ(1500000000, vne::math::midPoint(2000000000, 1000000000));
    ASSERT_EQ(500000000, vne::math::midPoint(-1000000000, 2000000000));
    ASSERT_EQ(30, vne::math::midPoint(25, 35));
    ASSERT_FLOAT_EQ(30, vne::math::midPoint(25.0f, 35.0f));
    ASSERT_FLOAT_EQ(vne::math::kFloatMin + vne::math::kFloatMax / 2,
                    vne::math::midPoint(vne::math::kFloatMin, vne::math::kFloatMax));
    ASSERT_FLOAT_EQ(vne::math::kFloatMin + vne::math::kFloatMax / 2,
                    vne::math::midPoint(vne::math::kFloatMax, vne::math::kFloatMin));
    ASSERT_FLOAT_EQ(vne::math::kFloatMax, vne::math::midPoint(vne::math::kFloatMax, vne::math::kFloatMax));
    ASSERT_DOUBLE_EQ(30, vne::math::midPoint(25.0, 35.0));
    ASSERT_DOUBLE_EQ(vne::math::kDoubleMin + vne::math::kDoubleMax / 2,
                     vne::math::midPoint(vne::math::kDoubleMin, vne::math::kDoubleMax));
    ASSERT_DOUBLE_EQ(vne::math::kDoubleMin + vne::math::kDoubleMax / 2,
                     vne::math::midPoint(vne::math::kDoubleMax, vne::math::kDoubleMin));
    ASSERT_DOUBLE_EQ(vne::math::kDoubleMax, vne::math::midPoint(vne::math::kDoubleMax, vne::math::kDoubleMax));
}

/**
 * Test vne::math::lerp<T>(...)
 */
TEST_F(MathUtilsTest, TestMathLerp) {
    ASSERT_EQ(15, static_cast<int>(vne::math::lerp(10.0f, 20.0f, 0.5f)));
    ASSERT_TRUE(vne::math::areSame(10.0f, vne::math::lerp(10.0f, 20.0f, 0.0f)));
    ASSERT_TRUE(vne::math::areSame(20.0f, vne::math::lerp(10.0f, 20.0f, 1.0f)));
}

/**
 * Test vne::math::biLerp<T>(...)
 */
TEST_F(MathUtilsTest, TestMathBiLerp) {
    ASSERT_FLOAT_EQ(1.5f, vne::math::biLerp(0.0f, 1.0f, 2.0f, 3.0f, 0.5f, 0.5f));
}

////////////////////////////////////////////////////////////////////////////
//               Nearest Integer floating point operations                 //
// /////////////////////////////////////////////////////////////////////////

/**
 * Test vne::math::roundMultipleOf<T>(...)
 */
TEST_F(MathUtilsTest, TestMathRoundMultipleOf) {
    ASSERT_FLOAT_EQ(2.5f, vne::math::roundMultipleOf<float>(2.6f, 0.5f));
    ASSERT_FLOAT_EQ(3.0f, vne::math::roundMultipleOf<float>(2.8f, 0.5f));
    ASSERT_FLOAT_EQ(-2.5f, vne::math::roundMultipleOf<float>(-2.6f, 0.5f));
    ASSERT_FLOAT_EQ(-3.0f, vne::math::roundMultipleOf<float>(-2.6f, 0.0f));
    ASSERT_FLOAT_EQ(-2.25f, vne::math::roundMultipleOf<float>(-2.3f, 0.25f));
    ASSERT_FLOAT_EQ(-3.0f, vne::math::roundMultipleOf<float>(-2.8f, 0.5f));
    ASSERT_FLOAT_EQ(-2.75f, vne::math::roundMultipleOf<float>(-2.8f, 0.25f));
    ASSERT_FLOAT_EQ(-3.0f, vne::math::roundMultipleOf<float>(-2.8f, -0.5f));
    ASSERT_DOUBLE_EQ(1301.0, vne::math::roundMultipleOf<double>(1300.875, 0.5));
}

////////////////////////////////////////////////////////////////////////////
//                  Exponential Functions                                 //
// /////////////////////////////////////////////////////////////////////////

/**
 * Test vne::math::logx(...)
 */
TEST_F(MathUtilsTest, TestMathLogx) {
    ASSERT_DOUBLE_EQ(glm::log(1) / glm::log(2), vne::math::logx(1, 2));
    ASSERT_DOUBLE_EQ(glm::log(2) / glm::log(1), vne::math::logx(2, 1));
    ASSERT_DOUBLE_EQ(glm::log(2) / glm::log(0), vne::math::logx(2, 0));
    ASSERT_DOUBLE_EQ(glm::log(15) / glm::log(2), vne::math::logx(15, 2));
    ASSERT_DOUBLE_EQ(glm::log(15) / glm::log(10), vne::math::logx(15, 10));
    ASSERT_FLOAT_EQ(glm::log(1.45f) / glm::log(3.0f), vne::math::logx(1.45f, 3.0f));
    ASSERT_DOUBLE_EQ(glm::log(1.45) / glm::log(3), vne::math::logx(1.45, 3));
    ASSERT_DOUBLE_EQ(glm::log(1.45) / glm::log(14.34), vne::math::logx(1.45, 14.34));
}

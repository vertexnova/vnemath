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

// note: please include math_utils below to gtest.h
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/extended_min_max.hpp>

#include "vertexnova/math/math_utils.h"

using namespace VNE;

class MathUtilsTest_C : public ::testing::Test {
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
TEST_F(MathUtilsTest_C, TestMathPIConstant) {
    ASSERT_FLOAT_EQ(glm::pi<float>(), Math::Pi<float>());
    ASSERT_DOUBLE_EQ(glm::pi<double>(), Math::Pi<double>());
    ASSERT_FLOAT_EQ(glm::two_pi<float>(), Math::TwoPi<float>());
    ASSERT_DOUBLE_EQ(glm::two_pi<double>(), Math::TwoPi<double>());
    ASSERT_FLOAT_EQ(glm::half_pi<float>(), Math::HalfPi<float>());
    ASSERT_DOUBLE_EQ(glm::half_pi<double>(), Math::HalfPi<double>());
    ASSERT_FLOAT_EQ(glm::quarter_pi<float>(), Math::QuarterPi<float>());
    ASSERT_DOUBLE_EQ(glm::quarter_pi<double>(), Math::QuarterPi<double>());
    ASSERT_FLOAT_EQ(glm::one_over_pi<float>(), Math::OneOverPi<float>());
    ASSERT_DOUBLE_EQ(glm::one_over_pi<double>(), Math::OneOverPi<double>());
    ASSERT_FLOAT_EQ(glm::one_over_two_pi<float>(), Math::OneOverTwoPi<float>());
    ASSERT_DOUBLE_EQ(glm::one_over_two_pi<double>(), Math::OneOverTwoPi<double>());
}

/**
 * Test Math GetEps<T>(...)
 */
TEST_F(MathUtilsTest_C, TestMathGetEps) {
    ASSERT_EQ(0, Math::GetEps<int>());
    ASSERT_EQ(0, Math::GetEps<char>());
    ASSERT_EQ(Math::FLOAT_EPSILON, Math::GetEps<float>());
    ASSERT_EQ(Math::DOUBLE_EPSILON, Math::GetEps<double>());
}

////////////////////////////////////////////////////////////////////////////
//                        Basic Operations                                 //
// /////////////////////////////////////////////////////////////////////////

/**
 * Test Math::RadToDeg<T>(...)
 */
TEST_F(MathUtilsTest_C, TestMathRadToDeg) {
    ASSERT_FLOAT_EQ(glm::degrees(3.14f), Math::RadToDeg<float>(3.14f));
    ASSERT_DOUBLE_EQ(glm::degrees(3.14), Math::RadToDeg<double>(3.14));
    ASSERT_DOUBLE_EQ(glm::degrees(3.0), Math::RadToDeg<double>(3));
    ASSERT_FLOAT_EQ(glm::degrees(glm::two_pi<float>()), Math::RadToDeg<float>(Math::TwoPi<float>()));
    ASSERT_FLOAT_EQ(360, Math::RadToDeg<float>(Math::TwoPi<float>()));
    ASSERT_DOUBLE_EQ(360.0, static_cast<double>(Math::RadToDeg<float>(Math::TwoPi<float>())));
    ASSERT_NEAR(static_cast<double>(glm::degrees(1.57f)), static_cast<double>(Math::RadToDeg<float>(1.57f)), 1E-4);
}

/**
 * Test Math::DegToRad<T>(...)
 */
TEST_F(MathUtilsTest_C, TestMathDegToRad) {
    ASSERT_EQ(glm::radians(90.0f), Math::DegToRad<float>(90));
    ASSERT_EQ(glm::radians(90.0f), Math::DegToRad<float>(90.0f));
    ASSERT_EQ(glm::radians(90.0), Math::DegToRad<double>(90));
    ASSERT_NE(glm::radians(90.0f), Math::DegToRad<double>(90));
    ASSERT_EQ(glm::radians(45.35f), Math::DegToRad<float>(45.35f));
    ASSERT_EQ(glm::radians(45.305), Math::DegToRad<double>(45.305));
}

/**
 * Test Math::Abs<T>(...)
 */
TEST_F(MathUtilsTest_C, TestMathAbs) {
    ASSERT_EQ(glm::abs(-13), Math::Abs(-13));
    ASSERT_EQ(13, Math::Abs(-13));
    ASSERT_EQ(glm::abs(-14.98f), Math::Abs(-14.98f));
    ASSERT_EQ(glm::abs(-18.9889), Math::Abs(-18.9889));
    ASSERT_EQ(glm::abs(2000.2), Math::Abs(2000.2));
    ASSERT_EQ(glm::abs(2021), Math::Abs(-2021));
}

/**
 * Test Math::Sign<T>(...)
 */
TEST_F(MathUtilsTest_C, TestMathSign) {
    ASSERT_EQ(glm::sign(-23.5f), Math::Sign(-23.5f));
    ASSERT_EQ(glm::sign(9), Math::Sign(9));
    ASSERT_EQ(glm::sign(0.0), Math::Sign(0.0));
    ASSERT_EQ(-1, Math::Sign(0.00005, 0.0001));
}

/**
 * Test Math::Min<T>(...)
 */
TEST_F(MathUtilsTest_C, TestMathMin) {
    // For two values
    ASSERT_EQ(glm::min(1, 3), Math::Min<int>(1, 3));
    ASSERT_EQ(glm::min(4.0f, 3.1f), Math::Min<float>(4.0f, 3.1f));
    ASSERT_EQ(glm::min(24.56, 24.5555), Math::Min<double>(24.56, 24.5555));
    // For Three values
    ASSERT_EQ(1, Math::Min<int>(1, 13, 4));
    ASSERT_EQ(0, Math::Min<int>(static_cast<int>(4.0f), static_cast<int>(3.1f), static_cast<int>(0.05f)));
    ASSERT_EQ(0.05f, Math::Min<float>(4.0f, 3.1f, 0.05f));
    ASSERT_EQ(16.07, Math::Min<double>(24.56, 24.5555, 16.07));
}

/**
 * Test Math::Max<T>(...)
 */
TEST_F(MathUtilsTest_C, TestMathMax) {
    // For two values
    ASSERT_EQ(glm::max(1, 3), Math::Max<int>(1, 3));
    ASSERT_EQ(glm::max(4.0f, 3.1f), Math::Max<float>(4.0f, 3.1f));
    ASSERT_NE(glm::max(24.56, 24.5555), Math::Max<float>(24.56f, 24.5555f));
    ASSERT_EQ(glm::max(24.56, 24.5555), Math::Max<double>(24.56, 24.5555));
    // For Three values
    ASSERT_EQ(13, Math::Max<int>(1, 13, 4));
    ASSERT_EQ(4, Math::Max<int>(static_cast<int>(4.0f), static_cast<int>(3.1f), static_cast<int>(0.05f)));
    ASSERT_EQ(4, Math::Max<float>(4.0f, 3.1f, 0.05f));
    ASSERT_EQ(24.56, Math::Max<double>(24.56, 24.5555, 16.07));
}

/**
 * Test Math::Clamp<T>(...)
 */
TEST_F(MathUtilsTest_C, TestMathClamp) {
    ASSERT_EQ(glm::clamp(1, 2, 3), Math::Clamp<int>(1, 2, 3));
    ASSERT_EQ(2, Math::Clamp<int>(1, 2, 3));
    ASSERT_EQ(glm::clamp(4, 2, 3), Math::Clamp<int>(4, 2, 3));
    ASSERT_EQ(3, Math::Clamp<int>(4, 2, 3));
    ASSERT_EQ(glm::clamp(4, 2, 7), Math::Clamp<int>(4, 2, 7));
    ASSERT_EQ(4, Math::Clamp<int>(4, 2, 7));
    ASSERT_EQ(glm::clamp(15.5f, 0.05f, 13.34f), Math::Clamp<float>(15.5f, 0.05f, 13.34f));
    ASSERT_EQ(glm::clamp(20.34, 15.67, 30.89), Math::Clamp<double>(20.34, 15.67, 30.89));
}

/**
 * Test Math::Saturate<T>(...)
 */
TEST_F(MathUtilsTest_C, TestMathSaturate) {
    ASSERT_EQ(glm::clamp(-1, 0, 1), Math::Saturate<int>(-1));
    ASSERT_EQ(glm::clamp(1, 0, 1), Math::Saturate<int>(1));
    ASSERT_EQ(glm::clamp(4, 0, 1), Math::Saturate<int>(4));
    ASSERT_EQ(glm::clamp(15.5f, 0.0f, 1.0f), Math::Saturate<float>(15.5f));
    ASSERT_EQ(glm::clamp(20.34, 0.0, 1.0), Math::Saturate<double>(20.34));
}

/**
 * Test Math::ArrangeMinMax<T>(...)
 */
TEST_F(MathUtilsTest_C, TestMathArrangeMinMax) {
    int min_i = 3;
    int max_i = 1;
    Math::ArrangeMinMax(&min_i, &max_i);
    ASSERT_EQ(1, min_i);
    ASSERT_EQ(3, max_i);

    float min_f = 10.34f;
    float max_f = 10.35f;
    Math::ArrangeMinMax(&min_f, &max_f);
    ASSERT_FLOAT_EQ(10.34f, min_f);
    ASSERT_FLOAT_EQ(10.35f, max_f);

    double min_d = 20.45;
    double max_d = 20.0;
    Math::ArrangeMinMax<double>(&min_d, &max_d);
    ASSERT_DOUBLE_EQ(20.0, min_d);
    ASSERT_DOUBLE_EQ(20.45, max_d);
}

/**
 * Test Math::IsInBetween<T>(...)
 */
TEST_F(MathUtilsTest_C, TestMathIsInBetween) {
    ASSERT_FALSE(Math::IsInBetween(1, 2, 3));
    ASSERT_TRUE(Math::IsInBetween(2, 1, 3));
    ASSERT_TRUE(Math::IsInBetween(2, 3, 1));
    ASSERT_TRUE(Math::IsInBetween(0.0834f, 0.0f, 1.0f));
    ASSERT_TRUE(Math::IsInBetween(Math::DOUBLE_MAX, Math::DOUBLE_MIN, Math::DOUBLE_INFINITY, Math::DOUBLE_EPSILON));
}

/**
 * Test Math::Square<T>(...)
 */
TEST_F(MathUtilsTest_C, TestMathSquare) {
    ASSERT_EQ(4, Math::Square<int>(2));
    ASSERT_FLOAT_EQ(5.0625f, Math::Square<float>(2.25f));
    ASSERT_DOUBLE_EQ(185.640625, Math::Square<double>(13.625));
    ASSERT_NEAR(static_cast<double>(Math::Square<float>(125.678f)), Math::Square<double>(125.678), 1E-3);
    ASSERT_NEAR(152415765.27968, Math::Square<double>(12345.678), 1E-5);
}

/**
 * Test Math::Cube<T>(...)
 */
TEST_F(MathUtilsTest_C, TestMathCube) {
    ASSERT_EQ(27, Math::Cube<int>(3));
    ASSERT_EQ(216, Math::Cube<int>(6));
    ASSERT_EQ(1111 * 1111 * 1111, Math::Cube<long int>(1111));
    ASSERT_FLOAT_EQ(2460.375f, Math::Cube<float>(13.5f));
    ASSERT_DOUBLE_EQ(2460.375, Math::Cube<double>(13.5));
}

/**
 * Test Math::Pow<T>(...)
 */
TEST_F(MathUtilsTest_C, TestMathPow) {
    ASSERT_EQ(glm::pow(0.25f, 2), Math::Pow<float>(0.25f, 2));
    ASSERT_EQ(glm::pow(625, 0.5f), Math::Pow<float>(625, 0.5f));
    ASSERT_EQ(25.0f, Math::Pow<float>(625, 0.5f));
    ASSERT_DOUBLE_EQ(glm::pow(625, 625), Math::Pow<double>(625, 625));
}

/**
 * Test Math::Sqrt<T>(...)
 */
TEST_F(MathUtilsTest_C, TestMathSqrt) {
    ASSERT_FLOAT_EQ(0.0f, Math::Sqrt<float>(0));
    ASSERT_NE(glm::sqrt(-1),
              Math::Sqrt<float>(-1));  // compiler dependent test (NaN)
    ASSERT_FLOAT_EQ(glm::sqrt(2.0f), Math::Sqrt<float>(2.0f));
    ASSERT_FLOAT_EQ(glm::sqrt(3.0f), Math::Sqrt<float>(3.0f));
    ASSERT_FLOAT_EQ(glm::sqrt(625.0f), Math::Sqrt<float>(625.0f));
    ASSERT_DOUBLE_EQ(glm::sqrt(6252.5), Math::Sqrt<double>(6252.5));
    ASSERT_DOUBLE_EQ(SQRT_TWO, Math::Sqrt<double>(2));
    ASSERT_DOUBLE_EQ(SQRT_THREE, Math::Sqrt<double>(3));
}

/**
 * Test Math::InvSqrt<T>(...)
 */
TEST_F(MathUtilsTest_C, TestMathInvSqrt) {
    ASSERT_FLOAT_EQ(glm::inversesqrt(0.0f), Math::InvSqrt<float>(0));
    ASSERT_TRUE(std::isnan(glm::inversesqrt(-1.0f)));
    ASSERT_TRUE(std::isnan(Math::InvSqrt<float>(-1.0f)));
    ASSERT_FLOAT_EQ(glm::inversesqrt(2.0f), Math::InvSqrt<float>(2));
    ASSERT_FLOAT_EQ(glm::inversesqrt(3.0f), Math::InvSqrt<float>(3));
    ASSERT_FLOAT_EQ(glm::inversesqrt(25.0f), Math::InvSqrt(static_cast<float>(25)));
    ASSERT_DOUBLE_EQ(glm::inversesqrt(0.625), Math::InvSqrt<double>(0.625));
}

/**
 * Test Math::AreSame(...)
 */
TEST_F(MathUtilsTest_C, TestMathAreSame) {
    // Test for the float type values
    ASSERT_TRUE(Math::AreSame(32.34f, 32.3400002f));
    ASSERT_TRUE(Math::AreSame(32.34f, 32.3400002f, Math::FLOAT_EPSILON));
    ASSERT_FALSE(Math::AreSame(32.34f, 32.34002f, Math::FLOAT_EPSILON));
    ASSERT_TRUE(Math::AreSame(9999.653456f, 9999.653466f, Math::FLOAT_EPSILON));
    ASSERT_FALSE(Math::AreSame(0.653456f, 0.653466f, Math::FLOAT_EPSILON));
    ASSERT_TRUE(Math::AreSame(0.653456f, 0.653466f, 1E-4f));
    // Test for the double type values
    ASSERT_FALSE(Math::AreSame(32.34, 32.3400002, Math::DOUBLE_EPSILON));
    ASSERT_TRUE(Math::AreSame(32.34, 32.34000000000000002, Math::DOUBLE_EPSILON));
    ASSERT_TRUE(Math::AreSame(32.34, 32.34000000000000002));
    ASSERT_FALSE(Math::AreSame(9999.653456, 9999.653466, Math::DOUBLE_EPSILON));
    ASSERT_TRUE(Math::AreSame(99999999999.653456, 99999999999.653466, Math::DOUBLE_EPSILON));
    ASSERT_FALSE(Math::AreSame(0.653456, 0.653466, Math::DOUBLE_EPSILON));
    ASSERT_TRUE(Math::AreSame(0.653456, 0.653466, 1E-4));
    // Test for the int type values
    int val1_i = -32;
    int val2_i = 32;
    ASSERT_TRUE(Math::AreSame(val1_i, val1_i));
    ASSERT_TRUE(Math::AreSame(val1_i, val1_i, 0));
    ASSERT_TRUE(Math::AreSame(val1_i, val1_i, 1));
    ASSERT_TRUE(Math::AreSame(val1_i, val1_i, 100000));
    ASSERT_FALSE(Math::AreSame(val1_i, val2_i));
    // Test for the unsigned int
    unsigned int val1_ui = 254;
    unsigned int val2_ui = 255;
    unsigned int eps_ui = 0;
    ASSERT_TRUE(Math::AreSame(val1_ui, val1_ui));
    ASSERT_TRUE(Math::AreSame(val1_ui, val1_ui, eps_ui));
    ASSERT_FALSE(Math::AreSame(val1_ui, val2_ui));
    // Test for the char
    char val1_c = 'A';
    char val2_c = 'B';
    char eps_c = 0;
    ASSERT_TRUE(Math::AreSame(val1_c, val1_c));
    ASSERT_TRUE(Math::AreSame(val1_c, val1_c, eps_c));
    ASSERT_FALSE(Math::AreSame(val1_c, val2_c));
    // Test for the unsigned char
    unsigned char val1_uc = 'C';
    unsigned char val2_uc = 'D';
    unsigned char eps_uc = 2;
    ASSERT_TRUE(Math::AreSame(val1_uc, val1_uc));
    ASSERT_TRUE(Math::AreSame(val1_uc, val1_uc, eps_uc));
    ASSERT_FALSE(Math::AreSame(val1_uc, val2_uc));
    // Test for the long int
    long val1_l = 34456l;
    long val2_l = 34457l;
    long eps_l = 22l;
    ASSERT_TRUE(Math::AreSame(val1_l, val1_l));
    ASSERT_TRUE(Math::AreSame(val1_l, val1_l, eps_l));
    ASSERT_FALSE(Math::AreSame(val1_l, val2_l));
    // Test for the unsigned long
    unsigned long val1_ul = 29873ul;
    unsigned long val2_ul = static_cast<unsigned long>(-22);  // This will result in a large positive number
    unsigned long val3_ul = 4294967274ul;                     // This is the unsigned long equivalent of -22 when using 32-bit unsigned long

    ASSERT_TRUE(Math::AreSame(val1_ul, val1_ul));
    ASSERT_TRUE(Math::AreSame(val1_ul, val1_ul, val3_ul));
    ASSERT_FALSE(Math::AreSame(val1_ul, val2_ul));
}

/**
 * Test Math::IsZero(...)
 */
TEST_F(MathUtilsTest_C, TestMathIsZero) {
    ASSERT_TRUE(Math::IsZero(0.00000003f));
    ASSERT_TRUE(Math::IsZero(0.00000003f, Math::FLOAT_EPSILON));
    ASSERT_FALSE(Math::IsZero(0.00003f, Math::FLOAT_EPSILON));
    ASSERT_FALSE(Math::IsZero(0.00000003, Math::DOUBLE_EPSILON));
    ASSERT_TRUE(Math::IsZero(0.00000000000000003, Math::DOUBLE_EPSILON));
    ASSERT_TRUE(Math::IsZero(0.00000003, 1E-7));
    ASSERT_TRUE(Math::IsZero(0));
    ASSERT_TRUE(Math::IsZero(0u));
    ASSERT_TRUE(Math::IsZero(0L));
    ASSERT_TRUE(Math::IsZero(0UL));
    ASSERT_TRUE(Math::IsZero(0UL, 1UL));
    ASSERT_FALSE(Math::IsZero(1u));
}
////////////////////////////////////////////////////////////////////////////
//                             Interpolations                              //
// /////////////////////////////////////////////////////////////////////////

/**
 * Test Math::MidPoint(...)
 */
TEST_F(MathUtilsTest_C, TestMathMidPoint) {
    ASSERT_EQ(3, Math::MidPoint(2, 4));
    ASSERT_EQ(3, Math::MidPoint(2, 5));
    ASSERT_EQ(3, Math::MidPoint(4, 2));
    ASSERT_EQ(4, Math::MidPoint(5, 2));
    ASSERT_EQ(4, Math::MidPoint(2, 6));
    ASSERT_EQ(1500000000, Math::MidPoint(2000000000, 1000000000));
    ASSERT_EQ(500000000, Math::MidPoint(-1000000000, 2000000000));
    ASSERT_EQ(30, Math::MidPoint(25, 35));
    ASSERT_FLOAT_EQ(30, Math::MidPoint(25.0f, 35.0f));
    ASSERT_FLOAT_EQ(Math::FLOAT_MIN + Math::FLOAT_MAX / 2, Math::MidPoint(Math::FLOAT_MIN, Math::FLOAT_MAX));
    ASSERT_FLOAT_EQ(Math::FLOAT_MIN + Math::FLOAT_MAX / 2, Math::MidPoint(Math::FLOAT_MAX, Math::FLOAT_MIN));
    ASSERT_FLOAT_EQ(Math::FLOAT_MAX, Math::MidPoint(Math::FLOAT_MAX, Math::FLOAT_MAX));
    ASSERT_DOUBLE_EQ(30, Math::MidPoint(25.0, 35.0));
    ASSERT_DOUBLE_EQ(Math::DOUBLE_MIN + Math::DOUBLE_MAX / 2, Math::MidPoint(Math::DOUBLE_MIN, Math::DOUBLE_MAX));
    ASSERT_DOUBLE_EQ(Math::DOUBLE_MIN + Math::DOUBLE_MAX / 2, Math::MidPoint(Math::DOUBLE_MAX, Math::DOUBLE_MIN));
    ASSERT_DOUBLE_EQ(Math::DOUBLE_MAX, Math::MidPoint(Math::DOUBLE_MAX, Math::DOUBLE_MAX));
}

/**
 * Test Math::Lerp<T>(...)
 */
TEST_F(MathUtilsTest_C, TestMathLerp) {
    ASSERT_EQ(15, static_cast<int>(Math::Lerp(10.0f, 20.0f, 0.5f)));
    ASSERT_TRUE(Math::AreSame(10.0f, Math::Lerp(10.0f, 20.0f, 0.0f)));
    ASSERT_TRUE(Math::AreSame(20.0f, Math::Lerp(10.0f, 20.0f, 1.0f)));
}

/**
 * Test Math::BiLerp<T>(...)
 */
TEST_F(MathUtilsTest_C, TestMathBiLerp) {
    ASSERT_FLOAT_EQ(1.5f, Math::BiLerp(0.0f, 1.0f, 2.0f, 3.0f, 0.5f, 0.5f));
}

////////////////////////////////////////////////////////////////////////////
//               Nearest Integer floating point operations                 //
// /////////////////////////////////////////////////////////////////////////

/**
 * Test Math::Floor<T>(...)
 */
TEST_F(MathUtilsTest_C, TestMathFloor) {
    ASSERT_FLOAT_EQ(2.0f, Math::Floor<float>(2.7f));
    ASSERT_FLOAT_EQ(-3.0f, Math::Floor<float>(-2.7f));
    ASSERT_FLOAT_EQ(-3.0f, Math::Floor(-2.7f));
    ASSERT_FLOAT_EQ(-0.0f, Math::Floor(-0.0f));
    ASSERT_FLOAT_EQ(Math::FLOAT_INFINITY, Math::Floor(Math::FLOAT_INFINITY));
    ASSERT_DOUBLE_EQ(-Math::DOUBLE_INFINITY, Math::Floor(-Math::DOUBLE_INFINITY));
}

/**
 * Test Math::Ceil<T>(...)
 */
TEST_F(MathUtilsTest_C, TestMathCeil) {
    ASSERT_FLOAT_EQ(3.0f, Math::Ceil<float>(2.4f));
    ASSERT_FLOAT_EQ(-2.0f, Math::Ceil<float>(-2.4f));
    ASSERT_FLOAT_EQ(-2.0f, Math::Ceil(-2.4f));
    ASSERT_FLOAT_EQ(-0.0f, Math::Ceil(-0.0f));
    ASSERT_FLOAT_EQ(Math::FLOAT_INFINITY, Math::Ceil(Math::FLOAT_INFINITY));
    ASSERT_DOUBLE_EQ(-Math::DOUBLE_INFINITY, Math::Ceil(-Math::DOUBLE_INFINITY));
}

/**
 * Test Math::Trunc<T>(...)
 */
TEST_F(MathUtilsTest_C, TestMathTrunc) {
    ASSERT_FLOAT_EQ(2.0f, Math::Trunc<float>(2.7f));
    ASSERT_FLOAT_EQ(-2.0f, Math::Trunc<float>(-2.9f));
    ASSERT_FLOAT_EQ(-2.0f, Math::Trunc(-2.9f));
    ASSERT_FLOAT_EQ(-0.0f, Math::Trunc(-0.0f));
    ASSERT_FLOAT_EQ(Math::FLOAT_INFINITY, Math::Trunc(Math::FLOAT_INFINITY));
    ASSERT_DOUBLE_EQ(-Math::DOUBLE_INFINITY, Math::Trunc(-Math::DOUBLE_INFINITY));
}

/**
 * Test Math::Round<T>(...)
 */
TEST_F(MathUtilsTest_C, TestMathRound) {
    ASSERT_FLOAT_EQ(2.0f, Math::Round<float>(2.3f));
    ASSERT_FLOAT_EQ(-2.0f, Math::Round<float>(-2.3f));
    ASSERT_FLOAT_EQ(-2.0f, Math::Round(-2.3f));
    ASSERT_FLOAT_EQ(-0.0f, Math::Round(-0.0f));
    ASSERT_FLOAT_EQ(Math::FLOAT_INFINITY, Math::Round(Math::FLOAT_INFINITY));
    ASSERT_DOUBLE_EQ(-Math::DOUBLE_INFINITY, Math::Round(-Math::DOUBLE_INFINITY));
}

/**
 * Test Math::RoundMultipleOf<T>(...)
 */
TEST_F(MathUtilsTest_C, TestMathRoundMultipleOf) {
    ASSERT_FLOAT_EQ(2.5f, Math::RoundMultipleOf<float>(2.6f, 0.5f));
    ASSERT_FLOAT_EQ(3.0f, Math::RoundMultipleOf<float>(2.8f, 0.5f));
    ASSERT_FLOAT_EQ(-2.5f, Math::RoundMultipleOf<float>(-2.6f, 0.5f));
    ASSERT_FLOAT_EQ(-3.0f, Math::RoundMultipleOf<float>(-2.6f, 0.0f));
    ASSERT_FLOAT_EQ(-2.25f, Math::RoundMultipleOf<float>(-2.3f, 0.25f));
    ASSERT_FLOAT_EQ(-3.0f, Math::RoundMultipleOf<float>(-2.8f, 0.5f));
    ASSERT_FLOAT_EQ(-2.75f, Math::RoundMultipleOf<float>(-2.8f, 0.25f));
    ASSERT_FLOAT_EQ(-3.0f, Math::RoundMultipleOf<float>(-2.8f, -0.5f));
    ASSERT_DOUBLE_EQ(1301.0, Math::RoundMultipleOf<double>(1300.875, 0.5));
}

/**
 * Test Math::FloatToInt(...)
 */
TEST_F(MathUtilsTest_C, TestMathFloatToInt) {
    ASSERT_EQ(1, Math::FloatToInt(1.0f));
    ASSERT_EQ(13, Math::FloatToInt(13.657f));
    ASSERT_EQ(0, Math::FloatToInt(Math::FLOAT_EPSILON));
}

/**
 * Test Math::Modf(...)
 */
TEST_F(MathUtilsTest_C, TestMathModf) {
    float int_part, frac_part;
    frac_part = Math::Modf(123.45f, &int_part);
    ASSERT_TRUE(Math::AreSame(123.0f, int_part));
    ASSERT_TRUE(Math::AreSame(0.45f, frac_part, 1E-5f));
    frac_part = Math::Modf(-0.0f, &int_part);
    ASSERT_TRUE(Math::AreSame(-0.0f, int_part));
    ASSERT_TRUE(Math::AreSame(-0.0f, frac_part));
    double i_part, f_part;
    f_part = Math::Modf(-Math::DOUBLE_INFINITY, &i_part);
    ASSERT_DOUBLE_EQ(-Math::DOUBLE_INFINITY, i_part);
    ASSERT_TRUE(Math::AreSame(-0.0, f_part));
}

////////////////////////////////////////////////////////////////////////////
//               Classification and comparison                            //
// /////////////////////////////////////////////////////////////////////////

/**
 * Test Math::IsNaN(...)
 */
TEST_F(MathUtilsTest_C, TestMathIsNaN) {
    ASSERT_TRUE(Math::IsNaN(NAN));
    ASSERT_FALSE(Math::IsNaN(INFINITY));
    // ASSERT_TRUE(Math::IsNaN(0.0/0.0));
}

/**
 * Test Math::IsInf(...)
 */
TEST_F(MathUtilsTest_C, TestMathIsInf) {
    ASSERT_FALSE(Math::IsInf(NAN));
    ASSERT_TRUE(Math::IsInf(INFINITY));
    // ASSERT_TRUE(Math::IsInf(1.0/0.0));
}

/**
 * Test Math::IsNormal(...)
 */
TEST_F(MathUtilsTest_C, TestMathIsNormal) {
    ASSERT_FALSE(Math::IsNormal(NAN));
    ASSERT_FALSE(Math::IsNormal(INFINITY));
    ASSERT_TRUE(Math::IsNormal(1.0));
}

/**
 * Test Math::IsFinite(...)
 */
TEST_F(MathUtilsTest_C, TestMathIsFinite) {
    ASSERT_FALSE(Math::IsFinite(NAN));
    ASSERT_FALSE(Math::IsFinite(INFINITY));
    ASSERT_FALSE(Math::IsFinite(Math::Exp(800.0f)));
    ASSERT_TRUE(Math::IsFinite(0.0));
}

////////////////////////////////////////////////////////////////////////////
//                  Exponential Functions                                 //
// /////////////////////////////////////////////////////////////////////////

/**
 * Test Math::Exp(...)
 */
TEST_F(MathUtilsTest_C, TestMathExp) {
    ASSERT_FLOAT_EQ(glm::exp(0.03f), Math::Exp(0.03f));
    ASSERT_DOUBLE_EQ(glm::exp(1), Math::Exp(1));
    ASSERT_DOUBLE_EQ(glm::exp('c'), Math::Exp('c'));
    ASSERT_DOUBLE_EQ(glm::exp(710), Math::Exp(710));
    ASSERT_DOUBLE_EQ(glm::exp(-0.0), Math::Exp(-0.0));
    ASSERT_DOUBLE_EQ(glm::exp(Math::DOUBLE_INFINITY), Math::Exp(Math::DOUBLE_INFINITY));
}

/**
 * Test Math::Log(...)
 */
TEST_F(MathUtilsTest_C, TestMathLog) {
    ASSERT_FLOAT_EQ(glm::log(1.0f), Math::Log(1.0f));
    ASSERT_FLOAT_EQ(glm::log(125.0f), Math::Log(125.0f));
    ASSERT_DOUBLE_EQ(glm::log(0.0), Math::Log(0.0));
    ASSERT_DOUBLE_EQ(glm::log(Math::DOUBLE_INFINITY), Math::Log(Math::DOUBLE_INFINITY));
}

/**
 * Test Math::Log2(...)
 */
TEST_F(MathUtilsTest_C, TestMathLog2) {
    ASSERT_DOUBLE_EQ(glm::log2(65536.0), Math::Log2(65536));
    ASSERT_DOUBLE_EQ(glm::log2(0.125), Math::Log2(0.125));
    ASSERT_FLOAT_EQ(glm::log2(0.0f), Math::Log2(0.0f));
}

/**
 * Test Math::Log10(...)
 */
TEST_F(MathUtilsTest_C, TestMathLog10) {
    ASSERT_DOUBLE_EQ(3, Math::Log10(1000));
    ASSERT_FLOAT_EQ(-4, Math::Log10(0.0001f));
    ASSERT_DOUBLE_EQ(-3, Math::Log10(0.001));
    ASSERT_DOUBLE_EQ(0, Math::Log10(1));
    ASSERT_DOUBLE_EQ(-Math::DOUBLE_INFINITY, Math::Log10(0));
}

/**
 * Test Math::Logx(...)
 */
TEST_F(MathUtilsTest_C, TestMathLogx) {
    ASSERT_DOUBLE_EQ(glm::log(1) / glm::log(2), Math::Logx(1, 2));
    ASSERT_DOUBLE_EQ(glm::log(2) / glm::log(1), Math::Logx(2, 1));
    ASSERT_DOUBLE_EQ(glm::log(2) / glm::log(0), Math::Logx(2, 0));
    ASSERT_DOUBLE_EQ(glm::log(15) / glm::log(2), Math::Logx(15, 2));
    ASSERT_DOUBLE_EQ(glm::log(15) / glm::log(10), Math::Logx(15, 10));
    ASSERT_FLOAT_EQ(glm::log(1.45f) / glm::log(3.0f), Math::Logx(1.45f, 3.0f));
    ASSERT_DOUBLE_EQ(glm::log(1.45) / glm::log(3), Math::Logx(1.45, 3));
    ASSERT_DOUBLE_EQ(glm::log(1.45) / glm::log(14.34), Math::Logx(1.45, 14.34));
}

////////////////////////////////////////////////////////////////////////////
//               Trigonometric and hyperbolic functions                    //
// /////////////////////////////////////////////////////////////////////////

/**
 * Test Math::Sin(...)
 */
TEST_F(MathUtilsTest_C, TestMathSin) {
    ASSERT_DOUBLE_EQ(0.5, static_cast<double>(Math::Sin(Math::Pi<float>() / 6.0f)));
    ASSERT_DOUBLE_EQ(1.0, static_cast<double>(Math::Sin(Math::DegToRad<float>(90.0f))));
    ASSERT_DOUBLE_EQ(glm::sin(3 * Math::Pi<double>() / 4), Math::Sin(3 * Math::Pi<double>() / 4));
    ASSERT_NE(-0.707, Math::Sin(3 * Math::Pi<double>() / 4));
    ASSERT_DOUBLE_EQ(0, Math::Sin(0));
    ASSERT_DOUBLE_EQ(-0, Math::Sin(-0));
    ASSERT_NE(glm::sin(Math::DOUBLE_INFINITY),
              Math::Sin(Math::DOUBLE_INFINITY));  // NaN test
}

/**
 * Test Math::ASin(...)
 */
TEST_F(MathUtilsTest_C, TestMathASin) {
    ASSERT_DOUBLE_EQ(Math::HalfPi<double>(), Math::ASin(1));
    ASSERT_FLOAT_EQ(0.0f, Math::ASin(0.0f));
    ASSERT_DOUBLE_EQ(90, Math::RadToDeg(Math::ASin(1)));
    ASSERT_DOUBLE_EQ(Math::QuarterPi<double>(), Math::ASin(Math::InvSqrt<double>(2)));
    ASSERT_NE(glm::asin(1.1f), Math::ASin(1.1f));  // NaN test
}

/**
 * Test Math::Sinh(...)
 */
TEST_F(MathUtilsTest_C, TestMathSinh) {
    ASSERT_NEAR(1.175, Math::Sinh(1), 1E-3);
    ASSERT_DOUBLE_EQ(glm::sinh(1), Math::Sinh(1));
    ASSERT_DOUBLE_EQ(0, Math::Sinh(0.0));
    ASSERT_DOUBLE_EQ(Math::DOUBLE_INFINITY,
                     Math::Sinh(710.5));  // Infinity test
}

/**
 * Test Math::Cos(...)
 */
TEST_F(MathUtilsTest_C, TestMathCos) {
    ASSERT_DOUBLE_EQ(0.5, Math::Cos(Math::Pi<double>() / 3));
    ASSERT_FLOAT_EQ(glm::cos(Math::HalfPi<float>()),
                    Math::Cos(Math::HalfPi<float>()));  // value would not be exact zero
    ASSERT_NEAR(-0.707, Math::Cos(-3.0 * (Math::Pi<double>() / 4.0)), 1E-3);
    ASSERT_DOUBLE_EQ(1, Math::Cos(0));
    ASSERT_DOUBLE_EQ(1, Math::Cos(-0));
    ASSERT_NE(glm::cos(Math::DOUBLE_INFINITY),
              Math::Cos(Math::DOUBLE_INFINITY));  // NaN test
}

/**
 * Test Math::ACos(...)
 */
TEST_F(MathUtilsTest_C, TestMathACos) {
    ASSERT_DOUBLE_EQ(0, Math::ACos(1));
    ASSERT_DOUBLE_EQ(Math::Pi<double>(), Math::ACos(-1));
    ASSERT_DOUBLE_EQ(Math::HalfPi<double>(), Math::ACos(0));
    ASSERT_FLOAT_EQ(60.0f, Math::RadToDeg(Math::ACos(0.5f)));
    ASSERT_NE(glm::cos(1.1), Math::ACos(1.1));  // NaN test
}

/**
 * Test Math::Cosh(...)
 */
TEST_F(MathUtilsTest_C, TestMathCosh) {
    ASSERT_NEAR(1.543, Math::Cosh(1), 1E-3);
    ASSERT_DOUBLE_EQ(glm::cosh(1), Math::Cosh(1));
    ASSERT_DOUBLE_EQ(Math::Cosh(1), Math::Cosh(-1));
    ASSERT_DOUBLE_EQ(1.0, Math::Cosh(0.0));
    ASSERT_DOUBLE_EQ(Math::DOUBLE_INFINITY,
                     Math::Cosh(710.5));  // Infinity test
    ASSERT_DOUBLE_EQ(1,
                     Math::Log(Math::Sinh(1) + Math::Cosh(1)));  // Property
}

/**
 * Test Math::SinCos(...)
 */
TEST_F(MathUtilsTest_C, TestMathSinCos) {
    float sin, cos;
    Math::SinCos(Math::HalfPi<float>(), sin, cos);
    ASSERT_TRUE(Math::AreSame(1.0f, sin));
    ASSERT_TRUE(Math::AreSame(0.0f, cos));
    double s, c;
    Math::SinCos(0, s, c);
    ASSERT_TRUE(Math::AreSame(0.0, s));
    ASSERT_TRUE(Math::AreSame(1.0, c));
    Math::SinCos(Math::DOUBLE_INFINITY, sin, cos);  // NaN test
    ASSERT_NE(glm::sin(Math::DOUBLE_INFINITY), sin);
    ASSERT_NE(glm::cos(Math::DOUBLE_INFINITY), cos);
}

/**
 * Test Math::Tan(...)
 */
TEST_F(MathUtilsTest_C, TestMathTan) {
    ASSERT_DOUBLE_EQ(1, Math::Tan(Math::QuarterPi<double>()));
    ASSERT_DOUBLE_EQ(-1, Math::Tan(3 * Math::QuarterPi<double>()));
    ASSERT_DOUBLE_EQ(1, Math::Tan(5 * Math::QuarterPi<double>()));
    ASSERT_DOUBLE_EQ(-1, Math::Tan(7 * Math::QuarterPi<double>()));
    ASSERT_FLOAT_EQ(0, Math::Tan(0.0f));
    ASSERT_FLOAT_EQ(0, Math::Tan(-0.0f));
    ASSERT_NE(glm::tan(Math::FLOAT_INFINITY),
              Math::Tan(Math::FLOAT_INFINITY));  // NaN test
}

/**
 * Test Math::ATan(...)
 */
TEST_F(MathUtilsTest_C, TestMathATan) {
    ASSERT_DOUBLE_EQ(Math::QuarterPi<double>(), Math::ATan(1));
    ASSERT_DOUBLE_EQ(Math::HalfPi<double>(), Math::ATan(Math::DOUBLE_INFINITY));
    ASSERT_FLOAT_EQ(0, Math::ATan(0.0f));
    ASSERT_FLOAT_EQ(-0, Math::ATan(-0.0f));
}

/**
 * Test Math::ATan2(...)
 */
TEST_F(MathUtilsTest_C, TestMathATan2) {
    ASSERT_DOUBLE_EQ(1 * Math::QuarterPi<double>(), Math::ATan2(1, 1));     // Quad I
    ASSERT_DOUBLE_EQ(3 * Math::QuarterPi<double>(), Math::ATan2(1, -1));    // Quad II
    ASSERT_DOUBLE_EQ(-3 * Math::QuarterPi<double>(), Math::ATan2(-1, -1));  // Quad III
    ASSERT_DOUBLE_EQ(-1 * Math::QuarterPi<double>(), Math::ATan2(-1, 1));   // Quad IV
    ASSERT_FLOAT_EQ(0, Math::ATan2(0.0f, 0.0f));
    ASSERT_FLOAT_EQ(Math::Pi<float>(), Math::ATan2(0.0f, -0.0f));
    ASSERT_DOUBLE_EQ(Math::HalfPi<double>(), Math::ATan2(7.0, 0.0));
}

/**
 * Test Math::Tanh(...)
 */
TEST_F(MathUtilsTest_C, TestMathTanh) {
    ASSERT_NEAR(0.7615, Math::Tanh(1), 1E-4);
    ASSERT_NEAR(-0.7615, Math::Tanh(-1), 1E-4);
    ASSERT_DOUBLE_EQ(0, Math::Tanh(0.0));
    ASSERT_FLOAT_EQ(-0, Math::Tanh(-0.0f));
    ASSERT_DOUBLE_EQ(-1, Math::Tanh(0.1) * Math::Sinh(0.2) - Math::Cosh(0.2));  // Property
}

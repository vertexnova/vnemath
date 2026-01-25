/* ---------------------------------------------------------------------
 * Copyright (c) 2024 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Author:    Ajeet Singh Yadav
 * Created:   July-2024
 *
 * Autodoc:   yes
 * ----------------------------------------------------------------------
 */

// Testing framework
#include <gtest/gtest.h>

// Project headers
#include "vertexnova/math/color.h"

using namespace vne;

class ColorTest : public ::testing::Test {
    // Interface of test fixture base class
   protected:
    void SetUp() override {}

    void TearDown() override {}

   protected:
};

/**
 * Test predefined constant colors of the Color
 *
 */
TEST_F(ColorTest, TestConstColors) {
    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::WHITE.R());
    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::WHITE.G());
    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::WHITE.B());
    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::WHITE.A());

    EXPECT_FLOAT_EQ(0.0f, vne::math::Color::BLACK.R());
    EXPECT_FLOAT_EQ(0.0f, vne::math::Color::BLACK.G());
    EXPECT_FLOAT_EQ(0.0f, vne::math::Color::BLACK.B());
    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::BLACK.A());

    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::RED.R());
    EXPECT_FLOAT_EQ(0.0f, vne::math::Color::RED.G());
    EXPECT_FLOAT_EQ(0.0f, vne::math::Color::RED.B());
    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::RED.A());

    EXPECT_FLOAT_EQ(0.0f, vne::math::Color::GREEN.R());
    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::GREEN.G());
    EXPECT_FLOAT_EQ(0.0f, vne::math::Color::GREEN.B());
    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::GREEN.A());

    EXPECT_FLOAT_EQ(0.0f, vne::math::Color::BLUE.R());
    EXPECT_FLOAT_EQ(0.0f, vne::math::Color::BLUE.G());
    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::BLUE.B());
    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::BLUE.A());

    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::YELLOW.R());
    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::YELLOW.G());
    EXPECT_FLOAT_EQ(0.0f, vne::math::Color::YELLOW.B());
    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::YELLOW.A());

    EXPECT_FLOAT_EQ(0.0f, vne::math::Color::CYAN.R());
    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::CYAN.G());
    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::CYAN.B());
    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::CYAN.A());

    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::MAGENTA.R());
    EXPECT_FLOAT_EQ(0.0f, vne::math::Color::MAGENTA.G());
    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::MAGENTA.B());
    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::MAGENTA.A());

    EXPECT_FLOAT_EQ(0.4f, vne::math::Color::LIGHT_BLUE.R());
    EXPECT_FLOAT_EQ(0.4f, vne::math::Color::LIGHT_BLUE.G());
    EXPECT_FLOAT_EQ(0.8f, vne::math::Color::LIGHT_BLUE.B());
    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::LIGHT_BLUE.A());

    EXPECT_FLOAT_EQ(0.1f, vne::math::Color::DARK_BLUE.R());
    EXPECT_FLOAT_EQ(0.1f, vne::math::Color::DARK_BLUE.G());
    EXPECT_FLOAT_EQ(0.6f, vne::math::Color::DARK_BLUE.B());
    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::DARK_BLUE.A());

    EXPECT_FLOAT_EQ(0.5f, vne::math::Color::MAROON.R());
    EXPECT_FLOAT_EQ(0.0f, vne::math::Color::MAROON.G());
    EXPECT_FLOAT_EQ(0.0f, vne::math::Color::MAROON.B());
    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::MAROON.A());

    EXPECT_FLOAT_EQ(0.96f, vne::math::Color::BEIGE.R());
    EXPECT_FLOAT_EQ(0.96f, vne::math::Color::BEIGE.G());
    EXPECT_FLOAT_EQ(0.862f, vne::math::Color::BEIGE.B());
    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::BEIGE.A());

    EXPECT_FLOAT_EQ(0.647f, vne::math::Color::BROWN.R());
    EXPECT_FLOAT_EQ(0.164f, vne::math::Color::BROWN.G());
    EXPECT_FLOAT_EQ(0.164f, vne::math::Color::BROWN.B());
    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::BROWN.A());

    EXPECT_FLOAT_EQ(0.5f, vne::math::Color::GRAY.R());
    EXPECT_FLOAT_EQ(0.5f, vne::math::Color::GRAY.G());
    EXPECT_FLOAT_EQ(0.5f, vne::math::Color::GRAY.B());
    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::GRAY.A());

    EXPECT_FLOAT_EQ(0.5f, vne::math::Color::GREY.R());
    EXPECT_FLOAT_EQ(0.5f, vne::math::Color::GREY.G());
    EXPECT_FLOAT_EQ(0.5f, vne::math::Color::GREY.B());
    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::GREY.A());
}

/**
 * Test Color
 *
 */
TEST_F(ColorTest, TestColorRGBA) {
    vne::math::Color clr0;
    EXPECT_FLOAT_EQ(0.0f, clr0.R());
    EXPECT_FLOAT_EQ(0.0f, clr0.G());
    EXPECT_FLOAT_EQ(0.0f, clr0.B());
    EXPECT_FLOAT_EQ(1.0f, clr0.A());

    vne::math::Color clr(0.1f, 0.2f, 0.3f, 1.0f);
    EXPECT_FLOAT_EQ(0.1f, clr.R());
    EXPECT_FLOAT_EQ(0.2f, clr.G());
    EXPECT_FLOAT_EQ(0.3f, clr.B());
    EXPECT_FLOAT_EQ(1.0f, clr.A());

    vne::math::Vec3f rgb{0.1f, 0.2f, 0.3f};
    vne::math::Color clr_rgb(rgb, 1.0f);
    EXPECT_FLOAT_EQ(0.1f, clr_rgb.R());
    EXPECT_FLOAT_EQ(0.2f, clr_rgb.G());
    EXPECT_FLOAT_EQ(0.3f, clr_rgb.B());
    EXPECT_FLOAT_EQ(1.0f, clr_rgb.A());

    vne::math::Vec4f rgba{0.1f, 0.2f, 0.3f, 1.0f};
    vne::math::Color clr_rgba(rgba);
    EXPECT_FLOAT_EQ(0.1f, clr_rgba.R());
    EXPECT_FLOAT_EQ(0.2f, clr_rgba.G());
    EXPECT_FLOAT_EQ(0.3f, clr_rgba.B());
    EXPECT_FLOAT_EQ(1.0f, clr_rgba.A());

    clr_rgba.R() = 0.5f;
    clr_rgba.G() = 0.5f;
    clr_rgba.B() = 0.5f;
    clr_rgba.A() = 0.5f;
    EXPECT_FLOAT_EQ(0.5f, clr_rgba.R());
    EXPECT_FLOAT_EQ(0.5f, clr_rgba.G());
    EXPECT_FLOAT_EQ(0.5f, clr_rgba.B());
    EXPECT_FLOAT_EQ(0.5f, clr_rgba.A());
}

/**
 * Test Color GetPtr()
 */
TEST_F(ColorTest, TestColorGetPtr) {
    vne::math::Color clr(0.0f, 0.2f, 0.5f, 1.0f);
    EXPECT_EQ(clr.R(), *clr.GetPtr());
    EXPECT_EQ(clr.G(), *(clr.GetPtr() + 1));
    EXPECT_EQ(clr.B(), *(clr.GetPtr() + 2));
    EXPECT_EQ(clr.A(), *(clr.GetPtr() + 3));
}

/**
 * Test Color Reset(...) and Set(...)
 */
TEST_F(ColorTest, TestColorSetAndReset) {
    vne::math::Color clr(0.0f, 0.01f, 0.2f, 1.0f);

    clr.Reset();
    EXPECT_FLOAT_EQ(0.0f, clr.R());
    EXPECT_FLOAT_EQ(0.0f, clr.G());
    EXPECT_FLOAT_EQ(0.0f, clr.B());
    EXPECT_FLOAT_EQ(1.0f, clr.A());

    clr.Set();
    EXPECT_FLOAT_EQ(1.0f, clr.R());
    EXPECT_FLOAT_EQ(1.0f, clr.G());
    EXPECT_FLOAT_EQ(1.0f, clr.B());
    EXPECT_FLOAT_EQ(1.0f, clr.A());

    clr.Set(0.0f, 0.01f, 0.2f, 1.0f);
    EXPECT_FLOAT_EQ(0.0f, clr.R());
    EXPECT_FLOAT_EQ(0.01f, clr.G());
    EXPECT_FLOAT_EQ(0.2f, clr.B());
    EXPECT_FLOAT_EQ(1.0f, clr.A());

    vne::math::Vec3f rgb{0.2f, 0.0f, 0.8f};
    clr.Set(rgb);
    EXPECT_FLOAT_EQ(0.2f, clr.R());
    EXPECT_FLOAT_EQ(0.0f, clr.G());
    EXPECT_FLOAT_EQ(0.8f, clr.B());
    EXPECT_FLOAT_EQ(1.0f, clr.A());

    clr.Set(rgb, 0.5f);
    EXPECT_FLOAT_EQ(0.2f, clr.R());
    EXPECT_FLOAT_EQ(0.0f, clr.G());
    EXPECT_FLOAT_EQ(0.8f, clr.B());
    EXPECT_FLOAT_EQ(0.5f, clr.A());

    vne::math::Vec4f rgba{0.5f, 0.5f, 0.5f, 1.0f};
    clr.Set(rgba);
    EXPECT_FLOAT_EQ(0.5f, clr.R());
    EXPECT_FLOAT_EQ(0.5f, clr.G());
    EXPECT_FLOAT_EQ(0.5f, clr.B());
    EXPECT_FLOAT_EQ(1.0f, clr.A());
}

/**
 * Test Color AreSame(...)
 *
 * clr1.AreSame(clr2, eps)
 *
 */
TEST_F(ColorTest, TestColorAreSame) {
    vne::math::Color clr(0.0f, 0.01f, 0.2f, 1.0f);
    EXPECT_TRUE(clr.AreSame(vne::math::Color(0.00000001f, 0.01000075f, 0.2000001f), 1E-5f));
    EXPECT_FALSE(clr.AreSame(vne::math::Color(0.000001f, 0.010075f, 0.20001f)));
}

/**
 * Test Color IsZero(...)
 *
 * clr.IsZero(eps)
 *
 */
TEST_F(ColorTest, TestColorIsZero) {
    vne::math::Color clr(0.0f, 0.01f, 0.2f, 1.0f);
    ASSERT_TRUE(vne::math::Color().IsZero());
    ASSERT_FALSE(clr.IsZero());
}

/**
 * Test Color Lerp(...)
 *
 * clr1.Color(clr2, t)
 *
 */
TEST_F(ColorTest, TestColorLerp) {
    vne::math::Color clr1(0.0f, 0.01f, 0.2f, 1.0f);
    vne::math::Color clr2(1.0f, 0.2f, 0.2f, 0.0f);
    EXPECT_EQ(clr1, clr1.Lerp(clr2, 0.0f));
    EXPECT_EQ(clr2, clr1.Lerp(clr2, 1.0f));
    EXPECT_EQ(vne::math::Color(0.5f, 0.105f, 0.2f, 0.5f), clr1.Lerp(clr2, 0.5f));
}

/**
 * Test Color Addition
 */
TEST_F(ColorTest, TestColorAddition) {
    vne::math::Color clr1(0.0f, 0.01f, 0.2f, 1.0f);
    vne::math::Color clr2(1.0f, 0.2f, 0.2f, 0.0f);

    vne::math::Color clr3 = clr1 + clr2;
    EXPECT_FLOAT_EQ(1.0f, clr3.R());
    EXPECT_FLOAT_EQ(0.21f, clr3.G());
    EXPECT_FLOAT_EQ(0.4f, clr3.B());
    EXPECT_FLOAT_EQ(1.0f, clr3.A());

    clr3 += clr1;
    EXPECT_FLOAT_EQ(clr3.R(), 1.0f);
    EXPECT_FLOAT_EQ(clr3.G(), 0.22f);
    EXPECT_FLOAT_EQ(clr3.B(), 0.6f);
    EXPECT_FLOAT_EQ(clr3.A(), 1.0f);

    clr3 = clr1 + 0.005f;
    EXPECT_FLOAT_EQ(clr3.R(), 0.005f);
    EXPECT_FLOAT_EQ(clr3.G(), 0.015f);
    EXPECT_FLOAT_EQ(clr3.B(), 0.205f);
    EXPECT_FLOAT_EQ(clr3.A(), 1.0f);

    clr3 += 0.003f;
    EXPECT_FLOAT_EQ(clr3.R(), 0.008f);
    EXPECT_FLOAT_EQ(clr3.G(), 0.018f);
    EXPECT_FLOAT_EQ(clr3.B(), 0.208f);
    EXPECT_FLOAT_EQ(clr3.A(), 1.0f);
}

/**
 * Test Color Subtraction
 */
TEST_F(ColorTest, TestColorSubtraction) {
    vne::math::Color clr1(0.0f, 0.01f, 0.2f, 1.0f);
    vne::math::Color clr2(1.0f, 0.2f, 0.2f, 0.0f);

    vne::math::Color clr3 = clr1 - clr2;
    EXPECT_FLOAT_EQ(clr3.R(), 0.0f);
    EXPECT_FLOAT_EQ(clr3.G(), 0.0f);
    EXPECT_FLOAT_EQ(clr3.B(), 0.0f);
    EXPECT_FLOAT_EQ(clr3.A(), 1.0f);

    clr3 -= clr2;
    EXPECT_FLOAT_EQ(clr3.R(), 0.0f);
    EXPECT_FLOAT_EQ(clr3.G(), 0.0f);
    EXPECT_FLOAT_EQ(clr3.B(), 0.0f);
    EXPECT_FLOAT_EQ(clr3.A(), 1.0f);

    clr3 = clr1 - 0.005f;
    EXPECT_FLOAT_EQ(clr3.R(), 0.0f);
    EXPECT_FLOAT_EQ(clr3.G(), 0.005f);
    EXPECT_FLOAT_EQ(clr3.B(), 0.195f);
    EXPECT_FLOAT_EQ(clr3.A(), 0.995f);

    clr3 -= 0.003f;
    EXPECT_FLOAT_EQ(clr3.R(), 0.0f);
    EXPECT_FLOAT_EQ(clr3.G(), 0.002f);
    EXPECT_FLOAT_EQ(clr3.B(), 0.192f);
    EXPECT_FLOAT_EQ(clr3.A(), 0.992f);
}

/**
 * Test Color multiplication
 */
TEST_F(ColorTest, TestColorMultiplication) {
    vne::math::Color clr1(0.0f, 0.01f, 0.2f, 1.0f);
    vne::math::Color clr2(1.0f, 0.2f, 0.2f, 0.0f);

    vne::math::Color clr3 = clr1 * clr2;
    EXPECT_FLOAT_EQ(clr3.R(), 0.0f);
    EXPECT_FLOAT_EQ(clr3.G(), 0.002f);
    EXPECT_FLOAT_EQ(clr3.B(), 0.04f);
    EXPECT_FLOAT_EQ(clr3.A(), 0.0f);

    clr3 *= clr2;
    EXPECT_FLOAT_EQ(clr3.R(), 0.0f);
    EXPECT_FLOAT_EQ(clr3.G(), 0.0004f);
    EXPECT_FLOAT_EQ(clr3.B(), 0.008f);
    EXPECT_FLOAT_EQ(clr3.A(), 0.0f);

    clr3 = clr1 * 0.5f;
    EXPECT_FLOAT_EQ(clr3.R(), 0.0f);
    EXPECT_FLOAT_EQ(clr3.G(), 0.005f);
    EXPECT_FLOAT_EQ(clr3.B(), 0.1f);
    EXPECT_FLOAT_EQ(clr3.A(), 0.5f);

    clr3 *= 2.0f;
    EXPECT_FLOAT_EQ(clr3.R(), 0.0f);
    EXPECT_FLOAT_EQ(clr3.G(), 0.01f);
    EXPECT_FLOAT_EQ(clr3.B(), 0.2f);
    EXPECT_FLOAT_EQ(clr3.A(), 1.0f);
}

/**
 * Test Color division
 */
TEST_F(ColorTest, TestColorDivision) {
    vne::math::Color clr(0.0f, 0.2f, 0.5f, 1.0f);

    vne::math::Color out = clr / 0.5f;
    EXPECT_FLOAT_EQ(out.R(), 0.0f);
    EXPECT_FLOAT_EQ(out.G(), 0.4f);
    EXPECT_FLOAT_EQ(out.B(), 1.0f);
    EXPECT_FLOAT_EQ(out.A(), 1.0f);

    out /= 2.0f;
    EXPECT_FLOAT_EQ(out.R(), 0.0f);
    EXPECT_FLOAT_EQ(out.G(), 0.2f);
    EXPECT_FLOAT_EQ(out.B(), 0.5f);
    EXPECT_FLOAT_EQ(out.A(), 0.5f);

    vne::math::Color other{0.0f, 0.4f, 0.5f, 0.5f};
    out = clr / other;
    EXPECT_FLOAT_EQ(out.R(), 0.0f);
    EXPECT_FLOAT_EQ(out.G(), 0.5f);
    EXPECT_FLOAT_EQ(out.B(), 1.0f);
    EXPECT_FLOAT_EQ(out.A(), 1.0f);

    out /= other;
    EXPECT_FLOAT_EQ(out.R(), 0.0f);
    EXPECT_FLOAT_EQ(out.G(), 0.004901961f);   // Out.G() / 255; if > 1
    EXPECT_FLOAT_EQ(out.B(), 0.0078431377f);  // Out.B() / 255; if > 1
    EXPECT_FLOAT_EQ(out.A(), 1.0f);

    other.Set(0.0f, 0.0f, 0.0f, 0.0f);
    out /= other;
    EXPECT_FLOAT_EQ(out.R(), 0.0f);
    EXPECT_FLOAT_EQ(out.G(), 1.0f);
    EXPECT_FLOAT_EQ(out.B(), 1.0f);
    EXPECT_FLOAT_EQ(out.A(), 1.0f);

    clr.Set(0.0f, 0.0f, 0.0f, 0.0f);
    out = clr / other;
    EXPECT_FLOAT_EQ(out.R(), 0.0f);
    EXPECT_FLOAT_EQ(out.G(), 0.0f);
    EXPECT_FLOAT_EQ(out.B(), 0.0f);
    EXPECT_FLOAT_EQ(out.A(), 0.0f);
}

/**
 * Test Color comparison
 */
TEST_F(ColorTest, TestColorComparison) {
    vne::math::Color clr(0.0f, 0.2f, 0.5f, 1.0f);
    vne::math::Color clr_equal = clr;
    vne::math::Color clr_less = clr - 0.001f;
    vne::math::Color clr_greater = clr + 0.001f;
    EXPECT_TRUE(clr == clr_equal);
    EXPECT_TRUE(clr != clr_less);
    EXPECT_TRUE(clr != clr_greater);
}

/**
 * Test Color assignment operator
 */
TEST_F(ColorTest, TestColorAssignmentOp) {
    vne::math::Color clr(0.0f, 0.2f, 0.5f, 1.0f);
    vne::math::Color out;
    EXPECT_EQ(clr, out = clr);
}

/**
 * Test Color specific component
 */
TEST_F(ColorTest, TestColorComponent) {
    vne::math::Color clr(0.0f, 0.2f, 0.5f, 1.0f);
    EXPECT_EQ(clr.R(), clr[0]);
    EXPECT_EQ(clr.G(), clr[1]);
    EXPECT_EQ(clr.B(), clr[2]);
    EXPECT_EQ(clr.A(), clr[3]);
}

TEST_F(ColorTest, TestColorStreamOut) {
    vne::math::Color clr(0.5f, 0.2f, 0.5f, 1.0f);
    std::ostringstream stream;
    stream << clr;
    EXPECT_EQ(stream.str(), "[0.5, 0.2, 0.5, 1]");
}

TEST_F(ColorTest, TestColorStreamIn) {
    vne::math::Color clr(0.1f, 0.2f, 0.3f, 0.5f);
    vne::math::Color test;
    std::stringstream ss("[0.1, 0.2, 0.3, 0.5]");
    ss >> test;
    EXPECT_EQ(clr, test);
}

TEST_F(ColorTest, TestColorStreamInWithoutAlpha) {
    vne::math::Color clr(0.1f, 0.2f, 0.3f, 1.0f);
    vne::math::Color test;
    std::stringstream ss("[0.1, 0.2, 0.3]");
    ss >> test;
    EXPECT_EQ(clr, test);
}

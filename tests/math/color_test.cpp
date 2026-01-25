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
    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::kWhite.r());
    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::kWhite.g());
    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::kWhite.b());
    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::kWhite.a());

    EXPECT_FLOAT_EQ(0.0f, vne::math::Color::kBlack.r());
    EXPECT_FLOAT_EQ(0.0f, vne::math::Color::kBlack.g());
    EXPECT_FLOAT_EQ(0.0f, vne::math::Color::kBlack.b());
    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::kBlack.a());

    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::kRed.r());
    EXPECT_FLOAT_EQ(0.0f, vne::math::Color::kRed.g());
    EXPECT_FLOAT_EQ(0.0f, vne::math::Color::kRed.b());
    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::kRed.a());

    EXPECT_FLOAT_EQ(0.0f, vne::math::Color::kGreen.r());
    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::kGreen.g());
    EXPECT_FLOAT_EQ(0.0f, vne::math::Color::kGreen.b());
    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::kGreen.a());

    EXPECT_FLOAT_EQ(0.0f, vne::math::Color::kBlue.r());
    EXPECT_FLOAT_EQ(0.0f, vne::math::Color::kBlue.g());
    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::kBlue.b());
    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::kBlue.a());

    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::kYellow.r());
    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::kYellow.g());
    EXPECT_FLOAT_EQ(0.0f, vne::math::Color::kYellow.b());
    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::kYellow.a());

    EXPECT_FLOAT_EQ(0.0f, vne::math::Color::kCyan.r());
    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::kCyan.g());
    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::kCyan.b());
    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::kCyan.a());

    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::kMagenta.r());
    EXPECT_FLOAT_EQ(0.0f, vne::math::Color::kMagenta.g());
    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::kMagenta.b());
    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::kMagenta.a());

    EXPECT_FLOAT_EQ(0.4f, vne::math::Color::kLightBlue.r());
    EXPECT_FLOAT_EQ(0.4f, vne::math::Color::kLightBlue.g());
    EXPECT_FLOAT_EQ(0.8f, vne::math::Color::kLightBlue.b());
    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::kLightBlue.a());

    EXPECT_FLOAT_EQ(0.1f, vne::math::Color::kDarkBlue.r());
    EXPECT_FLOAT_EQ(0.1f, vne::math::Color::kDarkBlue.g());
    EXPECT_FLOAT_EQ(0.6f, vne::math::Color::kDarkBlue.b());
    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::kDarkBlue.a());

    EXPECT_FLOAT_EQ(0.5f, vne::math::Color::kMaroon.r());
    EXPECT_FLOAT_EQ(0.0f, vne::math::Color::kMaroon.g());
    EXPECT_FLOAT_EQ(0.0f, vne::math::Color::kMaroon.b());
    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::kMaroon.a());

    EXPECT_FLOAT_EQ(0.96f, vne::math::Color::kBeige.r());
    EXPECT_FLOAT_EQ(0.96f, vne::math::Color::kBeige.g());
    EXPECT_FLOAT_EQ(0.862f, vne::math::Color::kBeige.b());
    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::kBeige.a());

    EXPECT_FLOAT_EQ(0.647f, vne::math::Color::kBrown.r());
    EXPECT_FLOAT_EQ(0.164f, vne::math::Color::kBrown.g());
    EXPECT_FLOAT_EQ(0.164f, vne::math::Color::kBrown.b());
    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::kBrown.a());

    EXPECT_FLOAT_EQ(0.5f, vne::math::Color::kGray.r());
    EXPECT_FLOAT_EQ(0.5f, vne::math::Color::kGray.g());
    EXPECT_FLOAT_EQ(0.5f, vne::math::Color::kGray.b());
    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::kGray.a());

    EXPECT_FLOAT_EQ(0.5f, vne::math::Color::kGrey.r());
    EXPECT_FLOAT_EQ(0.5f, vne::math::Color::kGrey.g());
    EXPECT_FLOAT_EQ(0.5f, vne::math::Color::kGrey.b());
    EXPECT_FLOAT_EQ(1.0f, vne::math::Color::kGrey.a());
}

/**
 * Test Color
 *
 */
TEST_F(ColorTest, TestColorRGBA) {
    vne::math::Color clr0;
    EXPECT_FLOAT_EQ(0.0f, clr0.r());
    EXPECT_FLOAT_EQ(0.0f, clr0.g());
    EXPECT_FLOAT_EQ(0.0f, clr0.b());
    EXPECT_FLOAT_EQ(1.0f, clr0.a());

    vne::math::Color clr(0.1f, 0.2f, 0.3f, 1.0f);
    EXPECT_FLOAT_EQ(0.1f, clr.r());
    EXPECT_FLOAT_EQ(0.2f, clr.g());
    EXPECT_FLOAT_EQ(0.3f, clr.b());
    EXPECT_FLOAT_EQ(1.0f, clr.a());

    vne::math::Vec3f rgb{0.1f, 0.2f, 0.3f};
    vne::math::Color clr_rgb(rgb, 1.0f);
    EXPECT_FLOAT_EQ(0.1f, clr_rgb.r());
    EXPECT_FLOAT_EQ(0.2f, clr_rgb.g());
    EXPECT_FLOAT_EQ(0.3f, clr_rgb.b());
    EXPECT_FLOAT_EQ(1.0f, clr_rgb.a());

    vne::math::Vec4f rgba{0.1f, 0.2f, 0.3f, 1.0f};
    vne::math::Color clr_rgba(rgba);
    EXPECT_FLOAT_EQ(0.1f, clr_rgba.r());
    EXPECT_FLOAT_EQ(0.2f, clr_rgba.g());
    EXPECT_FLOAT_EQ(0.3f, clr_rgba.b());
    EXPECT_FLOAT_EQ(1.0f, clr_rgba.a());

    clr_rgba.r() = 0.5f;
    clr_rgba.g() = 0.5f;
    clr_rgba.b() = 0.5f;
    clr_rgba.a() = 0.5f;
    EXPECT_FLOAT_EQ(0.5f, clr_rgba.r());
    EXPECT_FLOAT_EQ(0.5f, clr_rgba.g());
    EXPECT_FLOAT_EQ(0.5f, clr_rgba.b());
    EXPECT_FLOAT_EQ(0.5f, clr_rgba.a());
}

/**
 * Test Color GetPtr()
 */
TEST_F(ColorTest, TestColorGetPtr) {
    vne::math::Color clr(0.0f, 0.2f, 0.5f, 1.0f);
    EXPECT_EQ(clr.r(), *clr.getPtr());
    EXPECT_EQ(clr.g(), *(clr.getPtr() + 1));
    EXPECT_EQ(clr.b(), *(clr.getPtr() + 2));
    EXPECT_EQ(clr.a(), *(clr.getPtr() + 3));
}

/**
 * Test Color Reset(...) and Set(...)
 */
TEST_F(ColorTest, TestColorSetAndReset) {
    vne::math::Color clr(0.0f, 0.01f, 0.2f, 1.0f);

    clr.reset();
    EXPECT_FLOAT_EQ(0.0f, clr.r());
    EXPECT_FLOAT_EQ(0.0f, clr.g());
    EXPECT_FLOAT_EQ(0.0f, clr.b());
    EXPECT_FLOAT_EQ(1.0f, clr.a());

    clr.set();
    EXPECT_FLOAT_EQ(1.0f, clr.r());
    EXPECT_FLOAT_EQ(1.0f, clr.g());
    EXPECT_FLOAT_EQ(1.0f, clr.b());
    EXPECT_FLOAT_EQ(1.0f, clr.a());

    clr.set(0.0f, 0.01f, 0.2f, 1.0f);
    EXPECT_FLOAT_EQ(0.0f, clr.r());
    EXPECT_FLOAT_EQ(0.01f, clr.g());
    EXPECT_FLOAT_EQ(0.2f, clr.b());
    EXPECT_FLOAT_EQ(1.0f, clr.a());

    vne::math::Vec3f rgb{0.2f, 0.0f, 0.8f};
    clr.set(rgb);
    EXPECT_FLOAT_EQ(0.2f, clr.r());
    EXPECT_FLOAT_EQ(0.0f, clr.g());
    EXPECT_FLOAT_EQ(0.8f, clr.b());
    EXPECT_FLOAT_EQ(1.0f, clr.a());

    clr.set(rgb, 0.5f);
    EXPECT_FLOAT_EQ(0.2f, clr.r());
    EXPECT_FLOAT_EQ(0.0f, clr.g());
    EXPECT_FLOAT_EQ(0.8f, clr.b());
    EXPECT_FLOAT_EQ(0.5f, clr.a());

    vne::math::Vec4f rgba{0.5f, 0.5f, 0.5f, 1.0f};
    clr.set(rgba);
    EXPECT_FLOAT_EQ(0.5f, clr.r());
    EXPECT_FLOAT_EQ(0.5f, clr.g());
    EXPECT_FLOAT_EQ(0.5f, clr.b());
    EXPECT_FLOAT_EQ(1.0f, clr.a());
}

/**
 * Test Color AreSame(...)
 *
 * clr1.areSame(clr2, eps)
 *
 */
TEST_F(ColorTest, TestColorAreSame) {
    vne::math::Color clr(0.0f, 0.01f, 0.2f, 1.0f);
    EXPECT_TRUE(clr.areSame(vne::math::Color(0.00000001f, 0.01000075f, 0.2000001f), 1E-5f));
    EXPECT_FALSE(clr.areSame(vne::math::Color(0.000001f, 0.010075f, 0.20001f)));
}

/**
 * Test Color IsZero(...)
 *
 * clr.isZero(eps)
 *
 */
TEST_F(ColorTest, TestColorIsZero) {
    vne::math::Color clr(0.0f, 0.01f, 0.2f, 1.0f);
    ASSERT_TRUE(vne::math::Color().isZero());
    ASSERT_FALSE(clr.isZero());
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
    EXPECT_EQ(clr1, clr1.lerp(clr2, 0.0f));
    EXPECT_EQ(clr2, clr1.lerp(clr2, 1.0f));
    EXPECT_EQ(vne::math::Color(0.5f, 0.105f, 0.2f, 0.5f), clr1.lerp(clr2, 0.5f));
}

/**
 * Test Color Addition
 */
TEST_F(ColorTest, TestColorAddition) {
    vne::math::Color clr1(0.0f, 0.01f, 0.2f, 1.0f);
    vne::math::Color clr2(1.0f, 0.2f, 0.2f, 0.0f);

    vne::math::Color clr3 = clr1 + clr2;
    EXPECT_FLOAT_EQ(1.0f, clr3.r());
    EXPECT_FLOAT_EQ(0.21f, clr3.g());
    EXPECT_FLOAT_EQ(0.4f, clr3.b());
    EXPECT_FLOAT_EQ(1.0f, clr3.a());

    clr3 += clr1;
    EXPECT_FLOAT_EQ(clr3.r(), 1.0f);
    EXPECT_FLOAT_EQ(clr3.g(), 0.22f);
    EXPECT_FLOAT_EQ(clr3.b(), 0.6f);
    EXPECT_FLOAT_EQ(clr3.a(), 1.0f);

    clr3 = clr1 + 0.005f;
    EXPECT_FLOAT_EQ(clr3.r(), 0.005f);
    EXPECT_FLOAT_EQ(clr3.g(), 0.015f);
    EXPECT_FLOAT_EQ(clr3.b(), 0.205f);
    EXPECT_FLOAT_EQ(clr3.a(), 1.0f);

    clr3 += 0.003f;
    EXPECT_FLOAT_EQ(clr3.r(), 0.008f);
    EXPECT_FLOAT_EQ(clr3.g(), 0.018f);
    EXPECT_FLOAT_EQ(clr3.b(), 0.208f);
    EXPECT_FLOAT_EQ(clr3.a(), 1.0f);
}

/**
 * Test Color Subtraction
 */
TEST_F(ColorTest, TestColorSubtraction) {
    vne::math::Color clr1(0.0f, 0.01f, 0.2f, 1.0f);
    vne::math::Color clr2(1.0f, 0.2f, 0.2f, 0.0f);

    vne::math::Color clr3 = clr1 - clr2;
    EXPECT_FLOAT_EQ(clr3.r(), 0.0f);
    EXPECT_FLOAT_EQ(clr3.g(), 0.0f);
    EXPECT_FLOAT_EQ(clr3.b(), 0.0f);
    EXPECT_FLOAT_EQ(clr3.a(), 1.0f);

    clr3 -= clr2;
    EXPECT_FLOAT_EQ(clr3.r(), 0.0f);
    EXPECT_FLOAT_EQ(clr3.g(), 0.0f);
    EXPECT_FLOAT_EQ(clr3.b(), 0.0f);
    EXPECT_FLOAT_EQ(clr3.a(), 1.0f);

    clr3 = clr1 - 0.005f;
    EXPECT_FLOAT_EQ(clr3.r(), 0.0f);
    EXPECT_FLOAT_EQ(clr3.g(), 0.005f);
    EXPECT_FLOAT_EQ(clr3.b(), 0.195f);
    EXPECT_FLOAT_EQ(clr3.a(), 0.995f);

    clr3 -= 0.003f;
    EXPECT_FLOAT_EQ(clr3.r(), 0.0f);
    EXPECT_FLOAT_EQ(clr3.g(), 0.002f);
    EXPECT_FLOAT_EQ(clr3.b(), 0.192f);
    EXPECT_FLOAT_EQ(clr3.a(), 0.992f);
}

/**
 * Test Color multiplication
 */
TEST_F(ColorTest, TestColorMultiplication) {
    vne::math::Color clr1(0.0f, 0.01f, 0.2f, 1.0f);
    vne::math::Color clr2(1.0f, 0.2f, 0.2f, 0.0f);

    vne::math::Color clr3 = clr1 * clr2;
    EXPECT_FLOAT_EQ(clr3.r(), 0.0f);
    EXPECT_FLOAT_EQ(clr3.g(), 0.002f);
    EXPECT_FLOAT_EQ(clr3.b(), 0.04f);
    EXPECT_FLOAT_EQ(clr3.a(), 0.0f);

    clr3 *= clr2;
    EXPECT_FLOAT_EQ(clr3.r(), 0.0f);
    EXPECT_FLOAT_EQ(clr3.g(), 0.0004f);
    EXPECT_FLOAT_EQ(clr3.b(), 0.008f);
    EXPECT_FLOAT_EQ(clr3.a(), 0.0f);

    clr3 = clr1 * 0.5f;
    EXPECT_FLOAT_EQ(clr3.r(), 0.0f);
    EXPECT_FLOAT_EQ(clr3.g(), 0.005f);
    EXPECT_FLOAT_EQ(clr3.b(), 0.1f);
    EXPECT_FLOAT_EQ(clr3.a(), 0.5f);

    clr3 *= 2.0f;
    EXPECT_FLOAT_EQ(clr3.r(), 0.0f);
    EXPECT_FLOAT_EQ(clr3.g(), 0.01f);
    EXPECT_FLOAT_EQ(clr3.b(), 0.2f);
    EXPECT_FLOAT_EQ(clr3.a(), 1.0f);
}

/**
 * Test Color division
 */
TEST_F(ColorTest, TestColorDivision) {
    vne::math::Color clr(0.0f, 0.2f, 0.5f, 1.0f);

    vne::math::Color out = clr / 0.5f;
    EXPECT_FLOAT_EQ(out.r(), 0.0f);
    EXPECT_FLOAT_EQ(out.g(), 0.4f);
    EXPECT_FLOAT_EQ(out.b(), 1.0f);
    EXPECT_FLOAT_EQ(out.a(), 1.0f);

    out /= 2.0f;
    EXPECT_FLOAT_EQ(out.r(), 0.0f);
    EXPECT_FLOAT_EQ(out.g(), 0.2f);
    EXPECT_FLOAT_EQ(out.b(), 0.5f);
    EXPECT_FLOAT_EQ(out.a(), 0.5f);

    vne::math::Color other{0.0f, 0.4f, 0.5f, 0.5f};
    out = clr / other;
    EXPECT_FLOAT_EQ(out.r(), 0.0f);
    EXPECT_FLOAT_EQ(out.g(), 0.5f);
    EXPECT_FLOAT_EQ(out.b(), 1.0f);
    EXPECT_FLOAT_EQ(out.a(), 1.0f);

    out /= other;
    EXPECT_FLOAT_EQ(out.r(), 0.0f);
    EXPECT_FLOAT_EQ(out.g(), 0.004901961f);   // Out.g() / 255; if > 1
    EXPECT_FLOAT_EQ(out.b(), 0.0078431377f);  // Out.b() / 255; if > 1
    EXPECT_FLOAT_EQ(out.a(), 1.0f);

    other.set(0.0f, 0.0f, 0.0f, 0.0f);
    out /= other;
    EXPECT_FLOAT_EQ(out.r(), 0.0f);
    EXPECT_FLOAT_EQ(out.g(), 1.0f);
    EXPECT_FLOAT_EQ(out.b(), 1.0f);
    EXPECT_FLOAT_EQ(out.a(), 1.0f);

    clr.set(0.0f, 0.0f, 0.0f, 0.0f);
    out = clr / other;
    EXPECT_FLOAT_EQ(out.r(), 0.0f);
    EXPECT_FLOAT_EQ(out.g(), 0.0f);
    EXPECT_FLOAT_EQ(out.b(), 0.0f);
    EXPECT_FLOAT_EQ(out.a(), 0.0f);
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
    EXPECT_EQ(clr.r(), clr[0]);
    EXPECT_EQ(clr.g(), clr[1]);
    EXPECT_EQ(clr.b(), clr[2]);
    EXPECT_EQ(clr.a(), clr[3]);
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

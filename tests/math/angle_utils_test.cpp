/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 * ----------------------------------------------------------------------
 */

#include <gtest/gtest.h>
#include <vertexnova/math/core/math_utils.h>

using namespace vne::math;

// ============================================================================
// Normalize Angle Tests
// ============================================================================

TEST(NormalizeAngleTest, AlreadyNormalized) {
    EXPECT_NEAR(normalizeAngle(0.0f), 0.0f, 1e-5f);
    EXPECT_NEAR(normalizeAngle(kPi), kPi, 1e-5f);
    EXPECT_NEAR(normalizeAngle(kHalfPi), kHalfPi, 1e-5f);
}

TEST(NormalizeAngleTest, NegativeAngles) {
    EXPECT_NEAR(normalizeAngle(-kPi), kPi, 1e-5f);
    EXPECT_NEAR(normalizeAngle(-kHalfPi), kTwoPi - kHalfPi, 1e-5f);
}

TEST(NormalizeAngleTest, LargeAngles) {
    EXPECT_NEAR(normalizeAngle(kTwoPi), 0.0f, 1e-5f);
    EXPECT_NEAR(normalizeAngle(kTwoPi + kHalfPi), kHalfPi, 1e-5f);
    EXPECT_NEAR(normalizeAngle(4.0f * kPi), 0.0f, 1e-5f);
}

// ============================================================================
// Normalize Angle Signed Tests
// ============================================================================

TEST(NormalizeAngleSignedTest, AlreadyNormalized) {
    EXPECT_NEAR(normalizeAngleSigned(0.0f), 0.0f, 1e-5f);
    EXPECT_NEAR(normalizeAngleSigned(kHalfPi), kHalfPi, 1e-5f);
    EXPECT_NEAR(normalizeAngleSigned(-kHalfPi), -kHalfPi, 1e-5f);
}

TEST(NormalizeAngleSignedTest, WrapAround) {
    // Just over π should wrap to negative
    EXPECT_NEAR(normalizeAngleSigned(kPi + 0.1f), -kPi + 0.1f, 1e-5f);

    // Just under -π should wrap to positive
    EXPECT_NEAR(normalizeAngleSigned(-kPi - 0.1f), kPi - 0.1f, 1e-5f);
}

// ============================================================================
// Angle Difference Tests
// ============================================================================

TEST(AngleDifferenceTest, SmallDifference) {
    EXPECT_NEAR(angleDifference(0.0f, 0.5f), 0.5f, 1e-5f);
    EXPECT_NEAR(angleDifference(0.5f, 0.0f), -0.5f, 1e-5f);
}

TEST(AngleDifferenceTest, WrapAround) {
    // From 0 to 3π/2 should go backwards (-π/2) not forwards (3π/2)
    float diff = angleDifference(0.0f, 3.0f * kHalfPi);
    EXPECT_NEAR(diff, -kHalfPi, 1e-5f);

    // From π to -π (represented as π) should be 0
    EXPECT_NEAR(angleDifference(kPi, -kPi), 0.0f, 1e-5f);
}

TEST(AngleDifferenceTest, HalfCircle) {
    // Going exactly π should work in either direction
    float diff = angleDifference(0.0f, kPi);
    EXPECT_TRUE(std::abs(diff) <= kPi + 1e-5f);
}

// ============================================================================
// Lerp Angle Tests
// ============================================================================

TEST(LerpAngleTest, Simple) {
    EXPECT_NEAR(lerpAngle(0.0f, 1.0f, 0.0f), 0.0f, 1e-5f);
    EXPECT_NEAR(lerpAngle(0.0f, 1.0f, 1.0f), 1.0f, 1e-5f);
    EXPECT_NEAR(lerpAngle(0.0f, 1.0f, 0.5f), 0.5f, 1e-5f);
}

TEST(LerpAngleTest, WrapAround) {
    // Lerp from near 0 to near 2π should go through 0, not the long way
    float from = 0.1f;
    float to = kTwoPi - 0.1f;
    float mid = lerpAngle(from, to, 0.5f);

    // Should be close to 0 (wrapped)
    float normalized = normalizeAngle(mid);
    EXPECT_TRUE(normalized < 0.2f || normalized > kTwoPi - 0.2f);
}

// ============================================================================
// Wrap Tests
// ============================================================================

TEST(WrapTest, InRange) {
    EXPECT_NEAR(wrap(5.0f, 0.0f, 10.0f), 5.0f, 1e-5f);
}

TEST(WrapTest, AboveRange) {
    EXPECT_NEAR(wrap(12.0f, 0.0f, 10.0f), 2.0f, 1e-5f);
    EXPECT_NEAR(wrap(25.0f, 0.0f, 10.0f), 5.0f, 1e-5f);
}

TEST(WrapTest, BelowRange) {
    EXPECT_NEAR(wrap(-2.0f, 0.0f, 10.0f), 8.0f, 1e-5f);
    EXPECT_NEAR(wrap(-15.0f, 0.0f, 10.0f), 5.0f, 1e-5f);
}

TEST(WrapTest, NonZeroMin) {
    EXPECT_NEAR(wrap(15.0f, 5.0f, 10.0f), 5.0f, 1e-5f);
    EXPECT_NEAR(wrap(3.0f, 5.0f, 10.0f), 8.0f, 1e-5f);
}

// ============================================================================
// Remap Tests
// ============================================================================

TEST(RemapTest, Identity) {
    EXPECT_NEAR(remap(0.5f, 0.0f, 1.0f, 0.0f, 1.0f), 0.5f, 1e-5f);
}

TEST(RemapTest, Scale) {
    EXPECT_NEAR(remap(0.5f, 0.0f, 1.0f, 0.0f, 100.0f), 50.0f, 1e-5f);
}

TEST(RemapTest, Offset) {
    EXPECT_NEAR(remap(0.5f, 0.0f, 1.0f, 10.0f, 20.0f), 15.0f, 1e-5f);
}

TEST(RemapTest, Invert) {
    EXPECT_NEAR(remap(0.25f, 0.0f, 1.0f, 1.0f, 0.0f), 0.75f, 1e-5f);
}

// ============================================================================
// Inverse Lerp Tests
// ============================================================================

TEST(InverseLerpTest, Basic) {
    EXPECT_NEAR(inverseLerp(0.0f, 10.0f, 5.0f), 0.5f, 1e-5f);
    EXPECT_NEAR(inverseLerp(0.0f, 10.0f, 0.0f), 0.0f, 1e-5f);
    EXPECT_NEAR(inverseLerp(0.0f, 10.0f, 10.0f), 1.0f, 1e-5f);
}

TEST(InverseLerpTest, OutsideRange) {
    EXPECT_NEAR(inverseLerp(0.0f, 10.0f, -5.0f), -0.5f, 1e-5f);
    EXPECT_NEAR(inverseLerp(0.0f, 10.0f, 15.0f), 1.5f, 1e-5f);
}

TEST(InverseLerpTest, EqualBounds) {
    EXPECT_NEAR(inverseLerp(5.0f, 5.0f, 5.0f), 0.0f, 1e-5f);
}

// ============================================================================
// Step Tests
// ============================================================================

TEST(StepTest, Basic) {
    EXPECT_FLOAT_EQ(step(0.5f, 0.25f), 0.0f);
    EXPECT_FLOAT_EQ(step(0.5f, 0.75f), 1.0f);
    EXPECT_FLOAT_EQ(step(0.5f, 0.5f), 1.0f);  // At edge returns 1
}

// ============================================================================
// Fract Tests
// ============================================================================

TEST(FractTest, Positive) {
    EXPECT_NEAR(fract(1.5f), 0.5f, 1e-5f);
    EXPECT_NEAR(fract(3.75f), 0.75f, 1e-5f);
}

TEST(FractTest, Negative) {
    // fract of negative is positive (based on floor)
    EXPECT_NEAR(fract(-0.25f), 0.75f, 1e-5f);
}

TEST(FractTest, Integer) {
    EXPECT_NEAR(fract(5.0f), 0.0f, 1e-5f);
}

// ============================================================================
// Mod Tests
// ============================================================================

TEST(ModTest, Positive) {
    EXPECT_NEAR(mod(5.5f, 2.0f), 1.5f, 1e-5f);
}

TEST(ModTest, Negative) {
    // Unlike fmod, mod always returns positive for positive divisor
    EXPECT_NEAR(mod(-0.5f, 2.0f), 1.5f, 1e-5f);
}

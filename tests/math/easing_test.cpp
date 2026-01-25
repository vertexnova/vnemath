/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 * ----------------------------------------------------------------------
 */

#include <gtest/gtest.h>
#include <vertexnova/math/easing.h>

using namespace vne::math;

// ============================================================================
// Smoothstep Tests
// ============================================================================

TEST(SmoothstepTest, CubicBasics) {
    // Endpoints
    EXPECT_FLOAT_EQ(smoothstep(0.0f), 0.0f);
    EXPECT_FLOAT_EQ(smoothstep(1.0f), 1.0f);

    // Midpoint
    EXPECT_FLOAT_EQ(smoothstep(0.5f), 0.5f);

    // Monotonically increasing
    EXPECT_LT(smoothstep(0.25f), smoothstep(0.5f));
    EXPECT_LT(smoothstep(0.5f), smoothstep(0.75f));
}

TEST(SmoothstepTest, CubicWithEdges) {
    EXPECT_FLOAT_EQ(smoothstep(0.0f, 1.0f, 0.0f), 0.0f);
    EXPECT_FLOAT_EQ(smoothstep(0.0f, 1.0f, 1.0f), 1.0f);
    EXPECT_FLOAT_EQ(smoothstep(0.0f, 1.0f, 0.5f), 0.5f);

    // Outside range should clamp
    EXPECT_FLOAT_EQ(smoothstep(0.0f, 1.0f, -1.0f), 0.0f);
    EXPECT_FLOAT_EQ(smoothstep(0.0f, 1.0f, 2.0f), 1.0f);

    // Custom range
    EXPECT_FLOAT_EQ(smoothstep(10.0f, 20.0f, 15.0f), 0.5f);
}

TEST(SmoothstepTest, QuinticBasics) {
    EXPECT_FLOAT_EQ(smootherstep(0.0f), 0.0f);
    EXPECT_FLOAT_EQ(smootherstep(1.0f), 1.0f);
    EXPECT_FLOAT_EQ(smootherstep(0.5f), 0.5f);

    // Smootherstep should be closer to linear in the middle
    float cubic_quarter = smoothstep(0.25f);
    float quintic_quarter = smootherstep(0.25f);
    // Quintic is "softer" - rises slower at start
    EXPECT_LT(quintic_quarter, cubic_quarter);
}

TEST(SmoothstepTest, Quartic) {
    EXPECT_FLOAT_EQ(smoothstepQuartic(0.0f), 0.0f);
    EXPECT_FLOAT_EQ(smoothstepQuartic(1.0f), 1.0f);
}

TEST(SmoothstepTest, Inverse) {
    for (float x = 0.1f; x < 1.0f; x += 0.1f) {
        float y = smoothstep(x);
        float recovered = smoothstepInverse(y);
        EXPECT_NEAR(recovered, x, 1e-5f);
    }
}

TEST(SmoothstepTest, Rational) {
    EXPECT_FLOAT_EQ(smoothstepRational(0.0f, 2.0f), 0.0f);
    EXPECT_FLOAT_EQ(smoothstepRational(1.0f, 2.0f), 1.0f);
    EXPECT_FLOAT_EQ(smoothstepRational(0.5f, 2.0f), 0.5f);
}

// ============================================================================
// Impulse Tests
// ============================================================================

TEST(ImpulseTest, ExponentialImpulse) {
    // Should peak at x = 1/k
    float k = 4.0f;
    float peak_x = 1.0f / k;
    float peak_val = expImpulse(peak_x, k);

    // Peak should be 1
    EXPECT_NEAR(peak_val, 1.0f, 1e-5f);

    // Should be less than peak before and after
    EXPECT_LT(expImpulse(peak_x * 0.5f, k), peak_val);
    EXPECT_LT(expImpulse(peak_x * 2.0f, k), peak_val);
}

TEST(ImpulseTest, PolynomialImpulse) {
    float k = 4.0f;
    float peak_x = std::sqrt(1.0f / k);
    float peak_val = polyImpulse(peak_x, k);

    EXPECT_NEAR(peak_val, 1.0f, 1e-5f);
}

// ============================================================================
// Cubic Pulse Tests
// ============================================================================

TEST(CubicPulseTest, Basics) {
    float c = 5.0f;
    float w = 2.0f;

    // At center, value is 1
    EXPECT_FLOAT_EQ(cubicPulse(c, w, c), 1.0f);

    // At edges, value is 0
    EXPECT_FLOAT_EQ(cubicPulse(c, w, c - w), 0.0f);
    EXPECT_FLOAT_EQ(cubicPulse(c, w, c + w), 0.0f);

    // Outside is 0
    EXPECT_FLOAT_EQ(cubicPulse(c, w, c - w - 1.0f), 0.0f);
    EXPECT_FLOAT_EQ(cubicPulse(c, w, c + w + 1.0f), 0.0f);

    // Symmetric
    EXPECT_FLOAT_EQ(cubicPulse(c, w, c - 1.0f), cubicPulse(c, w, c + 1.0f));
}

// ============================================================================
// Gain and Bias Tests
// ============================================================================

TEST(GainTest, Identity) {
    // k=1 should be close to identity
    for (float x = 0.0f; x <= 1.0f; x += 0.1f) {
        EXPECT_NEAR(gain(x, 1.0f), x, 0.05f);
    }
}

TEST(GainTest, Endpoints) {
    EXPECT_FLOAT_EQ(gain(0.0f, 0.5f), 0.0f);
    EXPECT_FLOAT_EQ(gain(1.0f, 0.5f), 1.0f);
    EXPECT_NEAR(gain(0.5f, 0.5f), 0.5f, 1e-5f);
}

// ============================================================================
// Parabola Tests
// ============================================================================

TEST(ParabolaTest, Basics) {
    // At corners, value is 0
    EXPECT_FLOAT_EQ(parabola(0.0f, 1.0f), 0.0f);
    EXPECT_FLOAT_EQ(parabola(1.0f, 1.0f), 0.0f);

    // At center, value is 1
    EXPECT_FLOAT_EQ(parabola(0.5f, 1.0f), 1.0f);

    // With k=2, center is still 1
    EXPECT_FLOAT_EQ(parabola(0.5f, 2.0f), 1.0f);
}

// ============================================================================
// Almost Identity Tests
// ============================================================================

TEST(AlmostIdentityTest, Basics) {
    float m = 0.5f;
    float n = 0.1f;

    // Above threshold, passes through
    EXPECT_FLOAT_EQ(almostIdentity(0.6f, m, n), 0.6f);
    EXPECT_FLOAT_EQ(almostIdentity(1.0f, m, n), 1.0f);

    // At zero, returns n
    EXPECT_FLOAT_EQ(almostIdentity(0.0f, m, n), n);
}

TEST(AlmostIdentityTest, SmoothAbs) {
    // Large values should be close to abs
    EXPECT_NEAR(smoothAbs(10.0f, 0.1f), 10.0f, 0.01f);
    EXPECT_NEAR(smoothAbs(-10.0f, 0.1f), 10.0f, 0.01f);

    // At zero, returns n
    EXPECT_FLOAT_EQ(smoothAbs(0.0f, 0.1f), 0.1f);
}

// ============================================================================
// Easing Function Tests
// ============================================================================

class EasingTest : public ::testing::Test {
   protected:
    void testEndpoints(EaseType type) {
        EXPECT_NEAR(ease(type, 0.0f), 0.0f, 1e-5f) << "Failed at t=0 for " << static_cast<int>(type);
        EXPECT_NEAR(ease(type, 1.0f), 1.0f, 1e-5f) << "Failed at t=1 for " << static_cast<int>(type);
    }
};

TEST_F(EasingTest, AllEndpoints) {
    testEndpoints(EaseType::eLinear);
    testEndpoints(EaseType::eQuadIn);
    testEndpoints(EaseType::eQuadOut);
    testEndpoints(EaseType::eQuadInOut);
    testEndpoints(EaseType::eCubicIn);
    testEndpoints(EaseType::eCubicOut);
    testEndpoints(EaseType::eCubicInOut);
    testEndpoints(EaseType::eQuartIn);
    testEndpoints(EaseType::eQuartOut);
    testEndpoints(EaseType::eQuartInOut);
    testEndpoints(EaseType::eQuintIn);
    testEndpoints(EaseType::eQuintOut);
    testEndpoints(EaseType::eQuintInOut);
    testEndpoints(EaseType::eSineIn);
    testEndpoints(EaseType::eSineOut);
    testEndpoints(EaseType::eSineInOut);
    testEndpoints(EaseType::eExpoIn);
    testEndpoints(EaseType::eExpoOut);
    testEndpoints(EaseType::eExpoInOut);
    testEndpoints(EaseType::eCircIn);
    testEndpoints(EaseType::eCircOut);
    testEndpoints(EaseType::eCircInOut);
    testEndpoints(EaseType::eBackIn);
    testEndpoints(EaseType::eBackOut);
    testEndpoints(EaseType::eBackInOut);
    testEndpoints(EaseType::eElasticIn);
    testEndpoints(EaseType::eElasticOut);
    testEndpoints(EaseType::eElasticInOut);
    testEndpoints(EaseType::eBounceIn);
    testEndpoints(EaseType::eBounceOut);
    testEndpoints(EaseType::eBounceInOut);
}

TEST_F(EasingTest, InOutSymmetry) {
    // InOut functions should pass through (0.5, 0.5)
    EXPECT_NEAR(ease(EaseType::eQuadInOut, 0.5f), 0.5f, 1e-5f);
    EXPECT_NEAR(ease(EaseType::eCubicInOut, 0.5f), 0.5f, 1e-5f);
    EXPECT_NEAR(ease(EaseType::eSineInOut, 0.5f), 0.5f, 1e-5f);
    EXPECT_NEAR(ease(EaseType::eCircInOut, 0.5f), 0.5f, 1e-5f);
}

TEST_F(EasingTest, InVsOut) {
    // Out should be faster at start than In
    EXPECT_GT(easeOutQuad(0.25f), easeInQuad(0.25f));
    EXPECT_GT(easeOutCubic(0.25f), easeInCubic(0.25f));

    // In should be faster at end than Out
    EXPECT_LT(easeInQuad(0.75f), easeOutQuad(0.75f));
}

TEST_F(EasingTest, BackOvershoot) {
    // Back easing should overshoot
    EXPECT_LT(easeInBack(0.5f), 0.0f);   // Undershoots
    EXPECT_GT(easeOutBack(0.5f), 1.0f);  // Overshoots
}

TEST_F(EasingTest, BounceMultiplePeaks) {
    // Bounce should have multiple local maxima
    float v1 = easeOutBounce(0.9f);
    float v2 = easeOutBounce(0.95f);
    float v3 = easeOutBounce(1.0f);

    // Last bounce approaches 1
    EXPECT_GT(v3, v2);
    EXPECT_GT(v3, v1);
}

// ============================================================================
// Damp Tests
// ============================================================================

TEST(DampTest, ConvergesToTarget) {
    float current = 0.0f;
    float target = 10.0f;
    float smoothing = 0.1f;
    float dt = 0.016f;

    for (int i = 0; i < 1000; ++i) {
        current = damp(current, target, smoothing, dt);
    }

    EXPECT_NEAR(current, target, 0.01f);
}

TEST(DampTest, InstantWithZeroSmoothing) {
    float current = 0.0f;
    float target = 10.0f;

    // Very small smoothing = fast convergence
    float result = damp(current, target, 0.001f, 1.0f);
    EXPECT_NEAR(result, target, 0.1f);
}

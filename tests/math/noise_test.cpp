/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 * ----------------------------------------------------------------------
 */

#include <gtest/gtest.h>
#include <vertexnova/math/noise.h>

#include <cmath>
#include <unordered_set>

using namespace vne::math;

// ============================================================================
// Perlin Noise Tests
// ============================================================================

TEST(PerlinNoiseTest, 1DRange) {
    // Perlin noise should return values roughly in [-1, 1]
    for (float x = -10.0f; x <= 10.0f; x += 0.1f) {
        float val = perlin(x);
        EXPECT_GE(val, -1.5f);  // Allow some tolerance
        EXPECT_LE(val, 1.5f);
    }
}

TEST(PerlinNoiseTest, 1DDeterministic) {
    // Same input should give same output
    float x = 3.14159f;
    float val1 = perlin(x);
    float val2 = perlin(x);
    EXPECT_FLOAT_EQ(val1, val2);
}

TEST(PerlinNoiseTest, 1DContinuity) {
    // Nearby inputs should give nearby outputs
    float x = 5.0f;
    float delta = 0.001f;

    float val1 = perlin(x);
    float val2 = perlin(x + delta);

    EXPECT_NEAR(val1, val2, 0.1f);
}

TEST(PerlinNoiseTest, 2DRange) {
    for (float x = -5.0f; x <= 5.0f; x += 0.5f) {
        for (float y = -5.0f; y <= 5.0f; y += 0.5f) {
            float val = perlin(x, y);
            EXPECT_GE(val, -1.5f);
            EXPECT_LE(val, 1.5f);
        }
    }
}

TEST(PerlinNoiseTest, 2DVec2fInput) {
    Vec2f p(3.0f, 4.0f);
    float val1 = perlin(p);
    float val2 = perlin(p.x(), p.y());
    EXPECT_FLOAT_EQ(val1, val2);
}

TEST(PerlinNoiseTest, 3DRange) {
    for (float x = -2.0f; x <= 2.0f; x += 0.5f) {
        for (float y = -2.0f; y <= 2.0f; y += 0.5f) {
            for (float z = -2.0f; z <= 2.0f; z += 0.5f) {
                float val = perlin(x, y, z);
                EXPECT_GE(val, -1.5f);
                EXPECT_LE(val, 1.5f);
            }
        }
    }
}

TEST(PerlinNoiseTest, 3DVec3fInput) {
    Vec3f p(1.0f, 2.0f, 3.0f);
    float val1 = perlin(p);
    float val2 = perlin(p.x(), p.y(), p.z());
    EXPECT_FLOAT_EQ(val1, val2);
}

TEST(PerlinNoiseTest, Variance) {
    // Noise should have variance (not constant)
    float sum = 0.0f;
    float sum_sq = 0.0f;
    int count = 0;

    for (float x = 0.0f; x < 10.0f; x += 0.1f) {
        float val = perlin(x);
        sum += val;
        sum_sq += val * val;
        count++;
    }

    float mean = sum / count;
    float variance = sum_sq / count - mean * mean;

    EXPECT_GT(variance, 0.01f);  // Should have some variance
}

// ============================================================================
// Simplex Noise Tests
// ============================================================================

TEST(SimplexNoiseTest, 2DRange) {
    for (float x = -5.0f; x <= 5.0f; x += 0.5f) {
        for (float y = -5.0f; y <= 5.0f; y += 0.5f) {
            float val = simplex(x, y);
            EXPECT_GE(val, -1.5f);
            EXPECT_LE(val, 1.5f);
        }
    }
}

TEST(SimplexNoiseTest, 2DDeterministic) {
    Vec2f p(7.5f, -3.2f);
    float val1 = simplex(p);
    float val2 = simplex(p);
    EXPECT_FLOAT_EQ(val1, val2);
}

TEST(SimplexNoiseTest, 2DContinuity) {
    Vec2f p(2.5f, 3.5f);
    Vec2f delta(0.001f, 0.001f);

    float val1 = simplex(p);
    float val2 = simplex(p + delta);

    EXPECT_NEAR(val1, val2, 0.1f);
}

TEST(SimplexNoiseTest, 3DRange) {
    for (float x = -2.0f; x <= 2.0f; x += 0.5f) {
        for (float y = -2.0f; y <= 2.0f; y += 0.5f) {
            for (float z = -2.0f; z <= 2.0f; z += 0.5f) {
                float val = simplex(x, y, z);
                EXPECT_GE(val, -1.5f);
                EXPECT_LE(val, 1.5f);
            }
        }
    }
}

TEST(SimplexNoiseTest, 3DVec3fInput) {
    Vec3f p(1.5f, 2.5f, 3.5f);
    float val1 = simplex(p);
    float val2 = simplex(p.x(), p.y(), p.z());
    EXPECT_FLOAT_EQ(val1, val2);
}

// ============================================================================
// FBM Tests
// ============================================================================

TEST(FbmTest, 2DBasics) {
    Vec2f p(5.0f, 5.0f);
    float val = fbm(p);

    EXPECT_FALSE(std::isnan(val));
    EXPECT_FALSE(std::isinf(val));
}

TEST(FbmTest, 2DOctaveInfluence) {
    Vec2f p(5.0f, 5.0f);

    // More octaves = more detail
    float val1 = fbm(p, 1);
    float val6 = fbm(p, 6);

    // Both should be valid
    EXPECT_FALSE(std::isnan(val1));
    EXPECT_FALSE(std::isnan(val6));
}

TEST(FbmTest, 3DBasics) {
    Vec3f p(3.0f, 4.0f, 5.0f);
    float val = fbm(p);

    EXPECT_FALSE(std::isnan(val));
    EXPECT_FALSE(std::isinf(val));
}

TEST(FbmTest, SimplexVersion) {
    Vec2f p(5.0f, 5.0f);
    float val = fbmSimplex(p);

    EXPECT_FALSE(std::isnan(val));
    EXPECT_FALSE(std::isinf(val));
}

TEST(FbmTest, 3DSimplexVersion) {
    Vec3f p(3.0f, 4.0f, 5.0f);
    float val = fbmSimplex(p);

    EXPECT_FALSE(std::isnan(val));
    EXPECT_FALSE(std::isinf(val));
}

// ============================================================================
// Turbulence Tests
// ============================================================================

TEST(TurbulenceTest, 2DPositive) {
    Vec2f p(5.0f, 5.0f);
    float val = turbulence(p);

    // Turbulence uses absolute value, should be positive
    EXPECT_GE(val, 0.0f);
    EXPECT_FALSE(std::isnan(val));
}

TEST(TurbulenceTest, 3DPositive) {
    Vec3f p(3.0f, 4.0f, 5.0f);
    float val = turbulence(p);

    EXPECT_GE(val, 0.0f);
    EXPECT_FALSE(std::isnan(val));
}

// ============================================================================
// Ridged Noise Tests
// ============================================================================

TEST(RidgedTest, 2DBasics) {
    Vec2f p(5.0f, 5.0f);
    float val = ridged(p);

    EXPECT_FALSE(std::isnan(val));
    EXPECT_FALSE(std::isinf(val));
}

TEST(RidgedTest, 3DBasics) {
    Vec3f p(3.0f, 4.0f, 5.0f);
    float val = ridged(p);

    EXPECT_FALSE(std::isnan(val));
    EXPECT_FALSE(std::isinf(val));
}

// ============================================================================
// Value Noise Tests
// ============================================================================

TEST(ValueNoiseTest, Range) {
    for (float x = -5.0f; x <= 5.0f; x += 0.5f) {
        for (float y = -5.0f; y <= 5.0f; y += 0.5f) {
            float val = valueNoise(x, y);
            EXPECT_GE(val, 0.0f);
            EXPECT_LE(val, 1.0f);
        }
    }
}

TEST(ValueNoiseTest, Deterministic) {
    Vec2f p(3.14f, 2.71f);
    float val1 = valueNoise(p);
    float val2 = valueNoise(p);
    EXPECT_FLOAT_EQ(val1, val2);
}

TEST(ValueNoiseTest, Continuity) {
    Vec2f p(5.0f, 5.0f);
    Vec2f delta(0.001f, 0.001f);

    float val1 = valueNoise(p);
    float val2 = valueNoise(p + delta);

    EXPECT_NEAR(val1, val2, 0.1f);
}

// ============================================================================
// Statistical Properties
// ============================================================================

TEST(NoiseStatisticsTest, PerlinMeanNearZero) {
    float sum = 0.0f;
    int count = 0;

    for (float x = 0.0f; x < 100.0f; x += 0.1f) {
        sum += perlin(x);
        count++;
    }

    float mean = sum / static_cast<float>(count);
    EXPECT_NEAR(mean, 0.0f, 0.2f);  // Mean should be near zero
}

TEST(NoiseStatisticsTest, SimplexMeanNearZero) {
    float sum = 0.0f;
    int count = 0;

    for (float x = 0.0f; x < 10.0f; x += 0.1f) {
        for (float y = 0.0f; y < 10.0f; y += 0.1f) {
            sum += simplex(x, y);
            count++;
        }
    }

    float mean = sum / static_cast<float>(count);
    EXPECT_NEAR(mean, 0.0f, 0.2f);
}

// ============================================================================
// Performance Sanity Checks
// ============================================================================

TEST(NoisePerformanceTest, SimplexVsPerlin2D) {
    // Both should complete without issues
    for (int i = 0; i < 1000; ++i) {
        float x = static_cast<float>(i) * 0.01f;
        float y = static_cast<float>(i) * 0.02f;

        volatile float p = perlin(x, y);
        volatile float s = simplex(x, y);

        (void)p;
        (void)s;
    }
}

TEST(NoisePerformanceTest, FbmMultipleOctaves) {
    Vec2f p(1.0f, 1.0f);

    for (int octaves = 1; octaves <= 8; ++octaves) {
        float val = fbm(p, octaves);
        EXPECT_FALSE(std::isnan(val));
    }
}

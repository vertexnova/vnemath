/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 * ----------------------------------------------------------------------
 */

#include <gtest/gtest.h>
#include <vertexnova/math/statistic.h>

using namespace vne::math;

TEST(StatisticTest, DefaultConstruction) {
    Statisticf stats;
    EXPECT_EQ(stats.count(), 0u);
    EXPECT_TRUE(stats.isEmpty());
}

TEST(StatisticTest, AddValue) {
    Statisticf stats;
    stats.addValue(10.0f);

    EXPECT_EQ(stats.count(), 1u);
    EXPECT_FLOAT_EQ(stats.sum(), 10.0f);
    EXPECT_FLOAT_EQ(stats.min(), 10.0f);
    EXPECT_FLOAT_EQ(stats.max(), 10.0f);
}

TEST(StatisticTest, AddMultipleValues) {
    Statisticf stats;
    stats.addValue(1.0f);
    stats.addValue(2.0f);
    stats.addValue(3.0f);
    stats.addValue(4.0f);
    stats.addValue(5.0f);

    EXPECT_EQ(stats.count(), 5u);
    EXPECT_FLOAT_EQ(stats.sum(), 15.0f);
    EXPECT_FLOAT_EQ(stats.min(), 1.0f);
    EXPECT_FLOAT_EQ(stats.max(), 5.0f);
}

TEST(StatisticTest, ConstructFromVector) {
    std::vector<float> values = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
    Statisticf stats(values);

    EXPECT_EQ(stats.count(), 5u);
    EXPECT_FLOAT_EQ(stats.sum(), 15.0f);
}

TEST(StatisticTest, AddValues) {
    Statisticf stats;
    stats.addValues({1.0f, 2.0f, 3.0f, 4.0f, 5.0f});

    EXPECT_EQ(stats.count(), 5u);
    EXPECT_FLOAT_EQ(stats.sum(), 15.0f);
}

TEST(StatisticTest, Mean) {
    Statisticf stats;
    stats.addValues({1.0f, 2.0f, 3.0f, 4.0f, 5.0f});

    EXPECT_FLOAT_EQ(stats.mean(), 3.0f);
}

TEST(StatisticTest, MeanEmpty) {
    Statisticf stats;
    EXPECT_FLOAT_EQ(stats.mean(), 0.0f);
}

TEST(StatisticTest, Range) {
    Statisticf stats;
    stats.addValues({1.0f, 5.0f, 10.0f});

    EXPECT_FLOAT_EQ(stats.range(), 9.0f);
}

TEST(StatisticTest, Variance) {
    Statisticf stats;
    // Values: 2, 4, 4, 4, 5, 5, 7, 9
    // Mean: 5
    // Variance: ((2-5)² + (4-5)² + (4-5)² + (4-5)² + (5-5)² + (5-5)² + (7-5)² + (9-5)²) / 8
    //         = (9 + 1 + 1 + 1 + 0 + 0 + 4 + 16) / 8 = 32 / 8 = 4
    stats.addValues({2.0f, 4.0f, 4.0f, 4.0f, 5.0f, 5.0f, 7.0f, 9.0f});

    EXPECT_NEAR(stats.mean(), 5.0f, 1e-5f);
    EXPECT_NEAR(stats.variance(), 4.0f, 1e-5f);
}

TEST(StatisticTest, StdDev) {
    Statisticf stats;
    stats.addValues({2.0f, 4.0f, 4.0f, 4.0f, 5.0f, 5.0f, 7.0f, 9.0f});

    EXPECT_NEAR(stats.stdDev(), 2.0f, 1e-5f);  // sqrt(4) = 2
}

TEST(StatisticTest, SampleVariance) {
    Statisticf stats;
    // For sample variance, divide by (n-1)
    stats.addValues({2.0f, 4.0f, 4.0f, 4.0f, 5.0f, 5.0f, 7.0f, 9.0f});

    // Sample variance = 32 / 7 = 4.571...
    EXPECT_NEAR(stats.sampleVariance(), 32.0f / 7.0f, 1e-5f);
}

TEST(StatisticTest, SampleStdDev) {
    Statisticf stats;
    stats.addValues({2.0f, 4.0f, 4.0f, 4.0f, 5.0f, 5.0f, 7.0f, 9.0f});

    EXPECT_NEAR(stats.sampleStdDev(), std::sqrt(32.0f / 7.0f), 1e-5f);
}

TEST(StatisticTest, RMS) {
    Statisticf stats;
    // RMS of {3, 4} = sqrt((9 + 16) / 2) = sqrt(12.5) = 3.535...
    stats.addValues({3.0f, 4.0f});

    EXPECT_NEAR(stats.rms(), std::sqrt(12.5f), 1e-5f);
}

TEST(StatisticTest, SumSquare) {
    Statisticf stats;
    stats.addValues({1.0f, 2.0f, 3.0f});

    EXPECT_FLOAT_EQ(stats.sumSquare(), 14.0f);  // 1 + 4 + 9
}

TEST(StatisticTest, CoefficientOfVariation) {
    Statisticf stats;
    stats.addValues({2.0f, 4.0f, 4.0f, 4.0f, 5.0f, 5.0f, 7.0f, 9.0f});

    // CV = stdDev / |mean| = 2 / 5 = 0.4
    EXPECT_NEAR(stats.coefficientOfVariation(), 0.4f, 1e-5f);
}

TEST(StatisticTest, Reset) {
    Statisticf stats;
    stats.addValues({1.0f, 2.0f, 3.0f});
    stats.reset();

    EXPECT_EQ(stats.count(), 0u);
    EXPECT_TRUE(stats.isEmpty());
    EXPECT_FLOAT_EQ(stats.sum(), 0.0f);
}

TEST(StatisticTest, HasVariation) {
    Statisticf stats1;
    stats1.addValues({5.0f, 5.0f, 5.0f});
    EXPECT_FALSE(stats1.hasVariation());

    Statisticf stats2;
    stats2.addValues({1.0f, 5.0f, 10.0f});
    EXPECT_TRUE(stats2.hasVariation());
}

TEST(StatisticTest, Merge) {
    Statisticf stats1;
    stats1.addValues({1.0f, 2.0f, 3.0f});

    Statisticf stats2;
    stats2.addValues({4.0f, 5.0f});

    stats1.merge(stats2);

    EXPECT_EQ(stats1.count(), 5u);
    EXPECT_FLOAT_EQ(stats1.sum(), 15.0f);
    EXPECT_FLOAT_EQ(stats1.min(), 1.0f);
    EXPECT_FLOAT_EQ(stats1.max(), 5.0f);
}

TEST(StatisticTest, DoubleType) {
    Statisticd stats;
    stats.addValues({1.0, 2.0, 3.0, 4.0, 5.0});

    EXPECT_EQ(stats.count(), 5u);
    EXPECT_DOUBLE_EQ(stats.mean(), 3.0);
}

TEST(StatisticTest, NegativeValues) {
    Statisticf stats;
    stats.addValues({-5.0f, -3.0f, 0.0f, 3.0f, 5.0f});

    EXPECT_FLOAT_EQ(stats.min(), -5.0f);
    EXPECT_FLOAT_EQ(stats.max(), 5.0f);
    EXPECT_FLOAT_EQ(stats.mean(), 0.0f);
    EXPECT_FLOAT_EQ(stats.range(), 10.0f);
}

TEST(StatisticTest, SingleValue) {
    Statisticf stats;
    stats.addValue(42.0f);

    EXPECT_FLOAT_EQ(stats.mean(), 42.0f);
    EXPECT_FLOAT_EQ(stats.variance(), 0.0f);
    EXPECT_FLOAT_EQ(stats.stdDev(), 0.0f);
    EXPECT_FLOAT_EQ(stats.min(), 42.0f);
    EXPECT_FLOAT_EQ(stats.max(), 42.0f);
}

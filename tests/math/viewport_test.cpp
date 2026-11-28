/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 * ----------------------------------------------------------------------
 */

#include <gtest/gtest.h>

#include "vertexnova/math/viewport.h"

using namespace vne::math;

TEST(ViewportTest, DefaultIsOneByOneAtOrigin) {
    Viewport vp;
    EXPECT_FLOAT_EQ(vp.x, 0.0f);
    EXPECT_FLOAT_EQ(vp.y, 0.0f);
    EXPECT_FLOAT_EQ(vp.width, 1.0f);
    EXPECT_FLOAT_EQ(vp.height, 1.0f);
    EXPECT_TRUE(vp.isValid());
}

TEST(ViewportTest, AspectRatioIsWidthOverHeight) {
    Viewport vp(800.0f, 600.0f);
    EXPECT_FLOAT_EQ(vp.aspectRatio(), 800.0f / 600.0f);
}

TEST(ViewportTest, CenterSizePositionEdges) {
    Viewport vp(10.0f, 20.0f, 100.0f, 50.0f);

    EXPECT_TRUE(vp.center().areSame(Vec2f(60.0f, 45.0f)));
    EXPECT_TRUE(vp.size().areSame(Vec2f(100.0f, 50.0f)));
    EXPECT_TRUE(vp.position().areSame(Vec2f(10.0f, 20.0f)));
    EXPECT_FLOAT_EQ(vp.right(), 110.0f);
    EXPECT_FLOAT_EQ(vp.bottom(), 70.0f);
}

TEST(ViewportTest, ToVec4MatchesComponents) {
    Viewport vp(1.0f, 2.0f, 3.0f, 4.0f);
    Vec4f v = vp.toVec4();
    EXPECT_FLOAT_EQ(v.x(), 1.0f);
    EXPECT_FLOAT_EQ(v.y(), 2.0f);
    EXPECT_FLOAT_EQ(v.z(), 3.0f);
    EXPECT_FLOAT_EQ(v.w(), 4.0f);
}

TEST(ViewportTest, ContainsIsHalfOpen) {
    Viewport vp(0.0f, 0.0f, 100.0f, 50.0f);

    EXPECT_TRUE(vp.contains(Vec2f(0.0f, 0.0f)));
    EXPECT_TRUE(vp.contains(Vec2f(99.9f, 49.9f)));
    EXPECT_FALSE(vp.contains(Vec2f(100.0f, 25.0f)));
    EXPECT_FALSE(vp.contains(Vec2f(50.0f, 50.0f)));
    EXPECT_FALSE(vp.contains(Vec2f(-0.1f, 10.0f)));
}

TEST(ViewportTest, IsValidRequiresPositiveSize) {
    EXPECT_TRUE(Viewport(10.0f, 10.0f).isValid());
    EXPECT_FALSE(Viewport(0.0f, 10.0f).isValid());
    EXPECT_FALSE(Viewport(10.0f, 0.0f).isValid());
    EXPECT_FALSE(Viewport(-1.0f, 5.0f).isValid());
}

TEST(ViewportTest, EqualityComparesAllFields) {
    Viewport a(1.0f, 2.0f, 3.0f, 4.0f, 0.0f, 1.0f);
    Viewport b(1.0f, 2.0f, 3.0f, 4.0f, 0.0f, 1.0f);
    Viewport c(1.0f, 2.0f, 3.0f, 4.0f, 0.0f, 0.5f);

    EXPECT_EQ(a, b);
    EXPECT_NE(a, c);
}

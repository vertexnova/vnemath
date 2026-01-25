/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 * ----------------------------------------------------------------------
 */

#include <gtest/gtest.h>
#include <vertexnova/math/geometry/rect.h>

using namespace vne::math;

TEST(RectTest, DefaultConstruction) {
    Rect rect;
    EXPECT_FLOAT_EQ(rect.x, 0.0f);
    EXPECT_FLOAT_EQ(rect.y, 0.0f);
    EXPECT_FLOAT_EQ(rect.width, 0.0f);
    EXPECT_FLOAT_EQ(rect.height, 0.0f);
}

TEST(RectTest, Construction) {
    Rect rect(10.0f, 20.0f, 100.0f, 50.0f);
    EXPECT_FLOAT_EQ(rect.x, 10.0f);
    EXPECT_FLOAT_EQ(rect.y, 20.0f);
    EXPECT_FLOAT_EQ(rect.width, 100.0f);
    EXPECT_FLOAT_EQ(rect.height, 50.0f);
}

TEST(RectTest, ConstructFromVectors) {
    Rect rect(Vec2f(10.0f, 20.0f), Vec2f(100.0f, 50.0f));
    EXPECT_FLOAT_EQ(rect.x, 10.0f);
    EXPECT_FLOAT_EQ(rect.y, 20.0f);
    EXPECT_FLOAT_EQ(rect.width, 100.0f);
    EXPECT_FLOAT_EQ(rect.height, 50.0f);
}

TEST(RectTest, FromCorners) {
    Rect rect = Rect::fromCorners(Vec2f(10.0f, 20.0f), Vec2f(110.0f, 70.0f));
    EXPECT_FLOAT_EQ(rect.x, 10.0f);
    EXPECT_FLOAT_EQ(rect.y, 20.0f);
    EXPECT_FLOAT_EQ(rect.width, 100.0f);
    EXPECT_FLOAT_EQ(rect.height, 50.0f);
}

TEST(RectTest, FromCenterAndHalfExtents) {
    Rect rect = Rect::fromCenterAndHalfExtents(Vec2f(100.0f, 100.0f), Vec2f(50.0f, 25.0f));
    EXPECT_FLOAT_EQ(rect.x, 50.0f);
    EXPECT_FLOAT_EQ(rect.y, 75.0f);
    EXPECT_FLOAT_EQ(rect.width, 100.0f);
    EXPECT_FLOAT_EQ(rect.height, 50.0f);
}

TEST(RectTest, FromCenterAndSize) {
    Rect rect = Rect::fromCenterAndSize(Vec2f(100.0f, 100.0f), Vec2f(100.0f, 50.0f));
    EXPECT_FLOAT_EQ(rect.x, 50.0f);
    EXPECT_FLOAT_EQ(rect.y, 75.0f);
    EXPECT_FLOAT_EQ(rect.width, 100.0f);
    EXPECT_FLOAT_EQ(rect.height, 50.0f);
}

TEST(RectTest, Accessors) {
    Rect rect(10.0f, 20.0f, 100.0f, 50.0f);

    EXPECT_EQ(rect.position(), Vec2f(10.0f, 20.0f));
    EXPECT_EQ(rect.size(), Vec2f(100.0f, 50.0f));
    EXPECT_EQ(rect.center(), Vec2f(60.0f, 45.0f));
    EXPECT_EQ(rect.halfExtents(), Vec2f(50.0f, 25.0f));
    EXPECT_EQ(rect.min(), Vec2f(10.0f, 20.0f));
    EXPECT_EQ(rect.max(), Vec2f(110.0f, 70.0f));
}

TEST(RectTest, Edges) {
    Rect rect(10.0f, 20.0f, 100.0f, 50.0f);

    EXPECT_FLOAT_EQ(rect.left(), 10.0f);
    EXPECT_FLOAT_EQ(rect.right(), 110.0f);
    EXPECT_FLOAT_EQ(rect.top(), 20.0f);
    EXPECT_FLOAT_EQ(rect.bottom(), 70.0f);
}

TEST(RectTest, AreaPerimeter) {
    Rect rect(0.0f, 0.0f, 10.0f, 5.0f);

    EXPECT_FLOAT_EQ(rect.area(), 50.0f);
    EXPECT_FLOAT_EQ(rect.perimeter(), 30.0f);
}

TEST(RectTest, AspectRatio) {
    Rect rect(0.0f, 0.0f, 16.0f, 9.0f);
    EXPECT_NEAR(rect.aspectRatio(), 16.0f / 9.0f, 1e-5f);
}

TEST(RectTest, ContainsPoint) {
    Rect rect(0.0f, 0.0f, 100.0f, 100.0f);

    EXPECT_TRUE(rect.contains(Vec2f(50.0f, 50.0f)));
    EXPECT_TRUE(rect.contains(Vec2f(0.0f, 0.0f)));
    EXPECT_TRUE(rect.contains(Vec2f(100.0f, 100.0f)));
    EXPECT_FALSE(rect.contains(Vec2f(-1.0f, 50.0f)));
    EXPECT_FALSE(rect.contains(Vec2f(101.0f, 50.0f)));
}

TEST(RectTest, ContainsExclusive) {
    Rect rect(0.0f, 0.0f, 100.0f, 100.0f);

    EXPECT_TRUE(rect.containsExclusive(Vec2f(50.0f, 50.0f)));
    EXPECT_FALSE(rect.containsExclusive(Vec2f(0.0f, 0.0f)));
    EXPECT_FALSE(rect.containsExclusive(Vec2f(100.0f, 100.0f)));
}

TEST(RectTest, ContainsRect) {
    Rect outer(0.0f, 0.0f, 100.0f, 100.0f);
    Rect inner(10.0f, 10.0f, 50.0f, 50.0f);
    Rect partial(50.0f, 50.0f, 100.0f, 100.0f);

    EXPECT_TRUE(outer.contains(inner));
    EXPECT_FALSE(outer.contains(partial));
    EXPECT_FALSE(inner.contains(outer));
}

TEST(RectTest, Intersects) {
    Rect rect1(0.0f, 0.0f, 100.0f, 100.0f);
    Rect rect2(50.0f, 50.0f, 100.0f, 100.0f);
    Rect rect3(200.0f, 200.0f, 50.0f, 50.0f);

    EXPECT_TRUE(rect1.intersects(rect2));
    EXPECT_TRUE(rect2.intersects(rect1));
    EXPECT_FALSE(rect1.intersects(rect3));
}

TEST(RectTest, Intersection) {
    Rect rect1(0.0f, 0.0f, 100.0f, 100.0f);
    Rect rect2(50.0f, 50.0f, 100.0f, 100.0f);

    Rect inter = rect1.intersection(rect2);
    EXPECT_FLOAT_EQ(inter.x, 50.0f);
    EXPECT_FLOAT_EQ(inter.y, 50.0f);
    EXPECT_FLOAT_EQ(inter.width, 50.0f);
    EXPECT_FLOAT_EQ(inter.height, 50.0f);

    // No intersection
    Rect rect3(200.0f, 200.0f, 50.0f, 50.0f);
    Rect no_inter = rect1.intersection(rect3);
    EXPECT_TRUE(no_inter.isEmpty());
}

TEST(RectTest, UnionWith) {
    Rect rect1(0.0f, 0.0f, 50.0f, 50.0f);
    Rect rect2(50.0f, 50.0f, 50.0f, 50.0f);

    Rect uni = rect1.unionWith(rect2);
    EXPECT_FLOAT_EQ(uni.x, 0.0f);
    EXPECT_FLOAT_EQ(uni.y, 0.0f);
    EXPECT_FLOAT_EQ(uni.width, 100.0f);
    EXPECT_FLOAT_EQ(uni.height, 100.0f);
}

TEST(RectTest, Expand) {
    Rect rect(10.0f, 10.0f, 50.0f, 50.0f);
    rect.expand(Vec2f(0.0f, 0.0f));

    EXPECT_FLOAT_EQ(rect.x, 0.0f);
    EXPECT_FLOAT_EQ(rect.y, 0.0f);
    EXPECT_FLOAT_EQ(rect.right(), 60.0f);
    EXPECT_FLOAT_EQ(rect.bottom(), 60.0f);
}

TEST(RectTest, Expanded) {
    Rect rect(10.0f, 10.0f, 50.0f, 50.0f);
    Rect expanded = rect.expanded(5.0f);

    EXPECT_FLOAT_EQ(expanded.x, 5.0f);
    EXPECT_FLOAT_EQ(expanded.y, 5.0f);
    EXPECT_FLOAT_EQ(expanded.width, 60.0f);
    EXPECT_FLOAT_EQ(expanded.height, 60.0f);
}

TEST(RectTest, Translated) {
    Rect rect(0.0f, 0.0f, 50.0f, 50.0f);
    Rect moved = rect.translated(Vec2f(10.0f, 20.0f));

    EXPECT_FLOAT_EQ(moved.x, 10.0f);
    EXPECT_FLOAT_EQ(moved.y, 20.0f);
    EXPECT_FLOAT_EQ(moved.width, 50.0f);
    EXPECT_FLOAT_EQ(moved.height, 50.0f);
}

TEST(RectTest, Scaled) {
    Rect rect(0.0f, 0.0f, 100.0f, 100.0f);
    Rect scaled = rect.scaled(0.5f);

    // Scaled from center
    EXPECT_FLOAT_EQ(scaled.center().x(), 50.0f);
    EXPECT_FLOAT_EQ(scaled.center().y(), 50.0f);
    EXPECT_FLOAT_EQ(scaled.width, 50.0f);
    EXPECT_FLOAT_EQ(scaled.height, 50.0f);
}

TEST(RectTest, Validation) {
    Rect valid(0.0f, 0.0f, 100.0f, 100.0f);
    EXPECT_TRUE(valid.isValid());
    EXPECT_FALSE(valid.isEmpty());

    Rect empty;
    EXPECT_FALSE(empty.isValid());
    EXPECT_TRUE(empty.isEmpty());

    Rect negative(0.0f, 0.0f, -10.0f, 10.0f);
    EXPECT_FALSE(negative.isValid());
    EXPECT_TRUE(negative.isEmpty());
}

TEST(RectTest, Comparison) {
    Rect rect1(10.0f, 20.0f, 100.0f, 50.0f);
    Rect rect2(10.0f, 20.0f, 100.0f, 50.0f);
    Rect rect3(10.0f, 20.0f, 100.0f, 51.0f);

    EXPECT_TRUE(rect1 == rect2);
    EXPECT_FALSE(rect1 == rect3);
    EXPECT_TRUE(rect1.areSame(rect2));
}

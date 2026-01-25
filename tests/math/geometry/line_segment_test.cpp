/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 * ----------------------------------------------------------------------
 */

#include <gtest/gtest.h>
#include <vertexnova/math/geometry/line_segment.h>

using namespace vne::math;

TEST(LineSegmentTest, DefaultConstruction) {
    LineSegment seg;
    EXPECT_EQ(seg.start, Vec3f::zero());
    EXPECT_EQ(seg.end, Vec3f::zero());
}

TEST(LineSegmentTest, Construction) {
    LineSegment seg(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(1.0f, 0.0f, 0.0f));
    EXPECT_EQ(seg.start, Vec3f(0.0f, 0.0f, 0.0f));
    EXPECT_EQ(seg.end, Vec3f(1.0f, 0.0f, 0.0f));
}

TEST(LineSegmentTest, Direction) {
    LineSegment seg(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(2.0f, 0.0f, 0.0f));

    Vec3f dir = seg.direction();
    EXPECT_EQ(dir, Vec3f(2.0f, 0.0f, 0.0f));

    Vec3f norm_dir = seg.normalizedDirection();
    EXPECT_NEAR(norm_dir.x(), 1.0f, 1e-5f);
    EXPECT_NEAR(norm_dir.y(), 0.0f, 1e-5f);
    EXPECT_NEAR(norm_dir.z(), 0.0f, 1e-5f);
}

TEST(LineSegmentTest, Length) {
    LineSegment seg(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(3.0f, 4.0f, 0.0f));

    EXPECT_NEAR(seg.length(), 5.0f, 1e-5f);
    EXPECT_NEAR(seg.lengthSquared(), 25.0f, 1e-5f);
}

TEST(LineSegmentTest, Midpoint) {
    LineSegment seg(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(10.0f, 0.0f, 0.0f));

    Vec3f mid = seg.midpoint();
    EXPECT_NEAR(mid.x(), 5.0f, 1e-5f);
    EXPECT_NEAR(mid.y(), 0.0f, 1e-5f);
    EXPECT_NEAR(mid.z(), 0.0f, 1e-5f);
}

TEST(LineSegmentTest, GetPoint) {
    LineSegment seg(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(10.0f, 0.0f, 0.0f));

    EXPECT_EQ(seg.getPoint(0.0f), seg.start);
    EXPECT_EQ(seg.getPoint(1.0f), seg.end);
    EXPECT_EQ(seg.getPoint(0.5f), Vec3f(5.0f, 0.0f, 0.0f));
}

TEST(LineSegmentTest, ClosestPointOnSegment) {
    LineSegment seg(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(10.0f, 0.0f, 0.0f));

    // Point perpendicular to middle
    Vec3f p1 = seg.closestPoint(Vec3f(5.0f, 5.0f, 0.0f));
    EXPECT_NEAR(p1.x(), 5.0f, 1e-5f);
    EXPECT_NEAR(p1.y(), 0.0f, 1e-5f);

    // Point before start
    Vec3f p2 = seg.closestPoint(Vec3f(-5.0f, 0.0f, 0.0f));
    EXPECT_EQ(p2, seg.start);

    // Point after end
    Vec3f p3 = seg.closestPoint(Vec3f(15.0f, 0.0f, 0.0f));
    EXPECT_EQ(p3, seg.end);
}

TEST(LineSegmentTest, ClosestPointWithT) {
    LineSegment seg(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(10.0f, 0.0f, 0.0f));

    float t;
    Vec3f p = seg.closestPoint(Vec3f(5.0f, 5.0f, 0.0f), t);

    EXPECT_NEAR(t, 0.5f, 1e-5f);
    EXPECT_NEAR(p.x(), 5.0f, 1e-5f);
}

TEST(LineSegmentTest, Distance) {
    LineSegment seg(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(10.0f, 0.0f, 0.0f));

    // Distance perpendicular to segment
    EXPECT_NEAR(seg.distanceToPoint(Vec3f(5.0f, 3.0f, 0.0f)), 3.0f, 1e-5f);

    // Distance to start
    EXPECT_NEAR(seg.distanceToPoint(Vec3f(-3.0f, 4.0f, 0.0f)), 5.0f, 1e-5f);
}

TEST(LineSegmentTest, Degenerate) {
    LineSegment seg(Vec3f(1.0f, 2.0f, 3.0f), Vec3f(1.0f, 2.0f, 3.0f));

    EXPECT_TRUE(seg.isDegenerate());
    EXPECT_FALSE(seg.isValid());

    LineSegment valid(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(1.0f, 0.0f, 0.0f));
    EXPECT_FALSE(valid.isDegenerate());
    EXPECT_TRUE(valid.isValid());
}

TEST(LineSegmentTest, Reversed) {
    LineSegment seg(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(1.0f, 2.0f, 3.0f));
    LineSegment rev = seg.reversed();

    EXPECT_EQ(rev.start, seg.end);
    EXPECT_EQ(rev.end, seg.start);
}

TEST(LineSegmentTest, Translated) {
    LineSegment seg(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(1.0f, 0.0f, 0.0f));
    LineSegment moved = seg.translated(Vec3f(10.0f, 20.0f, 30.0f));

    EXPECT_EQ(moved.start, Vec3f(10.0f, 20.0f, 30.0f));
    EXPECT_EQ(moved.end, Vec3f(11.0f, 20.0f, 30.0f));
}

TEST(LineSegmentTest, Comparison) {
    LineSegment seg1(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(1.0f, 0.0f, 0.0f));
    LineSegment seg2(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(1.0f, 0.0f, 0.0f));
    LineSegment seg3(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(2.0f, 0.0f, 0.0f));

    EXPECT_TRUE(seg1 == seg2);
    EXPECT_FALSE(seg1 == seg3);
    EXPECT_TRUE(seg1.areSame(seg2));
}

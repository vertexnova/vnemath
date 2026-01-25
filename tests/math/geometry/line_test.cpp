/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 * ----------------------------------------------------------------------
 */

#include <gtest/gtest.h>
#include <vertexnova/math/geometry/line.h>

using namespace vne::math;

TEST(LineTest, DefaultConstruction) {
    Line line;
    EXPECT_EQ(line.point, Vec3f::zero());
    EXPECT_EQ(line.dir, Vec3f::zAxis());
}

TEST(LineTest, Construction) {
    Line line(Vec3f(1.0f, 2.0f, 3.0f), Vec3f(1.0f, 0.0f, 0.0f));
    EXPECT_EQ(line.point, Vec3f(1.0f, 2.0f, 3.0f));
    EXPECT_NEAR(line.dir.length(), 1.0f, 1e-5f);  // Should be normalized
}

TEST(LineTest, ConstructFromRay) {
    Ray ray(Vec3f(1.0f, 2.0f, 3.0f), Vec3f(0.0f, 1.0f, 0.0f));
    Line line(ray);

    EXPECT_EQ(line.point, ray.origin());
    EXPECT_EQ(line.dir, ray.direction());
}

TEST(LineTest, ConstructFromLineSegment) {
    LineSegment seg(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(10.0f, 0.0f, 0.0f));
    Line line(seg);

    EXPECT_EQ(line.point, seg.start);
    EXPECT_NEAR(line.dir.x(), 1.0f, 1e-5f);
}

TEST(LineTest, FromPoints) {
    Line line = Line::fromPoints(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(1.0f, 0.0f, 0.0f));

    EXPECT_EQ(line.point, Vec3f::zero());
    EXPECT_NEAR(line.dir.x(), 1.0f, 1e-5f);
}

TEST(LineTest, GetPoint) {
    Line line(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(1.0f, 0.0f, 0.0f));

    EXPECT_EQ(line.getPoint(0.0f), Vec3f::zero());
    EXPECT_EQ(line.getPoint(5.0f), Vec3f(5.0f, 0.0f, 0.0f));
    EXPECT_EQ(line.getPoint(-3.0f), Vec3f(-3.0f, 0.0f, 0.0f));
}

TEST(LineTest, ClosestPoint) {
    Line line(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(1.0f, 0.0f, 0.0f));

    // Point directly above the line
    Vec3f p = line.closestPoint(Vec3f(5.0f, 10.0f, 0.0f));
    EXPECT_NEAR(p.x(), 5.0f, 1e-5f);
    EXPECT_NEAR(p.y(), 0.0f, 1e-5f);
}

TEST(LineTest, ClosestPointWithT) {
    Line line(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(1.0f, 0.0f, 0.0f));

    float t;
    Vec3f p = line.closestPoint(Vec3f(5.0f, 10.0f, 0.0f), t);

    EXPECT_NEAR(t, 5.0f, 1e-5f);
    EXPECT_NEAR(p.x(), 5.0f, 1e-5f);
}

TEST(LineTest, Distance) {
    Line line(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(1.0f, 0.0f, 0.0f));

    EXPECT_NEAR(line.distanceToPoint(Vec3f(0.0f, 5.0f, 0.0f)), 5.0f, 1e-5f);
    EXPECT_NEAR(line.distanceToPoint(Vec3f(100.0f, 3.0f, 4.0f)), 5.0f, 1e-5f);
}

TEST(LineTest, Contains) {
    Line line(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(1.0f, 0.0f, 0.0f));

    EXPECT_TRUE(line.contains(Vec3f(0.0f, 0.0f, 0.0f)));
    EXPECT_TRUE(line.contains(Vec3f(100.0f, 0.0f, 0.0f)));
    EXPECT_TRUE(line.contains(Vec3f(-50.0f, 0.0f, 0.0f)));
    EXPECT_FALSE(line.contains(Vec3f(0.0f, 1.0f, 0.0f)));
}

TEST(LineTest, IsParallel) {
    Line line1(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(1.0f, 0.0f, 0.0f));
    Line line2(Vec3f(0.0f, 10.0f, 0.0f), Vec3f(1.0f, 0.0f, 0.0f));
    Line line3(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.0f, 1.0f, 0.0f));

    EXPECT_TRUE(line1.isParallel(line2));
    EXPECT_FALSE(line1.isParallel(line3));
}

TEST(LineTest, IsSame) {
    Line line1(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(1.0f, 0.0f, 0.0f));
    Line line2(Vec3f(5.0f, 0.0f, 0.0f), Vec3f(1.0f, 0.0f, 0.0f));   // Same line, different point
    Line line3(Vec3f(0.0f, 10.0f, 0.0f), Vec3f(1.0f, 0.0f, 0.0f));  // Parallel but different

    EXPECT_TRUE(line1.isSame(line2));
    EXPECT_FALSE(line1.isSame(line3));
}

TEST(LineTest, LineToLineDistance) {
    // Parallel lines
    Line line1(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(1.0f, 0.0f, 0.0f));
    Line line2(Vec3f(0.0f, 5.0f, 0.0f), Vec3f(1.0f, 0.0f, 0.0f));

    EXPECT_NEAR(line1.distanceToLine(line2), 5.0f, 1e-5f);

    // Skew lines
    Line line3(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(1.0f, 0.0f, 0.0f));
    Line line4(Vec3f(0.0f, 0.0f, 3.0f), Vec3f(0.0f, 1.0f, 0.0f));

    EXPECT_NEAR(line3.distanceToLine(line4), 3.0f, 1e-5f);
}

TEST(LineTest, IsValid) {
    Line valid(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(1.0f, 0.0f, 0.0f));
    EXPECT_TRUE(valid.isValid());
}

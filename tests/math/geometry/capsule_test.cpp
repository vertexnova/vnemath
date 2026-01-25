/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Author:    Ajeet Singh Yadav
 * Created:   January 2026
 *
 * Autodoc:   yes
 * ----------------------------------------------------------------------
 */

#include <gtest/gtest.h>

#include "vertexnova/math/geometry/aabb.h"
#include "vertexnova/math/geometry/capsule.h"
#include "vertexnova/math/geometry/sphere.h"

namespace vne::math {

class CapsuleTest : public ::testing::Test {
   protected:
    void SetUp() override {
        // Default capsule along Y axis
        default_capsule_ = Capsule();

        // Custom capsule
        custom_capsule_ = Capsule(Vec3f(0, -1, 0), Vec3f(0, 1, 0), 0.5f);
    }

    Capsule default_capsule_;
    Capsule custom_capsule_;
};

TEST_F(CapsuleTest, DefaultConstructor) {
    Capsule capsule;
    EXPECT_TRUE(capsule.isValid());
    EXPECT_EQ(capsule.radius(), 0.5f);
}

TEST_F(CapsuleTest, ParameterizedConstructor) {
    Capsule capsule(Vec3f(0, 0, 0), Vec3f(0, 2, 0), 1.0f);

    EXPECT_EQ(capsule.start(), Vec3f::zero());
    EXPECT_EQ(capsule.end(), Vec3f(0, 2, 0));
    EXPECT_EQ(capsule.radius(), 1.0f);
}

TEST_F(CapsuleTest, FromLineSegment) {
    LineSegment segment(Vec3f(0, 0, 0), Vec3f(1, 0, 0));
    Capsule capsule(segment, 0.25f);

    EXPECT_EQ(capsule.start(), segment.start);
    EXPECT_EQ(capsule.end(), segment.end);
    EXPECT_EQ(capsule.radius(), 0.25f);
}

TEST_F(CapsuleTest, FromCenterHeightRadius) {
    Capsule capsule = Capsule::fromCenterHeightRadius(Vec3f(0, 0, 0), 4.0f, 1.0f);

    // Height = 4, radius = 1, so segment length = 4 - 2*1 = 2
    EXPECT_NEAR(capsule.segmentLength(), 2.0f, kFloatEpsilon);
    EXPECT_EQ(capsule.center(), Vec3f::zero());
    EXPECT_EQ(capsule.radius(), 1.0f);
}

TEST_F(CapsuleTest, FromCenterDirectionLengthRadius) {
    Capsule capsule = Capsule::fromCenterDirectionLengthRadius(Vec3f(0, 0, 0), Vec3f(1, 0, 0), 2.0f, 0.5f);

    EXPECT_EQ(capsule.center(), Vec3f::zero());
    EXPECT_NEAR(capsule.segmentLength(), 2.0f, kFloatEpsilon);
    EXPECT_EQ(capsule.radius(), 0.5f);
    EXPECT_EQ(capsule.start(), Vec3f(-1, 0, 0));
    EXPECT_EQ(capsule.end(), Vec3f(1, 0, 0));
}

TEST_F(CapsuleTest, Center) {
    Capsule capsule(Vec3f(0, -2, 0), Vec3f(0, 2, 0), 1.0f);
    EXPECT_EQ(capsule.center(), Vec3f::zero());
}

TEST_F(CapsuleTest, Direction) {
    Capsule capsule(Vec3f(0, 0, 0), Vec3f(1, 0, 0), 0.5f);

    EXPECT_EQ(capsule.direction(), Vec3f(1, 0, 0));
    EXPECT_TRUE(capsule.normalizedDirection().areSame(Vec3f(1, 0, 0)));
}

TEST_F(CapsuleTest, SegmentLength) {
    Capsule capsule(Vec3f(0, 0, 0), Vec3f(3, 0, 0), 0.5f);
    EXPECT_FLOAT_EQ(capsule.segmentLength(), 3.0f);
}

TEST_F(CapsuleTest, Height) {
    Capsule capsule(Vec3f(0, 0, 0), Vec3f(0, 2, 0), 0.5f);
    // Height = segment length + 2 * radius = 2 + 1 = 3
    EXPECT_FLOAT_EQ(capsule.height(), 3.0f);
}

TEST_F(CapsuleTest, Diameter) {
    Capsule capsule(Vec3f::zero(), Vec3f(0, 1, 0), 1.5f);
    EXPECT_FLOAT_EQ(capsule.diameter(), 3.0f);
}

TEST_F(CapsuleTest, Volume) {
    // Volume = cylinder + sphere
    // Cylinder: pi * r^2 * h
    // Sphere: (4/3) * pi * r^3
    Capsule capsule(Vec3f(0, 0, 0), Vec3f(0, 2, 0), 1.0f);

    float cylinder_volume = kPi * 1.0f * 1.0f * 2.0f;  // pi * r^2 * h
    float sphere_volume = (4.0f / 3.0f) * kPi * 1.0f * 1.0f * 1.0f;
    float expected_volume = cylinder_volume + sphere_volume;

    EXPECT_NEAR(capsule.volume(), expected_volume, 0.001f);
}

TEST_F(CapsuleTest, SurfaceArea) {
    // Surface = cylinder lateral + sphere
    Capsule capsule(Vec3f(0, 0, 0), Vec3f(0, 2, 0), 1.0f);

    float cylinder_area = 2.0f * kPi * 1.0f * 2.0f;  // 2*pi*r*h
    float sphere_area = 4.0f * kPi * 1.0f * 1.0f;    // 4*pi*r^2
    float expected_area = cylinder_area + sphere_area;

    EXPECT_NEAR(capsule.surfaceArea(), expected_area, 0.001f);
}

TEST_F(CapsuleTest, GetAabb) {
    Capsule capsule(Vec3f(0, -1, 0), Vec3f(0, 1, 0), 0.5f);
    Aabb aabb = capsule.getAabb();

    EXPECT_EQ(aabb.min(), Vec3f(-0.5f, -1.5f, -0.5f));
    EXPECT_EQ(aabb.max(), Vec3f(0.5f, 1.5f, 0.5f));
}

TEST_F(CapsuleTest, Translate) {
    Capsule capsule(Vec3f(0, 0, 0), Vec3f(0, 1, 0), 0.5f);
    capsule.translate(Vec3f(1, 2, 3));

    EXPECT_EQ(capsule.start(), Vec3f(1, 2, 3));
    EXPECT_EQ(capsule.end(), Vec3f(1, 3, 3));
}

TEST_F(CapsuleTest, Grow) {
    Capsule capsule(Vec3f::zero(), Vec3f(0, 1, 0), 0.5f);
    capsule.grow(0.25f);

    EXPECT_FLOAT_EQ(capsule.radius(), 0.75f);
}

TEST_F(CapsuleTest, IsValid) {
    Capsule valid(Vec3f::zero(), Vec3f(0, 1, 0), 0.5f);
    EXPECT_TRUE(valid.isValid());

    Capsule invalid(Vec3f::zero(), Vec3f(0, 1, 0), -0.5f);
    EXPECT_FALSE(invalid.isValid());
}

TEST_F(CapsuleTest, IsDegenerate) {
    // Zero length segment
    Capsule degenerate(Vec3f::zero(), Vec3f::zero(), 0.5f);
    EXPECT_TRUE(degenerate.isDegenerate());

    Capsule normal(Vec3f::zero(), Vec3f(1, 0, 0), 0.5f);
    EXPECT_FALSE(normal.isDegenerate());
}

TEST_F(CapsuleTest, ContainsPoint) {
    Capsule capsule(Vec3f(0, -1, 0), Vec3f(0, 1, 0), 0.5f);

    // Center should be inside
    EXPECT_TRUE(capsule.contains(Vec3f::zero()));

    // Point on segment within radius
    EXPECT_TRUE(capsule.contains(Vec3f(0.4f, 0, 0)));

    // Point outside
    EXPECT_FALSE(capsule.contains(Vec3f(1, 0, 0)));

    // Point in hemispherical cap
    EXPECT_TRUE(capsule.contains(Vec3f(0, 1.4f, 0)));
    EXPECT_FALSE(capsule.contains(Vec3f(0, 2.0f, 0)));
}

TEST_F(CapsuleTest, ClosestPointOnSegment) {
    Capsule capsule(Vec3f(0, -1, 0), Vec3f(0, 1, 0), 0.5f);

    // Point directly at center
    Vec3f closest = capsule.closestPointOnSegment(Vec3f(2, 0, 0));
    EXPECT_TRUE(closest.areSame(Vec3f(0, 0, 0)));

    // Point beyond end
    closest = capsule.closestPointOnSegment(Vec3f(0, 5, 0));
    EXPECT_TRUE(closest.areSame(Vec3f(0, 1, 0)));
}

TEST_F(CapsuleTest, DistanceToPoint) {
    Capsule capsule(Vec3f(0, -1, 0), Vec3f(0, 1, 0), 0.5f);

    // Point inside
    EXPECT_FLOAT_EQ(capsule.distanceToPoint(Vec3f::zero()), 0.0f);

    // Point at radius distance
    EXPECT_NEAR(capsule.distanceToPoint(Vec3f(0.5f, 0, 0)), 0.0f, kFloatEpsilon);

    // Point outside
    EXPECT_NEAR(capsule.distanceToPoint(Vec3f(1.5f, 0, 0)), 1.0f, kFloatEpsilon);
}

TEST_F(CapsuleTest, SignedDistance) {
    Capsule capsule(Vec3f(0, -1, 0), Vec3f(0, 1, 0), 0.5f);

    // Inside (negative)
    EXPECT_LT(capsule.signedDistanceToPoint(Vec3f::zero()), 0.0f);

    // On surface (zero)
    EXPECT_NEAR(capsule.signedDistanceToPoint(Vec3f(0.5f, 0, 0)), 0.0f, kFloatEpsilon);

    // Outside (positive)
    EXPECT_GT(capsule.signedDistanceToPoint(Vec3f(1.0f, 0, 0)), 0.0f);
}

TEST_F(CapsuleTest, IntersectsCapsule) {
    Capsule c1(Vec3f(0, -1, 0), Vec3f(0, 1, 0), 0.5f);
    Capsule c2(Vec3f(0.8f, -1, 0), Vec3f(0.8f, 1, 0), 0.5f);  // Overlapping

    EXPECT_TRUE(c1.intersects(c2));

    Capsule c3(Vec3f(5, 0, 0), Vec3f(5, 2, 0), 0.5f);  // Far away
    EXPECT_FALSE(c1.intersects(c3));
}

TEST_F(CapsuleTest, IntersectsSphere) {
    Capsule capsule(Vec3f(0, -1, 0), Vec3f(0, 1, 0), 0.5f);

    Sphere sphere_inside(Vec3f::zero(), 0.3f);
    EXPECT_TRUE(capsule.intersects(sphere_inside));

    // Sphere at distance 1.0 with radius 0.5 just touches capsule with radius 0.5
    Sphere sphere_touching(Vec3f(1.0f, 0, 0), 0.5f);
    EXPECT_TRUE(capsule.intersects(sphere_touching));

    // Sphere too far to touch
    Sphere sphere_not_touching(Vec3f(1.5f, 0, 0), 0.5f);
    EXPECT_FALSE(capsule.intersects(sphere_not_touching));

    Sphere sphere_outside(Vec3f(5, 0, 0), 0.5f);
    EXPECT_FALSE(capsule.intersects(sphere_outside));
}

TEST_F(CapsuleTest, Comparison) {
    Capsule c1(Vec3f(0, 0, 0), Vec3f(0, 1, 0), 0.5f);
    Capsule c2(Vec3f(0, 0, 0), Vec3f(0, 1, 0), 0.5f);
    Capsule c3(Vec3f(0, 0, 0), Vec3f(0, 2, 0), 0.5f);

    EXPECT_TRUE(c1 == c2);
    EXPECT_FALSE(c1 == c3);
    EXPECT_TRUE(c1.areSame(c2));
}

}  // namespace vne::math

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
#include "vertexnova/math/geometry/obb.h"

namespace vne::math {

class ObbTest : public ::testing::Test {
   protected:
    void SetUp() override {
        // Default unit OBB at origin
        unit_obb_ = Obb();

        // Rotated OBB
        Quatf rotation = Quatf::fromAxisAngle(Vec3f::yAxis(), degToRad(45.0f));
        rotated_obb_ = Obb(Vec3f(0, 0, 0), Vec3f(1, 2, 1), rotation);
    }

    Obb unit_obb_;
    Obb rotated_obb_;
};

TEST_F(ObbTest, DefaultConstructor) {
    Obb obb;
    EXPECT_TRUE(obb.isValid());
    EXPECT_EQ(obb.center(), Vec3f::zero());
    EXPECT_EQ(obb.halfExtents(), Vec3f(0.5f, 0.5f, 0.5f));
}

TEST_F(ObbTest, ParameterizedConstructor) {
    Vec3f center(1, 2, 3);
    Vec3f half_extents(2, 3, 4);
    Quatf orientation = Quatf::fromAxisAngle(Vec3f::zAxis(), degToRad(30.0f));

    Obb obb(center, half_extents, orientation);

    EXPECT_EQ(obb.center(), center);
    EXPECT_EQ(obb.halfExtents(), half_extents);
    EXPECT_TRUE(obb.orientation().approxEquals(orientation));
}

TEST_F(ObbTest, FromAabb) {
    Aabb aabb(Vec3f(-1, -2, -3), Vec3f(1, 2, 3));
    Obb obb = Obb::fromAabb(aabb);

    EXPECT_EQ(obb.center(), Vec3f::zero());
    EXPECT_TRUE(obb.halfExtents().areSame(Vec3f(1, 2, 3)));
    EXPECT_TRUE(obb.orientation().approxEquals(Quatf::identity()));
}

TEST_F(ObbTest, FromMinMax) {
    Obb obb = Obb::fromMinMax(Vec3f(-2, -2, -2), Vec3f(2, 2, 2));

    EXPECT_EQ(obb.center(), Vec3f::zero());
    EXPECT_EQ(obb.halfExtents(), Vec3f(2, 2, 2));
}

TEST_F(ObbTest, Size) {
    Obb obb(Vec3f::zero(), Vec3f(1, 2, 3));
    Vec3f size = obb.size();

    EXPECT_EQ(size.x(), 2.0f);
    EXPECT_EQ(size.y(), 4.0f);
    EXPECT_EQ(size.z(), 6.0f);
}

TEST_F(ObbTest, Volume) {
    Obb obb(Vec3f::zero(), Vec3f(1, 1, 1));
    EXPECT_FLOAT_EQ(obb.volume(), 8.0f);  // 2*2*2

    Obb obb2(Vec3f::zero(), Vec3f(1, 2, 3));
    EXPECT_FLOAT_EQ(obb2.volume(), 48.0f);  // 2*4*6
}

TEST_F(ObbTest, LocalAxes) {
    // Identity orientation - axes should match world axes
    Obb obb(Vec3f::zero(), Vec3f(1, 1, 1), Quatf::identity());

    EXPECT_TRUE(obb.axisX().areSame(Vec3f::xAxis()));
    EXPECT_TRUE(obb.axisY().areSame(Vec3f::yAxis()));
    EXPECT_TRUE(obb.axisZ().areSame(Vec3f::zAxis()));
}

TEST_F(ObbTest, ContainsPoint) {
    Obb obb(Vec3f::zero(), Vec3f(1, 1, 1));

    EXPECT_TRUE(obb.contains(Vec3f::zero()));
    EXPECT_TRUE(obb.contains(Vec3f(0.5f, 0.5f, 0.5f)));
    EXPECT_TRUE(obb.contains(Vec3f(-1.0f, -1.0f, -1.0f)));
    EXPECT_FALSE(obb.contains(Vec3f(1.5f, 0, 0)));
}

TEST_F(ObbTest, ContainsPointRotated) {
    Quatf rotation = Quatf::fromAxisAngle(Vec3f::zAxis(), degToRad(45.0f));
    Obb obb(Vec3f::zero(), Vec3f(1, 0.5f, 0.5f), rotation);

    // Point on rotated X axis should be inside
    Vec3f point_on_axis = rotation.rotate(Vec3f(0.9f, 0, 0));
    EXPECT_TRUE(obb.contains(point_on_axis));

    // Point far outside should not be inside
    EXPECT_FALSE(obb.contains(Vec3f(5, 5, 5)));
}

TEST_F(ObbTest, ClosestPoint) {
    Obb obb(Vec3f::zero(), Vec3f(1, 1, 1));

    // Point inside returns the point
    Vec3f inside(0.5f, 0.5f, 0.5f);
    EXPECT_TRUE(obb.closestPoint(inside).areSame(inside));

    // Point outside on X axis
    Vec3f outside(3, 0, 0);
    Vec3f closest = obb.closestPoint(outside);
    EXPECT_NEAR(closest.x(), 1.0f, kFloatEpsilon);
    EXPECT_NEAR(closest.y(), 0.0f, kFloatEpsilon);
    EXPECT_NEAR(closest.z(), 0.0f, kFloatEpsilon);
}

TEST_F(ObbTest, DistanceToPoint) {
    Obb obb(Vec3f::zero(), Vec3f(1, 1, 1));

    EXPECT_FLOAT_EQ(obb.distanceToPoint(Vec3f::zero()), 0.0f);
    EXPECT_FLOAT_EQ(obb.distanceToPoint(Vec3f(2, 0, 0)), 1.0f);
    EXPECT_FLOAT_EQ(obb.distanceToPoint(Vec3f(3, 0, 0)), 2.0f);
}

TEST_F(ObbTest, Corners) {
    Obb obb(Vec3f::zero(), Vec3f(1, 1, 1));

    Vec3f corners[8];
    obb.getCorners(corners);

    // All corners should be at distance sqrt(3) from center
    for (int i = 0; i < 8; ++i) {
        EXPECT_NEAR(corners[i].length(), std::sqrt(3.0f), kFloatEpsilon);
    }
}

TEST_F(ObbTest, GetAabb) {
    // Axis-aligned OBB should return same as AABB
    Obb obb(Vec3f::zero(), Vec3f(1, 2, 3));
    Aabb aabb = obb.getAabb();

    EXPECT_TRUE(aabb.min().areSame(Vec3f(-1, -2, -3)));
    EXPECT_TRUE(aabb.max().areSame(Vec3f(1, 2, 3)));
}

TEST_F(ObbTest, Translate) {
    Obb obb(Vec3f::zero(), Vec3f(1, 1, 1));
    obb.translate(Vec3f(5, 10, 15));

    EXPECT_EQ(obb.center(), Vec3f(5, 10, 15));
}

TEST_F(ObbTest, Scale) {
    Obb obb(Vec3f::zero(), Vec3f(1, 1, 1));
    obb.scale(2.0f);

    EXPECT_EQ(obb.halfExtents(), Vec3f(2, 2, 2));
}

TEST_F(ObbTest, IntersectsObb) {
    Obb obb1(Vec3f::zero(), Vec3f(1, 1, 1));
    Obb obb2(Vec3f(1, 0, 0), Vec3f(1, 1, 1));  // Overlapping

    EXPECT_TRUE(obb1.intersects(obb2));

    Obb obb3(Vec3f(10, 0, 0), Vec3f(1, 1, 1));  // Far away
    EXPECT_FALSE(obb1.intersects(obb3));
}

TEST_F(ObbTest, IntersectsAabb) {
    Obb obb(Vec3f::zero(), Vec3f(1, 1, 1));
    Aabb aabb(Vec3f(-0.5f, -0.5f, -0.5f), Vec3f(0.5f, 0.5f, 0.5f));

    EXPECT_TRUE(obb.intersects(aabb));

    Aabb aabb_far(Vec3f(10, 10, 10), Vec3f(11, 11, 11));
    EXPECT_FALSE(obb.intersects(aabb_far));
}

TEST_F(ObbTest, Comparison) {
    Obb obb1(Vec3f(1, 2, 3), Vec3f(1, 1, 1));
    Obb obb2(Vec3f(1, 2, 3), Vec3f(1, 1, 1));
    Obb obb3(Vec3f(1, 2, 4), Vec3f(1, 1, 1));

    EXPECT_TRUE(obb1 == obb2);
    EXPECT_FALSE(obb1 == obb3);
    EXPECT_TRUE(obb1.areSame(obb2));
}

}  // namespace vne::math

/* ---------------------------------------------------------------------
 * Copyright (c) 2024 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Author:    Ajeet Singh Yadav
 * Created:   January 2025
 *
 * Autodoc:   yes
 * ----------------------------------------------------------------------
 */

#include <gtest/gtest.h>

#include "vertexnova/math/geometry/aabb.h"
#include "vertexnova/math/math_utils.h"

namespace vne::math {

class AabbTest : public ::testing::Test {
   protected:
    void SetUp() override {
        unit_box_ = Aabb(Vec3f(-1.0f, -1.0f, -1.0f), Vec3f(1.0f, 1.0f, 1.0f));
        offset_box_ = Aabb(Vec3f(5.0f, 5.0f, 5.0f), Vec3f(10.0f, 10.0f, 10.0f));
    }

    Aabb unit_box_;
    Aabb offset_box_;
};

TEST_F(AabbTest, DefaultConstructor) {
    Aabb aabb;
    EXPECT_FALSE(aabb.isValid());
}

TEST_F(AabbTest, ParameterizedConstructor) {
    EXPECT_TRUE(unit_box_.min().areSame(Vec3f(-1.0f, -1.0f, -1.0f)));
    EXPECT_TRUE(unit_box_.max().areSame(Vec3f(1.0f, 1.0f, 1.0f)));
    EXPECT_TRUE(unit_box_.isValid());
}

TEST_F(AabbTest, FromCenterAndHalfExtents) {
    Aabb aabb = Aabb::fromCenterAndHalfExtents(Vec3f::zero(), Vec3f(1.0f, 1.0f, 1.0f));
    EXPECT_TRUE(aabb.min().areSame(Vec3f(-1.0f, -1.0f, -1.0f)));
    EXPECT_TRUE(aabb.max().areSame(Vec3f(1.0f, 1.0f, 1.0f)));
}

TEST_F(AabbTest, FromCenterAndSize) {
    Aabb aabb = Aabb::fromCenterAndSize(Vec3f::zero(), Vec3f(2.0f, 2.0f, 2.0f));
    EXPECT_TRUE(aabb.min().areSame(Vec3f(-1.0f, -1.0f, -1.0f)));
    EXPECT_TRUE(aabb.max().areSame(Vec3f(1.0f, 1.0f, 1.0f)));
}

TEST_F(AabbTest, Center) {
    EXPECT_TRUE(unit_box_.center().areSame(Vec3f::zero()));
    EXPECT_TRUE(offset_box_.center().areSame(Vec3f(7.5f, 7.5f, 7.5f)));
}

TEST_F(AabbTest, Size) {
    EXPECT_TRUE(unit_box_.size().areSame(Vec3f(2.0f, 2.0f, 2.0f)));
    EXPECT_TRUE(offset_box_.size().areSame(Vec3f(5.0f, 5.0f, 5.0f)));
}

TEST_F(AabbTest, HalfExtents) {
    EXPECT_TRUE(unit_box_.halfExtents().areSame(Vec3f(1.0f, 1.0f, 1.0f)));
}

TEST_F(AabbTest, Volume) {
    EXPECT_NEAR(unit_box_.volume(), 8.0f, kFloatEpsilon);      // 2 * 2 * 2
    EXPECT_NEAR(offset_box_.volume(), 125.0f, kFloatEpsilon);  // 5 * 5 * 5
}

TEST_F(AabbTest, SurfaceArea) {
    // 6 faces, each 2x2 = 4, total = 24
    EXPECT_NEAR(unit_box_.surfaceArea(), 24.0f, kFloatEpsilon);
}

TEST_F(AabbTest, Corner) {
    EXPECT_TRUE(unit_box_.corner(0).areSame(Vec3f(-1.0f, -1.0f, -1.0f)));
    EXPECT_TRUE(unit_box_.corner(1).areSame(Vec3f(1.0f, -1.0f, -1.0f)));
    EXPECT_TRUE(unit_box_.corner(2).areSame(Vec3f(-1.0f, 1.0f, -1.0f)));
    EXPECT_TRUE(unit_box_.corner(3).areSame(Vec3f(1.0f, 1.0f, -1.0f)));
    EXPECT_TRUE(unit_box_.corner(4).areSame(Vec3f(-1.0f, -1.0f, 1.0f)));
    EXPECT_TRUE(unit_box_.corner(5).areSame(Vec3f(1.0f, -1.0f, 1.0f)));
    EXPECT_TRUE(unit_box_.corner(6).areSame(Vec3f(-1.0f, 1.0f, 1.0f)));
    EXPECT_TRUE(unit_box_.corner(7).areSame(Vec3f(1.0f, 1.0f, 1.0f)));
}

TEST_F(AabbTest, ExpandWithPoint) {
    Aabb aabb;
    aabb.expand(Vec3f(0.0f, 0.0f, 0.0f));
    EXPECT_TRUE(aabb.isValid());
    EXPECT_TRUE(aabb.min().areSame(Vec3f::zero()));
    EXPECT_TRUE(aabb.max().areSame(Vec3f::zero()));

    aabb.expand(Vec3f(1.0f, 1.0f, 1.0f));
    EXPECT_TRUE(aabb.max().areSame(Vec3f(1.0f, 1.0f, 1.0f)));

    aabb.expand(Vec3f(-1.0f, -1.0f, -1.0f));
    EXPECT_TRUE(aabb.min().areSame(Vec3f(-1.0f, -1.0f, -1.0f)));
}

TEST_F(AabbTest, ExpandWithAabb) {
    Aabb aabb = unit_box_;
    aabb.expand(offset_box_);

    EXPECT_TRUE(aabb.min().areSame(Vec3f(-1.0f, -1.0f, -1.0f)));
    EXPECT_TRUE(aabb.max().areSame(Vec3f(10.0f, 10.0f, 10.0f)));
}

TEST_F(AabbTest, Grow) {
    Aabb aabb = unit_box_;
    aabb.grow(0.5f);

    EXPECT_TRUE(aabb.min().areSame(Vec3f(-1.5f, -1.5f, -1.5f)));
    EXPECT_TRUE(aabb.max().areSame(Vec3f(1.5f, 1.5f, 1.5f)));
}

TEST_F(AabbTest, GrowWithVector) {
    Aabb aabb = unit_box_;
    aabb.grow(Vec3f(0.5f, 1.0f, 1.5f));

    EXPECT_TRUE(aabb.min().areSame(Vec3f(-1.5f, -2.0f, -2.5f)));
    EXPECT_TRUE(aabb.max().areSame(Vec3f(1.5f, 2.0f, 2.5f)));
}

TEST_F(AabbTest, Translate) {
    Aabb aabb = unit_box_;
    aabb.translate(Vec3f(5.0f, 5.0f, 5.0f));

    EXPECT_TRUE(aabb.min().areSame(Vec3f(4.0f, 4.0f, 4.0f)));
    EXPECT_TRUE(aabb.max().areSame(Vec3f(6.0f, 6.0f, 6.0f)));
}

TEST_F(AabbTest, Reset) {
    Aabb aabb = unit_box_;
    aabb.reset();
    EXPECT_FALSE(aabb.isValid());
}

TEST_F(AabbTest, ContainsPoint) {
    EXPECT_TRUE(unit_box_.contains(Vec3f::zero()));
    EXPECT_TRUE(unit_box_.contains(Vec3f(0.5f, 0.5f, 0.5f)));
    EXPECT_TRUE(unit_box_.contains(Vec3f(1.0f, 1.0f, 1.0f)));  // on surface
    EXPECT_FALSE(unit_box_.contains(Vec3f(2.0f, 0.0f, 0.0f)));
}

TEST_F(AabbTest, ContainsAabb) {
    Aabb small_box(Vec3f(-0.5f, -0.5f, -0.5f), Vec3f(0.5f, 0.5f, 0.5f));
    EXPECT_TRUE(unit_box_.contains(small_box));
    EXPECT_FALSE(unit_box_.contains(offset_box_));
}

TEST_F(AabbTest, Intersects) {
    Aabb overlapping(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(2.0f, 2.0f, 2.0f));
    EXPECT_TRUE(unit_box_.intersects(overlapping));

    Aabb non_overlapping(Vec3f(5.0f, 5.0f, 5.0f), Vec3f(6.0f, 6.0f, 6.0f));
    EXPECT_FALSE(unit_box_.intersects(non_overlapping));
}

TEST_F(AabbTest, ClosestPoint) {
    // Point inside - should return the point itself
    Vec3f inside(0.0f, 0.0f, 0.0f);
    EXPECT_TRUE(unit_box_.closestPoint(inside).areSame(inside));

    // Point outside - should return closest point on surface
    Vec3f outside(5.0f, 0.0f, 0.0f);
    EXPECT_TRUE(unit_box_.closestPoint(outside).areSame(Vec3f(1.0f, 0.0f, 0.0f)));
}

TEST_F(AabbTest, SquaredDistanceToPoint) {
    // Point inside - distance should be 0
    EXPECT_NEAR(unit_box_.squaredDistanceToPoint(Vec3f::zero()), 0.0f, kFloatEpsilon);

    // Point outside - 2 units away on x-axis
    EXPECT_NEAR(unit_box_.squaredDistanceToPoint(Vec3f(3.0f, 0.0f, 0.0f)), 4.0f, kFloatEpsilon);
}

TEST_F(AabbTest, EqualityOperators) {
    Aabb aabb1(Vec3f(-1.0f, -1.0f, -1.0f), Vec3f(1.0f, 1.0f, 1.0f));
    Aabb aabb2(Vec3f(-1.0f, -1.0f, -1.0f), Vec3f(1.0f, 1.0f, 1.0f));

    EXPECT_TRUE(aabb1 == aabb2);
    EXPECT_FALSE(aabb1 != aabb2);
    EXPECT_FALSE(aabb1 == offset_box_);
}

TEST_F(AabbTest, StreamOperator) {
    std::ostringstream oss;
    oss << unit_box_;
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("Aabb"), std::string::npos);
}

}  // namespace vne::math

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

#include "vertexnova/math/geometry/sphere.h"
#include "vertexnova/math/core/math_utils.h"

namespace vne::math {

class SphereTest : public ::testing::Test {
   protected:
    void SetUp() override {
        unit_sphere_ = Sphere(Vec3f::zero(), 1.0f);
        offset_sphere_ = Sphere(Vec3f(5.0f, 5.0f, 5.0f), 2.0f);
    }

    Sphere unit_sphere_;
    Sphere offset_sphere_;
};

TEST_F(SphereTest, DefaultConstructor) {
    Sphere sphere;
    EXPECT_TRUE(sphere.center().areSame(Vec3f::zero()));
    EXPECT_LT(sphere.radius(), 0.0f);
    EXPECT_FALSE(sphere.isValid());
}

TEST_F(SphereTest, ParameterizedConstructor) {
    EXPECT_TRUE(unit_sphere_.center().areSame(Vec3f::zero()));
    EXPECT_NEAR(unit_sphere_.radius(), 1.0f, kFloatEpsilon);
    EXPECT_TRUE(unit_sphere_.isValid());
}

TEST_F(SphereTest, SetCenter) {
    Sphere sphere = unit_sphere_;
    sphere.setCenter(Vec3f(1.0f, 2.0f, 3.0f));
    EXPECT_TRUE(sphere.center().areSame(Vec3f(1.0f, 2.0f, 3.0f)));
}

TEST_F(SphereTest, SetRadius) {
    Sphere sphere = unit_sphere_;
    sphere.setRadius(5.0f);
    EXPECT_NEAR(sphere.radius(), 5.0f, kFloatEpsilon);
}

TEST_F(SphereTest, Diameter) {
    EXPECT_NEAR(unit_sphere_.diameter(), 2.0f, kFloatEpsilon);
    EXPECT_NEAR(offset_sphere_.diameter(), 4.0f, kFloatEpsilon);
}

TEST_F(SphereTest, Volume) {
    // V = 4/3 * pi * r^3
    float expected = (4.0f / 3.0f) * kPi * 1.0f;
    EXPECT_NEAR(unit_sphere_.volume(), expected, 1e-5f);
}

TEST_F(SphereTest, SurfaceArea) {
    // A = 4 * pi * r^2
    float expected = 4.0f * kPi * 1.0f;
    EXPECT_NEAR(unit_sphere_.surfaceArea(), expected, 1e-5f);
}

TEST_F(SphereTest, ExpandWithPoint) {
    Sphere sphere;
    sphere.expand(Vec3f::zero());
    EXPECT_TRUE(sphere.isValid());
    EXPECT_TRUE(sphere.center().areSame(Vec3f::zero()));
    EXPECT_NEAR(sphere.radius(), 0.0f, kFloatEpsilon);

    sphere.expand(Vec3f(2.0f, 0.0f, 0.0f));
    EXPECT_TRUE(sphere.contains(Vec3f::zero()));
    EXPECT_TRUE(sphere.contains(Vec3f(2.0f, 0.0f, 0.0f)));
}

TEST_F(SphereTest, ExpandWithSphere) {
    Sphere sphere = unit_sphere_;
    sphere.expand(offset_sphere_);

    // Should contain both original spheres
    EXPECT_TRUE(sphere.contains(Vec3f::zero()));
    EXPECT_TRUE(sphere.contains(Vec3f(7.0f, 5.0f, 5.0f)));  // Edge of offset sphere
}

TEST_F(SphereTest, Grow) {
    Sphere sphere = unit_sphere_;
    sphere.grow(0.5f);
    EXPECT_NEAR(sphere.radius(), 1.5f, kFloatEpsilon);
}

TEST_F(SphereTest, Translate) {
    Sphere sphere = unit_sphere_;
    sphere.translate(Vec3f(5.0f, 0.0f, 0.0f));
    EXPECT_TRUE(sphere.center().areSame(Vec3f(5.0f, 0.0f, 0.0f)));
}

TEST_F(SphereTest, ContainsPoint) {
    EXPECT_TRUE(unit_sphere_.contains(Vec3f::zero()));
    EXPECT_TRUE(unit_sphere_.contains(Vec3f(0.5f, 0.0f, 0.0f)));
    EXPECT_TRUE(unit_sphere_.contains(Vec3f(1.0f, 0.0f, 0.0f)));  // on surface
    EXPECT_FALSE(unit_sphere_.contains(Vec3f(2.0f, 0.0f, 0.0f)));
}

TEST_F(SphereTest, ContainsSphere) {
    Sphere small_sphere(Vec3f::zero(), 0.5f);
    EXPECT_TRUE(unit_sphere_.contains(small_sphere));

    Sphere large_sphere(Vec3f::zero(), 2.0f);
    EXPECT_FALSE(unit_sphere_.contains(large_sphere));
}

TEST_F(SphereTest, Intersects) {
    Sphere overlapping(Vec3f(1.5f, 0.0f, 0.0f), 1.0f);
    EXPECT_TRUE(unit_sphere_.intersects(overlapping));

    Sphere non_overlapping(Vec3f(5.0f, 0.0f, 0.0f), 1.0f);
    EXPECT_FALSE(unit_sphere_.intersects(non_overlapping));

    Sphere touching(Vec3f(2.0f, 0.0f, 0.0f), 1.0f);
    EXPECT_TRUE(unit_sphere_.intersects(touching));  // touching at edge
}

TEST_F(SphereTest, ClosestPoint) {
    // Point inside - should return point on surface towards the point
    Vec3f inside(0.5f, 0.0f, 0.0f);
    Vec3f closest_inside = unit_sphere_.closestPoint(inside);
    EXPECT_TRUE(closest_inside.areSame(Vec3f(1.0f, 0.0f, 0.0f)));

    // Point outside - should return point on surface towards the point
    Vec3f outside(5.0f, 0.0f, 0.0f);
    Vec3f closest_outside = unit_sphere_.closestPoint(outside);
    EXPECT_TRUE(closest_outside.areSame(Vec3f(1.0f, 0.0f, 0.0f)));
}

TEST_F(SphereTest, ClosestPointAtCenter) {
    // Point at center - should return some point on surface
    Vec3f at_center = unit_sphere_.closestPoint(Vec3f::zero());
    EXPECT_NEAR(at_center.length(), 1.0f, kFloatEpsilon);  // Should be on surface
}

TEST_F(SphereTest, SignedDistanceToPoint) {
    // Point inside - negative distance
    EXPECT_LT(unit_sphere_.signedDistanceToPoint(Vec3f::zero()), 0.0f);

    // Point on surface - zero distance
    EXPECT_NEAR(unit_sphere_.signedDistanceToPoint(Vec3f(1.0f, 0.0f, 0.0f)), 0.0f, kFloatEpsilon);

    // Point outside - positive distance
    EXPECT_GT(unit_sphere_.signedDistanceToPoint(Vec3f(5.0f, 0.0f, 0.0f)), 0.0f);
}

TEST_F(SphereTest, DistanceToPoint) {
    // Point inside - distance should be 0
    EXPECT_NEAR(unit_sphere_.distanceToPoint(Vec3f::zero()), 0.0f, kFloatEpsilon);

    // Point outside - distance should be positive
    EXPECT_NEAR(unit_sphere_.distanceToPoint(Vec3f(3.0f, 0.0f, 0.0f)), 2.0f, kFloatEpsilon);
}

TEST_F(SphereTest, EqualityOperators) {
    Sphere sphere1(Vec3f::zero(), 1.0f);
    Sphere sphere2(Vec3f::zero(), 1.0f);

    EXPECT_TRUE(sphere1 == sphere2);
    EXPECT_FALSE(sphere1 != sphere2);
    EXPECT_FALSE(sphere1 == offset_sphere_);
}

TEST_F(SphereTest, StreamOperator) {
    std::ostringstream oss;
    oss << unit_sphere_;
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("Sphere"), std::string::npos);
}

}  // namespace vne::math

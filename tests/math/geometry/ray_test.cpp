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

#include "vertexnova/math/geometry/ray.h"
#include "vertexnova/math/core/math_utils.h"

namespace vne::math {

class RayTest : public ::testing::Test {
   protected:
    void SetUp() override {
        origin_ = Vec3f(1.0f, 2.0f, 3.0f);
        direction_ = Vec3f(1.0f, 0.0f, 0.0f);
    }

    Vec3f origin_;
    Vec3f direction_;
};

TEST_F(RayTest, DefaultConstructor) {
    Ray ray;
    EXPECT_TRUE(ray.origin().areSame(Vec3f::zero()));
    EXPECT_TRUE(ray.direction().areSame(Vec3f::zAxis()));
}

TEST_F(RayTest, ParameterizedConstructor) {
    Ray ray(origin_, direction_);
    EXPECT_TRUE(ray.origin().areSame(origin_));
    EXPECT_TRUE(ray.direction().areSame(direction_));
}

TEST_F(RayTest, ConstructorNormalizesDirection) {
    Vec3f unnormalized(2.0f, 0.0f, 0.0f);
    Ray ray(origin_, unnormalized);
    EXPECT_TRUE(ray.direction().isNormalized());
    EXPECT_TRUE(ray.direction().areSame(Vec3f::xAxis()));
}

TEST_F(RayTest, GetPoint) {
    Ray ray(origin_, direction_);

    Vec3f point0 = ray.getPoint(0.0f);
    EXPECT_TRUE(point0.areSame(origin_));

    Vec3f point5 = ray.getPoint(5.0f);
    EXPECT_TRUE(point5.areSame(Vec3f(6.0f, 2.0f, 3.0f)));

    Vec3f point_neg = ray.getPoint(-2.0f);
    EXPECT_TRUE(point_neg.areSame(Vec3f(-1.0f, 2.0f, 3.0f)));
}

TEST_F(RayTest, ClosestPointOnRay) {
    Ray ray(Vec3f::zero(), Vec3f::xAxis());

    // Point on the ray
    Vec3f on_ray(5.0f, 0.0f, 0.0f);
    EXPECT_TRUE(ray.closestPoint(on_ray).areSame(on_ray));

    // Point above the ray
    Vec3f above_ray(5.0f, 3.0f, 0.0f);
    EXPECT_TRUE(ray.closestPoint(above_ray).areSame(Vec3f(5.0f, 0.0f, 0.0f)));

    // Point behind origin - closest should be origin (ray is one-directional)
    Vec3f behind(-5.0f, 0.0f, 0.0f);
    EXPECT_TRUE(ray.closestPoint(behind).areSame(Vec3f::zero()));
}

TEST_F(RayTest, ClosestPointWithDistance) {
    Ray ray(Vec3f::zero(), Vec3f::xAxis());
    float distance = 0.0f;

    Vec3f point(5.0f, 3.0f, 0.0f);
    Vec3f closest = ray.closestPoint(point, distance);

    EXPECT_NEAR(distance, 5.0f, kFloatEpsilon);
    EXPECT_TRUE(closest.areSame(Vec3f(5.0f, 0.0f, 0.0f)));
}

TEST_F(RayTest, DistanceToPoint) {
    Ray ray(Vec3f::zero(), Vec3f::xAxis());

    // Point on ray - distance should be 0
    EXPECT_NEAR(ray.distanceToPoint(Vec3f(5.0f, 0.0f, 0.0f)), 0.0f, kFloatEpsilon);

    // Point 3 units above the ray at x=5
    EXPECT_NEAR(ray.distanceToPoint(Vec3f(5.0f, 3.0f, 0.0f)), 3.0f, kFloatEpsilon);

    // Point behind origin
    EXPECT_NEAR(ray.distanceToPoint(Vec3f(-5.0f, 3.0f, 0.0f)), sqrt(25.0f + 9.0f), kFloatEpsilon);
}

TEST_F(RayTest, AreSame) {
    Ray ray1(origin_, direction_);
    Ray ray2(origin_, direction_);
    Ray ray3(origin_ + Vec3f(0.1f, 0.0f, 0.0f), direction_);

    EXPECT_TRUE(ray1.areSame(ray2));
    EXPECT_FALSE(ray1.areSame(ray3));
}

TEST_F(RayTest, SetOrigin) {
    Ray ray;
    ray.setOrigin(origin_);
    EXPECT_TRUE(ray.origin().areSame(origin_));
}

TEST_F(RayTest, SetDirection) {
    Ray ray;
    ray.setDirection(Vec3f(0.0f, 2.0f, 0.0f));
    EXPECT_TRUE(ray.direction().isNormalized());
    EXPECT_TRUE(ray.direction().areSame(Vec3f::yAxis()));
}

TEST_F(RayTest, StreamOperator) {
    Ray ray(origin_, direction_);
    std::ostringstream oss;
    oss << ray;
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("Ray"), std::string::npos);
}

}  // namespace vne::math

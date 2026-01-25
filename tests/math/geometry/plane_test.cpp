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

#include "vertexnova/math/geometry/plane.h"
#include "vertexnova/math/math_utils.h"

namespace vne::math {

class PlaneTest : public ::testing::Test {
   protected:
    void SetUp() override {
        xy_plane_ = Plane(Vec3f::zAxis(), 0.0f);          // z = 0 plane
        offset_xy_plane_ = Plane(Vec3f::zAxis(), -5.0f);  // z = 5 plane
    }

    Plane xy_plane_;
    Plane offset_xy_plane_;
};

TEST_F(PlaneTest, DefaultConstructor) {
    Plane plane;
    EXPECT_TRUE(plane.normal.areSame(Vec3f::zAxis()));
    EXPECT_NEAR(plane.d, 0.0f, kFloatEpsilon);
}

TEST_F(PlaneTest, ConstructorFromNormalAndDistance) {
    Plane plane(Vec3f::yAxis(), 3.0f);
    EXPECT_TRUE(plane.normal.areSame(Vec3f::yAxis()));
    EXPECT_NEAR(plane.d, 3.0f, kFloatEpsilon);
}

TEST_F(PlaneTest, ConstructorFromComponents) {
    Plane plane(0.0f, 1.0f, 0.0f, 2.0f);
    EXPECT_TRUE(plane.normal.areSame(Vec3f::yAxis()));
    EXPECT_NEAR(plane.d, 2.0f, kFloatEpsilon);
}

TEST_F(PlaneTest, ConstructorFromVec4f) {
    Plane plane(Vec4f(0.0f, 0.0f, 1.0f, -5.0f));
    EXPECT_TRUE(plane.normal.areSame(Vec3f::zAxis()));
    EXPECT_NEAR(plane.d, -5.0f, kFloatEpsilon);
}

TEST_F(PlaneTest, ConstructorFromPoints) {
    Vec3f p0(0.0f, 0.0f, 0.0f);
    Vec3f p1(1.0f, 0.0f, 0.0f);
    Vec3f p2(0.0f, 1.0f, 0.0f);

    Plane plane(p0, p1, p2);
    // Counter-clockwise winding should give +Z normal
    EXPECT_TRUE(plane.normal.areSame(Vec3f::zAxis(), 1e-5f));
    EXPECT_NEAR(plane.d, 0.0f, 1e-5f);
}

TEST_F(PlaneTest, ConstructorFromPointAndNormal) {
    Vec3f point(0.0f, 0.0f, 5.0f);
    Vec3f normal(0.0f, 0.0f, 1.0f);

    Plane plane(point, normal);
    EXPECT_TRUE(plane.normal.areSame(Vec3f::zAxis()));
    EXPECT_NEAR(plane.d, -5.0f, kFloatEpsilon);
}

TEST_F(PlaneTest, FromPoints) {
    Vec3f p0(0.0f, 0.0f, 0.0f);
    Vec3f p1(1.0f, 0.0f, 0.0f);
    Vec3f p2(0.0f, 1.0f, 0.0f);

    Plane plane = Plane::fromPoints(p0, p1, p2);
    EXPECT_TRUE(plane.isNormalized());
}

TEST_F(PlaneTest, FromPointNormal) {
    Plane plane = Plane::fromPointNormal(Vec3f(0.0f, 5.0f, 0.0f), Vec3f::yAxis());
    EXPECT_TRUE(plane.normal.areSame(Vec3f::yAxis()));
    EXPECT_NEAR(plane.d, -5.0f, kFloatEpsilon);
}

TEST_F(PlaneTest, SignedDistance) {
    // Point above XY plane
    EXPECT_GT(xy_plane_.signedDistance(Vec3f(0.0f, 0.0f, 5.0f)), 0.0f);

    // Point below XY plane
    EXPECT_LT(xy_plane_.signedDistance(Vec3f(0.0f, 0.0f, -5.0f)), 0.0f);

    // Point on XY plane
    EXPECT_NEAR(xy_plane_.signedDistance(Vec3f(0.0f, 0.0f, 0.0f)), 0.0f, kFloatEpsilon);
}

TEST_F(PlaneTest, Distance) {
    EXPECT_NEAR(xy_plane_.distance(Vec3f(0.0f, 0.0f, 5.0f)), 5.0f, kFloatEpsilon);
    EXPECT_NEAR(xy_plane_.distance(Vec3f(0.0f, 0.0f, -5.0f)), 5.0f, kFloatEpsilon);
}

TEST_F(PlaneTest, ClosestPoint) {
    Vec3f point(3.0f, 4.0f, 7.0f);
    Vec3f closest = xy_plane_.closestPoint(point);

    EXPECT_NEAR(closest.x, 3.0f, kFloatEpsilon);
    EXPECT_NEAR(closest.y, 4.0f, kFloatEpsilon);
    EXPECT_NEAR(closest.z, 0.0f, kFloatEpsilon);
}

TEST_F(PlaneTest, PointOnPlane) {
    Plane plane = Plane::fromPointNormal(Vec3f(0.0f, 0.0f, 5.0f), Vec3f::zAxis());
    Vec3f point = plane.pointOnPlane();
    EXPECT_NEAR(plane.signedDistance(point), 0.0f, kFloatEpsilon);
}

TEST_F(PlaneTest, IsNormalized) {
    Plane normalized_plane(Vec3f::zAxis(), 0.0f);
    EXPECT_TRUE(normalized_plane.isNormalized());

    Plane unnormalized_plane(Vec3f(0.0f, 0.0f, 2.0f), 0.0f);
    EXPECT_FALSE(unnormalized_plane.isNormalized());
}

TEST_F(PlaneTest, IsOnPositiveSide) {
    EXPECT_TRUE(xy_plane_.isOnPositiveSide(Vec3f(0.0f, 0.0f, 1.0f)));
    EXPECT_FALSE(xy_plane_.isOnPositiveSide(Vec3f(0.0f, 0.0f, -1.0f)));
}

TEST_F(PlaneTest, IsOnNegativeSide) {
    EXPECT_TRUE(xy_plane_.isOnNegativeSide(Vec3f(0.0f, 0.0f, -1.0f)));
    EXPECT_FALSE(xy_plane_.isOnNegativeSide(Vec3f(0.0f, 0.0f, 1.0f)));
}

TEST_F(PlaneTest, IsOnPlane) {
    EXPECT_TRUE(xy_plane_.isOnPlane(Vec3f(5.0f, 3.0f, 0.0f)));
    EXPECT_FALSE(xy_plane_.isOnPlane(Vec3f(0.0f, 0.0f, 1.0f)));
}

TEST_F(PlaneTest, AreOnSameSide) {
    Vec3f above1(0.0f, 0.0f, 1.0f);
    Vec3f above2(0.0f, 0.0f, 2.0f);
    Vec3f below(0.0f, 0.0f, -1.0f);

    EXPECT_TRUE(xy_plane_.areOnSameSide(above1, above2));
    EXPECT_FALSE(xy_plane_.areOnSameSide(above1, below));
}

TEST_F(PlaneTest, Contains) {
    EXPECT_TRUE(xy_plane_.contains(Vec3f(5.0f, 3.0f, 0.0f)));
    EXPECT_FALSE(xy_plane_.contains(Vec3f(0.0f, 0.0f, 1.0f)));
}

TEST_F(PlaneTest, Flip) {
    Plane plane(Vec3f::zAxis(), 5.0f);
    plane.flip();

    EXPECT_TRUE(plane.normal.areSame(-Vec3f::zAxis()));
    EXPECT_NEAR(plane.d, -5.0f, kFloatEpsilon);
}

TEST_F(PlaneTest, Normalize) {
    Plane plane(Vec3f(0.0f, 0.0f, 2.0f), 4.0f);
    plane.normalize();

    EXPECT_TRUE(plane.isNormalized());
    EXPECT_NEAR(plane.d, 2.0f, kFloatEpsilon);
}

TEST_F(PlaneTest, Translate) {
    Plane plane(Vec3f::zAxis(), 0.0f);
    plane.translate(Vec3f(0.0f, 0.0f, 5.0f));

    EXPECT_NEAR(plane.d, -5.0f, kFloatEpsilon);
}

TEST_F(PlaneTest, EqualityOperators) {
    Plane plane1(Vec3f::zAxis(), 5.0f);
    Plane plane2(Vec3f::zAxis(), 5.0f);
    Plane plane3(Vec3f::yAxis(), 5.0f);

    EXPECT_TRUE(plane1 == plane2);
    EXPECT_FALSE(plane1 == plane3);
    EXPECT_TRUE(plane1 != plane3);
}

TEST_F(PlaneTest, StreamOperator) {
    std::ostringstream oss;
    oss << xy_plane_;
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("Plane"), std::string::npos);
}

}  // namespace vne::math

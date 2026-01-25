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
#include "vertexnova/math/geometry/frustum.h"
#include "vertexnova/math/geometry/sphere.h"
#include "vertexnova/math/core/mat.h"
#include "vertexnova/math/core/math_utils.h"

namespace vne::math {

class FrustumTest : public ::testing::Test {
   protected:
    void SetUp() override {
        // Create a simple perspective projection matrix
        projection_ = Mat4x4f::perspective(degToRad(45.0f), 1.0f, 0.1f, 100.0f);

        // Create a simple look-at view matrix
        view_ = Mat4x4f::lookAt(Vec3f(0.0f, 0.0f, 10.0f), Vec3f::zero(), Vec3f::up());

        // Combined view-projection
        view_projection_ = projection_ * view_;

        // Extract frustum from view-projection matrix
        frustum_.extractFromMatrix(view_projection_);
    }

    Mat4x4f projection_;
    Mat4x4f view_;
    Mat4x4f view_projection_;
    Frustum frustum_;
};

TEST_F(FrustumTest, DefaultConstructor) {
    Frustum frustum;
    // Default frustum should have valid planes
    EXPECT_TRUE(frustum.nearPlane().isNormalized(1e-3f));
}

TEST_F(FrustumTest, ExtractFromMatrix) {
    // After extraction, all planes should be normalized
    EXPECT_TRUE(frustum_.nearPlane().isNormalized(1e-3f));
    EXPECT_TRUE(frustum_.farPlane().isNormalized(1e-3f));
    EXPECT_TRUE(frustum_.leftPlane().isNormalized(1e-3f));
    EXPECT_TRUE(frustum_.rightPlane().isNormalized(1e-3f));
    EXPECT_TRUE(frustum_.topPlane().isNormalized(1e-3f));
    EXPECT_TRUE(frustum_.bottomPlane().isNormalized(1e-3f));
}

TEST_F(FrustumTest, ContainsPointInside) {
    // Origin should be inside the frustum (camera at z=10 looking at origin)
    EXPECT_TRUE(frustum_.contains(Vec3f::zero()));

    // A point in front of the camera
    EXPECT_TRUE(frustum_.contains(Vec3f(0.0f, 0.0f, 1.0f)));
}

TEST_F(FrustumTest, ContainsPointOutside) {
    // A point far behind the camera should be outside
    EXPECT_FALSE(frustum_.contains(Vec3f(0.0f, 0.0f, 200.0f)));

    // A point far to the side should be outside
    EXPECT_FALSE(frustum_.contains(Vec3f(100.0f, 0.0f, 0.0f)));
}

TEST_F(FrustumTest, IntersectsSphereInside) {
    Sphere inside(Vec3f::zero(), 1.0f);
    EXPECT_TRUE(frustum_.intersects(inside));
}

TEST_F(FrustumTest, IntersectsSphereOutside) {
    Sphere outside(Vec3f(0.0f, 0.0f, 200.0f), 1.0f);
    EXPECT_FALSE(frustum_.intersects(outside));
}

TEST_F(FrustumTest, IntersectsSpherePartial) {
    // A large sphere that intersects the frustum boundary
    Sphere partial(Vec3f(0.0f, 0.0f, -50.0f), 60.0f);
    EXPECT_TRUE(frustum_.intersects(partial));
}

TEST_F(FrustumTest, IntersectsAabbInside) {
    Aabb inside(Vec3f(-1.0f, -1.0f, -1.0f), Vec3f(1.0f, 1.0f, 1.0f));
    EXPECT_TRUE(frustum_.intersects(inside));
}

TEST_F(FrustumTest, IntersectsAabbOutside) {
    Aabb outside(Vec3f(100.0f, 100.0f, 100.0f), Vec3f(101.0f, 101.0f, 101.0f));
    EXPECT_FALSE(frustum_.intersects(outside));
}

TEST_F(FrustumTest, ContainsFullySphereInside) {
    Sphere small_inside(Vec3f::zero(), 0.1f);
    EXPECT_TRUE(frustum_.containsFully(small_inside));
}

TEST_F(FrustumTest, ContainsFullySpherePartial) {
    // Large sphere that extends beyond frustum
    Sphere large(Vec3f::zero(), 50.0f);
    EXPECT_FALSE(frustum_.containsFully(large));
}

TEST_F(FrustumTest, ContainsFullyAabbInside) {
    Aabb small_inside(Vec3f(-0.1f, -0.1f, -0.1f), Vec3f(0.1f, 0.1f, 0.1f));
    EXPECT_TRUE(frustum_.containsFully(small_inside));
}

TEST_F(FrustumTest, ContainsFullyAabbPartial) {
    // Large AABB that extends beyond frustum
    Aabb large(Vec3f(-50.0f, -50.0f, -50.0f), Vec3f(50.0f, 50.0f, 50.0f));
    EXPECT_FALSE(frustum_.containsFully(large));
}

TEST_F(FrustumTest, EqualityOperators) {
    Frustum frustum1;
    Frustum frustum2;

    EXPECT_TRUE(frustum1 == frustum2);
    EXPECT_FALSE(frustum1 != frustum2);

    frustum1.extractFromMatrix(projection_);
    EXPECT_FALSE(frustum1 == frustum2);
}

TEST_F(FrustumTest, StreamOperator) {
    std::ostringstream oss;
    oss << frustum_;
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("Frustum"), std::string::npos);
}

TEST_F(FrustumTest, PlaneAccessors) {
    // Just verify accessors don't crash and return valid planes
    const Plane& near = frustum_.nearPlane();
    const Plane& far = frustum_.farPlane();
    const Plane& left = frustum_.leftPlane();
    const Plane& right = frustum_.rightPlane();
    const Plane& top = frustum_.topPlane();
    const Plane& bottom = frustum_.bottomPlane();

    EXPECT_TRUE(near.isNormalized(1e-3f));
    EXPECT_TRUE(far.isNormalized(1e-3f));
    EXPECT_TRUE(left.isNormalized(1e-3f));
    EXPECT_TRUE(right.isNormalized(1e-3f));
    EXPECT_TRUE(top.isNormalized(1e-3f));
    EXPECT_TRUE(bottom.isNormalized(1e-3f));
}

}  // namespace vne::math

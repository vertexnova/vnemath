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

// ============================================================================
// Non-uniform Scale Tests
// ============================================================================

TEST_F(ObbTest, ScaleNonUniform) {
    Obb obb(Vec3f::zero(), Vec3f(1, 1, 1));
    obb.scale(Vec3f(2, 3, 4));

    EXPECT_FLOAT_EQ(obb.halfExtents().x(), 2.0f);
    EXPECT_FLOAT_EQ(obb.halfExtents().y(), 3.0f);
    EXPECT_FLOAT_EQ(obb.halfExtents().z(), 4.0f);
}

TEST_F(ObbTest, ScaleNonUniformPreservesCenter) {
    Vec3f center(5, 10, 15);
    Obb obb(center, Vec3f(1, 1, 1));
    obb.scale(Vec3f(2, 3, 4));

    EXPECT_EQ(obb.center(), center);  // Center should not change
}

TEST_F(ObbTest, ScaleNonUniformPreservesOrientation) {
    Quatf rotation = Quatf::fromAxisAngle(Vec3f::yAxis(), degToRad(45.0f));
    Obb obb(Vec3f::zero(), Vec3f(1, 1, 1), rotation);
    obb.scale(Vec3f(2, 3, 4));

    EXPECT_TRUE(obb.orientation().approxEquals(rotation));
}

// ============================================================================
// Transform Tests
// ============================================================================

TEST_F(ObbTest, TransformIdentity) {
    Obb obb(Vec3f(1, 2, 3), Vec3f(1, 1, 1));
    Obb original = obb;

    obb.transform(Mat4f::identity());

    EXPECT_TRUE(obb.center().areSame(original.center()));
    EXPECT_TRUE(obb.halfExtents().areSame(original.halfExtents()));
}

TEST_F(ObbTest, TransformTranslation) {
    Obb obb(Vec3f::zero(), Vec3f(1, 1, 1));
    Mat4f translation = Mat4f::translate(Vec3f(10, 20, 30));

    obb.transform(translation);

    EXPECT_TRUE(obb.center().areSame(Vec3f(10, 20, 30)));
    EXPECT_TRUE(obb.halfExtents().areSame(Vec3f(1, 1, 1)));  // Size unchanged
}

TEST_F(ObbTest, TransformUniformScale) {
    Obb obb(Vec3f::zero(), Vec3f(1, 1, 1));
    Mat4f scale = Mat4f::scale(Vec3f(2, 2, 2));

    obb.transform(scale);

    EXPECT_FLOAT_EQ(obb.halfExtents().x(), 2.0f);
    EXPECT_FLOAT_EQ(obb.halfExtents().y(), 2.0f);
    EXPECT_FLOAT_EQ(obb.halfExtents().z(), 2.0f);
}

TEST_F(ObbTest, TransformNonUniformScale) {
    Obb obb(Vec3f::zero(), Vec3f(1, 1, 1));
    Mat4f scale = Mat4f::scale(Vec3f(2, 3, 4));

    obb.transform(scale);

    EXPECT_NEAR(obb.halfExtents().x(), 2.0f, kFloatEpsilon);
    EXPECT_NEAR(obb.halfExtents().y(), 3.0f, kFloatEpsilon);
    EXPECT_NEAR(obb.halfExtents().z(), 4.0f, kFloatEpsilon);
}

TEST_F(ObbTest, TransformRotation) {
    Obb obb(Vec3f::zero(), Vec3f(1, 1, 1), Quatf::identity());
    Mat4f rotation = Mat4f::rotate(degToRad(90.0f), Vec3f::zAxis());

    obb.transform(rotation);

    // After 90 degree rotation around Z, X axis becomes Y and Y becomes -X
    Vec3f new_x = obb.axisX();
    EXPECT_NEAR(new_x.x(), 0.0f, kFloatEpsilon);
    EXPECT_NEAR(new_x.y(), 1.0f, kFloatEpsilon);
    EXPECT_NEAR(new_x.z(), 0.0f, kFloatEpsilon);
}

TEST_F(ObbTest, TransformCombined) {
    Obb obb(Vec3f::zero(), Vec3f(1, 1, 1));

    // Apply translation + scale
    Mat4f transform = Mat4f::translate(Vec3f(5, 0, 0)) * Mat4f::scale(Vec3f(2, 2, 2));

    obb.transform(transform);

    EXPECT_NEAR(obb.center().x(), 5.0f, kFloatEpsilon);
    EXPECT_NEAR(obb.halfExtents().x(), 2.0f, kFloatEpsilon);
}

// ============================================================================
// Rotate Tests
// ============================================================================

TEST_F(ObbTest, RotateIdentity) {
    Obb obb(Vec3f(1, 0, 0), Vec3f(1, 1, 1));
    Obb original = obb;

    obb.rotate(Quatf::identity());

    EXPECT_TRUE(obb.center().areSame(original.center()));
    EXPECT_TRUE(obb.orientation().approxEquals(original.orientation()));
}

TEST_F(ObbTest, RotateCenter) {
    Obb obb(Vec3f(1, 0, 0), Vec3f(1, 1, 1));
    Quatf rot = Quatf::fromAxisAngle(Vec3f::zAxis(), degToRad(90.0f));

    obb.rotate(rot);

    // Center at (1,0,0) rotated 90 degrees around Z should be at (0,1,0)
    EXPECT_NEAR(obb.center().x(), 0.0f, kFloatEpsilon);
    EXPECT_NEAR(obb.center().y(), 1.0f, kFloatEpsilon);
    EXPECT_NEAR(obb.center().z(), 0.0f, kFloatEpsilon);
}

TEST_F(ObbTest, RotateOrientation) {
    Obb obb(Vec3f::zero(), Vec3f(1, 1, 1), Quatf::identity());
    Quatf rot = Quatf::fromAxisAngle(Vec3f::yAxis(), degToRad(45.0f));

    obb.rotate(rot);

    EXPECT_TRUE(obb.orientation().approxEquals(rot));
}

TEST_F(ObbTest, RotatePreservesSize) {
    Obb obb(Vec3f::zero(), Vec3f(1, 2, 3));
    Quatf rot = Quatf::fromAxisAngle(Vec3f::yAxis(), degToRad(45.0f));

    obb.rotate(rot);

    EXPECT_TRUE(obb.halfExtents().areSame(Vec3f(1, 2, 3)));
}

TEST_F(ObbTest, RotateMultiple) {
    Obb obb(Vec3f::zero(), Vec3f(1, 1, 1), Quatf::identity());

    // Rotate 90 degrees 4 times should return to original (or equivalent rotation)
    Quatf rot = Quatf::fromAxisAngle(Vec3f::yAxis(), degToRad(90.0f));

    obb.rotate(rot);
    obb.rotate(rot);
    obb.rotate(rot);
    obb.rotate(rot);

    // After 360 degrees, quaternion can be identity or -identity (both represent same rotation)
    // Also account for floating-point accumulation errors
    bool is_identity = obb.orientation().approxEquals(Quatf::identity(), 0.05f);
    bool is_neg_identity = obb.orientation().approxEquals(-Quatf::identity(), 0.05f);
    EXPECT_TRUE(is_identity || is_neg_identity);
}

// ============================================================================
// Corner Tests
// ============================================================================

TEST_F(ObbTest, CornerIndices) {
    Obb obb(Vec3f::zero(), Vec3f(1, 1, 1));

    // Verify all 8 corners are unique
    std::vector<Vec3f> corners;
    for (uint32_t i = 0; i < 8; ++i) {
        corners.push_back(obb.corner(i));
    }

    // All corners should be at distance sqrt(3) from center (unit cube)
    for (const auto& c : corners) {
        EXPECT_NEAR(c.length(), std::sqrt(3.0f), kFloatEpsilon);
    }
}

TEST_F(ObbTest, CornerBitPattern) {
    Obb obb(Vec3f::zero(), Vec3f(1, 2, 3));

    // Index 0: (-x, -y, -z)
    Vec3f c0 = obb.corner(0);
    EXPECT_NEAR(c0.x(), -1.0f, kFloatEpsilon);
    EXPECT_NEAR(c0.y(), -2.0f, kFloatEpsilon);
    EXPECT_NEAR(c0.z(), -3.0f, kFloatEpsilon);

    // Index 7: (+x, +y, +z) - all bits set
    Vec3f c7 = obb.corner(7);
    EXPECT_NEAR(c7.x(), 1.0f, kFloatEpsilon);
    EXPECT_NEAR(c7.y(), 2.0f, kFloatEpsilon);
    EXPECT_NEAR(c7.z(), 3.0f, kFloatEpsilon);

    // Index 1: (+x, -y, -z) - only bit 0 set
    Vec3f c1 = obb.corner(1);
    EXPECT_NEAR(c1.x(), 1.0f, kFloatEpsilon);
    EXPECT_NEAR(c1.y(), -2.0f, kFloatEpsilon);
    EXPECT_NEAR(c1.z(), -3.0f, kFloatEpsilon);
}

TEST_F(ObbTest, CornerWithOffset) {
    Obb obb(Vec3f(10, 20, 30), Vec3f(1, 1, 1));

    Vec3f c0 = obb.corner(0);
    EXPECT_NEAR(c0.x(), 9.0f, kFloatEpsilon);
    EXPECT_NEAR(c0.y(), 19.0f, kFloatEpsilon);
    EXPECT_NEAR(c0.z(), 29.0f, kFloatEpsilon);

    Vec3f c7 = obb.corner(7);
    EXPECT_NEAR(c7.x(), 11.0f, kFloatEpsilon);
    EXPECT_NEAR(c7.y(), 21.0f, kFloatEpsilon);
    EXPECT_NEAR(c7.z(), 31.0f, kFloatEpsilon);
}

TEST_F(ObbTest, CornerMatchesGetCorners) {
    Quatf rotation = Quatf::fromAxisAngle(Vec3f::yAxis(), degToRad(45.0f));
    Obb obb(Vec3f(5, 10, 15), Vec3f(1, 2, 3), rotation);

    Vec3f corners_array[8];
    obb.getCorners(corners_array);

    for (uint32_t i = 0; i < 8; ++i) {
        Vec3f single_corner = obb.corner(i);
        EXPECT_TRUE(single_corner.areSame(corners_array[i])) << "Corner " << i << " mismatch";
    }
}

// ============================================================================
// Surface Area Tests
// ============================================================================

TEST_F(ObbTest, SurfaceAreaUnitCube) {
    Obb obb(Vec3f::zero(), Vec3f(0.5f, 0.5f, 0.5f));  // Unit cube (size 1x1x1)

    // Surface area = 6 * 1 * 1 = 6
    EXPECT_FLOAT_EQ(obb.surfaceArea(), 6.0f);
}

TEST_F(ObbTest, SurfaceAreaRectangular) {
    Obb obb(Vec3f::zero(), Vec3f(1, 2, 3));  // Size 2x4x6

    // Surface area = 2 * (2*4 + 4*6 + 6*2) = 2 * (8 + 24 + 12) = 2 * 44 = 88
    EXPECT_FLOAT_EQ(obb.surfaceArea(), 88.0f);
}

TEST_F(ObbTest, SurfaceAreaInvariantUnderRotation) {
    Obb obb1(Vec3f::zero(), Vec3f(1, 2, 3));
    Quatf rotation = Quatf::fromAxisAngle(Vec3f(1, 1, 1).normalized(), degToRad(47.0f));
    Obb obb2(Vec3f::zero(), Vec3f(1, 2, 3), rotation);

    EXPECT_FLOAT_EQ(obb1.surfaceArea(), obb2.surfaceArea());
}

TEST_F(ObbTest, SurfaceAreaInvariantUnderTranslation) {
    Obb obb1(Vec3f::zero(), Vec3f(1, 2, 3));
    Obb obb2(Vec3f(100, 200, 300), Vec3f(1, 2, 3));

    EXPECT_FLOAT_EQ(obb1.surfaceArea(), obb2.surfaceArea());
}

// ============================================================================
// Axis Index Tests
// ============================================================================

TEST_F(ObbTest, AxisByIndex) {
    Quatf rotation = Quatf::fromAxisAngle(Vec3f::yAxis(), degToRad(45.0f));
    Obb obb(Vec3f::zero(), Vec3f(1, 1, 1), rotation);

    EXPECT_TRUE(obb.axis(0).areSame(obb.axisX()));
    EXPECT_TRUE(obb.axis(1).areSame(obb.axisY()));
    EXPECT_TRUE(obb.axis(2).areSame(obb.axisZ()));
}

TEST_F(ObbTest, AxisByIndexOutOfRange) {
    Obb obb;

    // Index >= 2 should return Z axis (default case)
    EXPECT_TRUE(obb.axis(3).areSame(obb.axisZ()));
    EXPECT_TRUE(obb.axis(100).areSame(obb.axisZ()));
}

TEST_F(ObbTest, AxesOrthogonal) {
    Quatf rotation = Quatf::fromAxisAngle(Vec3f(1, 2, 3).normalized(), degToRad(37.0f));
    Obb obb(Vec3f::zero(), Vec3f(1, 1, 1), rotation);

    Vec3f x = obb.axis(0);
    Vec3f y = obb.axis(1);
    Vec3f z = obb.axis(2);

    // All axes should be orthogonal
    EXPECT_NEAR(x.dot(y), 0.0f, kFloatEpsilon);
    EXPECT_NEAR(y.dot(z), 0.0f, kFloatEpsilon);
    EXPECT_NEAR(z.dot(x), 0.0f, kFloatEpsilon);

    // All axes should be unit length
    EXPECT_NEAR(x.length(), 1.0f, kFloatEpsilon);
    EXPECT_NEAR(y.length(), 1.0f, kFloatEpsilon);
    EXPECT_NEAR(z.length(), 1.0f, kFloatEpsilon);
}

// ============================================================================
// Rotation Matrix Tests
// ============================================================================

TEST_F(ObbTest, RotationMatrixIdentity) {
    Obb obb(Vec3f::zero(), Vec3f(1, 1, 1), Quatf::identity());
    Mat3f rot = obb.rotationMatrix();

    EXPECT_TRUE(rot.approxEquals(Mat3f::identity()));
}

TEST_F(ObbTest, RotationMatrixFromOrientation) {
    Quatf orientation = Quatf::fromAxisAngle(Vec3f::yAxis(), degToRad(90.0f));
    Obb obb(Vec3f::zero(), Vec3f(1, 1, 1), orientation);

    Mat3f rot = obb.rotationMatrix();
    Mat3f expected = orientation.toMatrix3();

    EXPECT_TRUE(rot.approxEquals(expected));
}

TEST_F(ObbTest, RotationMatrixColumnsMatchAxes) {
    Quatf orientation = Quatf::fromAxisAngle(Vec3f(1, 1, 1).normalized(), degToRad(60.0f));
    Obb obb(Vec3f::zero(), Vec3f(1, 1, 1), orientation);

    Mat3f rot = obb.rotationMatrix();

    EXPECT_TRUE(rot.getColumn(0).areSame(obb.axisX()));
    EXPECT_TRUE(rot.getColumn(1).areSame(obb.axisY()));
    EXPECT_TRUE(rot.getColumn(2).areSame(obb.axisZ()));
}

// ============================================================================
// Setter Tests
// ============================================================================

TEST_F(ObbTest, SetCenter) {
    Obb obb;
    Vec3f new_center(10, 20, 30);

    obb.setCenter(new_center);

    EXPECT_EQ(obb.center(), new_center);
}

TEST_F(ObbTest, SetHalfExtents) {
    Obb obb;
    Vec3f new_extents(5, 10, 15);

    obb.setHalfExtents(new_extents);

    EXPECT_EQ(obb.halfExtents(), new_extents);
}

TEST_F(ObbTest, SetOrientation) {
    Obb obb;
    Quatf new_orientation = Quatf::fromAxisAngle(Vec3f::zAxis(), degToRad(45.0f));

    obb.setOrientation(new_orientation);

    EXPECT_TRUE(obb.orientation().approxEquals(new_orientation));
}

TEST_F(ObbTest, SettersPreserveOtherProperties) {
    Vec3f center(1, 2, 3);
    Vec3f extents(4, 5, 6);
    Quatf orientation = Quatf::fromAxisAngle(Vec3f::xAxis(), degToRad(30.0f));

    Obb obb(center, extents, orientation);

    // Change center
    obb.setCenter(Vec3f(10, 20, 30));
    EXPECT_TRUE(obb.halfExtents().areSame(extents));
    EXPECT_TRUE(obb.orientation().approxEquals(orientation));

    // Reset and change extents
    obb = Obb(center, extents, orientation);
    obb.setHalfExtents(Vec3f(7, 8, 9));
    EXPECT_TRUE(obb.center().areSame(center));
    EXPECT_TRUE(obb.orientation().approxEquals(orientation));

    // Reset and change orientation
    obb = Obb(center, extents, orientation);
    obb.setOrientation(Quatf::identity());
    EXPECT_TRUE(obb.center().areSame(center));
    EXPECT_TRUE(obb.halfExtents().areSame(extents));
}

// ============================================================================
// Edge Cases and Validity Tests
// ============================================================================

TEST_F(ObbTest, ZeroHalfExtents) {
    Obb obb(Vec3f::zero(), Vec3f::zero());

    EXPECT_FLOAT_EQ(obb.volume(), 0.0f);
    EXPECT_FLOAT_EQ(obb.surfaceArea(), 0.0f);
    EXPECT_TRUE(obb.contains(Vec3f::zero()));
}

TEST_F(ObbTest, VerySmallExtents) {
    Obb obb(Vec3f::zero(), Vec3f(kFloatEpsilon, kFloatEpsilon, kFloatEpsilon));

    EXPECT_TRUE(obb.isValid());
    EXPECT_GT(obb.volume(), 0.0f);
}

TEST_F(ObbTest, LargeExtents) {
    Obb obb(Vec3f::zero(), Vec3f(1000000.0f, 1000000.0f, 1000000.0f));

    EXPECT_TRUE(obb.isValid());
    EXPECT_TRUE(obb.contains(Vec3f(500000.0f, 500000.0f, 500000.0f)));
}

}  // namespace vne::math

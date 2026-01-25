/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Author:    Ajeet Singh Yadav
 * Created:   January 2026
 *
 * Frustum culling tests - practical visibility testing scenarios
 * Tests culling with multi-backend projection matrices.
 * ----------------------------------------------------------------------
 */

#include <gtest/gtest.h>

#include "vertexnova/math/core/core.h"
#include "vertexnova/math/geometry/geometry.h"

#include <vector>

namespace vne::math {

// ============================================================================
// Practical Frustum Culling Tests
// ============================================================================

class FrustumCullingTest : public ::testing::Test {
   protected:
    void SetUp() override {
        // Camera setup
        eye_ = Vec3f(0.0f, 5.0f, 10.0f);
        target_ = Vec3f(0.0f, 0.0f, 0.0f);
        fov_ = degToRad(60.0f);
        aspect_ = 16.0f / 9.0f;
        z_near_ = 0.1f;
        z_far_ = 100.0f;
    }

    Frustum createFrustum(GraphicsApi api) {
        Mat4f view = Mat4f::lookAt(eye_, target_, Vec3f::yAxis(), api);
        Mat4f proj = Mat4f::perspective(fov_, aspect_, z_near_, z_far_, api);
        Mat4f vp = viewProjection(view, proj);

        Frustum frustum;
        frustum.extractFromMatrix(vp);
        return frustum;
    }

    Vec3f eye_;
    Vec3f target_;
    float fov_;
    float aspect_;
    float z_near_;
    float z_far_;
};

TEST_F(FrustumCullingTest, PointInFrontOfCamera) {
    Frustum frustum = createFrustum(GraphicsApi::eVulkan);

    // Point in front of camera (at target)
    EXPECT_TRUE(frustum.contains(Vec3f::zero()));

    // Point slightly in front
    EXPECT_TRUE(frustum.contains(Vec3f(0.0f, 0.0f, -5.0f)));
}

TEST_F(FrustumCullingTest, PointBehindCamera) {
    Frustum frustum = createFrustum(GraphicsApi::eVulkan);

    // Point behind camera
    EXPECT_FALSE(frustum.contains(Vec3f(0.0f, 5.0f, 20.0f)));
}

TEST_F(FrustumCullingTest, PointBeyondFarPlane) {
    Frustum frustum = createFrustum(GraphicsApi::eVulkan);

    // Point far beyond far plane
    EXPECT_FALSE(frustum.contains(Vec3f(0.0f, 0.0f, -200.0f)));
}

TEST_F(FrustumCullingTest, PointOutsideFOV) {
    Frustum frustum = createFrustum(GraphicsApi::eVulkan);

    // Point far to the side
    EXPECT_FALSE(frustum.contains(Vec3f(100.0f, 0.0f, 0.0f)));
}

TEST_F(FrustumCullingTest, SphereFullyInside) {
    Frustum frustum = createFrustum(GraphicsApi::eVulkan);

    Sphere sphere(Vec3f::zero(), 0.5f);

    EXPECT_TRUE(frustum.intersects(sphere));
    EXPECT_TRUE(frustum.containsFully(sphere));
}

TEST_F(FrustumCullingTest, SpherePartiallyInside) {
    Frustum frustum = createFrustum(GraphicsApi::eVulkan);

    // Large sphere that intersects frustum boundary
    Sphere sphere(Vec3f(20.0f, 0.0f, 0.0f), 15.0f);

    EXPECT_TRUE(frustum.intersects(sphere));
    EXPECT_FALSE(frustum.containsFully(sphere));
}

TEST_F(FrustumCullingTest, SphereFullyOutside) {
    Frustum frustum = createFrustum(GraphicsApi::eVulkan);

    Sphere sphere(Vec3f(100.0f, 0.0f, 0.0f), 2.0f);

    EXPECT_FALSE(frustum.intersects(sphere));
    EXPECT_FALSE(frustum.containsFully(sphere));
}

TEST_F(FrustumCullingTest, AabbFullyInside) {
    Frustum frustum = createFrustum(GraphicsApi::eVulkan);

    Aabb box(Vec3f(-0.5f, -0.5f, -0.5f), Vec3f(0.5f, 0.5f, 0.5f));

    EXPECT_TRUE(frustum.intersects(box));
    EXPECT_TRUE(frustum.containsFully(box));
}

TEST_F(FrustumCullingTest, AabbPartiallyInside) {
    Frustum frustum = createFrustum(GraphicsApi::eVulkan);

    // Large box that definitely extends beyond the frustum
    // Camera at (0,5,10) with far=100 - far plane around z = -90
    // This huge box must be partially inside
    Aabb box(Vec3f(-200.0f, -200.0f, -200.0f), Vec3f(200.0f, 200.0f, 200.0f));

    // Such a large box definitely intersects the frustum
    EXPECT_TRUE(frustum.intersects(box));
    // But cannot be fully contained
    EXPECT_FALSE(frustum.containsFully(box));
}

TEST_F(FrustumCullingTest, AabbFullyOutside) {
    Frustum frustum = createFrustum(GraphicsApi::eVulkan);

    Aabb box(Vec3f(100.0f, 100.0f, 100.0f), Vec3f(101.0f, 101.0f, 101.0f));

    EXPECT_FALSE(frustum.intersects(box));
    EXPECT_FALSE(frustum.containsFully(box));
}

// ============================================================================
// Multi-Backend Culling Tests
// ============================================================================

class MultiBackendCullingTest : public ::testing::Test {
   protected:
    void SetUp() override {
        eye_ = Vec3f(0.0f, 5.0f, 10.0f);
        target_ = Vec3f(0.0f, 0.0f, 0.0f);
    }

    Vec3f eye_;
    Vec3f target_;
};

TEST_F(MultiBackendCullingTest, SameCullingResultsAllApis) {
    // A visible object should be visible from all APIs
    Sphere visible_sphere(Vec3f::zero(), 1.0f);

    // An invisible object should be invisible from all APIs
    Sphere invisible_sphere(Vec3f(1000.0f, 0.0f, 0.0f), 1.0f);

    GraphicsApi apis[] = {GraphicsApi::eOpenGL,
                          GraphicsApi::eVulkan,
                          GraphicsApi::eMetal,
                          GraphicsApi::eDirectX,
                          GraphicsApi::eWebGPU};

    for (GraphicsApi api : apis) {
        Mat4f view = Mat4f::lookAt(eye_, target_, Vec3f::yAxis(), api);
        Mat4f proj = Mat4f::perspective(degToRad(60.0f), 16.0f / 9.0f, 0.1f, 100.0f, api);
        Mat4f vp = viewProjection(view, proj);

        Frustum frustum;
        frustum.extractFromMatrix(vp);

        EXPECT_TRUE(frustum.intersects(visible_sphere)) << "Failed for API: " << static_cast<int>(api);

        EXPECT_FALSE(frustum.intersects(invisible_sphere)) << "Failed for API: " << static_cast<int>(api);
    }
}

// ============================================================================
// Scene Culling Simulation Tests
// ============================================================================

class SceneCullingTest : public ::testing::Test {
   protected:
    struct SceneObject {
        std::string name;
        Aabb bounds;
    };

    void SetUp() override {
        // Create a simple scene
        scene_ = {
            {"Tree_1", Aabb(Vec3f(-2.0f, 0.0f, -15.0f), Vec3f(-1.0f, 5.0f, -14.0f))},
            {"Tree_2", Aabb(Vec3f(3.0f, 0.0f, -20.0f), Vec3f(4.0f, 5.0f, -19.0f))},
            {"Rock_1", Aabb(Vec3f(-5.0f, 0.0f, -10.0f), Vec3f(-4.0f, 1.0f, -9.0f))},
            {"House", Aabb(Vec3f(0.0f, 0.0f, -30.0f), Vec3f(5.0f, 4.0f, -25.0f))},
            {"Enemy_behind", Aabb(Vec3f(-1.0f, 0.0f, 5.0f), Vec3f(1.0f, 2.0f, 7.0f))},
            {"Distant_mountain", Aabb(Vec3f(-20.0f, 0.0f, -200.0f), Vec3f(20.0f, 50.0f, -150.0f))},
            {"Far_left_tree", Aabb(Vec3f(-100.0f, 0.0f, -15.0f), Vec3f(-99.0f, 5.0f, -14.0f))},
        };
    }

    std::vector<SceneObject> scene_;
};

TEST_F(SceneCullingTest, CullScene) {
    Vec3f eye(0.0f, 2.0f, 0.0f);
    Vec3f target(0.0f, 0.0f, -10.0f);

    Mat4f view = Mat4f::lookAt(eye, target, Vec3f::yAxis(), GraphicsApi::eVulkan);
    Mat4f proj = Mat4f::perspective(degToRad(60.0f), 16.0f / 9.0f, 0.5f, 100.0f, GraphicsApi::eVulkan);
    Mat4f vp = viewProjection(view, proj);

    Frustum frustum;
    frustum.extractFromMatrix(vp);

    int visible_count = 0;
    int culled_count = 0;

    for (const auto& obj : scene_) {
        if (frustum.intersects(obj.bounds)) {
            visible_count++;
        } else {
            culled_count++;
        }
    }

    // Should have culled at least some objects
    EXPECT_GT(culled_count, 0);

    // Should have some visible objects
    EXPECT_GT(visible_count, 0);

    // Known objects that should be culled:
    // - Enemy_behind (behind camera)
    // - Distant_mountain (beyond far plane)
    // - Far_left_tree (outside FOV)
    EXPECT_GE(culled_count, 3);
}

TEST_F(SceneCullingTest, ObjectBehindCameraIsCulled) {
    Vec3f eye(0.0f, 2.0f, 0.0f);
    Vec3f target(0.0f, 0.0f, -10.0f);

    Mat4f view = Mat4f::lookAt(eye, target, Vec3f::yAxis(), GraphicsApi::eVulkan);
    Mat4f proj = Mat4f::perspective(degToRad(60.0f), 16.0f / 9.0f, 0.5f, 100.0f, GraphicsApi::eVulkan);
    Mat4f vp = viewProjection(view, proj);

    Frustum frustum;
    frustum.extractFromMatrix(vp);

    // Find "Enemy_behind" object
    for (const auto& obj : scene_) {
        if (obj.name == "Enemy_behind") {
            EXPECT_FALSE(frustum.intersects(obj.bounds)) << "Object behind camera should be culled";
            break;
        }
    }
}

TEST_F(SceneCullingTest, ObjectBeyondFarPlaneIsCulled) {
    Vec3f eye(0.0f, 2.0f, 0.0f);
    Vec3f target(0.0f, 0.0f, -10.0f);

    Mat4f view = Mat4f::lookAt(eye, target, Vec3f::yAxis(), GraphicsApi::eVulkan);
    Mat4f proj = Mat4f::perspective(degToRad(60.0f), 16.0f / 9.0f, 0.5f, 100.0f, GraphicsApi::eVulkan);
    Mat4f vp = viewProjection(view, proj);

    Frustum frustum;
    frustum.extractFromMatrix(vp);

    // Find "Distant_mountain" object (at z = -200, far beyond far plane of 100)
    for (const auto& obj : scene_) {
        if (obj.name == "Distant_mountain") {
            EXPECT_FALSE(frustum.intersects(obj.bounds)) << "Object beyond far plane should be culled";
            break;
        }
    }
}

}  // namespace vne::math

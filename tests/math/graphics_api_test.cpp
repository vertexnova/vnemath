/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Author:    Ajeet Singh Yadav
 * Created:   January 2026
 *
 * Comprehensive multi-backend graphics API tests
 * Tests projection matrices, view matrices, and coordinate system
 * conventions across OpenGL, Vulkan, Metal, DirectX, and WebGPU.
 * ----------------------------------------------------------------------
 */

#include <gtest/gtest.h>

#include "vertexnova/math/core/core.h"
#include "vertexnova/math/projection_utils.h"

namespace vne::math {

// ============================================================================
// Graphics API Traits Tests
// ============================================================================

class GraphicsApiTraitsTest : public ::testing::Test {
   protected:
    static constexpr float kEps = 1e-5f;
};

TEST_F(GraphicsApiTraitsTest, OpenGLTraits) {
    EXPECT_EQ(getClipSpaceDepth(GraphicsApi::eOpenGL), ClipSpaceDepth::eNegativeOneToOne);
    EXPECT_EQ(getHandedness(GraphicsApi::eOpenGL), Handedness::eRight);
    // OpenGL framebuffer origin is bottom-left
    EXPECT_FALSE(needsYFlip(GraphicsApi::eOpenGL));
    EXPECT_FALSE(screenOriginIsTopLeft(GraphicsApi::eOpenGL));
    // OpenGL NDC is Y-up, no projection flip needed
    EXPECT_FALSE(needsProjectionYFlip(GraphicsApi::eOpenGL));
}

TEST_F(GraphicsApiTraitsTest, VulkanTraits) {
    EXPECT_EQ(getClipSpaceDepth(GraphicsApi::eVulkan), ClipSpaceDepth::eZeroToOne);
    EXPECT_EQ(getHandedness(GraphicsApi::eVulkan), Handedness::eRight);
    // Vulkan framebuffer origin is top-left
    EXPECT_TRUE(needsYFlip(GraphicsApi::eVulkan));
    EXPECT_TRUE(screenOriginIsTopLeft(GraphicsApi::eVulkan));
    // Vulkan NDC is Y-down, so projection Y-flip is needed
    EXPECT_TRUE(needsProjectionYFlip(GraphicsApi::eVulkan));
}

TEST_F(GraphicsApiTraitsTest, MetalTraits) {
    EXPECT_EQ(getClipSpaceDepth(GraphicsApi::eMetal), ClipSpaceDepth::eZeroToOne);
    EXPECT_EQ(getHandedness(GraphicsApi::eMetal), Handedness::eLeft);
    // Metal framebuffer origin is top-left
    EXPECT_TRUE(needsYFlip(GraphicsApi::eMetal));
    EXPECT_TRUE(screenOriginIsTopLeft(GraphicsApi::eMetal));
    // Metal NDC is Y-up, no projection flip needed
    EXPECT_FALSE(needsProjectionYFlip(GraphicsApi::eMetal));
}

TEST_F(GraphicsApiTraitsTest, DirectXTraits) {
    EXPECT_EQ(getClipSpaceDepth(GraphicsApi::eDirectX), ClipSpaceDepth::eZeroToOne);
    EXPECT_EQ(getHandedness(GraphicsApi::eDirectX), Handedness::eLeft);
    // DirectX framebuffer origin is top-left, so needsYFlip() returns true for screen-space
    EXPECT_TRUE(needsYFlip(GraphicsApi::eDirectX));
    // But no projection matrix Y-flip needed (NDC Y-up)
    EXPECT_FALSE(needsProjectionYFlip(GraphicsApi::eDirectX));
}

TEST_F(GraphicsApiTraitsTest, WebGPUTraits) {
    EXPECT_EQ(getClipSpaceDepth(GraphicsApi::eWebGPU), ClipSpaceDepth::eZeroToOne);
    EXPECT_EQ(getHandedness(GraphicsApi::eWebGPU), Handedness::eRight);
    // WebGPU framebuffer origin is top-left
    EXPECT_TRUE(needsYFlip(GraphicsApi::eWebGPU));
    EXPECT_TRUE(screenOriginIsTopLeft(GraphicsApi::eWebGPU));
    // WebGPU NDC is Y-up, no projection flip needed
    EXPECT_FALSE(needsProjectionYFlip(GraphicsApi::eWebGPU));
}

// ============================================================================
// Perspective Projection Tests - All APIs
// ============================================================================

class PerspectiveProjectionTest : public ::testing::Test {
   protected:
    static constexpr float kFov = degToRad(60.0f);
    static constexpr float kAspect = 16.0f / 9.0f;
    static constexpr float kNear = 0.1f;
    static constexpr float kFar = 1000.0f;
    static constexpr float kEps = 1e-5f;
};

TEST_F(PerspectiveProjectionTest, OpenGLPerspective) {
    Mat4f proj = Mat4f::perspective(kFov, kAspect, kNear, kFar, GraphicsApi::eOpenGL);

    // OpenGL: Y not flipped
    EXPECT_GT(proj[1][1], 0.0f);

    // Test near plane mapping (should map to -1)
    Vec4f near_point(0.0f, 0.0f, -kNear, 1.0f);
    Vec4f clip = proj * near_point;
    float ndc_z = clip.z() / clip.w();
    EXPECT_NEAR(ndc_z, -1.0f, kEps);

    // Test far plane mapping (should map to 1)
    Vec4f far_point(0.0f, 0.0f, -kFar, 1.0f);
    clip = proj * far_point;
    ndc_z = clip.z() / clip.w();
    EXPECT_NEAR(ndc_z, 1.0f, kEps);
}

TEST_F(PerspectiveProjectionTest, VulkanPerspective) {
    Mat4f proj = Mat4f::perspective(kFov, kAspect, kNear, kFar, GraphicsApi::eVulkan);

    // Vulkan: Y flipped
    EXPECT_LT(proj[1][1], 0.0f);

    // Test near plane mapping (should map to 0)
    Vec4f near_point(0.0f, 0.0f, -kNear, 1.0f);
    Vec4f clip = proj * near_point;
    float ndc_z = clip.z() / clip.w();
    EXPECT_NEAR(ndc_z, 0.0f, kEps);

    // Test far plane mapping (should map to 1)
    Vec4f far_point(0.0f, 0.0f, -kFar, 1.0f);
    clip = proj * far_point;
    ndc_z = clip.z() / clip.w();
    EXPECT_NEAR(ndc_z, 1.0f, kEps);
}

TEST_F(PerspectiveProjectionTest, MetalPerspective) {
    Mat4f proj = Mat4f::perspective(kFov, kAspect, kNear, kFar, GraphicsApi::eMetal);

    // Metal: NDC Y-up (NO projection flip needed), left-handed, [0,1] depth
    // Note: Metal's framebuffer origin is top-left, but that's handled by the
    // viewport/rasterizer, not the projection matrix.
    EXPECT_GT(proj[1][1], 0.0f);

    // Note: Metal is left-handed, so z direction is inverted
    Vec4f near_point(0.0f, 0.0f, kNear, 1.0f);  // +Z for left-handed
    Vec4f clip = proj * near_point;
    float ndc_z = clip.z() / clip.w();
    EXPECT_NEAR(ndc_z, 0.0f, kEps);
}

TEST_F(PerspectiveProjectionTest, DirectXPerspective) {
    Mat4f proj = Mat4f::perspective(kFov, kAspect, kNear, kFar, GraphicsApi::eDirectX);

    // DirectX: Y not flipped (native), left-handed, [0,1] depth
    EXPECT_GT(proj[1][1], 0.0f);

    Vec4f near_point(0.0f, 0.0f, kNear, 1.0f);  // +Z for left-handed
    Vec4f clip = proj * near_point;
    float ndc_z = clip.z() / clip.w();
    EXPECT_NEAR(ndc_z, 0.0f, kEps);
}

TEST_F(PerspectiveProjectionTest, WebGPUPerspective) {
    Mat4f proj = Mat4f::perspective(kFov, kAspect, kNear, kFar, GraphicsApi::eWebGPU);

    // WebGPU: NDC Y-up (NO projection flip needed), right-handed, [0,1] depth
    // Note: WebGPU's framebuffer origin is top-left, but that's handled by the
    // viewport/rasterizer, not the projection matrix.
    EXPECT_GT(proj[1][1], 0.0f);
}

TEST_F(PerspectiveProjectionTest, CenterPointMapsToOriginInNDC) {
    // For all APIs, a point at center of view should map to (0, 0, z) in NDC
    GraphicsApi apis[] = {GraphicsApi::eOpenGL,
                          GraphicsApi::eVulkan,
                          GraphicsApi::eMetal,
                          GraphicsApi::eDirectX,
                          GraphicsApi::eWebGPU};

    for (GraphicsApi api : apis) {
        Mat4f proj = Mat4f::perspective(kFov, kAspect, kNear, kFar, api);

        // Point at center of view, mid-depth
        float mid_z = (kNear + kFar) / 2.0f;
        Vec4f center(0.0f, 0.0f, getHandedness(api) == Handedness::eLeft ? mid_z : -mid_z, 1.0f);
        Vec4f clip = proj * center;

        float ndc_x = clip.x() / clip.w();
        float ndc_y = clip.y() / clip.w();

        EXPECT_NEAR(ndc_x, 0.0f, kEps) << "Failed for API: " << static_cast<int>(api);
        EXPECT_NEAR(ndc_y, 0.0f, kEps) << "Failed for API: " << static_cast<int>(api);
    }
}

// ============================================================================
// Orthographic Projection Tests - All APIs
// ============================================================================

class OrthographicProjectionTest : public ::testing::Test {
   protected:
    static constexpr float kLeft = -10.0f;
    static constexpr float kRight = 10.0f;
    static constexpr float kBottom = -10.0f;
    static constexpr float kTop = 10.0f;
    static constexpr float kNear = 0.1f;
    static constexpr float kFar = 100.0f;
    static constexpr float kEps = 1e-5f;
};

TEST_F(OrthographicProjectionTest, OpenGLOrtho) {
    Mat4f proj = Mat4f::ortho(kLeft, kRight, kBottom, kTop, kNear, kFar, GraphicsApi::eOpenGL);

    // Test corner mapping
    Vec4f corner(kRight, kTop, -kNear, 1.0f);
    Vec4f clip = proj * corner;
    EXPECT_NEAR(clip.x(), 1.0f, kEps);
    EXPECT_NEAR(clip.y(), 1.0f, kEps);
    EXPECT_NEAR(clip.z(), -1.0f, kEps);  // OpenGL: near maps to -1
}

TEST_F(OrthographicProjectionTest, VulkanOrtho) {
    Mat4f proj = Mat4f::ortho(kLeft, kRight, kBottom, kTop, kNear, kFar, GraphicsApi::eVulkan);

    // Vulkan: Y flipped
    EXPECT_LT(proj[1][1], 0.0f);

    // Test center mapping
    Vec4f center(0.0f, 0.0f, -kNear, 1.0f);
    Vec4f clip = proj * center;
    EXPECT_NEAR(clip.x(), 0.0f, kEps);
    EXPECT_NEAR(clip.y(), 0.0f, kEps);
    EXPECT_NEAR(clip.z(), 0.0f, kEps);  // Vulkan: near maps to 0
}

TEST_F(OrthographicProjectionTest, ScreenSpaceOrtho) {
    // Common use case: 2D UI rendering
    float screen_width = 1920.0f;
    float screen_height = 1080.0f;

    // OpenGL ortho - standard Y orientation
    Mat4f proj_gl = Mat4f::ortho(0.0f, screen_width, 0.0f, screen_height, -1.0f, 1.0f, GraphicsApi::eOpenGL);

    // Screen center should map to NDC (0, 0)
    Vec4f screen_center(screen_width / 2.0f, screen_height / 2.0f, 0.0f, 1.0f);
    Vec4f ndc_gl = proj_gl * screen_center;
    EXPECT_NEAR(ndc_gl.x(), 0.0f, kEps);
    EXPECT_NEAR(ndc_gl.y(), 0.0f, kEps);

    // Top-left corner should map to (-1, 1) in OpenGL
    Vec4f top_left(0.0f, screen_height, 0.0f, 1.0f);
    Vec4f ndc_tl = proj_gl * top_left;
    EXPECT_NEAR(ndc_tl.x(), -1.0f, kEps);
    EXPECT_NEAR(ndc_tl.y(), 1.0f, kEps);
}

// ============================================================================
// View Matrix Tests - All APIs
// ============================================================================

class ViewMatrixTest : public ::testing::Test {
   protected:
    Vec3f eye_{0.0f, 5.0f, 10.0f};
    Vec3f target_{0.0f, 0.0f, 0.0f};
    Vec3f up_{0.0f, 1.0f, 0.0f};
    static constexpr float kEps = 1e-5f;
};

TEST_F(ViewMatrixTest, LookAtRightHanded) {
    Mat4f view = Mat4f::lookAt(eye_, target_, up_, GraphicsApi::eVulkan);

    // Origin should be in front of camera in view space
    Vec3f origin_view = view.transformPoint(Vec3f::zero());
    EXPECT_LT(origin_view.z(), 0.0f);  // Negative Z = in front for RH

    // Eye position should be at origin in view space
    Vec3f eye_view = view.transformPoint(eye_);
    EXPECT_NEAR(eye_view.x(), 0.0f, kEps);
    EXPECT_NEAR(eye_view.y(), 0.0f, kEps);
    EXPECT_NEAR(eye_view.z(), 0.0f, kEps);
}

TEST_F(ViewMatrixTest, LookAtLeftHanded) {
    Mat4f view = Mat4f::lookAt(eye_, target_, up_, GraphicsApi::eMetal);

    // Origin should be in front of camera in view space
    Vec3f origin_view = view.transformPoint(Vec3f::zero());
    EXPECT_GT(origin_view.z(), 0.0f);  // Positive Z = in front for LH

    // Eye position should be at origin in view space
    Vec3f eye_view = view.transformPoint(eye_);
    EXPECT_NEAR(eye_view.x(), 0.0f, kEps);
    EXPECT_NEAR(eye_view.y(), 0.0f, kEps);
    EXPECT_NEAR(eye_view.z(), 0.0f, kEps);
}

TEST_F(ViewMatrixTest, ViewMatrixPreservesDistances) {
    // View matrix should preserve distances (it's an orthonormal transform)
    Mat4f view = Mat4f::lookAt(eye_, target_, up_, GraphicsApi::eVulkan);

    Vec3f p1(1.0f, 2.0f, 3.0f);
    Vec3f p2(4.0f, 5.0f, 6.0f);

    float world_dist = (p2 - p1).length();

    Vec3f p1_view = view.transformPoint(p1);
    Vec3f p2_view = view.transformPoint(p2);
    float view_dist = (p2_view - p1_view).length();

    EXPECT_NEAR(world_dist, view_dist, kEps);
}

TEST_F(ViewMatrixTest, DifferentApisProduceDifferentViews) {
    Mat4f view_vulkan = Mat4f::lookAt(eye_, target_, up_, GraphicsApi::eVulkan);
    Mat4f view_metal = Mat4f::lookAt(eye_, target_, up_, GraphicsApi::eMetal);

    // Vulkan (RH) and Metal (LH) should produce different view matrices
    EXPECT_FALSE(view_vulkan.approxEquals(view_metal));
}

// ============================================================================
// MVP Pipeline Tests - Complete Transformation Chain
// ============================================================================

class MVPPipelineTest : public ::testing::Test {
   protected:
    void SetUp() override {
        // Model: cube at (5, 0, -5), rotated 45 degrees
        position_ = Vec3f(5.0f, 0.0f, -5.0f);
        rotation_ = Quatf::fromAxisAngle(Vec3f::yAxis(), degToRad(45.0f));
        scale_ = Vec3f(1.0f, 1.0f, 1.0f);

        // Camera
        eye_ = Vec3f(0.0f, 5.0f, 10.0f);
        target_ = Vec3f(0.0f, 0.0f, 0.0f);

        // Projection parameters
        fov_ = degToRad(60.0f);
        aspect_ = 16.0f / 9.0f;
        z_near_ = 0.1f;
        z_far_ = 1000.0f;
    }

    Vec3f position_;
    Quatf rotation_;
    Vec3f scale_;
    Vec3f eye_;
    Vec3f target_;
    float fov_;
    float aspect_;
    float z_near_;
    float z_far_;
    static constexpr float kEps = 1e-4f;
};

TEST_F(MVPPipelineTest, MVPTransformVertexToClipSpace) {
    GraphicsApi apis[] = {GraphicsApi::eOpenGL, GraphicsApi::eVulkan, GraphicsApi::eMetal};

    for (GraphicsApi api : apis) {
        Mat4f model = modelMatrix(position_, rotation_, scale_);
        Mat4f view = Mat4f::lookAt(eye_, target_, Vec3f::yAxis(), api);
        Mat4f proj = Mat4f::perspective(fov_, aspect_, z_near_, z_far_, api);
        Mat4f mvp_mat = mvp(model, view, proj);

        // Transform a local vertex
        Vec4f local_vertex(0.0f, 1.0f, 0.0f, 1.0f);
        Vec4f clip_space = mvp_mat * local_vertex;

        // Should have valid W for perspective divide
        EXPECT_NE(clip_space.w(), 0.0f) << "Failed for API: " << static_cast<int>(api);

        // Perform perspective divide
        Vec3f ndc(clip_space.x() / clip_space.w(), clip_space.y() / clip_space.w(), clip_space.z() / clip_space.w());

        // NDC should be within valid range for visible geometry
        // (exact values depend on the scene setup, but should be reasonable)
        EXPECT_GT(ndc.x(), -2.0f) << "Failed for API: " << static_cast<int>(api);
        EXPECT_LT(ndc.x(), 2.0f) << "Failed for API: " << static_cast<int>(api);
    }
}

TEST_F(MVPPipelineTest, ViewProjectionHelper) {
    Mat4f view = Mat4f::lookAt(eye_, target_, Vec3f::yAxis(), GraphicsApi::eVulkan);
    Mat4f proj = Mat4f::perspective(fov_, aspect_, z_near_, z_far_, GraphicsApi::eVulkan);

    Mat4f vp1 = viewProjection(view, proj);
    Mat4f vp2 = proj * view;

    EXPECT_TRUE(vp1.approxEquals(vp2, kEps));
}

TEST_F(MVPPipelineTest, ModelMatrixHelper) {
    Mat4f model = modelMatrix(position_, rotation_, scale_);

    // Should correctly compose T * R * S
    Vec3f origin_local(0.0f, 0.0f, 0.0f);
    Vec3f origin_world = model.transformPoint(origin_local);

    EXPECT_NEAR(origin_world.x(), position_.x(), kEps);
    EXPECT_NEAR(origin_world.y(), position_.y(), kEps);
    EXPECT_NEAR(origin_world.z(), position_.z(), kEps);
}

TEST_F(MVPPipelineTest, InverseMVPRecoversWorldPosition) {
    Mat4f model = modelMatrix(position_, rotation_, scale_);
    Mat4f view = Mat4f::lookAt(eye_, target_, Vec3f::yAxis(), GraphicsApi::eVulkan);
    Mat4f proj = Mat4f::perspective(fov_, aspect_, z_near_, z_far_, GraphicsApi::eVulkan);
    Mat4f mvp_mat = mvp(model, view, proj);
    Mat4f mvp_inv = mvp_mat.inverse();

    // Transform to clip space then back
    Vec4f local_vertex(0.5f, 0.5f, 0.5f, 1.0f);
    Vec4f clip = mvp_mat * local_vertex;
    Vec4f recovered = mvp_inv * clip;

    // Normalize by W
    recovered = recovered / recovered.w();

    // Use larger epsilon for inverse precision
    constexpr float kInverseEps = 1e-3f;
    EXPECT_NEAR(recovered.x(), local_vertex.x(), kInverseEps);
    EXPECT_NEAR(recovered.y(), local_vertex.y(), kInverseEps);
    EXPECT_NEAR(recovered.z(), local_vertex.z(), kInverseEps);
}

// ============================================================================
// Screen Space Unprojection Tests
// ============================================================================

class UnprojectionTest : public ::testing::Test {
   protected:
    void SetUp() override {
        screen_width_ = 1920.0f;
        screen_height_ = 1080.0f;
        eye_ = Vec3f(0.0f, 5.0f, 10.0f);
        target_ = Vec3f(0.0f, 0.0f, 0.0f);
        fov_ = degToRad(60.0f);
    }

    float screen_width_;
    float screen_height_;
    Vec3f eye_;
    Vec3f target_;
    float fov_;
    static constexpr float kEps = 1e-4f;
};

TEST_F(UnprojectionTest, ScreenCenterUnprojectsToViewDirection) {
    Mat4f view = Mat4f::lookAt(eye_, target_, Vec3f::yAxis(), GraphicsApi::eVulkan);
    Mat4f proj = Mat4f::perspective(fov_, screen_width_ / screen_height_, 0.1f, 1000.0f, GraphicsApi::eVulkan);
    Mat4f vp_inv = (proj * view).inverse();

    // Screen center
    float ndc_x = 0.0f;
    float ndc_y = 0.0f;

    // Unproject near and far points
    Vec4f near_ndc(ndc_x, ndc_y, 0.0f, 1.0f);  // Vulkan near = 0
    Vec4f far_ndc(ndc_x, ndc_y, 1.0f, 1.0f);

    Vec4f near_world = vp_inv * near_ndc;
    Vec4f far_world = vp_inv * far_ndc;

    near_world = near_world / near_world.w();
    far_world = far_world / far_world.w();

    // Ray direction should point toward target
    Vec3f ray_dir =
        Vec3f(far_world.x() - near_world.x(), far_world.y() - near_world.y(), far_world.z() - near_world.z())
            .normalized();

    Vec3f expected_dir = (target_ - eye_).normalized();

    EXPECT_NEAR(ray_dir.x(), expected_dir.x(), kEps);
    EXPECT_NEAR(ray_dir.y(), expected_dir.y(), kEps);
    EXPECT_NEAR(ray_dir.z(), expected_dir.z(), kEps);
}

// ============================================================================
// Cross-API Consistency Tests
// ============================================================================

class CrossApiConsistencyTest : public ::testing::Test {
   protected:
    static constexpr float kEps = 1e-4f;
};

TEST_F(CrossApiConsistencyTest, AllApisRenderSameSceneCorrectly) {
    // Same scene should be "visible" from all APIs (just with different conventions)
    Vec3f object_pos(0.0f, 0.0f, -5.0f);  // Object in front of camera
    Vec3f camera_pos(0.0f, 0.0f, 0.0f);
    Vec3f camera_target(0.0f, 0.0f, -10.0f);

    GraphicsApi apis[] = {GraphicsApi::eOpenGL,
                          GraphicsApi::eVulkan,
                          GraphicsApi::eMetal,
                          GraphicsApi::eDirectX,
                          GraphicsApi::eWebGPU};

    for (GraphicsApi api : apis) {
        Mat4f view = Mat4f::lookAt(camera_pos, camera_target, Vec3f::yAxis(), api);
        Mat4f proj = Mat4f::perspective(degToRad(60.0f), 1.0f, 0.1f, 100.0f, api);
        Mat4f vp = proj * view;

        Vec4f object_clip = vp * Vec4f(object_pos.x(), object_pos.y(), object_pos.z(), 1.0f);

        // Object should be visible (positive W, within clip bounds)
        EXPECT_GT(object_clip.w(), 0.0f) << "Failed for API: " << static_cast<int>(api);

        float ndc_x = object_clip.x() / object_clip.w();
        float ndc_y = object_clip.y() / object_clip.w();
        float ndc_z = object_clip.z() / object_clip.w();

        // Should be within NDC bounds
        EXPECT_GE(ndc_x, -1.0f) << "Failed for API: " << static_cast<int>(api);
        EXPECT_LE(ndc_x, 1.0f) << "Failed for API: " << static_cast<int>(api);
        EXPECT_GE(ndc_y, -1.0f) << "Failed for API: " << static_cast<int>(api);
        EXPECT_LE(ndc_y, 1.0f) << "Failed for API: " << static_cast<int>(api);

        // Z should be within depth range (API-specific)
        if (getClipSpaceDepth(api) == ClipSpaceDepth::eZeroToOne) {
            EXPECT_GE(ndc_z, 0.0f) << "Failed for API: " << static_cast<int>(api);
            EXPECT_LE(ndc_z, 1.0f) << "Failed for API: " << static_cast<int>(api);
        } else {
            EXPECT_GE(ndc_z, -1.0f) << "Failed for API: " << static_cast<int>(api);
            EXPECT_LE(ndc_z, 1.0f) << "Failed for API: " << static_cast<int>(api);
        }
    }
}

// ============================================================================
// Projection Validation Tests
// ============================================================================

class ProjectionValidationTest : public ::testing::Test {
   protected:
    static constexpr float kFov = degToRad(60.0f);
    static constexpr float kAspect = 16.0f / 9.0f;
    static constexpr float kNear = 0.1f;
    static constexpr float kFar = 1000.0f;
};

TEST_F(ProjectionValidationTest, ValidateCorrectMatrices) {
    // Each API's projection matrix should validate for its own API
    GraphicsApi apis[] = {GraphicsApi::eOpenGL,
                          GraphicsApi::eVulkan,
                          GraphicsApi::eMetal,
                          GraphicsApi::eDirectX,
                          GraphicsApi::eWebGPU};

    for (GraphicsApi api : apis) {
        Mat4f proj = Mat4f::perspective(kFov, kAspect, kNear, kFar, api);
        EXPECT_TRUE(validateProjectionMatrix(proj, api)) << "Validation failed for " << graphicsApiName(api);
    }
}

TEST_F(ProjectionValidationTest, DetectMismatchedMatrices) {
    // Vulkan matrix used with OpenGL should fail validation
    Mat4f vulkan_proj = Mat4f::perspective(kFov, kAspect, kNear, kFar, GraphicsApi::eVulkan);
    EXPECT_FALSE(validateProjectionMatrix(vulkan_proj, GraphicsApi::eOpenGL));
    EXPECT_FALSE(validateProjectionMatrix(vulkan_proj, GraphicsApi::eMetal));
    EXPECT_FALSE(validateProjectionMatrix(vulkan_proj, GraphicsApi::eDirectX));
    EXPECT_FALSE(validateProjectionMatrix(vulkan_proj, GraphicsApi::eWebGPU));

    // OpenGL matrix used with Vulkan should fail validation
    Mat4f opengl_proj = Mat4f::perspective(kFov, kAspect, kNear, kFar, GraphicsApi::eOpenGL);
    EXPECT_FALSE(validateProjectionMatrix(opengl_proj, GraphicsApi::eVulkan));
}

TEST_F(ProjectionValidationTest, DetailedValidation) {
    Mat4f vulkan_proj = Mat4f::perspective(kFov, kAspect, kNear, kFar, GraphicsApi::eVulkan);

    bool expected_flip = false;
    bool actual_flip = false;

    // Vulkan matrix should validate correctly
    EXPECT_TRUE(validateProjectionMatrixDetailed(vulkan_proj, GraphicsApi::eVulkan, expected_flip, actual_flip));
    EXPECT_TRUE(expected_flip);  // Vulkan expects Y-flip
    EXPECT_TRUE(actual_flip);    // Matrix has Y-flip

    // Same matrix fails for OpenGL
    EXPECT_FALSE(validateProjectionMatrixDetailed(vulkan_proj, GraphicsApi::eOpenGL, expected_flip, actual_flip));
    EXPECT_FALSE(expected_flip);  // OpenGL doesn't expect Y-flip
    EXPECT_TRUE(actual_flip);     // But matrix has Y-flip
}

TEST_F(ProjectionValidationTest, GraphicsApiName) {
    EXPECT_STREQ(graphicsApiName(GraphicsApi::eOpenGL), "OpenGL");
    EXPECT_STREQ(graphicsApiName(GraphicsApi::eVulkan), "Vulkan");
    EXPECT_STREQ(graphicsApiName(GraphicsApi::eMetal), "Metal");
    EXPECT_STREQ(graphicsApiName(GraphicsApi::eDirectX), "DirectX");
    EXPECT_STREQ(graphicsApiName(GraphicsApi::eWebGPU), "WebGPU");
}

}  // namespace vne::math

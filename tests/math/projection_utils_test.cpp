/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Author:    Ajeet Singh Yadav
 * Created:   March 2026
 *
 * Autodoc:   yes
 * ----------------------------------------------------------------------
 */

/**
 * @file projection_utils_test.cpp
 * @brief Tests for clipToScreenMatrix, worldToScreenMatrix, ndcToScreen (3D),
 *        and consistency with the existing scalar project/unproject utilities.
 */

#include <gtest/gtest.h>

#include "vertexnova/math/projection_utils.h"

namespace vne::math {

class ProjectionUtilsTest : public ::testing::Test {
   protected:
    static constexpr float kEps = 1e-4f;
};

// ============================================================================
// clipToScreenMatrix — OpenGL (bottom-left origin, no Y-flip)
// ============================================================================

TEST_F(ProjectionUtilsTest, ClipToScreenMatrix_OpenGL_Center) {
    // NDC origin (0,0) should map to screen center
    Viewport vp(800.0f, 600.0f);
    Mat4f m = clipToScreenMatrix(vp, GraphicsApi::eOpenGL);

    Vec4f result = m * Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
    EXPECT_NEAR(result.x(), 400.0f, kEps);
    EXPECT_NEAR(result.y(), 300.0f, kEps);
}

TEST_F(ProjectionUtilsTest, ClipToScreenMatrix_OpenGL_BottomLeft) {
    // NDC (-1,-1) maps to (0,0) for OpenGL (bottom-left origin, Y is not flipped)
    Viewport vp(800.0f, 600.0f);
    Mat4f m = clipToScreenMatrix(vp, GraphicsApi::eOpenGL);

    Vec4f result = m * Vec4f(-1.0f, -1.0f, 0.0f, 1.0f);
    EXPECT_NEAR(result.x(), 0.0f, kEps);
    EXPECT_NEAR(result.y(), 0.0f, kEps);
}

TEST_F(ProjectionUtilsTest, ClipToScreenMatrix_OpenGL_TopRight) {
    // NDC (1,1) maps to (width, height) for OpenGL
    Viewport vp(800.0f, 600.0f);
    Mat4f m = clipToScreenMatrix(vp, GraphicsApi::eOpenGL);

    Vec4f result = m * Vec4f(1.0f, 1.0f, 0.0f, 1.0f);
    EXPECT_NEAR(result.x(), 800.0f, kEps);
    EXPECT_NEAR(result.y(), 600.0f, kEps);
}

// ============================================================================
// clipToScreenMatrix — Vulkan (top-left origin, Y-flip)
// ============================================================================

TEST_F(ProjectionUtilsTest, ClipToScreenMatrix_Vulkan_Center) {
    // NDC origin (0,0) should still map to screen center
    Viewport vp(800.0f, 600.0f);
    Mat4f m = clipToScreenMatrix(vp, GraphicsApi::eVulkan);

    Vec4f result = m * Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
    EXPECT_NEAR(result.x(), 400.0f, kEps);
    EXPECT_NEAR(result.y(), 300.0f, kEps);
}

TEST_F(ProjectionUtilsTest, ClipToScreenMatrix_Vulkan_YFlip) {
    // Vulkan projection keeps NDC Y-up; viewport transform flips to top-left screen space.
    Viewport vp(800.0f, 600.0f);
    Mat4f m = clipToScreenMatrix(vp, GraphicsApi::eVulkan);

    Vec4f top = m * Vec4f(0.0f, 1.0f, 0.0f, 1.0f);
    Vec4f bottom = m * Vec4f(0.0f, -1.0f, 0.0f, 1.0f);
    EXPECT_NEAR(top.y(), 0.0f, kEps);
    EXPECT_NEAR(bottom.y(), 600.0f, kEps);
}

TEST_F(ProjectionUtilsTest, ClipToScreenMatrix_Vulkan_TopLeft) {
    // NDC Y-up: top-left screen corner is NDC (-1, +1).
    Viewport vp(800.0f, 600.0f);
    Mat4f m = clipToScreenMatrix(vp, GraphicsApi::eVulkan);

    Vec4f result = m * Vec4f(-1.0f, 1.0f, 0.0f, 1.0f);
    EXPECT_NEAR(result.x(), 0.0f, kEps);
    EXPECT_NEAR(result.y(), 0.0f, kEps);
}

// ============================================================================
// clipToScreenMatrix — Metal (top-left origin, no projection Y-flip needed)
// ============================================================================

TEST_F(ProjectionUtilsTest, ClipToScreenMatrix_Metal_VsVulkan) {
    // Metal and Vulkan both use Y-up projection; viewport transform flips to top-left screen space.
    Viewport vp(800.0f, 600.0f);
    Mat4f m_metal = clipToScreenMatrix(vp, GraphicsApi::eMetal);
    Mat4f m_vk = clipToScreenMatrix(vp, GraphicsApi::eVulkan);

    Vec4f metal = m_metal * Vec4f(0.0f, 1.0f, 0.0f, 1.0f);
    Vec4f vk = m_vk * Vec4f(0.0f, 1.0f, 0.0f, 1.0f);
    EXPECT_NEAR(metal.y(), 0.0f, kEps);
    EXPECT_NEAR(vk.y(), 0.0f, kEps);
}

// ============================================================================
// clipToScreenMatrix — Offset viewport
// ============================================================================

TEST_F(ProjectionUtilsTest, ClipToScreenMatrix_OffsetViewport) {
    // Viewport starting at (100, 50)
    Viewport vp(100.0f, 50.0f, 800.0f, 600.0f);
    Mat4f m = clipToScreenMatrix(vp, GraphicsApi::eOpenGL);

    // NDC center (0,0) should map to viewport center
    Vec4f center = m * Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
    EXPECT_NEAR(center.x(), 500.0f, kEps);  // 100 + 400
    EXPECT_NEAR(center.y(), 350.0f, kEps);  // 50 + 300

    // NDC (-1,-1) should map to viewport origin
    Vec4f origin = m * Vec4f(-1.0f, -1.0f, 0.0f, 1.0f);
    EXPECT_NEAR(origin.x(), 100.0f, kEps);
    EXPECT_NEAR(origin.y(), 50.0f, kEps);
}

// ============================================================================
// clipToScreenMatrix — float width/height convenience overload
// ============================================================================

TEST_F(ProjectionUtilsTest, ClipToScreenMatrix_ConvenienceOverload_MatchesViewport) {
    Mat4f m_vp = clipToScreenMatrix(Viewport(800.0f, 600.0f), GraphicsApi::eOpenGL);
    Mat4f m_wh = clipToScreenMatrix(800.0f, 600.0f, GraphicsApi::eOpenGL);

    EXPECT_TRUE(m_vp.approxEquals(m_wh, kEps));
}

// ============================================================================
// clipToScreenMatrix — must match scalar ndcToScreen for XY
// ============================================================================

TEST_F(ProjectionUtilsTest, ClipToScreenMatrix_MatchesScalarNdcToScreen_OpenGL) {
    Viewport vp(1280.0f, 720.0f);
    Mat4f m = clipToScreenMatrix(vp, GraphicsApi::eOpenGL);

    // Test several NDC points
    const Vec2f ndc_points[] = {{0.0f, 0.0f}, {1.0f, 1.0f}, {-1.0f, -1.0f}, {0.5f, -0.3f}, {-0.7f, 0.8f}};

    for (const auto& ndc : ndc_points) {
        Vec2f scalar = ndcToScreen(ndc, vp, GraphicsApi::eOpenGL);
        Vec4f matrix = m * Vec4f(ndc.x(), ndc.y(), 0.0f, 1.0f);
        EXPECT_NEAR(matrix.x(), scalar.x(), kEps);
        EXPECT_NEAR(matrix.y(), scalar.y(), kEps);
    }
}

TEST_F(ProjectionUtilsTest, ClipToScreenMatrix_MatchesScalarNdcToScreen_Vulkan) {
    Viewport vp(1280.0f, 720.0f);
    Mat4f m = clipToScreenMatrix(vp, GraphicsApi::eVulkan);

    const Vec2f ndc_points[] = {{0.0f, 0.0f}, {1.0f, 1.0f}, {-1.0f, -1.0f}, {0.5f, -0.3f}, {-0.7f, 0.8f}};

    for (const auto& ndc : ndc_points) {
        Vec2f scalar = ndcToScreen(ndc, vp, GraphicsApi::eVulkan);
        Vec4f matrix = m * Vec4f(ndc.x(), ndc.y(), 0.0f, 1.0f);
        EXPECT_NEAR(matrix.x(), scalar.x(), kEps);
        EXPECT_NEAR(matrix.y(), scalar.y(), kEps);
    }
}

// ============================================================================
// worldToScreenMatrix — consistency with scalar project()
// ============================================================================

TEST_F(ProjectionUtilsTest, WorldToScreenMatrix_ConsistentWithProject_OpenGL) {
    // Set up a perspective camera
    Vec3f eye(0.0f, 0.0f, 5.0f);
    Vec3f target(0.0f, 0.0f, 0.0f);
    Vec3f up = Vec3f::yAxis();
    float fovy = degToRad(60.0f);
    float aspect = 800.0f / 600.0f;

    Mat4f view = Mat4f::lookAt(eye, target, up, GraphicsApi::eOpenGL);
    Mat4f proj = Mat4f::perspective(fovy, aspect, 0.1f, 100.0f, GraphicsApi::eOpenGL);
    Mat4f vp_mat = proj * view;

    Viewport vp(800.0f, 600.0f);

    // Test several world positions
    const Vec3f world_points[] = {
        {0.0f, 0.0f, 0.0f},
        {1.0f, 0.5f, -1.0f},
        {-0.5f, 0.3f, 0.5f},
    };

    Mat4f ws_mat = worldToScreenMatrix(vp_mat, vp, GraphicsApi::eOpenGL);

    for (const auto& wp : world_points) {
        // Scalar project
        Vec3f scalar = project(wp, vp_mat, vp, GraphicsApi::eOpenGL);

        // Matrix path: multiply, perspective divide
        Vec4f clip = ws_mat * Vec4f(wp, 1.0f);
        Vec2f matrix_screen(clip.x() / clip.w(), clip.y() / clip.w());

        EXPECT_NEAR(matrix_screen.x(), scalar.x(), kEps);
        EXPECT_NEAR(matrix_screen.y(), scalar.y(), kEps);
    }
}

TEST_F(ProjectionUtilsTest, WorldToScreenMatrix_ConsistentWithProject_Vulkan) {
    Vec3f eye(0.0f, 2.0f, 8.0f);
    Vec3f target(0.0f, 0.0f, 0.0f);
    Vec3f up = Vec3f::yAxis();
    float fovy = degToRad(45.0f);
    float aspect = 1920.0f / 1080.0f;

    Mat4f view = Mat4f::lookAt(eye, target, up, GraphicsApi::eVulkan);
    Mat4f proj = Mat4f::perspective(fovy, aspect, 0.1f, 1000.0f, GraphicsApi::eVulkan);
    Mat4f vp_mat = proj * view;

    Viewport vp(1920.0f, 1080.0f);

    const Vec3f world_points[] = {
        {0.0f, 0.0f, 0.0f},
        {2.0f, -1.0f, 1.0f},
    };

    Mat4f ws_mat = worldToScreenMatrix(vp_mat, vp, GraphicsApi::eVulkan);

    for (const auto& wp : world_points) {
        Vec3f scalar = project(wp, vp_mat, vp, GraphicsApi::eVulkan);

        Vec4f clip = ws_mat * Vec4f(wp, 1.0f);
        Vec2f matrix_screen(clip.x() / clip.w(), clip.y() / clip.w());

        EXPECT_NEAR(matrix_screen.x(), scalar.x(), kEps);
        EXPECT_NEAR(matrix_screen.y(), scalar.y(), kEps);
    }
}

// ============================================================================
// Round-trip: project → unproject
// ============================================================================

TEST_F(ProjectionUtilsTest, RoundTrip_ProjectUnproject_OpenGL) {
    Vec3f eye(0.0f, 3.0f, 10.0f);
    Vec3f target(0.0f, 0.0f, 0.0f);
    Mat4f view = Mat4f::lookAt(eye, target, Vec3f::yAxis(), GraphicsApi::eOpenGL);
    Mat4f proj = Mat4f::perspective(degToRad(60.0f), 800.0f / 600.0f, 0.1f, 100.0f, GraphicsApi::eOpenGL);
    Mat4f vp_mat = proj * view;
    Mat4f inv_vp = vp_mat.inverse();
    Viewport vp(800.0f, 600.0f);

    const Vec3f world_points[] = {
        {0.0f, 0.0f, 0.0f},
        {1.0f, 0.5f, -2.0f},
        {-0.3f, 0.7f, -1.5f},
    };

    for (const auto& wp : world_points) {
        Vec3f screen = project(wp, vp_mat, vp, GraphicsApi::eOpenGL);
        Vec3f recovered = unproject(screen, inv_vp, vp, GraphicsApi::eOpenGL);
        EXPECT_NEAR(recovered.x(), wp.x(), kEps);
        EXPECT_NEAR(recovered.y(), wp.y(), kEps);
        EXPECT_NEAR(recovered.z(), wp.z(), kEps);
    }
}

TEST_F(ProjectionUtilsTest, RoundTrip_ProjectUnproject_Vulkan) {
    Vec3f eye(0.0f, 3.0f, 10.0f);
    Vec3f target(0.0f, 0.0f, 0.0f);
    Mat4f view = Mat4f::lookAt(eye, target, Vec3f::yAxis(), GraphicsApi::eVulkan);
    Mat4f proj = Mat4f::perspective(degToRad(60.0f), 800.0f / 600.0f, 0.1f, 100.0f, GraphicsApi::eVulkan);
    Mat4f vp_mat = proj * view;
    Mat4f inv_vp = vp_mat.inverse();
    Viewport vp(800.0f, 600.0f);

    const Vec3f world_points[] = {
        {0.0f, 0.0f, 0.0f},
        {1.0f, 0.5f, -2.0f},
    };

    // Vulkan's projection Y-flip and [0,1] depth range accumulate slightly more
    // floating-point error through the perspective-divide + matrix-inverse path.
    static constexpr float kEpsVk = 5e-4f;

    for (const auto& wp : world_points) {
        Vec3f screen = project(wp, vp_mat, vp, GraphicsApi::eVulkan);
        Vec3f recovered = unproject(screen, inv_vp, vp, GraphicsApi::eVulkan);
        EXPECT_NEAR(recovered.x(), wp.x(), kEpsVk);
        EXPECT_NEAR(recovered.y(), wp.y(), kEpsVk);
        EXPECT_NEAR(recovered.z(), wp.z(), kEpsVk);
    }
}

// ============================================================================
// ndcToScreen (3D overload) — depth mapping
// ============================================================================

TEST_F(ProjectionUtilsTest, NdcToScreen3D_DepthMapping_OpenGL) {
    // OpenGL: ndc.z in [-1,1] → screen_z in [z_near, z_far]
    Viewport vp(0.0f, 0.0f, 800.0f, 600.0f, 0.0f, 1.0f);

    Vec3f near_ndc(0.0f, 0.0f, -1.0f);  // OpenGL near plane is NDC z = -1
    Vec3f far_ndc(0.0f, 0.0f, 1.0f);    // OpenGL far plane is NDC z = +1

    Vec3f near_screen = ndcToScreen(near_ndc, vp, GraphicsApi::eOpenGL);
    Vec3f far_screen = ndcToScreen(far_ndc, vp, GraphicsApi::eOpenGL);

    EXPECT_NEAR(near_screen.z(), 0.0f, kEps);  // z_near
    EXPECT_NEAR(far_screen.z(), 1.0f, kEps);   // z_far
}

TEST_F(ProjectionUtilsTest, NdcToScreen3D_DepthMapping_Vulkan) {
    // Vulkan: ndc.z in [0,1] → screen_z in [z_near, z_far]
    Viewport vp(0.0f, 0.0f, 800.0f, 600.0f, 0.0f, 1.0f);

    Vec3f near_ndc(0.0f, 0.0f, 0.0f);  // Vulkan near plane is NDC z = 0
    Vec3f far_ndc(0.0f, 0.0f, 1.0f);   // Vulkan far plane is NDC z = 1

    Vec3f near_screen = ndcToScreen(near_ndc, vp, GraphicsApi::eVulkan);
    Vec3f far_screen = ndcToScreen(far_ndc, vp, GraphicsApi::eVulkan);

    EXPECT_NEAR(near_screen.z(), 0.0f, kEps);  // z_near
    EXPECT_NEAR(far_screen.z(), 1.0f, kEps);   // z_far
}

TEST_F(ProjectionUtilsTest, NdcToScreen3D_XY_MatchesScalar2D) {
    // 3D ndcToScreen xy must match the existing 2D overload exactly
    Viewport vp(1920.0f, 1080.0f);
    Vec3f ndc(0.4f, -0.6f, 0.5f);

    Vec3f result3d = ndcToScreen(ndc, vp, GraphicsApi::eVulkan);
    Vec2f result2d = ndcToScreen(Vec2f(ndc.x(), ndc.y()), vp, GraphicsApi::eVulkan);

    EXPECT_NEAR(result3d.x(), result2d.x(), kEps);
    EXPECT_NEAR(result3d.y(), result2d.y(), kEps);
}

// ============================================================================
// screenToWorldRay — direction and origin
// ============================================================================

TEST_F(ProjectionUtilsTest, ScreenToWorldRay_OriginIsCameraPosition) {
    Vec3f eye(0.0f, 0.0f, 5.0f);
    Vec3f target(0.0f, 0.0f, 0.0f);
    Mat4f view = Mat4f::lookAt(eye, target, Vec3f::yAxis(), GraphicsApi::eOpenGL);
    Mat4f proj = Mat4f::perspective(degToRad(60.0f), 800.0f / 600.0f, 0.1f, 100.0f, GraphicsApi::eOpenGL);
    Mat4f inv_vp = (proj * view).inverse();
    Viewport vp(800.0f, 600.0f);

    Ray ray = screenToWorldRay(Vec2f(400.0f, 300.0f), inv_vp, vp, eye, GraphicsApi::eOpenGL);

    EXPECT_NEAR(ray.origin().x(), eye.x(), kEps);
    EXPECT_NEAR(ray.origin().y(), eye.y(), kEps);
    EXPECT_NEAR(ray.origin().z(), eye.z(), kEps);
}

TEST_F(ProjectionUtilsTest, ScreenToWorldRay_CenterPointsAtTarget) {
    // A ray through screen center should point toward the camera target
    Vec3f eye(0.0f, 0.0f, 5.0f);
    Vec3f target(0.0f, 0.0f, 0.0f);
    Mat4f view = Mat4f::lookAt(eye, target, Vec3f::yAxis(), GraphicsApi::eOpenGL);
    Mat4f proj = Mat4f::perspective(degToRad(60.0f), 800.0f / 600.0f, 0.1f, 100.0f, GraphicsApi::eOpenGL);
    Mat4f inv_vp = (proj * view).inverse();
    Viewport vp(800.0f, 600.0f);

    // Center pixel
    Ray ray = screenToWorldRay(Vec2f(400.0f, 300.0f), inv_vp, vp, eye, GraphicsApi::eOpenGL);

    // Direction should be (0,0,-1) — pointing from camera toward origin
    EXPECT_NEAR(ray.direction().x(), 0.0f, kEps);
    EXPECT_NEAR(ray.direction().y(), 0.0f, kEps);
    EXPECT_NEAR(ray.direction().z(), -1.0f, kEps);
}

}  // namespace vne::math

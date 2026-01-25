/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Example: Multi-Backend Projection
 * Demonstrates creating projection matrices for different graphics APIs
 * ----------------------------------------------------------------------
 */

#include "common/logging_guard.h"

#include <vertexnova/math/core/core.h>

#include <string>

using namespace vne::math;
using vne::math::examples::LoggingGuard_C;

const char* apiName(GraphicsApi api) {
    switch (api) {
        case GraphicsApi::eOpenGL: return "OpenGL";
        case GraphicsApi::eVulkan: return "Vulkan";
        case GraphicsApi::eMetal: return "Metal";
        case GraphicsApi::eDirectX: return "DirectX";
        case GraphicsApi::eWebGPU: return "WebGPU";
        default: return "Unknown";
    }
}

void printApiInfo(GraphicsApi api) {
    VNE_LOG_INFO << "  Depth Range: "
                 << (getClipSpaceDepth(api) == ClipSpaceDepth::eZeroToOne ? "[0, 1]" : "[-1, 1]");
    VNE_LOG_INFO << "  Handedness: "
                 << (getHandedness(api) == Handedness::eLeft ? "Left-handed" : "Right-handed");
    VNE_LOG_INFO << "  Y-Flip: " << (needsYFlip(api) ? "Yes" : "No");
}

void demonstratePerspectiveMatrices() {
    VNE_LOG_INFO << "=== Perspective Projection Matrices ===";

    // Common parameters
    float fov = degToRad(60.0f);
    float aspect = 16.0f / 9.0f;
    float z_near = 0.1f;
    float z_far = 1000.0f;

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Parameters:";
    VNE_LOG_INFO << "  FOV: 60 degrees";
    VNE_LOG_INFO << "  Aspect: 16:9";
    VNE_LOG_INFO << "  Near: " << z_near;
    VNE_LOG_INFO << "  Far: " << z_far;

    // Generate perspective matrix for each API
    GraphicsApi apis[] = {GraphicsApi::eOpenGL, GraphicsApi::eVulkan, GraphicsApi::eMetal,
                          GraphicsApi::eDirectX, GraphicsApi::eWebGPU};

    for (GraphicsApi api : apis) {
        VNE_LOG_INFO << "";
        VNE_LOG_INFO << "--- " << apiName(api) << " ---";
        printApiInfo(api);

        Mat4f proj = Mat4f::perspective(fov, aspect, z_near, z_far, api);
        VNE_LOG_INFO << "  Perspective Matrix:";
        VNE_LOG_INFO << proj;

        // Show key matrix elements
        VNE_LOG_INFO << "  Key values:";
        VNE_LOG_INFO << "    [0][0] (X scale): " << proj[0][0];
        VNE_LOG_INFO << "    [1][1] (Y scale): " << proj[1][1];
        VNE_LOG_INFO << "    [2][2] (Z mapping): " << proj[2][2];
        VNE_LOG_INFO << "    [2][3] (W component): " << proj[2][3];
    }
}

void demonstrateOrthographicMatrices() {
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Orthographic Projection Matrices ===";

    // Common parameters for a 2D UI or side-scroller
    float left = 0.0f;
    float right = 1920.0f;
    float bottom = 0.0f;
    float top = 1080.0f;
    float z_near = -1.0f;
    float z_far = 1.0f;

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Parameters (1080p screen):";
    VNE_LOG_INFO << "  Left: " << left << ", Right: " << right;
    VNE_LOG_INFO << "  Bottom: " << bottom << ", Top: " << top;
    VNE_LOG_INFO << "  Near: " << z_near << ", Far: " << z_far;

    // Compare OpenGL and Vulkan orthographic matrices
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "--- OpenGL Orthographic ---";
    Mat4f orthoGL = Mat4f::ortho(left, right, bottom, top, z_near, z_far, GraphicsApi::eOpenGL);
    VNE_LOG_INFO << orthoGL;

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "--- Vulkan Orthographic ---";
    Mat4f orthoVK = Mat4f::ortho(left, right, bottom, top, z_near, z_far, GraphicsApi::eVulkan);
    VNE_LOG_INFO << orthoVK;

    // Transform a screen point
    Vec4f screenPoint(960.0f, 540.0f, 0.0f, 1.0f);  // Center of screen
    Vec4f ndcGL = orthoGL * screenPoint;
    Vec4f ndcVK = orthoVK * screenPoint;

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Screen center (960, 540) in NDC:";
    VNE_LOG_INFO << "  OpenGL: " << ndcGL;
    VNE_LOG_INFO << "  Vulkan: " << ndcVK;
}

void demonstrateViewMatrix() {
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== View Matrix (Camera) ===";

    // Camera setup
    Vec3f eye(0.0f, 5.0f, 10.0f);    // Camera position
    Vec3f target(0.0f, 0.0f, 0.0f);  // Look at origin
    Vec3f up = Vec3f::yAxis();       // Y-up world

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Camera Setup:";
    VNE_LOG_INFO << "  Eye: " << eye;
    VNE_LOG_INFO << "  Target: " << target;
    VNE_LOG_INFO << "  Up: " << up;

    // Create view matrices for different APIs
    Mat4f viewGL = Mat4f::lookAt(eye, target, up, GraphicsApi::eOpenGL);
    Mat4f viewVK = Mat4f::lookAt(eye, target, up, GraphicsApi::eVulkan);

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "--- OpenGL View Matrix ---";
    VNE_LOG_INFO << viewGL;

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "--- Vulkan View Matrix ---";
    VNE_LOG_INFO << viewVK;

    // Transform world origin to view space
    Vec3f worldOrigin(0.0f, 0.0f, 0.0f);
    Vec3f viewSpaceGL = viewGL.transformPoint(worldOrigin);
    Vec3f viewSpaceVK = viewVK.transformPoint(worldOrigin);

    VNE_LOG_INFO << "World origin in view space:";
    VNE_LOG_INFO << "  OpenGL: " << viewSpaceGL;
    VNE_LOG_INFO << "  Vulkan: " << viewSpaceVK;
}

void demonstrateMVP() {
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Complete MVP Pipeline ===";

    // Model transform: cube at (5, 0, -5), rotated 45 degrees
    Vec3f position(5.0f, 0.0f, -5.0f);
    Quatf rotation = Quatf::fromAxisAngle(Vec3f::yAxis(), degToRad(45.0f));
    Vec3f scale(1.0f, 1.0f, 1.0f);

    Mat4f model = modelMatrix(position, rotation, scale);

    // View: camera at (0, 5, 10) looking at origin
    Vec3f eye(0.0f, 5.0f, 10.0f);
    Vec3f target(0.0f, 0.0f, 0.0f);
    Mat4f view = Mat4f::lookAt(eye, target, Vec3f::yAxis(), GraphicsApi::eVulkan);

    // Projection: 60 degree FOV, 16:9
    float fov = degToRad(60.0f);
    float aspect = 16.0f / 9.0f;
    Mat4f proj = Mat4f::perspective(fov, aspect, 0.1f, 1000.0f, GraphicsApi::eVulkan);

    // Combine into MVP
    Mat4f mvpMatrix = mvp(model, view, proj);

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Model Matrix:";
    VNE_LOG_INFO << model;

    VNE_LOG_INFO << "View Matrix:";
    VNE_LOG_INFO << view;

    VNE_LOG_INFO << "Projection Matrix:";
    VNE_LOG_INFO << proj;

    VNE_LOG_INFO << "MVP Matrix:";
    VNE_LOG_INFO << mvpMatrix;

    // Transform a vertex through the pipeline
    Vec4f localVertex(0.0f, 1.0f, 0.0f, 1.0f);  // Top of unit cube
    Vec4f clipSpace = mvpMatrix * localVertex;
    Vec3f ndc(clipSpace.x() / clipSpace.w(), clipSpace.y() / clipSpace.w(),
              clipSpace.z() / clipSpace.w());

    VNE_LOG_INFO << "Vertex transformation:";
    VNE_LOG_INFO << "  Local: " << localVertex;
    VNE_LOG_INFO << "  Clip space: " << clipSpace;
    VNE_LOG_INFO << "  NDC: " << ndc;
}

void demonstrateApiSwitching() {
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Runtime API Switching ===";

    // Simulate runtime graphics API selection
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Simulating runtime API selection...";

    auto renderScene = [](GraphicsApi api) {
        float fov = degToRad(60.0f);
        float aspect = 16.0f / 9.0f;

        Vec3f eye(0.0f, 5.0f, 10.0f);
        Vec3f target(0.0f, 0.0f, 0.0f);

        // Matrices automatically adapt to the target API
        Mat4f view = Mat4f::lookAt(eye, target, Vec3f::yAxis(), api);
        Mat4f proj = Mat4f::perspective(fov, aspect, 0.1f, 1000.0f, api);
        Mat4f vp = viewProjection(view, proj);

        VNE_LOG_INFO << "  Rendering for " << apiName(api);
        VNE_LOG_INFO << "    VP[1][1]: " << vp[1][1] << (vp[1][1] < 0 ? " (Y-flipped)" : " (Y-up)");
    };

    // The same code works for any API
    renderScene(GraphicsApi::eOpenGL);
    renderScene(GraphicsApi::eVulkan);
    renderScene(GraphicsApi::eMetal);
    renderScene(GraphicsApi::eDirectX);
    renderScene(GraphicsApi::eWebGPU);
}

int main() {
    LoggingGuard_C logging_guard;

    VNE_LOG_INFO << "VneMath Example: Multi-Backend Projection";
    VNE_LOG_INFO << "==========================================";
    VNE_LOG_INFO << "";

    demonstratePerspectiveMatrices();
    demonstrateOrthographicMatrices();
    demonstrateViewMatrix();
    demonstrateMVP();
    demonstrateApiSwitching();

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Done ===";
    return 0;
}

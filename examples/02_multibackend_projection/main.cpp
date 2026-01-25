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

#include <iostream>
#include <iomanip>
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
    std::cout << "  Depth Range: "
              << (getClipSpaceDepth(api) == ClipSpaceDepth::eZeroToOne ? "[0, 1]" : "[-1, 1]")
              << std::endl;
    std::cout << "  Handedness: "
              << (getHandedness(api) == Handedness::eLeft ? "Left-handed" : "Right-handed")
              << std::endl;
    std::cout << "  Y-Flip: " << (needsYFlip(api) ? "Yes" : "No") << std::endl;
}

void demonstratePerspectiveMatrices() {
    std::cout << "=== Perspective Projection Matrices ===" << std::endl;

    // Common parameters
    float fov = degToRad(60.0f);
    float aspect = 16.0f / 9.0f;
    float z_near = 0.1f;
    float z_far = 1000.0f;

    std::cout << "\nParameters:" << std::endl;
    std::cout << "  FOV: 60 degrees" << std::endl;
    std::cout << "  Aspect: 16:9" << std::endl;
    std::cout << "  Near: " << z_near << std::endl;
    std::cout << "  Far: " << z_far << std::endl;

    // Generate perspective matrix for each API
    GraphicsApi apis[] = {
        GraphicsApi::eOpenGL,
        GraphicsApi::eVulkan,
        GraphicsApi::eMetal,
        GraphicsApi::eDirectX,
        GraphicsApi::eWebGPU
    };

    for (GraphicsApi api : apis) {
        std::cout << "\n--- " << apiName(api) << " ---" << std::endl;
        printApiInfo(api);

        Mat4f proj = Mat4f::perspective(fov, aspect, z_near, z_far, api);
        std::cout << "  Perspective Matrix:" << std::endl;
        std::cout << proj << std::endl;

        // Show key matrix elements
        std::cout << "  Key values:" << std::endl;
        std::cout << "    [0][0] (X scale): " << proj[0][0] << std::endl;
        std::cout << "    [1][1] (Y scale): " << proj[1][1] << std::endl;
        std::cout << "    [2][2] (Z mapping): " << proj[2][2] << std::endl;
        std::cout << "    [2][3] (W component): " << proj[2][3] << std::endl;
    }
}

void demonstrateOrthographicMatrices() {
    std::cout << "\n=== Orthographic Projection Matrices ===" << std::endl;

    // Common parameters for a 2D UI or side-scroller
    float left = 0.0f;
    float right = 1920.0f;
    float bottom = 0.0f;
    float top = 1080.0f;
    float z_near = -1.0f;
    float z_far = 1.0f;

    std::cout << "\nParameters (1080p screen):" << std::endl;
    std::cout << "  Left: " << left << ", Right: " << right << std::endl;
    std::cout << "  Bottom: " << bottom << ", Top: " << top << std::endl;
    std::cout << "  Near: " << z_near << ", Far: " << z_far << std::endl;

    // Compare OpenGL and Vulkan orthographic matrices
    std::cout << "\n--- OpenGL Orthographic ---" << std::endl;
    Mat4f orthoGL = Mat4f::ortho(left, right, bottom, top, z_near, z_far, GraphicsApi::eOpenGL);
    std::cout << orthoGL << std::endl;

    std::cout << "\n--- Vulkan Orthographic ---" << std::endl;
    Mat4f orthoVK = Mat4f::ortho(left, right, bottom, top, z_near, z_far, GraphicsApi::eVulkan);
    std::cout << orthoVK << std::endl;

    // Transform a screen point
    Vec4f screenPoint(960.0f, 540.0f, 0.0f, 1.0f);  // Center of screen
    Vec4f ndcGL = orthoGL * screenPoint;
    Vec4f ndcVK = orthoVK * screenPoint;

    std::cout << "\nScreen center (960, 540) in NDC:" << std::endl;
    std::cout << "  OpenGL: " << ndcGL << std::endl;
    std::cout << "  Vulkan: " << ndcVK << std::endl;
}

void demonstrateViewMatrix() {
    std::cout << "\n=== View Matrix (Camera) ===" << std::endl;

    // Camera setup
    Vec3f eye(0.0f, 5.0f, 10.0f);     // Camera position
    Vec3f target(0.0f, 0.0f, 0.0f);   // Look at origin
    Vec3f up = Vec3f::yAxis();         // Y-up world

    std::cout << "\nCamera Setup:" << std::endl;
    std::cout << "  Eye: " << eye << std::endl;
    std::cout << "  Target: " << target << std::endl;
    std::cout << "  Up: " << up << std::endl;

    // Create view matrices for different APIs
    Mat4f viewGL = Mat4f::lookAt(eye, target, up, GraphicsApi::eOpenGL);
    Mat4f viewVK = Mat4f::lookAt(eye, target, up, GraphicsApi::eVulkan);

    std::cout << "\n--- OpenGL View Matrix ---" << std::endl;
    std::cout << viewGL << std::endl;

    std::cout << "\n--- Vulkan View Matrix ---" << std::endl;
    std::cout << viewVK << std::endl;

    // Transform world origin to view space
    Vec3f worldOrigin(0.0f, 0.0f, 0.0f);
    Vec3f viewSpaceGL = viewGL.transformPoint(worldOrigin);
    Vec3f viewSpaceVK = viewVK.transformPoint(worldOrigin);

    std::cout << "World origin in view space:" << std::endl;
    std::cout << "  OpenGL: " << viewSpaceGL << std::endl;
    std::cout << "  Vulkan: " << viewSpaceVK << std::endl;
}

void demonstrateMVP() {
    std::cout << "\n=== Complete MVP Pipeline ===" << std::endl;

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

    std::cout << "\nModel Matrix:" << std::endl;
    std::cout << model << std::endl;

    std::cout << "View Matrix:" << std::endl;
    std::cout << view << std::endl;

    std::cout << "Projection Matrix:" << std::endl;
    std::cout << proj << std::endl;

    std::cout << "MVP Matrix:" << std::endl;
    std::cout << mvpMatrix << std::endl;

    // Transform a vertex through the pipeline
    Vec4f localVertex(0.0f, 1.0f, 0.0f, 1.0f);  // Top of unit cube
    Vec4f clipSpace = mvpMatrix * localVertex;
    Vec3f ndc(clipSpace.x() / clipSpace.w(),
              clipSpace.y() / clipSpace.w(),
              clipSpace.z() / clipSpace.w());

    std::cout << "Vertex transformation:" << std::endl;
    std::cout << "  Local: " << localVertex << std::endl;
    std::cout << "  Clip space: " << clipSpace << std::endl;
    std::cout << "  NDC: " << ndc << std::endl;
}

void demonstrateApiSwitching() {
    std::cout << "\n=== Runtime API Switching ===" << std::endl;

    // Simulate runtime graphics API selection
    std::cout << "\nSimulating runtime API selection..." << std::endl;

    auto renderScene = [](GraphicsApi api) {
        float fov = degToRad(60.0f);
        float aspect = 16.0f / 9.0f;

        Vec3f eye(0.0f, 5.0f, 10.0f);
        Vec3f target(0.0f, 0.0f, 0.0f);

        // Matrices automatically adapt to the target API
        Mat4f view = Mat4f::lookAt(eye, target, Vec3f::yAxis(), api);
        Mat4f proj = Mat4f::perspective(fov, aspect, 0.1f, 1000.0f, api);
        Mat4f vp = viewProjection(view, proj);

        std::cout << "  Rendering for " << apiName(api) << std::endl;
        std::cout << "    VP[1][1]: " << vp[1][1]
                  << (vp[1][1] < 0 ? " (Y-flipped)" : " (Y-up)") << std::endl;
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

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "VneMath Example: Multi-Backend Projection" << std::endl;
    std::cout << "==========================================\n" << std::endl;

    demonstratePerspectiveMatrices();
    demonstrateOrthographicMatrices();
    demonstrateViewMatrix();
    demonstrateMVP();
    demonstrateApiSwitching();

    std::cout << "\n=== Done ===" << std::endl;
    return 0;
}

/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Example: Frustum Culling
 * Demonstrates visibility testing with geometry primitives
 * ----------------------------------------------------------------------
 */

#include "common/logging_guard.h"

#include <vertexnova/math/core/core.h>
#include <vertexnova/math/geometry/geometry.h>

#include <vector>

using namespace vne::math;
using vne::math::examples::LoggingGuard_C;

void demonstrateFrustumCreation() {
    VNE_LOG_INFO << "=== Frustum Creation ===";

    // Create camera matrices
    Vec3f eye(0.0f, 5.0f, 10.0f);
    Vec3f target(0.0f, 0.0f, 0.0f);
    Vec3f up = Vec3f::yAxis();

    Mat4f view = Mat4f::lookAt(eye, target, up, GraphicsApi::eVulkan);
    Mat4f proj = Mat4f::perspective(degToRad(60.0f), 16.0f / 9.0f, 0.1f, 100.0f, GraphicsApi::eVulkan);

    // Combine into view-projection matrix
    Mat4f vp = viewProjection(view, proj);

    // Extract frustum planes
    Frustum frustum;
    frustum.extractFromMatrix(vp);

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Camera setup:";
    VNE_LOG_INFO << "  Eye: " << eye;
    VNE_LOG_INFO << "  Target: " << target;
    VNE_LOG_INFO << "  FOV: 60 degrees";
    VNE_LOG_INFO << "  Near: 0.1, Far: 100";

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Frustum planes extracted successfully.";
    VNE_LOG_INFO << "  Left plane normal: " << frustum.leftPlane().normal;
    VNE_LOG_INFO << "  Right plane normal: " << frustum.rightPlane().normal;
    VNE_LOG_INFO << "  Top plane normal: " << frustum.topPlane().normal;
    VNE_LOG_INFO << "  Bottom plane normal: " << frustum.bottomPlane().normal;
    VNE_LOG_INFO << "  Near plane normal: " << frustum.nearPlane().normal;
    VNE_LOG_INFO << "  Far plane normal: " << frustum.farPlane().normal;
}

void demonstratePointTesting() {
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Point Testing ===";

    // Create a frustum looking down -Z axis
    Vec3f eye(0.0f, 0.0f, 0.0f);
    Vec3f target(0.0f, 0.0f, -10.0f);
    Vec3f up = Vec3f::yAxis();

    Mat4f view = Mat4f::lookAt(eye, target, up, GraphicsApi::eVulkan);
    Mat4f proj = Mat4f::perspective(degToRad(60.0f), 1.0f, 1.0f, 100.0f, GraphicsApi::eVulkan);
    Mat4f vp = viewProjection(view, proj);

    Frustum frustum;
    frustum.extractFromMatrix(vp);

    // Test various points
    std::vector<std::pair<std::string, Vec3f>> points = {
        {"In front of camera (inside)", Vec3f(0.0f, 0.0f, -10.0f)},
        {"Behind camera (outside)", Vec3f(0.0f, 0.0f, 10.0f)},
        {"Far left (outside)", Vec3f(-100.0f, 0.0f, -10.0f)},
        {"Near plane (inside)", Vec3f(0.0f, 0.0f, -2.0f)},
        {"Beyond far plane (outside)", Vec3f(0.0f, 0.0f, -150.0f)},
        {"Origin (behind near)", Vec3f(0.0f, 0.0f, 0.0f)},
    };

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Testing points (camera at origin looking -Z):";
    for (const auto& [name, point] : points) {
        bool inside = frustum.contains(point);
        VNE_LOG_INFO << "  " << name << ": " << point << " -> " << (inside ? "INSIDE" : "OUTSIDE");
    }
}

void demonstrateSphereTesting() {
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Sphere Testing ===";

    // Create frustum
    Vec3f eye(0.0f, 0.0f, 0.0f);
    Vec3f target(0.0f, 0.0f, -10.0f);
    Mat4f view = Mat4f::lookAt(eye, target, Vec3f::yAxis(), GraphicsApi::eVulkan);
    Mat4f proj = Mat4f::perspective(degToRad(60.0f), 1.0f, 1.0f, 100.0f, GraphicsApi::eVulkan);
    Mat4f vp = viewProjection(view, proj);

    Frustum frustum;
    frustum.extractFromMatrix(vp);

    // Test various spheres
    std::vector<std::pair<std::string, Sphere>> spheres = {
        {"Fully inside", Sphere(Vec3f(0.0f, 0.0f, -20.0f), 2.0f)},
        {"Partially inside (intersects side)", Sphere(Vec3f(10.0f, 0.0f, -20.0f), 5.0f)},
        {"Fully outside", Sphere(Vec3f(100.0f, 0.0f, -20.0f), 2.0f)},
        {"Behind camera", Sphere(Vec3f(0.0f, 0.0f, 5.0f), 2.0f)},
        {"Intersects near plane", Sphere(Vec3f(0.0f, 0.0f, -1.0f), 1.5f)},
        {"Large sphere (contains frustum)", Sphere(Vec3f(0.0f, 0.0f, -50.0f), 200.0f)},
    };

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Testing spheres:";
    for (const auto& [name, sphere] : spheres) {
        bool intersects = frustum.intersects(sphere);
        bool fullyInside = frustum.containsFully(sphere);

        std::string status;
        if (fullyInside) {
            status = "FULLY INSIDE";
        } else if (intersects) {
            status = "INTERSECTS";
        } else {
            status = "OUTSIDE";
        }

        VNE_LOG_INFO << "  " << name << ": center=" << sphere.center() << " r=" << sphere.radius()
                     << " -> " << status;
    }
}

void demonstrateAABBTesting() {
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== AABB Testing ===";

    // Create frustum
    Vec3f eye(0.0f, 0.0f, 0.0f);
    Vec3f target(0.0f, 0.0f, -10.0f);
    Mat4f view = Mat4f::lookAt(eye, target, Vec3f::yAxis(), GraphicsApi::eVulkan);
    Mat4f proj = Mat4f::perspective(degToRad(60.0f), 1.0f, 1.0f, 100.0f, GraphicsApi::eVulkan);
    Mat4f vp = viewProjection(view, proj);

    Frustum frustum;
    frustum.extractFromMatrix(vp);

    // Test various AABBs
    std::vector<std::pair<std::string, Aabb>> boxes = {
        {"Fully inside", Aabb(Vec3f(-1.0f, -1.0f, -21.0f), Vec3f(1.0f, 1.0f, -19.0f))},
        {"Partially inside", Aabb(Vec3f(8.0f, -1.0f, -21.0f), Vec3f(12.0f, 1.0f, -19.0f))},
        {"Fully outside (right)", Aabb(Vec3f(50.0f, -1.0f, -21.0f), Vec3f(52.0f, 1.0f, -19.0f))},
        {"Fully outside (behind)", Aabb(Vec3f(-1.0f, -1.0f, 1.0f), Vec3f(1.0f, 1.0f, 3.0f))},
        {"Straddles near plane", Aabb(Vec3f(-1.0f, -1.0f, -2.0f), Vec3f(1.0f, 1.0f, 0.0f))},
        {"Large box (contains camera)", Aabb(Vec3f(-50.0f, -50.0f, -100.0f), Vec3f(50.0f, 50.0f, 50.0f))},
    };

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Testing AABBs:";
    for (const auto& [name, aabb] : boxes) {
        bool intersects = frustum.intersects(aabb);
        bool fullyInside = frustum.containsFully(aabb);

        std::string status;
        if (fullyInside) {
            status = "FULLY INSIDE";
        } else if (intersects) {
            status = "INTERSECTS";
        } else {
            status = "OUTSIDE";
        }

        VNE_LOG_INFO << "  " << name << ":";
        VNE_LOG_INFO << "    min=" << aabb.min() << " max=" << aabb.max() << " -> " << status;
    }
}

void demonstratePracticalCulling() {
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Practical Culling Example ===";

    // Simulate a scene with many objects
    struct SceneObject {
        std::string name;
        Aabb bounds;
    };

    std::vector<SceneObject> scene = {
        {"Tree_1", Aabb(Vec3f(-2.0f, 0.0f, -15.0f), Vec3f(-1.0f, 5.0f, -14.0f))},
        {"Tree_2", Aabb(Vec3f(3.0f, 0.0f, -20.0f), Vec3f(4.0f, 5.0f, -19.0f))},
        {"Rock_1", Aabb(Vec3f(-5.0f, 0.0f, -10.0f), Vec3f(-4.0f, 1.0f, -9.0f))},
        {"House", Aabb(Vec3f(0.0f, 0.0f, -30.0f), Vec3f(5.0f, 4.0f, -25.0f))},
        {"Enemy_behind", Aabb(Vec3f(-1.0f, 0.0f, 5.0f), Vec3f(1.0f, 2.0f, 7.0f))},
        {"Distant_mountain", Aabb(Vec3f(-20.0f, 0.0f, -200.0f), Vec3f(20.0f, 50.0f, -150.0f))},
        {"Far_left_tree", Aabb(Vec3f(-100.0f, 0.0f, -15.0f), Vec3f(-99.0f, 5.0f, -14.0f))},
    };

    // Create frustum from camera
    Vec3f eye(0.0f, 2.0f, 0.0f);
    Vec3f target(0.0f, 0.0f, -10.0f);
    Mat4f view = Mat4f::lookAt(eye, target, Vec3f::yAxis(), GraphicsApi::eVulkan);
    Mat4f proj = Mat4f::perspective(degToRad(60.0f), 16.0f / 9.0f, 0.5f, 100.0f, GraphicsApi::eVulkan);
    Mat4f vp = viewProjection(view, proj);

    Frustum frustum;
    frustum.extractFromMatrix(vp);

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Scene has " << scene.size() << " objects.";
    VNE_LOG_INFO << "Camera at " << eye << " looking at " << target;
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Culling results:";

    int visible_count = 0;
    int culled_count = 0;

    for (const auto& obj : scene) {
        if (frustum.intersects(obj.bounds)) {
            VNE_LOG_INFO << "  [VISIBLE] " << obj.name;
            visible_count++;
        } else {
            VNE_LOG_INFO << "  [CULLED]  " << obj.name;
            culled_count++;
        }
    }

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Summary:";
    VNE_LOG_INFO << "  Visible: " << visible_count;
    VNE_LOG_INFO << "  Culled: " << culled_count;
    VNE_LOG_INFO << "  Draw call reduction: " << (culled_count * 100 / static_cast<int>(scene.size())) << "%";
}

int main() {
    LoggingGuard_C logging_guard;

    VNE_LOG_INFO << "VneMath Example: Frustum Culling";
    VNE_LOG_INFO << "=================================";
    VNE_LOG_INFO << "";

    demonstrateFrustumCreation();
    demonstratePointTesting();
    demonstrateSphereTesting();
    demonstrateAABBTesting();
    demonstratePracticalCulling();

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Done ===";
    return 0;
}

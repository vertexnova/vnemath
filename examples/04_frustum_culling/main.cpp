/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Example: Frustum Culling
 * Demonstrates visibility testing with geometry primitives
 * ----------------------------------------------------------------------
 */

#include <vertexnova/math/core/core.h>
#include <vertexnova/math/geometry/geometry.h>

#include <iostream>
#include <iomanip>
#include <vector>

using namespace vne::math;

void demonstrateFrustumCreation() {
    std::cout << "=== Frustum Creation ===" << std::endl;

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

    std::cout << "\nCamera setup:" << std::endl;
    std::cout << "  Eye: " << eye << std::endl;
    std::cout << "  Target: " << target << std::endl;
    std::cout << "  FOV: 60 degrees" << std::endl;
    std::cout << "  Near: 0.1, Far: 100" << std::endl;

    std::cout << "\nFrustum planes extracted successfully." << std::endl;
    std::cout << "  Left plane normal: " << frustum.leftPlane().normal << std::endl;
    std::cout << "  Right plane normal: " << frustum.rightPlane().normal << std::endl;
    std::cout << "  Top plane normal: " << frustum.topPlane().normal << std::endl;
    std::cout << "  Bottom plane normal: " << frustum.bottomPlane().normal << std::endl;
    std::cout << "  Near plane normal: " << frustum.nearPlane().normal << std::endl;
    std::cout << "  Far plane normal: " << frustum.farPlane().normal << std::endl;
}

void demonstratePointTesting() {
    std::cout << "\n=== Point Testing ===" << std::endl;

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

    std::cout << "\nTesting points (camera at origin looking -Z):" << std::endl;
    for (const auto& [name, point] : points) {
        bool inside = frustum.contains(point);
        std::cout << "  " << name << ": " << point
                  << " -> " << (inside ? "INSIDE" : "OUTSIDE") << std::endl;
    }
}

void demonstrateSphereTesting() {
    std::cout << "\n=== Sphere Testing ===" << std::endl;

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

    std::cout << "\nTesting spheres:" << std::endl;
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

        std::cout << "  " << name << ": center=" << sphere.center()
                  << " r=" << sphere.radius() << " -> " << status << std::endl;
    }
}

void demonstrateAABBTesting() {
    std::cout << "\n=== AABB Testing ===" << std::endl;

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

    std::cout << "\nTesting AABBs:" << std::endl;
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

        std::cout << "  " << name << ":" << std::endl;
        std::cout << "    min=" << aabb.min() << " max=" << aabb.max()
                  << " -> " << status << std::endl;
    }
}

void demonstratePracticalCulling() {
    std::cout << "\n=== Practical Culling Example ===" << std::endl;

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

    std::cout << "\nScene has " << scene.size() << " objects." << std::endl;
    std::cout << "Camera at " << eye << " looking at " << target << std::endl;
    std::cout << "\nCulling results:" << std::endl;

    int visible_count = 0;
    int culled_count = 0;

    for (const auto& obj : scene) {
        if (frustum.intersects(obj.bounds)) {
            std::cout << "  [VISIBLE] " << obj.name << std::endl;
            visible_count++;
        } else {
            std::cout << "  [CULLED]  " << obj.name << std::endl;
            culled_count++;
        }
    }

    std::cout << "\nSummary:" << std::endl;
    std::cout << "  Visible: " << visible_count << std::endl;
    std::cout << "  Culled: " << culled_count << std::endl;
    std::cout << "  Draw call reduction: "
              << (culled_count * 100 / static_cast<int>(scene.size())) << "%" << std::endl;
}

int main() {
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "VneMath Example: Frustum Culling" << std::endl;
    std::cout << "=================================\n" << std::endl;

    demonstrateFrustumCreation();
    demonstratePointTesting();
    demonstrateSphereTesting();
    demonstrateAABBTesting();
    demonstratePracticalCulling();

    std::cout << "\n=== Done ===" << std::endl;
    return 0;
}

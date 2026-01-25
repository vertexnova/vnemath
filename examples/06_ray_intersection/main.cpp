/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Example: Ray Intersection
 * Demonstrates ray casting against geometry primitives
 * ----------------------------------------------------------------------
 */

#include "common/logging_guard.h"

#include <vertexnova/math/core/core.h>
#include <vertexnova/math/geometry/geometry.h>

#include <iostream>
#include <iomanip>
#include <vector>
#include <optional>

using namespace vne::math;
using vne::math::examples::LoggingGuard_C;

void demonstrateRayBasics() {
    std::cout << "=== Ray Basics ===" << std::endl;

    // Create a ray from origin pointing down -Z axis
    Vec3f origin(0.0f, 0.0f, 0.0f);
    Vec3f direction(0.0f, 0.0f, -1.0f);

    Ray ray(origin, direction);

    std::cout << "\nRay:" << std::endl;
    std::cout << "  Origin: " << ray.origin() << std::endl;
    std::cout << "  Direction: " << ray.direction() << std::endl;

    // Get points along the ray
    std::cout << "\nPoints along ray:" << std::endl;
    for (float t = 0.0f; t <= 10.0f; t += 2.5f) {
        Vec3f point = ray.getPoint(t);
        std::cout << "  t=" << t << ": " << point << std::endl;
    }

    // Closest point on ray to an external point
    Vec3f external_point(5.0f, 0.0f, -5.0f);
    Vec3f closest = ray.closestPoint(external_point);
    float distance = ray.distanceToPoint(external_point);

    std::cout << "\nClosest point to " << external_point << ":" << std::endl;
    std::cout << "  Closest on ray: " << closest << std::endl;
    std::cout << "  Distance: " << distance << std::endl;
}

void demonstrateRayPlaneIntersection() {
    std::cout << "\n=== Ray-Plane Intersection ===" << std::endl;

    // Create a ground plane (Y = 0)
    Plane ground(Vec3f::yAxis(), 0.0f);

    // Ray pointing downward from above
    Ray ray_down(Vec3f(0.0f, 10.0f, 0.0f), Vec3f(0.0f, -1.0f, 0.0f));

    std::cout << "\nGround plane: Y = 0 (normal pointing up)" << std::endl;
    std::cout << "Ray: origin=(0, 10, 0), direction=(0, -1, 0)" << std::endl;

    // Calculate intersection manually (plane.signedDistance gives distance to plane)
    float ray_t = -ground.signedDistance(ray_down.origin()) / ground.normal.dot(ray_down.direction());
    if (ray_t >= 0) {
        Vec3f hit_point = ray_down.getPoint(ray_t);
        std::cout << "  Intersection at t=" << ray_t << ": " << hit_point << std::endl;
    }

    // Ray parallel to plane (no intersection)
    Ray ray_parallel(Vec3f(0.0f, 5.0f, 0.0f), Vec3f(1.0f, 0.0f, 0.0f));
    float denom = ground.normal.dot(ray_parallel.direction());
    std::cout << "\nRay parallel to plane: origin=(0, 5, 0), direction=(1, 0, 0)" << std::endl;
    std::cout << "  Dot product with normal: " << denom << std::endl;
    if (approxEqual(denom, 0.0f, 0.0001f)) {
        std::cout << "  No intersection (ray parallel to plane)" << std::endl;
    }

    // Ray pointing away from plane
    Ray ray_away(Vec3f(0.0f, 10.0f, 0.0f), Vec3f(0.0f, 1.0f, 0.0f));
    ray_t = -ground.signedDistance(ray_away.origin()) / ground.normal.dot(ray_away.direction());
    std::cout << "\nRay pointing away: origin=(0, 10, 0), direction=(0, 1, 0)" << std::endl;
    std::cout << "  t=" << ray_t << " (negative means intersection behind ray origin)" << std::endl;
}

void demonstrateRaySphereIntersection() {
    std::cout << "\n=== Ray-Sphere Intersection ===" << std::endl;

    Sphere sphere(Vec3f(0.0f, 0.0f, -10.0f), 2.0f);
    std::cout << "\nSphere: center=" << sphere.center() << ", radius=" << sphere.radius() << std::endl;

    // Ray that hits the sphere
    Ray ray_hit(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.0f, 0.0f, -1.0f));
    std::cout << "\nRay 1: origin=(0,0,0), direction=(0,0,-1)" << std::endl;

    // Solve quadratic for ray-sphere intersection
    // |ray.origin + t * ray.direction - sphere.center|^2 = radius^2
    Vec3f oc = ray_hit.origin() - sphere.center();
    float a = ray_hit.direction().dot(ray_hit.direction());
    float b = 2.0f * oc.dot(ray_hit.direction());
    float c = oc.dot(oc) - sphere.radius() * sphere.radius();
    float discriminant = b * b - 4 * a * c;

    if (discriminant >= 0) {
        float t1 = (-b - std::sqrt(discriminant)) / (2 * a);
        float t2 = (-b + std::sqrt(discriminant)) / (2 * a);
        std::cout << "  Entry point (t=" << t1 << "): " << ray_hit.getPoint(t1) << std::endl;
        std::cout << "  Exit point (t=" << t2 << "): " << ray_hit.getPoint(t2) << std::endl;
    }

    // Ray that misses the sphere
    Ray ray_miss(Vec3f(10.0f, 0.0f, 0.0f), Vec3f(0.0f, 0.0f, -1.0f));
    std::cout << "\nRay 2: origin=(10,0,0), direction=(0,0,-1)" << std::endl;

    oc = ray_miss.origin() - sphere.center();
    b = 2.0f * oc.dot(ray_miss.direction());
    c = oc.dot(oc) - sphere.radius() * sphere.radius();
    discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        std::cout << "  No intersection (ray misses sphere)" << std::endl;
        std::cout << "  Closest distance: " << ray_miss.distanceToPoint(sphere.center()) - sphere.radius() << std::endl;
    }
}

void demonstrateRayAABBIntersection() {
    std::cout << "\n=== Ray-AABB Intersection ===" << std::endl;

    Aabb box(Vec3f(-1.0f, -1.0f, -11.0f), Vec3f(1.0f, 1.0f, -9.0f));
    std::cout << "\nAABB: min=" << box.min() << ", max=" << box.max() << std::endl;
    std::cout << "      center=" << box.center() << ", size=" << box.size() << std::endl;

    // Ray that hits the box
    Ray ray(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.0f, 0.0f, -1.0f));
    std::cout << "\nRay: origin=(0,0,0), direction=(0,0,-1)" << std::endl;

    // Slab intersection algorithm
    Vec3f inv_dir(1.0f / ray.direction().x(),
                  1.0f / ray.direction().y(),
                  1.0f / ray.direction().z());

    float t1 = (box.min().x() - ray.origin().x()) * inv_dir.x();
    float t2 = (box.max().x() - ray.origin().x()) * inv_dir.x();
    float t3 = (box.min().y() - ray.origin().y()) * inv_dir.y();
    float t4 = (box.max().y() - ray.origin().y()) * inv_dir.y();
    float t5 = (box.min().z() - ray.origin().z()) * inv_dir.z();
    float t6 = (box.max().z() - ray.origin().z()) * inv_dir.z();

    float t_min = max(max(min(t1, t2), min(t3, t4)), min(t5, t6));
    float t_max = min(min(max(t1, t2), max(t3, t4)), max(t5, t6));

    if (t_max >= t_min && t_max >= 0) {
        float t_entry = t_min >= 0 ? t_min : t_max;
        std::cout << "  Hit! Entry at t=" << t_entry << ": " << ray.getPoint(t_entry) << std::endl;
        std::cout << "  Exit at t=" << t_max << ": " << ray.getPoint(t_max) << std::endl;
    } else {
        std::cout << "  Miss" << std::endl;
    }
}

void demonstrateMousePicking() {
    std::cout << "\n=== Mouse Picking Example ===" << std::endl;

    // Simulate screen-space mouse click to world ray conversion
    float screen_width = 1920.0f;
    float screen_height = 1080.0f;
    float mouse_x = 960.0f;   // Center of screen
    float mouse_y = 540.0f;

    // Camera setup
    Vec3f camera_pos(0.0f, 5.0f, 10.0f);
    Vec3f camera_target(0.0f, 0.0f, 0.0f);
    float fov = degToRad(60.0f);
    float aspect = screen_width / screen_height;

    Mat4f view = Mat4f::lookAt(camera_pos, camera_target, Vec3f::yAxis(), GraphicsApi::eVulkan);
    Mat4f proj = Mat4f::perspective(fov, aspect, 0.1f, 1000.0f, GraphicsApi::eVulkan);
    Mat4f vp_inverse = (proj * view).inverse();

    // Convert screen coordinates to NDC
    float ndc_x = (2.0f * mouse_x / screen_width) - 1.0f;
    float ndc_y = 1.0f - (2.0f * mouse_y / screen_height);  // Flip Y for Vulkan

    std::cout << "\nMouse position: (" << mouse_x << ", " << mouse_y << ")" << std::endl;
    std::cout << "NDC: (" << ndc_x << ", " << ndc_y << ")" << std::endl;

    // Unproject to world space (near and far planes)
    Vec4f near_ndc(ndc_x, ndc_y, 0.0f, 1.0f);  // Vulkan near plane is 0
    Vec4f far_ndc(ndc_x, ndc_y, 1.0f, 1.0f);

    Vec4f near_world = vp_inverse * near_ndc;
    Vec4f far_world = vp_inverse * far_ndc;

    near_world = near_world / near_world.w();
    far_world = far_world / far_world.w();

    Vec3f ray_origin(near_world.x(), near_world.y(), near_world.z());
    Vec3f ray_dir = Vec3f(far_world.x() - near_world.x(),
                          far_world.y() - near_world.y(),
                          far_world.z() - near_world.z()).normalized();

    Ray pick_ray(ray_origin, ray_dir);

    std::cout << "Pick ray origin: " << pick_ray.origin() << std::endl;
    std::cout << "Pick ray direction: " << pick_ray.direction() << std::endl;

    // Test against some scene objects
    std::vector<std::pair<std::string, Sphere>> objects = {
        {"Red Sphere", Sphere(Vec3f(0.0f, 0.0f, 0.0f), 1.0f)},
        {"Blue Sphere", Sphere(Vec3f(3.0f, 0.0f, 0.0f), 1.0f)},
        {"Green Sphere", Sphere(Vec3f(-3.0f, 0.0f, 0.0f), 1.0f)},
    };

    std::cout << "\nTesting against scene objects:" << std::endl;
    for (const auto& [name, sphere] : objects) {
        Vec3f oc = pick_ray.origin() - sphere.center();
        float a = pick_ray.direction().dot(pick_ray.direction());
        float b = 2.0f * oc.dot(pick_ray.direction());
        float c = oc.dot(oc) - sphere.radius() * sphere.radius();
        float discriminant = b * b - 4 * a * c;

        if (discriminant >= 0) {
            float t = (-b - std::sqrt(discriminant)) / (2 * a);
            if (t >= 0) {
                std::cout << "  [HIT] " << name << " at distance " << t << std::endl;
            } else {
                std::cout << "  [MISS] " << name << " (behind camera)" << std::endl;
            }
        } else {
            std::cout << "  [MISS] " << name << std::endl;
        }
    }
}

int main() {
    LoggingGuard_C logging_guard;

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "VneMath Example: Ray Intersection" << std::endl;
    std::cout << "==================================\n" << std::endl;

    demonstrateRayBasics();
    demonstrateRayPlaneIntersection();
    demonstrateRaySphereIntersection();
    demonstrateRayAABBIntersection();
    demonstrateMousePicking();

    std::cout << "\n=== Done ===" << std::endl;
    return 0;
}

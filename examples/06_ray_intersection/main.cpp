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

#include <vector>

using namespace vne::math;
using vne::math::examples::LoggingGuard_C;

void demonstrateRayBasics() {
    VNE_LOG_INFO << "=== Ray Basics ===";

    // Create a ray from origin pointing down -Z axis
    Vec3f origin(0.0f, 0.0f, 0.0f);
    Vec3f direction(0.0f, 0.0f, -1.0f);

    Ray ray(origin, direction);

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Ray:";
    VNE_LOG_INFO << "  Origin: " << ray.origin();
    VNE_LOG_INFO << "  Direction: " << ray.direction();

    // Get points along the ray
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Points along ray:";
    for (float t = 0.0f; t <= 10.0f; t += 2.5f) {
        Vec3f point = ray.getPoint(t);
        VNE_LOG_INFO << "  t=" << t << ": " << point;
    }

    // Closest point on ray to an external point
    Vec3f external_point(5.0f, 0.0f, -5.0f);
    Vec3f closest = ray.closestPoint(external_point);
    float distance = ray.distanceToPoint(external_point);

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Closest point to " << external_point << ":";
    VNE_LOG_INFO << "  Closest on ray: " << closest;
    VNE_LOG_INFO << "  Distance: " << distance;
}

void demonstrateRayPlaneIntersection() {
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Ray-Plane Intersection ===";

    // Create a ground plane (Y = 0)
    Plane ground(Vec3f::yAxis(), 0.0f);

    // Ray pointing downward from above
    Ray ray_down(Vec3f(0.0f, 10.0f, 0.0f), Vec3f(0.0f, -1.0f, 0.0f));

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Ground plane: Y = 0 (normal pointing up)";
    VNE_LOG_INFO << "Ray: origin=(0, 10, 0), direction=(0, -1, 0)";

    // Calculate intersection manually (plane.signedDistance gives distance to plane)
    float ray_t = -ground.signedDistance(ray_down.origin()) / ground.normal.dot(ray_down.direction());
    if (ray_t >= 0) {
        Vec3f hit_point = ray_down.getPoint(ray_t);
        VNE_LOG_INFO << "  Intersection at t=" << ray_t << ": " << hit_point;
    }

    // Ray parallel to plane (no intersection)
    Ray ray_parallel(Vec3f(0.0f, 5.0f, 0.0f), Vec3f(1.0f, 0.0f, 0.0f));
    float denom = ground.normal.dot(ray_parallel.direction());
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Ray parallel to plane: origin=(0, 5, 0), direction=(1, 0, 0)";
    VNE_LOG_INFO << "  Dot product with normal: " << denom;
    if (approxEqual(denom, 0.0f, 0.0001f)) {
        VNE_LOG_INFO << "  No intersection (ray parallel to plane)";
    }

    // Ray pointing away from plane
    Ray ray_away(Vec3f(0.0f, 10.0f, 0.0f), Vec3f(0.0f, 1.0f, 0.0f));
    ray_t = -ground.signedDistance(ray_away.origin()) / ground.normal.dot(ray_away.direction());
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Ray pointing away: origin=(0, 10, 0), direction=(0, 1, 0)";
    VNE_LOG_INFO << "  t=" << ray_t << " (negative means intersection behind ray origin)";
}

void demonstrateRaySphereIntersection() {
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Ray-Sphere Intersection ===";

    Sphere sphere(Vec3f(0.0f, 0.0f, -10.0f), 2.0f);
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Sphere: center=" << sphere.center() << ", radius=" << sphere.radius();

    // Ray that hits the sphere
    Ray ray_hit(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.0f, 0.0f, -1.0f));
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Ray 1: origin=(0,0,0), direction=(0,0,-1)";

    // Solve quadratic for ray-sphere intersection
    Vec3f oc = ray_hit.origin() - sphere.center();
    float a = ray_hit.direction().dot(ray_hit.direction());
    float b = 2.0f * oc.dot(ray_hit.direction());
    float c = oc.dot(oc) - sphere.radius() * sphere.radius();
    float discriminant = b * b - 4 * a * c;

    if (discriminant >= 0) {
        float t1 = (-b - std::sqrt(discriminant)) / (2 * a);
        float t2 = (-b + std::sqrt(discriminant)) / (2 * a);
        VNE_LOG_INFO << "  Entry point (t=" << t1 << "): " << ray_hit.getPoint(t1);
        VNE_LOG_INFO << "  Exit point (t=" << t2 << "): " << ray_hit.getPoint(t2);
    }

    // Ray that misses the sphere
    Ray ray_miss(Vec3f(10.0f, 0.0f, 0.0f), Vec3f(0.0f, 0.0f, -1.0f));
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Ray 2: origin=(10,0,0), direction=(0,0,-1)";

    oc = ray_miss.origin() - sphere.center();
    b = 2.0f * oc.dot(ray_miss.direction());
    c = oc.dot(oc) - sphere.radius() * sphere.radius();
    discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        VNE_LOG_INFO << "  No intersection (ray misses sphere)";
        VNE_LOG_INFO << "  Closest distance: " << ray_miss.distanceToPoint(sphere.center()) - sphere.radius();
    }
}

void demonstrateRayAABBIntersection() {
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Ray-AABB Intersection ===";

    Aabb box(Vec3f(-1.0f, -1.0f, -11.0f), Vec3f(1.0f, 1.0f, -9.0f));
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "AABB: min=" << box.min() << ", max=" << box.max();
    VNE_LOG_INFO << "      center=" << box.center() << ", size=" << box.size();

    // Ray that hits the box
    Ray ray(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.0f, 0.0f, -1.0f));
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Ray: origin=(0,0,0), direction=(0,0,-1)";

    // Slab intersection algorithm
    Vec3f inv_dir(1.0f / ray.direction().x(), 1.0f / ray.direction().y(), 1.0f / ray.direction().z());

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
        VNE_LOG_INFO << "  Hit! Entry at t=" << t_entry << ": " << ray.getPoint(t_entry);
        VNE_LOG_INFO << "  Exit at t=" << t_max << ": " << ray.getPoint(t_max);
    } else {
        VNE_LOG_INFO << "  Miss";
    }
}

void demonstrateMousePicking() {
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Mouse Picking Example ===";

    // Simulate screen-space mouse click to world ray conversion
    float screen_width = 1920.0f;
    float screen_height = 1080.0f;
    float mouse_x = 960.0f;  // Center of screen
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

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Mouse position: (" << mouse_x << ", " << mouse_y << ")";
    VNE_LOG_INFO << "NDC: (" << ndc_x << ", " << ndc_y << ")";

    // Unproject to world space (near and far planes)
    Vec4f near_ndc(ndc_x, ndc_y, 0.0f, 1.0f);  // Vulkan near plane is 0
    Vec4f far_ndc(ndc_x, ndc_y, 1.0f, 1.0f);

    Vec4f near_world = vp_inverse * near_ndc;
    Vec4f far_world = vp_inverse * far_ndc;

    near_world = near_world / near_world.w();
    far_world = far_world / far_world.w();

    Vec3f ray_origin(near_world.x(), near_world.y(), near_world.z());
    Vec3f ray_dir =
        Vec3f(far_world.x() - near_world.x(), far_world.y() - near_world.y(), far_world.z() - near_world.z())
            .normalized();

    Ray pick_ray(ray_origin, ray_dir);

    VNE_LOG_INFO << "Pick ray origin: " << pick_ray.origin();
    VNE_LOG_INFO << "Pick ray direction: " << pick_ray.direction();

    // Test against some scene objects
    std::vector<std::pair<std::string, Sphere>> objects = {
        {"Red Sphere", Sphere(Vec3f(0.0f, 0.0f, 0.0f), 1.0f)},
        {"Blue Sphere", Sphere(Vec3f(3.0f, 0.0f, 0.0f), 1.0f)},
        {"Green Sphere", Sphere(Vec3f(-3.0f, 0.0f, 0.0f), 1.0f)},
    };

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Testing against scene objects:";
    for (const auto& [name, sphere] : objects) {
        Vec3f oc = pick_ray.origin() - sphere.center();
        float a = pick_ray.direction().dot(pick_ray.direction());
        float b = 2.0f * oc.dot(pick_ray.direction());
        float c = oc.dot(oc) - sphere.radius() * sphere.radius();
        float discriminant = b * b - 4 * a * c;

        if (discriminant >= 0) {
            float t = (-b - std::sqrt(discriminant)) / (2 * a);
            if (t >= 0) {
                VNE_LOG_INFO << "  [HIT] " << name << " at distance " << t;
            } else {
                VNE_LOG_INFO << "  [MISS] " << name << " (behind camera)";
            }
        } else {
            VNE_LOG_INFO << "  [MISS] " << name;
        }
    }
}

int main() {
    LoggingGuard_C logging_guard;

    VNE_LOG_INFO << "VneMath Example: Ray Intersection";
    VNE_LOG_INFO << "==================================";
    VNE_LOG_INFO << "";

    demonstrateRayBasics();
    demonstrateRayPlaneIntersection();
    demonstrateRaySphereIntersection();
    demonstrateRayAABBIntersection();
    demonstrateMousePicking();

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Done ===";
    return 0;
}

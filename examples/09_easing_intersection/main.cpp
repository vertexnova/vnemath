/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Example: Easing Functions and Ray Intersection
 * Demonstrates high-performance easing functions (IQ-style) and ray casting.
 * ----------------------------------------------------------------------
 */

#include "common/logging_guard.h"

#include <vertexnova/math/core/core.h>
#include <vertexnova/math/core/math_utils.h>
#include <vertexnova/math/easing.h>
#include <vertexnova/math/geometry/intersection.h>
#include <vertexnova/math/projection_utils.h>

using namespace vne::math;
using vne::math::examples::LoggingGuard_C;

void demonstrateSmoothstep() {
    VNE_LOG_INFO << "=== Smoothstep Variants ===";
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Comparing different smoothstep implementations at x=0.25:";

    float x = 0.25f;
    VNE_LOG_INFO << "  Cubic (standard):  " << smoothstep(x);
    VNE_LOG_INFO << "  Quintic (smoother): " << smootherstep(x);
    VNE_LOG_INFO << "  Quartic:           " << smoothstepQuartic(x);
    VNE_LOG_INFO << "  Rational (n=2):    " << smoothstepRational(x, 2.0f);

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "All implementations:";
    VNE_LOG_INFO << "  - Map 0 to 0, 1 to 1";
    VNE_LOG_INFO << "  - Have zero derivative at edges (smooth transitions)";
    VNE_LOG_INFO << "  - Quintic also has zero second derivative (C2)";
}

void demonstrateEasingFunctions() {
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Easing Functions ===";
    VNE_LOG_INFO << "";

    // Show different easing types at t=0.3
    float t = 0.3f;
    VNE_LOG_INFO << "Comparing easing types at t=0.3:";
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "  Quadratic:";
    VNE_LOG_INFO << "    In:    " << easeInQuad(t) << " (slow start)";
    VNE_LOG_INFO << "    Out:   " << easeOutQuad(t) << " (fast start)";
    VNE_LOG_INFO << "    InOut: " << easeInOutQuad(t) << " (slow at both ends)";

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "  Cubic:";
    VNE_LOG_INFO << "    In:    " << easeInCubic(t);
    VNE_LOG_INFO << "    Out:   " << easeOutCubic(t);
    VNE_LOG_INFO << "    InOut: " << easeInOutCubic(t);

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "  Special effects:";
    VNE_LOG_INFO << "    Back In:     " << easeInBack(t) << " (undershoots)";
    VNE_LOG_INFO << "    Elastic Out: " << easeOutElastic(t) << " (bouncy)";
    VNE_LOG_INFO << "    Bounce Out:  " << easeOutBounce(t) << " (ball bounce)";

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Using EaseType enum:";
    VNE_LOG_INFO << "  ease(EaseType::eSineInOut, 0.5) = " << ease(EaseType::eSineInOut, 0.5f);
}

void demonstrateImpulseFunctions() {
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Impulse Functions (IQ-style) ===";
    VNE_LOG_INFO << "";

    float k = 4.0f;

    VNE_LOG_INFO << "Exponential impulse (k=" << k << "):";
    VNE_LOG_INFO << "  Peak at x=1/k = " << 1.0f / k;
    VNE_LOG_INFO << "  Value at peak: " << expImpulse(1.0f / k, k);

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Polynomial impulse (k=" << k << "):";
    VNE_LOG_INFO << "  Peak at x=sqrt(1/k) = " << std::sqrt(1.0f / k);
    VNE_LOG_INFO << "  Value at peak: " << polyImpulse(std::sqrt(1.0f / k), k);

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Cubic pulse (center=5, width=2):";
    VNE_LOG_INFO << "  At center: " << cubicPulse(5.0f, 2.0f, 5.0f);
    VNE_LOG_INFO << "  At edge:   " << cubicPulse(5.0f, 2.0f, 7.0f);
    VNE_LOG_INFO << "  Outside:   " << cubicPulse(5.0f, 2.0f, 8.0f);
}

void demonstrateRayIntersection() {
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Ray Intersection Tests ===";
    VNE_LOG_INFO << "";

    // Create a ray
    Ray ray(Vec3f(0.0f, 0.0f, 10.0f), Vec3f(0.0f, 0.0f, -1.0f));
    VNE_LOG_INFO << "Ray: origin=" << ray.origin() << ", direction=" << ray.direction();

    // Ray-Sphere intersection
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Ray-Sphere:";
    Sphere sphere(Vec3f(0.0f, 0.0f, 0.0f), 2.0f);
    RayHit sphere_hit = intersect(ray, sphere);
    if (sphere_hit) {
        VNE_LOG_INFO << "  Hit at distance: " << sphere_hit.distance;
        VNE_LOG_INFO << "  Hit point: " << sphere_hit.point;
        VNE_LOG_INFO << "  Normal: " << sphere_hit.normal;
    }

    // Ray-AABB intersection
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Ray-AABB:";
    Aabb aabb(Vec3f(-1.0f, -1.0f, -1.0f), Vec3f(1.0f, 1.0f, 1.0f));
    RayHit aabb_hit = intersect(ray, aabb);
    if (aabb_hit) {
        VNE_LOG_INFO << "  Hit at distance: " << aabb_hit.distance;
        VNE_LOG_INFO << "  Hit point: " << aabb_hit.point;
        VNE_LOG_INFO << "  Normal: " << aabb_hit.normal;
    }

    // Ray-Triangle intersection
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Ray-Triangle:";
    Triangle tri(Vec3f(-2.0f, -2.0f, 0.0f), Vec3f(2.0f, -2.0f, 0.0f), Vec3f(0.0f, 2.0f, 0.0f));
    RayHit tri_hit = intersect(ray, tri);
    if (tri_hit) {
        VNE_LOG_INFO << "  Hit at distance: " << tri_hit.distance;
        VNE_LOG_INFO << "  Hit point: " << tri_hit.point;
        VNE_LOG_INFO << "  Barycentric UV: " << tri_hit.uv;
    }

    // Ray-Plane intersection
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Ray-Plane:";
    Plane plane(Vec3f(0.0f, 0.0f, 1.0f), 5.0f);  // z = -5
    RayHit plane_hit = intersect(ray, plane);
    if (plane_hit) {
        VNE_LOG_INFO << "  Hit at distance: " << plane_hit.distance;
        VNE_LOG_INFO << "  Hit point: " << plane_hit.point;
    }

    // Fast intersection tests
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Fast intersection tests (bool only):";
    VNE_LOG_INFO << "  Ray-Sphere: " << (intersects(ray, sphere) ? "HIT" : "MISS");
    VNE_LOG_INFO << "  Ray-AABB:   " << (intersects(ray, aabb) ? "HIT" : "MISS");

    // Miss case
    Ray miss_ray(Vec3f(10.0f, 10.0f, 10.0f), Vec3f(0.0f, 0.0f, -1.0f));
    VNE_LOG_INFO << "  Miss ray:   " << (intersects(miss_ray, sphere) ? "HIT" : "MISS");
}

void demonstrateScreenProjection() {
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Screen Projection Utilities ===";
    VNE_LOG_INFO << "";

    // Create camera matrices
    Vec3f eye(0.0f, 5.0f, 10.0f);
    Vec3f target(0.0f, 0.0f, 0.0f);
    Vec3f up = Vec3f::yAxis();

    Mat4f view = Mat4f::lookAt(eye, target, up, GraphicsApi::eVulkan);
    Mat4f proj = Mat4f::perspective(degToRad(60.0f), 16.0f / 9.0f, 0.1f, 100.0f, GraphicsApi::eVulkan);
    Mat4f mvp = viewProjection(view, proj);
    Mat4f inv_mvp = mvp.inverse();

    Viewport viewport(1920.0f, 1080.0f);

    VNE_LOG_INFO << "Camera: eye=" << eye << ", target=" << target;
    VNE_LOG_INFO << "Viewport: " << viewport.width << "x" << viewport.height;

    // Project world point to screen
    Vec3f world_point(0.0f, 0.0f, 0.0f);
    Vec3f screen_pos = project(world_point, mvp, viewport, GraphicsApi::eVulkan);
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "World-to-Screen:";
    VNE_LOG_INFO << "  World point: " << world_point;
    VNE_LOG_INFO << "  Screen pos:  (" << screen_pos.x() << ", " << screen_pos.y() << ") depth=" << screen_pos.z();

    // Unproject screen point to world
    Vec3f recovered = unproject(screen_pos, inv_mvp, viewport, GraphicsApi::eVulkan);
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Screen-to-World (unproject):";
    VNE_LOG_INFO << "  Recovered:   " << recovered;

    // Create picking ray from screen center
    Vec2f screen_center(viewport.width / 2.0f, viewport.height / 2.0f);
    Ray picking_ray = screenToWorldRay(screen_center, inv_mvp, viewport, eye, GraphicsApi::eVulkan);
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Picking ray from screen center:";
    VNE_LOG_INFO << "  Origin:    " << picking_ray.origin();
    VNE_LOG_INFO << "  Direction: " << picking_ray.direction();
}

void demonstrateAngleUtilities() {
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Angle Utilities ===";
    VNE_LOG_INFO << "";

    VNE_LOG_INFO << "normalizeAngle (to [0, 2π]):";
    VNE_LOG_INFO << "  -π    -> " << normalizeAngle(-kPi);
    VNE_LOG_INFO << "  3π    -> " << normalizeAngle(3.0f * kPi);
    VNE_LOG_INFO << "  -π/2  -> " << normalizeAngle(-kHalfPi);

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "normalizeAngleSigned (to [-π, π]):";
    VNE_LOG_INFO << "  3π/2  -> " << normalizeAngleSigned(1.5f * kPi);
    VNE_LOG_INFO << "  -3π/2 -> " << normalizeAngleSigned(-1.5f * kPi);

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "angleDifference (shortest path):";
    VNE_LOG_INFO << "  0 to π/2:  " << angleDifference(0.0f, kHalfPi);
    VNE_LOG_INFO << "  0 to 3π/2: " << angleDifference(0.0f, 1.5f * kPi) << " (goes backward!)";

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "lerpAngle (handles wraparound):";
    VNE_LOG_INFO << "  lerp(0, π, 0.5) = " << lerpAngle(0.0f, kPi, 0.5f);
}

void demonstrateDamping() {
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Animation Helpers ===";
    VNE_LOG_INFO << "";

    VNE_LOG_INFO << "Exponential damping (smooth following):";
    float current = 0.0f;
    float target = 10.0f;
    float smoothing = 0.1f;
    float dt = 0.016f;  // ~60 FPS

    VNE_LOG_INFO << "  Target: " << target << ", Smoothing: " << smoothing;
    for (int frame = 0; frame <= 100; frame += 20) {
        if (frame > 0) {
            for (int i = 0; i < 20; ++i) {
                current = damp(current, target, smoothing, dt);
            }
        }
        VNE_LOG_INFO << "  Frame " << frame << ": " << current;
    }
}

int main() {
    LoggingGuard_C logging_guard;

    VNE_LOG_INFO << "VneMath Example: Easing & Intersection";
    VNE_LOG_INFO << "=======================================";
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "High-performance easing functions (IQ-style)";
    VNE_LOG_INFO << "and ray intersection utilities.";

    demonstrateSmoothstep();
    demonstrateEasingFunctions();
    demonstrateImpulseFunctions();
    demonstrateRayIntersection();
    demonstrateScreenProjection();
    demonstrateAngleUtilities();
    demonstrateDamping();

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Done ===";
    return 0;
}

/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Example: Camera Controller
 * Demonstrates FPS and orbital camera implementations
 * ----------------------------------------------------------------------
 */

#include "fps_camera.h"
#include "orbital_camera.h"

#include "common/logging_guard.h"

#include <vertexnova/math/core/core.h>

using namespace vne::math;
using vne::math::examples::FPSCamera;
using vne::math::examples::LoggingGuard_C;
using vne::math::examples::OrbitalCamera;

void demonstrateFPSCamera() {
    VNE_LOG_INFO << "=== FPS Camera ===";

    FPSCamera camera(Vec3f(0.0f, 2.0f, 5.0f));

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Initial state:";
    VNE_LOG_INFO << "  Position: " << camera.getPosition();
    VNE_LOG_INFO << "  Front: " << camera.getFront();
    VNE_LOG_INFO << "  Right: " << camera.getRight();
    VNE_LOG_INFO << "  Up: " << camera.getUp();

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "View Matrix (Vulkan):";
    VNE_LOG_INFO << camera.getViewMatrix(GraphicsApi::eVulkan);

    // Simulate mouse look - turn 45 degrees right
    VNE_LOG_INFO << "After looking right 45 degrees:";
    camera.processMouseMovement(450.0f, 0.0f);  // 45 deg with 0.1 sensitivity
    VNE_LOG_INFO << "  Front: " << camera.getFront();

    // Simulate WASD movement - move forward
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "After moving forward for 1 second:";
    camera.processKeyboard(true, false, false, false, 1.0f);
    VNE_LOG_INFO << "  Position: " << camera.getPosition();

    // Simulate strafing right
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "After strafing right for 1 second:";
    camera.processKeyboard(false, false, false, true, 1.0f);
    VNE_LOG_INFO << "  Position: " << camera.getPosition();

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Final View Matrix:";
    VNE_LOG_INFO << camera.getViewMatrix(GraphicsApi::eVulkan);
}

void demonstrateOrbitalCamera() {
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Orbital Camera ===";

    OrbitalCamera camera(Vec3f::zero(), 10.0f);

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Initial state:";
    VNE_LOG_INFO << "  Target: " << camera.getTarget();
    VNE_LOG_INFO << "  Position: " << camera.getPosition();
    VNE_LOG_INFO << "  Distance: " << camera.getDistance();

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "View Matrix (Vulkan):";
    VNE_LOG_INFO << camera.getViewMatrix(GraphicsApi::eVulkan);

    // Orbit around the target
    VNE_LOG_INFO << "After orbiting 90 degrees horizontally:";
    camera.orbit(90.0f, 0.0f);
    VNE_LOG_INFO << "  Position: " << camera.getPosition();

    // Orbit vertically
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "After increasing elevation by 30 degrees:";
    camera.orbit(0.0f, 30.0f);
    VNE_LOG_INFO << "  Position: " << camera.getPosition();

    // Zoom in
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "After zooming in (distance - 5):";
    camera.zoom(5.0f);
    VNE_LOG_INFO << "  Distance: " << camera.getDistance();
    VNE_LOG_INFO << "  Position: " << camera.getPosition();

    // Pan the target
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "After panning target right by 2 units:";
    camera.pan(2.0f, 0.0f);
    VNE_LOG_INFO << "  Target: " << camera.getTarget();
    VNE_LOG_INFO << "  Position: " << camera.getPosition();

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Final View Matrix:";
    VNE_LOG_INFO << camera.getViewMatrix(GraphicsApi::eVulkan);
}

void demonstrateCameraInterpolation() {
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Camera Interpolation (Smooth Transitions) ===";

    // Two camera positions to interpolate between
    Vec3f start_pos(0.0f, 5.0f, 10.0f);
    Vec3f end_pos(10.0f, 2.0f, 0.0f);

    Quatf start_rot = Quatf::fromAxisAngle(Vec3f::yAxis(), degToRad(0.0f));
    Quatf end_rot = Quatf::fromAxisAngle(Vec3f::yAxis(), degToRad(90.0f));

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Start:";
    VNE_LOG_INFO << "  Position: " << start_pos;
    VNE_LOG_INFO << "  Rotation: " << start_rot;

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "End:";
    VNE_LOG_INFO << "  Position: " << end_pos;
    VNE_LOG_INFO << "  Rotation: " << end_rot;

    // Interpolate at different t values
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Interpolation:";
    for (float t = 0.0f; t <= 1.0f; t += 0.25f) {
        Vec3f pos = start_pos.lerp(end_pos, t);
        Quatf rot = Quatf::slerp(start_rot, end_rot, t);

        VNE_LOG_INFO << "  t=" << t << ":";
        VNE_LOG_INFO << "    Position: " << pos;
        VNE_LOG_INFO << "    Rotation angle: " << radToDeg(rot.angle()) << " degrees";
    }
}

int main() {
    LoggingGuard_C logging_guard;

    VNE_LOG_INFO << "VneMath Example: Camera Controller";
    VNE_LOG_INFO << "===================================";
    VNE_LOG_INFO << "";

    demonstrateFPSCamera();
    demonstrateOrbitalCamera();
    demonstrateCameraInterpolation();

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Done ===";
    return 0;
}

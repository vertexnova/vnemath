/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Example: Camera Controller
 * Demonstrates FPS and orbital camera implementations
 * ----------------------------------------------------------------------
 */

#include "common/logging_guard.h"

#include <vertexnova/math/core/core.h>

using namespace vne::math;
using vne::math::examples::LoggingGuard_C;

// =============================================================================
// FPS Camera - First Person Shooter style
// =============================================================================
class FPSCamera {
   public:
    FPSCamera(const Vec3f& position = Vec3f::zero())
        : position_(position), yaw_(0.0f), pitch_(0.0f), move_speed_(5.0f), look_sensitivity_(0.1f) {
        updateVectors();
    }

    // Process mouse movement (delta x, delta y in pixels)
    void processMouseMovement(float delta_x, float delta_y) {
        yaw_ += delta_x * look_sensitivity_;
        pitch_ -= delta_y * look_sensitivity_;

        // Clamp pitch to prevent flipping
        pitch_ = clamp(pitch_, -89.0f, 89.0f);

        updateVectors();
    }

    // Process keyboard input (WASD movement)
    void processKeyboard(bool forward, bool backward, bool left, bool right, float delta_time) {
        float velocity = move_speed_ * delta_time;

        if (forward) {
            position_ = position_ + front_ * velocity;
        }
        if (backward) {
            position_ = position_ - front_ * velocity;
        }
        if (left) {
            position_ = position_ - right_ * velocity;
        }
        if (right) {
            position_ = position_ + right_ * velocity;
        }
    }

    // Get the view matrix for the specified graphics API
    [[nodiscard]] Mat4f getViewMatrix(GraphicsApi api = GraphicsApi::eVulkan) const {
        return Mat4f::lookAt(position_, position_ + front_, up_, api);
    }

    [[nodiscard]] Vec3f getPosition() const { return position_; }
    [[nodiscard]] Vec3f getFront() const { return front_; }
    [[nodiscard]] Vec3f getRight() const { return right_; }
    [[nodiscard]] Vec3f getUp() const { return up_; }

    void setPosition(const Vec3f& pos) { position_ = pos; }

   private:
    void updateVectors() {
        // Calculate front vector from yaw and pitch using quaternions
        Quatf yaw_quat = Quatf::fromAxisAngle(Vec3f::yAxis(), degToRad(yaw_));
        Quatf pitch_quat = Quatf::fromAxisAngle(Vec3f::xAxis(), degToRad(pitch_));

        // Apply yaw first, then pitch (order matters!)
        Quatf orientation = yaw_quat * pitch_quat;

        // Default forward is -Z in right-handed coordinate system
        front_ = orientation.rotate(-Vec3f::zAxis());
        right_ = orientation.rotate(Vec3f::xAxis());
        up_ = orientation.rotate(Vec3f::yAxis());
    }

    Vec3f position_;
    Vec3f front_;
    Vec3f up_;
    Vec3f right_;

    float yaw_;    // Rotation around Y axis (horizontal)
    float pitch_;  // Rotation around X axis (vertical)

    float move_speed_;
    float look_sensitivity_;
};

// =============================================================================
// Orbital Camera - Rotate around a target
// =============================================================================
class OrbitalCamera {
   public:
    OrbitalCamera(const Vec3f& target = Vec3f::zero(), float distance = 10.0f)
        : target_(target),
          distance_(distance),
          azimuth_(0.0f),
          elevation_(30.0f),
          min_distance_(1.0f),
          max_distance_(100.0f) {
        updatePosition();
    }

    // Orbit around the target (delta in degrees)
    void orbit(float delta_azimuth, float delta_elevation) {
        azimuth_ += delta_azimuth;
        elevation_ += delta_elevation;

        // Clamp elevation to prevent flipping
        elevation_ = clamp(elevation_, -89.0f, 89.0f);

        // Wrap azimuth
        if (azimuth_ > 360.0f) azimuth_ -= 360.0f;
        if (azimuth_ < 0.0f) azimuth_ += 360.0f;

        updatePosition();
    }

    // Zoom in/out
    void zoom(float delta) {
        distance_ -= delta;
        distance_ = clamp(distance_, min_distance_, max_distance_);
        updatePosition();
    }

    // Pan the target point
    void pan(float delta_x, float delta_y) {
        // Get camera right and up vectors
        Vec3f to_camera = (position_ - target_).normalized();
        Vec3f right = Vec3f::yAxis().cross(to_camera).normalized();
        Vec3f up = to_camera.cross(right);

        target_ = target_ + right * delta_x + up * delta_y;
        updatePosition();
    }

    // Get the view matrix for the specified graphics API
    [[nodiscard]] Mat4f getViewMatrix(GraphicsApi api = GraphicsApi::eVulkan) const {
        return Mat4f::lookAt(position_, target_, Vec3f::yAxis(), api);
    }

    [[nodiscard]] Vec3f getPosition() const { return position_; }
    [[nodiscard]] Vec3f getTarget() const { return target_; }
    [[nodiscard]] float getDistance() const { return distance_; }

    void setTarget(const Vec3f& target) {
        target_ = target;
        updatePosition();
    }

   private:
    void updatePosition() {
        // Convert spherical coordinates to Cartesian
        float azimuth_rad = degToRad(azimuth_);
        float elevation_rad = degToRad(elevation_);

        float cos_elev = std::cos(elevation_rad);

        position_.x() = target_.x() + distance_ * cos_elev * std::sin(azimuth_rad);
        position_.y() = target_.y() + distance_ * std::sin(elevation_rad);
        position_.z() = target_.z() + distance_ * cos_elev * std::cos(azimuth_rad);
    }

    Vec3f target_;
    Vec3f position_;

    float distance_;
    float azimuth_;    // Horizontal angle (degrees)
    float elevation_;  // Vertical angle (degrees)

    float min_distance_;
    float max_distance_;
};

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
    Vec3f startPos(0.0f, 5.0f, 10.0f);
    Vec3f endPos(10.0f, 2.0f, 0.0f);

    Quatf startRot = Quatf::fromAxisAngle(Vec3f::yAxis(), degToRad(0.0f));
    Quatf endRot = Quatf::fromAxisAngle(Vec3f::yAxis(), degToRad(90.0f));

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Start:";
    VNE_LOG_INFO << "  Position: " << startPos;
    VNE_LOG_INFO << "  Rotation: " << startRot;

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "End:";
    VNE_LOG_INFO << "  Position: " << endPos;
    VNE_LOG_INFO << "  Rotation: " << endRot;

    // Interpolate at different t values
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Interpolation:";
    for (float t = 0.0f; t <= 1.0f; t += 0.25f) {
        Vec3f pos = startPos.lerp(endPos, t);
        Quatf rot = Quatf::slerp(startRot, endRot, t);

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

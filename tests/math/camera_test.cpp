/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Author:    Ajeet Singh Yadav
 * Created:   January 2026
 *
 * Camera system tests - FPS and Orbital camera controllers
 * Tests camera movement, rotation, and view matrix generation
 * for multi-backend graphics.
 * ----------------------------------------------------------------------
 */

#include <gtest/gtest.h>

#include "vertexnova/math/core/core.h"

namespace vne::math {

// ============================================================================
// FPS Camera Tests
// ============================================================================

/**
 * @brief Simple FPS camera for testing purposes.
 *
 * This mirrors the FPSCamera from the examples to test camera behavior.
 */
class FPSCamera {
   public:
    explicit FPSCamera(const Vec3f& position = Vec3f::zero())
        : position_{position}
        , front_{}
        , up_{}
        , right_{}
        , yaw_{0.0f}
        , pitch_{0.0f}
        , move_speed_{5.0f}
        , look_sensitivity_{0.1f} {
        updateVectors();
    }

    void processMouseMovement(float delta_x, float delta_y) {
        yaw_ += delta_x * look_sensitivity_;
        pitch_ -= delta_y * look_sensitivity_;
        pitch_ = clamp(pitch_, -89.0f, 89.0f);
        updateVectors();
    }

    void processKeyboard(bool forward, bool backward, bool left, bool right, float delta_time) {
        float velocity = move_speed_ * delta_time;
        if (forward)
            position_ = position_ + front_ * velocity;
        if (backward)
            position_ = position_ - front_ * velocity;
        if (left)
            position_ = position_ - right_ * velocity;
        if (right)
            position_ = position_ + right_ * velocity;
    }

    [[nodiscard]] Mat4f getViewMatrix(GraphicsApi api = GraphicsApi::eVulkan) const {
        return Mat4f::lookAt(position_, position_ + front_, up_, api);
    }

    [[nodiscard]] Vec3f getPosition() const noexcept { return position_; }
    [[nodiscard]] Vec3f getFront() const noexcept { return front_; }
    [[nodiscard]] Vec3f getRight() const noexcept { return right_; }
    [[nodiscard]] Vec3f getUp() const noexcept { return up_; }
    [[nodiscard]] float getYaw() const noexcept { return yaw_; }
    [[nodiscard]] float getPitch() const noexcept { return pitch_; }

    void setPosition(const Vec3f& pos) { position_ = pos; }

   private:
    void updateVectors() {
        Quatf yaw_quat = Quatf::fromAxisAngle(Vec3f::yAxis(), degToRad(yaw_));
        Quatf pitch_quat = Quatf::fromAxisAngle(Vec3f::xAxis(), degToRad(pitch_));
        Quatf orientation = yaw_quat * pitch_quat;

        front_ = orientation.rotate(-Vec3f::zAxis());
        right_ = orientation.rotate(Vec3f::xAxis());
        up_ = orientation.rotate(Vec3f::yAxis());
    }

    Vec3f position_;
    Vec3f front_;
    Vec3f up_;
    Vec3f right_;
    float yaw_;
    float pitch_;
    float move_speed_;
    float look_sensitivity_;
};

class FPSCameraTest : public ::testing::Test {
   protected:
    static constexpr float kEps = 1e-5f;
};

TEST_F(FPSCameraTest, DefaultConstruction) {
    FPSCamera camera;

    EXPECT_TRUE(camera.getPosition().areSame(Vec3f::zero(), kEps));
    EXPECT_NEAR(camera.getYaw(), 0.0f, kEps);
    EXPECT_NEAR(camera.getPitch(), 0.0f, kEps);
}

TEST_F(FPSCameraTest, InitialDirections) {
    FPSCamera camera;

    // Default: looking down -Z axis
    EXPECT_NEAR(camera.getFront().x(), 0.0f, kEps);
    EXPECT_NEAR(camera.getFront().y(), 0.0f, kEps);
    EXPECT_NEAR(camera.getFront().z(), -1.0f, kEps);

    // Right should be +X
    EXPECT_NEAR(camera.getRight().x(), 1.0f, kEps);
    EXPECT_NEAR(camera.getRight().y(), 0.0f, kEps);
    EXPECT_NEAR(camera.getRight().z(), 0.0f, kEps);

    // Up should be +Y
    EXPECT_NEAR(camera.getUp().x(), 0.0f, kEps);
    EXPECT_NEAR(camera.getUp().y(), 1.0f, kEps);
    EXPECT_NEAR(camera.getUp().z(), 0.0f, kEps);
}

TEST_F(FPSCameraTest, LookRight) {
    FPSCamera camera;

    // Look right 90 degrees (yaw += 90)
    camera.processMouseMovement(900.0f, 0.0f);  // 90 deg with 0.1 sensitivity

    // Front should now be -X
    EXPECT_NEAR(camera.getFront().x(), -1.0f, kEps);
    EXPECT_NEAR(camera.getFront().y(), 0.0f, kEps);
    EXPECT_NEAR(camera.getFront().z(), 0.0f, kEps);
}

TEST_F(FPSCameraTest, LookUp) {
    FPSCamera camera;

    // Look up 45 degrees (negative delta_y means pitch increases)
    camera.processMouseMovement(0.0f, -450.0f);  // 45 deg with 0.1 sensitivity

    // When looking up, front.y should be positive
    EXPECT_GT(camera.getFront().y(), 0.0f);
    EXPECT_NEAR(camera.getPitch(), 45.0f, kEps);
}

TEST_F(FPSCameraTest, PitchClamp) {
    FPSCamera camera;

    // Try to look straight up (beyond 89 degrees)
    camera.processMouseMovement(0.0f, -1000.0f);

    // Pitch should be clamped to 89
    EXPECT_NEAR(camera.getPitch(), 89.0f, kEps);

    // Try to look straight down
    camera.processMouseMovement(0.0f, 2000.0f);

    // Pitch should be clamped to -89
    EXPECT_NEAR(camera.getPitch(), -89.0f, kEps);
}

TEST_F(FPSCameraTest, MoveForward) {
    FPSCamera camera(Vec3f(0.0f, 0.0f, 10.0f));

    camera.processKeyboard(true, false, false, false, 1.0f);

    // Should have moved forward (along -Z)
    EXPECT_LT(camera.getPosition().z(), 10.0f);
}

TEST_F(FPSCameraTest, Strafe) {
    FPSCamera camera(Vec3f::zero());

    camera.processKeyboard(false, false, false, true, 1.0f);  // Strafe right

    // Should have moved right (along +X)
    EXPECT_GT(camera.getPosition().x(), 0.0f);
}

TEST_F(FPSCameraTest, ViewMatrixMultiBackend) {
    FPSCamera camera(Vec3f(0.0f, 5.0f, 10.0f));

    Mat4f view_vulkan = camera.getViewMatrix(GraphicsApi::eVulkan);
    Mat4f view_opengl = camera.getViewMatrix(GraphicsApi::eOpenGL);
    Mat4f view_metal = camera.getViewMatrix(GraphicsApi::eMetal);

    // Vulkan and OpenGL are both right-handed, should be similar
    // Metal is left-handed, should be different
    EXPECT_TRUE(view_vulkan.approxEquals(view_opengl, kEps));
    EXPECT_FALSE(view_vulkan.approxEquals(view_metal, kEps));
}

// ============================================================================
// Orbital Camera Tests
// ============================================================================

/**
 * @brief Simple orbital camera for testing purposes.
 */
class OrbitalCamera {
   public:
    explicit OrbitalCamera(const Vec3f& target = Vec3f::zero(), float distance = 10.0f)
        : target_{target}
        , position_{}
        , distance_{distance}
        , azimuth_{0.0f}
        , elevation_{30.0f}
        , min_distance_{1.0f}
        , max_distance_{100.0f} {
        updatePosition();
    }

    void orbit(float delta_azimuth, float delta_elevation) {
        azimuth_ += delta_azimuth;
        elevation_ += delta_elevation;
        elevation_ = clamp(elevation_, -89.0f, 89.0f);
        if (azimuth_ > 360.0f)
            azimuth_ -= 360.0f;
        if (azimuth_ < 0.0f)
            azimuth_ += 360.0f;
        updatePosition();
    }

    void zoom(float delta) {
        distance_ -= delta;
        distance_ = clamp(distance_, min_distance_, max_distance_);
        updatePosition();
    }

    [[nodiscard]] Mat4f getViewMatrix(GraphicsApi api = GraphicsApi::eVulkan) const {
        return Mat4f::lookAt(position_, target_, Vec3f::yAxis(), api);
    }

    [[nodiscard]] Vec3f getPosition() const noexcept { return position_; }
    [[nodiscard]] Vec3f getTarget() const noexcept { return target_; }
    [[nodiscard]] float getDistance() const noexcept { return distance_; }
    [[nodiscard]] float getAzimuth() const noexcept { return azimuth_; }
    [[nodiscard]] float getElevation() const noexcept { return elevation_; }

    void setTarget(const Vec3f& target) {
        target_ = target;
        updatePosition();
    }

   private:
    void updatePosition() {
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
    float azimuth_;
    float elevation_;
    float min_distance_;
    float max_distance_;
};

class OrbitalCameraTest : public ::testing::Test {
   protected:
    static constexpr float kEps = 1e-4f;
};

TEST_F(OrbitalCameraTest, DefaultConstruction) {
    OrbitalCamera camera;

    EXPECT_TRUE(camera.getTarget().areSame(Vec3f::zero(), kEps));
    EXPECT_NEAR(camera.getDistance(), 10.0f, kEps);
    EXPECT_NEAR(camera.getAzimuth(), 0.0f, kEps);
    EXPECT_NEAR(camera.getElevation(), 30.0f, kEps);
}

TEST_F(OrbitalCameraTest, DistanceFromTarget) {
    OrbitalCamera camera(Vec3f::zero(), 10.0f);

    float actual_distance = (camera.getPosition() - camera.getTarget()).length();
    EXPECT_NEAR(actual_distance, 10.0f, kEps);
}

TEST_F(OrbitalCameraTest, OrbitHorizontal) {
    OrbitalCamera camera(Vec3f::zero(), 10.0f);

    float initial_x = camera.getPosition().x();

    camera.orbit(90.0f, 0.0f);

    // After 90 degree horizontal orbit, X and Z should swap (roughly)
    EXPECT_NE(camera.getPosition().x(), initial_x);
    EXPECT_NEAR(camera.getAzimuth(), 90.0f, kEps);
}

TEST_F(OrbitalCameraTest, OrbitVertical) {
    OrbitalCamera camera(Vec3f::zero(), 10.0f);

    float initial_y = camera.getPosition().y();

    camera.orbit(0.0f, 30.0f);  // Increase elevation

    // Y position should increase
    EXPECT_GT(camera.getPosition().y(), initial_y);
    EXPECT_NEAR(camera.getElevation(), 60.0f, kEps);
}

TEST_F(OrbitalCameraTest, ElevationClamp) {
    OrbitalCamera camera(Vec3f::zero(), 10.0f);

    camera.orbit(0.0f, 100.0f);  // Try to go past 89 degrees

    EXPECT_NEAR(camera.getElevation(), 89.0f, kEps);
}

TEST_F(OrbitalCameraTest, ZoomIn) {
    OrbitalCamera camera(Vec3f::zero(), 10.0f);

    camera.zoom(5.0f);

    EXPECT_NEAR(camera.getDistance(), 5.0f, kEps);

    float actual_distance = (camera.getPosition() - camera.getTarget()).length();
    EXPECT_NEAR(actual_distance, 5.0f, kEps);
}

TEST_F(OrbitalCameraTest, ZoomClamp) {
    OrbitalCamera camera(Vec3f::zero(), 10.0f);

    camera.zoom(100.0f);  // Try to zoom past min distance

    EXPECT_NEAR(camera.getDistance(), 1.0f, kEps);  // min_distance_ = 1.0f
}

TEST_F(OrbitalCameraTest, AlwaysLooksAtTarget) {
    OrbitalCamera camera(Vec3f(5.0f, 5.0f, 5.0f), 20.0f);

    // Orbit to various positions
    for (float azimuth = 0.0f; azimuth < 360.0f; azimuth += 45.0f) {
        camera.orbit(45.0f, 0.0f);

        Mat4f view = camera.getViewMatrix(GraphicsApi::eVulkan);

        // Target should be at (0, 0, -distance) in view space (RH)
        Vec3f target_view = view.transformPoint(camera.getTarget());

        EXPECT_NEAR(target_view.x(), 0.0f, kEps);
        EXPECT_NEAR(target_view.y(), 0.0f, kEps);
    }
}

// ============================================================================
// Camera Interpolation Tests
// ============================================================================

class CameraInterpolationTest : public ::testing::Test {
   protected:
    static constexpr float kEps = 1e-5f;
};

TEST_F(CameraInterpolationTest, PositionLerp) {
    Vec3f start(0.0f, 5.0f, 10.0f);
    Vec3f end(10.0f, 2.0f, 0.0f);

    Vec3f mid = start.lerp(end, 0.5f);

    EXPECT_NEAR(mid.x(), 5.0f, kEps);
    EXPECT_NEAR(mid.y(), 3.5f, kEps);
    EXPECT_NEAR(mid.z(), 5.0f, kEps);
}

TEST_F(CameraInterpolationTest, RotationSlerp) {
    Quatf start = Quatf::identity();
    Quatf end = Quatf::fromAxisAngle(Vec3f::yAxis(), degToRad(180.0f));

    Quatf mid = Quatf::slerp(start, end, 0.5f);

    // Should be halfway (90 degrees)
    float angle = radToDeg(mid.angle());
    EXPECT_NEAR(angle, 90.0f, 0.1f);
}

TEST_F(CameraInterpolationTest, SlerpEndpoints) {
    Quatf start = Quatf::fromAxisAngle(Vec3f::yAxis(), degToRad(45.0f));
    Quatf end = Quatf::fromAxisAngle(Vec3f::yAxis(), degToRad(135.0f));

    Quatf at_start = Quatf::slerp(start, end, 0.0f);
    Quatf at_end = Quatf::slerp(start, end, 1.0f);

    // Should match endpoints
    Vec3f test_vec = Vec3f::zAxis();
    Vec3f start_rotated = start.rotate(test_vec);
    Vec3f end_rotated = end.rotate(test_vec);
    Vec3f at_start_rotated = at_start.rotate(test_vec);
    Vec3f at_end_rotated = at_end.rotate(test_vec);

    EXPECT_TRUE(start_rotated.areSame(at_start_rotated, kEps));
    EXPECT_TRUE(end_rotated.areSame(at_end_rotated, kEps));
}

}  // namespace vne::math

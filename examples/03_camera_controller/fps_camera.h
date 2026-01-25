#pragma once
/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Author:    Ajeet Singh Yadav
 * Created:   January 2026
 *
 * FPS Camera - First Person Shooter style camera controller
 * ----------------------------------------------------------------------
 */

#include <vertexnova/math/core/core.h>

namespace vne::math::examples {

/**
 * @class FPSCamera
 * @brief First-person shooter style camera controller.
 *
 * This camera uses quaternion-based rotation to avoid gimbal lock.
 * It supports WASD-style movement and mouse look controls.
 */
class FPSCamera {
   public:
    /**
     * @brief Constructs an FPS camera at the given position.
     * @param position Initial camera position (default: origin)
     */
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

    ~FPSCamera() = default;

    // Non-copyable, movable
    FPSCamera(const FPSCamera&) = default;
    FPSCamera& operator=(const FPSCamera&) = default;
    FPSCamera(FPSCamera&&) noexcept = default;
    FPSCamera& operator=(FPSCamera&&) noexcept = default;

   public:
    /**
     * @brief Process mouse movement for camera rotation.
     * @param delta_x Mouse delta X in pixels
     * @param delta_y Mouse delta Y in pixels
     */
    void processMouseMovement(float delta_x, float delta_y) {
        yaw_ += delta_x * look_sensitivity_;
        pitch_ -= delta_y * look_sensitivity_;

        // Clamp pitch to prevent flipping
        pitch_ = clamp(pitch_, -89.0f, 89.0f);

        updateVectors();
    }

    /**
     * @brief Process keyboard input for WASD movement.
     * @param forward Move forward
     * @param backward Move backward
     * @param left Strafe left
     * @param right Strafe right
     * @param delta_time Time since last frame in seconds
     */
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

    /**
     * @brief Get the view matrix for the specified graphics API.
     * @param api Target graphics API
     * @return View matrix
     */
    [[nodiscard]] Mat4f getViewMatrix(GraphicsApi api = GraphicsApi::eVulkan) const {
        return Mat4f::lookAt(position_, position_ + front_, up_, api);
    }

   public:
    /// @name Getters
    /// @{
    [[nodiscard]] Vec3f getPosition() const noexcept { return position_; }
    [[nodiscard]] Vec3f getFront() const noexcept { return front_; }
    [[nodiscard]] Vec3f getRight() const noexcept { return right_; }
    [[nodiscard]] Vec3f getUp() const noexcept { return up_; }
    [[nodiscard]] float getYaw() const noexcept { return yaw_; }
    [[nodiscard]] float getPitch() const noexcept { return pitch_; }
    [[nodiscard]] float getMoveSpeed() const noexcept { return move_speed_; }
    [[nodiscard]] float getLookSensitivity() const noexcept { return look_sensitivity_; }
    /// @}

    /// @name Setters
    /// @{
    void setPosition(const Vec3f& position) { position_ = position; }
    void setMoveSpeed(float speed) { move_speed_ = speed; }
    void setLookSensitivity(float sensitivity) { look_sensitivity_ = sensitivity; }
    /// @}

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

   private:
    Vec3f position_;
    Vec3f front_;
    Vec3f up_;
    Vec3f right_;

    float yaw_;    ///< Rotation around Y axis (horizontal) in degrees
    float pitch_;  ///< Rotation around X axis (vertical) in degrees

    float move_speed_;        ///< Movement speed in units per second
    float look_sensitivity_;  ///< Mouse look sensitivity
};

}  // namespace vne::math::examples

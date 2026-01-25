#pragma once
/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Author:    Ajeet Singh Yadav
 * Created:   January 2026
 *
 * Orbital Camera - Arcball style camera that orbits around a target
 * ----------------------------------------------------------------------
 */

#include <vertexnova/math/core/core.h>

#include <cmath>

namespace vne::math::examples {

/**
 * @class OrbitalCamera
 * @brief Arcball/orbital camera that rotates around a target point.
 *
 * Useful for object inspection, 3D modeling views, and similar scenarios
 * where the camera orbits around a focal point.
 */
class OrbitalCamera {
   public:
    /**
     * @brief Constructs an orbital camera.
     * @param target The point to orbit around (default: origin)
     * @param distance Initial distance from target
     */
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

    ~OrbitalCamera() = default;

    // Copyable, movable
    OrbitalCamera(const OrbitalCamera&) = default;
    OrbitalCamera& operator=(const OrbitalCamera&) = default;
    OrbitalCamera(OrbitalCamera&&) noexcept = default;
    OrbitalCamera& operator=(OrbitalCamera&&) noexcept = default;

   public:
    /**
     * @brief Orbit around the target.
     * @param delta_azimuth Horizontal rotation delta in degrees
     * @param delta_elevation Vertical rotation delta in degrees
     */
    void orbit(float delta_azimuth, float delta_elevation) {
        azimuth_ += delta_azimuth;
        elevation_ += delta_elevation;

        // Clamp elevation to prevent flipping
        elevation_ = clamp(elevation_, -89.0f, 89.0f);

        // Wrap azimuth
        if (azimuth_ > 360.0f) {
            azimuth_ -= 360.0f;
        }
        if (azimuth_ < 0.0f) {
            azimuth_ += 360.0f;
        }

        updatePosition();
    }

    /**
     * @brief Zoom in or out.
     * @param delta Positive value zooms in, negative zooms out
     */
    void zoom(float delta) {
        distance_ -= delta;
        distance_ = clamp(distance_, min_distance_, max_distance_);
        updatePosition();
    }

    /**
     * @brief Pan the target point.
     * @param delta_x Horizontal pan amount
     * @param delta_y Vertical pan amount
     */
    void pan(float delta_x, float delta_y) {
        // Get camera right and up vectors
        Vec3f to_camera = (position_ - target_).normalized();
        Vec3f right = Vec3f::yAxis().cross(to_camera).normalized();
        Vec3f up = to_camera.cross(right);

        target_ = target_ + right * delta_x + up * delta_y;
        updatePosition();
    }

    /**
     * @brief Get the view matrix for the specified graphics API.
     * @param api Target graphics API
     * @return View matrix
     */
    [[nodiscard]] Mat4f getViewMatrix(GraphicsApi api = GraphicsApi::eVulkan) const {
        return Mat4f::lookAt(position_, target_, Vec3f::yAxis(), api);
    }

   public:
    /// @name Getters
    /// @{
    [[nodiscard]] Vec3f getPosition() const noexcept { return position_; }
    [[nodiscard]] Vec3f getTarget() const noexcept { return target_; }
    [[nodiscard]] float getDistance() const noexcept { return distance_; }
    [[nodiscard]] float getAzimuth() const noexcept { return azimuth_; }
    [[nodiscard]] float getElevation() const noexcept { return elevation_; }
    [[nodiscard]] float getMinDistance() const noexcept { return min_distance_; }
    [[nodiscard]] float getMaxDistance() const noexcept { return max_distance_; }
    /// @}

    /// @name Setters
    /// @{
    void setTarget(const Vec3f& target) {
        target_ = target;
        updatePosition();
    }

    void setDistance(float distance) {
        distance_ = clamp(distance, min_distance_, max_distance_);
        updatePosition();
    }

    void setDistanceLimits(float min_dist, float max_dist) {
        min_distance_ = min_dist;
        max_distance_ = max_dist;
        distance_ = clamp(distance_, min_distance_, max_distance_);
        updatePosition();
    }
    /// @}

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

   private:
    Vec3f target_;    ///< The point the camera orbits around
    Vec3f position_;  ///< Current camera position (computed from spherical coords)

    float distance_;   ///< Distance from target
    float azimuth_;    ///< Horizontal angle in degrees
    float elevation_;  ///< Vertical angle in degrees

    float min_distance_;  ///< Minimum zoom distance
    float max_distance_;  ///< Maximum zoom distance
};

}  // namespace vne::math::examples

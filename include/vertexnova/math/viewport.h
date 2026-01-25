/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Viewport structure for screen-space transformations.
 * ----------------------------------------------------------------------
 */

#pragma once

#include "core/vec.h"

namespace vne::math {

/**
 * @struct Viewport
 * @brief Represents a viewport for screen-space transformations.
 *
 * A viewport defines the rectangular region of the screen where
 * rendering occurs. It's used for:
 * - World-to-screen projection (project)
 * - Screen-to-world unprojection (unproject)
 * - Picking ray generation (screenToWorldRay)
 * - Scissor rectangle definition
 * - Render target region specification
 *
 * The coordinate system depends on the graphics API:
 * - OpenGL: Y=0 at bottom
 * - Vulkan/Metal/DirectX: Y=0 at top
 */
struct Viewport {
    float x = 0.0f;       ///< Left edge in pixels
    float y = 0.0f;       ///< Top/bottom edge in pixels (depends on API)
    float width = 1.0f;   ///< Width in pixels
    float height = 1.0f;  ///< Height in pixels
    float z_near = 0.0f;  ///< Near depth value (0 or -1 depending on API)
    float z_far = 1.0f;   ///< Far depth value (always 1)

    // ========================================================================
    // Constructors
    // ========================================================================

    /**
     * @brief Default constructor. Creates a 1x1 viewport at origin.
     */
    constexpr Viewport() noexcept = default;

    /**
     * @brief Constructs a viewport from dimensions at origin.
     *
     * @param w Width in pixels
     * @param h Height in pixels
     */
    constexpr Viewport(float w, float h) noexcept
        : width(w)
        , height(h) {}

    /**
     * @brief Constructs a full viewport with all parameters.
     *
     * @param x_ Left edge in pixels
     * @param y_ Top/bottom edge in pixels
     * @param w Width in pixels
     * @param h Height in pixels
     * @param zn Near depth value (default 0)
     * @param zf Far depth value (default 1)
     */
    constexpr Viewport(float x_, float y_, float w, float h, float zn = 0.0f, float zf = 1.0f) noexcept
        : x(x_)
        , y(y_)
        , width(w)
        , height(h)
        , z_near(zn)
        , z_far(zf) {}

    // ========================================================================
    // Accessors
    // ========================================================================

    /**
     * @brief Returns viewport as Vec4 (x, y, width, height).
     *
     * Useful for passing to shaders or APIs that expect a 4-component vector.
     */
    [[nodiscard]] constexpr Vec4f toVec4() const noexcept { return Vec4f(x, y, width, height); }

    /**
     * @brief Returns the aspect ratio (width / height).
     */
    [[nodiscard]] constexpr float aspectRatio() const noexcept { return width / height; }

    /**
     * @brief Returns the center of the viewport.
     */
    [[nodiscard]] constexpr Vec2f center() const noexcept { return Vec2f(x + width * 0.5f, y + height * 0.5f); }

    /**
     * @brief Returns the size as a Vec2f (width, height).
     */
    [[nodiscard]] constexpr Vec2f size() const noexcept { return Vec2f(width, height); }

    /**
     * @brief Returns the top-left corner position.
     */
    [[nodiscard]] constexpr Vec2f position() const noexcept { return Vec2f(x, y); }

    /**
     * @brief Returns the right edge (x + width).
     */
    [[nodiscard]] constexpr float right() const noexcept { return x + width; }

    /**
     * @brief Returns the bottom edge (y + height).
     *
     * Note: Whether this is visually "bottom" depends on the API's Y direction.
     */
    [[nodiscard]] constexpr float bottom() const noexcept { return y + height; }

    // ========================================================================
    // Queries
    // ========================================================================

    /**
     * @brief Checks if a screen point is inside this viewport.
     *
     * @param screen_pos Screen coordinates (x, y)
     * @return true if inside viewport bounds
     */
    [[nodiscard]] constexpr bool contains(const Vec2f& screen_pos) const noexcept {
        return screen_pos.x() >= x && screen_pos.x() < x + width && screen_pos.y() >= y && screen_pos.y() < y + height;
    }

    /**
     * @brief Checks if this viewport is valid (positive dimensions).
     */
    [[nodiscard]] constexpr bool isValid() const noexcept { return width > 0.0f && height > 0.0f; }

    // ========================================================================
    // Comparison
    // ========================================================================

    [[nodiscard]] constexpr bool operator==(const Viewport& other) const noexcept = default;
};

}  // namespace vne::math

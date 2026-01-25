/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * 2D Rectangle primitive for UI, 2D games, and screen regions.
 * ----------------------------------------------------------------------
 */

#pragma once

#include "../core/types.h"
#include "../core/vec.h"

namespace vne::math {

/**
 * @class Rect
 * @brief A 2D axis-aligned rectangle defined by position and size.
 *
 * Uses the convention:
 * - (x, y) is the top-left corner (or min corner depending on coordinate system)
 * - (width, height) are the dimensions
 *
 * Common uses:
 * - UI element bounds
 * - 2D collision detection
 * - Texture regions / sprite sheets
 * - Screen regions
 */
class Rect {
   public:
    float x = 0.0f;       ///< X coordinate of the rectangle origin
    float y = 0.0f;       ///< Y coordinate of the rectangle origin
    float width = 0.0f;   ///< Width of the rectangle
    float height = 0.0f;  ///< Height of the rectangle

    // ========================================================================
    // Constructors
    // ========================================================================

    /**
     * @brief Default constructor. Creates an empty rectangle at origin.
     */
    constexpr Rect() noexcept = default;

    /**
     * @brief Constructs a rectangle from position and size.
     */
    constexpr Rect(float x_, float y_, float w, float h) noexcept
        : x(x_)
        , y(y_)
        , width(w)
        , height(h) {}

    /**
     * @brief Constructs a rectangle from position and size vectors.
     */
    constexpr Rect(const Vec2f& position, const Vec2f& size) noexcept
        : x(position.x())
        , y(position.y())
        , width(size.x())
        , height(size.y()) {}

    /**
     * @brief Constructs a rectangle from two corner points.
     *
     * @param min_corner Minimum corner (top-left in screen coords)
     * @param max_corner Maximum corner (bottom-right in screen coords)
     */
    [[nodiscard]] static constexpr Rect fromCorners(const Vec2f& min_corner, const Vec2f& max_corner) noexcept {
        return Rect(min_corner.x(), min_corner.y(), max_corner.x() - min_corner.x(), max_corner.y() - min_corner.y());
    }

    /**
     * @brief Constructs a rectangle from center and half-extents.
     */
    [[nodiscard]] static constexpr Rect fromCenterAndHalfExtents(const Vec2f& center,
                                                                 const Vec2f& half_extents) noexcept {
        return Rect(center.x() - half_extents.x(),
                    center.y() - half_extents.y(),
                    half_extents.x() * 2.0f,
                    half_extents.y() * 2.0f);
    }

    /**
     * @brief Constructs a rectangle from center and size.
     */
    [[nodiscard]] static constexpr Rect fromCenterAndSize(const Vec2f& center, const Vec2f& size) noexcept {
        return Rect(center.x() - size.x() * 0.5f, center.y() - size.y() * 0.5f, size.x(), size.y());
    }

    // ========================================================================
    // Accessors
    // ========================================================================

    /**
     * @brief Returns the position (top-left corner).
     */
    [[nodiscard]] constexpr Vec2f position() const noexcept { return Vec2f(x, y); }

    /**
     * @brief Returns the size.
     */
    [[nodiscard]] constexpr Vec2f size() const noexcept { return Vec2f(width, height); }

    /**
     * @brief Returns the center point.
     */
    [[nodiscard]] constexpr Vec2f center() const noexcept { return Vec2f(x + width * 0.5f, y + height * 0.5f); }

    /**
     * @brief Returns the half-extents (half size).
     */
    [[nodiscard]] constexpr Vec2f halfExtents() const noexcept { return Vec2f(width * 0.5f, height * 0.5f); }

    /**
     * @brief Returns the minimum corner (same as position).
     */
    [[nodiscard]] constexpr Vec2f min() const noexcept { return Vec2f(x, y); }

    /**
     * @brief Returns the maximum corner.
     */
    [[nodiscard]] constexpr Vec2f max() const noexcept { return Vec2f(x + width, y + height); }

    // Edge accessors
    [[nodiscard]] constexpr float left() const noexcept { return x; }
    [[nodiscard]] constexpr float right() const noexcept { return x + width; }
    [[nodiscard]] constexpr float top() const noexcept { return y; }
    [[nodiscard]] constexpr float bottom() const noexcept { return y + height; }

    /**
     * @brief Returns the area.
     */
    [[nodiscard]] constexpr float area() const noexcept { return width * height; }

    /**
     * @brief Returns the perimeter.
     */
    [[nodiscard]] constexpr float perimeter() const noexcept { return 2.0f * (width + height); }

    /**
     * @brief Returns the aspect ratio (width / height).
     */
    [[nodiscard]] constexpr float aspectRatio() const noexcept { return height != 0.0f ? width / height : 0.0f; }

    // ========================================================================
    // Containment Tests
    // ========================================================================

    /**
     * @brief Checks if a point is inside the rectangle.
     *
     * @param point The point to test
     * @return true if inside or on edge
     */
    [[nodiscard]] constexpr bool contains(const Vec2f& point) const noexcept {
        return point.x() >= x && point.x() <= x + width && point.y() >= y && point.y() <= y + height;
    }

    /**
     * @brief Checks if a point is inside (exclusive of edges).
     */
    [[nodiscard]] constexpr bool containsExclusive(const Vec2f& point) const noexcept {
        return point.x() > x && point.x() < x + width && point.y() > y && point.y() < y + height;
    }

    /**
     * @brief Checks if this rectangle fully contains another.
     */
    [[nodiscard]] constexpr bool contains(const Rect& other) const noexcept {
        return other.x >= x && other.y >= y && other.x + other.width <= x + width
               && other.y + other.height <= y + height;
    }

    // ========================================================================
    // Intersection Tests
    // ========================================================================

    /**
     * @brief Checks if this rectangle intersects another.
     */
    [[nodiscard]] constexpr bool intersects(const Rect& other) const noexcept {
        return x < other.x + other.width && x + width > other.x && y < other.y + other.height && y + height > other.y;
    }

    /**
     * @brief Returns the intersection of two rectangles.
     *
     * Returns an empty rectangle if no intersection.
     */
    [[nodiscard]] constexpr Rect intersection(const Rect& other) const noexcept {
        float x1 = vne::math::max(x, other.x);
        float y1 = vne::math::max(y, other.y);
        float x2 = vne::math::min(x + width, other.x + other.width);
        float y2 = vne::math::min(y + height, other.y + other.height);

        if (x2 <= x1 || y2 <= y1) {
            return Rect();  // No intersection
        }
        return Rect(x1, y1, x2 - x1, y2 - y1);
    }

    /**
     * @brief Returns the union (bounding box) of two rectangles.
     */
    [[nodiscard]] constexpr Rect unionWith(const Rect& other) const noexcept {
        float x1 = vne::math::min(x, other.x);
        float y1 = vne::math::min(y, other.y);
        float x2 = vne::math::max(x + width, other.x + other.width);
        float y2 = vne::math::max(y + height, other.y + other.height);
        return Rect(x1, y1, x2 - x1, y2 - y1);
    }

    // ========================================================================
    // Modifications
    // ========================================================================

    /**
     * @brief Expands the rectangle to include a point.
     */
    constexpr void expand(const Vec2f& point) noexcept {
        float new_x = vne::math::min(x, point.x());
        float new_y = vne::math::min(y, point.y());
        float new_max_x = vne::math::max(x + width, point.x());
        float new_max_y = vne::math::max(y + height, point.y());
        x = new_x;
        y = new_y;
        width = new_max_x - new_x;
        height = new_max_y - new_y;
    }

    /**
     * @brief Expands the rectangle by a uniform amount on all sides.
     */
    [[nodiscard]] constexpr Rect expanded(float amount) const noexcept {
        return Rect(x - amount, y - amount, width + 2.0f * amount, height + 2.0f * amount);
    }

    /**
     * @brief Translates the rectangle by an offset.
     */
    [[nodiscard]] constexpr Rect translated(const Vec2f& offset) const noexcept {
        return Rect(x + offset.x(), y + offset.y(), width, height);
    }

    /**
     * @brief Scales the rectangle from its center.
     */
    [[nodiscard]] constexpr Rect scaled(float scale) const noexcept {
        Vec2f c = center();
        float new_w = width * scale;
        float new_h = height * scale;
        return Rect(c.x() - new_w * 0.5f, c.y() - new_h * 0.5f, new_w, new_h);
    }

    // ========================================================================
    // Validation
    // ========================================================================

    /**
     * @brief Checks if the rectangle is valid (positive dimensions).
     */
    [[nodiscard]] constexpr bool isValid() const noexcept { return width > 0.0f && height > 0.0f; }

    /**
     * @brief Checks if the rectangle is empty (zero or negative dimensions).
     */
    [[nodiscard]] constexpr bool isEmpty() const noexcept { return width <= 0.0f || height <= 0.0f; }

    // ========================================================================
    // Comparison
    // ========================================================================

    [[nodiscard]] constexpr bool operator==(const Rect& other) const noexcept = default;

    [[nodiscard]] bool areSame(const Rect& other, float epsilon = kEpsilon<float>) const noexcept {
        return approxEqual(x, other.x, epsilon) && approxEqual(y, other.y, epsilon)
               && approxEqual(width, other.width, epsilon) && approxEqual(height, other.height, epsilon);
    }
};

}  // namespace vne::math

#pragma once
/* ---------------------------------------------------------------------
 * Copyright (c) 2024 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Author:    Ajeet Singh Yadav
 * Created:   September-2024
 *
 * Autodoc:   yes
 * ----------------------------------------------------------------------
 */

/**
 * @file color.h
 * @brief Defines the Color class for RGBA color representation.
 */

#include "constants.h"
#include "vec4f.h"

namespace vne::math {

/**
 * @class Color
 * @brief Represents a color using RGBA components.
 *
 * Each component is stored as a float in the range [0, 1].
 * Values outside this range are automatically clamped.
 */
class Color {
   public:
    /** @brief Default constructor, initializes to black with full opacity (0, 0, 0, 1) */
    Color() noexcept;

    /** @brief Default destructor */
    ~Color() noexcept = default;

    /**
     * @brief Constructs a color with specified RGBA values
     * @param red Red component [0, 1]
     * @param green Green component [0, 1]
     * @param blue Blue component [0, 1]
     * @param alpha Alpha (opacity) component [0, 1], default is 1.0
     */
    Color(float red, float green, float blue, float alpha = 1.0f) noexcept;

    /**
     * @brief Constructs a color from RGB vector and alpha
     * @param rgb Vec3f containing RGB components
     * @param alpha Alpha component, default is 1.0
     */
    Color(const Vec3f& rgb, float alpha = 1.0f) noexcept;

    /**
     * @brief Constructs a color from RGBA vector
     * @param rgba Vec4f containing RGBA components
     */
    Color(const Vec4f& rgba) noexcept;

    /** @brief Copy constructor */
    Color(const Color& rhs) noexcept;

    /** @brief Copy assignment operator */
    Color& operator=(const Color& rhs) noexcept;

   public:
    /**
     * @brief Gets a pointer to the underlying RGBA data
     * @return Pointer to the first component (red)
     */
    [[nodiscard]] float* getPtr() noexcept;

    /**
     * @brief Gets a const pointer to the underlying RGBA data
     * @return Const pointer to the first component (red)
     */
    [[nodiscard]] const float* getPtr() const noexcept;

   public:
    /**
     * @brief Checks if two colors are approximately equal
     * @param color The color to compare against
     * @param eps The tolerance for comparison
     * @return true if all components are within eps
     */
    [[nodiscard]] bool areSame(const Color& color, float eps = kFloatEpsilon) const noexcept;

    /**
     * @brief Checks if this color is approximately black (RGB = 0)
     * @param eps The tolerance for comparison
     * @return true if RGB components are within eps of zero
     */
    [[nodiscard]] bool isZero(float eps = kFloatEpsilon) const noexcept;

    /**
     * @brief Linearly interpolates between this color and another
     * @param color The target color
     * @param t The interpolation factor [0, 1]
     * @return The interpolated color
     */
    [[nodiscard]] Color lerp(const Color& color, float t) const noexcept;

   public:
    /** @brief Resets the color to black with full opacity (0, 0, 0, 1) */
    void reset() noexcept;

    /**
     * @brief Sets all color components
     * @param red Red component
     * @param green Green component
     * @param blue Blue component
     * @param alpha Alpha component
     */
    void set(float red = 1.0f, float green = 1.0f, float blue = 1.0f, float alpha = 1.0f) noexcept;

    /**
     * @brief Sets color from RGB vector and alpha
     * @param rgb Vec3f containing RGB
     * @param alpha Alpha component
     */
    void set(const Vec3f& rgb, float alpha = 1.0f) noexcept;

    /**
     * @brief Sets color from RGBA vector
     * @param rgba Vec4f containing RGBA
     */
    void set(const Vec4f& rgba) noexcept;

   public:
    /// @name Component Accessors
    /// @{

    /** @brief Gets the red component */
    [[nodiscard]] float r() const noexcept;

    /** @brief Gets the green component */
    [[nodiscard]] float g() const noexcept;

    /** @brief Gets the blue component */
    [[nodiscard]] float b() const noexcept;

    /** @brief Gets the alpha component */
    [[nodiscard]] float a() const noexcept;

    /** @brief Gets the RGB components as a Vec3f */
    [[nodiscard]] Vec3f rgb() const noexcept;

    /** @brief Gets the RGBA components as a Vec4f */
    [[nodiscard]] Vec4f rgba() const noexcept;

    /** @brief Gets a reference to the red component */
    [[nodiscard]] float& r() noexcept;

    /** @brief Gets a reference to the green component */
    [[nodiscard]] float& g() noexcept;

    /** @brief Gets a reference to the blue component */
    [[nodiscard]] float& b() noexcept;

    /** @brief Gets a reference to the alpha component */
    [[nodiscard]] float& a() noexcept;

    /** @brief Sets the red component */
    void setR(float red) noexcept;

    /** @brief Sets the green component */
    void setG(float green) noexcept;

    /** @brief Sets the blue component */
    void setB(float blue) noexcept;

    /** @brief Sets the alpha component */
    void setA(float alpha) noexcept;
    /// @}

   public:
    /// @name Arithmetic Assignment Operators
    /// @{
    Color& operator+=(float scalar) noexcept;
    Color& operator-=(float scalar) noexcept;
    Color& operator*=(float scalar) noexcept;
    Color& operator/=(float scalar) noexcept;
    Color& operator+=(const Color& color) noexcept;
    Color& operator-=(const Color& color) noexcept;
    Color& operator*=(const Color& color) noexcept;
    Color& operator/=(const Color& color) noexcept;
    /// @}

    /// @name Arithmetic Operators
    /// @{
    [[nodiscard]] Color operator+(float scalar) const noexcept;
    [[nodiscard]] Color operator-(float scalar) const noexcept;
    [[nodiscard]] Color operator*(float scalar) const noexcept;
    [[nodiscard]] Color operator/(float scalar) const noexcept;
    [[nodiscard]] Color operator+(const Color& color) const noexcept;
    [[nodiscard]] Color operator-(const Color& color) const noexcept;
    [[nodiscard]] Color operator*(const Color& color) const noexcept;
    [[nodiscard]] Color operator/(const Color& color) const noexcept;
    /// @}

    /// @name Comparison Operators
    /// @{
    [[nodiscard]] bool operator==(const Color& color) const noexcept;
    [[nodiscard]] bool operator!=(const Color& color) const noexcept;
    /// @}

    /// @name Subscript Operators
    /// @{
    [[nodiscard]] float operator[](uint32_t index) noexcept;
    [[nodiscard]] float operator[](uint32_t index) const noexcept;
    /// @}

   public:
    /// @name Stream Operators
    /// @{
    friend std::ostream& operator<<(std::ostream& os, const Color& color);
    friend std::istream& operator>>(std::istream& is, Color& color);
    /// @}

   private:
    /** @brief Clamps all components to valid ranges */
    void clamp() noexcept;

   private:
    float r_ = 0.0f;  ///< Red component [0, 1]
    float g_ = 0.0f;  ///< Green component [0, 1]
    float b_ = 0.0f;  ///< Blue component [0, 1]
    float a_ = 1.0f;  ///< Alpha component [0, 1]

   public:
    /// @name Predefined Colors
    /// @{
    static const Color kWhite;      ///< White (1, 1, 1, 1)
    static const Color kBlack;      ///< Black (0, 0, 0, 1)
    static const Color kRed;        ///< Red (1, 0, 0, 1)
    static const Color kGreen;      ///< Green (0, 1, 0, 1)
    static const Color kBlue;       ///< Blue (0, 0, 1, 1)
    static const Color kYellow;     ///< Yellow (1, 1, 0, 1)
    static const Color kCyan;       ///< Cyan (0, 1, 1, 1)
    static const Color kMagenta;    ///< Magenta (1, 0, 1, 1)
    static const Color kLightBlue;  ///< Light Blue
    static const Color kDarkBlue;   ///< Dark Blue
    static const Color kMaroon;     ///< Maroon
    static const Color kBeige;      ///< Beige
    static const Color kBrown;      ///< Brown
    static const Color kGray;       ///< Gray (0.5, 0.5, 0.5, 1)
    static const Color kGrey;       ///< Grey (alias for kGray)
    /// @}
};

}  // namespace vne::math

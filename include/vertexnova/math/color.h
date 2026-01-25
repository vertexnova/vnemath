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
 * @brief Defines a color using RGBA components. Each component is in [0..1].
 */

#include "constants.h"
#include "vec4f.h"

namespace vne::math {

class Color {
   public:
    Color() noexcept;
    ~Color() noexcept = default;
    Color(float red, float green, float blue, float alpha = 1.0f) noexcept;
    Color(const Vec3f_C& rgb, float alpha = 1.0f) noexcept;
    Color(const Vec4f_C& rgba) noexcept;
    Color(const Color& rhs) noexcept;
    Color& operator=(const Color& rhs) noexcept;

   public:
    [[nodiscard]] float* GetPtr() noexcept;
    [[nodiscard]] const float* GetPtr() const noexcept;

   public:
    [[nodiscard]] bool AreSame(const Color& color, float eps = kFloatEpsilon) const noexcept;
    [[nodiscard]] bool IsZero(float eps = kFloatEpsilon) const noexcept;
    [[nodiscard]] Color Lerp(const Color& color, float t) const noexcept;

   public:
    void Reset() noexcept;
    void Set(float red = 1.0f, float green = 1.0f, float blue = 1.0f, float alpha = 1.0f) noexcept;
    void Set(const Vec3f_C& rgb, float alpha = 1.0f) noexcept;
    void Set(const Vec4f_C& rgba) noexcept;

   public:
    [[nodiscard]] float R() const noexcept;
    [[nodiscard]] float G() const noexcept;
    [[nodiscard]] float B() const noexcept;
    [[nodiscard]] float A() const noexcept;
    [[nodiscard]] Vec3f_C RGB() const noexcept;
    [[nodiscard]] Vec4f_C RGBA() const noexcept;
    [[nodiscard]] float& R() noexcept;
    [[nodiscard]] float& G() noexcept;
    [[nodiscard]] float& B() noexcept;
    [[nodiscard]] float& A() noexcept;
    void R(float red) noexcept;
    void G(float green) noexcept;
    void B(float blue) noexcept;
    void A(float alpha) noexcept;

   public:
    Color& operator+=(float scalar) noexcept;
    Color& operator-=(float scalar) noexcept;
    Color& operator*=(float scalar) noexcept;
    Color& operator/=(float scalar) noexcept;
    Color& operator+=(const Color& color) noexcept;
    Color& operator-=(const Color& color) noexcept;
    Color& operator*=(const Color& color) noexcept;
    Color& operator/=(const Color& color) noexcept;
    [[nodiscard]] Color operator+(float scalar) const noexcept;
    [[nodiscard]] Color operator-(float scalar) const noexcept;
    [[nodiscard]] Color operator*(float scalar) const noexcept;
    [[nodiscard]] Color operator/(float scalar) const noexcept;
    [[nodiscard]] Color operator+(const Color& color) const noexcept;
    [[nodiscard]] Color operator-(const Color& color) const noexcept;
    [[nodiscard]] Color operator*(const Color& color) const noexcept;
    [[nodiscard]] Color operator/(const Color& color) const noexcept;
    [[nodiscard]] bool operator==(const Color& color) const noexcept;
    [[nodiscard]] bool operator!=(const Color& color) const noexcept;
    [[nodiscard]] float operator[](uint32_t index) noexcept;
    [[nodiscard]] float operator[](uint32_t index) const noexcept;

   public:
    friend std::ostream& operator<<(std::ostream& os, const Color& color);
    friend std::istream& operator>>(std::istream& is, Color& color);

   private:
    void Clamp() noexcept;

   private:
    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;
    float a = 1.0f;

   public:
    static const Color WHITE;
    static const Color BLACK;
    static const Color RED;
    static const Color GREEN;
    static const Color BLUE;
    static const Color YELLOW;
    static const Color CYAN;
    static const Color MAGENTA;
    static const Color LIGHT_BLUE;
    static const Color DARK_BLUE;
    static const Color MAROON;
    static const Color BEIGE;
    static const Color BROWN;
    static const Color GRAY;
    static const Color GREY;
};

}  // namespace vne::math

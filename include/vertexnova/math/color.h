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
    Color(const Vec3f& rgb, float alpha = 1.0f) noexcept;
    Color(const Vec4f& rgba) noexcept;
    Color(const Color& rhs) noexcept;
    Color& operator=(const Color& rhs) noexcept;

   public:
    [[nodiscard]] float* getPtr() noexcept;
    [[nodiscard]] const float* getPtr() const noexcept;

   public:
    [[nodiscard]] bool areSame(const Color& color, float eps = kFloatEpsilon) const noexcept;
    [[nodiscard]] bool isZero(float eps = kFloatEpsilon) const noexcept;
    [[nodiscard]] Color lerp(const Color& color, float t) const noexcept;

   public:
    void reset() noexcept;
    void set(float red = 1.0f, float green = 1.0f, float blue = 1.0f, float alpha = 1.0f) noexcept;
    void set(const Vec3f& rgb, float alpha = 1.0f) noexcept;
    void set(const Vec4f& rgba) noexcept;

   public:
    [[nodiscard]] float r() const noexcept;
    [[nodiscard]] float g() const noexcept;
    [[nodiscard]] float b() const noexcept;
    [[nodiscard]] float a() const noexcept;
    [[nodiscard]] Vec3f rgb() const noexcept;
    [[nodiscard]] Vec4f rgba() const noexcept;
    [[nodiscard]] float& r() noexcept;
    [[nodiscard]] float& g() noexcept;
    [[nodiscard]] float& b() noexcept;
    [[nodiscard]] float& a() noexcept;
    void setR(float red) noexcept;
    void setG(float green) noexcept;
    void setB(float blue) noexcept;
    void setA(float alpha) noexcept;

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
    void clamp() noexcept;

   private:
    float r_ = 0.0f;
    float g_ = 0.0f;
    float b_ = 0.0f;
    float a_ = 1.0f;

   public:
    static const Color kWhite;
    static const Color kBlack;
    static const Color kRed;
    static const Color kGreen;
    static const Color kBlue;
    static const Color kYellow;
    static const Color kCyan;
    static const Color kMagenta;
    static const Color kLightBlue;
    static const Color kDarkBlue;
    static const Color kMaroon;
    static const Color kBeige;
    static const Color kBrown;
    static const Color kGray;
    static const Color kGrey;
};

}  // namespace vne::math

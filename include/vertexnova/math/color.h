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
    Color();
    ~Color();
    Color(float red, float green, float blue, float alpha = 1.0f);
    Color(const Vec3f_C& rgb, float alpha = 1.0f);
    Color(const Vec4f_C& rgba);
    Color(const Color& rhs);
    Color& operator=(const Color& rhs);

   public:
    float* GetPtr();
    const float* GetPtr() const;

   public:
    bool AreSame(const Color& color, float eps = kFloatEpsilon) const;
    bool IsZero(float eps = kFloatEpsilon) const;
    Color Lerp(const Color& color, float t) const;

   public:
    void Reset();
    void Set(float red = 1.0f, float green = 1.0f, float blue = 1.0f, float alpha = 1.0f);
    void Set(const Vec3f_C& rgb, float alpha = 1.0f);
    void Set(const Vec4f_C& rgba);

   public:
    float R() const;
    float G() const;
    float B() const;
    float A() const;
    Vec3f_C RGB() const;
    Vec4f_C RGBA() const;
    float& R();
    float& G();
    float& B();
    float& A();
    void R(float red);
    void G(float green);
    void B(float blue);
    void A(float alpha);

   public:
    Color& operator+=(float scalar);
    Color& operator-=(float scalar);
    Color& operator*=(float scalar);
    Color& operator/=(float scalar);
    Color& operator+=(const Color& color);
    Color& operator-=(const Color& color);
    Color& operator*=(const Color& color);
    Color& operator/=(const Color& color);
    Color operator+(float scalar) const;
    Color operator-(float scalar) const;
    Color operator*(float scalar) const;
    Color operator/(float scalar) const;
    Color operator+(const Color& color) const;
    Color operator-(const Color& color) const;
    Color operator*(const Color& color) const;
    Color operator/(const Color& color) const;
    bool operator==(const Color& color) const;
    bool operator!=(const Color& color) const;
    float operator[](uint32_t index);
    float operator[](uint32_t index) const;

   public:
    friend std::ostream& operator<<(std::ostream& os, const Color& color);
    friend std::istream& operator>>(std::istream& is, Color& color);

   private:
    void Clamp();

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


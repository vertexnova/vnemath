#ifndef VNE_MATH_COLOR_H
#define VNE_MATH_COLOR_H
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

namespace VNE {
namespace Math {

class Color_C {
   public:
    Color_C();
    ~Color_C();
    Color_C(float red, float green, float blue, float alpha = 1.0f);
    Color_C(const Vec3f_C& rgb, float alpha = 1.0f);
    Color_C(const Vec4f_C& rgba);
    Color_C(const Color_C& rhs);
    Color_C& operator=(const Color_C& rhs);

   public:
    float* GetPtr();
    const float* GetPtr() const;

   public:
    bool AreSame(const Color_C& color, float eps = Math::FLOAT_EPSILON) const;
    bool IsZero(float eps = Math::FLOAT_EPSILON) const;
    Color_C Lerp(const Color_C& color, float t) const;

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
    Color_C& operator+=(float scalar);
    Color_C& operator-=(float scalar);
    Color_C& operator*=(float scalar);
    Color_C& operator/=(float scalar);
    Color_C& operator+=(const Color_C& color);
    Color_C& operator-=(const Color_C& color);
    Color_C& operator*=(const Color_C& color);
    Color_C& operator/=(const Color_C& color);
    Color_C operator+(float scalar) const;
    Color_C operator-(float scalar) const;
    Color_C operator*(float scalar) const;
    Color_C operator/(float scalar) const;
    Color_C operator+(const Color_C& color) const;
    Color_C operator-(const Color_C& color) const;
    Color_C operator*(const Color_C& color) const;
    Color_C operator/(const Color_C& color) const;
    bool operator==(const Color_C& color) const;
    bool operator!=(const Color_C& color) const;
    float operator[](uint32_t index);
    float operator[](uint32_t index) const;

   public:
    friend std::ostream& operator<<(std::ostream& os, const Color_C& color);
    friend std::istream& operator>>(std::istream& is, Color_C& color);

   private:
    void Clamp();

   private:
    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;
    float a = 1.0f;

   public:
    static const Color_C WHITE;
    static const Color_C BLACK;
    static const Color_C RED;
    static const Color_C GREEN;
    static const Color_C BLUE;
    static const Color_C YELLOW;
    static const Color_C CYAN;
    static const Color_C MAGENTA;
    static const Color_C LIGHT_BLUE;
    static const Color_C DARK_BLUE;
    static const Color_C MAROON;
    static const Color_C BEIGE;
    static const Color_C BROWN;
    static const Color_C GRAY;
    static const Color_C GREY;
};

}  // namespace Math
}  // namespace VNE

#endif  // VNE_MATH_COLOR_H

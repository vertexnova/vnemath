/* ---------------------------------------------------------------------
 * Copyright (c) 2024 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Author:    Ajeet Singh Yadav
 * Created:   July-2024
 *
 * Autodoc:   yes
 * ----------------------------------------------------------------------
 */

// Corresponding header
#include "vertexnova/math/color.h"

// Project headers
#include "vertexnova/common/macros.h"
#include "vertexnova/math/math_utils.h"

namespace vne::math {

const Color Color::WHITE = Color(1.0f, 1.0f, 1.0f);
const Color Color::BLACK = Color(0.0f, 0.0f, 0.0f);
const Color Color::RED = Color(1.0f, 0.0f, 0.0f);
const Color Color::GREEN = Color(0.0f, 1.0f, 0.0f);
const Color Color::BLUE = Color(0.0f, 0.0f, 1.0f);
const Color Color::YELLOW = Color(1.0f, 1.0f, 0.0f);
const Color Color::CYAN = Color(0.0f, 1.0f, 1.0f);
const Color Color::MAGENTA = Color(1.0f, 0.0f, 1.0f);
const Color Color::LIGHT_BLUE = Color(0.4f, 0.4f, 0.8f);
const Color Color::DARK_BLUE = Color(0.1f, 0.1f, 0.6f);
const Color Color::MAROON = Color(0.5f, 0.0f, 0.0f);
const Color Color::BEIGE = Color(0.96f, 0.96f, 0.862f);
const Color Color::BROWN = Color(0.647f, 0.164f, 0.164f);
const Color Color::GRAY = Color(0.5f, 0.5f, 0.5f);
const Color Color::GREY = Color(0.5f, 0.5f, 0.5f);

//------------------------------------------------------------------------------
Color::Color() noexcept {}

//------------------------------------------------------------------------------
Color::Color(const float red, const float green, const float blue, const float alpha) noexcept
    : r(red)
    , g(green)
    , b(blue)
    , a(alpha) {
    Clamp();
}

//------------------------------------------------------------------------------
Color::Color(const Vec3f_C& rgb, float alpha) noexcept
    : r(rgb.r)
    , g(rgb.g)
    , b(rgb.b)
    , a(alpha) {
    Clamp();
}

//------------------------------------------------------------------------------
Color::Color(const Vec4f_C& rgba) noexcept
    : r(rgba.r)
    , g(rgba.g)
    , b(rgba.b)
    , a(rgba.a) {
    Clamp();
}

//------------------------------------------------------------------------------
Color::Color(const Color& rhs) noexcept
    : r(rhs.r)
    , g(rhs.g)
    , b(rhs.b)
    , a(rhs.a) {
    Clamp();
}

//------------------------------------------------------------------------------
Color& Color::operator=(const Color& rhs) noexcept {
    r = rhs.r;
    g = rhs.g;
    b = rhs.b;
    a = rhs.a;
    Clamp();

    return *this;
}

//------------------------------------------------------------------------------
float* Color::GetPtr() noexcept {
    return &r;
}

//------------------------------------------------------------------------------
const float* Color::GetPtr() const noexcept {
    return &r;
}

//------------------------------------------------------------------------------
bool Color::AreSame(const Color& color, float eps) const noexcept {
    return vne::math::areSame(r, color.r, eps) && vne::math::areSame(g, color.g, eps)
           && vne::math::areSame(b, color.b, eps) && vne::math::areSame(a, color.a, eps);
}

//------------------------------------------------------------------------------
bool Color::IsZero(float eps) const noexcept {
    return vne::math::isZero(r, eps) && vne::math::isZero(g, eps) && vne::math::isZero(b, eps);
}

//------------------------------------------------------------------------------
Color Color::Lerp(const Color& color, float t) const noexcept {
    return Color(vne::math::lerp(r, color.r, t),
                 vne::math::lerp(g, color.g, t),
                 vne::math::lerp(b, color.b, t),
                 vne::math::lerp(a, color.a, t));
}

//------------------------------------------------------------------------------
void Color::Reset() noexcept {
    r = 0.0f;
    g = 0.0f;
    b = 0.0f;
    a = 1.0f;
}

//------------------------------------------------------------------------------
void Color::Set(float red, float green, float blue, float alpha) noexcept {
    r = red;
    g = green;
    b = blue;
    a = alpha;
    Clamp();
}

//------------------------------------------------------------------------------
void Color::Set(const Vec3f_C& rgb, float alpha) noexcept {
    r = rgb.r;
    g = rgb.g;
    b = rgb.b;
    a = alpha;
    Clamp();
}

//------------------------------------------------------------------------------
void Color::Set(const Vec4f_C& rgba) noexcept {
    r = rgba.r;
    g = rgba.g;
    b = rgba.b;
    a = rgba.a;
    Clamp();
}

//------------------------------------------------------------------------------
float Color::R() const noexcept {
    return r;
}

//------------------------------------------------------------------------------
float Color::G() const noexcept {
    return g;
}

//------------------------------------------------------------------------------
float Color::B() const noexcept {
    return b;
}

//------------------------------------------------------------------------------
float Color::A() const noexcept {
    return a;
}

//------------------------------------------------------------------------------
Vec3f_C Color::RGB() const noexcept {
    return {r, b, g};
}

//------------------------------------------------------------------------------
Vec4f_C Color::RGBA() const noexcept {
    return {r, g, b, a};
}

//------------------------------------------------------------------------------
float& Color::R() noexcept {
    return r;
}

//------------------------------------------------------------------------------
float& Color::G() noexcept {
    return g;
}

//------------------------------------------------------------------------------
float& Color::B() noexcept {
    return b;
}

//------------------------------------------------------------------------------
float& Color::A() noexcept {
    return a;
}

//------------------------------------------------------------------------------
void Color::R(float red) noexcept {
    r = red;
}
//------------------------------------------------------------------------------
void Color::G(float green) noexcept {
    g = green;
}

//------------------------------------------------------------------------------
void Color::B(const float blue) noexcept {
    b = blue;
}

//------------------------------------------------------------------------------
void Color::A(const float alpha) noexcept {
    a = alpha;
}

//------------------------------------------------------------------------------
Color& Color::operator+=(float scalar) noexcept {
    r += scalar;
    g += scalar;
    b += scalar;
    a += scalar;
    Clamp();

    return *this;
}

//------------------------------------------------------------------------------
Color& Color::operator-=(float scalar) noexcept {
    r -= scalar;
    g -= scalar;
    b -= scalar;
    a -= scalar;
    Clamp();

    return *this;
}

//------------------------------------------------------------------------------
Color& Color::operator*=(float scalar) noexcept {
    r *= scalar;
    g *= scalar;
    b *= scalar;
    a *= scalar;
    Clamp();

    return *this;
}

//------------------------------------------------------------------------------
Color& Color::operator/=(float scalar) noexcept {
    r /= scalar;
    g /= scalar;
    b /= scalar;
    a /= scalar;
    Clamp();

    return *this;
}

//------------------------------------------------------------------------------
Color& Color::operator+=(const Color& color) noexcept {
    r += color.r;
    g += color.g;
    b += color.b;
    a += color.a;
    Clamp();

    return *this;
}

//------------------------------------------------------------------------------
Color& Color::operator-=(const Color& color) noexcept {
    r -= color.r;
    g -= color.g;
    b -= color.b;
    a -= color.a;
    Clamp();

    return *this;
}

//------------------------------------------------------------------------------
Color& Color::operator*=(const Color& color) noexcept {
    r *= color.r;
    g *= color.g;
    b *= color.b;
    a *= color.a;
    Clamp();

    return *this;
}

//------------------------------------------------------------------------------
Color& Color::operator/=(const Color& color) noexcept {
    r /= color.r;
    g /= color.g;
    b /= color.b;
    a /= color.a;
    Clamp();

    return *this;
}

//------------------------------------------------------------------------------
Color Color::operator+(float scalar) const noexcept {
    return Color(r + scalar, g + scalar, b + scalar, a + scalar);
}

//------------------------------------------------------------------------------
Color Color::operator-(float scalar) const noexcept {
    return Color(r - scalar, g - scalar, b - scalar, a - scalar);
}

//------------------------------------------------------------------------------
Color Color::operator*(float scalar) const noexcept {
    return Color(r * scalar, g * scalar, b * scalar, a * scalar);
}

//------------------------------------------------------------------------------
Color Color::operator/(float scalar) const noexcept {
    return Color(r / scalar, g / scalar, b / scalar, a / scalar);
}

//------------------------------------------------------------------------------
Color Color::operator+(const Color& color) const noexcept {
    return Color(r + color.r, g + color.g, b + color.b, a + color.a);
}

//------------------------------------------------------------------------------
Color Color::operator-(const Color& color) const noexcept {
    return Color(r - color.r, g - color.g, b - color.b, a - color.a);
}

//------------------------------------------------------------------------------
Color Color::operator*(const Color& color) const noexcept {
    return Color(r * color.r, g * color.g, b * color.b, a * color.a);
}

//------------------------------------------------------------------------------
Color Color::operator/(const Color& color) const noexcept {
    return Color(r / color.r, g / color.g, b / color.b, a / color.a);
}

//------------------------------------------------------------------------------
bool Color::operator==(const Color& color) const noexcept {
    return r == color.r && g == color.g && b == color.b && a == color.a;
}

//------------------------------------------------------------------------------
bool Color::operator!=(const Color& color) const noexcept {
    return r != color.r || g != color.g || b != color.b || a != color.a;
}

//------------------------------------------------------------------------------
float Color::operator[](uint32_t index) noexcept {
    VNE_ASSERT_MSG(index < 4, "Color index out of bounds");
    return (&r)[index];
}

//------------------------------------------------------------------------------
float Color::operator[](uint32_t index) const noexcept {
    VNE_ASSERT_MSG(index < 4, "Color index out of bounds");
    return (&r)[index];
}

//------------------------------------------------------------------------------
void Color::Clamp() noexcept {
    r = r < 0.0f || vne::math::isNaN(r) ? 0.0f : r;
    r = r > kColorByteMax ? 1.0f : r > 1.0f ? r / kColorByteMax : r;

    g = g < 0.0f || vne::math::isNaN(g) ? 0.0f : g;
    g = g > kColorByteMax ? 1.0f : g > 1.0f ? g / kColorByteMax : g;

    b = b < 0.0f || vne::math::isNaN(b) ? 0.0f : b;
    b = b > kColorByteMax ? 1.0f : b > 1.0f ? b / kColorByteMax : b;

    a = a < 0.0f || vne::math::isNaN(a) ? 0.0f : a;
    a = a > 1.0f ? 1.0f : a;
}

//------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const Color& color) {
    return os << "[" << color.r << ", " << color.g << ", " << color.b << ", " << color.a << "]";
}

//------------------------------------------------------------------------------
std::istream& operator>>(std::istream& is, Color& color) {
    // Skip white spaces
    is.setf(std::ios_base::skipws);
    is.ignore(1);
    is >> color.r;
    is.ignore(1);
    is >> color.g;
    is.ignore(1);
    is >> color.b;
    is.ignore(1);
    // Since alpha is optional, check if it's there before parsing
    while (!is.eof() && std::isspace(is.peek())) {
        is.get();
    }
    if (!is.eof()) {
        is >> color.a;
    } else {
        color.a = 1.0f;
    }
    return is;
}

}  // namespace vne::math

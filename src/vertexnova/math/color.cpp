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

// Project includes
#include "vertexnova/math/color.h"
#include "vertexnova/math/math_utils.h"
#include "vertexnova/common/macros.h"

namespace VNE {
namespace Math {

const Color_C Color_C::WHITE = Color_C(1.0f, 1.0f, 1.0f);
const Color_C Color_C::BLACK = Color_C(0.0f, 0.0f, 0.0f);
const Color_C Color_C::RED = Color_C(1.0f, 0.0f, 0.0f);
const Color_C Color_C::GREEN = Color_C(0.0f, 1.0f, 0.0f);
const Color_C Color_C::BLUE = Color_C(0.0f, 0.0f, 1.0f);
const Color_C Color_C::YELLOW = Color_C(1.0f, 1.0f, 0.0f);
const Color_C Color_C::CYAN = Color_C(0.0f, 1.0f, 1.0f);
const Color_C Color_C::MAGENTA = Color_C(1.0f, 0.0f, 1.0f);
const Color_C Color_C::LIGHT_BLUE = Color_C(0.4f, 0.4f, 0.8f);
const Color_C Color_C::DARK_BLUE = Color_C(0.1f, 0.1f, 0.6f);
const Color_C Color_C::MAROON = Color_C(0.5f, 0.0f, 0.0f);
const Color_C Color_C::BEIGE = Color_C(0.96f, 0.96f, 0.862f);
const Color_C Color_C::BROWN = Color_C(0.647f, 0.164f, 0.164f);
const Color_C Color_C::GRAY = Color_C(0.5f, 0.5f, 0.5f);
const Color_C Color_C::GREY = Color_C(0.5f, 0.5f, 0.5f);

//------------------------------------------------------------------------------
Color_C::Color_C() {}

//------------------------------------------------------------------------------
Color_C::~Color_C() {}

//------------------------------------------------------------------------------
Color_C::Color_C(const float red, const float green, const float blue, const float alpha)
    : r(red)
    , g(green)
    , b(blue)
    , a(alpha) {
    Clamp();
}

//------------------------------------------------------------------------------
Color_C::Color_C(const Vec3f_C& rgb, float alpha)
    : r(rgb.r)
    , g(rgb.g)
    , b(rgb.b)
    , a(alpha) {
    Clamp();
}

//------------------------------------------------------------------------------
Color_C::Color_C(const Vec4f_C& rgba)
    : r(rgba.r)
    , g(rgba.g)
    , b(rgba.b)
    , a(rgba.a) {
    Clamp();
}

//------------------------------------------------------------------------------
Color_C::Color_C(const Color_C& rhs)
    : r(rhs.r)
    , g(rhs.g)
    , b(rhs.b)
    , a(rhs.a) {
    Clamp();
}

//------------------------------------------------------------------------------
Color_C& Color_C::operator=(const Color_C& rhs) {
    r = rhs.r;
    g = rhs.g;
    b = rhs.b;
    a = rhs.a;
    Clamp();

    return *this;
}

//------------------------------------------------------------------------------
float* Color_C::GetPtr() {
    return &r;
}

//------------------------------------------------------------------------------
const float* Color_C::GetPtr() const {
    return &r;
}

//------------------------------------------------------------------------------
bool Color_C::AreSame(const Color_C& color, float eps) const {
    return Math::AreSame(r, color.r, eps) && Math::AreSame(g, color.g, eps) && Math::AreSame(b, color.b, eps) && Math::AreSame(a, color.a, eps);
}

//------------------------------------------------------------------------------
bool Color_C::IsZero(float eps) const {
    return Math::IsZero(r, eps) && Math::IsZero(g, eps) && Math::IsZero(b, eps);
}

//------------------------------------------------------------------------------
Color_C Color_C::Lerp(const Color_C& color, float t) const {
    return Color_C(Math::Lerp(r, color.r, t), Math::Lerp(g, color.g, t), Math::Lerp(b, color.b, t), Math::Lerp(a, color.a, t));
}

//------------------------------------------------------------------------------
void Color_C::Reset() {
    r = 0.0f;
    g = 0.0f;
    b = 0.0f;
    a = 1.0f;
}

//------------------------------------------------------------------------------
void Color_C::Set(float red, float green, float blue, float alpha) {
    r = red;
    g = green;
    b = blue;
    a = alpha;
    Clamp();
}

//------------------------------------------------------------------------------
void Color_C::Set(const Vec3f_C& rgb, float alpha) {
    r = rgb.r;
    g = rgb.g;
    b = rgb.b;
    a = alpha;
    Clamp();
}

//------------------------------------------------------------------------------
void Color_C::Set(const Vec4f_C& rgba) {
    r = rgba.r;
    g = rgba.g;
    b = rgba.b;
    a = rgba.a;
    Clamp();
}

//------------------------------------------------------------------------------
float Color_C::R() const {
    return r;
}

//------------------------------------------------------------------------------
float Color_C::G() const {
    return g;
}

//------------------------------------------------------------------------------
float Color_C::B() const {
    return b;
}

//------------------------------------------------------------------------------
float Color_C::A() const {
    return a;
}

//------------------------------------------------------------------------------
Vec3f_C Color_C::RGB() const {
    return Vec3f_C(r, b, g);
}

//------------------------------------------------------------------------------
Vec4f_C Color_C::RGBA() const {
    return Vec4f_C(r, g, b, a);
}

//------------------------------------------------------------------------------
float& Color_C::R() {
    return r;
}

//------------------------------------------------------------------------------
float& Color_C::G() {
    return g;
}

//------------------------------------------------------------------------------
float& Color_C::B() {
    return b;
}

//------------------------------------------------------------------------------
float& Color_C::A() {
    return a;
}

//------------------------------------------------------------------------------
void Color_C::R(float red) {
    r = red;
}
//------------------------------------------------------------------------------
void Color_C::G(float green) {
    g = green;
}

//------------------------------------------------------------------------------
void Color_C::B(const float blue) {
    b = blue;
}

//------------------------------------------------------------------------------
void Color_C::A(const float alpha) {
    a = alpha;
}

//------------------------------------------------------------------------------
Color_C& Color_C::operator+=(float scalar) {
    r += scalar;
    g += scalar;
    b += scalar;
    a += scalar;
    Clamp();

    return *this;
}

//------------------------------------------------------------------------------
Color_C& Color_C::operator-=(float scalar) {
    r -= scalar;
    g -= scalar;
    b -= scalar;
    a -= scalar;
    Clamp();

    return *this;
}

//------------------------------------------------------------------------------
Color_C& Color_C::operator*=(float scalar) {
    r *= scalar;
    g *= scalar;
    b *= scalar;
    a *= scalar;
    Clamp();

    return *this;
}

//------------------------------------------------------------------------------
Color_C& Color_C::operator/=(float scalar) {
    r /= scalar;
    g /= scalar;
    b /= scalar;
    a /= scalar;
    Clamp();

    return *this;
}

//------------------------------------------------------------------------------
Color_C& Color_C::operator+=(const Color_C& color) {
    r += color.r;
    g += color.g;
    b += color.b;
    a += color.a;
    Clamp();

    return *this;
}

//------------------------------------------------------------------------------
Color_C& Color_C::operator-=(const Color_C& color) {
    r -= color.r;
    g -= color.g;
    b -= color.b;
    a -= color.a;
    Clamp();

    return *this;
}

//------------------------------------------------------------------------------
Color_C& Color_C::operator*=(const Color_C& color) {
    r *= color.r;
    g *= color.g;
    b *= color.b;
    a *= color.a;
    Clamp();

    return *this;
}

//------------------------------------------------------------------------------
Color_C& Color_C::operator/=(const Color_C& color) {
    r /= color.r;
    g /= color.g;
    b /= color.b;
    a /= color.a;
    Clamp();

    return *this;
}

//------------------------------------------------------------------------------
Color_C Color_C::operator+(float scalar) const {
    return Color_C(r + scalar, g + scalar, b + scalar, a + scalar);
}

//------------------------------------------------------------------------------
Color_C Color_C::operator-(float scalar) const {
    return Color_C(r - scalar, g - scalar, b - scalar, a - scalar);
}

//------------------------------------------------------------------------------
Color_C Color_C::operator*(float scalar) const {
    return Color_C(r * scalar, g * scalar, b * scalar, a * scalar);
}

//------------------------------------------------------------------------------
Color_C Color_C::operator/(float scalar) const {
    return Color_C(r / scalar, g / scalar, b / scalar, a / scalar);
}

//------------------------------------------------------------------------------
Color_C Color_C::operator+(const Color_C& color) const {
    return Color_C(r + color.r, g + color.g, b + color.b, a + color.a);
}

//------------------------------------------------------------------------------
Color_C Color_C::operator-(const Color_C& color) const {
    return Color_C(r - color.r, g - color.g, b - color.b, a - color.a);
}

//------------------------------------------------------------------------------
Color_C Color_C::operator*(const Color_C& color) const {
    return Color_C(r * color.r, g * color.g, b * color.b, a * color.a);
}

//------------------------------------------------------------------------------
Color_C Color_C::operator/(const Color_C& color) const {
    return Color_C(r / color.r, g / color.g, b / color.b, a / color.a);
}

//------------------------------------------------------------------------------
bool Color_C::operator==(const Color_C& color) const {
    return r == color.r && g == color.g && b == color.b && a == color.a;
}

//------------------------------------------------------------------------------
bool Color_C::operator!=(const Color_C& color) const {
    return r != color.r || g != color.g || b != color.b || a != color.a;
}

//------------------------------------------------------------------------------
float Color_C::operator[](uint32_t index) {
    VNE_ASSERT_MSG(index < 4, "Color_C index out of bounds");
    return (&r)[index];
}

//------------------------------------------------------------------------------
float Color_C::operator[](uint32_t index) const {
    VNE_ASSERT_MSG(index < 4, "Color_C index out of bounds");
    return (&r)[index];
}

//------------------------------------------------------------------------------
void Color_C::Clamp() {
    r = r < 0.0f || Math::IsNaN(r) ? 0.0f : r;
    r = r > 255.0f ? 1.0f : r > 1.0f ? r / 255.0f : r;

    g = g < 0.0f || Math::IsNaN(g) ? 0.0f : g;
    g = g > 255.0f ? 1.0f : g > 1.0f ? g / 255.0f : g;

    b = b < 0.0f || Math::IsNaN(b) ? 0.0f : b;
    b = b > 255.0f ? 1.0f : b > 1.0f ? b / 255.0f : b;

    a = a < 0.0f || Math::IsNaN(a) ? 0.0f : a;
    a = a > 1.0f ? 1.0f : a;
}

//------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const Color_C& color) {
    return os << "[" << color.r << ", " << color.g << ", " << color.b << ", " << color.a << "]";
}

//------------------------------------------------------------------------------
std::istream& operator>>(std::istream& is, Color_C& color) {
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

}  // namespace Math
}  // namespace VNE

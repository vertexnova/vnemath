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

const Color Color::kWhite = Color(1.0f, 1.0f, 1.0f);
const Color Color::kBlack = Color(0.0f, 0.0f, 0.0f);
const Color Color::kRed = Color(1.0f, 0.0f, 0.0f);
const Color Color::kGreen = Color(0.0f, 1.0f, 0.0f);
const Color Color::kBlue = Color(0.0f, 0.0f, 1.0f);
const Color Color::kYellow = Color(1.0f, 1.0f, 0.0f);
const Color Color::kCyan = Color(0.0f, 1.0f, 1.0f);
const Color Color::kMagenta = Color(1.0f, 0.0f, 1.0f);
const Color Color::kLightBlue = Color(0.4f, 0.4f, 0.8f);
const Color Color::kDarkBlue = Color(0.1f, 0.1f, 0.6f);
const Color Color::kMaroon = Color(0.5f, 0.0f, 0.0f);
const Color Color::kBeige = Color(0.96f, 0.96f, 0.862f);
const Color Color::kBrown = Color(0.647f, 0.164f, 0.164f);
const Color Color::kGray = Color(0.5f, 0.5f, 0.5f);
const Color Color::kGrey = Color(0.5f, 0.5f, 0.5f);

//------------------------------------------------------------------------------
Color::Color() noexcept {}

//------------------------------------------------------------------------------
Color::Color(const float red, const float green, const float blue, const float alpha) noexcept
    : r_(red)
    , g_(green)
    , b_(blue)
    , a_(alpha) {
    clamp();
}

//------------------------------------------------------------------------------
Color::Color(const Vec3f& rgb, float alpha) noexcept
    : r_(rgb.r)
    , g_(rgb.g)
    , b_(rgb.b)
    , a_(alpha) {
    clamp();
}

//------------------------------------------------------------------------------
Color::Color(const Vec4f& rgba) noexcept
    : r_(rgba.r)
    , g_(rgba.g)
    , b_(rgba.b)
    , a_(rgba.a) {
    clamp();
}

//------------------------------------------------------------------------------
Color::Color(const Color& rhs) noexcept
    : r_(rhs.r_)
    , g_(rhs.g_)
    , b_(rhs.b_)
    , a_(rhs.a_) {
    clamp();
}

//------------------------------------------------------------------------------
Color& Color::operator=(const Color& rhs) noexcept {
    r_ = rhs.r_;
    g_ = rhs.g_;
    b_ = rhs.b_;
    a_ = rhs.a_;
    clamp();

    return *this;
}

//------------------------------------------------------------------------------
float* Color::getPtr() noexcept {
    return &r_;
}

//------------------------------------------------------------------------------
const float* Color::getPtr() const noexcept {
    return &r_;
}

//------------------------------------------------------------------------------
bool Color::areSame(const Color& color, float eps) const noexcept {
    return vne::math::areSame(r_, color.r_, eps) && vne::math::areSame(g_, color.g_, eps)
           && vne::math::areSame(b_, color.b_, eps) && vne::math::areSame(a_, color.a_, eps);
}

//------------------------------------------------------------------------------
bool Color::isZero(float eps) const noexcept {
    return vne::math::isZero(r_, eps) && vne::math::isZero(g_, eps) && vne::math::isZero(b_, eps);
}

//------------------------------------------------------------------------------
Color Color::lerp(const Color& color, float t) const noexcept {
    return Color(vne::math::lerp(r_, color.r_, t),
                 vne::math::lerp(g_, color.g_, t),
                 vne::math::lerp(b_, color.b_, t),
                 vne::math::lerp(a_, color.a_, t));
}

//------------------------------------------------------------------------------
void Color::reset() noexcept {
    r_ = 0.0f;
    g_ = 0.0f;
    b_ = 0.0f;
    a_ = 1.0f;
}

//------------------------------------------------------------------------------
void Color::set(float red, float green, float blue, float alpha) noexcept {
    r_ = red;
    g_ = green;
    b_ = blue;
    a_ = alpha;
    clamp();
}

//------------------------------------------------------------------------------
void Color::set(const Vec3f& rgb, float alpha) noexcept {
    r_ = rgb.r;
    g_ = rgb.g;
    b_ = rgb.b;
    a_ = alpha;
    clamp();
}

//------------------------------------------------------------------------------
void Color::set(const Vec4f& rgba) noexcept {
    r_ = rgba.r;
    g_ = rgba.g;
    b_ = rgba.b;
    a_ = rgba.a;
    clamp();
}

//------------------------------------------------------------------------------
float Color::r() const noexcept {
    return r_;
}

//------------------------------------------------------------------------------
float Color::g() const noexcept {
    return g_;
}

//------------------------------------------------------------------------------
float Color::b() const noexcept {
    return b_;
}

//------------------------------------------------------------------------------
float Color::a() const noexcept {
    return a_;
}

//------------------------------------------------------------------------------
Vec3f Color::rgb() const noexcept {
    return {r_, b_, g_};
}

//------------------------------------------------------------------------------
Vec4f Color::rgba() const noexcept {
    return {r_, g_, b_, a_};
}

//------------------------------------------------------------------------------
float& Color::r() noexcept {
    return r_;
}

//------------------------------------------------------------------------------
float& Color::g() noexcept {
    return g_;
}

//------------------------------------------------------------------------------
float& Color::b() noexcept {
    return b_;
}

//------------------------------------------------------------------------------
float& Color::a() noexcept {
    return a_;
}

//------------------------------------------------------------------------------
void Color::setR(float red) noexcept {
    r_ = red;
}
//------------------------------------------------------------------------------
void Color::setG(float green) noexcept {
    g_ = green;
}

//------------------------------------------------------------------------------
void Color::setB(const float blue) noexcept {
    b_ = blue;
}

//------------------------------------------------------------------------------
void Color::setA(const float alpha) noexcept {
    a_ = alpha;
}

//------------------------------------------------------------------------------
Color& Color::operator+=(float scalar) noexcept {
    r_ += scalar;
    g_ += scalar;
    b_ += scalar;
    a_ += scalar;
    clamp();

    return *this;
}

//------------------------------------------------------------------------------
Color& Color::operator-=(float scalar) noexcept {
    r_ -= scalar;
    g_ -= scalar;
    b_ -= scalar;
    a_ -= scalar;
    clamp();

    return *this;
}

//------------------------------------------------------------------------------
Color& Color::operator*=(float scalar) noexcept {
    r_ *= scalar;
    g_ *= scalar;
    b_ *= scalar;
    a_ *= scalar;
    clamp();

    return *this;
}

//------------------------------------------------------------------------------
Color& Color::operator/=(float scalar) noexcept {
    r_ /= scalar;
    g_ /= scalar;
    b_ /= scalar;
    a_ /= scalar;
    clamp();

    return *this;
}

//------------------------------------------------------------------------------
Color& Color::operator+=(const Color& color) noexcept {
    r_ += color.r_;
    g_ += color.g_;
    b_ += color.b_;
    a_ += color.a_;
    clamp();

    return *this;
}

//------------------------------------------------------------------------------
Color& Color::operator-=(const Color& color) noexcept {
    r_ -= color.r_;
    g_ -= color.g_;
    b_ -= color.b_;
    a_ -= color.a_;
    clamp();

    return *this;
}

//------------------------------------------------------------------------------
Color& Color::operator*=(const Color& color) noexcept {
    r_ *= color.r_;
    g_ *= color.g_;
    b_ *= color.b_;
    a_ *= color.a_;
    clamp();

    return *this;
}

//------------------------------------------------------------------------------
Color& Color::operator/=(const Color& color) noexcept {
    r_ /= color.r_;
    g_ /= color.g_;
    b_ /= color.b_;
    a_ /= color.a_;
    clamp();

    return *this;
}

//------------------------------------------------------------------------------
Color Color::operator+(float scalar) const noexcept {
    return Color(r_ + scalar, g_ + scalar, b_ + scalar, a_ + scalar);
}

//------------------------------------------------------------------------------
Color Color::operator-(float scalar) const noexcept {
    return Color(r_ - scalar, g_ - scalar, b_ - scalar, a_ - scalar);
}

//------------------------------------------------------------------------------
Color Color::operator*(float scalar) const noexcept {
    return Color(r_ * scalar, g_ * scalar, b_ * scalar, a_ * scalar);
}

//------------------------------------------------------------------------------
Color Color::operator/(float scalar) const noexcept {
    return Color(r_ / scalar, g_ / scalar, b_ / scalar, a_ / scalar);
}

//------------------------------------------------------------------------------
Color Color::operator+(const Color& color) const noexcept {
    return Color(r_ + color.r_, g_ + color.g_, b_ + color.b_, a_ + color.a_);
}

//------------------------------------------------------------------------------
Color Color::operator-(const Color& color) const noexcept {
    return Color(r_ - color.r_, g_ - color.g_, b_ - color.b_, a_ - color.a_);
}

//------------------------------------------------------------------------------
Color Color::operator*(const Color& color) const noexcept {
    return Color(r_ * color.r_, g_ * color.g_, b_ * color.b_, a_ * color.a_);
}

//------------------------------------------------------------------------------
Color Color::operator/(const Color& color) const noexcept {
    return Color(r_ / color.r_, g_ / color.g_, b_ / color.b_, a_ / color.a_);
}

//------------------------------------------------------------------------------
bool Color::operator==(const Color& color) const noexcept {
    return r_ == color.r_ && g_ == color.g_ && b_ == color.b_ && a_ == color.a_;
}

//------------------------------------------------------------------------------
bool Color::operator!=(const Color& color) const noexcept {
    return r_ != color.r_ || g_ != color.g_ || b_ != color.b_ || a_ != color.a_;
}

//------------------------------------------------------------------------------
float Color::operator[](uint32_t index) noexcept {
    VNE_ASSERT_MSG(index < 4, "Color index out of bounds");
    return (&r_)[index];
}

//------------------------------------------------------------------------------
float Color::operator[](uint32_t index) const noexcept {
    VNE_ASSERT_MSG(index < 4, "Color index out of bounds");
    return (&r_)[index];
}

//------------------------------------------------------------------------------
void Color::clamp() noexcept {
    r_ = r_ < 0.0f || vne::math::isNaN(r_) ? 0.0f : r_;
    r_ = r_ > kColorByteMax ? 1.0f : r_ > 1.0f ? r_ / kColorByteMax : r_;

    g_ = g_ < 0.0f || vne::math::isNaN(g_) ? 0.0f : g_;
    g_ = g_ > kColorByteMax ? 1.0f : g_ > 1.0f ? g_ / kColorByteMax : g_;

    b_ = b_ < 0.0f || vne::math::isNaN(b_) ? 0.0f : b_;
    b_ = b_ > kColorByteMax ? 1.0f : b_ > 1.0f ? b_ / kColorByteMax : b_;

    a_ = a_ < 0.0f || vne::math::isNaN(a_) ? 0.0f : a_;
    a_ = a_ > 1.0f ? 1.0f : a_;
}

//------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const Color& color) {
    return os << "[" << color.r_ << ", " << color.g_ << ", " << color.b_ << ", " << color.a_ << "]";
}

//------------------------------------------------------------------------------
std::istream& operator>>(std::istream& is, Color& color) {
    // Skip white spaces
    is.setf(std::ios_base::skipws);
    is.ignore(1);
    is >> color.r_;
    is.ignore(1);
    is >> color.g_;
    is.ignore(1);
    is >> color.b_;
    is.ignore(1);
    // Since alpha is optional, check if it's there before parsing
    while (!is.eof() && std::isspace(is.peek())) {
        is.get();
    }
    if (!is.eof()) {
        is >> color.a_;
    } else {
        color.a_ = 1.0f;
    }
    return is;
}

}  // namespace vne::math

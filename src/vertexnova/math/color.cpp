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
#include "vertexnova/math/core/math_utils.h"

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
    : r_(rgb.x())
    , g_(rgb.y())
    , b_(rgb.z())
    , a_(alpha) {
    clamp();
}

//------------------------------------------------------------------------------
Color::Color(const Vec4f& rgba) noexcept
    : r_(rgba.x())
    , g_(rgba.y())
    , b_(rgba.z())
    , a_(rgba.w()) {
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
    return {vne::math::lerp(r_, color.r_, t),
            vne::math::lerp(g_, color.g_, t),
            vne::math::lerp(b_, color.b_, t),
            vne::math::lerp(a_, color.a_, t)};
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
    r_ = rgb.x();
    g_ = rgb.y();
    b_ = rgb.z();
    a_ = alpha;
    clamp();
}

//------------------------------------------------------------------------------
void Color::set(const Vec4f& rgba) noexcept {
    r_ = rgba.x();
    g_ = rgba.y();
    b_ = rgba.z();
    a_ = rgba.w();
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
    return {r_ + scalar, g_ + scalar, b_ + scalar, a_ + scalar};
}

//------------------------------------------------------------------------------
Color Color::operator-(float scalar) const noexcept {
    return {r_ - scalar, g_ - scalar, b_ - scalar, a_ - scalar};
}

//------------------------------------------------------------------------------
Color Color::operator*(float scalar) const noexcept {
    return {r_ * scalar, g_ * scalar, b_ * scalar, a_ * scalar};
}

//------------------------------------------------------------------------------
Color Color::operator/(float scalar) const noexcept {
    return {r_ / scalar, g_ / scalar, b_ / scalar, a_ / scalar};
}

//------------------------------------------------------------------------------
Color Color::operator+(const Color& color) const noexcept {
    return {r_ + color.r_, g_ + color.g_, b_ + color.b_, a_ + color.a_};
}

//------------------------------------------------------------------------------
Color Color::operator-(const Color& color) const noexcept {
    return {r_ - color.r_, g_ - color.g_, b_ - color.b_, a_ - color.a_};
}

//------------------------------------------------------------------------------
Color Color::operator*(const Color& color) const noexcept {
    return {r_ * color.r_, g_ * color.g_, b_ * color.b_, a_ * color.a_};
}

//------------------------------------------------------------------------------
Color Color::operator/(const Color& color) const noexcept {
    return {r_ / color.r_, g_ / color.g_, b_ / color.b_, a_ / color.a_};
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

//------------------------------------------------------------------------------
// Color Space Conversions
//------------------------------------------------------------------------------

namespace {
// sRGB gamma constants
constexpr float kSRGBLinearThreshold = 0.04045f;
constexpr float kSRGBLinearScale = 12.92f;
constexpr float kSRGBGammaOffset = 0.055f;
constexpr float kSRGBGammaScale = 1.055f;
constexpr float kSRGBGamma = 2.4f;

// ITU-R BT.709 luminance coefficients
constexpr float kLuminanceR = 0.2126f;
constexpr float kLuminanceG = 0.7152f;
constexpr float kLuminanceB = 0.0722f;

// Helper: sRGB to linear for a single component
inline float srgbToLinearComponent(float c) {
    if (c <= kSRGBLinearThreshold) {
        return c / kSRGBLinearScale;
    }
    return std::pow((c + kSRGBGammaOffset) / kSRGBGammaScale, kSRGBGamma);
}

// Helper: linear to sRGB for a single component
inline float linearToSrgbComponent(float c) {
    if (c <= 0.0031308f) {
        return c * kSRGBLinearScale;
    }
    return kSRGBGammaScale * std::pow(c, 1.0f / kSRGBGamma) - kSRGBGammaOffset;
}

// Helper: HSL to RGB conversion helper
inline float hslToRgbHelper(float p, float q, float t) {
    if (t < 0.0f)
        t += 1.0f;
    if (t > 1.0f)
        t -= 1.0f;
    if (t < 1.0f / 6.0f)
        return p + (q - p) * 6.0f * t;
    if (t < 0.5f)
        return q;
    if (t < 2.0f / 3.0f)
        return p + (q - p) * (2.0f / 3.0f - t) * 6.0f;
    return p;
}
}  // namespace

//------------------------------------------------------------------------------
Color Color::fromHSV(float h, float s, float v, float a) noexcept {
    // Normalize hue to [0, 360)
    h = std::fmod(h, 360.0f);
    if (h < 0.0f)
        h += 360.0f;

    s = vne::math::clamp(s, 0.0f, 1.0f);
    v = vne::math::clamp(v, 0.0f, 1.0f);

    float c = v * s;  // Chroma
    float x = c * (1.0f - std::abs(std::fmod(h / 60.0f, 2.0f) - 1.0f));
    float m = v - c;

    float r = 0.0f, g = 0.0f, b = 0.0f;

    if (h < 60.0f) {
        r = c;
        g = x;
        b = 0.0f;
    } else if (h < 120.0f) {
        r = x;
        g = c;
        b = 0.0f;
    } else if (h < 180.0f) {
        r = 0.0f;
        g = c;
        b = x;
    } else if (h < 240.0f) {
        r = 0.0f;
        g = x;
        b = c;
    } else if (h < 300.0f) {
        r = x;
        g = 0.0f;
        b = c;
    } else {
        r = c;
        g = 0.0f;
        b = x;
    }

    return {r + m, g + m, b + m, a};
}

//------------------------------------------------------------------------------
Color Color::fromHSL(float h, float s, float l, float a) noexcept {
    // Normalize hue to [0, 360)
    h = std::fmod(h, 360.0f);
    if (h < 0.0f)
        h += 360.0f;

    s = vne::math::clamp(s, 0.0f, 1.0f);
    l = vne::math::clamp(l, 0.0f, 1.0f);

    if (vne::math::isZero(s)) {
        // Achromatic (gray)
        return {l, l, l, a};
    }

    float q = l < 0.5f ? l * (1.0f + s) : l + s - l * s;
    float p = 2.0f * l - q;
    float h_norm = h / 360.0f;

    float r = hslToRgbHelper(p, q, h_norm + 1.0f / 3.0f);
    float g = hslToRgbHelper(p, q, h_norm);
    float b = hslToRgbHelper(p, q, h_norm - 1.0f / 3.0f);

    return {r, g, b, a};
}

//------------------------------------------------------------------------------
Vec3f Color::toHSV() const noexcept {
    float max_val = vne::math::max(r_, vne::math::max(g_, b_));
    float min_val = vne::math::min(r_, vne::math::min(g_, b_));
    float delta = max_val - min_val;

    float h = 0.0f;
    float s = 0.0f;
    float v = max_val;

    if (!vne::math::isZero(delta)) {
        s = delta / max_val;

        if (vne::math::areSame(r_, max_val)) {
            h = 60.0f * std::fmod((g_ - b_) / delta, 6.0f);
        } else if (vne::math::areSame(g_, max_val)) {
            h = 60.0f * ((b_ - r_) / delta + 2.0f);
        } else {
            h = 60.0f * ((r_ - g_) / delta + 4.0f);
        }

        if (h < 0.0f)
            h += 360.0f;
    }

    return {h, s, v};
}

//------------------------------------------------------------------------------
Vec3f Color::toHSL() const noexcept {
    float max_val = vne::math::max(r_, vne::math::max(g_, b_));
    float min_val = vne::math::min(r_, vne::math::min(g_, b_));
    float delta = max_val - min_val;

    float h = 0.0f;
    float s = 0.0f;
    float l = (max_val + min_val) * 0.5f;

    if (!vne::math::isZero(delta)) {
        s = l > 0.5f ? delta / (2.0f - max_val - min_val) : delta / (max_val + min_val);

        if (vne::math::areSame(r_, max_val)) {
            h = 60.0f * std::fmod((g_ - b_) / delta, 6.0f);
        } else if (vne::math::areSame(g_, max_val)) {
            h = 60.0f * ((b_ - r_) / delta + 2.0f);
        } else {
            h = 60.0f * ((r_ - g_) / delta + 4.0f);
        }

        if (h < 0.0f)
            h += 360.0f;
    }

    return {h, s, l};
}

//------------------------------------------------------------------------------
Color Color::toLinear() const noexcept {
    return {srgbToLinearComponent(r_), srgbToLinearComponent(g_), srgbToLinearComponent(b_), a_};
}

//------------------------------------------------------------------------------
Color Color::toSRGB() const noexcept {
    return {linearToSrgbComponent(r_), linearToSrgbComponent(g_), linearToSrgbComponent(b_), a_};
}

//------------------------------------------------------------------------------
Color Color::gammaCorrect(float gamma) const noexcept {
    float inv_gamma = 1.0f / gamma;
    return {std::pow(r_, inv_gamma), std::pow(g_, inv_gamma), std::pow(b_, inv_gamma), a_};
}

//------------------------------------------------------------------------------
float Color::luminance() const noexcept {
    return kLuminanceR * r_ + kLuminanceG * g_ + kLuminanceB * b_;
}

//------------------------------------------------------------------------------
Color Color::grayscale() const noexcept {
    float lum = luminance();
    return {lum, lum, lum, a_};
}

//------------------------------------------------------------------------------
Color Color::inverted() const noexcept {
    return {1.0f - r_, 1.0f - g_, 1.0f - b_, a_};
}

}  // namespace vne::math

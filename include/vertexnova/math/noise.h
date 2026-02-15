/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Noise functions for procedural generation.
 * Includes Perlin noise, Simplex noise, and Fractal Brownian Motion.
 * ----------------------------------------------------------------------
 */

#pragma once

#include "core/types.h"
#include "core/vec.h"

#include <array>
#include <cmath>

namespace vne::math {

// ============================================================================
// Internal Helpers
// ============================================================================

namespace detail {

// Permutation table for noise generation
inline constexpr std::array<uint8_t, 512> kPermutation = {
    151, 160, 137, 91, 90, 15, 131, 13,
    201, 95, 96, 53, 194, 233, 7, 225,
    140, 36, 103, 30, 69, 142, 8, 99,
    37, 240, 21, 10, 23, 190, 6, 148,
    247,
                                                          120,
                                                          234,
                                                          75,
                                                          0,
                                                          26,
                                                          197,
                                                          62,
                                                          94,
                                                          252,
                                                          219,
                                                          203,
                                                          117,
                                                          35,
                                                          11,
                                                          32,
                                                          57,
                                                          177,
                                                          33,
                                                          88,
                                                          237,
                                                          149,
                                                          56,
                                                          87,
                                                          174,
                                                          20,
                                                          125,
                                                          136,
                                                          171,
                                                          168,
                                                          68,
                                                          175,
                                                          74,
                                                          165,
                                                          71,
                                                          134,
                                                          139,
                                                          48,
                                                          27,
                                                          166,
                                                          77,
                                                          146,
                                                          158,
                                                          231,
                                                          83,
                                                          111,
                                                          229,
                                                          122,
                                                          60,
                                                          211,
                                                          133,
                                                          230,
                                                          220,
                                                          105,
                                                          92,
                                                          41,
                                                          55,
                                                          46,
                                                          245,
                                                          40,
                                                          244,
                                                          102,
                                                          143,
                                                          54,
                                                          65,
                                                          25,
                                                          63,
                                                          161,
                                                          1,
                                                          216,
                                                          80,
                                                          73,
                                                          209,
                                                          76,
                                                          132,
                                                          187,
                                                          208,
                                                          89,
                                                          18,
                                                          169,
                                                          200,
                                                          196,
                                                          135,
                                                          130,
                                                          116,
                                                          188,
                                                          159,
                                                          86,
                                                          164,
                                                          100,
                                                          109,
                                                          198,
                                                          173,
                                                          186,
                                                          3,
                                                          64,
                                                          52,
                                                          217,
                                                          226,
                                                          250,
                                                          124,
                                                          123,
                                                          5,
                                                          202,
                                                          38,
                                                          147,
                                                          118,
                                                          126,
                                                          255,
                                                          82,
                                                          85,
                                                          212,
                                                          207,
                                                          206,
                                                          59,
                                                          227,
                                                          47,
                                                          16,
                                                          58,
                                                          17,
                                                          182,
                                                          189,
                                                          28,
                                                          42,
                                                          223,
                                                          183,
                                                          170,
                                                          213,
                                                          119,
                                                          248,
                                                          152,
                                                          2,
                                                          44,
                                                          154,
                                                          163,
                                                          70,
                                                          221,
                                                          153,
                                                          101,
                                                          155,
                                                          167,
                                                          43,
                                                          172,
                                                          9,
                                                          129,
                                                          22,
                                                          39,
                                                          253,
                                                          19,
                                                          98,
                                                          108,
                                                          110,
                                                          79,
                                                          113,
                                                          224,
                                                          232,
                                                          178,
                                                          185,
                                                          112,
                                                          104,
                                                          218,
                                                          246,
                                                          97,
                                                          228,
                                                          251,
                                                          34,
                                                          242,
                                                          193,
                                                          238,
                                                          210,
                                                          144,
                                                          12,
                                                          191,
                                                          179,
                                                          162,
                                                          241,
                                                          81,
                                                          51,
                                                          145,
                                                          235,
                                                          249,
                                                          14,
                                                          239,
                                                          107,
                                                          49,
                                                          192,
                                                          214,
                                                          31,
                                                          181,
                                                          199,
                                                          106,
                                                          157,
                                                          184,
                                                          84,
                                                          204,
                                                          176,
                                                          115,
                                                          121,
                                                          50,
                                                          45,
                                                          127,
                                                          4,
                                                          150,
                                                          254,
                                                          138,
                                                          236,
                                                          205,
                                                          93,
                                                          222,
                                                          114,
                                                          67,
                                                          29,
                                                          24,
                                                          72,
                                                          243,
                                                          141,
                                                          128,
                                                          195,
                                                          78,
                                                          66,
                                                          215,
                                                          61,
                                                          156,
                                                          180,
                                                          // Repeat the table
                                                          151,
                                                          160,
                                                          137,
                                                          91,
                                                          90,
                                                          15,
                                                          131,
                                                          13,
                                                          201,
                                                          95,
                                                          96,
                                                          53,
                                                          194,
                                                          233,
                                                          7,
                                                          225,
                                                          140,
                                                          36,
                                                          103,
                                                          30,
                                                          69,
                                                          142,
                                                          8,
                                                          99,
                                                          37,
                                                          240,
                                                          21,
                                                          10,
                                                          23,
                                                          190,
                                                          6,
                                                          148,
                                                          247,
                                                          120,
                                                          234,
                                                          75,
                                                          0,
                                                          26,
                                                          197,
                                                          62,
                                                          94,
                                                          252,
                                                          219,
                                                          203,
                                                          117,
                                                          35,
                                                          11,
                                                          32,
                                                          57,
                                                          177,
                                                          33,
                                                          88,
                                                          237,
                                                          149,
                                                          56,
                                                          87,
                                                          174,
                                                          20,
                                                          125,
                                                          136,
                                                          171,
                                                          168,
                                                          68,
                                                          175,
                                                          74,
                                                          165,
                                                          71,
                                                          134,
                                                          139,
                                                          48,
                                                          27,
                                                          166,
                                                          77,
                                                          146,
                                                          158,
                                                          231,
                                                          83,
                                                          111,
                                                          229,
                                                          122,
                                                          60,
                                                          211,
                                                          133,
                                                          230,
                                                          220,
                                                          105,
                                                          92,
                                                          41,
                                                          55,
                                                          46,
                                                          245,
                                                          40,
                                                          244,
                                                          102,
                                                          143,
                                                          54,
                                                          65,
                                                          25,
                                                          63,
                                                          161,
                                                          1,
                                                          216,
                                                          80,
                                                          73,
                                                          209,
                                                          76,
                                                          132,
                                                          187,
                                                          208,
                                                          89,
                                                          18,
                                                          169,
                                                          200,
                                                          196,
                                                          135,
                                                          130,
                                                          116,
                                                          188,
                                                          159,
                                                          86,
                                                          164,
                                                          100,
                                                          109,
                                                          198,
                                                          173,
                                                          186,
                                                          3,
                                                          64,
                                                          52,
                                                          217,
                                                          226,
                                                          250,
                                                          124,
                                                          123,
                                                          5,
                                                          202,
                                                          38,
                                                          147,
                                                          118,
                                                          126,
                                                          255,
                                                          82,
                                                          85,
                                                          212,
                                                          207,
                                                          206,
                                                          59,
                                                          227,
                                                          47,
                                                          16,
                                                          58,
                                                          17,
                                                          182,
                                                          189,
                                                          28,
                                                          42,
                                                          223,
                                                          183,
                                                          170,
                                                          213,
                                                          119,
                                                          248,
                                                          152,
                                                          2,
                                                          44,
                                                          154,
                                                          163,
                                                          70,
                                                          221,
                                                          153,
                                                          101,
                                                          155,
                                                          167,
                                                          43,
                                                          172,
                                                          9,
                                                          129,
                                                          22,
                                                          39,
                                                          253,
                                                          19,
                                                          98,
                                                          108,
                                                          110,
                                                          79,
                                                          113,
                                                          224,
                                                          232,
                                                          178,
                                                          185,
                                                          112,
                                                          104,
                                                          218,
                                                          246,
                                                          97,
                                                          228,
                                                          251,
                                                          34,
                                                          242,
                                                          193,
                                                          238,
                                                          210,
                                                          144,
                                                          12,
                                                          191,
                                                          179,
                                                          162,
                                                          241,
                                                          81,
                                                          51,
                                                          145,
                                                          235,
                                                          249,
                                                          14,
                                                          239,
                                                          107,
                                                          49,
                                                          192,
                                                          214,
                                                          31,
                                                          181,
                                                          199,
                                                          106,
                                                          157,
                                                          184,
                                                          84,
                                                          204,
                                                          176,
                                                          115,
                                                          121,
                                                          50,
                                                          45,
                                                          127,
                                                          4,
                                                          150,
                                                          254,
                                                          138,
                                                          236,
                                                          205,
                                                          93,
                                                          222,
                                                          114,
                                                          67,
                                                          29,
                                                          24,
                                                          72,
                                                          243,
                                                          141,
                                                          128,
                                                          195,
                                                          78,
                                                          66,
                                                          215,
                                                          61,
                                                          156,
                                                          180};

// Fade function for Perlin noise (smootherstep)
[[nodiscard]] inline constexpr float fade(float t) noexcept {
    return t * t * t * (t * (t * 6.0f - 15.0f) + 10.0f);
}

// Gradient function for 1D Perlin
[[nodiscard]] inline constexpr float grad1(int hash, float x) noexcept {
    return (hash & 1) ? -x : x;
}

// Gradient function for 2D Perlin
[[nodiscard]] inline constexpr float grad2(int hash, float x, float y) noexcept {
    int h = hash & 3;
    float u = h < 2 ? x : y;
    float v = h < 2 ? y : x;
    return ((h & 1) ? -u : u) + ((h & 2) ? -v : v);
}

// Gradient function for 3D Perlin
[[nodiscard]] inline constexpr float grad3(int hash, float x, float y, float z) noexcept {
    int h = hash & 15;
    float u = h < 8 ? x : y;
    float v = h < 4 ? y : (h == 12 || h == 14 ? x : z);
    return ((h & 1) ? -u : u) + ((h & 2) ? -v : v);
}

// Fast floor
[[nodiscard]] inline int fastFloor(float x) noexcept {
    int xi = static_cast<int>(x);
    return x < xi ? xi - 1 : xi;
}

// Safe permutation table access (handles int to size_t conversion)
[[nodiscard]] inline constexpr int perm(int index) noexcept {
    return static_cast<int>(kPermutation[static_cast<size_t>(index)]);
}

}  // namespace detail

// ============================================================================
// Perlin Noise
// ============================================================================

/**
 * @brief 1D Perlin noise.
 *
 * @param x Input coordinate
 * @return Noise value in approximately [-1, 1)
 */
[[nodiscard]] inline float perlin(float x) noexcept {
    int X = detail::fastFloor(x) & 255;
    x -= std::floor(x);
    float u = detail::fade(x);

    int a = detail::perm(X);
    int b = detail::perm(X + 1);

    return lerp(detail::grad1(a, x), detail::grad1(b, x - 1.0f), u);
}

/**
 * @brief 2D Perlin noise.
 *
 * @param x X coordinate
 * @param y Y coordinate
 * @return Noise value in approximately [-1, 1)
 */
[[nodiscard]] inline float perlin(float x, float y) noexcept {
    int X = detail::fastFloor(x) & 255;
    int Y = detail::fastFloor(y) & 255;

    x -= std::floor(x);
    y -= std::floor(y);

    float u = detail::fade(x);
    float v = detail::fade(y);

    int aa = detail::perm(detail::perm(X) + Y);
    int ab = detail::perm(detail::perm(X) + Y + 1);
    int ba = detail::perm(detail::perm(X + 1) + Y);
    int bb = detail::perm(detail::perm(X + 1) + Y + 1);

    float x1 = lerp(detail::grad2(aa, x, y), detail::grad2(ba, x - 1.0f, y), u);
    float x2 = lerp(detail::grad2(ab, x, y - 1.0f), detail::grad2(bb, x - 1.0f, y - 1.0f), u);

    return lerp(x1, x2, v);
}

/**
 * @brief 2D Perlin noise with Vec2f input.
 */
[[nodiscard]] inline float perlin(const Vec2f& p) noexcept {
    return perlin(p.x(), p.y());
}

/**
 * @brief 3D Perlin noise.
 *
 * @param x X coordinate
 * @param y Y coordinate
 * @param z Z coordinate
 * @return Noise value in approximately [-1, 1)
 */
[[nodiscard]] inline float perlin(float x, float y, float z) noexcept {
    int X = detail::fastFloor(x) & 255;
    int Y = detail::fastFloor(y) & 255;
    int Z = detail::fastFloor(z) & 255;

    x -= std::floor(x);
    y -= std::floor(y);
    z -= std::floor(z);

    float u = detail::fade(x);
    float v = detail::fade(y);
    float w = detail::fade(z);

    int A = detail::perm(X) + Y;
    int AA = detail::perm(A) + Z;
    int AB = detail::perm(A + 1) + Z;
    int B = detail::perm(X + 1) + Y;
    int BA = detail::perm(B) + Z;
    int BB = detail::perm(B + 1) + Z;

    float x1 = lerp(detail::grad3(detail::perm(AA), x, y, z), detail::grad3(detail::perm(BA), x - 1.0f, y, z), u);
    float x2 = lerp(detail::grad3(detail::perm(AB), x, y - 1.0f, z),
                    detail::grad3(detail::perm(BB), x - 1.0f, y - 1.0f, z),
                    u);
    float y1 = lerp(x1, x2, v);

    float x3 = lerp(detail::grad3(detail::perm(AA + 1), x, y, z - 1.0f),
                    detail::grad3(detail::perm(BA + 1), x - 1.0f, y, z - 1.0f),
                    u);
    float x4 = lerp(detail::grad3(detail::perm(AB + 1), x, y - 1.0f, z - 1.0f),
                    detail::grad3(detail::perm(BB + 1), x - 1.0f, y - 1.0f, z - 1.0f),
                    u);
    float y2 = lerp(x3, x4, v);

    return lerp(y1, y2, w);
}

/**
 * @brief 3D Perlin noise with Vec3f input.
 */
[[nodiscard]] inline float perlin(const Vec3f& p) noexcept {
    return perlin(p.x(), p.y(), p.z());
}

// ============================================================================
// Simplex Noise
// ============================================================================

/**
 * @brief 2D Simplex noise.
 *
 * Simplex noise is an improvement over Perlin noise:
 * - Fewer directional artifacts
 * - Better scaling to higher dimensions
 * - Slightly faster in 2D and much faster in higher dimensions
 *
 * @param x X coordinate
 * @param y Y coordinate
 * @return Noise value in approximately [-1, 1)
 */
[[nodiscard]] inline float simplex(float x, float y) noexcept {
    constexpr float F2 = 0.366025403784439f;  // (sqrt(3) - 1) / 2
    constexpr float G2 = 0.211324865405187f;  // (3 - sqrt(3)) / 6

    // Skew the input space to determine which simplex cell we're in
    float s = (x + y) * F2;
    int i = detail::fastFloor(x + s);
    int j = detail::fastFloor(y + s);

    // Unskew the cell origin back to (x, y) space
    float t = static_cast<float>(i + j) * G2;
    float X0 = i - t;
    float Y0 = j - t;
    float x0 = x - X0;
    float y0 = y - Y0;

    // Determine which simplex we're in
    int i1, j1;
    if (x0 > y0) {
        i1 = 1;
        j1 = 0;
    } else {
        i1 = 0;
        j1 = 1;
    }

    // Offsets for middle and last corners
    float x1 = x0 - static_cast<float>(i1) + G2;
    float y1 = y0 - static_cast<float>(j1) + G2;
    float x2 = x0 - 1.0f + 2.0f * G2;
    float y2 = y0 - 1.0f + 2.0f * G2;

    // Hashed gradient indices
    int ii = i & 255;
    int jj = j & 255;
    int gi0 = detail::perm(ii + detail::perm(jj)) & 7;
    int gi1 = detail::perm(ii + i1 + detail::perm(jj + j1)) & 7;
    int gi2 = detail::perm(ii + 1 + detail::perm(jj + 1)) & 7;

    // Gradient directions
    constexpr std::array<float, 16> grad2_x = {1, -1, 1, -1, 1, -1, 0, 0};
    constexpr std::array<float, 16> grad2_y = {1, 1, -1, -1, 0, 0, 1, -1};

    // Calculate contributions from three corners
    float n0 = 0.0f, n1 = 0.0f, n2 = 0.0f;

    float t0 = 0.5f - x0 * x0 - y0 * y0;
    if (t0 >= 0.0f) {
        t0 *= t0;
        auto idx0 = static_cast<size_t>(gi0);
        n0 = t0 * t0 * (grad2_x[idx0] * x0 + grad2_y[idx0] * y0);
    }

    float t1 = 0.5f - x1 * x1 - y1 * y1;
    if (t1 >= 0.0f) {
        t1 *= t1;
        auto idx1 = static_cast<size_t>(gi1);
        n1 = t1 * t1 * (grad2_x[idx1] * x1 + grad2_y[idx1] * y1);
    }

    float t2 = 0.5f - x2 * x2 - y2 * y2;
    if (t2 >= 0.0f) {
        t2 *= t2;
        auto idx2 = static_cast<size_t>(gi2);
        n2 = t2 * t2 * (grad2_x[idx2] * x2 + grad2_y[idx2] * y2);
    }

    // Scale to [-1, 1)
    return 70.0f * (n0 + n1 + n2);
}

/**
 * @brief 2D Simplex noise with Vec2f input.
 */
[[nodiscard]] inline float simplex(const Vec2f& p) noexcept {
    return simplex(p.x(), p.y());
}

/**
 * @brief 3D Simplex noise.
 *
 * @param x X coordinate
 * @param y Y coordinate
 * @param z Z coordinate
 * @return Noise value in approximately [-1, 1)
 */
[[nodiscard]] inline float simplex(float x, float y, float z) noexcept {
    constexpr float F3 = 1.0f / 3.0f;
    constexpr float G3 = 1.0f / 6.0f;

    // Skew
    float s = (x + y + z) * F3;
    int i = detail::fastFloor(x + s);
    int j = detail::fastFloor(y + s);
    int k = detail::fastFloor(z + s);

    // Unskew
    float t = static_cast<float>(i + j + k) * G3;
    float X0 = i - t;
    float Y0 = j - t;
    float Z0 = k - t;
    float x0 = x - X0;
    float y0 = y - Y0;
    float z0 = z - Z0;

    // Determine which simplex we're in
    int i1, j1, k1, i2, j2, k2;
    if (x0 >= y0) {
        if (y0 >= z0) {
            i1 = 1;
            j1 = 0;
            k1 = 0;
            i2 = 1;
            j2 = 1;
            k2 = 0;
        } else if (x0 >= z0) {
            i1 = 1;
            j1 = 0;
            k1 = 0;
            i2 = 1;
            j2 = 0;
            k2 = 1;
        } else {
            i1 = 0;
            j1 = 0;
            k1 = 1;
            i2 = 1;
            j2 = 0;
            k2 = 1;
        }
    } else {
        if (y0 < z0) {
            i1 = 0;
            j1 = 0;
            k1 = 1;
            i2 = 0;
            j2 = 1;
            k2 = 1;
        } else if (x0 < z0) {
            i1 = 0;
            j1 = 1;
            k1 = 0;
            i2 = 0;
            j2 = 1;
            k2 = 1;
        } else {
            i1 = 0;
            j1 = 1;
            k1 = 0;
            i2 = 1;
            j2 = 1;
            k2 = 0;
        }
    }

    // Offsets
    float x1 = x0 - static_cast<float>(i1) + G3;
    float y1 = y0 - static_cast<float>(j1) + G3;
    float z1 = z0 - static_cast<float>(k1) + G3;
    float x2 = x0 - static_cast<float>(i2) + 2.0f * G3;
    float y2 = y0 - static_cast<float>(j2) + 2.0f * G3;
    float z2 = z0 - static_cast<float>(k2) + 2.0f * G3;
    float x3 = x0 - 1.0f + 3.0f * G3;
    float y3 = y0 - 1.0f + 3.0f * G3;
    float z3 = z0 - 1.0f + 3.0f * G3;

    // Hash coordinates
    int ii = i & 255;
    int jj = j & 255;
    int kk = k & 255;

    // Contributions
    float n0 = 0.0f, n1 = 0.0f, n2 = 0.0f, n3 = 0.0f;

    float t0 = 0.6f - x0 * x0 - y0 * y0 - z0 * z0;
    if (t0 >= 0.0f) {
        int gi0 = detail::perm(ii + detail::perm(jj + detail::perm(kk))) & 15;
        t0 *= t0;
        n0 = t0 * t0 * detail::grad3(gi0, x0, y0, z0);
    }

    float t1 = 0.6f - x1 * x1 - y1 * y1 - z1 * z1;
    if (t1 >= 0.0f) {
        int gi1 = detail::perm(ii + i1 + detail::perm(jj + j1 + detail::perm(kk + k1))) & 15;
        t1 *= t1;
        n1 = t1 * t1 * detail::grad3(gi1, x1, y1, z1);
    }

    float t2 = 0.6f - x2 * x2 - y2 * y2 - z2 * z2;
    if (t2 >= 0.0f) {
        int gi2 = detail::perm(ii + i2 + detail::perm(jj + j2 + detail::perm(kk + k2))) & 15;
        t2 *= t2;
        n2 = t2 * t2 * detail::grad3(gi2, x2, y2, z2);
    }

    float t3 = 0.6f - x3 * x3 - y3 * y3 - z3 * z3;
    if (t3 >= 0.0f) {
        int gi3 = detail::perm(ii + 1 + detail::perm(jj + 1 + detail::perm(kk + 1))) & 15;
        t3 *= t3;
        n3 = t3 * t3 * detail::grad3(gi3, x3, y3, z3);
    }

    // Scale to [-1, 1)
    return 32.0f * (n0 + n1 + n2 + n3);
}

/**
 * @brief 3D Simplex noise with Vec3f input.
 */
[[nodiscard]] inline float simplex(const Vec3f& p) noexcept {
    return simplex(p.x(), p.y(), p.z());
}

// ============================================================================
// Fractal Brownian Motion (fBm)
// ============================================================================

/**
 * @brief 2D Fractal Brownian Motion using Perlin noise.
 *
 * Combines multiple octaves of noise at different frequencies
 * to create natural-looking fractal patterns.
 *
 * @param p Input coordinates
 * @param octaves Number of noise layers (default 6)
 * @param lacunarity Frequency multiplier per octave (default 2.0)
 * @param gain Amplitude multiplier per octave (default 0.5)
 * @return Noise value
 */
[[nodiscard]] inline float fbm(const Vec2f& p, int octaves = 6, float lacunarity = 2.0f, float gain = 0.5f) noexcept {
    float sum = 0.0f;
    float amplitude = 1.0f;
    float frequency = 1.0f;
    float max_value = 0.0f;

    Vec2f coords = p;

    for (int i = 0; i < octaves; ++i) {
        sum += amplitude * perlin(coords * frequency);
        max_value += amplitude;
        amplitude *= gain;
        frequency *= lacunarity;
    }

    return sum / max_value;
}

/**
 * @brief 3D Fractal Brownian Motion using Perlin noise.
 */
[[nodiscard]] inline float fbm(const Vec3f& p, int octaves = 6, float lacunarity = 2.0f, float gain = 0.5f) noexcept {
    float sum = 0.0f;
    float amplitude = 1.0f;
    float frequency = 1.0f;
    float max_value = 0.0f;

    Vec3f coords = p;

    for (int i = 0; i < octaves; ++i) {
        sum += amplitude * perlin(coords * frequency);
        max_value += amplitude;
        amplitude *= gain;
        frequency *= lacunarity;
    }

    return sum / max_value;
}

/**
 * @brief 2D fBm using Simplex noise.
 */
[[nodiscard]] inline float fbmSimplex(const Vec2f& p,
                                      int octaves = 6,
                                      float lacunarity = 2.0f,
                                      float gain = 0.5f) noexcept {
    float sum = 0.0f;
    float amplitude = 1.0f;
    float frequency = 1.0f;
    float max_value = 0.0f;

    Vec2f coords = p;

    for (int i = 0; i < octaves; ++i) {
        sum += amplitude * simplex(coords * frequency);
        max_value += amplitude;
        amplitude *= gain;
        frequency *= lacunarity;
    }

    return sum / max_value;
}

/**
 * @brief 3D fBm using Simplex noise.
 */
[[nodiscard]] inline float fbmSimplex(const Vec3f& p,
                                      int octaves = 6,
                                      float lacunarity = 2.0f,
                                      float gain = 0.5f) noexcept {
    float sum = 0.0f;
    float amplitude = 1.0f;
    float frequency = 1.0f;
    float max_value = 0.0f;

    Vec3f coords = p;

    for (int i = 0; i < octaves; ++i) {
        sum += amplitude * simplex(coords * frequency);
        max_value += amplitude;
        amplitude *= gain;
        frequency *= lacunarity;
    }

    return sum / max_value;
}

// ============================================================================
// Turbulence (Absolute fBm)
// ============================================================================

/**
 * @brief 2D Turbulence noise.
 *
 * Similar to fBm but uses absolute value of noise,
 * creating sharper, more turbulent patterns.
 *
 * @param p Input coordinates
 * @param octaves Number of layers
 * @param lacunarity Frequency multiplier
 * @param gain Amplitude multiplier
 * @return Noise value in [0, 1)
 */
[[nodiscard]] inline float turbulence(const Vec2f& p,
                                      int octaves = 6,
                                      float lacunarity = 2.0f,
                                      float gain = 0.5f) noexcept {
    float sum = 0.0f;
    float amplitude = 1.0f;
    float frequency = 1.0f;
    float max_value = 0.0f;

    Vec2f coords = p;

    for (int i = 0; i < octaves; ++i) {
        sum += amplitude * std::abs(perlin(coords * frequency));
        max_value += amplitude;
        amplitude *= gain;
        frequency *= lacunarity;
    }

    return sum / max_value;
}

/**
 * @brief 3D Turbulence noise.
 */
[[nodiscard]] inline float turbulence(const Vec3f& p,
                                      int octaves = 6,
                                      float lacunarity = 2.0f,
                                      float gain = 0.5f) noexcept {
    float sum = 0.0f;
    float amplitude = 1.0f;
    float frequency = 1.0f;
    float max_value = 0.0f;

    Vec3f coords = p;

    for (int i = 0; i < octaves; ++i) {
        sum += amplitude * std::abs(perlin(coords * frequency));
        max_value += amplitude;
        amplitude *= gain;
        frequency *= lacunarity;
    }

    return sum / max_value;
}

// ============================================================================
// Ridged Noise
// ============================================================================

/**
 * @brief 2D Ridged multifractal noise.
 *
 * Creates sharp ridges useful for mountains, veins, lightning.
 *
 * @param p Input coordinates
 * @param octaves Number of layers
 * @param lacunarity Frequency multiplier
 * @param gain Amplitude multiplier
 * @param offset Ridge offset (default 1.0)
 * @return Noise value
 */
[[nodiscard]] inline float ridged(
    const Vec2f& p, int octaves = 6, float lacunarity = 2.0f, float gain = 0.5f, float offset = 1.0f) noexcept {
    float sum = 0.0f;
    float amplitude = 1.0f;
    float frequency = 1.0f;
    float weight = 1.0f;

    Vec2f coords = p;

    for (int i = 0; i < octaves; ++i) {
        float signal = offset - std::abs(perlin(coords * frequency));
        signal *= signal * weight;
        weight = clamp(signal * gain, 0.0f, 1.0f);
        sum += signal * amplitude;
        amplitude *= gain;
        frequency *= lacunarity;
    }

    return sum;
}

/**
 * @brief 3D Ridged multifractal noise.
 */
[[nodiscard]] inline float ridged(
    const Vec3f& p, int octaves = 6, float lacunarity = 2.0f, float gain = 0.5f, float offset = 1.0f) noexcept {
    float sum = 0.0f;
    float amplitude = 1.0f;
    float frequency = 1.0f;
    float weight = 1.0f;

    Vec3f coords = p;

    for (int i = 0; i < octaves; ++i) {
        float signal = offset - std::abs(perlin(coords * frequency));
        signal *= signal * weight;
        weight = clamp(signal * gain, 0.0f, 1.0f);
        sum += signal * amplitude;
        amplitude *= gain;
        frequency *= lacunarity;
    }

    return sum;
}

// ============================================================================
// Value Noise (Simple Hash-Based)
// ============================================================================

/**
 * @brief 2D Value noise.
 *
 * Simpler than Perlin, uses random values at lattice points.
 * Less visually pleasing but faster.
 *
 * @param x X coordinate
 * @param y Y coordinate
 * @return Noise value in [0, 1)
 */
[[nodiscard]] inline float valueNoise(float x, float y) noexcept {
    int xi = detail::fastFloor(x);
    int yi = detail::fastFloor(y);
    float xf = x - static_cast<float>(xi);
    float yf = y - static_cast<float>(yi);

    xi &= 255;
    yi &= 255;

    // Hash corners
    float n00 = static_cast<float>(detail::perm(detail::perm(xi) + yi)) / 255.0f;
    float n01 = static_cast<float>(detail::perm(detail::perm(xi) + yi + 1)) / 255.0f;
    float n10 = static_cast<float>(detail::perm(detail::perm(xi + 1) + yi)) / 255.0f;
    float n11 = static_cast<float>(detail::perm(detail::perm(xi + 1) + yi + 1)) / 255.0f;

    // Smooth interpolation
    float u = detail::fade(xf);
    float v = detail::fade(yf);

    return lerp(lerp(n00, n10, u), lerp(n01, n11, u), v);
}

/**
 * @brief 2D Value noise with Vec2f input.
 */
[[nodiscard]] inline float valueNoise(const Vec2f& p) noexcept {
    return valueNoise(p.x(), p.y());
}

}  // namespace vne::math

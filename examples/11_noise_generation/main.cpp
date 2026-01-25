/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Example: Noise Generation
 * Demonstrates Perlin, Simplex, and Fractal Brownian Motion noise
 * ----------------------------------------------------------------------
 */

#include "common/logging_guard.h"

#include <vertexnova/math/noise.h>
#include <vertexnova/math/core/vec.h>

#include <iomanip>
#include <sstream>

using namespace vne::math;
using vne::math::examples::LoggingGuard_C;

// Helper to visualize noise as ASCII art
std::string noiseToAscii(float value) {
    // Map [-1, 1] to characters
    const char chars[] = " .-:=+*#%@";
    int index = static_cast<int>((value + 1.0f) * 0.5f * 9.0f);
    index = clamp(index, 0, 9);
    return std::string(1, chars[index]);
}

void demonstratePerlin1D() {
    VNE_LOG_INFO << "=== 1D Perlin Noise ===";
    VNE_LOG_INFO << "(Good for: terrain height, audio modulation)";

    std::stringstream ss;
    ss << "  ";
    for (float x = 0.0f; x < 20.0f; x += 0.5f) {
        float value = perlin(x);
        ss << noiseToAscii(value);
    }
    VNE_LOG_INFO << ss.str();

    // Show numerical values
    VNE_LOG_INFO << "Sample values:";
    for (float x = 0.0f; x < 5.0f; x += 1.0f) {
        VNE_LOG_INFO << "  perlin(" << x << ") = " << perlin(x);
    }
}

void demonstratePerlin2D() {
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== 2D Perlin Noise ===";
    VNE_LOG_INFO << "(Good for: terrain heightmaps, cloud textures)";

    // Generate small noise map
    VNE_LOG_INFO << "8x8 noise sample:";
    for (float y = 0.0f; y < 4.0f; y += 0.5f) {
        std::stringstream ss;
        ss << "  ";
        for (float x = 0.0f; x < 4.0f; x += 0.5f) {
            float value = perlin(x, y);
            ss << noiseToAscii(value) << noiseToAscii(value);
        }
        VNE_LOG_INFO << ss.str();
    }
}

void demonstrateSimplex() {
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Simplex Noise ===";
    VNE_LOG_INFO << "(Faster than Perlin, fewer directional artifacts)";

    VNE_LOG_INFO << "2D Simplex sample:";
    for (float y = 0.0f; y < 4.0f; y += 0.5f) {
        std::stringstream ss;
        ss << "  ";
        for (float x = 0.0f; x < 4.0f; x += 0.5f) {
            float value = simplex(x, y);
            ss << noiseToAscii(value) << noiseToAscii(value);
        }
        VNE_LOG_INFO << ss.str();
    }

    // 3D Simplex
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "3D Simplex samples:";
    for (float z = 0.0f; z < 3.0f; z += 1.0f) {
        VNE_LOG_INFO << "  simplex(1.0, 2.0, " << z << ") = " << simplex(1.0f, 2.0f, z);
    }
}

void demonstrateFBM() {
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Fractal Brownian Motion (fBm) ===";
    VNE_LOG_INFO << "(Layered noise for natural-looking textures)";

    Vec2f p(5.0f, 5.0f);

    VNE_LOG_INFO << "Effect of octaves at point " << p << ":";
    for (int octaves = 1; octaves <= 6; octaves++) {
        float value = fbm(p, octaves);
        VNE_LOG_INFO << "  octaves=" << octaves << ": " << value;
    }

    // Visualize FBM
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "FBM (6 octaves) sample:";
    for (float y = 0.0f; y < 4.0f; y += 0.5f) {
        std::stringstream ss;
        ss << "  ";
        for (float x = 0.0f; x < 4.0f; x += 0.5f) {
            float value = fbm(Vec2f(x, y), 6);
            ss << noiseToAscii(value) << noiseToAscii(value);
        }
        VNE_LOG_INFO << ss.str();
    }
}

void demonstrateTurbulence() {
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Turbulence ===";
    VNE_LOG_INFO << "(Absolute fBm - good for fire, smoke, marble)";

    VNE_LOG_INFO << "Turbulence sample:";
    for (float y = 0.0f; y < 4.0f; y += 0.5f) {
        std::stringstream ss;
        ss << "  ";
        for (float x = 0.0f; x < 4.0f; x += 0.5f) {
            float value = turbulence(Vec2f(x, y), 4);
            // Turbulence is [0,1], scale for visualization
            ss << noiseToAscii(value * 2.0f - 1.0f) << noiseToAscii(value * 2.0f - 1.0f);
        }
        VNE_LOG_INFO << ss.str();
    }
}

void demonstrateRidged() {
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Ridged Noise ===";
    VNE_LOG_INFO << "(Sharp ridges - good for mountains, veins, lightning)";

    VNE_LOG_INFO << "Ridged sample:";
    for (float y = 0.0f; y < 4.0f; y += 0.5f) {
        std::stringstream ss;
        ss << "  ";
        for (float x = 0.0f; x < 4.0f; x += 0.5f) {
            float value = ridged(Vec2f(x, y), 4);
            // Normalize ridged noise for visualization
            ss << noiseToAscii(value * 0.5f - 0.5f) << noiseToAscii(value * 0.5f - 0.5f);
        }
        VNE_LOG_INFO << ss.str();
    }
}

void demonstrateValueNoise() {
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Value Noise ===";
    VNE_LOG_INFO << "(Simpler than Perlin, range [0,1])";

    VNE_LOG_INFO << "Value noise sample:";
    for (float y = 0.0f; y < 4.0f; y += 0.5f) {
        std::stringstream ss;
        ss << "  ";
        for (float x = 0.0f; x < 4.0f; x += 0.5f) {
            float value = valueNoise(x, y);
            // Value noise is [0,1], convert to [-1,1] for visualization
            ss << noiseToAscii(value * 2.0f - 1.0f) << noiseToAscii(value * 2.0f - 1.0f);
        }
        VNE_LOG_INFO << ss.str();
    }
}

void demonstratePracticalExample() {
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Practical: Terrain Height Generation ===";

    VNE_LOG_INFO << "Combining multiple noise layers:";
    VNE_LOG_INFO << "  base = fbm(pos * 0.1)       // Large features";
    VNE_LOG_INFO << "  detail = fbm(pos * 0.5)     // Small features";
    VNE_LOG_INFO << "  ridges = ridged(pos * 0.2)  // Mountain ridges";
    VNE_LOG_INFO << "  height = base * 0.6 + detail * 0.2 + ridges * 0.2";

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Sample terrain heights:";
    for (float y = 0.0f; y < 4.0f; y += 1.0f) {
        std::stringstream ss;
        ss << "  ";
        for (float x = 0.0f; x < 8.0f; x += 1.0f) {
            Vec2f pos(x, y);
            float base = fbm(pos * 0.1f, 4);
            float detail = fbm(pos * 0.5f, 2);
            float ridges = ridged(pos * 0.2f, 3);
            float height = base * 0.6f + detail * 0.2f + ridges * 0.2f;
            ss << std::fixed << std::setprecision(2) << height << " ";
        }
        VNE_LOG_INFO << ss.str();
    }
}

int main() {
    LoggingGuard_C logging_guard;

    VNE_LOG_INFO << "VneMath Example: Noise Generation";
    VNE_LOG_INFO << "==================================";
    VNE_LOG_INFO << "";

    demonstratePerlin1D();
    demonstratePerlin2D();
    demonstrateSimplex();
    demonstrateFBM();
    demonstrateTurbulence();
    demonstrateRidged();
    demonstrateValueNoise();
    demonstratePracticalExample();

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Done ===";
    return 0;
}

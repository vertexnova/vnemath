/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Example: Color Utilities
 * Demonstrates color manipulation for graphics
 * ----------------------------------------------------------------------
 */

#include "common/logging_guard.h"

#include <vertexnova/math/color.h>
#include <vertexnova/math/core/types.h>

#include <vector>

using namespace vne::math;
using vne::math::examples::LoggingGuard_C;

void logColor(const std::string& name, const Color& color) {
    VNE_LOG_INFO << "  " << name << ": RGBA(" << color.r() << ", " << color.g() << ", " << color.b() << ", "
                 << color.a() << ")";
}

void demonstrateColorCreation() {
    VNE_LOG_INFO << "=== Color Creation ===";

    // From RGBA floats (0-1 range)
    Color red(1.0f, 0.0f, 0.0f, 1.0f);
    Color green(0.0f, 1.0f, 0.0f, 1.0f);
    Color blue(0.0f, 0.0f, 1.0f, 1.0f);

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "From RGBA floats:";
    logColor("Red", red);
    logColor("Green", green);
    logColor("Blue", blue);

    // With transparency
    Color semi_transparent(1.0f, 0.0f, 0.0f, 0.5f);
    logColor("Semi-transparent red", semi_transparent);

    // Default constructor (black)
    Color default_color;
    logColor("Default (black)", default_color);
}

void demonstratePredefinedColors() {
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Predefined Colors ===";

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Basic colors:";
    logColor("White", Color::kWhite);
    logColor("Black", Color::kBlack);
    logColor("Red", Color::kRed);
    logColor("Green", Color::kGreen);
    logColor("Blue", Color::kBlue);

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Secondary colors:";
    logColor("Yellow", Color::kYellow);
    logColor("Cyan", Color::kCyan);
    logColor("Magenta", Color::kMagenta);

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Other colors:";
    logColor("Gray", Color::kGray);
    logColor("LightBlue", Color::kLightBlue);
    logColor("DarkBlue", Color::kDarkBlue);
    logColor("Maroon", Color::kMaroon);
    logColor("Brown", Color::kBrown);
    logColor("Beige", Color::kBeige);
}

void demonstrateColorLerp() {
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Color Interpolation (Lerp) ===";

    Color start = Color::kRed;
    Color end = Color::kBlue;

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Gradient from Red to Blue:";
    for (float t = 0.0f; t <= 1.0f; t += 0.25f) {
        Color blended = start.lerp(end, t);
        VNE_LOG_INFO << "  t=" << t << ": RGBA(" << blended.r() << ", " << blended.g() << ", " << blended.b() << ", "
                     << blended.a() << ")";
    }

    // Fade out animation
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Fade out (Red to Transparent):";
    Color opaque = Color::kRed;
    Color transparent(1.0f, 0.0f, 0.0f, 0.0f);
    for (float t = 0.0f; t <= 1.0f; t += 0.25f) {
        Color faded = opaque.lerp(transparent, t);
        VNE_LOG_INFO << "  t=" << t << ": alpha=" << faded.a();
    }
}

void demonstrateColorArithmetic() {
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Color Arithmetic ===";

    Color base(0.5f, 0.5f, 0.5f, 1.0f);  // Gray

    // Scalar operations
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Scalar operations on Gray (0.5, 0.5, 0.5):";
    Color darkened = base * 0.5f;
    Color brightened = base * 1.5f;
    logColor("Darkened (*0.5)", darkened);
    logColor("Brightened (*1.5)", brightened);

    // Color addition (additive blending)
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Additive blending:";
    Color dim_red(0.3f, 0.0f, 0.0f, 1.0f);
    Color dim_green(0.0f, 0.3f, 0.0f, 1.0f);
    Color combined = dim_red + dim_green;
    logColor("Dim Red + Dim Green", combined);

    // Color multiplication (multiplicative blending)
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Multiplicative blending (light filtering):";
    Color white_light = Color::kWhite;
    Color red_filter(1.0f, 0.0f, 0.0f, 1.0f);
    Color filtered = white_light * red_filter;
    logColor("White through Red filter", filtered);

    Color yellow_light = Color::kYellow;
    Color blue_filter = Color::kBlue;
    Color yellow_through_blue = yellow_light * blue_filter;
    logColor("Yellow through Blue filter", yellow_through_blue);
}

void demonstrateColorComparison() {
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Color Comparison ===";

    Color a(0.5f, 0.5f, 0.5f, 1.0f);
    Color b(0.5f, 0.5f, 0.5f, 1.0f);
    Color c(0.6f, 0.5f, 0.5f, 1.0f);

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Color A: RGBA(" << a.r() << ", " << a.g() << ", " << a.b() << ", " << a.a() << ")";
    VNE_LOG_INFO << "Color B: RGBA(" << b.r() << ", " << b.g() << ", " << b.b() << ", " << b.a() << ")";
    VNE_LOG_INFO << "Color C: RGBA(" << c.r() << ", " << c.g() << ", " << c.b() << ", " << c.a() << ")";

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Exact comparison:";
    VNE_LOG_INFO << "  A == B: " << (a == b ? "true" : "false");
    VNE_LOG_INFO << "  A == C: " << (a == c ? "true" : "false");

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Approximate comparison (areSame):";
    Color almost_a(0.5f + 0.00001f, 0.5f, 0.5f, 1.0f);
    VNE_LOG_INFO << "  A areSame almost_A: " << (a.areSame(almost_a) ? "true" : "false");
}

void demonstratePracticalExamples() {
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Practical Examples ===";

    // UI button states
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "UI Button color states:";
    Color button_normal(0.2f, 0.4f, 0.8f, 1.0f);
    Color button_hover = button_normal * 1.2f;                       // Brighten on hover
    Color button_pressed = button_normal * 0.8f;                     // Darken on press
    Color button_disabled = button_normal.lerp(Color::kGray, 0.7f);  // Gray out

    logColor("Normal", button_normal);
    logColor("Hover", button_hover);
    logColor("Pressed", button_pressed);
    logColor("Disabled", button_disabled);

    // Health bar gradient
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Health bar gradient (full to empty):";
    Color healthy = Color::kGreen;
    Color warning = Color::kYellow;
    Color critical = Color::kRed;

    for (float health = 1.0f; health >= 0.0f; health -= 0.25f) {
        Color bar_color;
        if (health > 0.5f) {
            // Green to Yellow
            float t = (1.0f - health) * 2.0f;  // 0 at health=1, 1 at health=0.5
            bar_color = healthy.lerp(warning, t);
        } else {
            // Yellow to Red
            float t = (0.5f - health) * 2.0f;  // 0 at health=0.5, 1 at health=0
            bar_color = warning.lerp(critical, t);
        }
        VNE_LOG_INFO << "  Health " << static_cast<int>(health * 100) << "%: RGB(" << bar_color.r() << ", "
                     << bar_color.g() << ", " << bar_color.b() << ")";
    }

    // Day/night cycle sky color
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Day/Night sky transition:";
    Color day_sky(0.529f, 0.808f, 0.922f, 1.0f);  // Light blue
    Color sunset_sky(1.0f, 0.5f, 0.0f, 1.0f);     // Orange
    Color night_sky(0.05f, 0.05f, 0.15f, 1.0f);   // Dark blue

    std::vector<std::pair<std::string, float>> times = {{"Noon", 0.0f},
                                                        {"Afternoon", 0.25f},
                                                        {"Sunset", 0.5f},
                                                        {"Dusk", 0.75f},
                                                        {"Night", 1.0f}};

    for (const auto& [name, t] : times) {
        Color sky;
        if (t <= 0.5f) {
            sky = day_sky.lerp(sunset_sky, t * 2.0f);
        } else {
            sky = sunset_sky.lerp(night_sky, (t - 0.5f) * 2.0f);
        }
        VNE_LOG_INFO << "  " << name << ": RGB(" << sky.r() << ", " << sky.g() << ", " << sky.b() << ")";
    }
}

int main() {
    LoggingGuard_C logging_guard;

    VNE_LOG_INFO << "VneMath Example: Color Utilities";
    VNE_LOG_INFO << "=================================";
    VNE_LOG_INFO << "";

    demonstrateColorCreation();
    demonstratePredefinedColors();
    demonstrateColorLerp();
    demonstrateColorArithmetic();
    demonstrateColorComparison();
    demonstratePracticalExamples();

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Done ===";
    return 0;
}

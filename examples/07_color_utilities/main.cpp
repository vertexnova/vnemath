/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Example: Color Utilities
 * Demonstrates color manipulation for graphics
 * ----------------------------------------------------------------------
 */

#include <vertexnova/math/color.h>
#include <vertexnova/math/core/types.h>

#include <iostream>
#include <iomanip>
#include <vector>

using namespace vne::math;

void printColor(const std::string& name, const Color& color) {
    std::cout << "  " << name << ": RGBA(" << color.r() << ", " << color.g() << ", "
              << color.b() << ", " << color.a() << ")" << std::endl;
}

void demonstrateColorCreation() {
    std::cout << "=== Color Creation ===" << std::endl;

    // From RGBA floats (0-1 range)
    Color red(1.0f, 0.0f, 0.0f, 1.0f);
    Color green(0.0f, 1.0f, 0.0f, 1.0f);
    Color blue(0.0f, 0.0f, 1.0f, 1.0f);

    std::cout << "\nFrom RGBA floats:" << std::endl;
    printColor("Red", red);
    printColor("Green", green);
    printColor("Blue", blue);

    // With transparency
    Color semi_transparent(1.0f, 0.0f, 0.0f, 0.5f);
    printColor("Semi-transparent red", semi_transparent);

    // Default constructor (black)
    Color default_color;
    printColor("Default (black)", default_color);
}

void demonstratePredefinedColors() {
    std::cout << "\n=== Predefined Colors ===" << std::endl;

    std::cout << "\nBasic colors:" << std::endl;
    printColor("White", Color::kWhite);
    printColor("Black", Color::kBlack);
    printColor("Red", Color::kRed);
    printColor("Green", Color::kGreen);
    printColor("Blue", Color::kBlue);

    std::cout << "\nSecondary colors:" << std::endl;
    printColor("Yellow", Color::kYellow);
    printColor("Cyan", Color::kCyan);
    printColor("Magenta", Color::kMagenta);

    std::cout << "\nOther colors:" << std::endl;
    printColor("Gray", Color::kGray);
    printColor("LightBlue", Color::kLightBlue);
    printColor("DarkBlue", Color::kDarkBlue);
    printColor("Maroon", Color::kMaroon);
    printColor("Brown", Color::kBrown);
    printColor("Beige", Color::kBeige);
}

void demonstrateColorLerp() {
    std::cout << "\n=== Color Interpolation (Lerp) ===" << std::endl;

    Color start = Color::kRed;
    Color end = Color::kBlue;

    std::cout << "\nGradient from Red to Blue:" << std::endl;
    for (float t = 0.0f; t <= 1.0f; t += 0.25f) {
        Color blended = start.lerp(end, t);
        std::cout << "  t=" << t << ": RGBA(" << blended.r() << ", " << blended.g()
                  << ", " << blended.b() << ", " << blended.a() << ")" << std::endl;
    }

    // Fade out animation
    std::cout << "\nFade out (Red to Transparent):" << std::endl;
    Color opaque = Color::kRed;
    Color transparent(1.0f, 0.0f, 0.0f, 0.0f);
    for (float t = 0.0f; t <= 1.0f; t += 0.25f) {
        Color faded = opaque.lerp(transparent, t);
        std::cout << "  t=" << t << ": alpha=" << faded.a() << std::endl;
    }
}

void demonstrateColorArithmetic() {
    std::cout << "\n=== Color Arithmetic ===" << std::endl;

    Color base(0.5f, 0.5f, 0.5f, 1.0f);  // Gray

    // Scalar operations
    std::cout << "\nScalar operations on Gray (0.5, 0.5, 0.5):" << std::endl;
    Color darkened = base * 0.5f;
    Color brightened = base * 1.5f;
    printColor("Darkened (*0.5)", darkened);
    printColor("Brightened (*1.5)", brightened);

    // Color addition (additive blending)
    std::cout << "\nAdditive blending:" << std::endl;
    Color dim_red(0.3f, 0.0f, 0.0f, 1.0f);
    Color dim_green(0.0f, 0.3f, 0.0f, 1.0f);
    Color combined = dim_red + dim_green;
    printColor("Dim Red + Dim Green", combined);

    // Color multiplication (multiplicative blending)
    std::cout << "\nMultiplicative blending (light filtering):" << std::endl;
    Color white_light = Color::kWhite;
    Color red_filter(1.0f, 0.0f, 0.0f, 1.0f);
    Color filtered = white_light * red_filter;
    printColor("White through Red filter", filtered);

    Color yellow_light = Color::kYellow;
    Color blue_filter = Color::kBlue;
    Color yellow_through_blue = yellow_light * blue_filter;
    printColor("Yellow through Blue filter", yellow_through_blue);
}

void demonstrateColorComparison() {
    std::cout << "\n=== Color Comparison ===" << std::endl;

    Color a(0.5f, 0.5f, 0.5f, 1.0f);
    Color b(0.5f, 0.5f, 0.5f, 1.0f);
    Color c(0.6f, 0.5f, 0.5f, 1.0f);

    std::cout << "\nColor A: ";
    printColor("", a);
    std::cout << "Color B: ";
    printColor("", b);
    std::cout << "Color C: ";
    printColor("", c);

    std::cout << "\nExact comparison:" << std::endl;
    std::cout << "  A == B: " << (a == b ? "true" : "false") << std::endl;
    std::cout << "  A == C: " << (a == c ? "true" : "false") << std::endl;

    std::cout << "\nApproximate comparison (areSame):" << std::endl;
    Color almost_a(0.5f + 0.00001f, 0.5f, 0.5f, 1.0f);
    std::cout << "  A areSame almost_A: " << (a.areSame(almost_a) ? "true" : "false") << std::endl;
}

void demonstratePracticalExamples() {
    std::cout << "\n=== Practical Examples ===" << std::endl;

    // UI button states
    std::cout << "\nUI Button color states:" << std::endl;
    Color button_normal(0.2f, 0.4f, 0.8f, 1.0f);
    Color button_hover = button_normal * 1.2f;  // Brighten on hover
    Color button_pressed = button_normal * 0.8f;  // Darken on press
    Color button_disabled = button_normal.lerp(Color::kGray, 0.7f);  // Gray out

    printColor("Normal", button_normal);
    printColor("Hover", button_hover);
    printColor("Pressed", button_pressed);
    printColor("Disabled", button_disabled);

    // Health bar gradient
    std::cout << "\nHealth bar gradient (full to empty):" << std::endl;
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
        std::cout << "  Health " << static_cast<int>(health * 100) << "%: RGB("
                  << bar_color.r() << ", " << bar_color.g() << ", " << bar_color.b() << ")"
                  << std::endl;
    }

    // Day/night cycle sky color
    std::cout << "\nDay/Night sky transition:" << std::endl;
    Color day_sky(0.529f, 0.808f, 0.922f, 1.0f);    // Light blue
    Color sunset_sky(1.0f, 0.5f, 0.0f, 1.0f);       // Orange
    Color night_sky(0.05f, 0.05f, 0.15f, 1.0f);     // Dark blue

    std::vector<std::pair<std::string, float>> times = {
        {"Noon", 0.0f},
        {"Afternoon", 0.25f},
        {"Sunset", 0.5f},
        {"Dusk", 0.75f},
        {"Night", 1.0f}
    };

    for (const auto& [name, t] : times) {
        Color sky;
        if (t <= 0.5f) {
            sky = day_sky.lerp(sunset_sky, t * 2.0f);
        } else {
            sky = sunset_sky.lerp(night_sky, (t - 0.5f) * 2.0f);
        }
        std::cout << "  " << name << ": RGB(" << sky.r() << ", " << sky.g() << ", "
                  << sky.b() << ")" << std::endl;
    }
}

int main() {
    std::cout << std::fixed << std::setprecision(3);
    std::cout << "VneMath Example: Color Utilities" << std::endl;
    std::cout << "=================================\n" << std::endl;

    demonstrateColorCreation();
    demonstratePredefinedColors();
    demonstrateColorLerp();
    demonstrateColorArithmetic();
    demonstrateColorComparison();
    demonstratePracticalExamples();

    std::cout << "\n=== Done ===" << std::endl;
    return 0;
}

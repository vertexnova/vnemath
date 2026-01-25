/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Example: Curves and Animation
 * Demonstrates Bezier, Catmull-Rom, and Hermite spline evaluation
 * ----------------------------------------------------------------------
 */

#include "common/logging_guard.h"

#include <vertexnova/math/curves.h>
#include <vertexnova/math/core/vec.h>

using namespace vne::math;
using vne::math::examples::LoggingGuard_C;

void demonstrateBezierCurves() {
    VNE_LOG_INFO << "=== Bezier Curves ===";

    // Quadratic Bezier (3 control points)
    Vec3f p0(0.0f, 0.0f, 0.0f);
    Vec3f p1(5.0f, 10.0f, 0.0f);  // Control point
    Vec3f p2(10.0f, 0.0f, 0.0f);

    VNE_LOG_INFO << "Quadratic Bezier: " << p0 << " -> " << p1 << " -> " << p2;
    VNE_LOG_INFO << "  t=0.00: " << bezierQuadratic(p0, p1, p2, 0.0f);
    VNE_LOG_INFO << "  t=0.25: " << bezierQuadratic(p0, p1, p2, 0.25f);
    VNE_LOG_INFO << "  t=0.50: " << bezierQuadratic(p0, p1, p2, 0.5f);
    VNE_LOG_INFO << "  t=0.75: " << bezierQuadratic(p0, p1, p2, 0.75f);
    VNE_LOG_INFO << "  t=1.00: " << bezierQuadratic(p0, p1, p2, 1.0f);

    // Cubic Bezier (4 control points) - like CSS transitions
    Vec3f c0(0.0f, 0.0f, 0.0f);
    Vec3f c1(2.0f, 8.0f, 0.0f);
    Vec3f c2(8.0f, 8.0f, 0.0f);
    Vec3f c3(10.0f, 0.0f, 0.0f);

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Cubic Bezier (S-curve):";
    for (float t = 0.0f; t <= 1.0f; t += 0.2f) {
        Vec3f point = bezierCubic(c0, c1, c2, c3, t);
        Vec3f tangent = bezierCubicDerivative(c0, c1, c2, c3, t);
        VNE_LOG_INFO << "  t=" << t << ": pos=" << point << " tangent=" << tangent;
    }

    // Arc length approximation
    float length = bezierCubicArcLength(c0, c1, c2, c3, 32);
    VNE_LOG_INFO << "  Arc length: " << length;
}

void demonstrateCatmullRom() {
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Catmull-Rom Spline ===";
    VNE_LOG_INFO << "(Passes through control points - great for animation paths)";

    // 4 points - curve passes through p1 and p2
    Vec3f p0(0.0f, 0.0f, 0.0f);
    Vec3f p1(10.0f, 5.0f, 0.0f);
    Vec3f p2(20.0f, 0.0f, 0.0f);
    Vec3f p3(30.0f, 5.0f, 0.0f);

    VNE_LOG_INFO << "Control points: " << p0 << ", " << p1 << ", " << p2 << ", " << p3;
    VNE_LOG_INFO << "Curve segment from p1 to p2:";

    for (float t = 0.0f; t <= 1.0f; t += 0.2f) {
        Vec3f point = catmullRom(p0, p1, p2, p3, t);
        VNE_LOG_INFO << "  t=" << t << ": " << point;
    }

    // Tension parameter
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Effect of tension parameter at t=0.5:";
    VNE_LOG_INFO << "  tension=-0.5 (loose): " << catmullRomTension(p0, p1, p2, p3, 0.5f, -0.5f);
    VNE_LOG_INFO << "  tension= 0.0 (standard): " << catmullRomTension(p0, p1, p2, p3, 0.5f, 0.0f);
    VNE_LOG_INFO << "  tension= 0.5 (tight): " << catmullRomTension(p0, p1, p2, p3, 0.5f, 0.5f);
}

void demonstrateHermite() {
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Hermite Spline ===";
    VNE_LOG_INFO << "(Define points AND tangents - great for camera motion)";

    Vec3f p0(0.0f, 0.0f, 0.0f);
    Vec3f t0(10.0f, 20.0f, 0.0f);  // Tangent at p0 (steep upward)
    Vec3f p1(10.0f, 0.0f, 0.0f);
    Vec3f t1(10.0f, 0.0f, 0.0f);   // Tangent at p1 (horizontal)

    VNE_LOG_INFO << "Start: " << p0 << " with tangent " << t0;
    VNE_LOG_INFO << "End: " << p1 << " with tangent " << t1;

    for (float t = 0.0f; t <= 1.0f; t += 0.2f) {
        Vec3f point = hermite(p0, t0, p1, t1, t);
        Vec3f tangent = hermiteDerivative(p0, t0, p1, t1, t);
        VNE_LOG_INFO << "  t=" << t << ": pos=" << point << " tangent=" << tangent.normalized();
    }
}

void demonstrateCurveSplitting() {
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Curve Splitting (de Casteljau) ===";

    Vec3f p0(0.0f, 0.0f, 0.0f);
    Vec3f p1(3.0f, 10.0f, 0.0f);
    Vec3f p2(7.0f, 10.0f, 0.0f);
    Vec3f p3(10.0f, 0.0f, 0.0f);

    std::array<Vec3f, 4> left, right;
    bezierCubicSplit(p0, p1, p2, p3, 0.5f, left, right);

    VNE_LOG_INFO << "Original curve split at t=0.5:";
    VNE_LOG_INFO << "Left segment:";
    VNE_LOG_INFO << "  " << left[0] << " -> " << left[1] << " -> " << left[2] << " -> " << left[3];
    VNE_LOG_INFO << "Right segment:";
    VNE_LOG_INFO << "  " << right[0] << " -> " << right[1] << " -> " << right[2] << " -> " << right[3];
}

void demonstrateScalarCurves() {
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Scalar Curves (for animation timing) ===";

    // Ease-in timing curve (slow start, fast end)
    float p0 = 0.0f;
    float p1 = 0.0f;
    float p2 = 1.0f;
    float p3 = 1.0f;

    VNE_LOG_INFO << "Ease-in curve (CSS: cubic-bezier(0, 0, 1, 1) equivalent):";
    for (float t = 0.0f; t <= 1.0f; t += 0.2f) {
        float value = bezierCubic(p0, p1, p2, p3, t);
        VNE_LOG_INFO << "  t=" << t << ": value=" << value;
    }

    // Ease-in-out timing curve
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Ease-in-out (smooth start and end):";
    float e0 = 0.0f, e1 = 0.0f, e2 = 1.0f, e3 = 1.0f;
    for (float t = 0.0f; t <= 1.0f; t += 0.2f) {
        float value = bezierCubic(e0, e1, e2, e3, t);
        VNE_LOG_INFO << "  t=" << t << ": value=" << value;
    }
}

int main() {
    LoggingGuard_C logging_guard;

    VNE_LOG_INFO << "VneMath Example: Curves and Animation";
    VNE_LOG_INFO << "======================================";
    VNE_LOG_INFO << "";

    demonstrateBezierCurves();
    demonstrateCatmullRom();
    demonstrateHermite();
    demonstrateCurveSplitting();
    demonstrateScalarCurves();

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Done ===";
    return 0;
}

/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Example: Transform Decomposition
 * Demonstrates matrix decomposition into TRS and recomposition
 * ----------------------------------------------------------------------
 */

#include "common/logging_guard.h"

#include <vertexnova/math/transform_utils.h>
#include <vertexnova/math/core/core.h>

using namespace vne::math;
using vne::math::examples::LoggingGuard_C;

void demonstrateBasicDecomposition() {
    VNE_LOG_INFO << "=== Basic Transform Decomposition ===";

    // Create a transform matrix
    Vec3f translation(10.0f, 20.0f, 30.0f);
    Quatf rotation = Quatf::fromAxisAngle(Vec3f::yAxis(), degToRad(45.0f));
    Vec3f scale(2.0f, 2.0f, 2.0f);

    VNE_LOG_INFO << "Original components:";
    VNE_LOG_INFO << "  Translation: " << translation;
    VNE_LOG_INFO << "  Rotation: " << rotation << " (" << radToDeg(rotation.angle()) << " degrees)";
    VNE_LOG_INFO << "  Scale: " << scale;

    // Compose into matrix
    Mat4f matrix = compose(translation, rotation, scale);
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Composed matrix:";
    VNE_LOG_INFO << matrix;

    // Decompose back
    TransformComponents components = decompose(matrix);
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Decomposed components:";
    VNE_LOG_INFO << "  Translation: " << components.translation;
    VNE_LOG_INFO << "  Rotation: " << components.rotation << " (" << radToDeg(components.rotation.angle()) << " degrees)";
    VNE_LOG_INFO << "  Scale: " << components.scale;
}

void demonstrateIndividualExtraction() {
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Individual Component Extraction ===";

    Mat4f matrix = compose(Vec3f(5.0f, 10.0f, 15.0f),
                           Quatf::fromAxisAngle(Vec3f::zAxis(), degToRad(90.0f)),
                           Vec3f(3.0f, 3.0f, 3.0f));

    VNE_LOG_INFO << "From combined TRS matrix:";
    VNE_LOG_INFO << "  extractTranslation: " << extractTranslation(matrix);
    VNE_LOG_INFO << "  extractScale: " << extractScale(matrix);
    VNE_LOG_INFO << "  extractRotation: " << extractRotation(matrix);

    Mat3f upper3x3 = extractMat3(matrix);
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Upper 3x3 (rotation * scale):";
    VNE_LOG_INFO << upper3x3;
}

void demonstrateMatrixFactories() {
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Matrix Factory Functions ===";

    Mat4f translation_matrix = makeTranslation(Vec3f(1.0f, 2.0f, 3.0f));
    VNE_LOG_INFO << "makeTranslation(1, 2, 3):";
    VNE_LOG_INFO << translation_matrix;

    Mat4f rotation_matrix = makeRotation(Quatf::fromAxisAngle(Vec3f::yAxis(), degToRad(90.0f)));
    VNE_LOG_INFO << "makeRotation(90 deg around Y):";
    VNE_LOG_INFO << rotation_matrix;

    Mat4f uniform_scale = makeScale(2.0f);
    VNE_LOG_INFO << "makeScale(2.0):";
    VNE_LOG_INFO << uniform_scale;

    Mat4f non_uniform_scale = makeScale(Vec3f(1.0f, 2.0f, 3.0f));
    VNE_LOG_INFO << "makeScale(1, 2, 3):";
    VNE_LOG_INFO << non_uniform_scale;
}

void demonstrateTransformInterpolation() {
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Transform Interpolation ===";
    VNE_LOG_INFO << "(Smooth interpolation between two transformations)";

    // Start transform
    Mat4f start = compose(Vec3f(0.0f, 0.0f, 0.0f),
                          Quatf::identity(),
                          Vec3f(1.0f, 1.0f, 1.0f));

    // End transform
    Mat4f end = compose(Vec3f(10.0f, 5.0f, 0.0f),
                        Quatf::fromAxisAngle(Vec3f::yAxis(), degToRad(180.0f)),
                        Vec3f(2.0f, 2.0f, 2.0f));

    VNE_LOG_INFO << "Interpolating from origin to (10, 5, 0) with 180 deg rotation:";
    for (float t = 0.0f; t <= 1.0f; t += 0.25f) {
        Mat4f interpolated = lerpTransform(start, end, t);
        TransformComponents tc = decompose(interpolated);

        VNE_LOG_INFO << "  t=" << t << ": pos=" << tc.translation
                     << " rot=" << radToDeg(tc.rotation.angle()) << "deg"
                     << " scale=" << tc.scale.x();
    }
}

void demonstrateTransformComponents() {
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== TransformComponents Struct ===";

    TransformComponents tc;
    VNE_LOG_INFO << "Default TransformComponents:";
    VNE_LOG_INFO << "  isIdentity: " << (tc.isIdentity() ? "true" : "false");
    VNE_LOG_INFO << "  hasUniformScale: " << (tc.hasUniformScale() ? "true" : "false");

    tc.translation = Vec3f(1.0f, 0.0f, 0.0f);
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "After setting translation:";
    VNE_LOG_INFO << "  isIdentity: " << (tc.isIdentity() ? "true" : "false");

    tc.translation = Vec3f::zero();
    tc.scale = Vec3f(1.0f, 2.0f, 3.0f);
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "With non-uniform scale (1, 2, 3):";
    VNE_LOG_INFO << "  hasUniformScale: " << (tc.hasUniformScale() ? "true" : "false");
}

void demonstratePracticalUseCase() {
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Practical: Animation Blending ===";

    // Scenario: Blending between two animation keyframes
    TransformComponents keyframe1;
    keyframe1.translation = Vec3f(0.0f, 0.0f, 0.0f);
    keyframe1.rotation = Quatf::fromEuler(0.0f, 0.0f, 0.0f);
    keyframe1.scale = Vec3f(1.0f, 1.0f, 1.0f);

    TransformComponents keyframe2;
    keyframe2.translation = Vec3f(0.0f, 2.0f, 0.0f);  // Jump up
    keyframe2.rotation = Quatf::fromEuler(degToRad(15.0f), 0.0f, 0.0f);  // Tilt forward
    keyframe2.scale = Vec3f(0.9f, 1.1f, 0.9f);  // Squash/stretch

    Mat4f m1 = compose(keyframe1);
    Mat4f m2 = compose(keyframe2);

    VNE_LOG_INFO << "Blending jump animation keyframes:";
    for (float t = 0.0f; t <= 1.0f; t += 0.2f) {
        Mat4f blended = lerpTransform(m1, m2, t);
        TransformComponents tc = decompose(blended);

        VNE_LOG_INFO << "  t=" << t << ": y=" << tc.translation.y()
                     << " pitch=" << radToDeg(tc.rotation.toEuler().x()) << "deg"
                     << " scale_y=" << tc.scale.y();
    }
}

int main() {
    LoggingGuard_C logging_guard;

    VNE_LOG_INFO << "VneMath Example: Transform Decomposition";
    VNE_LOG_INFO << "=========================================";
    VNE_LOG_INFO << "";

    demonstrateBasicDecomposition();
    demonstrateIndividualExtraction();
    demonstrateMatrixFactories();
    demonstrateTransformInterpolation();
    demonstrateTransformComponents();
    demonstratePracticalUseCase();

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Done ===";
    return 0;
}

/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 * ----------------------------------------------------------------------
 */

#include <gtest/gtest.h>

#include <vertexnova/math/core/core.h>
#include <vertexnova/math/transform_utils.h>

#include <cmath>

using namespace vne::math;

// ============================================================================
// TransformComponents Tests
// ============================================================================

TEST(TransformComponentsTest, DefaultIsIdentity) {
    TransformComponents tc;

    EXPECT_TRUE(tc.translation.areSame(Vec3f::zero()));
    EXPECT_TRUE(tc.rotation.approxEquals(Quatf::identity()));
    EXPECT_TRUE(tc.scale.areSame(Vec3f(1.0f, 1.0f, 1.0f)));
}

TEST(TransformComponentsTest, IsIdentityCheck) {
    TransformComponents identity;
    EXPECT_TRUE(identity.isIdentity());

    TransformComponents translated;
    translated.translation = Vec3f(1.0f, 0.0f, 0.0f);
    EXPECT_FALSE(translated.isIdentity());

    TransformComponents scaled;
    scaled.scale = Vec3f(2.0f, 2.0f, 2.0f);
    EXPECT_FALSE(scaled.isIdentity());
}

TEST(TransformComponentsTest, UniformScaleCheck) {
    TransformComponents uniform;
    uniform.scale = Vec3f(2.0f, 2.0f, 2.0f);
    EXPECT_TRUE(uniform.hasUniformScale());

    TransformComponents non_uniform;
    non_uniform.scale = Vec3f(1.0f, 2.0f, 3.0f);
    EXPECT_FALSE(non_uniform.hasUniformScale());
}

// ============================================================================
// Decompose Tests
// ============================================================================

TEST(DecomposeTest, IdentityMatrix) {
    Mat4f identity = Mat4f::identity();
    auto result = decompose(identity);

    EXPECT_TRUE(result.translation.areSame(Vec3f::zero()));
    EXPECT_TRUE(result.rotation.approxEquals(Quatf::identity()));
    EXPECT_TRUE(result.scale.areSame(Vec3f(1.0f, 1.0f, 1.0f)));
}

TEST(DecomposeTest, TranslationOnly) {
    Vec3f translation(10.0f, 20.0f, 30.0f);
    Mat4f matrix = makeTranslation(translation);
    auto result = decompose(matrix);

    EXPECT_TRUE(result.translation.areSame(translation));
    EXPECT_TRUE(result.rotation.approxEquals(Quatf::identity()));
    EXPECT_TRUE(result.scale.areSame(Vec3f(1.0f, 1.0f, 1.0f)));
}

TEST(DecomposeTest, RotationOnly) {
    Quatf rotation = Quatf::fromAxisAngle(Vec3f::yAxis(), kPi / 4.0f);
    Mat4f matrix = makeRotation(rotation);
    auto result = decompose(matrix);

    EXPECT_TRUE(result.translation.areSame(Vec3f::zero()));
    EXPECT_TRUE(result.rotation.approxEquals(rotation, 0.001f));
    EXPECT_TRUE(result.scale.areSame(Vec3f(1.0f, 1.0f, 1.0f), 0.001f));
}

TEST(DecomposeTest, UniformScaleOnly) {
    float scale_factor = 3.0f;
    Mat4f matrix = makeScale(scale_factor);
    auto result = decompose(matrix);

    EXPECT_TRUE(result.translation.areSame(Vec3f::zero()));
    EXPECT_TRUE(result.rotation.approxEquals(Quatf::identity(), 0.001f));
    EXPECT_NEAR(result.scale.x(), scale_factor, 0.001f);
    EXPECT_NEAR(result.scale.y(), scale_factor, 0.001f);
    EXPECT_NEAR(result.scale.z(), scale_factor, 0.001f);
}

TEST(DecomposeTest, NonUniformScale) {
    Vec3f scale(2.0f, 3.0f, 4.0f);
    Mat4f matrix = makeScale(scale);
    auto result = decompose(matrix);

    EXPECT_TRUE(result.translation.areSame(Vec3f::zero()));
    EXPECT_TRUE(result.scale.areSame(scale, 0.001f));
}

TEST(DecomposeTest, CombinedTRS) {
    Vec3f translation(5.0f, 10.0f, 15.0f);
    Quatf rotation = Quatf::fromAxisAngle(Vec3f::zAxis(), kPi / 3.0f);
    Vec3f scale(2.0f, 2.0f, 2.0f);

    Mat4f matrix = compose(translation, rotation, scale);
    auto result = decompose(matrix);

    EXPECT_TRUE(result.translation.areSame(translation, 0.001f));
    EXPECT_TRUE(result.rotation.approxEquals(rotation, 0.001f));
    EXPECT_TRUE(result.scale.areSame(scale, 0.001f));
}

// ============================================================================
// Compose Tests
// ============================================================================

TEST(ComposeTest, Identity) {
    Mat4f result = compose(Vec3f::zero(), Quatf::identity(), Vec3f(1.0f, 1.0f, 1.0f));

    EXPECT_TRUE(result.approxEquals(Mat4f::identity(), 0.001f));
}

TEST(ComposeTest, TranslationOnly) {
    Vec3f translation(1.0f, 2.0f, 3.0f);
    Mat4f result = compose(translation, Quatf::identity(), Vec3f(1.0f, 1.0f, 1.0f));

    Vec4f point = result * Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
    EXPECT_NEAR(point.x(), 1.0f, 0.001f);
    EXPECT_NEAR(point.y(), 2.0f, 0.001f);
    EXPECT_NEAR(point.z(), 3.0f, 0.001f);
}

TEST(ComposeTest, FromComponents) {
    TransformComponents tc;
    tc.translation = Vec3f(1.0f, 2.0f, 3.0f);
    tc.rotation = Quatf::fromAxisAngle(Vec3f::yAxis(), kPi / 2.0f);
    tc.scale = Vec3f(2.0f, 2.0f, 2.0f);

    Mat4f result = compose(tc);

    // Decompose should give back the same components
    auto decomposed = decompose(result);
    EXPECT_TRUE(decomposed.translation.areSame(tc.translation, 0.001f));
    EXPECT_TRUE(decomposed.rotation.approxEquals(tc.rotation, 0.001f));
    EXPECT_TRUE(decomposed.scale.areSame(tc.scale, 0.001f));
}

// ============================================================================
// Extract Functions Tests
// ============================================================================

TEST(ExtractTest, Translation) {
    Vec3f expected(5.0f, 10.0f, 15.0f);
    Mat4f matrix = compose(expected, Quatf::fromAxisAngle(Vec3f::xAxis(), 0.5f), Vec3f(2.0f, 3.0f, 4.0f));

    Vec3f result = extractTranslation(matrix);
    EXPECT_TRUE(result.areSame(expected, 0.001f));
}

TEST(ExtractTest, Scale) {
    Vec3f expected(2.0f, 3.0f, 4.0f);
    Mat4f matrix = compose(Vec3f(1.0f, 2.0f, 3.0f), Quatf::fromAxisAngle(Vec3f::yAxis(), 0.5f), expected);

    Vec3f result = extractScale(matrix);
    EXPECT_TRUE(result.areSame(expected, 0.001f));
}

TEST(ExtractTest, Rotation) {
    Quatf expected = Quatf::fromAxisAngle(Vec3f::zAxis(), kPi / 4.0f);
    Mat4f matrix = compose(Vec3f(1.0f, 2.0f, 3.0f), expected, Vec3f(1.0f, 1.0f, 1.0f));

    Quatf result = extractRotation(matrix);
    EXPECT_TRUE(result.approxEquals(expected, 0.001f));
}

TEST(ExtractTest, Mat3) {
    Quatf rotation = Quatf::fromAxisAngle(Vec3f::yAxis(), kPi / 3.0f);
    Vec3f scale(2.0f, 2.0f, 2.0f);
    Mat4f matrix = compose(Vec3f::zero(), rotation, scale);

    Mat3f result = extractMat3(matrix);

    // The extracted 3x3 should contain rotation * scale
    EXPECT_FALSE(std::isnan(result.getColumn(0).x()));
}

// ============================================================================
// Make Functions Tests
// ============================================================================

TEST(MakeTest, Translation) {
    Vec3f translation(3.0f, 4.0f, 5.0f);
    Mat4f matrix = makeTranslation(translation);

    Vec4f result = matrix * Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
    EXPECT_NEAR(result.x(), 3.0f, 0.001f);
    EXPECT_NEAR(result.y(), 4.0f, 0.001f);
    EXPECT_NEAR(result.z(), 5.0f, 0.001f);
}

TEST(MakeTest, Rotation) {
    Quatf rotation = Quatf::fromAxisAngle(Vec3f::zAxis(), kPi / 2.0f);
    Mat4f matrix = makeRotation(rotation);

    // Rotate X axis around Z by 90 degrees = Y axis
    Vec4f result = matrix * Vec4f(1.0f, 0.0f, 0.0f, 0.0f);
    EXPECT_NEAR(result.x(), 0.0f, 0.001f);
    EXPECT_NEAR(result.y(), 1.0f, 0.001f);
    EXPECT_NEAR(result.z(), 0.0f, 0.001f);
}

TEST(MakeTest, UniformScale) {
    float scale = 3.0f;
    Mat4f matrix = makeScale(scale);

    Vec4f result = matrix * Vec4f(1.0f, 1.0f, 1.0f, 0.0f);
    EXPECT_NEAR(result.x(), 3.0f, 0.001f);
    EXPECT_NEAR(result.y(), 3.0f, 0.001f);
    EXPECT_NEAR(result.z(), 3.0f, 0.001f);
}

TEST(MakeTest, NonUniformScale) {
    Vec3f scale(2.0f, 3.0f, 4.0f);
    Mat4f matrix = makeScale(scale);

    Vec4f result = matrix * Vec4f(1.0f, 1.0f, 1.0f, 0.0f);
    EXPECT_NEAR(result.x(), 2.0f, 0.001f);
    EXPECT_NEAR(result.y(), 3.0f, 0.001f);
    EXPECT_NEAR(result.z(), 4.0f, 0.001f);
}

// ============================================================================
// Lerp Transform Tests
// ============================================================================

TEST(LerpTransformTest, Identity) {
    Mat4f a = Mat4f::identity();
    Mat4f b = Mat4f::identity();

    Mat4f result = lerpTransform(a, b, 0.5f);
    EXPECT_TRUE(result.approxEquals(Mat4f::identity(), 0.001f));
}

TEST(LerpTransformTest, Endpoints) {
    Mat4f a = compose(Vec3f(0.0f, 0.0f, 0.0f), Quatf::identity(), Vec3f(1.0f, 1.0f, 1.0f));
    Mat4f b = compose(Vec3f(10.0f, 0.0f, 0.0f), Quatf::identity(), Vec3f(2.0f, 2.0f, 2.0f));

    Mat4f at_zero = lerpTransform(a, b, 0.0f);
    Mat4f at_one = lerpTransform(a, b, 1.0f);

    EXPECT_TRUE(at_zero.approxEquals(a, 0.001f));
    EXPECT_TRUE(at_one.approxEquals(b, 0.001f));
}

TEST(LerpTransformTest, Midpoint) {
    Mat4f a = compose(Vec3f(0.0f, 0.0f, 0.0f), Quatf::identity(), Vec3f(1.0f, 1.0f, 1.0f));
    Mat4f b = compose(Vec3f(10.0f, 0.0f, 0.0f), Quatf::identity(), Vec3f(3.0f, 3.0f, 3.0f));

    Mat4f mid = lerpTransform(a, b, 0.5f);
    auto components = decompose(mid);

    EXPECT_NEAR(components.translation.x(), 5.0f, 0.001f);
    EXPECT_NEAR(components.scale.x(), 2.0f, 0.001f);
}

TEST(LerpTransformTest, RotationInterpolation) {
    // Use a smaller rotation to avoid quaternion slerp path ambiguity
    Quatf rot_a = Quatf::identity();
    Quatf rot_b = Quatf::fromAxisAngle(Vec3f::yAxis(), kPi / 2.0f);  // 90 degrees

    Mat4f a = compose(Vec3f::zero(), rot_a, Vec3f(1.0f, 1.0f, 1.0f));
    Mat4f b = compose(Vec3f::zero(), rot_b, Vec3f(1.0f, 1.0f, 1.0f));

    Mat4f mid = lerpTransform(a, b, 0.5f);
    auto components = decompose(mid);

    // Rotation should be 45 degrees around Y
    Quatf expected = Quatf::fromAxisAngle(Vec3f::yAxis(), kPi / 4.0f);

    // Check that the rotation is approximately correct (quaternions can be negated and still represent same rotation)
    bool matches =
        components.rotation.approxEquals(expected, 0.01f) || components.rotation.approxEquals(-expected, 0.01f);
    EXPECT_TRUE(matches);
}

// ============================================================================
// Round-Trip Tests
// ============================================================================

TEST(RoundTripTest, DecomposeCompose) {
    // Create a complex transformation
    Vec3f translation(5.0f, -3.0f, 10.0f);
    Quatf rotation = Quatf::fromAxisAngle(Vec3f(1.0f, 1.0f, 1.0f).normalized(), 0.7f);
    Vec3f scale(1.5f, 2.0f, 0.8f);

    Mat4f original = compose(translation, rotation, scale);
    auto components = decompose(original);
    Mat4f reconstructed = compose(components);

    // Should be able to round-trip
    EXPECT_TRUE(original.approxEquals(reconstructed, 0.001f));
}

TEST(RoundTripTest, MultipleIterations) {
    Mat4f matrix =
        compose(Vec3f(1.0f, 2.0f, 3.0f), Quatf::fromAxisAngle(Vec3f::zAxis(), 0.5f), Vec3f(2.0f, 2.0f, 2.0f));

    // Multiple round-trips should not accumulate error significantly
    for (int i = 0; i < 10; ++i) {
        auto components = decompose(matrix);
        matrix = compose(components);
    }

    auto final_components = decompose(matrix);
    EXPECT_NEAR(final_components.translation.x(), 1.0f, 0.01f);
    EXPECT_NEAR(final_components.scale.x(), 2.0f, 0.01f);
}

// ============================================================================
// Consistency Tests (overlapping APIs must stay aligned)
// ============================================================================

TEST(ConsistencyTest, ComposeEqualsModelMatrix) {
    Vec3f translation(1.5f, -2.0f, 3.25f);
    Quatf rotation = Quatf::fromAxisAngle(Vec3f::yAxis(), kPi / 3.0f);
    Vec3f scale(0.5f, 1.25f, 2.0f);

    Mat4f via_compose = compose(translation, rotation, scale);
    Mat4f via_model = modelMatrix(translation, rotation, scale);

    EXPECT_TRUE(via_compose.approxEquals(via_model, 1e-5f));
}

TEST(ConsistencyTest, MakeTranslationEqualsMat4Translate) {
    Vec3f t(4.0f, 5.0f, 6.0f);
    EXPECT_TRUE(makeTranslation(t).approxEquals(Mat4f::translate(t), 1e-6f));
}

TEST(ConsistencyTest, MakeRotationEqualsToMatrix4) {
    Quatf rotation = Quatf::fromAxisAngle(Vec3f::zAxis(), kPi / 5.0f);
    EXPECT_TRUE(makeRotation(rotation).approxEquals(rotation.toMatrix4(), 1e-5f));
}

TEST(ConsistencyTest, MakeScaleEqualsMat4Scale) {
    EXPECT_TRUE(makeScale(2.5f).approxEquals(Mat4f::scale(2.5f), 1e-6f));
    Vec3f s(1.0f, 2.0f, 3.0f);
    EXPECT_TRUE(makeScale(s).approxEquals(Mat4f::scale(s), 1e-6f));
}

TEST(DecomposeTest, NegativeScaleRecoversSign) {
    Vec3f translation(1.0f, 2.0f, 3.0f);
    Quatf rotation = Quatf::fromAxisAngle(Vec3f::yAxis(), kPi / 6.0f);
    Vec3f scale(-1.0f, 1.0f, 1.0f);

    Mat4f matrix = compose(translation, rotation, scale);
    auto result = decompose(matrix);

    EXPECT_TRUE(result.translation.areSame(translation, 1e-4f));
    EXPECT_NEAR(result.scale.x(), -1.0f, 1e-3f);
    EXPECT_NEAR(result.scale.y(), 1.0f, 1e-3f);
    EXPECT_NEAR(result.scale.z(), 1.0f, 1e-3f);

    Mat4f reconstructed = compose(result);
    EXPECT_TRUE(matrix.approxEquals(reconstructed, 1e-3f));
}

TEST(DecomposeTest, ZeroScaleIsFinite) {
    Mat4f matrix = makeScale(0.0f);
    auto result = decompose(matrix);

    EXPECT_TRUE(std::isfinite(result.translation.x()));
    EXPECT_TRUE(std::isfinite(result.translation.y()));
    EXPECT_TRUE(std::isfinite(result.translation.z()));
    EXPECT_TRUE(std::isfinite(result.scale.x()));
    EXPECT_TRUE(std::isfinite(result.scale.y()));
    EXPECT_TRUE(std::isfinite(result.scale.z()));
    EXPECT_TRUE(std::isfinite(result.rotation.x));
    EXPECT_TRUE(std::isfinite(result.rotation.y));
    EXPECT_TRUE(std::isfinite(result.rotation.z));
    EXPECT_TRUE(std::isfinite(result.rotation.w));
}

TEST(ExtractTest, ExtractScaleAndRotationAgreeWithDecompose) {
    Mat4f matrix =
        compose(Vec3f(2.0f, -1.0f, 4.0f), Quatf::fromAxisAngle(Vec3f::xAxis(), 0.4f), Vec3f(1.5f, 0.75f, 2.25f));
    auto components = decompose(matrix);

    EXPECT_TRUE(extractScale(matrix).areSame(components.scale, 1e-5f));
    EXPECT_TRUE(extractRotation(matrix).approxEquals(components.rotation, 1e-5f));
    EXPECT_TRUE(extractTranslation(matrix).areSame(components.translation, 1e-5f));
}

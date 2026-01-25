/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Example: Hello Math
 * Demonstrates basic vector, matrix, and quaternion operations
 * ----------------------------------------------------------------------
 */

#include "common/logging_guard.h"

#include <vertexnova/math/core/core.h>

using namespace vne::math;
using vne::math::examples::LoggingGuard_C;

void demonstrateVectors() {
    VNE_LOG_INFO << "=== Vectors ===";

    // 2D Vectors
    Vec2f v2a(1.0f, 2.0f);
    Vec2f v2b(3.0f, 4.0f);
    VNE_LOG_INFO << "Vec2f a: " << v2a;
    VNE_LOG_INFO << "Vec2f b: " << v2b;
    VNE_LOG_INFO << "a + b: " << (v2a + v2b);
    VNE_LOG_INFO << "a dot b: " << v2a.dot(v2b);

    // 3D Vectors
    Vec3f v3a(1.0f, 0.0f, 0.0f);
    Vec3f v3b(0.0f, 1.0f, 0.0f);
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Vec3f a (X-axis): " << v3a;
    VNE_LOG_INFO << "Vec3f b (Y-axis): " << v3b;
    VNE_LOG_INFO << "a cross b (Z-axis): " << v3a.cross(v3b);

    // Vector operations
    Vec3f position(10.0f, 20.0f, 30.0f);
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Position: " << position;
    VNE_LOG_INFO << "Length: " << position.length();
    VNE_LOG_INFO << "Normalized: " << position.normalized();

    // Static factory methods
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Static vectors:";
    VNE_LOG_INFO << "Zero: " << Vec3f::zero();
    VNE_LOG_INFO << "One: " << Vec3f::one();
    VNE_LOG_INFO << "X-Axis: " << Vec3f::xAxis();
    VNE_LOG_INFO << "Y-Axis: " << Vec3f::yAxis();
    VNE_LOG_INFO << "Z-Axis: " << Vec3f::zAxis();

    // 4D Vectors (homogeneous coordinates)
    Vec4f point(1.0f, 2.0f, 3.0f, 1.0f);      // w=1 for points
    Vec4f direction(1.0f, 0.0f, 0.0f, 0.0f);  // w=0 for directions
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "4D Point: " << point;
    VNE_LOG_INFO << "4D Direction: " << direction;
}

void demonstrateMatrices() {
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Matrices ===";

    // Identity matrix
    Mat4f identity = Mat4f::identity();
    VNE_LOG_INFO << "Identity 4x4:";
    VNE_LOG_INFO << identity;

    // Translation matrix
    Mat4f translation = Mat4f::translate(Vec3f(10.0f, 20.0f, 30.0f));
    VNE_LOG_INFO << "Translation matrix (10, 20, 30):";
    VNE_LOG_INFO << translation;

    // Scale matrix
    Mat4f scale = Mat4f::scale(Vec3f(2.0f, 2.0f, 2.0f));
    VNE_LOG_INFO << "Scale matrix (2x):";
    VNE_LOG_INFO << scale;

    // Rotation matrix
    float angle = degToRad(45.0f);
    Mat4f rotY = Mat4f::rotateY(angle);
    VNE_LOG_INFO << "Rotation around Y (45 degrees):";
    VNE_LOG_INFO << rotY;

    // Matrix multiplication
    Mat4f combined = translation * rotY * scale;
    VNE_LOG_INFO << "Combined (T * R * S):";
    VNE_LOG_INFO << combined;

    // Transform a point
    Vec3f point(1.0f, 0.0f, 0.0f);
    Vec3f transformed = combined.transformPoint(point);
    VNE_LOG_INFO << "Original point: " << point;
    VNE_LOG_INFO << "Transformed point: " << transformed;

    // Matrix inverse
    Mat4f inverse = combined.inverse();
    Vec3f backToOriginal = inverse.transformPoint(transformed);
    VNE_LOG_INFO << "Back to original: " << backToOriginal;
}

void demonstrateQuaternions() {
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Quaternions ===";

    // Identity quaternion (no rotation)
    Quatf identity = Quatf::identity();
    VNE_LOG_INFO << "Identity: " << identity;

    // Rotation from axis-angle
    Vec3f axis = Vec3f::yAxis();
    float angle = degToRad(90.0f);
    Quatf rotation = Quatf::fromAxisAngle(axis, angle);
    VNE_LOG_INFO << "90 deg around Y-axis: " << rotation;

    // Rotate a vector
    Vec3f forward = Vec3f::zAxis();
    Vec3f rotated = rotation.rotate(forward);
    VNE_LOG_INFO << "Z-axis rotated 90 deg around Y: " << rotated;

    // Quaternion from Euler angles
    Quatf euler = Quatf::fromEuler(degToRad(0.0f),   // pitch (X)
                                   degToRad(45.0f),  // yaw (Y)
                                   degToRad(0.0f)    // roll (Z)
    );
    VNE_LOG_INFO << "From Euler (0, 45, 0): " << euler;

    // Convert to matrix
    Mat4f rotMatrix = rotation.toMatrix4();
    VNE_LOG_INFO << "Quaternion as matrix:";
    VNE_LOG_INFO << rotMatrix;

    // Quaternion interpolation (slerp)
    Quatf q1 = Quatf::identity();
    Quatf q2 = Quatf::fromAxisAngle(Vec3f::yAxis(), degToRad(180.0f));
    Quatf halfway = Quatf::slerp(q1, q2, 0.5f);
    VNE_LOG_INFO << "Slerp halfway between 0 and 180 deg: " << halfway;
    VNE_LOG_INFO << "Angle: " << radToDeg(halfway.angle()) << " degrees";
}

void demonstrateMathUtils() {
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Math Utilities ===";

    // Angle conversions
    float degrees = 180.0f;
    float radians = degToRad(degrees);
    VNE_LOG_INFO << degrees << " degrees = " << radians << " radians";
    VNE_LOG_INFO << radians << " radians = " << radToDeg(radians) << " degrees";

    // Interpolation
    float a = 0.0f, b = 100.0f;
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Lerp between " << a << " and " << b << ":";
    VNE_LOG_INFO << "  t=0.0: " << lerp(a, b, 0.0f);
    VNE_LOG_INFO << "  t=0.5: " << lerp(a, b, 0.5f);
    VNE_LOG_INFO << "  t=1.0: " << lerp(a, b, 1.0f);

    // Vector lerp
    Vec3f start(0.0f, 0.0f, 0.0f);
    Vec3f end(10.0f, 20.0f, 30.0f);
    Vec3f mid = start.lerp(end, 0.5f);
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Vector lerp midpoint: " << mid;

    // Clamping
    float value = 150.0f;
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "Clamp " << value << " to [0, 100]: " << clamp(value, 0.0f, 100.0f);

    // Approximate equality
    float x = 1.0f / 3.0f;
    float y = x * 3.0f;
    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "1/3 * 3 = " << y;
    VNE_LOG_INFO << "approxEqual(1.0, " << y << "): " << (approxEqual(1.0f, y) ? "true" : "false");
}

int main() {
    LoggingGuard_C logging_guard;

    VNE_LOG_INFO << "VneMath Example: Hello Math";
    VNE_LOG_INFO << "============================";
    VNE_LOG_INFO << "";

    demonstrateVectors();
    demonstrateMatrices();
    demonstrateQuaternions();
    demonstrateMathUtils();

    VNE_LOG_INFO << "";
    VNE_LOG_INFO << "=== Done ===";
    return 0;
}

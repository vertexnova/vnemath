/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Example: Hello Math
 * Demonstrates basic vector, matrix, and quaternion operations
 * ----------------------------------------------------------------------
 */

#include <vertexnova/math/core/core.h>

#include <iostream>
#include <iomanip>

using namespace vne::math;

void demonstrateVectors() {
    std::cout << "=== Vectors ===" << std::endl;

    // 2D Vectors
    Vec2f v2a(1.0f, 2.0f);
    Vec2f v2b(3.0f, 4.0f);
    std::cout << "Vec2f a: " << v2a << std::endl;
    std::cout << "Vec2f b: " << v2b << std::endl;
    std::cout << "a + b: " << (v2a + v2b) << std::endl;
    std::cout << "a dot b: " << v2a.dot(v2b) << std::endl;

    // 3D Vectors
    Vec3f v3a(1.0f, 0.0f, 0.0f);
    Vec3f v3b(0.0f, 1.0f, 0.0f);
    std::cout << "\nVec3f a (X-axis): " << v3a << std::endl;
    std::cout << "Vec3f b (Y-axis): " << v3b << std::endl;
    std::cout << "a cross b (Z-axis): " << v3a.cross(v3b) << std::endl;

    // Vector operations
    Vec3f position(10.0f, 20.0f, 30.0f);
    std::cout << "\nPosition: " << position << std::endl;
    std::cout << "Length: " << position.length() << std::endl;
    std::cout << "Normalized: " << position.normalized() << std::endl;

    // Static factory methods
    std::cout << "\nStatic vectors:" << std::endl;
    std::cout << "Zero: " << Vec3f::zero() << std::endl;
    std::cout << "One: " << Vec3f::one() << std::endl;
    std::cout << "X-Axis: " << Vec3f::xAxis() << std::endl;
    std::cout << "Y-Axis: " << Vec3f::yAxis() << std::endl;
    std::cout << "Z-Axis: " << Vec3f::zAxis() << std::endl;

    // 4D Vectors (homogeneous coordinates)
    Vec4f point(1.0f, 2.0f, 3.0f, 1.0f);  // w=1 for points
    Vec4f direction(1.0f, 0.0f, 0.0f, 0.0f);  // w=0 for directions
    std::cout << "\n4D Point: " << point << std::endl;
    std::cout << "4D Direction: " << direction << std::endl;
}

void demonstrateMatrices() {
    std::cout << "\n=== Matrices ===" << std::endl;

    // Identity matrix
    Mat4f identity = Mat4f::identity();
    std::cout << "Identity 4x4:" << std::endl;
    std::cout << identity << std::endl;

    // Translation matrix
    Mat4f translation = Mat4f::translate(Vec3f(10.0f, 20.0f, 30.0f));
    std::cout << "Translation matrix (10, 20, 30):" << std::endl;
    std::cout << translation << std::endl;

    // Scale matrix
    Mat4f scale = Mat4f::scale(Vec3f(2.0f, 2.0f, 2.0f));
    std::cout << "Scale matrix (2x):" << std::endl;
    std::cout << scale << std::endl;

    // Rotation matrix
    float angle = degToRad(45.0f);
    Mat4f rotY = Mat4f::rotateY(angle);
    std::cout << "Rotation around Y (45 degrees):" << std::endl;
    std::cout << rotY << std::endl;

    // Matrix multiplication
    Mat4f combined = translation * rotY * scale;
    std::cout << "Combined (T * R * S):" << std::endl;
    std::cout << combined << std::endl;

    // Transform a point
    Vec3f point(1.0f, 0.0f, 0.0f);
    Vec3f transformed = combined.transformPoint(point);
    std::cout << "Original point: " << point << std::endl;
    std::cout << "Transformed point: " << transformed << std::endl;

    // Matrix inverse
    Mat4f inverse = combined.inverse();
    Vec3f backToOriginal = inverse.transformPoint(transformed);
    std::cout << "Back to original: " << backToOriginal << std::endl;
}

void demonstrateQuaternions() {
    std::cout << "\n=== Quaternions ===" << std::endl;

    // Identity quaternion (no rotation)
    Quatf identity = Quatf::identity();
    std::cout << "Identity: " << identity << std::endl;

    // Rotation from axis-angle
    Vec3f axis = Vec3f::yAxis();
    float angle = degToRad(90.0f);
    Quatf rotation = Quatf::fromAxisAngle(axis, angle);
    std::cout << "90 deg around Y-axis: " << rotation << std::endl;

    // Rotate a vector
    Vec3f forward = Vec3f::zAxis();
    Vec3f rotated = rotation.rotate(forward);
    std::cout << "Z-axis rotated 90 deg around Y: " << rotated << std::endl;

    // Quaternion from Euler angles
    Quatf euler = Quatf::fromEuler(
        degToRad(0.0f),   // pitch (X)
        degToRad(45.0f),  // yaw (Y)
        degToRad(0.0f)    // roll (Z)
    );
    std::cout << "From Euler (0, 45, 0): " << euler << std::endl;

    // Convert to matrix
    Mat4f rotMatrix = rotation.toMatrix4();
    std::cout << "Quaternion as matrix:" << std::endl;
    std::cout << rotMatrix << std::endl;

    // Quaternion interpolation (slerp)
    Quatf q1 = Quatf::identity();
    Quatf q2 = Quatf::fromAxisAngle(Vec3f::yAxis(), degToRad(180.0f));
    Quatf halfway = Quatf::slerp(q1, q2, 0.5f);
    std::cout << "Slerp halfway between 0 and 180 deg: " << halfway << std::endl;
    std::cout << "Angle: " << radToDeg(halfway.angle()) << " degrees" << std::endl;
}

void demonstrateMathUtils() {
    std::cout << "\n=== Math Utilities ===" << std::endl;

    // Angle conversions
    float degrees = 180.0f;
    float radians = degToRad(degrees);
    std::cout << degrees << " degrees = " << radians << " radians" << std::endl;
    std::cout << radians << " radians = " << radToDeg(radians) << " degrees" << std::endl;

    // Interpolation
    float a = 0.0f, b = 100.0f;
    std::cout << "\nLerp between " << a << " and " << b << ":" << std::endl;
    std::cout << "  t=0.0: " << lerp(a, b, 0.0f) << std::endl;
    std::cout << "  t=0.5: " << lerp(a, b, 0.5f) << std::endl;
    std::cout << "  t=1.0: " << lerp(a, b, 1.0f) << std::endl;

    // Vector lerp
    Vec3f start(0.0f, 0.0f, 0.0f);
    Vec3f end(10.0f, 20.0f, 30.0f);
    Vec3f mid = start.lerp(end, 0.5f);
    std::cout << "\nVector lerp midpoint: " << mid << std::endl;

    // Clamping
    float value = 150.0f;
    std::cout << "\nClamp " << value << " to [0, 100]: " << clamp(value, 0.0f, 100.0f) << std::endl;

    // Approximate equality
    float x = 1.0f / 3.0f;
    float y = x * 3.0f;
    std::cout << "\n1/3 * 3 = " << y << std::endl;
    std::cout << "approxEqual(1.0, " << y << "): " << (approxEqual(1.0f, y) ? "true" : "false") << std::endl;
}

int main() {
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "VneMath Example: Hello Math" << std::endl;
    std::cout << "============================\n" << std::endl;

    demonstrateVectors();
    demonstrateMatrices();
    demonstrateQuaternions();
    demonstrateMathUtils();

    std::cout << "\n=== Done ===" << std::endl;
    return 0;
}

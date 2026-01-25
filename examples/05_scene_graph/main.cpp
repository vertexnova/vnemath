/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Example: Scene Graph
 * Demonstrates hierarchical transforms with TransformNode
 * ----------------------------------------------------------------------
 */

#include "common/logging_guard.h"

#include <vertexnova/math/core/core.h>
#include <vertexnova/math/transform_node.h>

#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>

using namespace vne::math;
using vne::math::examples::LoggingGuard_C;

Vec3f extractPosition(const Mat4f& matrix) {
    return Vec3f(matrix[3][0], matrix[3][1], matrix[3][2]);
}

void demonstrateBasicHierarchy() {
    std::cout << "=== Basic Parent-Child Hierarchy ===" << std::endl;

    TransformNode parent;
    TransformNode child;

    // Set parent at position (10, 0, 0)
    parent.setLocalTransform(Mat4f::translate(Vec3f(10.0f, 0.0f, 0.0f)));

    // Make child a child of parent
    child.setParent(&parent);

    // Set child at local position (0, 5, 0) relative to parent
    child.setLocalTransform(Mat4f::translate(Vec3f(0.0f, 5.0f, 0.0f)));

    std::cout << "\nParent local position: " << extractPosition(parent.getLocalTransform()) << std::endl;
    std::cout << "Parent world position: " << extractPosition(parent.getModelMatrix()) << std::endl;

    std::cout << "\nChild local position: " << extractPosition(child.getLocalTransform()) << std::endl;
    std::cout << "Child world position: " << extractPosition(child.getModelMatrix()) << std::endl;
    std::cout << "  (Expected: (10, 5, 0) = parent + child local)" << std::endl;

    // Move parent - child should follow
    std::cout << "\nMoving parent to (20, 0, 0)..." << std::endl;
    parent.setLocalTransform(Mat4f::translate(Vec3f(20.0f, 0.0f, 0.0f)));

    std::cout << "Child world position: " << extractPosition(child.getModelMatrix()) << std::endl;
    std::cout << "  (Expected: (20, 5, 0))" << std::endl;
}

void demonstrateRobotArm() {
    std::cout << "\n=== Robot Arm Example ===" << std::endl;

    // Create a simple robot arm: base -> shoulder -> elbow -> wrist
    TransformNode base;
    TransformNode shoulder;
    TransformNode elbow;
    TransformNode wrist;

    // Set up hierarchy
    shoulder.setParent(&base);
    elbow.setParent(&shoulder);
    wrist.setParent(&elbow);

    // Arm segment lengths
    float shoulder_length = 3.0f;
    float forearm_length = 2.5f;
    float hand_length = 1.0f;

    // Initial pose: arm straight up
    base.setLocalTransform(Mat4f::translate(Vec3f(0.0f, 0.0f, 0.0f)));
    shoulder.setLocalTransform(Mat4f::translate(Vec3f(0.0f, shoulder_length, 0.0f)));
    elbow.setLocalTransform(Mat4f::translate(Vec3f(0.0f, forearm_length, 0.0f)));
    wrist.setLocalTransform(Mat4f::translate(Vec3f(0.0f, hand_length, 0.0f)));

    std::cout << "\nInitial pose (arm straight up):" << std::endl;
    std::cout << "  Base: " << extractPosition(base.getModelMatrix()) << std::endl;
    std::cout << "  Shoulder: " << extractPosition(shoulder.getModelMatrix()) << std::endl;
    std::cout << "  Elbow: " << extractPosition(elbow.getModelMatrix()) << std::endl;
    std::cout << "  Wrist: " << extractPosition(wrist.getModelMatrix()) << std::endl;

    // Rotate shoulder 90 degrees forward (around X)
    std::cout << "\nRotating shoulder 90 degrees forward..." << std::endl;
    Mat4f shoulder_rotate = Mat4f::rotateX(degToRad(-90.0f));
    Mat4f shoulder_translate = Mat4f::translate(Vec3f(0.0f, shoulder_length, 0.0f));
    shoulder.setLocalTransform(shoulder_translate * shoulder_rotate);

    std::cout << "  Shoulder: " << extractPosition(shoulder.getModelMatrix()) << std::endl;
    std::cout << "  Elbow: " << extractPosition(elbow.getModelMatrix()) << std::endl;
    std::cout << "  Wrist: " << extractPosition(wrist.getModelMatrix()) << std::endl;

    // Bend elbow 45 degrees
    std::cout << "\nBending elbow 45 degrees..." << std::endl;
    Mat4f elbow_rotate = Mat4f::rotateX(degToRad(-45.0f));
    Mat4f elbow_translate = Mat4f::translate(Vec3f(0.0f, forearm_length, 0.0f));
    elbow.setLocalTransform(elbow_translate * elbow_rotate);

    std::cout << "  Elbow: " << extractPosition(elbow.getModelMatrix()) << std::endl;
    std::cout << "  Wrist: " << extractPosition(wrist.getModelMatrix()) << std::endl;
}

void demonstrateSolarSystem() {
    std::cout << "\n=== Solar System Example ===" << std::endl;

    // Sun at center, Earth orbits Sun, Moon orbits Earth
    TransformNode sun;
    TransformNode earth;
    TransformNode moon;

    earth.setParent(&sun);
    moon.setParent(&earth);

    // Orbital distances
    float earth_orbit = 10.0f;
    float moon_orbit = 2.0f;

    std::cout << "\nSimulating orbital positions over time:" << std::endl;

    for (int frame = 0; frame <= 4; frame++) {
        float time = frame * 0.25f;  // 0 to 1 over 4 frames

        // Earth orbits sun (one full orbit per time unit)
        float earth_angle = time * 360.0f;
        Mat4f earth_orbit_mat = Mat4f::rotateY(degToRad(earth_angle));
        Mat4f earth_offset = Mat4f::translate(Vec3f(earth_orbit, 0.0f, 0.0f));
        earth.setLocalTransform(earth_orbit_mat * earth_offset);

        // Moon orbits earth faster (4 orbits per time unit)
        float moon_angle = time * 360.0f * 4.0f;
        Mat4f moon_orbit_mat = Mat4f::rotateY(degToRad(moon_angle));
        Mat4f moon_offset = Mat4f::translate(Vec3f(moon_orbit, 0.0f, 0.0f));
        moon.setLocalTransform(moon_orbit_mat * moon_offset);

        std::cout << "\n  Time " << time << ":" << std::endl;
        std::cout << "    Sun: " << extractPosition(sun.getModelMatrix()) << std::endl;
        std::cout << "    Earth: " << extractPosition(earth.getModelMatrix()) << std::endl;
        std::cout << "    Moon: " << extractPosition(moon.getModelMatrix()) << std::endl;
    }
}

void demonstrateMultipleChildren() {
    std::cout << "\n=== Multiple Children (Vehicle) ===" << std::endl;

    // Car body with 4 wheels
    TransformNode car_body;
    TransformNode wheel_fl;  // Front-left
    TransformNode wheel_fr;  // Front-right
    TransformNode wheel_bl;  // Back-left
    TransformNode wheel_br;  // Back-right

    wheel_fl.setParent(&car_body);
    wheel_fr.setParent(&car_body);
    wheel_bl.setParent(&car_body);
    wheel_br.setParent(&car_body);

    // Wheel positions relative to car center
    float wheel_x = 1.0f;
    float wheel_z_front = 1.5f;
    float wheel_z_back = -1.5f;
    float wheel_y = -0.5f;

    wheel_fl.setLocalTransform(Mat4f::translate(Vec3f(-wheel_x, wheel_y, wheel_z_front)));
    wheel_fr.setLocalTransform(Mat4f::translate(Vec3f(wheel_x, wheel_y, wheel_z_front)));
    wheel_bl.setLocalTransform(Mat4f::translate(Vec3f(-wheel_x, wheel_y, wheel_z_back)));
    wheel_br.setLocalTransform(Mat4f::translate(Vec3f(wheel_x, wheel_y, wheel_z_back)));

    std::cout << "\nCar at origin:" << std::endl;
    std::cout << "  Body: " << extractPosition(car_body.getModelMatrix()) << std::endl;
    std::cout << "  Wheel FL: " << extractPosition(wheel_fl.getModelMatrix()) << std::endl;
    std::cout << "  Wheel FR: " << extractPosition(wheel_fr.getModelMatrix()) << std::endl;
    std::cout << "  Wheel BL: " << extractPosition(wheel_bl.getModelMatrix()) << std::endl;
    std::cout << "  Wheel BR: " << extractPosition(wheel_br.getModelMatrix()) << std::endl;

    // Move and rotate the car
    std::cout << "\nMoving car to (10, 0, 5) and rotating 45 degrees..." << std::endl;
    Mat4f car_transform = Mat4f::translate(Vec3f(10.0f, 0.0f, 5.0f)) * Mat4f::rotateY(degToRad(45.0f));
    car_body.setLocalTransform(car_transform);

    std::cout << "  Body: " << extractPosition(car_body.getModelMatrix()) << std::endl;
    std::cout << "  Wheel FL: " << extractPosition(wheel_fl.getModelMatrix()) << std::endl;
    std::cout << "  Wheel FR: " << extractPosition(wheel_fr.getModelMatrix()) << std::endl;
    std::cout << "  Wheel BL: " << extractPosition(wheel_bl.getModelMatrix()) << std::endl;
    std::cout << "  Wheel BR: " << extractPosition(wheel_br.getModelMatrix()) << std::endl;
}

int main() {
    LoggingGuard_C logging_guard;

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "VneMath Example: Scene Graph" << std::endl;
    std::cout << "============================\n" << std::endl;

    demonstrateBasicHierarchy();
    demonstrateRobotArm();
    demonstrateSolarSystem();
    demonstrateMultipleChildren();

    std::cout << "\n=== Done ===" << std::endl;
    return 0;
}

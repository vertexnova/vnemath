/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Author:    Ajeet Singh Yadav
 * Created:   January 2026
 *
 * Autodoc:   yes
 * ----------------------------------------------------------------------
 */

// Project includes
#include "vertexnova/math/geometry/frustum.h"

#include "vertexnova/math/geometry/aabb.h"
#include "vertexnova/math/geometry/sphere.h"
#include "vertexnova/math/mat4x4f.h"

namespace vne::math {

void Frustum::extractFromMatrix(const Mat4x4f& mat) noexcept {
    // Gribb/Hartmann plane extraction method
    // Reference: http://www.cs.otago.ac.nz/postgrads/alexis/planeExtraction.pdf
    Vec4f row0 = mat.getRow(0);
    Vec4f row1 = mat.getRow(1);
    Vec4f row2 = mat.getRow(2);
    Vec4f row3 = mat.getRow(3);

    // Left plane: row3 + row0
    left_ = Plane(Vec4f(row3 + row0));
    // Right plane: row3 - row0
    right_ = Plane(Vec4f(row3 - row0));
    // Bottom plane: row3 + row1
    bottom_ = Plane(Vec4f(row3 + row1));
    // Top plane: row3 - row1
    top_ = Plane(Vec4f(row3 - row1));
    // Near plane: row3 + row2
    near_ = Plane(Vec4f(row3 + row2));
    // Far plane: row3 - row2
    far_ = Plane(Vec4f(row3 - row2));

    // Normalize all planes
    near_.normalize();
    far_.normalize();
    left_.normalize();
    right_.normalize();
    bottom_.normalize();
    top_.normalize();
}

bool Frustum::contains(const Vec3f& point, float eps) const noexcept {
    // A point is inside the frustum if it's on the positive side of all planes
    return near_.isOnPositiveSide(point, eps) && far_.isOnPositiveSide(point, eps) && left_.isOnPositiveSide(point, eps)
           && right_.isOnPositiveSide(point, eps) && bottom_.isOnPositiveSide(point, eps)
           && top_.isOnPositiveSide(point, eps);
}

bool Frustum::intersects(const Sphere& sphere) const noexcept {
    // A sphere intersects the frustum if it's not completely outside any plane
    const Vec3f& center = sphere.center();
    float radius = sphere.radius();

    if (near_.signedDistance(center) < -radius)
        return false;
    if (far_.signedDistance(center) < -radius)
        return false;
    if (left_.signedDistance(center) < -radius)
        return false;
    if (right_.signedDistance(center) < -radius)
        return false;
    if (bottom_.signedDistance(center) < -radius)
        return false;
    if (top_.signedDistance(center) < -radius)
        return false;

    return true;
}

bool Frustum::intersects(const Aabb& aabb) const noexcept {
    // For each plane, check if the AABB is completely outside
    // Use the "p-vertex" method: check the corner most aligned with the plane normal
    const Plane* planes[] = {&near_, &far_, &left_, &right_, &bottom_, &top_};

    for (const Plane* plane : planes) {
        // Find the positive vertex (p-vertex) - the corner furthest in the direction of the normal
        Vec3f p_vertex;
        p_vertex.x = (plane->normal.x >= 0) ? aabb.max().x : aabb.min().x;
        p_vertex.y = (plane->normal.y >= 0) ? aabb.max().y : aabb.min().y;
        p_vertex.z = (plane->normal.z >= 0) ? aabb.max().z : aabb.min().z;

        // If the p-vertex is outside, the entire AABB is outside
        if (plane->signedDistance(p_vertex) < 0) {
            return false;
        }
    }

    return true;
}

bool Frustum::containsFully(const Sphere& sphere) const noexcept {
    const Vec3f& center = sphere.center();
    float radius = sphere.radius();

    // Sphere is fully inside if its entire volume is on the positive side of all planes
    if (near_.signedDistance(center) < radius)
        return false;
    if (far_.signedDistance(center) < radius)
        return false;
    if (left_.signedDistance(center) < radius)
        return false;
    if (right_.signedDistance(center) < radius)
        return false;
    if (bottom_.signedDistance(center) < radius)
        return false;
    if (top_.signedDistance(center) < radius)
        return false;

    return true;
}

bool Frustum::containsFully(const Aabb& aabb) const noexcept {
    // Check all 8 corners of the AABB
    for (uint32_t i = 0; i < 8; ++i) {
        if (!contains(aabb.corner(i))) {
            return false;
        }
    }
    return true;
}

bool Frustum::operator==(const Frustum& other) const noexcept {
    return near_ == other.near_ && far_ == other.far_ && left_ == other.left_ && right_ == other.right_
           && bottom_ == other.bottom_ && top_ == other.top_;
}

bool Frustum::operator!=(const Frustum& other) const noexcept {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Frustum& frustum) {
    return os << "Frustum: [near: " << frustum.near_ << ", far: " << frustum.far_ << ", left: " << frustum.left_
              << ", right: " << frustum.right_ << ", bottom: " << frustum.bottom_ << ", top: " << frustum.top_ << "]";
}

}  // namespace vne::math

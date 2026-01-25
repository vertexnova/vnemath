/* ---------------------------------------------------------------------
 * Copyright (c) 2024 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Author:    Ajeet Singh Yadav
 * Created:   September-2024
 *
 * Autodoc:   yes
 * ----------------------------------------------------------------------
 */

// Project includes
#include "vertexnova/math/transform_node.h"

namespace VNE {
namespace Math {

//------------------------------------------------------------------------------
TransformNode_C::TransformNode_C()
    : _local_transform(Mat4x4f_C::Identity())
    , _root_transform(Mat4x4f_C::Identity())
    , _parent(nullptr) {}

//------------------------------------------------------------------------------
TransformNode_C::~TransformNode_C() {
    for (TransformNode_C* child : _children) {
        if (child) {
            child->SetParent(nullptr);
        }
    }
}

//------------------------------------------------------------------------------
void TransformNode_C::SetLocalTransform(const Mat4x4f_C& transform) {
    _local_transform = transform;
}

//------------------------------------------------------------------------------
Mat4x4f_C TransformNode_C::GetLocalTransform() const {
    return _local_transform;
}

//------------------------------------------------------------------------------
Mat4x4f_C TransformNode_C::GetModelMatrix() const {
    return _root_transform * _local_transform;
}

//------------------------------------------------------------------------------
void TransformNode_C::SetParent(TransformNode_C* parent) {
    if (_parent) {
        _parent->RemoveChild(this);
    }
    _parent = parent;
    if (_parent) {
        _parent->AddChild(this);
        UpdateRootTransform();
    }
}

//------------------------------------------------------------------------------
TransformNode_C* TransformNode_C::GetParent() const {
    return _parent;
}

//------------------------------------------------------------------------------
void TransformNode_C::AddChild(TransformNode_C* child) {
    if (child && std::find(_children.begin(), _children.end(), child) == _children.end()) {
        _children.push_back(child);
    }
}

//------------------------------------------------------------------------------
void TransformNode_C::RemoveChild(TransformNode_C* child) {
    auto it = std::find(_children.begin(), _children.end(), child);
    if (it != _children.end()) {
        _children.erase(it);
        if (child) {
            child->SetParent(nullptr);
        }
    }
}

//------------------------------------------------------------------------------
void TransformNode_C::RemoveFromParent() {
    if (_parent) {
        _parent->RemoveChild(this);
        _parent = nullptr;
    }
}

//------------------------------------------------------------------------------
std::vector<TransformNode_C*> TransformNode_C::GetChildren() const {
    return _children;
}

//------------------------------------------------------------------------------
size_t TransformNode_C::NumChildren() const {
    return _children.size();
}

//------------------------------------------------------------------------------
bool TransformNode_C::IsRoot() const {
    return _parent == nullptr;
}

//------------------------------------------------------------------------------
bool TransformNode_C::IsLeaf() const {
    return _children.empty();
}

//------------------------------------------------------------------------------
void TransformNode_C::UpdateRootTransform() {
    if (_parent) {
        _root_transform = _parent->GetModelMatrix();
    } else {
        _root_transform = Mat4x4f_C::Identity();
    }
}

//------------------------------------------------------------------------------
void TransformNode_C::ComposeTransform(const Mat4x4f_C& transform) {
    _local_transform = transform * _local_transform;
}

}  // namespace Math
}  // namespace VNE

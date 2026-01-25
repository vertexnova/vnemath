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

// Corresponding header
#include "vertexnova/math/transform_node.h"

// System headers
#include <algorithm>

namespace vne::math {

//------------------------------------------------------------------------------
TransformNode::TransformNode() noexcept
    : local_transform_(Mat4x4f::identity())
    , root_transform_(Mat4x4f::identity())
    , parent_(nullptr) {}

//------------------------------------------------------------------------------
TransformNode::~TransformNode() noexcept {
    for (TransformNode* child : children_) {
        if (child) {
            child->setParent(nullptr);
        }
    }
}

//------------------------------------------------------------------------------
void TransformNode::setLocalTransform(const Mat4x4f& transform) noexcept {
    local_transform_ = transform;
}

//------------------------------------------------------------------------------
Mat4x4f TransformNode::getLocalTransform() const noexcept {
    return local_transform_;
}

//------------------------------------------------------------------------------
Mat4x4f TransformNode::getModelMatrix() const noexcept {
    return root_transform_ * local_transform_;
}

//------------------------------------------------------------------------------
void TransformNode::setParent(TransformNode* parent) noexcept {
    if (parent_) {
        parent_->removeChild(this);
    }
    parent_ = parent;
    if (parent_) {
        parent_->addChild(this);
        updateRootTransform();
    }
}

//------------------------------------------------------------------------------
TransformNode* TransformNode::getParent() const noexcept {
    return parent_;
}

//------------------------------------------------------------------------------
void TransformNode::addChild(TransformNode* child) noexcept {
    if (child && std::find(children_.begin(), children_.end(), child) == children_.end()) {
        children_.push_back(child);
    }
}

//------------------------------------------------------------------------------
void TransformNode::removeChild(TransformNode* child) noexcept {
    auto it = std::find(children_.begin(), children_.end(), child);
    if (it != children_.end()) {
        children_.erase(it);
        if (child) {
            child->setParent(nullptr);
        }
    }
}

//------------------------------------------------------------------------------
void TransformNode::removeFromParent() noexcept {
    if (parent_) {
        parent_->removeChild(this);
        parent_ = nullptr;
    }
}

//------------------------------------------------------------------------------
std::vector<TransformNode*> TransformNode::getChildren() const noexcept {
    return children_;
}

//------------------------------------------------------------------------------
size_t TransformNode::numChildren() const noexcept {
    return children_.size();
}

//------------------------------------------------------------------------------
bool TransformNode::isRoot() const noexcept {
    return parent_ == nullptr;
}

//------------------------------------------------------------------------------
bool TransformNode::isLeaf() const noexcept {
    return children_.empty();
}

//------------------------------------------------------------------------------
void TransformNode::updateRootTransform() noexcept {
    if (parent_) {
        root_transform_ = parent_->getModelMatrix();
    } else {
        root_transform_ = Mat4x4f::identity();
    }
}

//------------------------------------------------------------------------------
void TransformNode::composeTransform(const Mat4x4f& transform) noexcept {
    local_transform_ = transform * local_transform_;
}

}  // namespace vne::math

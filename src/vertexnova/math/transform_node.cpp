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

namespace vne::math {


//------------------------------------------------------------------------------
TransformNode::TransformNode()
    : local_transform_(Mat4x4f::identity())
    , root_transform_(Mat4x4f::identity())
    , parent_(nullptr) {}

//------------------------------------------------------------------------------
TransformNode::~TransformNode() {
    for (TransformNode* child : children_) {
        if (child) {
            child->setParent(nullptr);
        }
    }
}

//------------------------------------------------------------------------------
void TransformNode::setLocalTransform(const Mat4x4f& transform) {
    local_transform_ = transform;
}

//------------------------------------------------------------------------------
Mat4x4f TransformNode::getLocalTransform() const {
    return local_transform_;
}

//------------------------------------------------------------------------------
Mat4x4f TransformNode::getModelMatrix() const {
    return root_transform_ * local_transform_;
}

//------------------------------------------------------------------------------
void TransformNode::setParent(TransformNode* parent) {
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
TransformNode* TransformNode::getParent() const {
    return parent_;
}

//------------------------------------------------------------------------------
void TransformNode::addChild(TransformNode* child) {
    if (child && std::find(children_.begin(), children_.end(), child) == children_.end()) {
        children_.push_back(child);
    }
}

//------------------------------------------------------------------------------
void TransformNode::removeChild(TransformNode* child) {
    auto it = std::find(children_.begin(), children_.end(), child);
    if (it != children_.end()) {
        children_.erase(it);
        if (child) {
            child->setParent(nullptr);
        }
    }
}

//------------------------------------------------------------------------------
void TransformNode::removeFromParent() {
    if (parent_) {
        parent_->removeChild(this);
        parent_ = nullptr;
    }
}

//------------------------------------------------------------------------------
std::vector<TransformNode*> TransformNode::getChildren() const {
    return children_;
}

//------------------------------------------------------------------------------
size_t TransformNode::numChildren() const {
    return children_.size();
}

//------------------------------------------------------------------------------
bool TransformNode::isRoot() const {
    return parent_ == nullptr;
}

//------------------------------------------------------------------------------
bool TransformNode::isLeaf() const {
    return children_.empty();
}

//------------------------------------------------------------------------------
void TransformNode::updateRootTransform() {
    if (parent_) {
        root_transform_ = parent_->getModelMatrix();
    } else {
        root_transform_ = Mat4x4f::identity();
    }
}

//------------------------------------------------------------------------------
void TransformNode::composeTransform(const Mat4x4f& transform) {
    local_transform_ = transform * local_transform_;
}


}  // namespace vne::math

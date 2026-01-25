#pragma once
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

/**
 * @file transform_node.h
 * @brief Hierarchical transformation node for scene graphs.
 */

// Project includes
#include "mat4x4f.h"

// Standard library includes
#include <vector>

namespace vne::math {

class TransformNode {
   public:
    TransformNode();
    ~TransformNode();

    void setLocalTransform(const Mat4x4f& transform);
    Mat4x4f getLocalTransform() const;
    Mat4x4f getModelMatrix() const;
    void setParent(TransformNode* parent);
    TransformNode* getParent() const;
    std::vector<TransformNode*> getChildren() const;
    bool isRoot() const;
    bool isLeaf() const;
    size_t numChildren() const;
    void addChild(TransformNode* child);
    void removeChild(TransformNode* child);
    void removeFromParent();
    void updateRootTransform();
    void composeTransform(const Mat4x4f& transform);

   private:
    Mat4x4f local_transform_;
    Mat4x4f root_transform_;
    TransformNode* parent_;
    std::vector<TransformNode*> children_;
};

// Legacy type alias for backward compatibility
using TransformNode_C = TransformNode;

}  // namespace vne::math

// Legacy namespace aliases
namespace VNE {
namespace Math {
using TransformNode_C = vne::math::TransformNode;
using TransformNode = vne::math::TransformNode;
}  // namespace Math
}  // namespace VNE

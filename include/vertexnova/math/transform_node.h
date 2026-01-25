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
    TransformNode() noexcept;
    ~TransformNode() noexcept;

    void setLocalTransform(const Mat4x4f& transform) noexcept;
    [[nodiscard]] Mat4x4f getLocalTransform() const noexcept;
    [[nodiscard]] Mat4x4f getModelMatrix() const noexcept;
    void setParent(TransformNode* parent) noexcept;
    [[nodiscard]] TransformNode* getParent() const noexcept;
    [[nodiscard]] std::vector<TransformNode*> getChildren() const noexcept;
    [[nodiscard]] bool isRoot() const noexcept;
    [[nodiscard]] bool isLeaf() const noexcept;
    [[nodiscard]] size_t numChildren() const noexcept;
    void addChild(TransformNode* child) noexcept;
    void removeChild(TransformNode* child) noexcept;
    void removeFromParent() noexcept;
    void updateRootTransform() noexcept;
    void composeTransform(const Mat4x4f& transform) noexcept;

   private:
    Mat4x4f local_transform_;
    Mat4x4f root_transform_;
    TransformNode* parent_;
    std::vector<TransformNode*> children_;
};

}  // namespace vne::math

#ifndef VNE_MATH_TRANSFORM_NODE_H
#define VNE_MATH_TRANSFORM_NODE_H
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

namespace VNE {
namespace Math {

class TransformNode_C {
   public:
    TransformNode_C();
    ~TransformNode_C();

    void SetLocalTransform(const Mat4x4f_C& transform);
    Mat4x4f_C GetLocalTransform() const;
    Mat4x4f_C GetModelMatrix() const;
    void SetParent(TransformNode_C* parent);
    TransformNode_C* GetParent() const;
    std::vector<TransformNode_C*> GetChildren() const;
    bool IsRoot() const;
    bool IsLeaf() const;
    size_t NumChildren() const;
    void AddChild(TransformNode_C* child);
    void RemoveChild(TransformNode_C* child);
    void RemoveFromParent();
    void UpdateRootTransform();
    void ComposeTransform(const Mat4x4f_C& transform);

   private:
    Mat4x4f_C _local_transform;
    Mat4x4f_C _root_transform;
    TransformNode_C* _parent;
    std::vector<TransformNode_C*> _children;
};

}  // namespace Math
}  // namespace VNE

#endif  // VNE_MATH_TRANSFORM_NODE_H

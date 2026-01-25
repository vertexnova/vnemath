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
 * @brief Defines the TransformNode class for hierarchical transformations.
 */

// Project includes
#include "vertexnova/math/core/mat4x4f.h"

// Standard library includes
#include <vector>

namespace vne::math {

/**
 * @class TransformNode
 * @brief Represents a node in a hierarchical transformation tree (scene graph).
 *
 * TransformNode maintains both a local transformation and a computed world
 * transformation based on the parent hierarchy. This is commonly used for
 * scene graphs in 3D applications where objects have parent-child relationships.
 */
class TransformNode {
   public:
    /** @brief Default constructor, creates a root node with identity transform */
    TransformNode() noexcept;

    /**
     * @brief Destructor
     *
     * Automatically removes this node from its parent's child list.
     */
    ~TransformNode() noexcept;

   public:
    /**
     * @brief Sets the local transformation matrix
     * @param transform The local transformation relative to parent
     */
    void setLocalTransform(const Mat4x4f& transform) noexcept;

    /**
     * @brief Gets the local transformation matrix
     * @return The local transformation relative to parent
     */
    [[nodiscard]] Mat4x4f getLocalTransform() const noexcept;

    /**
     * @brief Gets the world transformation matrix
     * @return The accumulated transformation from root to this node
     */
    [[nodiscard]] Mat4x4f getModelMatrix() const noexcept;

    /**
     * @brief Sets the parent node
     * @param parent The new parent node, or nullptr to make this a root
     *
     * This will update the parent-child relationships and recalculate
     * the world transformation.
     */
    void setParent(TransformNode* parent) noexcept;

    /**
     * @brief Gets the parent node
     * @return Pointer to parent node, or nullptr if this is a root
     */
    [[nodiscard]] TransformNode* getParent() const noexcept;

    /**
     * @brief Gets all child nodes
     * @return Vector of pointers to child nodes
     */
    [[nodiscard]] std::vector<TransformNode*> getChildren() const noexcept;

    /**
     * @brief Checks if this node is a root (has no parent)
     * @return true if this node has no parent
     */
    [[nodiscard]] bool isRoot() const noexcept;

    /**
     * @brief Checks if this node is a leaf (has no children)
     * @return true if this node has no children
     */
    [[nodiscard]] bool isLeaf() const noexcept;

    /**
     * @brief Gets the number of children
     * @return The number of child nodes
     */
    [[nodiscard]] size_t numChildren() const noexcept;

    /**
     * @brief Adds a child node
     * @param child The node to add as a child
     *
     * The child's parent will be set to this node.
     */
    void addChild(TransformNode* child) noexcept;

    /**
     * @brief Removes a child node
     * @param child The node to remove
     *
     * The child's parent will be set to nullptr.
     */
    void removeChild(TransformNode* child) noexcept;

    /**
     * @brief Removes this node from its parent
     *
     * Equivalent to calling parent->removeChild(this).
     */
    void removeFromParent() noexcept;

    /**
     * @brief Recalculates the world transformation
     *
     * Should be called after modifying the parent hierarchy or
     * after the parent's transformation has changed.
     */
    void updateRootTransform() noexcept;

    /**
     * @brief Composes (multiplies) a transformation with the local transform
     * @param transform The transformation to apply
     */
    void composeTransform(const Mat4x4f& transform) noexcept;

   private:
    Mat4x4f local_transform_;               ///< Local transformation relative to parent
    Mat4x4f root_transform_;                ///< Cached world transformation
    TransformNode* parent_;                 ///< Parent node (nullptr if root)
    std::vector<TransformNode*> children_;  ///< Child nodes
};

}  // namespace vne::math

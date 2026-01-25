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

#include <gtest/gtest.h>

#include "vertexnova/math/math_utils.h"
#include "vertexnova/math/transform_node.h"

using namespace VNE;

// Test fixture for TransformNode
class TransformNodeTest_C : public ::testing::Test {
   protected:
    void SetUp() override {
        // This function runs before each test
    }

    void TearDown() override {
        // This function runs after each test
    }

   protected:
    vne::math::TransformNode _node;
    vne::math::TransformNode _parent;
    vne::math::TransformNode _child;
};

// Test default constructor and matrix initialization
TEST_F(TransformNodeTest_C, DefaultConstructor) {
    // Verify that the local and root transforms are initialized to identity matrices
    EXPECT_EQ(_node.getLocalTransform(), vne::math::Mat4x4f::identity());
    EXPECT_EQ(_node.getModelMatrix(), vne::math::Mat4x4f::identity());
    EXPECT_TRUE(_node.isRoot());
    EXPECT_TRUE(_node.isLeaf());
}

// Test setting and getting the local transformation matrix
TEST_F(TransformNodeTest_C, SetLocalTransform) {
    vne::math::Mat4x4f custom_transform = vne::math::Mat4x4f::translate(vne::math::Vec3f(1.0f, 2.0f, 3.0f));
    _node.setLocalTransform(custom_transform);

    EXPECT_EQ(_node.getLocalTransform(), custom_transform);
}

// Test the parent-child relationship
TEST_F(TransformNodeTest_C, ParentChildRelationship) {
    // Set the parent
    _child.setParent(&_parent);

    // Verify the parent-child relationship
    EXPECT_EQ(_child.getParent(), &_parent);
    EXPECT_EQ(_parent.numChildren(), 1);
    EXPECT_EQ(_parent.getChildren()[0], &_child);
    EXPECT_FALSE(_child.isRoot());
    EXPECT_TRUE(_parent.isRoot());
    EXPECT_TRUE(_child.isLeaf());
    EXPECT_FALSE(_parent.isLeaf());

    // Remove the child from the parent
    _child.removeFromParent();
    EXPECT_EQ(_child.getParent(), nullptr);
    EXPECT_EQ(_parent.numChildren(), 0);
    EXPECT_TRUE(_child.isRoot());
}

// Test adding and removing children
TEST_F(TransformNodeTest_C, AddRemoveChild) {
    // Add a child
    _parent.addChild(&_child);
    EXPECT_EQ(_parent.numChildren(), 1);
    EXPECT_EQ(_parent.getChildren()[0], &_child);

    // Remove the child
    _parent.removeChild(&_child);
    EXPECT_EQ(_parent.numChildren(), 0);
    EXPECT_EQ(_child.getParent(), nullptr);
}

// Test that child inherits the parent's root transform
TEST_F(TransformNodeTest_C, InheritedRootTransform) {
    vne::math::Mat4x4f parent_transform = vne::math::Mat4x4f::translate(vne::math::Vec3f(10.0f, 0.0f, 0.0f));
    vne::math::Mat4x4f child_transform = vne::math::Mat4x4f::translate(vne::math::Vec3f(0.0f, 5.0f, 0.0f));

    _parent.setLocalTransform(parent_transform);
    _child.setLocalTransform(child_transform);

    // Set parent-child relationship
    _child.setParent(&_parent);

    // Verify that the child's model matrix is the combined transform
    vne::math::Mat4x4f expected_model_matrix = parent_transform * child_transform;
    EXPECT_EQ(_child.getModelMatrix(), expected_model_matrix);
}

// Test composing a transformation
TEST_F(TransformNodeTest_C, ComposeTransform) {
    vne::math::Mat4x4f scale_transform = vne::math::Mat4x4f::scale(vne::math::Vec3f(2.0f, 2.0f, 2.0f));
    _node.composeTransform(scale_transform);

    // Verify that the local transform is updated
    EXPECT_EQ(_node.getLocalTransform(), scale_transform * vne::math::Mat4x4f::identity());
}

// Test destructor handling
TEST_F(TransformNodeTest_C, DestructorTest) {
    // Create parent-child hierarchy within a block scope
    {
        vne::math::TransformNode parent;
        vne::math::TransformNode* child = new vne::math::TransformNode();
        child->SetParent(&parent);

        // Verify parent has one child before destruction
        EXPECT_EQ(parent.numChildren(), 1);

        // Child will be destroyed automatically at the end of this scope
        delete child;
    }
}

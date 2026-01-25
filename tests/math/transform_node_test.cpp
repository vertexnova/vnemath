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

// Test fixture for TransformNode_C
class TransformNodeTest_C : public ::testing::Test {
   protected:
    void SetUp() override {
        // This function runs before each test
    }

    void TearDown() override {
        // This function runs after each test
    }

   protected:
    Math::TransformNode_C _node;
    Math::TransformNode_C _parent;
    Math::TransformNode_C _child;
};

// Test default constructor and matrix initialization
TEST_F(TransformNodeTest_C, DefaultConstructor) {
    // Verify that the local and root transforms are initialized to identity matrices
    EXPECT_EQ(_node.GetLocalTransform(), Math::Mat4x4f_C::Identity());
    EXPECT_EQ(_node.GetModelMatrix(), Math::Mat4x4f_C::Identity());
    EXPECT_TRUE(_node.IsRoot());
    EXPECT_TRUE(_node.IsLeaf());
}

// Test setting and getting the local transformation matrix
TEST_F(TransformNodeTest_C, SetLocalTransform) {
    Math::Mat4x4f_C custom_transform = Math::Mat4x4f_C::Translate(Math::Vec3f_C(1.0f, 2.0f, 3.0f));
    _node.SetLocalTransform(custom_transform);

    EXPECT_EQ(_node.GetLocalTransform(), custom_transform);
}

// Test the parent-child relationship
TEST_F(TransformNodeTest_C, ParentChildRelationship) {
    // Set the parent
    _child.SetParent(&_parent);

    // Verify the parent-child relationship
    EXPECT_EQ(_child.GetParent(), &_parent);
    EXPECT_EQ(_parent.NumChildren(), 1);
    EXPECT_EQ(_parent.GetChildren()[0], &_child);
    EXPECT_FALSE(_child.IsRoot());
    EXPECT_TRUE(_parent.IsRoot());
    EXPECT_TRUE(_child.IsLeaf());
    EXPECT_FALSE(_parent.IsLeaf());

    // Remove the child from the parent
    _child.RemoveFromParent();
    EXPECT_EQ(_child.GetParent(), nullptr);
    EXPECT_EQ(_parent.NumChildren(), 0);
    EXPECT_TRUE(_child.IsRoot());
}

// Test adding and removing children
TEST_F(TransformNodeTest_C, AddRemoveChild) {
    // Add a child
    _parent.AddChild(&_child);
    EXPECT_EQ(_parent.NumChildren(), 1);
    EXPECT_EQ(_parent.GetChildren()[0], &_child);

    // Remove the child
    _parent.RemoveChild(&_child);
    EXPECT_EQ(_parent.NumChildren(), 0);
    EXPECT_EQ(_child.GetParent(), nullptr);
}

// Test that child inherits the parent's root transform
TEST_F(TransformNodeTest_C, InheritedRootTransform) {
    Math::Mat4x4f_C parent_transform = Math::Mat4x4f_C::Translate(Math::Vec3f_C(10.0f, 0.0f, 0.0f));
    Math::Mat4x4f_C child_transform = Math::Mat4x4f_C::Translate(Math::Vec3f_C(0.0f, 5.0f, 0.0f));

    _parent.SetLocalTransform(parent_transform);
    _child.SetLocalTransform(child_transform);

    // Set parent-child relationship
    _child.SetParent(&_parent);

    // Verify that the child's model matrix is the combined transform
    Math::Mat4x4f_C expected_model_matrix = parent_transform * child_transform;
    EXPECT_EQ(_child.GetModelMatrix(), expected_model_matrix);
}

// Test composing a transformation
TEST_F(TransformNodeTest_C, ComposeTransform) {
    Math::Mat4x4f_C scale_transform = Math::Mat4x4f_C::Scale(Math::Vec3f_C(2.0f, 2.0f, 2.0f));
    _node.ComposeTransform(scale_transform);

    // Verify that the local transform is updated
    EXPECT_EQ(_node.GetLocalTransform(), scale_transform * Math::Mat4x4f_C::Identity());
}

// Test destructor handling
TEST_F(TransformNodeTest_C, DestructorTest) {
    // Create parent-child hierarchy within a block scope
    {
        Math::TransformNode_C parent;
        Math::TransformNode_C* child = new Math::TransformNode_C();
        child->SetParent(&parent);

        // Verify parent has one child before destruction
        EXPECT_EQ(parent.NumChildren(), 1);

        // Child will be destroyed automatically at the end of this scope
        delete child;
    }
}

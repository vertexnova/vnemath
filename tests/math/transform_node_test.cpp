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

// Testing framework
#include <gtest/gtest.h>

// Project headers
#include "vertexnova/math/math_utils.h"
#include "vertexnova/math/transform_node.h"

using namespace vne;

// Test fixture for TransformNode
class TransformNodeTest : public ::testing::Test {
   protected:
    void SetUp() override {
        // This function runs before each test
    }

    void TearDown() override {
        // This function runs after each test
    }

   protected:
    vne::math::TransformNode node_;
    vne::math::TransformNode parent_;
    vne::math::TransformNode child_;
};

// Test default constructor and matrix initialization
TEST_F(TransformNodeTest, DefaultConstructor) {
    // Verify that the local and root transforms are initialized to identity matrices
    EXPECT_EQ(node_.getLocalTransform(), vne::math::Mat4x4f::identity());
    EXPECT_EQ(node_.getModelMatrix(), vne::math::Mat4x4f::identity());
    EXPECT_TRUE(node_.isRoot());
    EXPECT_TRUE(node_.isLeaf());
}

// Test setting and getting the local transformation matrix
TEST_F(TransformNodeTest, SetLocalTransform) {
    vne::math::Mat4x4f custom_transform = vne::math::Mat4x4f::translate(vne::math::Vec3f(1.0f, 2.0f, 3.0f));
    node_.setLocalTransform(custom_transform);

    EXPECT_EQ(node_.getLocalTransform(), custom_transform);
}

// Test the parent-child relationship
TEST_F(TransformNodeTest, ParentChildRelationship) {
    // Set the parent
    child_.setParent(&parent_);

    // Verify the parent-child relationship
    EXPECT_EQ(child_.getParent(), &parent_);
    EXPECT_EQ(parent_.numChildren(), 1);
    EXPECT_EQ(parent_.getChildren()[0], &child_);
    EXPECT_FALSE(child_.isRoot());
    EXPECT_TRUE(parent_.isRoot());
    EXPECT_TRUE(child_.isLeaf());
    EXPECT_FALSE(parent_.isLeaf());

    // Remove the child from the parent
    child_.removeFromParent();
    EXPECT_EQ(child_.getParent(), nullptr);
    EXPECT_EQ(parent_.numChildren(), 0);
    EXPECT_TRUE(child_.isRoot());
}

// Test adding and removing children
TEST_F(TransformNodeTest, AddRemoveChild) {
    // Add a child
    parent_.addChild(&child_);
    EXPECT_EQ(parent_.numChildren(), 1);
    EXPECT_EQ(parent_.getChildren()[0], &child_);

    // Remove the child
    parent_.removeChild(&child_);
    EXPECT_EQ(parent_.numChildren(), 0);
    EXPECT_EQ(child_.getParent(), nullptr);
}

// Test that child inherits the parent's root transform
TEST_F(TransformNodeTest, InheritedRootTransform) {
    vne::math::Mat4x4f parent_transform = vne::math::Mat4x4f::translate(vne::math::Vec3f(10.0f, 0.0f, 0.0f));
    vne::math::Mat4x4f child_transform = vne::math::Mat4x4f::translate(vne::math::Vec3f(0.0f, 5.0f, 0.0f));

    parent_.setLocalTransform(parent_transform);
    child_.setLocalTransform(child_transform);

    // Set parent-child relationship
    child_.setParent(&parent_);

    // Verify that the child's model matrix is the combined transform
    vne::math::Mat4x4f expected_model_matrix = parent_transform * child_transform;
    EXPECT_EQ(child_.getModelMatrix(), expected_model_matrix);
}

// Test composing a transformation
TEST_F(TransformNodeTest, ComposeTransform) {
    vne::math::Mat4x4f scale_transform = vne::math::Mat4x4f::scale(vne::math::Vec3f(2.0f, 2.0f, 2.0f));
    node_.composeTransform(scale_transform);

    // Verify that the local transform is updated
    EXPECT_EQ(node_.getLocalTransform(), scale_transform * vne::math::Mat4x4f::identity());
}

// Test destructor handling
TEST_F(TransformNodeTest, DestructorTest) {
    // Create parent-child hierarchy within a block scope
    {
        vne::math::TransformNode parent;
        vne::math::TransformNode* child = new vne::math::TransformNode();
        child->setParent(&parent);

        // Verify parent has one child before destruction
        EXPECT_EQ(parent.numChildren(), 1);

        // Child will be destroyed automatically at the end of this scope
        delete child;
    }
}

# 05 - Scene Graph

Demonstrates hierarchical transformations using TransformNode.

## What This Example Demonstrates

- Creating parent-child transform relationships
- Local vs world transform calculations
- Robot arm / articulated body simulation
- Solar system style orbital hierarchy

## Why Scene Graphs?

Scene graphs provide:
- Intuitive object hierarchies (wheels attached to car, fingers attached to hand)
- Automatic world transform propagation
- Efficient transform updates (only recalculate when dirty)

## Building

```bash
cmake -B build -DBUILD_EXAMPLES=ON
cmake --build build
./build/bin/examples/example_05_scene_graph
```

## Key Concepts

### Parent-Child Relationships
```cpp
TransformNode parent;
TransformNode child;
child.setParent(&parent);

// Child's world transform is automatically parent * local
```

### Transform Hierarchy
When parent transforms change, all children update automatically:
```cpp
parent.setLocalTransform(Mat4f::translate({10, 0, 0}));
child.setLocalTransform(Mat4f::translate({0, 5, 0}));

// Child world position is now (10, 5, 0)
Mat4f childWorld = child.getModelMatrix();
```

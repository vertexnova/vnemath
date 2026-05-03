# VertexNova Math Documentation

Documentation for the **vnemath** library (vectors, matrices, quaternions, geometry, and graphics-API-aware projection).

## VertexNova module guide

Human-readable architecture and usage for the math module:

- [vertexnova/math/math.md](vertexnova/math/math.md) — overview, layers, and integration patterns

Diagram sources (draw.io) live in [vertexnova/math/diagrams/](vertexnova/math/diagrams/). Export them to PNG before publishing HTML that embeds figures (see that folder’s README).

## Generating API documentation

Generate API documentation with Doxygen:

```bash
cmake -DENABLE_DOXYGEN=ON -B build
cmake --build build --target vnemath_doc
```

HTML output is written under `build/vnemath_doxygen/html/index.html` (see `doxyfile.in`). The custom target is **`vnemath_doc`** so it does not collide with **`doc_doxygen`** from the embedded **vnelogging** dependency when both projects enable Doxygen.

**Requirements:** Doxygen 1.8.13+, optional Graphviz (`dot`) for call graphs.

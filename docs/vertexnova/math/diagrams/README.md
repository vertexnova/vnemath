# Diagrams

Draw.io source files for the **vnemath** module documentation (`math.md`).

## Export to PNG

The `math.md` document references PNG images. Export the `.drawio` files to PNG using one of these methods:

### Option 1: draw.io Desktop (macOS/Windows/Linux)

If [draw.io Desktop](https://github.com/jgraph/drawio-desktop/releases) is installed:

```bash
cd docs/vertexnova/math/diagrams
drawio -x -f png -o context.png context.drawio
drawio -x -f png -o modules.png modules.drawio
drawio -x -f png -o api.png api.drawio
```

### Option 2: draw.io Web

1. Open [app.diagrams.net](https://app.diagrams.net)
2. File → Open from → Device → select each `.drawio` file
3. File → Export as → PNG
4. Save to this `diagrams/` folder

### Files

| Source | Output | Used in math.md | Contents |
|--------|--------|-----------------|----------|
| context.drawio | context.png | Overview | C4-style context: Application → VneMath → GPU/shaders and scene code |
| modules.drawio | modules.png | Architecture | Layered modules: core types, geometry, color & utilities |
| api.drawio | api.png | Usage | Flow: include `math.h` → build transforms / project → optional GPU helpers |

#!/usr/bin/env bash
# Run clang-tidy on project sources using repo .clang-tidy and compile_commands.json.
# Requires: cmake -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON (and build dir present).
# Usage: ./scripts/run-clang-tidy.sh [build_dir]
#   build_dir  Default: build

set -e
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
cd "$PROJECT_ROOT"

BUILD_DIR="${1:-build}"
if [ ! -f "$BUILD_DIR/compile_commands.json" ]; then
  echo "error: $BUILD_DIR/compile_commands.json not found."
  echo "Run: cmake -B $BUILD_DIR -S . -DCMAKE_EXPORT_COMPILE_COMMANDS=ON"
  exit 1
fi

CLANG_TIDY="${CLANG_TIDY:-clang-tidy}"
if ! command -v "$CLANG_TIDY" &>/dev/null; then
  echo "error: $CLANG_TIDY not found. Set CLANG_TIDY (e.g. /opt/homebrew/opt/llvm/bin/clang-tidy) or install llvm."
  exit 1
fi

# Only .cpp files that appear in compile_commands (project sources)
FILES=$(find ./src ./tests ./examples -type f -name '*.cpp' 2>/dev/null | sort)
if [ -z "$FILES" ]; then
  echo "No .cpp files found under src/tests/examples"
  exit 0
fi

FAILED=0
for f in $FILES; do
  if ! "$CLANG_TIDY" -p "$BUILD_DIR" --format-style=file "$f" 2>/dev/null; then
    FAILED=1
  fi
done
[ $FAILED -eq 0 ] || exit 1
echo "clang-tidy finished."

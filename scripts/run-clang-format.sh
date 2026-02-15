#!/usr/bin/env bash
# Run clang-format on project sources using repo .clang-format.
# Usage: ./scripts/run-clang-format.sh [--check]
#   --check  Dry run, exit 1 if any file would be reformatted (CI mode).

set -e
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
cd "$PROJECT_ROOT"

CLANG_FORMAT="${CLANG_FORMAT:-clang-format}"
if ! command -v "$CLANG_FORMAT" &>/dev/null; then
  echo "error: $CLANG_FORMAT not found. Set CLANG_FORMAT or install clang-format."
  exit 1
fi

FILES=$(find . -type f \( -name '*.cpp' -o -name '*.h' -o -name '*.hpp' \) \
  -not -path './deps/*' -not -path './cmake/*' \
  \( -path './src/*' -o -path './include/*' -o -path './tests/*' -o -path './examples/*' \) | sort)

if [ -z "$FILES" ]; then
  echo "No C/C++ files found under src/include/tests/examples"
  exit 0
fi

if [ "${1:-}" = "--check" ]; then
  echo "$FILES" | xargs "$CLANG_FORMAT" --dry-run -Werror --style=file
  echo "Format check passed."
else
  echo "$FILES" | xargs "$CLANG_FORMAT" -i --style=file
  echo "Formatting applied."
fi

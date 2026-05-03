#!/bin/bash

#==============================================================================
# VneMath Documentation helper
# Link validation and doc-tag heuristics. API (Doxygen) runs only if docs/doxyfile.in exists.
#==============================================================================
# Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
# Licensed under the Apache License, Version 2.0 (the "License")
#==============================================================================

set -e

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
DOCS_DIR="$PROJECT_ROOT/docs"
# Matches CI convention: build/shared/Release for a shared Release tree
BUILD_DIR="$PROJECT_ROOT/build/shared/Release"
DOXYFILE_IN="$PROJECT_ROOT/docs/doxyfile.in"
DOXYGEN_HTML="$BUILD_DIR/docs/html"

log_info() { echo -e "${BLUE}[INFO]${NC} $1"; }
log_success() { echo -e "${GREEN}[SUCCESS]${NC} $1"; }
log_warning() { echo -e "${YELLOW}[WARNING]${NC} $1"; }
log_error() { echo -e "${RED}[ERROR]${NC} $1"; }

check_prerequisites() {
    local skip_cmake_check="${1:-false}"
    log_info "Checking prerequisites..."

    if [[ ! -f "$PROJECT_ROOT/CMakeLists.txt" ]]; then
        log_error "Not in VneMath project root."
        exit 1
    fi

    if [[ "$skip_cmake_check" != "true" ]]; then
        if ! command -v cmake &> /dev/null; then
            log_error "CMake not found."
            exit 1
        fi
    fi

    if ! command -v doxygen &> /dev/null; then
        DOXYGEN_AVAILABLE=false
        log_warning "Doxygen not found."
    else
        DOXYGEN_AVAILABLE=true
    fi

    if ! command -v markdown-link-check &> /dev/null; then
        LINK_CHECK_AVAILABLE=false
        log_warning "markdown-link-check not found."
    else
        LINK_CHECK_AVAILABLE=true
    fi

    log_success "Prerequisites check completed"
}

generate_api_docs() {
    local strict="${1:-0}"

    if [[ ! -f "$DOXYFILE_IN" ]]; then
        if [[ "$strict" == "1" ]]; then
            log_error "API docs requested but $DOXYFILE_IN is missing."
            return 1
        fi
        log_warning "Skipping API docs (no $DOXYFILE_IN). Add Doxygen + ENABLE_DOXYGEN in CMake when ready."
        return 0
    fi

    if [[ "$DOXYGEN_AVAILABLE" == "false" ]]; then
        if [[ "$strict" == "1" ]]; then
            log_error "API docs requested but Doxygen is not installed."
            return 1
        fi
        log_warning "Skipping API documentation (Doxygen not installed)"
        return 0
    fi

    log_info "Generating API documentation (CMake + Doxygen)..."
    mkdir -p "$BUILD_DIR"
    cmake -S "$PROJECT_ROOT" -B "$BUILD_DIR" \
        -DCMAKE_BUILD_TYPE=Release \
        -DENABLE_DOXYGEN=ON \
        -DVNE_MATH_LIB_TYPE=shared \
        -DBUILD_TESTS=OFF \
        -DVNE_MATH_TESTS=OFF

    local target=""
    if cmake --build "$BUILD_DIR" --target help 2>/dev/null | grep -q vnemath_doc_doxygen; then
        target="vnemath_doc_doxygen"
    elif cmake --build "$BUILD_DIR" --target help 2>/dev/null | grep -q doc_doxygen; then
        target="doc_doxygen"
    else
        if [[ "$strict" == "1" ]]; then
            log_error "No vnemath_doc_doxygen or doc_doxygen CMake target (add Doxygen to the project)."
            return 1
        fi
        log_warning "No vnemath_doc_doxygen target found; skipping build step"
        return 0
    fi

    cmake --build "$BUILD_DIR" --target "$target"

    if [[ -f "$DOXYGEN_HTML/index.html" ]]; then
        log_success "API documentation: $DOXYGEN_HTML/index.html"
    else
        if [[ "$strict" == "1" ]]; then
            log_error "Expected HTML not found at $DOXYGEN_HTML/index.html"
            return 1
        fi
        log_warning "Expected HTML not found at $DOXYGEN_HTML/index.html"
    fi
    return 0
}

validate_links() {
    if [[ "$LINK_CHECK_AVAILABLE" == "false" ]]; then
        log_warning "Skipping link validation"
        return
    fi

    log_info "Validating documentation links..."
    local failed_links=0

    if [[ -d "$DOCS_DIR" ]]; then
        while IFS= read -r -d '' file; do
            log_info "Checking: $file"
            if ! markdown-link-check "$file" 2>/dev/null; then
                ((failed_links++)) || true
            fi
        done < <(find "$DOCS_DIR" -name "*.md" -print0 2>/dev/null || true)
    fi

    if [[ -f "$PROJECT_ROOT/README.md" ]]; then
        log_info "Checking: README.md"
        if ! markdown-link-check "$PROJECT_ROOT/README.md" 2>/dev/null; then
            ((failed_links++)) || true
        fi
    fi

    if [[ -f "$PROJECT_ROOT/examples/README.md" ]]; then
        log_info "Checking: examples/README.md"
        if ! markdown-link-check "$PROJECT_ROOT/examples/README.md" 2>/dev/null; then
            ((failed_links++)) || true
        fi
    fi

    if [[ $failed_links -eq 0 ]]; then
        log_success "Link validation passed"
    else
        log_error "Found $failed_links files with link issues"
        return 1
    fi
}

generate_coverage_report() {
    log_info "Documentation tag heuristic (include + src)..."
    local total_files=0
    local documented_files=0

    for dir in "$PROJECT_ROOT/include" "$PROJECT_ROOT/src"; do
        if [[ -d "$dir" ]]; then
            while IFS= read -r -d '' file; do
                ((total_files++)) || true
                if grep -qE '@brief|@class|@file|@param' "$file" 2>/dev/null; then
                    ((documented_files++)) || true
                fi
            done < <(find "$dir" \( -name "*.h" -o -name "*.hpp" -o -name "*.cpp" \) -print0 2>/dev/null || true)
        fi
    done

    if [[ $total_files -gt 0 ]]; then
        local coverage=$((documented_files * 100 / total_files))
        log_info "Files with common Doxygen tags: $documented_files / $total_files ($coverage%)"
    else
        log_warning "No source files found"
    fi
}

show_help() {
    echo "VneMath documentation helper"
    echo ""
    echo "Usage: $0 [OPTIONS]"
    echo "  --help, -h     Show help"
    echo "  --api-only     Generate API docs only (requires docs/doxyfile.in + ENABLE_DOXYGEN target)"
    echo "  --validate     Validate markdown links + tag heuristic only"
}

main() {
    log_info "VneMath documentation..."
    check_prerequisites false
    generate_api_docs 0
    if [[ -d "$DOCS_DIR" ]] || [[ -f "$PROJECT_ROOT/README.md" ]]; then
        validate_links
    fi
    generate_coverage_report
    log_success "Done."
}

case "${1:-}" in
    --help|-h)
        show_help
        exit 0
        ;;
    --api-only)
        check_prerequisites false
        generate_api_docs 1 || exit 1
        ;;
    --validate)
        check_prerequisites true
        validate_links
        generate_coverage_report
        ;;
    "")
        main
        ;;
    *)
        log_error "Unknown option: $1"
        show_help
        exit 1
        ;;
esac

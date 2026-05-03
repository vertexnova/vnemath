#!/usr/bin/env python3
"""
Clang formatter for C/C++. Same scope as CI (src, include, tests; examples if present).

Usage (from repo root; use ``python3`` so PATH is yours, not the kernel's):
    python3 scripts/clang_formatter.py all --dry-run
    python3 scripts/clang_formatter.py src
    python3 scripts/clang_formatter.py --file path/to/file.cpp
"""

import argparse
import os
import subprocess
import sys
from pathlib import Path


def find_source_files(folder_path: Path) -> list:
    """Find all C/C++ source files recursively under the given folder."""
    source_files = []
    root_path = Path(folder_path).resolve()

    extensions = (".h", ".cpp", ".mm", ".m", ".hpp", ".c")
    exclude_dirs = {"build", ".git", "node_modules", "CMakeFiles", "__pycache__"}

    for root, dirs, files in os.walk(root_path, topdown=True):
        dirs[:] = [d for d in dirs if d not in exclude_dirs]
        for f in files:
            if f.endswith(extensions):
                source_files.append(str(Path(root) / f))

    return source_files


def is_source_file(file_path: Path) -> bool:
    extensions = (".h", ".cpp", ".mm", ".m", ".hpp", ".c")
    return file_path.suffix.lower() in extensions


def get_clang_format_binary() -> str:
    for name in ("clang-format-17", "clang-format"):
        try:
            subprocess.run([name, "--version"], capture_output=True, check=True)
            return name
        except (subprocess.CalledProcessError, FileNotFoundError):
            continue
    return "clang-format"


def check_clang_format() -> bool:
    binary = get_clang_format_binary()
    try:
        subprocess.run([binary, "--version"], capture_output=True, check=True)
        return True
    except (subprocess.CalledProcessError, FileNotFoundError):
        return False


def run_clang_format(files: list, style_file: Path, dry_run: bool = False) -> bool:
    if not files:
        print("No source files found to format.")
        return True

    binary = get_clang_format_binary()
    print(f"Found {len(files)} source files to format (using {binary}).")

    base_cmd = [
        binary,
        "--style=file",
        "--fallback-style=Google",
    ]

    if dry_run:
        print("DRY RUN - Checking for format violations (matches CI).")
        result = subprocess.run(
            base_cmd + ["--dry-run", "--Werror"] + files,
            capture_output=True,
            text=True,
        )
        if result.returncode != 0:
            if result.stderr:
                print(result.stderr, file=sys.stderr)
            print("One or more files need formatting. Run without --dry-run to fix.")
            return False
        print("All files are formatted correctly.")
        return True

    for file_path in files:
        print(f"Formatting: {file_path}")
        try:
            subprocess.run(
                base_cmd + ["-i", file_path],
                capture_output=True,
                text=True,
                check=True,
            )
            print("  ✓ Formatted successfully")
        except subprocess.CalledProcessError as e:
            print(f"  ✗ Error formatting {file_path}: {e}")
            if e.stderr:
                print(f"    stderr: {e.stderr}")
            return False
        except FileNotFoundError:
            print("  ✗ clang-format not found. Please install clang-format.")
            return False

    return True


def main():
    parser = argparse.ArgumentParser(
        description="Format C/C++ using clang-format (VneMath; matches CI when using clang-format-17)",
        formatter_class=argparse.RawDescriptionHelpFormatter,
    )

    parser.add_argument(
        "folder_positional",
        nargs="?",
        default=None,
        metavar="FOLDER_OR_ALL",
        help='Folder to format recursively, or "all" for CI dirs (src, include, examples if present, tests). '
        "Alternative to --folder / --file.",
    )
    parser.add_argument(
        "--folder",
        "-f",
        dest="folder_option",
        metavar="PATH",
        nargs="?",
        const="all",
        default=None,
        help="Same as positional folder; omit PATH after --folder to use CI dirs (same as 'all').",
    )
    parser.add_argument("--file", metavar="PATH", default=None, help="Format a single file")

    parser.add_argument("--dry-run", action="store_true", help="Check only (CI-style)")
    parser.add_argument("--verbose", action="store_true")

    args = parser.parse_args()

    if args.file is not None:
        if args.folder_positional is not None or args.folder_option is not None:
            parser.error("Do not combine --file with a folder argument or --folder.")
    elif args.folder_positional is not None and args.folder_option is not None:
        parser.error("Use either positional FOLDER_OR_ALL or --folder, not both.")
    elif args.file is None and args.folder_positional is None and args.folder_option is None:
        parser.error(
            "Specify a folder (e.g. all or src), use --folder, or use --file PATH. "
            "Example: python3 scripts/clang_formatter.py all --dry-run"
        )

    script_dir = Path(__file__).parent
    project_root = script_dir.parent
    style_file = project_root / ".clang-format"

    print("VneMath Clang Formatter")
    print("=" * 40)
    if style_file.exists():
        print(f"Style file: {style_file}")
    print()

    if args.file:
        target_file = project_root / args.file
        if not target_file.exists():
            print(f"Error: File not found at {target_file}")
            sys.exit(1)
        if not is_source_file(target_file):
            print(f"Error: {target_file} is not a supported source file type.")
            sys.exit(1)
        source_files = [str(target_file)]
    else:
        if args.folder_option is not None:
            folder_arg = args.folder_option
        else:
            folder_arg = args.folder_positional
        if folder_arg.lower() in ("all", "ci"):
            ci_dirs = ("src", "include", "examples", "tests")
            source_files = []
            for d in ci_dirs:
                p = project_root / d
                if p.is_dir():
                    source_files.extend(find_source_files(p))
            source_files = sorted(set(source_files))
            print(f"Target: CI dirs — {len(source_files)} files")
        else:
            target_folder = (project_root / folder_arg).resolve()
            if not target_folder.is_dir():
                print(f"Error: Target folder not found at {target_folder}")
                sys.exit(1)
            print(f"Target folder (recursive): {target_folder}")
            source_files = find_source_files(target_folder)
        print()

    if args.verbose:
        for f in source_files:
            print(f"  {f}")
        print()

    binary = get_clang_format_binary()
    if not check_clang_format():
        print("Error: clang-format not found.")
        print("  Ubuntu/Debian: sudo apt install clang-format-17")
        sys.exit(1)
    if binary != "clang-format-17":
        print(f"Note: Using '{binary}'. For CI-identical formatting, install clang-format-17.")

    success = run_clang_format(source_files, style_file, args.dry_run)

    if success:
        print("\n✓ Formatting completed successfully!")
    else:
        print("\n✗ Formatting failed!")
        sys.exit(1)


if __name__ == "__main__":
    main()

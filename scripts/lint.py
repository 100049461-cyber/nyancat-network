"""Check C++ formatting and naming with the project's LLVM 18 tools."""

import argparse
import json
import os
from pathlib import Path
import re
import shutil
import subprocess
import sys

ROOT = Path(__file__).resolve().parent.parent
BUILD = ROOT / "build"
SOURCE_SUFFIXES = {".cpp", ".cc", ".cxx"}
CPP_SUFFIXES = SOURCE_SUFFIXES | {".h", ".hpp", ".hxx"}


def tool(name, override):
    executable = shutil.which(os.environ.get(override, f"{name}-18"))
    if executable is None:
        raise RuntimeError(f"Missing {name}-18. Rebuild the project's Codespace container.")
    version = subprocess.check_output([executable, "--version"], text=True)
    if not re.search(r"\bversion 18(?:\.|\b)", version):
        raise RuntimeError(f"Use {name} 18 so local formatting matches CI: {version.strip()}")
    return executable


def cpp_files():
    paths = subprocess.check_output(
        ["git", "ls-files", "-z", "--cached", "--others", "--exclude-standard", "--",
         "include", "src", "tests"], cwd=ROOT
    )
    return sorted({
        ROOT / os.fsdecode(path)
        for path in paths.split(b"\0") if path
        if Path(os.fsdecode(path)).suffix in CPP_SUFFIXES
        if (ROOT / os.fsdecode(path)).is_file()
    })


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--fix", action="store_true", help="apply formatting; report naming errors")
    parser.add_argument("--format-only", action="store_true", help="skip clang-tidy and build setup")
    args = parser.parse_args()
    files = cpp_files()
    if not files:
        raise RuntimeError("No project C++ files found.")

    formatter = tool("clang-format", "CLANG_FORMAT")
    mode = ["-i"] if args.fix else ["--dry-run", "--Werror"]
    result = subprocess.run([formatter, "--style=file", *mode, *map(str, files)], cwd=ROOT)
    if result.returncode:
        print("Run python3 scripts/lint.py --fix to apply formatting.", file=sys.stderr)
        return 1
    if args.format_only:
        print(f"Formatting passed ({len(files)} files).")
        return 0

    tidy = tool("clang-tidy", "CLANG_TIDY")
    database = BUILD / "compile_commands.json"
    if not database.is_file():
        raise RuntimeError("Run cmake --preset dev before linting.")
    commands = json.loads(database.read_text())
    units = sorted({
        (Path(entry["directory"]) / entry["file"]).resolve()
        for entry in commands
        if any((Path(entry["directory"]) / entry["file"]).resolve().is_relative_to(directory)
               for directory in (ROOT / "src", ROOT / "tests", BUILD / "header-checks"))
    })
    missing = [str(path.relative_to(ROOT)) for path in files
               if path.suffix in SOURCE_SUFFIXES and path.resolve() not in units]
    missing += [str(path.relative_to(ROOT)) for path in files
                if path.is_relative_to(ROOT / "include") and path.suffix == ".h"
                and (BUILD / "header-checks" / (str(path.relative_to(ROOT / "include")) + ".cpp"))
                not in units]
    if missing or not units:
        raise RuntimeError("Missing build entries; register sources in CMake and rerun "
                           "cmake --preset dev: " + ", ".join(missing))

    failed = False
    for unit in units:
        result = subprocess.run([tidy, "--quiet", "-p", str(BUILD), str(unit)], cwd=ROOT)
        failed = failed or result.returncode != 0
    if failed:
        return 1
    print(f"Lint passed ({len(files)} files; {len(units)} source/header compilation checks).")
    return 0


if __name__ == "__main__":
    try:
        sys.exit(main())
    except (RuntimeError, OSError, subprocess.CalledProcessError, json.JSONDecodeError) as error:
        print(f"Lint failed: {error}", file=sys.stderr)
        sys.exit(1)

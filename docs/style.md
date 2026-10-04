# Project C++ style

We use a small project style built around the existing code. The formatter uses
LLVM defaults with the overrides in [.clang-format](../.clang-format); naming
rules live in [.clang-tidy](../.clang-tidy). This is our style guide, rather than
a claim of compliance with Google's or LLVM's full coding standards.

| Item | Convention |
| --- | --- |
| Functions, methods, variables, parameters, namespaces | `snake_case`: `parse_options`, `byte_count` |
| Classes, structs, enums, type aliases | `PascalCase`: `Socket`, `WindowSize`, `Byte` |
| `constexpr` variables and global/class constants | `kCamelCase`: `kIac`, `kBufferSize` |
| Enum values | `snake_case`: `Event::Kind::subnegotiation` |
| Private/protected class fields | `snake_case_`: `fd_` |
| Public fields and struct fields | `snake_case`: `columns` |
| Files | `snake_case.cpp` / `snake_case.h`; headers use `#pragma once` |
| Indentation | Four spaces; no tabs; namespace contents are not indented |
| Braces and line width | Opening brace on the same line; formatter wraps at 100 columns |
| Pointers and references | Attach to the type: `int* value`, `const Event& event` |

Declare pointers separately (`int* first;`, `int** second;`). Use short namespace
closing comments, including nested names:

```cpp
namespace nyan::telnet {
Bytes encode_command(Byte command, Byte option);
} // namespace nyan::telnet
```

Clang-format adds and fixes these comments. Keep GNU++23 and the exception-based
error handling specified in [the design](design.md). Naming fixes must also
update callers; avoid renaming shared interfaces without coordinating with their
issue owners.

## Format and lint

Use **clang-format 18, clang-tidy 18, and clangd 18**, provided by the Codespace.
From the repository root:

```bash
cmake --preset dev
python3 scripts/lint.py --fix
python3 scripts/lint.py
```

`--fix` changes formatting, then reports naming/syntax errors for you to fix.
The command without `--fix` changes no files and fails for formatting, naming,
or compilation problems. `--format-only` skips clang-tidy when you only want to
format work in progress. The script includes new, untracked C++ files under
`include/`, `src/`, and `tests/`; add new implementation/test files to CMake and
rerun configuration before the full lint check.

CI runs this check as **C++ lint**. The normal build also compiles each public
header in isolation, so even a header without any callers must be valid C++ and
include its own dependencies. These are compilation checks, not client behavior
tests. No tests that merely repeat constant values are needed.

## Editor setup

Clangd provides completion, navigation, diagnostics, and formatting on save. It
reads the project's compilation database from `build/compile_commands.json`,
so it sees the same includes and GNU++23 mode as CMake. Clang-tidy naming warnings
appear while editing. The Microsoft C++ extension remains available for GDB
debugging with its competing IntelliSense engine disabled.

For an existing Codespace, pull the changes, open the command palette, and run
**Rebuild Container**. Setup regenerates the compilation database. After adding
sources, rerun `cmake --preset dev`; if diagnostics remain stale, use
**clangd: Restart language server** from the command palette.

References: [clang-format options](https://releases.llvm.org/18.1.8/tools/clang/docs/ClangFormatStyleOptions.html),
[clang-tidy naming rules](https://releases.llvm.org/18.1.8/tools/clang/tools/extra/docs/clang-tidy/checks/readability/identifier-naming.html),
[clangd configuration](https://clangd.llvm.org/config).

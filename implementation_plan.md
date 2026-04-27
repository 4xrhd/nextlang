# NetXLang Implementation Plan

This document outlines the design and step-by-step implementation plan for **NetXLang**, a Network-Oriented Bengali DSL. The project involves building a full compiler pipeline (Lexer, Parser, Semantic Analyzer, Interpreter/Simulator) using C++17, targeting Windows 11, and simulating network communications with AES-256 encryption via OpenSSL.

## User Review Required

> [!WARNING]
> Please review the milestones and the initial setup details below. In particular, confirm whether you already have MSYS2/MinGW and OpenSSL installed and accessible in your Windows environment. If not, I can help set those up or write scripts to automate it.

## Open Questions

> [!IMPORTANT]
> 1. **OpenSSL Dependency**: Do you have OpenSSL installed on Windows (e.g., via MSYS2 `pacman -S mingw-w64-x86_64-openssl` or vcpkg)? The build script will need to link against it.
> 2. **C++ Compiler**: Do you prefer MinGW-w64 or MSVC? (MinGW is assumed based on the example commands, but CMake can handle either).
> 3. **Testing Framework**: Can we use a lightweight testing framework like `Catch2` or `GoogleTest` for unit tests, or do you prefer a custom minimal test runner to reduce dependencies?

## Proposed Changes

The project will be structured into the following directories in the `nextlang` workspace:

### Workspace Setup & Build System
- Initialize a Git repository.
- Create `CMakeLists.txt` configured for C++17, linking OpenSSL.
- Add `.gitignore` and `README.md`.

#### [NEW] [CMakeLists.txt](file:///c:/Users/User/OneDrive/Desktop/nextlang/CMakeLists.txt)
#### [NEW] [README.md](file:///c:/Users/User/OneDrive/Desktop/nextlang/README.md)
#### [NEW] [.gitignore](file:///c:/Users/User/OneDrive/Desktop/nextlang/.gitignore)

---

### Grammar & Documentation
- Document the Backus-Naur Form (BNF) grammar.
- Create language reference documentation.

#### [NEW] [grammar.bnf](file:///c:/Users/User/OneDrive/Desktop/nextlang/grammar/grammar.bnf)
#### [NEW] [language_reference.md](file:///c:/Users/User/OneDrive/Desktop/nextlang/docs/language_reference.md)

---

### Core Compiler Pipeline (`src/`)
- Implement the 4 main compiler stages.

#### [NEW] [lexer.h / lexer.cpp](file:///c:/Users/User/OneDrive/Desktop/nextlang/src/lexer.cpp)
Tokenizes the 25 keywords, identifiers, IP literals, strings, and punctuation.
#### [NEW] [ast.h](file:///c:/Users/User/OneDrive/Desktop/nextlang/src/ast.h)
Defines Abstract Syntax Tree nodes for program structures, statements, and expressions.
#### [NEW] [parser.h / parser.cpp](file:///c:/Users/User/OneDrive/Desktop/nextlang/src/parser.cpp)
Recursive descent parser to generate AST from token stream.
#### [NEW] [semantic.h / semantic.cpp](file:///c:/Users/User/OneDrive/Desktop/nextlang/src/semantic.cpp)
Validates AST semantics (device existence, IPs, argument counts, etc.).
#### [NEW] [interpreter.h / interpreter.cpp](file:///c:/Users/User/OneDrive/Desktop/nextlang/src/interpreter.cpp)
Simulates the network backend (routing, encryption, dropping packets, looping, etc.).
#### [NEW] [crypto.h / crypto.cpp](file:///c:/Users/User/OneDrive/Desktop/nextlang/src/crypto.cpp)
Wraps OpenSSL for AES-256 simulate encryption (`GoponKoro`) and decryption (`UghatKoro`).
#### [NEW] [main.cpp](file:///c:/Users/User/OneDrive/Desktop/nextlang/src/main.cpp)
CLI entry point to execute `.nxl` files.

---

### Tests & Examples
- Unit tests for each pipeline stage.
- 6 example `.nxl` files.
- Windows-compatible test runner script.

#### [NEW] [run_tests.bat](file:///c:/Users/User/OneDrive/Desktop/nextlang/run_tests.bat)
#### [NEW] [tests/](file:///c:/Users/User/OneDrive/Desktop/nextlang/tests/)
#### [NEW] [examples/](file:///c:/Users/User/OneDrive/Desktop/nextlang/examples/)

## Verification Plan

### Automated Tests
1. **Unit Tests**: Verify lexer correctly parses all tokens, parser builds correct ASTs, semantic analyzer catches errors (e.g., undeclared devices), and crypto wrapper successfully encrypts/decrypts AES-256.
2. **Integration Tests**: Run the 6 examples using the CLI and capture stdout/stderr to match expected outcomes (including firewall block simulation and packet drops).

### Manual Verification
1. I will configure the project using CMake (`cmake -G "MinGW Makefiles" ..`).
2. Run `mingw32-make` to build the application and tests.
3. Run `run_tests.bat` to verify all test cases pass.
4. Run `build\netxlang.exe ../examples/sample1.nxl` to verify successful end-to-end execution.

## Execution Milestones
- **Milestone 1**: Produce grammar (`.bnf`) and token list.
- **Milestone 2**: Implement lexer and unit tests.
- **Milestone 3**: Implement parser, AST types, and unit tests.
- **Milestone 4**: Implement semantic analyzer and unit tests.
- **Milestone 5**: Implement interpreter with all 25 functions and integration tests.
- **Milestone 6**: Add examples, docs, build scripts, and end-to-end demo.

Once you approve, I will initialize the workspace and begin with Milestone 1!

# NetXLang

NetXLang is a Network-Oriented Bengali Domain Specific Language (DSL) designed for simulating network topologies, packet routing, and security policies.

## Features
- Full compiler pipeline (Lexer, Parser, Semantic Analyzer, Interpreter).
- 25 keywords for network simulation.
- Virtual network device registry and packet routing simulation.
- Firewall rules (`ProtirodhDao`) and packet loss simulation (`HariyeFelo`).
- Encryption simulation (AES-256 placeholder).
- Control flow (`Jodi`, `Nahole`, `GhuroChol`).

## Project Structure
- `/src`: C++17 source code.
- `/grammar`: BNF grammar file.
- `/examples`: Sample `.nxl` programs.
- `/tests`: Unit and integration tests.
- `/docs`: Language reference and design notes.

## Build Instructions (Windows 11)
Requires `g++` (MinGW or MSYS2) and `make`/`cmake` (optional).

### Using g++ directly:
```powershell
g++ -std=c++17 -Isrc src/lexer.cpp src/parser.cpp src/semantic.cpp src/interpreter.cpp src/main.cpp -o netxlang.exe
```

### Running an example:
```powershell
./netxlang.exe examples/sample1.nxl
```

### Running tests:
```powershell
./run_tests.bat
```

## Language Reference
See [docs/language_reference.md](docs/language_reference.md) for a full list of keywords and syntax.

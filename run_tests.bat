@echo off
echo Building tests using g++...
if not exist build mkdir build

g++ -std=c++17 -Isrc src/lexer.cpp src/parser.cpp src/semantic.cpp tests/test_lexer.cpp -o build/test_lexer.exe
g++ -std=c++17 -Isrc src/lexer.cpp src/parser.cpp src/semantic.cpp tests/test_parser.cpp -o build/test_parser.exe
g++ -std=c++17 -Isrc src/lexer.cpp src/parser.cpp src/semantic.cpp tests/test_semantic.cpp -o build/test_semantic.exe
if %errorlevel% neq 0 (
    echo Build failed.
    exit /b %errorlevel%
)

echo Running Lexer tests...
build\test_lexer.exe
if %errorlevel% neq 0 (
    echo Lexer tests failed.
    exit /b %errorlevel%
)

echo Running Parser tests...
build\test_parser.exe
if %errorlevel% neq 0 (
    echo Parser tests failed.
    exit /b %errorlevel%
)

echo Running Semantic tests...
build\test_semantic.exe
if %errorlevel% neq 0 (
    echo Semantic tests failed.
    exit /b %errorlevel%
)

echo All tests passed successfully.
exit /b 0

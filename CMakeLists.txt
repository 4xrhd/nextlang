cmake_minimum_required(VERSION 3.10)
project(NetXLang)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files for the compiler
set(COMPILER_SOURCES
    src/lexer.cpp
    # src/parser.cpp
    # src/semantic.cpp
    # src/interpreter.cpp
    # src/crypto.cpp
)

# If we were compiling main
# add_executable(netxlang src/main.cpp ${COMPILER_SOURCES})

# Testing - just building basic executables for tests
enable_testing()
add_executable(test_lexer tests/test_lexer.cpp ${COMPILER_SOURCES})

# Add test target that will run when testing
add_test(NAME LexerTest COMMAND test_lexer)

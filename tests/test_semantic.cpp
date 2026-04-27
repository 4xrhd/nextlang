#include "../src/lexer.h"
#include "../src/parser.h"
#include "../src/semantic.h"
#include <iostream>
#include <cassert>

void testValidSemantic() {
    std::string source = R"(
        NetArambho
            JontraGothon Router R1;
            JontraGothon Host H1;
            JogajogSet R1 H1;
            ThikanaDao H1 192.168.1.1;
        NetShesh
    )";
    Lexer lexer(source);
    Parser parser(lexer.tokenize());
    auto ast = parser.parse();
    SemanticAnalyzer analyzer;
    analyzer.analyze(ast.get());
}

void testDuplicateDevice() {
    std::string source = R"(
        NetArambho
            JontraGothon Router R1;
            JontraGothon Router R1;
        NetShesh
    )";
    Lexer lexer(source);
    Parser parser(lexer.tokenize());
    auto ast = parser.parse();
    SemanticAnalyzer analyzer;
    try {
        analyzer.analyze(ast.get());
        assert(false && "Should have thrown error for duplicate device");
    } catch (const std::exception& e) {
        std::cout << "Caught expected error: " << e.what() << "\n";
    }
}

void testUndeclaredDevice() {
    std::string source = R"(
        NetArambho
            JogajogSet R1 H1;
        NetShesh
    )";
    Lexer lexer(source);
    Parser parser(lexer.tokenize());
    auto ast = parser.parse();
    SemanticAnalyzer analyzer;
    try {
        analyzer.analyze(ast.get());
        assert(false && "Should have thrown error for undeclared device");
    } catch (const std::exception& e) {
        std::cout << "Caught expected error: " << e.what() << "\n";
    }
}

int main() {
    std::cout << "Running Semantic tests...\n";
    testValidSemantic();
    testDuplicateDevice();
    testUndeclaredDevice();
    std::cout << "All Semantic tests passed!\n";
    return 0;
}

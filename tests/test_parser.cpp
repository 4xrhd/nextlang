#include "../src/lexer.h"
#include "../src/parser.h"
#include <iostream>
#include <cassert>

void testBasicProgram() {
    std::string source = R"(
        NetArambho
            JontraGothon Router R1;
            JontraGothon Host H1;
            JogajogSet R1 H1;
            ThikanaDao H1 192.168.1.2;
            Dekhao "Init Done";
        NetShesh
    )";
    Lexer lexer(source);
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    auto ast = parser.parse();
    assert(ast->getType() == ASTNodeType::Program);
    auto program = static_cast<ProgramNode*>(ast.get());
    assert(program->statements.size() == 5);
}

void testControlFlow() {
    std::string source = R"(
        NetArambho
            Jodi (1) {
                Dekhao "True";
            } Nahole {
                Dekhao "False";
            }
            GhuroChol (5) {
                Dekhao "Looping";
            }
        NetShesh
    )";
    Lexer lexer(source);
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    auto ast = parser.parse();
    assert(ast->getType() == ASTNodeType::Program);
}

int main() {
    std::cout << "Running Parser tests...\n";
    try {
        testBasicProgram();
        testControlFlow();
        std::cout << "All Parser tests passed!\n";
    } catch (const std::exception& e) {
        std::cerr << "Test failed: " << e.what() << "\n";
        return 1;
    }
    return 0;
}

#include "../src/lexer.h"
#include <iostream>
#include <cassert>

void testKeywords() {
    Lexer lexer("NetArambho NetShesh JontraGothon");
    auto tokens = lexer.tokenize();
    assert(tokens.size() == 4); // 3 keywords + EOF
    assert(tokens[0].type == TokenType::NetArambho);
    assert(tokens[1].type == TokenType::NetShesh);
    assert(tokens[2].type == TokenType::JontraGothon);
}

void testLiterals() {
    Lexer lexer("192.168.1.1 100 \"hello world\" MyVar");
    auto tokens = lexer.tokenize();
    assert(tokens.size() == 5);
    assert(tokens[0].type == TokenType::IPLiteral);
    assert(tokens[1].type == TokenType::Number);
    assert(tokens[2].type == TokenType::StringLiteral);
    assert(tokens[3].type == TokenType::Identifier);
}

void testOperators() {
    Lexer lexer("= == != < > + - * / ; , ( ) { }");
    auto tokens = lexer.tokenize();
    assert(tokens.size() == 16);
    assert(tokens[0].type == TokenType::Assign);
    assert(tokens[1].type == TokenType::Equals);
    assert(tokens[14].type == TokenType::RBrace);
}

int main() {
    std::cout << "Running Lexer tests...\n";
    testKeywords();
    testLiterals();
    testOperators();
    std::cout << "All Lexer tests passed!\n";
    return 0;
}

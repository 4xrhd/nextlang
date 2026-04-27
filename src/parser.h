#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "ast.h"
#include <memory>
#include <vector>

class Parser {
public:
    Parser(const std::vector<Token>& tokens);
    ASTNodePtr parse();

private:
    std::vector<Token> tokens;
    size_t current;

    Token peek() const;
    Token previous() const;
    bool isAtEnd() const;
    Token advance();
    bool check(TokenType type) const;
    bool match(std::vector<TokenType> types);
    Token consume(TokenType type, const std::string& message);

    ASTNodePtr statement();
    ASTNodePtr deviceDecl();
    ASTNodePtr linkDecl();
    ASTNodePtr ipAssign();
    ASTNodePtr portAssign();
    ASTNodePtr sendPacket();
    ASTNodePtr print();
    ASTNodePtr ifStatement();
    ASTNodePtr loopStatement();
    
    std::vector<ASTNodePtr> block();

    ExprPtr expression();
    ExprPtr primary();
};

#endif // PARSER_H

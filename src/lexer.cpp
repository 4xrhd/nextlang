#include "lexer.h"
#include <cctype>
#include <unordered_map>

static const std::unordered_map<std::string, TokenType> keywords = {
    {"NetArambho", TokenType::NetArambho},
    {"NetShesh", TokenType::NetShesh},
    {"JontraGothon", TokenType::JontraGothon},
    {"JogajogSet", TokenType::JogajogSet},
    {"ThikanaDao", TokenType::ThikanaDao},
    {"DorjaDao", TokenType::DorjaDao},
    {"PacketPathao", TokenType::PacketPathao},
    {"PacketNey", TokenType::PacketNey},
    {"ShobaiPathao", TokenType::ShobaiPathao},
    {"PothNirdharon", TokenType::PothNirdharon},
    {"JachaiPing", TokenType::JachaiPing},
    {"Bilombho", TokenType::Bilombho},
    {"HariyeFelo", TokenType::HariyeFelo},
    {"GotiNiyontron", TokenType::GotiNiyontron},
    {"NiyomBoshao", TokenType::NiyomBoshao},
    {"ProtirodhDao", TokenType::ProtirodhDao},
    {"GoponKoro", TokenType::GoponKoro},
    {"UghatKoro", TokenType::UghatKoro},
    {"NirikhaKoro", TokenType::NirikhaKoro},
    {"GhotonaLekho", TokenType::GhotonaLekho},
    {"Jodi", TokenType::Jodi},
    {"Nahole", TokenType::Nahole},
    {"GhuroChol", TokenType::GhuroChol},
    {"KajGothon", TokenType::KajGothon},
    {"Dekhao", TokenType::Dekhao}
};

Lexer::Lexer(const std::string& source) : source(source), pos(0), line(1), column(1) {}

char Lexer::peek(int offset) const {
    if (pos + offset >= source.length()) return '\0';
    return source[pos + offset];
}

char Lexer::advance() {
    char c = source[pos++];
    if (c == '\n') {
        line++;
        column = 1;
    } else {
        column++;
    }
    return c;
}

bool Lexer::isAtEnd() const {
    return pos >= source.length();
}

void Lexer::skipWhitespace() {
    while (!isAtEnd()) {
        char c = peek();
        if (std::isspace(c)) {
            advance();
        } else if (c == '/' && peek(1) == '/') {
            while (!isAtEnd() && peek() != '\n') {
                advance();
            }
        } else {
            break;
        }
    }
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    while (!isAtEnd()) {
        skipWhitespace();
        if (isAtEnd()) break;
        tokens.push_back(scanToken());
    }
    tokens.push_back({TokenType::EndOfFile, "", line, column});
    return tokens;
}

Token Lexer::scanToken() {
    int startLine = line;
    int startColumn = column;
    char c = advance();

    if (std::isalpha(c) || c == '_') {
        pos--; column--;
        return scanIdentifierOrKeyword();
    }
    if (std::isdigit(c)) {
        pos--; column--;
        return scanNumberOrIP();
    }
    if (c == '"') {
        return scanString();
    }

    switch (c) {
        case '=':
            if (peek() == '=') {
                advance();
                return {TokenType::Equals, "==", startLine, startColumn};
            }
            return {TokenType::Assign, "=", startLine, startColumn};
        case '!':
            if (peek() == '=') {
                advance();
                return {TokenType::NotEquals, "!=", startLine, startColumn};
            }
            break; // unknown token
        case '<': return {TokenType::LessThan, "<", startLine, startColumn};
        case '>': return {TokenType::GreaterThan, ">", startLine, startColumn};
        case '+': return {TokenType::Plus, "+", startLine, startColumn};
        case '-': return {TokenType::Minus, "-", startLine, startColumn};
        case '*': return {TokenType::Multiply, "*", startLine, startColumn};
        case '/': return {TokenType::Divide, "/", startLine, startColumn};
        case ';': return {TokenType::SemiColon, ";", startLine, startColumn};
        case ',': return {TokenType::Comma, ",", startLine, startColumn};
        case '(': return {TokenType::LParen, "(", startLine, startColumn};
        case ')': return {TokenType::RParen, ")", startLine, startColumn};
        case '{': return {TokenType::LBrace, "{", startLine, startColumn};
        case '}': return {TokenType::RBrace, "}", startLine, startColumn};
    }

    return {TokenType::Unknown, std::string(1, c), startLine, startColumn};
}

Token Lexer::scanIdentifierOrKeyword() {
    int startLine = line;
    int startColumn = column;
    std::string value;

    while (!isAtEnd() && (std::isalnum(peek()) || peek() == '_')) {
        value += advance();
    }

    auto it = keywords.find(value);
    if (it != keywords.end()) {
        return {it->second, value, startLine, startColumn};
    }

    return {TokenType::Identifier, value, startLine, startColumn};
}

Token Lexer::scanNumberOrIP() {
    int startLine = line;
    int startColumn = column;
    std::string value;
    int dotCount = 0;

    while (!isAtEnd() && (std::isdigit(peek()) || peek() == '.')) {
        char c = advance();
        value += c;
        if (c == '.') dotCount++;
    }

    if (dotCount == 3) {
        return {TokenType::IPLiteral, value, startLine, startColumn};
    }

    return {TokenType::Number, value, startLine, startColumn};
}

Token Lexer::scanString() {
    int startLine = line;
    int startColumn = column - 1; // " was advanced
    std::string value;

    while (!isAtEnd() && peek() != '"') {
        value += advance();
    }

    if (!isAtEnd() && peek() == '"') {
        advance(); // consume closing quote
    } else {
        // Unterminated string (handle error here properly in real implementation)
        return {TokenType::Unknown, value, startLine, startColumn};
    }

    return {TokenType::StringLiteral, value, startLine, startColumn};
}

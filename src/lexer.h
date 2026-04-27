#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include <stdexcept>

enum class TokenType {
    // Keywords
    NetArambho, NetShesh, JontraGothon, JogajogSet, ThikanaDao, DorjaDao,
    PacketPathao, PacketNey, ShobaiPathao, PothNirdharon, JachaiPing,
    Bilombho, HariyeFelo, GotiNiyontron, NiyomBoshao, ProtirodhDao,
    GoponKoro, UghatKoro, NirikhaKoro, GhotonaLekho, Jodi, Nahole,
    GhuroChol, KajGothon, Dekhao,

    // Literals and Identifiers
    Identifier,
    IPLiteral,
    StringLiteral,
    Number,

    // Operators and Punctuation
    Assign,         // =
    Equals,         // ==
    NotEquals,      // !=
    LessThan,       // <
    GreaterThan,    // >
    Plus,           // +
    Minus,          // -
    Multiply,       // *
    Divide,         // /
    SemiColon,      // ;
    Comma,          // ,
    LParen,         // (
    RParen,         // )
    LBrace,         // {
    RBrace,         // }

    EndOfFile,
    Unknown
};

struct Token {
    TokenType type;
    std::string value;
    int line;
    int column;
};

class Lexer {
public:
    Lexer(const std::string& source);
    std::vector<Token> tokenize();

private:
    std::string source;
    size_t pos;
    int line;
    int column;

    char peek(int offset = 0) const;
    char advance();
    bool isAtEnd() const;
    void skipWhitespace();

    Token scanToken();
    Token scanIdentifierOrKeyword();
    Token scanNumberOrIP();
    Token scanString();
};

#endif // LEXER_H

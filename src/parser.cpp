#include "parser.h"
#include <iostream>

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens), current(0) {}

Token Parser::peek() const { return tokens[current]; }
Token Parser::previous() const { return tokens[current - 1]; }
bool Parser::isAtEnd() const { return peek().type == TokenType::EndOfFile; }
Token Parser::advance() { if (!isAtEnd()) current++; return previous(); }
bool Parser::check(TokenType type) const { if (isAtEnd()) return false; return peek().type == type; }

bool Parser::match(std::vector<TokenType> types) {
    for (auto type : types) {
        if (check(type)) {
            advance();
            return true;
        }
    }
    return false;
}

Token Parser::consume(TokenType type, const std::string& message) {
    if (check(type)) return advance();
    throw std::runtime_error("Line " + std::to_string(peek().line) + ": " + message);
}

ASTNodePtr Parser::parse() {
    auto program = std::make_unique<ProgramNode>();
    consume(TokenType::NetArambho, "Expected 'NetArambho' at the start of program.");
    while (!isAtEnd() && !check(TokenType::NetShesh)) {
        program->statements.push_back(statement());
    }
    consume(TokenType::NetShesh, "Expected 'NetShesh' at the end of program.");
    return program;
}

ASTNodePtr Parser::statement() {
    if (match({TokenType::JontraGothon})) return deviceDecl();
    if (match({TokenType::JogajogSet})) return linkDecl();
    if (match({TokenType::ThikanaDao})) return ipAssign();
    if (match({TokenType::DorjaDao})) return portAssign();
    if (match({TokenType::PacketPathao})) return sendPacket();
    if (match({TokenType::PacketNey})) {
        Token n = consume(TokenType::Identifier, "Expected node name.");
        consume(TokenType::SemiColon, "Expected ';'.");
        return std::make_unique<RecvPacketNode>(n.value);
    }
    if (match({TokenType::ShobaiPathao})) {
        Token s = consume(TokenType::Identifier, "Expected src node.");
        ExprPtr d = expression();
        consume(TokenType::SemiColon, "Expected ';'.");
        return std::make_unique<BroadcastNode>(s.value, std::move(d));
    }
    if (match({TokenType::PothNirdharon})) {
        Token s = consume(TokenType::Identifier, "Expected src.");
        Token d = consume(TokenType::Identifier, "Expected dest.");
        Token n = consume(TokenType::Identifier, "Expected nextHop.");
        consume(TokenType::SemiColon, "Expected ';'.");
        return std::make_unique<RouteDefNode>(s.value, d.value, n.value);
    }
    if (match({TokenType::JachaiPing})) {
        Token s = consume(TokenType::Identifier, "Expected src.");
        Token d = consume(TokenType::Identifier, "Expected dest.");
        consume(TokenType::SemiColon, "Expected ';'.");
        return std::make_unique<PingNode>(s.value, d.value);
    }
    if (match({TokenType::Bilombho})) {
        Token m = consume(TokenType::Number, "Expected ms.");
        consume(TokenType::SemiColon, "Expected ';'.");
        return std::make_unique<DelayNode>(std::stoi(m.value));
    }
    if (match({TokenType::HariyeFelo})) {
        Token n = consume(TokenType::Identifier, "Expected node.");
        Token p = consume(TokenType::Number, "Expected percent.");
        consume(TokenType::SemiColon, "Expected ';'.");
        return std::make_unique<PacketDropNode>(n.value, std::stoi(p.value));
    }
    if (match({TokenType::GotiNiyontron})) {
        Token n = consume(TokenType::Identifier, "Expected node.");
        Token r = consume(TokenType::Number, "Expected rate.");
        consume(TokenType::SemiColon, "Expected ';'.");
        return std::make_unique<RateLimitNode>(n.value, std::stoi(r.value));
    }
    if (match({TokenType::ProtirodhDao})) {
        Token n = consume(TokenType::Identifier, "Expected node.");
        Token t = consume(TokenType::StringLiteral, "Expected target.");
        consume(TokenType::SemiColon, "Expected ';'.");
        return std::make_unique<FirewallNode>(n.value, t.value);
    }
    if (match({TokenType::NirikhaKoro})) {
        Token n = consume(TokenType::Identifier, "Expected node.");
        consume(TokenType::SemiColon, "Expected ';'.");
        return std::make_unique<MonitorNode>(n.value);
    }
    if (match({TokenType::GhotonaLekho})) {
        Token m = consume(TokenType::StringLiteral, "Expected message.");
        consume(TokenType::SemiColon, "Expected ';'.");
        return std::make_unique<LogEventNode>(m.value);
    }
    if (match({TokenType::Dekhao})) return print();
    if (match({TokenType::Jodi})) return ifStatement();
    if (match({TokenType::GhuroChol})) return loopStatement();
    
    throw std::runtime_error("Unknown statement at line " + std::to_string(peek().line));
}

ASTNodePtr Parser::deviceDecl() {
    Token type = consume(TokenType::Identifier, "Expected device type.");
    Token name = consume(TokenType::Identifier, "Expected device name.");
    consume(TokenType::SemiColon, "Expected ';' after device declaration.");
    return std::make_unique<DeviceDeclNode>(type.value, name.value);
}

ASTNodePtr Parser::linkDecl() {
    Token n1 = consume(TokenType::Identifier, "Expected first node name.");
    Token n2 = consume(TokenType::Identifier, "Expected second node name.");
    consume(TokenType::SemiColon, "Expected ';' after link declaration.");
    return std::make_unique<LinkDeclNode>(n1.value, n2.value);
}

ASTNodePtr Parser::ipAssign() {
    Token node = consume(TokenType::Identifier, "Expected node name.");
    Token ip = consume(TokenType::IPLiteral, "Expected IP address.");
    consume(TokenType::SemiColon, "Expected ';' after IP assignment.");
    return std::make_unique<IPAssignNode>(node.value, ip.value);
}

ASTNodePtr Parser::portAssign() {
    Token node = consume(TokenType::Identifier, "Expected node name.");
    Token port = consume(TokenType::Number, "Expected port number.");
    consume(TokenType::SemiColon, "Expected ';' after port assignment.");
    return std::make_unique<PortAssignNode>(node.value, std::stoi(port.value));
}

ASTNodePtr Parser::sendPacket() {
    Token src = consume(TokenType::Identifier, "Expected source node.");
    Token dest = consume(TokenType::Identifier, "Expected destination node.");
    ExprPtr data = expression();
    consume(TokenType::SemiColon, "Expected ';' after packet send.");
    return std::make_unique<SendPacketNode>(src.value, dest.value, std::move(data));
}

ASTNodePtr Parser::print() {
    ExprPtr expr = expression();
    consume(TokenType::SemiColon, "Expected ';' after dekhao.");
    return std::make_unique<PrintNode>(std::move(expr));
}

ASTNodePtr Parser::ifStatement() {
    consume(TokenType::LParen, "Expected '(' after Jodi.");
    ExprPtr cond = expression();
    consume(TokenType::RParen, "Expected ')' after condition.");
    consume(TokenType::LBrace, "Expected '{' after Jodi condition.");
    auto thenBr = block();
    std::vector<ASTNodePtr> elseBr;
    if (match({TokenType::Nahole})) {
        consume(TokenType::LBrace, "Expected '{' after Nahole.");
        elseBr = block();
    }
    return std::make_unique<IfNode>(std::move(cond), std::move(thenBr), std::move(elseBr));
}

ASTNodePtr Parser::loopStatement() {
    consume(TokenType::LParen, "Expected '(' after GhuroChol.");
    Token count = consume(TokenType::Number, "Expected loop count.");
    consume(TokenType::RParen, "Expected ')' after loop count.");
    consume(TokenType::LBrace, "Expected '{' after GhuroChol.");
    auto body = block();
    return std::make_unique<LoopNode>(std::stoi(count.value), std::move(body));
}

std::vector<ASTNodePtr> Parser::block() {
    std::vector<ASTNodePtr> statements;
    while (!isAtEnd() && !check(TokenType::RBrace)) {
        statements.push_back(statement());
    }
    consume(TokenType::RBrace, "Expected '}' after block.");
    return statements;
}

ExprPtr Parser::expression() {
    if (match({TokenType::GoponKoro})) {
        consume(TokenType::LParen, "Expected '(' after GoponKoro.");
        ExprPtr d = expression();
        consume(TokenType::RParen, "Expected ')'.");
        return std::make_unique<EncryptExpr>(std::move(d));
    }
    if (match({TokenType::UghatKoro})) {
        consume(TokenType::LParen, "Expected '(' after UghatKoro.");
        ExprPtr d = expression();
        consume(TokenType::RParen, "Expected ')'.");
        return std::make_unique<DecryptExpr>(std::move(d));
    }
    return primary();
}

ExprPtr Parser::primary() {
    if (match({TokenType::Identifier})) return std::make_unique<IdentifierExpr>(previous().value);
    if (match({TokenType::Number, TokenType::StringLiteral, TokenType::IPLiteral})) return std::make_unique<LiteralExpr>(previous().value);
    throw std::runtime_error("Expected expression at line " + std::to_string(peek().line));
}

#ifndef AST_H
#define AST_H

#include <string>
#include <vector>
#include <memory>

enum class ASTNodeType {
    Program, DeviceDecl, LinkDecl, IPAssign, PortAssign,
    SendPacket, RecvPacket, Broadcast, RouteDef, Ping,
    Delay, PacketDrop, RateLimit, ApplyRule, Firewall,
    Monitor, LogEvent, Print, IfStatement, LoopStatement,
    FuncDef, FuncCall, Assignment, Expression
};

class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual ASTNodeType getType() const = 0;
};

using ASTNodePtr = std::unique_ptr<ASTNode>;

class ProgramNode : public ASTNode {
public:
    std::vector<ASTNodePtr> statements;
    ASTNodeType getType() const override { return ASTNodeType::Program; }
};

class ExpressionNode : public ASTNode {
public:
    virtual ~ExpressionNode() = default;
    virtual std::string toString() const = 0;
};

using ExprPtr = std::unique_ptr<ExpressionNode>;

class IdentifierExpr : public ExpressionNode {
public:
    std::string name;
    IdentifierExpr(std::string name) : name(name) {}
    std::string toString() const override { return name; }
    ASTNodeType getType() const override { return ASTNodeType::Expression; }
};

class LiteralExpr : public ExpressionNode {
public:
    std::string value;
    LiteralExpr(std::string value) : value(value) {}
    std::string toString() const override { return value; }
    ASTNodeType getType() const override { return ASTNodeType::Expression; }
};

class BinaryExpr : public ExpressionNode {
public:
    ExprPtr left;
    std::string op;
    ExprPtr right;
    BinaryExpr(ExprPtr left, std::string op, ExprPtr right) 
        : left(std::move(left)), op(op), right(std::move(right)) {}
    std::string toString() const override { return "(" + left->toString() + " " + op + " " + right->toString() + ")"; }
    ASTNodeType getType() const override { return ASTNodeType::Expression; }
};

class EncryptExpr : public ExpressionNode {
public:
    ExprPtr data;
    EncryptExpr(ExprPtr data) : data(std::move(data)) {}
    std::string toString() const override { return "encrypt(" + data->toString() + ")"; }
    ASTNodeType getType() const override { return ASTNodeType::Expression; }
};

class DecryptExpr : public ExpressionNode {
public:
    ExprPtr data;
    DecryptExpr(ExprPtr data) : data(std::move(data)) {}
    std::string toString() const override { return "decrypt(" + data->toString() + ")"; }
    ASTNodeType getType() const override { return ASTNodeType::Expression; }
};

// Statements
class DeviceDeclNode : public ASTNode {
public:
    std::string type, name;
    DeviceDeclNode(std::string t, std::string n) : type(t), name(n) {}
    ASTNodeType getType() const override { return ASTNodeType::DeviceDecl; }
};

class LinkDeclNode : public ASTNode {
public:
    std::string node1, node2;
    LinkDeclNode(std::string n1, std::string n2) : node1(n1), node2(n2) {}
    ASTNodeType getType() const override { return ASTNodeType::LinkDecl; }
};

class IPAssignNode : public ASTNode {
public:
    std::string node, ip;
    IPAssignNode(std::string n, std::string i) : node(n), ip(i) {}
    ASTNodeType getType() const override { return ASTNodeType::IPAssign; }
};

class PortAssignNode : public ASTNode {
public:
    std::string node; int port;
    PortAssignNode(std::string n, int p) : node(n), port(p) {}
    ASTNodeType getType() const override { return ASTNodeType::PortAssign; }
};

class SendPacketNode : public ASTNode {
public:
    std::string src, dest; ExprPtr data;
    SendPacketNode(std::string s, std::string d, ExprPtr dat) : src(s), dest(d), data(std::move(dat)) {}
    ASTNodeType getType() const override { return ASTNodeType::SendPacket; }
};

class RecvPacketNode : public ASTNode {
public:
    std::string node;
    RecvPacketNode(std::string n) : node(n) {}
    ASTNodeType getType() const override { return ASTNodeType::RecvPacket; }
};

class BroadcastNode : public ASTNode {
public:
    std::string src; ExprPtr data;
    BroadcastNode(std::string s, ExprPtr d) : src(s), data(std::move(d)) {}
    ASTNodeType getType() const override { return ASTNodeType::Broadcast; }
};

class RouteDefNode : public ASTNode {
public:
    std::string src, dest, nextHop;
    RouteDefNode(std::string s, std::string d, std::string n) : src(s), dest(d), nextHop(n) {}
    ASTNodeType getType() const override { return ASTNodeType::RouteDef; }
};

class PingNode : public ASTNode {
public:
    std::string src, dest;
    PingNode(std::string s, std::string d) : src(s), dest(d) {}
    ASTNodeType getType() const override { return ASTNodeType::Ping; }
};

class DelayNode : public ASTNode {
public:
    int ms;
    DelayNode(int m) : ms(m) {}
    ASTNodeType getType() const override { return ASTNodeType::Delay; }
};

class PacketDropNode : public ASTNode {
public:
    std::string node; int percent;
    PacketDropNode(std::string n, int p) : node(n), percent(p) {}
    ASTNodeType getType() const override { return ASTNodeType::PacketDrop; }
};

class RateLimitNode : public ASTNode {
public:
    std::string node; int rate;
    RateLimitNode(std::string n, int r) : node(n), rate(r) {}
    ASTNodeType getType() const override { return ASTNodeType::RateLimit; }
};

class FirewallNode : public ASTNode {
public:
    std::string node, target;
    FirewallNode(std::string n, std::string t) : node(n), target(t) {}
    ASTNodeType getType() const override { return ASTNodeType::Firewall; }
};

class MonitorNode : public ASTNode {
public:
    std::string node;
    MonitorNode(std::string n) : node(n) {}
    ASTNodeType getType() const override { return ASTNodeType::Monitor; }
};

class LogEventNode : public ASTNode {
public:
    std::string msg;
    LogEventNode(std::string m) : msg(m) {}
    ASTNodeType getType() const override { return ASTNodeType::LogEvent; }
};

class PrintNode : public ASTNode {
public:
    ExprPtr expr;
    PrintNode(ExprPtr e) : expr(std::move(e)) {}
    ASTNodeType getType() const override { return ASTNodeType::Print; }
};

class IfNode : public ASTNode {
public:
    ExprPtr condition; std::vector<ASTNodePtr> thenBranch, elseBranch;
    IfNode(ExprPtr c, std::vector<ASTNodePtr> t, std::vector<ASTNodePtr> e) : condition(std::move(c)), thenBranch(std::move(t)), elseBranch(std::move(e)) {}
    ASTNodeType getType() const override { return ASTNodeType::IfStatement; }
};

class LoopNode : public ASTNode {
public:
    int count; std::vector<ASTNodePtr> body;
    LoopNode(int c, std::vector<ASTNodePtr> b) : count(c), body(std::move(b)) {}
    ASTNodeType getType() const override { return ASTNodeType::LoopStatement; }
};

#endif // AST_H

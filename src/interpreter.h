#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "ast.h"
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>
#include <queue>
#include <memory>

struct Packet {
    std::string src;
    std::string dest;
    std::string payload;
    bool encrypted = false;
};

struct Device {
    std::string name;
    std::string type;
    std::string ip;
    int port = 0;
    std::vector<std::string> neighbors;
    std::queue<Packet> packetQueue;
    std::unordered_map<std::string, std::string> routingTable; // dest -> nextHop
    
    // Firewall/Rules
    std::unordered_set<std::string> blockedIps;
    int dropRate = 0; // 0-100
};

class Interpreter {
public:
    void interpret(const ASTNode* node);

private:
    std::unordered_map<std::string, std::shared_ptr<Device>> devices;
    std::unordered_map<std::string, std::string> variables;

    void visit(const ASTNode* node);
    void visitProgram(const ProgramNode* node);
    void visitDeviceDecl(const DeviceDeclNode* node);
    void visitLinkDecl(const LinkDeclNode* node);
    void visitIPAssign(const IPAssignNode* node);
    void visitPortAssign(const PortAssignNode* node);
    void visitSendPacket(const SendPacketNode* node);
    void visitBroadcast(const BroadcastNode* node);
    void visitPrint(const PrintNode* node);
    void visitIf(const IfNode* node);
    void visitLoop(const LoopNode* node);
    void visitDelay(const ASTNode* node); // Need to add delay node
    
    std::string evaluate(const ExpressionNode* expr);
    
    void routePacket(const std::string& src, const std::string& dest, const std::string& payload);
};

#endif // INTERPRETER_H

#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "ast.h"
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <string>

class SemanticAnalyzer {
public:
    void analyze(const ASTNode* node);

private:
    std::unordered_set<std::string> devices;
    std::unordered_map<std::string, std::string> deviceIps;

    void visit(const ASTNode* node);
    void visitProgram(const ProgramNode* node);
    void visitDeviceDecl(const DeviceDeclNode* node);
    void visitLinkDecl(const LinkDeclNode* node);
    void visitIPAssign(const IPAssignNode* node);
    void visitPortAssign(const PortAssignNode* node);
    void visitSendPacket(const SendPacketNode* node);
    void visitPrint(const PrintNode* node);
    void visitIf(const IfNode* node);
    void visitLoop(const LoopNode* node);

    void error(const std::string& message);
};

#endif // SEMANTIC_H

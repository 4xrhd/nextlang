#include "semantic.h"
#include <stdexcept>
#include <regex>

void SemanticAnalyzer::analyze(const ASTNode* node) {
    visit(node);
}

void SemanticAnalyzer::error(const std::string& message) {
    throw std::runtime_error("Semantic Error: " + message);
}

void SemanticAnalyzer::visit(const ASTNode* node) {
    if (!node) return;
    switch (node->getType()) {
        case ASTNodeType::Program: visitProgram(static_cast<const ProgramNode*>(node)); break;
        case ASTNodeType::DeviceDecl: visitDeviceDecl(static_cast<const DeviceDeclNode*>(node)); break;
        case ASTNodeType::LinkDecl: visitLinkDecl(static_cast<const LinkDeclNode*>(node)); break;
        case ASTNodeType::IPAssign: visitIPAssign(static_cast<const IPAssignNode*>(node)); break;
        case ASTNodeType::PortAssign: visitPortAssign(static_cast<const PortAssignNode*>(node)); break;
        case ASTNodeType::SendPacket: visitSendPacket(static_cast<const SendPacketNode*>(node)); break;
        case ASTNodeType::Print: visitPrint(static_cast<const PrintNode*>(node)); break;
        case ASTNodeType::IfStatement: visitIf(static_cast<const IfNode*>(node)); break;
        case ASTNodeType::LoopStatement: visitLoop(static_cast<const LoopNode*>(node)); break;
        default: break; // Many nodes to be implemented
    }
}

void SemanticAnalyzer::visitProgram(const ProgramNode* node) {
    for (const auto& stmt : node->statements) {
        visit(stmt.get());
    }
}

void SemanticAnalyzer::visitDeviceDecl(const DeviceDeclNode* node) {
    if (devices.count(node->name)) {
        error("Duplicate device name: " + node->name);
    }
    devices.insert(node->name);
}

void SemanticAnalyzer::visitLinkDecl(const LinkDeclNode* node) {
    if (devices.find(node->node1) == devices.end()) {
        error("Device not declared: " + node->node1);
    }
    if (devices.find(node->node2) == devices.end()) {
        error("Device not declared: " + node->node2);
    }
}

void SemanticAnalyzer::visitIPAssign(const IPAssignNode* node) {
    if (devices.find(node->node) == devices.end()) {
        error("Device not declared: " + node->node);
    }
    // Simple IP validation
    std::regex ipRegex(R"(\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3})");
    if (!std::regex_match(node->ip, ipRegex)) {
        error("Invalid IP format: " + node->ip);
    }
    deviceIps[node->node] = node->ip;
}

void SemanticAnalyzer::visitPortAssign(const PortAssignNode* node) {
    if (devices.find(node->node) == devices.end()) {
        error("Device not declared: " + node->node);
    }
}

void SemanticAnalyzer::visitSendPacket(const SendPacketNode* node) {
    if (devices.find(node->src) == devices.end()) {
        error("Source device not declared: " + node->src);
    }
    if (devices.find(node->dest) == devices.end()) {
        error("Destination device not declared: " + node->dest);
    }
}

void SemanticAnalyzer::visitPrint(const PrintNode* node) {
    // Basic print doesn't need much semantic check for now
}

void SemanticAnalyzer::visitIf(const IfNode* node) {
    // Condition check?
    for (const auto& stmt : node->thenBranch) visit(stmt.get());
    for (const auto& stmt : node->elseBranch) visit(stmt.get());
}

void SemanticAnalyzer::visitLoop(const LoopNode* node) {
    if (node->count < 0) error("Loop count cannot be negative");
    for (const auto& stmt : node->body) visit(stmt.get());
}

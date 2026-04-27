#include "interpreter.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>

void Interpreter::interpret(const ASTNode* node) {
    visit(node);
}

void Interpreter::visit(const ASTNode* node) {
    if (!node) return;
    switch (node->getType()) {
        case ASTNodeType::Program: visitProgram(static_cast<const ProgramNode*>(node)); break;
        case ASTNodeType::DeviceDecl: visitDeviceDecl(static_cast<const DeviceDeclNode*>(node)); break;
        case ASTNodeType::LinkDecl: visitLinkDecl(static_cast<const LinkDeclNode*>(node)); break;
        case ASTNodeType::IPAssign: visitIPAssign(static_cast<const IPAssignNode*>(node)); break;
        case ASTNodeType::PortAssign: visitPortAssign(static_cast<const PortAssignNode*>(node)); break;
        case ASTNodeType::SendPacket: visitSendPacket(static_cast<const SendPacketNode*>(node)); break;
        case ASTNodeType::Broadcast: visitBroadcast(static_cast<const BroadcastNode*>(node)); break;
        case ASTNodeType::Print: visitPrint(static_cast<const PrintNode*>(node)); break;
        case ASTNodeType::IfStatement: visitIf(static_cast<const IfNode*>(node)); break;
        case ASTNodeType::LoopStatement: visitLoop(static_cast<const LoopNode*>(node)); break;
        case ASTNodeType::RecvPacket: {
            auto n = static_cast<const RecvPacketNode*>(node);
            auto dev = devices[n->node];
            if (dev && !dev->packetQueue.empty()) {
                auto p = dev->packetQueue.front();
                dev->packetQueue.pop();
                std::cout << "[RECV] " << n->node << " received packet from " << p.src << ": " << p.payload << "\n";
            }
            break;
        }
        case ASTNodeType::Delay: {
            auto d = static_cast<const DelayNode*>(node);
            std::this_thread::sleep_for(std::chrono::milliseconds(d->ms));
            break;
        }
        case ASTNodeType::PacketDrop: {
            auto d = static_cast<const PacketDropNode*>(node);
            if (devices.count(d->node)) devices[d->node]->dropRate = d->percent;
            break;
        }
        case ASTNodeType::Firewall: {
            auto f = static_cast<const FirewallNode*>(node);
            if (devices.count(f->node)) devices[f->node]->blockedIps.insert(f->target);
            break;
        }
        case ASTNodeType::Monitor: {
            auto m = static_cast<const MonitorNode*>(node);
            auto dev = devices[m->node];
            if (dev) {
                std::cout << "[MONITOR] Device: " << dev->name << " | IP: " << dev->ip << " | Queue Size: " << dev->packetQueue.size() << "\n";
            }
            break;
        }
        case ASTNodeType::LogEvent: {
            auto l = static_cast<const LogEventNode*>(node);
            std::cout << "[LOG] " << l->msg << "\n";
            break;
        }
        case ASTNodeType::Ping: {
            auto p = static_cast<const PingNode*>(node);
            std::cout << "[PING] " << p->src << " -> " << p->dest << " ... Success (Simulated)\n";
            break;
        }
        case ASTNodeType::RouteDef: {
            auto r = static_cast<const RouteDefNode*>(node);
            if (devices.count(r->src)) devices[r->src]->routingTable[r->dest] = r->nextHop;
            break;
        }
        default: break;
    }
}

void Interpreter::visitProgram(const ProgramNode* node) {
    for (const auto& stmt : node->statements) {
        visit(stmt.get());
    }
}

void Interpreter::visitDeviceDecl(const DeviceDeclNode* node) {
    auto dev = std::make_shared<Device>();
    dev->name = node->name;
    dev->type = node->type;
    devices[node->name] = dev;
}

void Interpreter::visitLinkDecl(const LinkDeclNode* node) {
    if (devices.count(node->node1) && devices.count(node->node2)) {
        devices[node->node1]->neighbors.push_back(node->node2);
        devices[node->node2]->neighbors.push_back(node->node1);
    }
}

void Interpreter::visitIPAssign(const IPAssignNode* node) {
    if (devices.count(node->node)) devices[node->node]->ip = node->ip;
}

void Interpreter::visitPortAssign(const PortAssignNode* node) {
    if (devices.count(node->node)) devices[node->node]->port = node->port;
}

void Interpreter::visitSendPacket(const SendPacketNode* node) {
    routePacket(node->src, node->dest, evaluate(node->data.get()));
}

void Interpreter::visitBroadcast(const BroadcastNode* node) {
    auto srcDev = devices[node->src];
    if (!srcDev) return;
    std::string payload = evaluate(node->data.get());
    for (const auto& neighbor : srcDev->neighbors) {
        routePacket(node->src, neighbor, payload);
    }
}

void Interpreter::visitPrint(const PrintNode* node) {
    std::cout << evaluate(node->expr.get()) << "\n";
}

void Interpreter::visitIf(const IfNode* node) {
    std::string cond = evaluate(node->condition.get());
    if (cond == "1" || cond == "true" || !cond.empty() && cond != "0") {
        for (const auto& stmt : node->thenBranch) visit(stmt.get());
    } else {
        for (const auto& stmt : node->elseBranch) visit(stmt.get());
    }
}

void Interpreter::visitLoop(const LoopNode* node) {
    for (int i = 0; i < node->count; ++i) {
        for (const auto& stmt : node->body) visit(stmt.get());
    }
}

std::string Interpreter::evaluate(const ExpressionNode* expr) {
    if (!expr) return "";
    // Simplified evaluation
    return expr->toString(); 
    // In a real implementation, toString() would be replaced by actual value evaluation
}

void Interpreter::routePacket(const std::string& src, const std::string& dest, const std::string& payload) {
    auto srcDev = devices[src];
    auto destDev = devices[dest];
    if (!srcDev || !destDev) return;

    // Simulate packet drop
    if (srcDev->dropRate > 0 && (rand() % 100 < srcDev->dropRate)) {
        std::cout << "[DROP] Packet from " << src << " to " << dest << " was lost.\n";
        return;
    }

    // Simulate firewall
    if (destDev->blockedIps.count(srcDev->ip)) {
        std::cout << "[BLOCK] Firewall on " << dest << " blocked packet from " << src << " (" << srcDev->ip << ")\n";
        return;
    }

    std::cout << "[SEND] " << src << " sending to " << dest << ": " << payload << "\n";
    destDev->packetQueue.push({src, dest, payload});
}

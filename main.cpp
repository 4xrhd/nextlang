#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <queue>
#include <thread>
#include <chrono>
#include <fstream>
#include <sstream>
#include <algorithm>

// --- Tokens ---
enum class TokenType {
    NetArambho, NetShesh, JontraGothon, JogajogSet, ThikanaDao, DorjaDao,
    PacketPathao, PacketNey, ShobaiPathao, PothNirdharon, JachaiPing,
    Bilombho, HariyeFelo, GotiNiyontron, NiyomBoshao, ProtirodhDao,
    GoponKoro, UghatKoro, NirikhaKoro, GhotonaLekho, Jodi, Nahole,
    GhuroChol, KajGothon, Dekhao,
    Identifier, IPLiteral, StringLiteral, Number,
    LParen, RParen, LBrace, RBrace, SemiColon, Comma,
    EndOfFile
};

struct Token {
    TokenType type;
    std::string value;
};

// --- Lexer ---
class Lexer {
    std::string source;
    size_t pos = 0;
public:
    Lexer(std::string src) : source(src) {}
    std::vector<Token> tokenize() {
        std::vector<Token> tokens;
        while (pos < source.length()) {
            char c = source[pos];
            if (isspace(c)) { pos++; continue; }
            if (c == '/' && source[pos+1] == '/') { while (pos < source.length() && source[pos] != '\n') pos++; continue; }
            
            if (isalpha(c)) {
                std::string s;
                while (pos < source.length() && (isalnum(source[pos]) || source[pos] == '_')) s += source[pos++];
                if (s == "NetArambho") tokens.push_back({TokenType::NetArambho, s});
                else if (s == "NetShesh") tokens.push_back({TokenType::NetShesh, s});
                else if (s == "JontraGothon") tokens.push_back({TokenType::JontraGothon, s});
                else if (s == "JogajogSet") tokens.push_back({TokenType::JogajogSet, s});
                else if (s == "ThikanaDao") tokens.push_back({TokenType::ThikanaDao, s});
                else if (s == "DorjaDao") tokens.push_back({TokenType::DorjaDao, s});
                else if (s == "PacketPathao") tokens.push_back({TokenType::PacketPathao, s});
                else if (s == "PacketNey") tokens.push_back({TokenType::PacketNey, s});
                else if (s == "ShobaiPathao") tokens.push_back({TokenType::ShobaiPathao, s});
                else if (s == "PothNirdharon") tokens.push_back({TokenType::PothNirdharon, s});
                else if (s == "JachaiPing") tokens.push_back({TokenType::JachaiPing, s});
                else if (s == "Bilombho") tokens.push_back({TokenType::Bilombho, s});
                else if (s == "HariyeFelo") tokens.push_back({TokenType::HariyeFelo, s});
                else if (s == "GotiNiyontron") tokens.push_back({TokenType::GotiNiyontron, s});
                else if (s == "NiyomBoshao") tokens.push_back({TokenType::NiyomBoshao, s});
                else if (s == "ProtirodhDao") tokens.push_back({TokenType::ProtirodhDao, s});
                else if (s == "GoponKoro") tokens.push_back({TokenType::GoponKoro, s});
                else if (s == "UghatKoro") tokens.push_back({TokenType::UghatKoro, s});
                else if (s == "NirikhaKoro") tokens.push_back({TokenType::NirikhaKoro, s});
                else if (s == "GhotonaLekho") tokens.push_back({TokenType::GhotonaLekho, s});
                else if (s == "Jodi") tokens.push_back({TokenType::Jodi, s});
                else if (s == "Nahole") tokens.push_back({TokenType::Nahole, s});
                else if (s == "GhuroChol") tokens.push_back({TokenType::GhuroChol, s});
                else if (s == "KajGothon") tokens.push_back({TokenType::KajGothon, s});
                else if (s == "Dekhao") tokens.push_back({TokenType::Dekhao, s});
                else tokens.push_back({TokenType::Identifier, s});
                continue;
            }
            if (isdigit(c)) {
                std::string s;
                int dots = 0;
                while (pos < source.length() && (isdigit(source[pos]) || source[pos] == '.')) {
                    if (source[pos] == '.') dots++;
                    s += source[pos++];
                }
                tokens.push_back({dots == 3 ? TokenType::IPLiteral : TokenType::Number, s});
                continue;
            }
            if (c == '"') {
                pos++; std::string s;
                while (pos < source.length() && source[pos] != '"') s += source[pos++];
                pos++; tokens.push_back({TokenType::StringLiteral, s});
                continue;
            }
            switch (c) {
                case '(': tokens.push_back({TokenType::LParen, "("}); break;
                case ')': tokens.push_back({TokenType::RParen, ")"}); break;
                case '{': tokens.push_back({TokenType::LBrace, "{"}); break;
                case '}': tokens.push_back({TokenType::RBrace, "}"}); break;
                case ';': tokens.push_back({TokenType::SemiColon, ";"}); break;
                case ',': tokens.push_back({TokenType::Comma, ","}); break;
            }
            pos++;
        }
        tokens.push_back({TokenType::EndOfFile, ""});
        return tokens;
    }
};

// --- AST ---
struct Node { virtual ~Node() = default; };
struct Stmt : Node {};
struct Expr : Node { virtual std::string eval() = 0; };

struct Program : Node { std::vector<std::shared_ptr<Stmt>> stmts; };
struct LiteralExpr : Expr { std::string val; LiteralExpr(std::string v) : val(v) {} std::string eval() override { return val; } };
struct EncryptExpr : Expr { std::shared_ptr<Expr> data; EncryptExpr(std::shared_ptr<Expr> d) : data(d) {} std::string eval() override {
    std::string s = data->eval(); for(char &c : s) c++; return "[ENC]"+s;
}};
struct DecryptExpr : Expr { std::shared_ptr<Expr> data; DecryptExpr(std::shared_ptr<Expr> d) : data(d) {} std::string eval() override {
    std::string s = data->eval(); if(s.substr(0,5)=="[ENC]") { s=s.substr(5); for(char &c : s) c--; } return s;
}};

struct DeviceDecl : Stmt { std::string type, name; };
struct LinkDecl : Stmt { std::string n1, n2; };
struct IPAssign : Stmt { std::string name, ip; };
struct PortAssign : Stmt { std::string name; int port; };
struct SendPacket : Stmt { std::string src, dest; std::shared_ptr<Expr> data; };
struct RecvPacket : Stmt { std::string name; };
struct Broadcast : Stmt { std::string src; std::shared_ptr<Expr> data; };
struct RouteDef : Stmt { std::string src, dest, next; };
struct Ping : Stmt { std::string src, dest; };
struct Delay : Stmt { int ms; };
struct Drop : Stmt { std::string name; int pct; };
struct Rate : Stmt { std::string name; int r; };
struct Proto : Stmt { std::string name, p; };
struct Firewall : Stmt { std::string name, target; };
struct Monitor : Stmt { std::string name; };
struct Log : Stmt { std::string msg; };
struct Print : Stmt { std::shared_ptr<Expr> expr; };
struct IfStmt : Stmt { std::shared_ptr<Expr> cond; std::vector<std::shared_ptr<Stmt>> thenBr, elseBr; };
struct LoopStmt : Stmt { int count; std::vector<std::shared_ptr<Stmt>> body; };
struct FuncDef : Stmt { std::string name; std::vector<std::shared_ptr<Stmt>> body; };
struct FuncCall : Stmt { std::string name; };

// --- Parser ---
class Parser {
    std::vector<Token> tokens;
    size_t cur = 0;
    Token peek() { return tokens[cur]; }
    Token advance() { return tokens[cur++]; }
    bool match(TokenType t) { if (peek().type == t) { advance(); return true; } return false; }
public:
    Parser(std::vector<Token> t) : tokens(t) {}
    std::shared_ptr<Expr> parseExpr() {
        if (match(TokenType::GoponKoro)) { advance(); auto e = parseExpr(); advance(); return std::make_shared<EncryptExpr>(e); }
        if (match(TokenType::UghatKoro)) { advance(); auto e = parseExpr(); advance(); return std::make_shared<DecryptExpr>(e); }
        return std::make_shared<LiteralExpr>(advance().value);
    }
    std::vector<std::shared_ptr<Stmt>> parseBlock() {
        std::vector<std::shared_ptr<Stmt>> stmts;
        while (peek().type != TokenType::RBrace && peek().type != TokenType::EndOfFile) {
            auto s = parseStmt(); if (s) stmts.push_back(s);
        }
        advance(); return stmts;
    }
    std::shared_ptr<Stmt> parseStmt() {
        if (match(TokenType::JontraGothon)) { auto d = std::make_shared<DeviceDecl>(); d->type = advance().value; d->name = advance().value; match(TokenType::SemiColon); return d; }
        if (match(TokenType::JogajogSet)) { auto l = std::make_shared<LinkDecl>(); l->n1 = advance().value; l->n2 = advance().value; match(TokenType::SemiColon); return l; }
        if (match(TokenType::ThikanaDao)) { auto i = std::make_shared<IPAssign>(); i->name = advance().value; i->ip = advance().value; match(TokenType::SemiColon); return i; }
        if (match(TokenType::DorjaDao)) { auto p = std::make_shared<PortAssign>(); p->name = advance().value; p->port = std::stoi(advance().value); match(TokenType::SemiColon); return p; }
        if (match(TokenType::PacketPathao)) { auto s = std::make_shared<SendPacket>(); s->src = advance().value; s->dest = advance().value; s->data = parseExpr(); match(TokenType::SemiColon); return s; }
        if (match(TokenType::PacketNey)) { auto r = std::make_shared<RecvPacket>(); r->name = advance().value; match(TokenType::SemiColon); return r; }
        if (match(TokenType::ShobaiPathao)) { auto b = std::make_shared<Broadcast>(); b->src = advance().value; b->data = parseExpr(); match(TokenType::SemiColon); return b; }
        if (match(TokenType::PothNirdharon)) { auto r = std::make_shared<RouteDef>(); r->src = advance().value; r->dest = advance().value; r->next = advance().value; match(TokenType::SemiColon); return r; }
        if (match(TokenType::JachaiPing)) { auto p = std::make_shared<Ping>(); p->src = advance().value; p->dest = advance().value; match(TokenType::SemiColon); return p; }
        if (match(TokenType::Bilombho)) { auto d = std::make_shared<Delay>(); d->ms = std::stoi(advance().value); match(TokenType::SemiColon); return d; }
        if (match(TokenType::HariyeFelo)) { auto d = std::make_shared<Drop>(); d->name = advance().value; d->pct = std::stoi(advance().value); match(TokenType::SemiColon); return d; }
        if (match(TokenType::GotiNiyontron)) { auto r = std::make_shared<Rate>(); r->name = advance().value; r->r = std::stoi(advance().value); match(TokenType::SemiColon); return r; }
        if (match(TokenType::NiyomBoshao)) { auto p = std::make_shared<Proto>(); p->name = advance().value; p->p = advance().value; match(TokenType::SemiColon); return p; }
        if (match(TokenType::ProtirodhDao)) { auto f = std::make_shared<Firewall>(); f->name = advance().value; f->target = advance().value; match(TokenType::SemiColon); return f; }
        if (match(TokenType::NirikhaKoro)) { auto m = std::make_shared<Monitor>(); m->name = advance().value; match(TokenType::SemiColon); return m; }
        if (match(TokenType::GhotonaLekho)) { auto l = std::make_shared<Log>(); l->msg = advance().value; match(TokenType::SemiColon); return l; }
        if (match(TokenType::Dekhao)) { auto p = std::make_shared<Print>(); p->expr = parseExpr(); match(TokenType::SemiColon); return p; }
        if (match(TokenType::Jodi)) { advance(); auto cond = parseExpr(); advance(); advance(); auto thenBr = parseBlock(); std::vector<std::shared_ptr<Stmt>> elseBr; if (match(TokenType::Nahole)) { advance(); elseBr = parseBlock(); } auto i = std::make_shared<IfStmt>(); i->cond = cond; i->thenBr = thenBr; i->elseBr = elseBr; return i; }
        if (match(TokenType::GhuroChol)) { advance(); int c = std::stoi(advance().value); advance(); advance(); auto body = parseBlock(); auto l = std::make_shared<LoopStmt>(); l->count = c; l->body = body; return l; }
        if (match(TokenType::KajGothon)) { std::string n = advance().value; advance(); advance(); advance(); auto body = parseBlock(); auto f = std::make_shared<FuncDef>(); f->name = n; f->body = body; return f; }
        if (peek().type == TokenType::Identifier) { std::string n = advance().value; if (match(TokenType::LParen)) { advance(); match(TokenType::SemiColon); auto c = std::make_shared<FuncCall>(); c->name = n; return c; } }
        return nullptr;
    }
    std::shared_ptr<Program> parse() {
        auto p = std::make_shared<Program>();
        match(TokenType::NetArambho);
        while (peek().type != TokenType::NetShesh && peek().type != TokenType::EndOfFile) {
            auto s = parseStmt(); if (s) p->stmts.push_back(s);
        }
        match(TokenType::NetShesh); return p;
    }
};

// --- Interpreter ---
struct Device { std::string name, type, ip, proto = "ANY"; int port = 0, drop = 0; std::vector<std::string> neighbors; std::queue<std::pair<std::string, std::string>> packets; std::unordered_set<std::string> blocked; };
class Interpreter {
    std::unordered_map<std::string, std::shared_ptr<Device>> devices;
    std::unordered_map<std::string, std::shared_ptr<FuncDef>> funcs;
public:
    void exec(std::shared_ptr<Stmt> s) {
        if (!s) return;
        if (auto d = std::dynamic_pointer_cast<DeviceDecl>(s)) { devices[d->name] = std::make_shared<Device>(); devices[d->name]->name = d->name; devices[d->name]->type = d->type; }
        else if (auto l = std::dynamic_pointer_cast<LinkDecl>(s)) { if(devices.count(l->n1) && devices.count(l->n2)) { devices[l->n1]->neighbors.push_back(l->n2); devices[l->n2]->neighbors.push_back(l->n1); } }
        else if (auto i = std::dynamic_pointer_cast<IPAssign>(s)) { if(devices.count(i->name)) devices[i->name]->ip = i->ip; }
        else if (auto p = std::dynamic_pointer_cast<PortAssign>(s)) { if(devices.count(p->name)) devices[p->name]->port = p->port; }
        else if (auto sp = std::dynamic_pointer_cast<SendPacket>(s)) { send(sp->src, sp->dest, sp->data->eval()); }
        else if (auto rp = std::dynamic_pointer_cast<RecvPacket>(s)) { auto dev = devices[rp->name]; if(dev && !dev->packets.empty()) { auto p = dev->packets.front(); dev->packets.pop(); std::cout << "[RECV] " << rp->name << " from " << p.first << ": " << p.second << "\n"; } }
        else if (auto b = std::dynamic_pointer_cast<Broadcast>(s)) { auto dev = devices[b->src]; if(dev) for(auto& n : dev->neighbors) send(b->src, n, b->data->eval()); }
        else if (auto pi = std::dynamic_pointer_cast<Ping>(s)) { std::cout << "[PING] " << pi->src << " -> " << pi->dest << " ... Success\n"; }
        else if (auto de = std::dynamic_pointer_cast<Delay>(s)) { std::this_thread::sleep_for(std::chrono::milliseconds(de->ms)); }
        else if (auto dr = std::dynamic_pointer_cast<Drop>(s)) { if(devices.count(dr->name)) devices[dr->name]->drop = dr->pct; }
        else if (auto pr = std::dynamic_pointer_cast<Proto>(s)) { if(devices.count(pr->name)) devices[pr->name]->proto = pr->p; }
        else if (auto fr = std::dynamic_pointer_cast<Firewall>(s)) { if(devices.count(fr->name)) devices[fr->name]->blocked.insert(fr->target); }
        else if (auto mo = std::dynamic_pointer_cast<Monitor>(s)) { auto dev = devices[mo->name]; if(dev) std::cout << "[MON] " << dev->name << " IP:" << dev->ip << " Proto:" << dev->proto << " Queue:" << dev->packets.size() << "\n"; }
        else if (auto lo = std::dynamic_pointer_cast<Log>(s)) { std::cout << "[LOG] " << lo->msg << "\n"; }
        else if (auto pr = std::dynamic_pointer_cast<Print>(s)) { std::cout << pr->expr->eval() << "\n"; }
        else if (auto ift = std::dynamic_pointer_cast<IfStmt>(s)) { if(!ift->cond->eval().empty() && ift->cond->eval() != "0") for(auto& sub : ift->thenBr) exec(sub); else for(auto& sub : ift->elseBr) exec(sub); }
        else if (auto lp = std::dynamic_pointer_cast<LoopStmt>(s)) { for(int i=0; i<lp->count; i++) for(auto& sub : lp->body) exec(sub); }
        else if (auto fd = std::dynamic_pointer_cast<FuncDef>(s)) { funcs[fd->name] = fd; }
        else if (auto fc = std::dynamic_pointer_cast<FuncCall>(s)) { if(funcs.count(fc->name)) for(auto& sub : funcs[fc->name]->body) exec(sub); }
    }
    void send(std::string s, std::string d, std::string p) {
        auto src = devices[s], dst = devices[d]; if(!src || !dst) return;
        if (src->drop > 0 && rand()%100 < src->drop) { std::cout << "[DROP] from " << s << "\n"; return; }
        if (dst->blocked.count(src->ip)) { std::cout << "[BLOCK] " << d << " blocked " << s << "\n"; return; }
        std::cout << "[SEND] " << s << " -> " << d << ": " << p << "\n";
        dst->packets.push({s, p});
    }
    void run(std::shared_ptr<Program> p) { for (auto& s : p->stmts) exec(s); }
};

int main(int argc, char** argv) {
    if (argc < 2) return 1;
    std::ifstream f(argv[1]); std::stringstream b; b << f.rdbuf();
    Lexer l(b.str()); Parser p(l.tokenize()); Interpreter i;
    std::cout << "--- NetXLang Start ---\n";
    i.run(p.parse());
    std::cout << "--- NetXLang End ---\n";
    return 0;
}

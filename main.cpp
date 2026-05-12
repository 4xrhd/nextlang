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

using namespace std;

// --- THE COMPILER (Backend Logic) ---
struct Device {
    string name, type, ip, proto = "ANY";
    int port = 0, drop = 0, rate = 0;
    vector<string> neighbors;
    queue<pair<string, string>> packets;
    unordered_set<string> blocked;
    unordered_map<string, string> routes;
};

struct NetCompiler {
    unordered_map<string, shared_ptr<Device>> devs;
    unordered_map<string, vector<string>> user_funcs;

    void addDevice(string type, string name) {
        devs[name] = make_shared<Device>();
        devs[name]->type = type;
        devs[name]->name = name;
    }

    void connect(string n1, string n2) {
        if (devs.count(n1) && devs.count(n2)) {
            devs[n1]->neighbors.push_back(n2);
            devs[n2]->neighbors.push_back(n1);
        }
    }

    void setIP(string name, string ip) { if (devs.count(name)) devs[name]->ip = ip; }
    void setPort(string name, int port) { if (devs.count(name)) devs[name]->port = port; }
    void setProto(string name, string p) { if (devs.count(name)) devs[name]->proto = p; }
    void setRate(string name, int r) { if (devs.count(name)) devs[name]->rate = r; }
    void setRoute(string src, string dest, string next) { if (devs.count(src)) devs[src]->routes[dest] = next; }

    void sendPacket(string s, string d, string p) {
        if (!devs.count(s) || !devs.count(d)) return;
        auto src = devs[s], dst = devs[d];
        if (src->drop > 0 && rand() % 100 < src->drop) { cout << "[DROP] from " << s << "\n"; return; }
        if (dst->blocked.count(src->ip)) { cout << "[BLOCK] " << d << " blocked " << s << "\n"; return; }
        cout << "[SEND] " << s << " -> " << d << ": " << p << "\n";
        dst->packets.push({s, p});
    }

    void recvPacket(string name) {
        if (devs.count(name) && !devs[name]->packets.empty()) {
            auto p = devs[name]->packets.front();
            devs[name]->packets.pop();
            cout << "[RECV] " << name << " from " << p.first << ": " << p.second << "\n";
        }
    }

    void broadcast(string s, string p) {
        if (devs.count(s)) for (auto& n : devs[s]->neighbors) sendPacket(s, n, p);
    }
};

// --- HELPER FUNCTIONS ---
string clean(string s) {
    while (!s.empty() && (s.back() == ';' || s.back() == ')' || s.back() == '}')) s.pop_back();
    while (!s.empty() && (s.front() == '(' || s.front() == '{')) s = s.substr(1);
    if (s.size() >= 2 && s.front() == '"' && s.back() == '"') s = s.substr(1, s.size() - 2);
    return s;
}

string eval(string s) {
    size_t p = s.find('(');
    if (s.find("GoponKoro") != string::npos && p != string::npos) {
        string d = clean(s.substr(p)); for (char& c : d) c++; return "[ENC]" + d;
    }
    if (s.find("UghatKoro") != string::npos && p != string::npos) {
        string d = clean(s.substr(p));
        if (d.substr(0, 5) == "[ENC]") { d = d.substr(5); for (char& c : d) c--; } return d;
    }
    return clean(s);
}

// --- THE INTERPRETER ---
void run(NetCompiler& c, const vector<string>& words, int& i);

vector<string> captureBlock(const vector<string>& w, int& i) {
    vector<string> block; int depth = 1;
    while (i < w.size() && depth > 0) {
        if (w[i] == "{") depth++; else if (w[i] == "}") depth--;
        if (depth > 0) block.push_back(w[i++]); else i++;
    }
    return block;
}

void handleCommand(NetCompiler& c, string cmd, const vector<string>& w, int& i) {
    if (cmd == "JontraGothon") { string type = w[i++], name = clean(w[i++]); c.addDevice(type, name); }
    else if (cmd == "JogajogSet") { string n1 = clean(w[i++]), n2 = clean(w[i++]); c.connect(n1, n2); }
    else if (cmd == "ThikanaDao") { string n = clean(w[i++]), ip = clean(w[i++]); c.setIP(n, ip); }
    else if (cmd == "DorjaDao") { string n = clean(w[i++]), p = clean(w[i++]); c.setPort(n, stoi(p)); }
    else if (cmd == "PacketPathao") { string src = clean(w[i++]), dst = clean(w[i++]), msg = eval(w[i++]); c.sendPacket(src, dst, msg); }
    else if (cmd == "PacketNey") { c.recvPacket(clean(w[i++])); }
    else if (cmd == "ShobaiPathao") { string src = clean(w[i++]), msg = eval(w[i++]); c.broadcast(src, msg); }
    else if (cmd == "PothNirdharon") { string s = clean(w[i++]), d = clean(w[i++]), n = clean(w[i++]); c.setRoute(s, d, n); }
    else if (cmd == "JachaiPing") { string s = clean(w[i++]), d = clean(w[i++]); cout << "[PING] " << s << " -> " << d << " ... Success\n"; }
    else if (cmd == "Bilombho") { this_thread::sleep_for(chrono::milliseconds(stoi(clean(w[i++])))); }
    else if (cmd == "HariyeFelo") { string n = clean(w[i++]); int p = stoi(clean(w[i++])); if (c.devs.count(n)) c.devs[n]->drop = p; }
    else if (cmd == "GotiNiyontron") { string n = clean(w[i++]), r = clean(w[i++]); c.setRate(n, stoi(r)); }
    else if (cmd == "NiyomBoshao") { string n = clean(w[i++]), p = clean(w[i++]); c.setProto(n, p); }
    else if (cmd == "ProtirodhDao") { string n = clean(w[i++]), target = clean(w[i++]); if (c.devs.count(n)) c.devs[n]->blocked.insert(target); }
    else if (cmd == "NirikhaKoro") { string n = clean(w[i++]); if (c.devs.count(n)) cout << "[MON] " << n << " IP:" << c.devs[n]->ip << " Proto:" << c.devs[n]->proto << " Queue:" << c.devs[n]->packets.size() << "\n"; }
    else if (cmd == "GhotonaLekho") { cout << "[LOG] " << clean(w[i++]) << "\n"; }
    else if (cmd == "Dekhao") { cout << eval(w[i++]) << "\n"; }
    else if (cmd == "Jodi") {
        bool ok = c.devs.count(clean(w[i++])); i++; vector<string> thenBody = captureBlock(w, i), elseBody;
        if (i < w.size() && w[i] == "Nahole") { i++; i++; elseBody = captureBlock(w, i); }
        int start = 0; if (ok) run(c, thenBody, start); else if (!elseBody.empty()) run(c, elseBody, start);
    }
    else if (cmd == "GhuroChol") {
        int count = stoi(clean(w[i++])); i++; vector<string> body = captureBlock(w, i);
        for (int k = 0; k < count; k++) { int start = 0; run(c, body, start); }
    }
    else if (cmd == "KajGothon") { string name = clean(w[i++]); i++; c.user_funcs[name] = captureBlock(w, i); }
    else if (c.user_funcs.count(clean(cmd))) { 
        int start = 0; run(c, c.user_funcs[clean(cmd)], start); 
        if (i < w.size() && w[i].find('(') != string::npos) { i++; while (i < w.size() && w[i++].find(')') == string::npos); }
    }
}

void run(NetCompiler& c, const vector<string>& words, int& i) {
    while (i < words.size()) {
        string cmd = words[i++]; if (cmd == "NetArambho" || cmd == "NetShesh" || cmd == "{" || cmd == "}") continue;
        handleCommand(c, cmd, words, i);
    }
}

int main(int argc, char** argv) {
    if (argc < 2) return 1;
    ifstream f(argv[1]); stringstream buffer; buffer << f.rdbuf(); string src = buffer.str();
    vector<string> words; string cur; bool inQ = false;
    for (size_t i = 0; i < src.size(); i++) {
        if (src[i] == '"') { inQ = !inQ; cur += '"'; if (!inQ) { words.push_back(cur); cur = ""; } }
        else if (isspace(src[i]) && !inQ) { if (!cur.empty()) { words.push_back(cur); cur = ""; } } else cur += src[i];
    }
    if (!cur.empty()) words.push_back(cur);
    NetCompiler compiler; cout << "--- NetXLang Start ---\n"; int idx = 0; run(compiler, words, idx); cout << "--- NetXLang End ---\n";
    return 0;
}

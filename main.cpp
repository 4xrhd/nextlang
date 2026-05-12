#include <chrono>
#include <fstream>
#include <iostream>
#include <memory>
#include <queue>
#include <sstream>
#include <string>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct Device {
    string name;
    string type;
    string ip;
    string proto = "ANY";

    int port = 0;
    int drop = 0;
    int rate = 0;

    vector<string> neighbors;
    queue<pair<string, string>> packets;
    unordered_set<string> blocked;
    unordered_map<string, string> routes;
};

struct NetCompiler {
    unordered_map<string, shared_ptr<Device>> devices;
    unordered_map<string, vector<string>> userFunctions;

    bool hasDevice(const string& name) const { return devices.count(name) > 0; }

    void addDevice(const string& type, const string& name) {
        auto d = make_shared<Device>();
        d->type = type;
        d->name = name;
        devices[name] = d;
    }

    void connect(const string& a, const string& b) {
        if (!hasDevice(a) || !hasDevice(b)) return;
        devices[a]->neighbors.push_back(b);
        devices[b]->neighbors.push_back(a);
    }

    void setIP(const string& name, const string& ip) {
        if (hasDevice(name)) devices[name]->ip = ip;
    }

    void setPort(const string& name, int port) {
        if (hasDevice(name)) devices[name]->port = port;
    }

    void setProto(const string& name, const string& proto) {
        if (hasDevice(name)) devices[name]->proto = proto;
    }

    void setRate(const string& name, int rate) {
        if (hasDevice(name)) devices[name]->rate = rate;
    }

    void setRoute(const string& src, const string& dest, const string& next) {
        if (hasDevice(src)) devices[src]->routes[dest] = next;
    }

    void sendPacket(const string& srcName, const string& dstName, const string& payload) {
        if (!hasDevice(srcName) || !hasDevice(dstName)) return;

        auto src = devices[srcName];
        auto dst = devices[dstName];

        if (src->drop > 0 && rand() % 100 < src->drop) {
            cout << "[DROP] from " << srcName << "\n";
            return;
        }

        if (dst->blocked.count(src->ip)) {
            cout << "[BLOCK] " << dstName << " blocked " << srcName << "\n";
            return;
        }

        cout << "[SEND] " << srcName << " -> " << dstName << ": " << payload << "\n";
        dst->packets.push({srcName, payload});
    }

    void receivePacket(const string& name) {
        if (!hasDevice(name) || devices[name]->packets.empty()) return;

        auto p = devices[name]->packets.front();
        devices[name]->packets.pop();
        cout << "[RECV] " << name << " from " << p.first << ": " << p.second << "\n";
    }

    void broadcast(const string& srcName, const string& payload) {
        if (!hasDevice(srcName)) return;
        for (const auto& n : devices[srcName]->neighbors) {
            sendPacket(srcName, n, payload);
        }
    }
};

string cleanToken(string s) {
    while (!s.empty() && (s.back() == ';' || s.back() == ')' || s.back() == '}')) s.pop_back();
    while (!s.empty() && (s.front() == '(' || s.front() == '{')) s.erase(s.begin());
    if (s.size() >= 2 && s.front() == '"' && s.back() == '"') {
        s = s.substr(1, s.size() - 2);
    }
    return s;
}

string evalToken(const string& raw) {
    size_t p = raw.find('(');

    if (raw.find("GoponKoro") != string::npos && p != string::npos) {
        string data = cleanToken(raw.substr(p));
        for (char& ch : data) ch++;
        return "[ENC]" + data;
    }

    if (raw.find("UghatKoro") != string::npos && p != string::npos) {
        string data = cleanToken(raw.substr(p));
        if (data.substr(0, 5) == "[ENC]") {
            data = data.substr(5);
            for (char& ch : data) ch--;
        }
        return data;
    }

    return cleanToken(raw);
}

vector<string> tokenize(const string& src) {
    vector<string> words;
    string current;
    bool inQuotes = false;

    for (char ch : src) {
        if (ch == '"') {
            inQuotes = !inQuotes;
            current += ch;
            if (!inQuotes) {
                words.push_back(current);
                current.clear();
            }
            continue;
        }

        if (isspace(ch) && !inQuotes) {
            if (!current.empty()) {
                words.push_back(current);
                current.clear();
            }
            continue;
        }

        current += ch;
    }

    if (!current.empty()) words.push_back(current);
    return words;
}

vector<string> captureBlock(const vector<string>& words, int& i) {
    vector<string> block;
    int depth = 1;

    while (i < static_cast<int>(words.size()) && depth > 0) {
        if (words[i] == "{") depth++;
        else if (words[i] == "}") depth--;

        if (depth > 0) block.push_back(words[i++]);
        else i++;
    }

    return block;
}

void run(NetCompiler& c, const vector<string>& words, int& i);

void handleCommand(NetCompiler& c, const string& cmd, const vector<string>& words, int& i) {
    if (cmd == "JontraGothon") {
        string type = words[i++];
        string name = cleanToken(words[i++]);
        c.addDevice(type, name);
    } else if (cmd == "JogajogSet") {
        string a = cleanToken(words[i++]);
        string b = cleanToken(words[i++]);
        c.connect(a, b);
    } else if (cmd == "ThikanaDao") {
        string name = cleanToken(words[i++]);
        string ip = cleanToken(words[i++]);
        c.setIP(name, ip);
    } else if (cmd == "DorjaDao") {
        string name = cleanToken(words[i++]);
        int port = stoi(cleanToken(words[i++]));
        c.setPort(name, port);
    } else if (cmd == "PacketPathao") {
        string src = cleanToken(words[i++]);
        string dst = cleanToken(words[i++]);
        string msg = evalToken(words[i++]);
        c.sendPacket(src, dst, msg);
    } else if (cmd == "PacketNey") {
        c.receivePacket(cleanToken(words[i++]));
    } else if (cmd == "ShobaiPathao") {
        string src = cleanToken(words[i++]);
        string msg = evalToken(words[i++]);
        c.broadcast(src, msg);
    } else if (cmd == "PothNirdharon") {
        string src = cleanToken(words[i++]);
        string dst = cleanToken(words[i++]);
        string next = cleanToken(words[i++]);
        c.setRoute(src, dst, next);
    } else if (cmd == "JachaiPing") {
        string src = cleanToken(words[i++]);
        string dst = cleanToken(words[i++]);
        cout << "[PING] " << src << " -> " << dst << " ... Success\n";
    } else if (cmd == "Bilombho") {
        this_thread::sleep_for(chrono::milliseconds(stoi(cleanToken(words[i++]))));
    } else if (cmd == "HariyeFelo") {
        string name = cleanToken(words[i++]);
        int percent = stoi(cleanToken(words[i++]));
        if (c.hasDevice(name)) c.devices[name]->drop = percent;
    } else if (cmd == "GotiNiyontron") {
        string name = cleanToken(words[i++]);
        int rate = stoi(cleanToken(words[i++]));
        c.setRate(name, rate);
    } else if (cmd == "NiyomBoshao") {
        string name = cleanToken(words[i++]);
        string proto = cleanToken(words[i++]);
        c.setProto(name, proto);
    } else if (cmd == "ProtirodhDao") {
        string name = cleanToken(words[i++]);
        string target = cleanToken(words[i++]);
        if (c.hasDevice(name)) c.devices[name]->blocked.insert(target);
    } else if (cmd == "NirikhaKoro") {
        string name = cleanToken(words[i++]);
        if (c.hasDevice(name)) {
            auto d = c.devices[name];
            cout << "[MON] " << name << " IP:" << d->ip << " Proto:" << d->proto << " Queue:" << d->packets.size()
                 << "\n";
        }
    } else if (cmd == "GhotonaLekho") {
        cout << "[LOG] " << cleanToken(words[i++]) << "\n";
    } else if (cmd == "Dekhao") {
        cout << evalToken(words[i++]) << "\n";
    } else if (cmd == "Jodi") {
        bool ok = c.hasDevice(cleanToken(words[i++]));
        i++;  // skip "{"
        vector<string> thenBody = captureBlock(words, i);
        vector<string> elseBody;

        if (i < static_cast<int>(words.size()) && words[i] == "Nahole") {
            i++;  // skip Nahole
            i++;  // skip "{"
            elseBody = captureBlock(words, i);
        }

        int start = 0;
        if (ok) run(c, thenBody, start);
        else if (!elseBody.empty()) run(c, elseBody, start);
    } else if (cmd == "GhuroChol") {
        int repeat = stoi(cleanToken(words[i++]));
        i++;  // skip "{"
        vector<string> body = captureBlock(words, i);

        for (int k = 0; k < repeat; k++) {
            int start = 0;
            run(c, body, start);
        }
    } else if (cmd == "KajGothon") {
        string name = cleanToken(words[i++]);
        i++;  // skip "{"
        c.userFunctions[name] = captureBlock(words, i);
    } else if (c.userFunctions.count(cleanToken(cmd))) {
        int start = 0;
        run(c, c.userFunctions[cleanToken(cmd)], start);

        // Skip optional "(...)" style call argument part if present.
        if (i < static_cast<int>(words.size()) && words[i].find('(') != string::npos) {
            i++;
            while (i < static_cast<int>(words.size()) && words[i++].find(')') == string::npos) {
            }
        }
    }
}

void run(NetCompiler& c, const vector<string>& words, int& i) {
    while (i < static_cast<int>(words.size())) {
        string cmd = words[i++];
        if (cmd == "NetArambho" || cmd == "NetShesh" || cmd == "{" || cmd == "}") {
            continue;
        }
        handleCommand(c, cmd, words, i);
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "Usage: ./nextlang <file.netx>\n";
        return 1;
    }

    ifstream file(argv[1]);
    if (!file.is_open()) {
        cout << "Cannot open file: " << argv[1] << "\n";
        return 1;
    }

    stringstream buffer;
    buffer << file.rdbuf();
    string source = buffer.str();

    vector<string> words = tokenize(source);

    NetCompiler compiler;
    cout << "--- NetXLang Start ---\n";
    int idx = 0;
    run(compiler, words, idx);
    cout << "--- NetXLang End ---\n";
    return 0;
}

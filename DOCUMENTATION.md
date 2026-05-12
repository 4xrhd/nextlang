# NetXLang Full Documentation

Welcome to the official documentation for **NetXLang**, a domain-specific language designed for networking simulation and security modeling using Bengali-inspired syntax.

---

## 1. Language Overview & Philosophy

NetXLang was created to make networking concepts more accessible and intuitive, especially for native Bengali speakers. It bridges the gap between high-level networking theory and practical programming.

### 1.1 Key Characteristics
- **Domain-Specific**: Every keyword in the language maps directly to a networking or security concept (e.g., routing, firewalls, encryption).
- **Imperative & Procedural**: The language follows a step-by-step execution model where you define your network topology first and then simulate traffic.
- **Bengali-Inspired Syntax**: Uses transliterated Bengali words as keywords to provide semantic meaning to the operations.
- **Simulation-Oriented**: Instead of managing actual hardware, it simulates a virtual environment where you can observe packet flow and security breaches.

### 1.2 Syntax Rules
- **Case Sensitivity**: Keywords (like `NetArambho`) are case-sensitive.
- **Statement Termination**: Every standalone statement must end with a semicolon (`;`).
- **Comments**: Single-line comments are supported using `//`.
- **Data Types**:
    - **String**: Enclosed in double quotes (e.g., `"Hello"`).
    - **Number**: Integer values (e.g., `80`, `500`).
    - **IP Address**: Dotted-decimal format (e.g., `192.168.1.1`).
- **Blocks**: Groups of code are enclosed in curly braces `{ }`.

---

## 2. Structure of a NetXLang Program

Every NetXLang script must start and end with the session markers:
- `NetArambho`: Marks the start of the network simulation.
- `NetShesh`: Marks the end of the network simulation.

```netxlang
NetArambho
    // Your code here
NetShesh
```

---

## 2. Function Reference (25 Primitives)

| # | NetXLang Function | Networking Concept | Technical Working |
|---|-------------------|-------------------|-------------------|
| 1 | `NetArambho` | Session Start | Initializes the interpreter and simulation environment. |
| 2 | `NetShesh` | Session End | Safely terminates the simulation and prints final logs. |
| 3 | `JontraGothon` | Device Creation | Allocates a new virtual node (Router, Host, Server) in memory. |
| 4 | `JogajogSet` | Physical Link | Establishes a bidirectional adjacency between two virtual nodes. |
| 5 | `ThikanaDao` | IP Assignment | Assigns a unique IPv4 address to a specific virtual node. |
| 6 | `DorjaDao` | Port Assignment | Assigns a listening network port to a virtual node. |
| 7 | `PacketPathao` | Data Transmission | Routes a packet from source to destination via the link layer. |
| 8 | `PacketNey` | Packet Processing | Pops the first packet from a device's queue and processes it. |
| 9 | `ShobaiPathao` | Broadcast | Floods a packet to all immediate neighbors of the source. |
| 10 | `PothNirdharon` | Static Routing | Adds an entry to the virtual routing table for path optimization. |
| 11 | `JachaiPing` | ICMP Echo | Verifies reachability between two nodes in the topology. |
| 12 | `Bilombho` | Latency Simulation | Blocks execution for N milliseconds to simulate network lag. |
| 13 | `HariyeFelo` | Packet Loss | Sets a percentage-based drop rate on a specific node. |
| 14 | `GotiNiyontron` | QoS / Bandwidth | Implements a simulated bitrate limit on a virtual device. |
| 15 | `NiyomBoshao` | Protocol Selection | Sets the active protocol layer (HTTP, HTTPS, FTP) for a node. |
| 16 | `ProtirodhDao` | Firewall Rule | Blacklists an IP address to block incoming traffic at the node. |
| 17 | `NirikhaKoro` | State Monitoring | Dumps the internal state (IP, Queue, Protocol) of a device. |
| 18 | `GhotonaLekho` | Event Logging | Prints a formatted timestamped log message to the console. |
| 19 | `Dekhao` | Output Stream | Standard output for printing expressions or variable results. |
| 20 | `Jodi` | Conditional (If) | Executes a block if the target device exists or condition is met. |
| 21 | `Nahole` | Conditional (Else) | Executes an alternative block if the `Jodi` condition fails. |
| 22 | `GhuroChol` | Iteration (Loop) | Repeats a sequence of network operations N times. |
| 23 | `KajGothon` | Encapsulation | Defines a reusable procedure (function) for complex tasks. |
| 24 | `GoponKoro` | Encryption | Transforms plaintext using a Caesar-shift based cipher. |
| 25 | `UghatKoro` | Decryption | Reverses the encryption transformation to retrieve plaintext. |

### 2.1 Network Setup

#### `JontraGothon <Type> <Name>;`
Creates a new network device.
- **Example**: `JontraGothon Router R1;`

#### `JogajogSet <Node1> <Node2>;`
Connects two devices physically.
- **Example**: `JogajogSet R1 H1;`

#### `ThikanaDao <Node> <IP>;`
Assigns an IP address to a device.
- **Example**: `ThikanaDao H1 192.168.1.1;`

#### `DorjaDao <Node> <Port>;`
Assigns a listening port to a device.
- **Example**: `DorjaDao S1 80;`

---

### 2.2 Data Transmission

#### `PacketPathao <Src> <Dest> <Data>;`
Sends a data packet from source to destination.
- **Example**: `PacketPathao H1 S1 "Hello Server";`

#### `PacketNey <Node>;`
Receives and processes the next packet in the queue.
- **Example**: `PacketNey S1;`

#### `ShobaiPathao <Src> <Data>;`
Broadcasts a packet to all connected neighbors.
- **Example**: `ShobaiPathao R1 "Broadcast Message";`

#### `PothNirdharon <Src> <Dest> <NextHop>;`
Defines a static route for a packet.
- **Example**: `PothNirdharon H1 S1 R1;`

---

### 2.3 Network Testing & Control

#### `JachaiPing <Src> <Dest>;`
Tests connectivity between two nodes.
- **Example**: `JachaiPing H1 S1;`

#### `Bilombho <ms>;`
Introduces a simulation delay in milliseconds.
- **Example**: `Bilombho 500;`

#### `HariyeFelo <Node> <Percentage>;`
Simulates packet loss on a node.
- **Example**: `HariyeFelo H1 10; // 10% packet loss`

#### `GotiNiyontron <Node> <Rate>;`
Limits the bandwidth/speed of a node.
- **Example**: `GotiNiyontron R1 100; // 100Mbps limit`

---

### 2.4 Security & Monitoring

#### `NiyomBoshao <Node> <Protocol>;`
Sets the active protocol for a device (e.g., HTTP, FTP).
- **Example**: `NiyomBoshao S1 HTTP;`

#### `ProtirodhDao <Node> <IP>;`
Adds a firewall rule to block traffic from a specific IP.
- **Example**: `ProtirodhDao S1 192.168.1.50;`

#### `NirikhaKoro <Node>;`
Displays the current state and stats of a device.
- **Example**: `NirikhaKoro S1;`

#### `GhotonaLekho <Message>;`
Logs a custom event to the console.
- **Example**: `GhotonaLekho "Security breach attempt detected";`

---

### 2.5 Logic & Flow Control

#### `Dekhao <Expr>;`
Prints a message or expression result.
- **Example**: `Dekhao "System Ready";`

#### `Jodi (<Cond>) { ... } Nahole { ... }`
Conditional logic (If-Else).
- **Example**:
```netxlang
Jodi ("1") {
    Dekhao "Condition True";
} Nahole {
    Dekhao "Condition False";
}
```

#### `GhuroChol (<Count>) { ... }`
Looping structure.
- **Example**:
```netxlang
GhuroChol (3) {
    JachaiPing H1 S1;
}
```

#### `KajGothon <Name>() { ... }`
Defines a reusable function.
- **Example**:
```netxlang
KajGothon MyTask() {
    Dekhao "Task Running";
}
MyTask();
```

---

### 2.6 Cryptography (Expressions)

#### `GoponKoro(<Data>)`
Encrypts a string payload.
- **Example**: `PacketPathao H1 S1 GoponKoro("MySecret");`

#### `UghatKoro(<EncryptedData>)`
Decrypts an encrypted payload.
- **Example**: `Dekhao UghatKoro("[ENC]Ufyu");`

---

## 3. Comprehensive Example Script

This script demonstrates a full workflow: Setup, Security, Logic, and Execution.

```netxlang
NetArambho
    // 1. Setup
    JontraGothon Router R1;
    JontraGothon Host C1;
    JontraGothon Host S1;

    JogajogSet C1 R1;
    JogajogSet R1 S1;

    ThikanaDao C1 10.0.0.1;
    ThikanaDao S1 10.0.0.2;

    // 2. Security
    ProtirodhDao S1 192.168.1.1; // Block suspicious IP
    NiyomBoshao S1 HTTPS;

    // 3. Reusable Task
    KajGothon CheckConnection() {
        JachaiPing C1 S1;
    }

    // 4. Execution Logic
    Dekhao "Starting Secure Session...";
    
    GhuroChol (2) {
        CheckConnection();
        PacketPathao C1 S1 GoponKoro("HelloServer");
        PacketNey S1;
        Bilombho 100;
    }

    NirikhaKoro S1;
    GhotonaLekho "Simulation Completed Successfully";
NetShesh
```

## 4. Examples

### 4.1 Security Audit Scenario
Demonstrates firewall rules, encryption, and device configuration.
[security_audit.nxl](examples_code/security_audit.nxl)

### 4.2 Network Broadcast & Loops
Demonstrates automated repetitive tasks and network-wide updates.
[broadcast_and_loops.nxl](examples_code/broadcast_and_loops.nxl)

---

## 5. Compilation & Execution

Use the provided `Makefile` to build:

```bash
# To build
make

# To run a script
./netxlang examples_code/full_features.nxl

# To clean build files
make clean
```

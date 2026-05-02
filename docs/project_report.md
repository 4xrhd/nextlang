# NetXLang Project Report

## Executive Summary
NetXLang is a Network-Oriented Bengali Domain Specific Language (DSL) designed for simulating network topologies, packet routing, and security policies. The project includes a full compiler pipeline written in C++17, encompassing a Lexer, Parser, Semantic Analyzer, and Interpreter.

## Implemented Features

### 1. Compiler Pipeline
- **Lexer**: Tokenizes the Bengali keywords and syntax.
- **Parser**: Builds an Abstract Syntax Tree (AST) based on the grammar.
- **Semantic Analyzer**: Ensures semantic correctness, such as variable definitions and type checking.
- **Interpreter**: Executes the AST to simulate the network environment.

### 2. Language Support
- Fully implemented 25 domain-specific Bengali keywords for network simulation.
- Control flow structures including `Jodi` (if), `Nahole` (else), and `GhuroChol` (fixed-count loop) are functional.

### 3. Network Simulation Capabilities
- **Device Management**: Virtual devices (Routers, Switches, Hosts) can be created using `JontraGothon`.
- **Connectivity**: Nodes can be connected via links (`JogajogSet`), and assigned IP addresses (`ThikanaDao`) and ports (`DorjaDao`).
- **Packet Routing**: Packets can be sent (`PacketPathao`), received (`PacketNey`), broadcasted (`ShobaiPathao`), and static routes can be configured (`PothNirdharon`).

### 4. Security & Quality of Service (QoS)
- **Firewall Simulation**: Specific IPs and ports can be blocked using `ProtirodhDao`.
- **Packet Loss Simulation**: Configurable packet drop percentage using `HariyeFelo`.
- **Traffic Shaping**: Rate limiting (`GotiNiyontron`) and simulated delays (`Bilombho`).

## Testing and Verification
- **Unit Testing**: Comprehensive tests implemented for Lexer, Parser, and Semantic Analyzer.
- **Integration Testing**: Multiple end-to-end example scripts (`.nxl`) validate the system's runtime behavior.
- **Results**: All core pipeline tests and integration tests (`sample1.nxl`, `firewall_test.nxl`, `drop_test.nxl`, `routing_test.nxl`) currently pass.

## Known Limitations & Future Work

### 1. Encryption Integration
While keywords for encryption (`GoponKoro`) and decryption (`UghatKoro`) are implemented, actual AES-256 OpenSSL integration is currently simulated via string labels due to standard library path constraints. In a production environment, linking against OpenSSL would enable real cryptographic operations.

### 2. Expression Evaluation
The current expression evaluator is simplified. Future iterations will support complex arithmetic, logical operations, and robust variable resolution.

### 3. Future Enhancements
- **Visualizer**: Add a graphical interface or output format (like Graphviz DOT) to visualize the generated network topology.
- **Advanced Routing**: Implement dynamic routing protocols (e.g., OSPF, BGP simulations).

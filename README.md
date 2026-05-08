# NetXLang: A Network-Oriented Bengali DSL

NetXLang is a custom domain-specific language (DSL) designed for network simulation and security modeling. It abstracts networking operations like packet transmission, routing, firewall enforcement, encryption, and traffic monitoring into simple, Bengali-inspired function keywords.

## Features
- **25 Unique Primitives**: Mapping directly to networking concepts.
- **Bengali-Inspired Syntax**: Accessible for students.
- **Simple Implementation**: The entire compiler and interpreter are contained in a single `main.cpp` file.
- **Security Simulation**: Built-in encryption (`GoponKoro`) and decryption (`UghatKoro`).

## Language Specification

| Standard Concept | NetXLang Function | Description |
|------------------|-------------------|-------------|
| Start Network | `NetArambho` | Initialize session |
| End Network | `NetShesh` | End session |
| Create Device | `JontraGothon` | Create a node |
| Connect Devices | `JogajogSet` | Link two nodes |
| Assign IP | `ThikanaDao` | Assign IP address |
| Assign Port | `DorjaDao` | Assign port |
| Send Packet | `PacketPathao` | Send data |
| Receive Packet | `PacketNey` | Accept data |
| Broadcast | `ShobaiPathao` | Send to all |
| Routing | `PothNirdharon` | Define path |
| Ping | `JachaiPing` | Test reachability |
| Delay | `Bilombho` | Simulate latency |
| Drop Packet | `HariyeFelo` | Simulate loss |
| Bandwidth Control| `GotiNiyontron` | Set throughput |
| Set Protocol | `NiyomBoshao` | Define protocol |
| Firewall Rule | `ProtirodhDao` | Block target |
| Encrypt | `GoponKoro` | Encrypt data |
| Decrypt | `UghatKoro` | Decrypt data |
| Monitor Traffic | `NirikhaKoro` | Monitor node |
| Log Event | `GhotonaLekho` | Log an event |
| Condition | `Jodi` / `Nahole` | If-Else logic |
| Loop | `GhuroChol` | Repeat actions |
| Function Define | `KajGothon` | Define reusable code |
| Output | `Dekhao` | Print message |

## Building and Running

### Build
```bash
make
```

### Run
```bash
./netxlang examples/full_features.nxl
```

## Project Structure
- `main.cpp`: The complete source code.
- `examples/`: Sample `.nxl` programs.
- `Makefile`: Build instructions.
- `nexxtlang.pdf`: Project proposal and specification.

## Author
**Sabikun Nahar Alina**  
ID: 1016 | Batch: CSE 54  
University of Information Technology and Sciences (UITS)

---

**For more details, see the full [DOCUMENTATION.md](DOCUMENTATION.md).**

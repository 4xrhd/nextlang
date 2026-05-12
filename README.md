# NetXLang Compiler Project

NetXLang is a small Bengali-inspired DSL for basic network simulation.

## Why this project is simple
- Single-file implementation in `main.cpp`
- Simple word-based tokenizer
- Direct command execution (interpreter style)
- Easy-to-read command keywords for networking tasks

## Core language commands

| Concept | NetXLang Command | What it does |
|---|---|---|
| Start program | `NetArambho` | Start simulation |
| End program | `NetShesh` | End simulation |
| Create device | `JontraGothon` | Make a device |
| Connect devices | `JogajogSet` | Link two devices |
| Set IP | `ThikanaDao` | Assign IP |
| Set port | `DorjaDao` | Assign port |
| Send packet | `PacketPathao` | Send message |
| Receive packet | `PacketNey` | Read queued packet |
| Broadcast | `ShobaiPathao` | Send to neighbors |
| Routing | `PothNirdharon` | Store route entry |
| Ping test | `JachaiPing` | Print ping success |
| Delay | `Bilombho` | Wait milliseconds |
| Packet drop | `HariyeFelo` | Set drop rate |
| Rate control | `GotiNiyontron` | Set speed value |
| Protocol | `NiyomBoshao` | Set protocol string |
| Firewall | `ProtirodhDao` | Block an IP |
| Monitor | `NirikhaKoro` | Show node state |
| Log | `GhotonaLekho` | Print log text |
| Print | `Dekhao` | Print expression |
| If/else | `Jodi`, `Nahole` | Conditional block |
| Loop | `GhuroChol` | Repeat a block |
| Function | `KajGothon` | Define reusable block |
| Encrypt | `GoponKoro` | Simple +1 char shift |
| Decrypt | `UghatKoro` | Reverse shift |

## Build and run

```bash
make
./netxlang examples_code/full_features.nxl
```

## Project files
- `main.cpp` - complete tokenizer + interpreter
- `examples_code/` - sample `.nxl` scripts
- `Makefile` - compile commands
- `DOCUMENTATION.md` - full command and syntax guide
- `REPORT.md` - project report

## Author
**Sabikun Nahar Alina**  
ID: 1016 | Batch: CSE 54  
University of Information Technology and Sciences (UITS)

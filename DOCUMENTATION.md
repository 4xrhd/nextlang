# NetXLang Documentation
This document explains NetXLang in simple terms for compiler/interpreter projects.


## 1) What is NetXLang?

NetXLang is a small DSL (domain-specific language) for network simulation.  
It uses Bengali-inspired command names and is implemented in one C++ file (`main.cpp`).

## 2) Program structure

Every script starts with `NetArambho` and ends with `NetShesh`.

```netxlang
NetArambho
    // commands
NetShesh
```

## 3) Basic syntax rules

- Commands are case-sensitive.
- Usually write one command per line.
- End commands with `;` in `.nxl` scripts.
- Strings use double quotes, for example `"Hello"`.
- Blocks use `{` and `}` (for `Jodi`, `Nahole`, `GhuroChol`, `KajGothon`).

## 4) Command reference

| Command | Purpose | Example |
|---|---|---|
| `NetArambho` | Start simulation | `NetArambho` |
| `NetShesh` | End simulation | `NetShesh` |
| `JontraGothon` | Create device | `JontraGothon Router R1;` |
| `JogajogSet` | Connect devices | `JogajogSet R1 H1;` |
| `ThikanaDao` | Set IP | `ThikanaDao H1 10.0.0.1;` |
| `DorjaDao` | Set port | `DorjaDao S1 80;` |
| `PacketPathao` | Send message | `PacketPathao H1 S1 "Hello";` |
| `PacketNey` | Receive next packet | `PacketNey S1;` |
| `ShobaiPathao` | Broadcast | `ShobaiPathao R1 "Notice";` |
| `PothNirdharon` | Save route entry | `PothNirdharon H1 S1 R1;` |
| `JachaiPing` | Connectivity check | `JachaiPing H1 S1;` |
| `Bilombho` | Delay in ms | `Bilombho 500;` |
| `HariyeFelo` | Packet drop percent | `HariyeFelo H1 10;` |
| `GotiNiyontron` | Set rate value | `GotiNiyontron R1 100;` |
| `NiyomBoshao` | Set protocol text | `NiyomBoshao S1 HTTP;` |
| `ProtirodhDao` | Block source IP | `ProtirodhDao S1 10.0.0.1;` |
| `NirikhaKoro` | Print device state | `NirikhaKoro S1;` |
| `GhotonaLekho` | Print log message | `GhotonaLekho "Done";` |
| `Dekhao` | Print expression | `Dekhao "Hello";` |
| `Jodi` / `Nahole` | If / else block | `Jodi (S1) { ... } Nahole { ... }` |
| `GhuroChol` | Loop block | `GhuroChol (3) { ... }` |
| `KajGothon` | Define function-like block | `KajGothon Task() { ... }` |
| `GoponKoro` | Encrypt string (`+1` char shift) | `GoponKoro("abc")` |
| `UghatKoro` | Decrypt `[ENC]...` string | `UghatKoro("[ENC]bcd")` |

## 5) Example script

```netxlang
NetArambho
    JontraGothon Router R1;
    JontraGothon Host C1;
    JontraGothon Host S1;

    JogajogSet C1 R1;
    JogajogSet R1 S1;

    ThikanaDao C1 10.0.0.1;
    ThikanaDao S1 10.0.0.2;

    NiyomBoshao S1 HTTPS;
    ProtirodhDao S1 10.0.0.99;

    KajGothon Check() {
        JachaiPing C1 S1;
    }

    GhuroChol (2) {
        Check();
        PacketPathao C1 S1 GoponKoro("HelloServer");
        PacketNey S1;
    }

    NirikhaKoro S1;
    GhotonaLekho "Simulation complete";
NetShesh
```

## 6) Build and run

```bash
make
./netxlang examples_code/full_features.nxl
make clean
```

## 7) Included sample files

- `examples_code/full_features.nxl`
- `examples_code/security_audit.nxl`
- `examples_code/broadcast_and_loops.nxl`
- `examples_code/logic_test.nxl`
- `examples_code/routing_test.nxl`

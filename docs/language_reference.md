# NetXLang Language Reference

## Keywords (25 required)
- `NetArambho`: Program entry point
- `NetShesh`: Program exit point
- `JontraGothon`: Declare a device (e.g., Router, Switch, Host)
- `JogajogSet`: Connect two devices
- `ThikanaDao`: Assign an IP address to a device
- `DorjaDao`: Assign a port to a device
- `PacketPathao`: Send a packet from source to destination
- `PacketNey`: Receive a packet at a node
- `ShobaiPathao`: Broadcast a packet
- `PothNirdharon`: Set routing next-hop
- `JachaiPing`: Ping destination from source
- `Bilombho`: Simulate delay in ms
- `HariyeFelo`: Set packet drop percentage
- `GotiNiyontron`: Apply rate limiting
- `NiyomBoshao`: Apply a generic rule
- `ProtirodhDao`: Block an IP/Port on a node (Firewall)
- `GoponKoro`: Encrypt payload (AES-256)
- `UghatKoro`: Decrypt payload
- `NirikhaKoro`: Monitor a node
- `GhotonaLekho`: Log an event
- `Jodi`: If condition
- `Nahole`: Else condition
- `GhuroChol`: Fixed-count loop
- `KajGothon`: Define a function
- `Dekhao`: Print expression

## Syntax
- Statements end with `;`
- Blocks are enclosed in `{ }`
- Comments use `//`
- IPs are standard IPv4 strings e.g. `192.168.1.1`
- Strings are enclosed in `"`

## Example
```nxl
NetArambho
  JontraGothon Router R1;
  JontraGothon Host H1;
  JogajogSet R1 H1;
  ThikanaDao H1 192.168.1.2;
  Dekhao "Setup complete";
NetShesh
```

## How to Run

To run a NetXLang program, use the `netxlang.exe` interpreter compiled in the root directory. Pass the path to your `.nxl` file as the first argument.

```powershell
# From the project root
./netxlang.exe path/to/your/file.nxl
```

For example, to run the provided sample:
```powershell
./netxlang.exe examples/sample1.nxl
```

## More Sample Codes

Here are a few more comprehensive examples of what you can do with NetXLang.

### 1. Basic Network Simulation (`sample1.nxl`)
This script sets up a router and two hosts, connects them, assigns IP addresses, and simulates sending a packet and a ping.

```nxl
NetArambho
    // Device setup
    JontraGothon Router R1;
    JontraGothon Host H1;
    JontraGothon Host H2;

    JogajogSet R1 H1;
    JogajogSet R1 H2;

    ThikanaDao H1 192.168.1.2;
    ThikanaDao H2 192.168.1.3;
    ThikanaDao R1 192.168.1.1;

    Dekhao "Network Setup Complete";

    // Communication
    PacketPathao H1 H2 "Hello H2!";
    PacketNey H2;

    // Ping
    JachaiPing H1 H2;

    // Monitoring
    NirikhaKoro R1;

    // Delay
    Bilombho 100;
    GhotonaLekho "Simulation cycle ended";
NetShesh
```

### 2. Static Routing Configuration (`routing_test.nxl`)
This script demonstrates how to define a static route between two routers.

```nxl
NetArambho
    JontraGothon Router R1;
    JontraGothon Router R2;
    PothNirdharon R1 "ExternalNet" R2;
    GhotonaLekho "Static route configured";
NetShesh
```

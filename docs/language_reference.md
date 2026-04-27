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

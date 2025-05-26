# Local Network Chat Application

A console-based chat application that enables real-time communication between multiple users over a local network. Built with C++ using object-oriented programming principles.

## Features

- Real-time messaging between multiple clients
- Server-client architecture
- Multi-threaded message handling
- Console-based user interface
- Message broadcasting system
- Connection management
- Error handling and recovery
- Chat history tracking
- Cross-platform support (Linux/Windows)

## Prerequisites

Before you begin, ensure you have the following installed:

### For Linux/Unix
- G++ compiler (version 7.0 or higher)
- Make build system
- POSIX-compliant operating system
- Git (for version control)

### For Windows
- MinGW or MSYS2 with G++ compiler
- Make for Windows
- Git for Windows
- Windows 7 or higher

## Installation

1. Clone the repository
```bash
git clone https://github.com/Owhab/LocalChat.git
cd LocalChat
```

2. Build the application
```bash
make all
```

This will create two executables:
- On Linux: `server` and `client`
- On Windows: `server.exe` and `client.exe`

## Usage

### Starting the Server

1. Open a terminal/command prompt and navigate to the project directory
2. Run the server:
   - On Linux: `./server`
   - On Windows: `server.exe`
3. The server will start and listen for connections on port 12345

### Starting a Client

1. Open a new terminal/command prompt
2. Run the client:
   - On Linux: `./client`
   - On Windows: `client.exe`
3. When prompted, enter:
   - The server's IP address (e.g., 127.0.0.1 for local testing or the server's network IP for remote connections)
   - Your username

### Chat Commands

- Send message: Simply type your message and press Enter
- Exit chat: Type 'exit' and press Enter
- Clear screen: Type 'clear' and press Enter

## Connecting from Another Device (Cross-Device Setup)

To connect to the chat server from another device (Windows or Ubuntu) on the same network:

### 1. Find the Server's IP Address

On the server machine (Ubuntu):
```bash
ip addr show
```
Look for your network interface (usually `wlan0` for wireless or `eth0`/`enp0s3` for Ethernet) and note the IPv4 address which looks like `192.168.x.x` or `10.x.x.x`.

On the server machine (Windows):
```cmd
ipconfig
```
Look for "IPv4 Address" under your network adapter.

### 2. Configure Firewall

#### On Ubuntu Server
```bash
sudo ufw allow 12345/tcp
sudo ufw status
```
Make sure the status shows that port 12345 is allowed.

#### On Windows Server
1. Open Windows Defender Firewall with Advanced Security
2. Select "Inbound Rules" and click "New Rule..."
3. Select "Port" > Next
4. Select "TCP" and enter "12345" for "Specific local ports" > Next
5. Select "Allow the connection" > Next
6. Select where the rule applies (Domain/Private/Public) > Next
7. Name the rule "LocalChat" and click Finish

### 3. Build the Client on the Other Device

#### Ubuntu Client
1. Clone the repository on the client machine
```bash
git clone https://github.com/Owhab/LocalChat.git
cd LocalChat
make client
```

2. Run the client
```bash
./client
```

3. When prompted:
   - Enter the server IP address you noted earlier
   - Enter your preferred username
   - Start chatting!

#### Windows Client
1. Clone the repository on the client machine
```cmd
git clone https://github.com/Owhab/LocalChat.git
cd LocalChat
```

2. If using MinGW/MSYS2:
```cmd
mingw32-make client
```
   Or if using Visual Studio with nmake:
```cmd
nmake client
```

3. Run the client
```cmd
client.exe
```

4. When prompted:
   - Enter the server IP address you noted earlier
   - Enter your preferred username
   - Start chatting!

### 4. Troubleshooting Connection Issues

If you cannot connect from another device:

1. **Verify Network Connectivity**:
   ```bash
   # On client machine
   ping [server-ip-address]
   ```

2. **Check if Server is Listening**:
   On the server machine:
   ```bash
   # Ubuntu
   sudo netstat -tuln | grep 12345
   
   # Windows
   netstat -an | findstr 12345
   ```
   
3. **Verify Firewall Settings**:
   - Temporarily disable the firewall to test if it's blocking the connection
   - On Ubuntu: `sudo ufw disable` (remember to enable it after testing)
   - On Windows: Turn off Windows Defender Firewall temporarily

4. **Check Router Settings**:
   - If devices are on different subnets, make sure your router allows traffic between them
   - Some routers block certain types of traffic between LAN devices by default

5. **Test with a Simple Connection**:
   On the server:
   ```bash
   # Ubuntu
   nc -l 12345
   
   # Windows (with netcat installed)
   nc -l -p 12345
   ```
   
   On the client:
   ```bash
   # Ubuntu
   nc [server-ip] 12345
   
   # Windows
   nc [server-ip] 12345
   ```
   Type something and see if it appears on the server terminal.

## Network Configuration

### Local Testing
- Server IP: 127.0.0.1
- Port: 12345

### LAN Configuration

#### Linux
1. Find server's IP address:
```bash
ip addr show
```
2. Configure firewall:
```bash
sudo ufw allow 12345/tcp
```

#### Windows
1. Find server's IP address:
```cmd
ipconfig
```
2. Configure Windows Firewall:
   - Open Control Panel > System and Security > Windows Defender Firewall
   - Click "Advanced settings" > "Inbound Rules" > "New Rule..."
   - Select "Port" > TCP > Specific local port: 12345 > Allow the connection
   - Name the rule "LocalChat" and finish the wizard

## Cross-Network Troubleshooting

If you're having trouble connecting between different devices:

1. Ensure both devices are on the same network
2. Verify that the server is using the correct network IP (not 127.0.0.1)
3. Check that port 12345 is open in the firewall on the server device
4. Try disabling firewall temporarily to test the connection
5. Ensure the router is not blocking internal connections

## Project Structure

```
local-chat-app/
├── src/
│   ├── server/
│   │   ├── ChatServer.hpp
│   │   ├── ChatServer.cpp
│   │   └── main_server.cpp
│   ├── client/
│   │   ├── ChatClient.hpp
│   │   ├── ChatClient.cpp
│   │   └── main_client.cpp
│   └── common/
│       └── MessageTypes.hpp
├── docs/
│   ├── technical/
│   └── user-guide/
├── Makefile
└── README.md
```

## Building from Source

### Debug Build
```bash
make debug
```

### Release Build
```bash
make release
```

### Clean Build
```bash
make clean
```

## Troubleshooting

### Common Issues

1. Connection Refused
   - Check if server is running
   - Verify correct IP address
   - Confirm port 12345 is open

2. Build Errors
   - Ensure all dependencies are installed
   - Check compiler version
   - Verify source files are present

3. Runtime Errors
   - Check network connectivity
   - Verify firewall settings
   - Ensure correct permissions

## Development

### Contributing
1. Fork the repository
2. Create your feature branch
3. Commit your changes
4. Push to the branch
5. Create a Pull Request

### Coding Standards
- Use snake_case for variables and functions
- Use PascalCase for class names
- Include documentation for public methods
- Follow the OOP principles

## Testing

Run the tests:
```bash
make test
```

### Test Coverage
- Unit tests for core components
- Integration tests for client-server communication
- Performance tests for concurrent connections

## License

This project is licensed under the MIT License - see the LICENSE file for details

## Authors

- Abdul Owhab <mail.owhab@gmail.com>

## Acknowledgments

- Thanks to the C++ community
- Inspired by modern chat applications
- Built for educational purposes

## Version History

- 0.1.0
  - Initial Release
  - Basic chat functionality
  - Console interface

## Roadmap

- Add GUI interface
- Implement private messaging
- Add file sharing capabilities
- Add user authentication
- Implement message encryption

## Support

For support, email mail.owhab@gmail.com or open an issue in the repository.
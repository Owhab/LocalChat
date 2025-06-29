# LocalChat - Emergency Communication System

A console-based chat application that enables real-time communication between multiple users over a local network. Built with C++ using object-oriented programming principles and designed for emergency situations when internet connectivity is unavailable.

## 🚨 Project Background

This project was inspired by the internet shutdown during Bangladesh's quota reform movement in July-August 2024, when centralized communication systems became unavailable. LocalChat provides a decentralized solution that operates on local area networks without requiring internet connectivity.

## ✨ Features

- **Real-time messaging** between multiple clients on the same network
- **Cross-platform compatibility** (Linux and Windows)
- **Multi-threaded server** supporting concurrent client connections
- **Enhanced console UI** with color-coded messages and beautiful formatting
- **User identification system** with unique usernames
- **Automatic message broadcasting** to all connected clients
- **Graceful connection handling** with join/leave notifications
- **Thread-safe operations** with proper synchronization
- **Emergency communication** capability without internet dependency

## 📁 Project Structure

```
LocalChat/
├── ChatServer.hpp          # Server class declaration
├── ChatServer.cpp          # Server implementation
├── ChatClient.hpp          # Client class declaration  
├── ChatClient.cpp          # Client implementation
├── ConsoleUtils.hpp        # Cross-platform console utilities and formatting
├── main_server.cpp         # Server application entry point
├── main_client.cpp         # Client application entry point
├── Makefile               # Cross-platform build configuration
├── README.md              # Project documentation
├── report.md              # Detailed project report
└── Learning_and_Timeline.md # Development timeline and learning notes
```

## 🛠️ Prerequisites

### Linux (Ubuntu/Debian)
```bash
sudo apt-get update
sudo apt-get install build-essential g++ make git
```

### Windows
- MinGW-w64 or Visual Studio with C++ support
- Git for Windows
- Windows 7 or higher

## 🚀 Installation & Setup

1. **Clone the repository**
```bash
git clone git@github.com:Owhab/LocalChat.git
cd LocalChat
```

2. **Build the applications**
```bash
# Build both server and client
make all

# Or build individually
make server
make client
```

3. **Verify installation**
```bash
# Check executables were created
ls -la server client  # Linux
dir server.exe client.exe  # Windows
```

## 💬 Usage

### Starting the Server

1. Open a terminal and navigate to the project directory
2. Run the server:
```bash
./server        # Linux
server.exe      # Windows
```
3. The server will start on port 12345 and display connection status

### Connecting Clients

1. Open a new terminal for each client
2. Run the client:
```bash
./client        # Linux
client.exe      # Windows
```
3. Enter the server's IP address (127.0.0.1 for local testing)
4. Choose a unique username
5. Start chatting!

### Chat Commands

- **Send message**: Type your message and press Enter
- **Exit**: Type `exit` and press Enter
- **Clear screen**: Type `clear` and press Enter

## 🌐 Network Setup (Cross-Device Communication)

### Find Server IP Address

**Linux:**
```bash
ip addr show
# Look for wlan0 (wireless) or eth0 (ethernet) interface
```

**Windows:**
```cmd
ipconfig
# Look for IPv4 Address under your network adapter
```

### Configure Firewall

**Linux (Ubuntu):**
```bash
sudo ufw allow 12345/tcp
sudo ufw status
```

**Windows:**
1. Open Windows Defender Firewall
2. Create new inbound rule for port 12345 (TCP)
3. Allow the connection

### Connect from Another Device

1. Build LocalChat on the client device
2. Run the client application
3. Enter the server's network IP address (e.g., 192.168.1.100)
4. Choose a username and start chatting

## 🔧 Technical Details

### Architecture
- **Server**: Multi-threaded TCP server handling concurrent connections
- **Client**: Dual-threaded client with separate send/receive operations
- **Protocol**: TCP for reliable message delivery
- **Threading**: C++11 standard threading library with mutex synchronization

### Key Classes
- **ChatServer**: Manages client connections and message broadcasting
- **ChatClient**: Handles server connection and message exchange
- **ConsoleUtils**: Cross-platform console formatting and color support

### Platform Compatibility
- Uses conditional compilation for Windows/Linux socket APIs
- Unified color system with ANSI codes (Linux) and Windows Console API
- Cross-platform threading with std::thread and std::mutex

## 🐛 Troubleshooting

### Connection Issues
```bash
# Test network connectivity
ping <server-ip>

# Check if server is listening
netstat -tuln | grep 12345  # Linux
netstat -an | findstr 12345  # Windows
```

### Build Issues
- Ensure G++ compiler supports C++11 or higher
- Verify all source files are present
- Check make utility is installed

### Runtime Issues
- Verify firewall allows port 12345
- Ensure server is running before connecting clients
- Check network connectivity between devices

## 🔮 Future Enhancements

- [ ] Graphical User Interface (GUI)
- [ ] Private messaging capabilities
- [ ] File sharing functionality
- [ ] Message encryption for security
- [ ] User authentication system
- [ ] Message persistence and history
- [ ] Audio/video communication support

## 📚 Learning Outcomes

This project demonstrates:
- **Network Programming**: Socket programming with TCP/IP
- **Concurrent Programming**: Multi-threading and synchronization
- **Cross-platform Development**: Platform abstraction techniques
- **Object-Oriented Design**: Clean class architecture and encapsulation
- **Emergency Communication**: Practical solution for connectivity crises

## 👨‍💻 Author

**Abdul Owhab**
- Email: mail.owhab@gmail.com
- Course: SDP-1 (Software Development Project - 1)

## 📄 License

This project is licensed under the MIT License - see the LICENSE file for details.

## 🙏 Acknowledgments

- Inspired by the need for resilient communication during the 2024 Bangladesh internet shutdown
- Built for educational purposes and emergency preparedness
- Thanks to the C++ community for excellent documentation and resources

---

**Note**: This project serves both as a functional emergency communication tool and an educational resource for understanding distributed systems and network programming concepts.
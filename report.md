# **LocalChat: Emergency Communication System for Network Outages**
## **Project Report**

---

## **Chapter 1: INTRODUCTION**

### **1.1. Problem Specification**

During the student-led quota reform movement in Bangladesh in July-August 2024, the government imposed a nationwide internet shutdown that lasted several days, severely disrupting communication channels. Educational institutions, businesses, families, and communities were left without reliable means of communication. Students couldn't coordinate with their universities, businesses couldn't operate effectively, and people lost contact with their loved ones.

This incident highlighted a critical gap in our communication infrastructure - the over-dependence on centralized internet services. When the central authority cuts off internet access, entire populations become isolated. Traditional communication methods like phone calls were also restricted, leaving people with no viable alternatives for coordination and communication.

The problem becomes particularly acute in educational settings where students need to coordinate activities, share information, and maintain contact during emergencies. There was an urgent need for a decentralized communication solution that could operate independently of internet connectivity while utilizing existing local network infrastructure.

### **1.2. Objectives**

**Primary Objectives:**
- Develop a console-based chat application that operates on local area networks without internet dependency
- Implement a robust client-server architecture supporting multiple concurrent users
- Create a cross-platform solution compatible with both Linux and Windows operating systems
- Ensure reliable real-time message delivery and broadcasting within the local network
- Provide an intuitive command-line interface with enhanced visual feedback and user-friendly interaction

**Secondary Objectives:**
- Demonstrate practical application of network programming concepts learned in SDP-1 course
- Implement thread-safe concurrent programming techniques for handling multiple clients
- Create a scalable architecture that can handle growing numbers of users
- Develop comprehensive error handling mechanisms for network failures and unexpected disconnections
- Document the project comprehensively for educational and practical reference

### **1.3. Scope**

**Project Scope Includes:**
- Real-time text messaging between multiple clients on the same local network
- Server application capable of handling concurrent client connections using multi-threading
- Client application with dual-threaded send/receive message capabilities
- Cross-platform compatibility (Linux/Windows) with unified codebase and conditional compilation
- Enhanced console-based user interface with color-coded messages and beautiful formatting
- User identification system with username-based messaging and unique color assignment
- Connection management with graceful handling of joins and disconnections
- Message broadcasting system for distributing messages to all connected clients
- Cross-platform console utilities for enhanced user experience

**Project Scope Excludes:**
- Graphical user interface (GUI) implementation
- File sharing capabilities
- Message encryption and security features
- User authentication and access control
- Message persistence and database storage
- Voice or video communication features
- Internet-based communication or routing

### **1.4. Organization Of Project Report**

**Chapter 1 - Introduction:** Provides the project background, problem statement, objectives, and scope definition, establishing the foundation and motivation for the LocalChat system.

**Chapter 2 - Background:** Analyzes existing communication systems during emergencies, discusses their limitations, and presents the theoretical foundation including network programming concepts, socket programming, and multi-threading principles.

**Chapter 3 - System Analysis & Design:** Details the technology stack, development model, system architecture, and various design diagrams including use case diagrams, data flow diagrams, and system flowcharts that guide the implementation.

**Chapter 4 - Implementation:** Describes the actual development process, including server and client implementation, enhanced console interface design, core functionalities, and the modular structure of the application.

**Chapter 5 - User Manual:** Provides comprehensive instructions for system installation, configuration, and usage, including hardware/software requirements, step-by-step setup procedures, and troubleshooting guidelines.

---

## **Chapter 2: BACKGROUND**

### **2.1. Existing System Analysis**

**Traditional Communication Systems During Emergencies:**

**1. Cellular Networks:**
- *Pros:* Wide coverage, portable, voice and text capabilities
- *Cons:* Centralized infrastructure vulnerable to shutdowns, dependent on cell towers, can be overloaded during emergencies

**2. Internet-based Messaging (WhatsApp, Telegram, Facebook Messenger):**
- *Pros:* Feature-rich, multimedia support, group communication
- *Cons:* Completely dependent on internet connectivity, centralized servers, vulnerable to government restrictions

**3. Amateur Radio Networks:**
- *Pros:* Independent of infrastructure, long-range communication
- *Cons:* Requires special equipment and licenses, limited to audio communication, complex setup

**4. Mesh Networking Solutions (FireChat, Bridgefy):**
- *Pros:* Decentralized, can work without internet
- *Cons:* Limited range, requires specific mobile apps, dependent on device density

**5. Local Area Network Solutions:**
- *Pros:* High-speed communication within buildings/campuses, independent of external infrastructure
- *Cons:* Limited geographical scope, requires existing LAN infrastructure

**Analysis:** Most existing systems fail during centralized shutdowns. Our LocalChat system addresses this gap by utilizing existing LAN infrastructure while remaining independent of internet connectivity.

### **2.2. Supporting Literatures**

**Network Programming Foundations:**
The project is built upon fundamental network programming concepts including the Berkeley Socket API, which provides a standardized interface for network communication across different operating systems. The TCP/IP protocol suite ensures reliable, ordered delivery of messages between clients and servers.

**Multi-threading and Concurrency:**
Modern C++ threading capabilities (std::thread, std::mutex) are utilized to handle concurrent client connections. The thread-per-client model ensures that each user's communication is handled independently, preventing blocking operations from affecting other users.

**Socket Programming Principles:**
- **Server Sockets:** Implement binding, listening, and accepting connections
- **Client Sockets:** Handle connection establishment and data transmission
- **Error Handling:** Robust error detection and recovery mechanisms

**Cross-platform Development:**
Platform abstraction techniques allow the same codebase to run on different operating systems by using conditional compilation and platform-specific API wrappers for both socket operations and console formatting.

**Object-Oriented Design:**
The project employs OOP principles including encapsulation (ChatServer and ChatClient classes), abstraction (platform-specific socket handling), and modularity (separation of server, client, and utility components).

**Choice of Technologies:**
- **C++:** Chosen for its performance, low-level network access, and cross-platform capabilities
- **TCP Protocol:** Selected for reliable message delivery over UDP's speed advantage
- **Enhanced Console Interface:** Provides rich visual experience while maintaining universal compatibility
- **Standard Threading Library:** Ensures portability and modern C++ compliance

---

## **Chapter 3: SYSTEM ANALYSIS & DESIGN**

### **3.1. Technology & Tools**

**Programming Language:** C++ (C++11 standard)
- Chosen for performance, low-level system access, and cross-platform support
- Modern C++ features including threading library, mutex synchronization, and STL containers

**Development Environment:**
- **Primary OS:** Linux (Ubuntu/Debian)
- **Secondary OS:** Windows (compatibility testing)
- **Compiler:** GCC (GNU Compiler Collection) version 7.0+
- **Build System:** GNU Make with cross-platform Makefile supporting conditional compilation
- **Version Control:** Git for source code management

**Networking Libraries:**
- **Linux:** POSIX sockets (sys/socket.h, netinet/in.h, arpa/inet.h, unistd.h)
- **Windows:** Winsock2 API (winsock2.h, ws2tcpip.h)
- **Protocol:** TCP/IP for reliable communication

**Threading Support:**
- **Standard Library:** std::thread, std::mutex for concurrent programming
- **Synchronization:** Mutex locks for thread-safe operations on shared resources

**Console Enhancement:**
- **Linux:** ANSI escape codes for colors and formatting
- **Windows:** Windows Console API with virtual terminal processing
- **Cross-platform:** Unified interface through ConsoleUtils.hpp

### **3.2. System Architecture & Design**

#### **3.2.1. Development Model (Agile)**

The project follows an **Agile development model** with iterative development cycles:

**Sprint 1:** Basic socket programming and connection establishment
**Sprint 2:** Multi-client support and threading implementation  
**Sprint 3:** Message broadcasting and user management
**Sprint 4:** Cross-platform compatibility and error handling
**Sprint 5:** Enhanced console interface and visual improvements
**Sprint 6:** Documentation and testing

#### **3.2.2. File Structure & Architecture**

```
LocalChat Project Architecture:

┌─────────────────────────────────────────────────────────┐
│                    APPLICATION LAYER                    │
├─────────────────────────────────────────────────────────┤
│  main_server.cpp        │        main_client.cpp       │
│  (Server Entry Point)   │       (Client Entry Point)   │
└─────────────────────────┼─────────────────────────────────┘
                          │
┌─────────────────────────────────────────────────────────┐
│                    BUSINESS LOGIC LAYER                 │
├─────────────────────────────────────────────────────────┤
│  ChatServer.hpp/cpp     │      ChatClient.hpp/cpp      │
│  - Connection Mgmt      │      - Server Connection     │
│  - Message Broadcasting │      - Message Send/Receive  │
│  - Multi-threading      │      - Dual Threading        │
└─────────────────────────┼─────────────────────────────────┘
                          │
┌─────────────────────────────────────────────────────────┐
│                    UTILITY LAYER                        │
├─────────────────────────────────────────────────────────┤
│                ConsoleUtils.hpp                         │
│  - Cross-platform Color Support                        │
│  - Message Formatting Functions                        │
│  - User Color Assignment                                │
│  - Border and Box Drawing                               │
└─────────────────────────────────────────────────────────┘
                          │
┌─────────────────────────────────────────────────────────┐
│                    SYSTEM LAYER                         │
├─────────────────────────────────────────────────────────┤
│  Platform-Specific APIs:                               │
│  Linux: POSIX Sockets + ANSI Colors                    │
│  Windows: Winsock2 + Console API                       │
└─────────────────────────────────────────────────────────┘
```

#### **3.2.3. Core Components**

**1. ChatServer Class:**
- Manages server socket creation and binding to port 12345
- Accepts incoming client connections
- Creates dedicated threads for each client
- Broadcasts messages to all connected clients
- Thread-safe client list management with mutex protection

**2. ChatClient Class:**
- Handles connection to server
- Implements dual-threading for send/receive operations
- Manages user input and message formatting
- Provides graceful disconnection handling

**3. ConsoleUtils Module:**
- Cross-platform console color and formatting support
- Enhanced message formatting with borders and colors
- User-specific color assignment system
- Beautiful UI elements for better user experience

#### **3.2.4. Data Flow Architecture**

```
Message Flow in LocalChat System:

Client A                    Server                    Client B
   │                          │                         │
   │ 1. Send Message           │                         │
   ├──────────────────────────▶│                         │
   │                          │ 2. Receive & Parse      │
   │                          │    Message              │
   │                          │                         │
   │                          │ 3. Format Message       │
   │                          │    with Username        │
   │                          │                         │
   │                          │ 4. Broadcast to All     │
   │                          │    Connected Clients    │
   │                          ├─────────────────────────▶│
   │                          │                         │
   │ 5. Display Message       │                         │ 6. Display Message
   │    (if echo enabled)     │                         │    with Color Coding
   │                          │                         │
```

#### **3.2.5. Threading Model**

```
Server Threading Architecture:

Main Thread                     Client Threads
     │                               │
     ▼                               │
┌─────────────┐                     │
│ Initialize  │                     │
│ Server      │                     │
│ Socket      │                     │
└─────┬───────┘                     │
      │                             │
      ▼                             │
┌─────────────┐                     │
│ Listen for  │                     │
│ Connections │                     │
└─────┬───────┘                     │
      │                             │
      ▼                             │
┌─────────────┐    Create Thread    │
│ Accept New  │──────────────────▶  │
│ Client      │                     │
└─────┬───────┘                     │
      │                             ▼
      │                    ┌─────────────────┐
      │                    │ Handle Client   │
      │                    │ Messages        │
      │                    │                 │
      │                    │ - Receive Msgs  │
      │                    │ - Broadcast     │
      │                    │ - Error Handle  │
      │                    └─────────────────┘
      │
      └──── Loop Back to Accept
```

---

## **Chapter 4: IMPLEMENTATION**

### **4.1. Enhanced Console Interface Design**

**Design Philosophy:**
The LocalChat system features a sophisticated console-based interface that maximizes visual appeal within terminal constraints. The interface utilizes advanced ANSI color codes, Unicode box-drawing characters, and dynamic color assignment to create an engaging user experience.

**Key Interface Features:**

**1. Dynamic User Color Assignment:**
- Each user gets a unique color from a palette of 30 distinct colors
- Colors are assigned automatically and persistently for the session
- Utilizes 256-color ANSI codes for rich visual diversity

**2. Message Formatting:**
- Bordered message boxes with user-specific colors
- System messages in distinctive yellow formatting
- Join/leave notifications with special green/red styling
- Clear visual separation between different message types

**3. Cross-Platform Compatibility:**
- ANSI escape sequences for Linux/macOS
- Windows Console API integration with virtual terminal processing
- Graceful fallback for terminals that don't support colors

### **4.2. Core Implementation Details**

**Server Implementation (ChatServer.cpp):**

**Socket Management:**
- Creates TCP server socket using platform-specific APIs
- Binds to port 12345 with error handling for port conflicts
- Listens for incoming connections with configurable backlog
- Accepts connections and maintains client socket vector

**Multi-Threading Architecture:**
- Main thread handles connection acceptance
- Spawns dedicated thread for each client using std::thread
- Thread-safe operations with std::mutex for shared resources
- Automatic thread cleanup on client disconnection

**Message Broadcasting System:**
- Receives messages from individual client threads
- Parses username and message content
- Formats messages with timestamps and user identification
- Broadcasts to all connected clients except sender

**Client Implementation (ChatClient.cpp):**

**Dual-Threading Model:**
- Main thread handles user input and message sending
- Receive thread continuously listens for incoming messages
- Non-blocking operation ensures responsive user interface
- Proper thread synchronization and cleanup

**Connection Management:**
- Establishes TCP connection to server with error handling
- Sends username as identification message
- Handles network errors and connection failures
- Graceful disconnection with resource cleanup

### **4.3. Key Modules & Features**

**1. ChatServer Module:**
```cpp
Key Methods:
- ChatServer(int port): Constructor with port configuration
- void start(): Begins server operation and connection listening
- void handleClient(socket_t): Manages individual client communication
- void broadcastMessage(): Distributes messages to all clients
- void stop(): Graceful server shutdown
```

**2. ChatClient Module:**
```cpp
Key Methods:
- ChatClient(): Constructor with socket initialization
- bool connect(serverIP, port): Establishes server connection
- void sendMessage(message): Sends user messages to server
- void receiveMessages(): Continuous message reception thread
- void disconnect(): Clean disconnection and resource cleanup
```

**3. ConsoleUtils Module:**
```cpp
Key Features:
- Cross-platform color support with ANSI/Windows API
- getUserColor(): Assigns unique colors to users
- formatSystemMessage(): Special formatting for system notifications
- formatUserJoin/Leave(): Styled join/leave announcements
- createBorderedMessage(): Beautiful message box creation
```

**4. Build System (Makefile):**
- Automatic platform detection (Windows_NT vs. Unix)
- Conditional compilation flags for cross-platform support
- Separate build targets for server and client
- Clean build and debugging support

### **4.4. Advanced Features Implemented**

**1. Enhanced User Experience:**
- Real-time message delivery with minimal latency
- Color-coded user identification system
- Beautiful console formatting with Unicode characters
- Clear status messages and error notifications

**2. Robust Error Handling:**
- Network connection error detection and reporting
- Graceful handling of client disconnections
- Resource cleanup and memory management
- Thread-safe operations with proper synchronization

**3. Cross-Platform Compatibility:**
- Unified codebase for Windows and Linux
- Platform-specific socket API abstraction
- Consistent color and formatting across platforms
- Conditional compilation for optimal performance

**4. Scalable Architecture:**
- Thread-per-client model supporting multiple concurrent users
- Efficient message broadcasting algorithm
- Modular design for easy feature expansion
- Clean separation of concerns between components

---

## **Chapter 5: USER MANUAL**

### **5.1. System Requirements**

#### **5.1.1. Hardware Requirements**

**Minimum Configuration:**
- **Processor:** 1.0 GHz or higher
- **RAM:** 512 MB minimum
- **Storage:** 50 MB free disk space
- **Network:** Ethernet or Wi-Fi adapter for LAN connectivity

**Recommended Configuration:**
- **Processor:** 2.0 GHz multi-core processor
- **RAM:** 2 GB or more
- **Storage:** 100 MB free disk space
- **Network:** Gigabit Ethernet for optimal performance

#### **5.1.2. Software Requirements**

**Linux (Ubuntu/Debian/CentOS):**
```bash
# Required packages
sudo apt-get install build-essential g++ make git

# Verify installation
g++ --version
make --version
```

**Windows:**
- Windows 7 or newer (Windows 10/11 recommended)
- MinGW-w64 or Visual Studio with C++ support
- Git for Windows
- Command Prompt or PowerShell

### **5.2. Installation Guide**

#### **5.2.1. Quick Start Installation**

**Step 1: Download Source Code**
```bash
git clone git@github.com:Owhab/LocalChat.git
cd LocalChat
```

**Step 2: Build Applications**
```bash
# Build everything
make all

# Verify build success
ls -la server client  # Linux
dir server.exe client.exe  # Windows
```

**Step 3: Test Local Connection**
```bash
# Terminal 1: Start server
./server

# Terminal 2: Start client
./client
# Enter: 127.0.0.1 (server IP)
# Enter: YourUsername
```

### **5.3. Usage Instructions**

#### **5.3.1. Server Operation**

**Starting the Server:**
1. Open terminal and navigate to LocalChat directory
2. Execute server application:
   ```bash
   ./server        # Linux
   server.exe      # Windows
   ```
3. Server will display startup message and begin listening on port 12345
4. Monitor connection logs and user activity
5. Press Enter to stop server gracefully

**Server Interface Example:**
```
===== Local Chat Server =====
[SYSTEM] Server starting on port 12345
[SYSTEM] Server started. Waiting for connections...
[SYSTEM] New client connected from 192.168.1.101
[Alice joined the chat]
[Alice]: Hello everyone!
[Bob joined the chat]
[Bob]: Hi Alice! How's everyone doing?
```

#### **5.3.2. Client Operation**

**Connecting to Server:**
1. Open new terminal for each client
2. Execute client application:
   ```bash
   ./client        # Linux
   client.exe      # Windows
   ```
3. Enter server IP address:
   - Local testing: `127.0.0.1`
   - Network: Server's IP (e.g., `192.168.1.100`)
4. Choose unique username
5. Begin chatting immediately

**Client Interface Example:**
```
===== Local Chat Client =====
Enter server IP (default 127.0.0.1): 192.168.1.100
Enter your username: Alice
Connecting to 192.168.1.100...
[SYSTEM] Connected to server successfully
===== Connected to Chat Server =====
Type 'exit' to quit or 'clear' to clear screen

┌──────────────────────────────────────────┐
│  🎉 Bob joined the chat!                │
└──────────────────────────────────────────┘

┌─────────────────────────────────────────────┐
│ Bob: Hello everyone! How's it going?       │
└─────────────────────────────────────────────┘

Hello from Alice!

┌─────────────────────────────────────────────┐
│ You: Hello from Alice!                      │
└─────────────────────────────────────────────┘
```

### **5.4. Network Configuration**

#### **5.4.1. Cross-Device Setup**

**Finding Server IP Address:**

**Linux:**
```bash
# Show all network interfaces
ip addr show

# Show specific interface
ip addr show wlan0  # For wireless
ip addr show eth0   # For ethernet
```

**Windows:**
```cmd
# Show IP configuration
ipconfig

# Show detailed configuration
ipconfig /all
```

**Firewall Configuration:**

**Linux (Ubuntu):**
```bash
# Allow LocalChat through firewall
sudo ufw allow 12345/tcp

# Check firewall status
sudo ufw status

# Enable firewall if disabled
sudo ufw enable
```

**Windows:**
1. Open Windows Defender Firewall with Advanced Security
2. Select "Inbound Rules" → "New Rule"
3. Choose "Port" → "TCP" → "Specific local ports: 12345"
4. Select "Allow the connection"
5. Apply to appropriate network profiles
6. Name rule "LocalChat Server"

#### **5.4.2. Troubleshooting Guide**

**Connection Issues:**

**1. Server Cannot Start:**
```bash
# Check if port is already in use
netstat -tuln | grep 12345  # Linux
netstat -an | findstr 12345  # Windows

# Kill process using port 12345
sudo lsof -ti:12345 | xargs kill -9  # Linux
```

**2. Client Cannot Connect:**
```bash
# Test network connectivity
ping <server-ip>

# Test port accessibility
telnet <server-ip> 12345

# Check firewall settings
sudo ufw status  # Linux
```

**3. Build Errors:**
```bash
# Check compiler version
g++ --version

# Ensure C++11 support
g++ -std=c++11 --version

# Clean and rebuild
make clean
make all
```

### **5.5. Advanced Usage**

#### **5.5.1. Multiple Network Testing**

**Scenario 1: Campus Network**
- Server on student laptop connected to university Wi-Fi
- Clients from dormitory rooms on same network
- IP range typically: 192.168.x.x or 10.x.x.x

**Scenario 2: Home Network**
- Server on desktop computer
- Clients from mobile devices with terminal apps
- Router assigns IPs in 192.168.1.x range

**Scenario 3: Emergency Hotspot**
- One device creates Wi-Fi hotspot
- Server runs on hotspot device
- Other devices connect to hotspot and run clients

#### **5.5.2. Performance Optimization**

**For High User Count:**
- Increase system file descriptor limits
- Monitor server memory usage
- Consider client connection limits based on hardware

**Network Optimization:**
- Use wired connections for server when possible
- Minimize network congestion during peak usage
- Monitor bandwidth usage for large groups

---

## **Conclusion**

The LocalChat Emergency Communication System successfully demonstrates a practical solution for maintaining communication during internet outages and connectivity crises. Through its implementation, the project achieves several key objectives:

**Technical Achievements:**
- **Robust Network Programming:** Successful implementation of TCP socket programming with cross-platform compatibility
- **Concurrent Programming:** Effective multi-threading with proper synchronization using modern C++ features
- **Enhanced User Experience:** Beautiful console interface with color-coding and advanced formatting
- **Cross-Platform Compatibility:** Unified codebase supporting both Linux and Windows environments

**Practical Impact:**
- **Emergency Preparedness:** Provides a ready-to-deploy solution for communication during internet shutdowns
- **Educational Value:** Demonstrates fundamental concepts in distributed systems and network programming
- **Real-World Application:** Addresses actual communication challenges faced during the 2024 Bangladesh crisis

**Project Success Factors:**
- **Modular Architecture:** Clean separation between server, client, and utility components
- **Scalable Design:** Thread-per-client model supporting multiple concurrent users
- **Comprehensive Documentation:** Detailed user manual and technical documentation
- **Thorough Testing:** Cross-platform validation and multi-client testing

**Future Development Opportunities:**
The project provides a solid foundation for advanced features including GUI development, message encryption, file sharing capabilities, and mobile app integration. The modular design facilitates easy extension and enhancement.

**Learning Outcomes:**
This project successfully integrates theoretical knowledge from computer networking, operating systems, and software engineering courses into a practical application. It demonstrates proficiency in C++ programming, network programming concepts, multi-threading, and cross-platform development.

The LocalChat system stands as both a functional emergency communication tool and a comprehensive demonstration of modern software development practices, proving that effective solutions can emerge from real-world challenges and academic learning combined.

---

**Project Information:**
- **Title:** LocalChat - Emergency Communication System  
- **Developer:** Abdul Owhab  
- **Course:** SDP-1 (Software Development Project - 1)  
- **Institution:** [University Name]  
- **Date:** June 2025  
- **Project Duration:** 6 weeks  
- **Programming Language:** C++ (C++11 Standard)  
- **Platform Support:** Linux and Windows  

**Contact Information:**
- **Email:** mail.owhab@gmail.com
- **GitHub:** [Repository URL]
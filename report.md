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
- Provide an intuitive command-line interface with visual feedback and user-friendly interaction

**Secondary Objectives:**
- Demonstrate practical application of network programming concepts learned in SDP-1 course
- Implement thread-safe concurrent programming techniques for handling multiple clients
- Create a scalable architecture that can handle growing numbers of users
- Develop error handling mechanisms for network failures and unexpected disconnections
- Document the project comprehensively for educational and practical reference

### **1.3. Scope**

**Project Scope Includes:**
- Real-time text messaging between multiple clients on the same local network
- Server application capable of handling concurrent client connections
- Client application with send/receive message capabilities
- Cross-platform compatibility (Linux/Windows) with unified codebase
- Console-based user interface with color-coded messages for better readability
- User identification system with username-based messaging
- Connection management with graceful handling of joins and disconnections
- Message broadcasting system for distributing messages to all connected clients

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

**Chapter 4 - Implementation:** Describes the actual development process, including server and client implementation, user interface design, core functionalities, and the modular structure of the application.

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
Platform abstraction techniques allow the same codebase to run on different operating systems by using conditional compilation and platform-specific API wrappers.

**Object-Oriented Design:**
The project employs OOP principles including encapsulation (ChatServer and ChatClient classes), abstraction (platform-specific socket handling), and modularity (separation of server, client, and utility components).

**Choice of Technologies:**
- **C++:** Chosen for its performance, low-level network access, and cross-platform capabilities
- **TCP Protocol:** Selected for reliable message delivery over UDP's speed advantage
- **Console Interface:** Provides simplicity and universal compatibility across systems
- **Standard Threading Library:** Ensures portability and modern C++ compliance

---

## **Chapter 3: SYSTEM ANALYSIS & DESIGN**

### **3.1. Technology & Tools**

**Programming Language:** C++ (C++11 standard)
- Chosen for performance, low-level system access, and cross-platform support
- Modern C++ features including smart pointers, lambda expressions, and threading library

**Development Environment:**
- **Primary OS:** Ubuntu Linux (development and testing)
- **Secondary OS:** Windows (compatibility testing)
- **Compiler:** GCC (GNU Compiler Collection) version 7.0+
- **Build System:** GNU Make with cross-platform Makefile
- **Version Control:** Git for source code management

**Networking Libraries:**
- **Linux:** POSIX sockets (sys/socket.h, netinet/in.h, arpa/inet.h)
- **Windows:** Winsock2 API (winsock2.h, ws2tcpip.h)
- **Protocol:** TCP/IP for reliable communication

**Threading Support:**
- **Standard Library:** std::thread, std::mutex for concurrent programming
- **Synchronization:** Mutex locks for thread-safe operations

**Development Tools:**
- **Text Editor:** VS Code with C++ extensions
- **Debugger:** GDB (GNU Debugger)
- **Network Analysis:** netstat, tcpdump for network monitoring
- **Testing:** Manual testing with multiple client instances

### **3.2. Model & Diagram**

#### **3.2.1. Model (Agile Development)**

The project follows an **Agile development model** with iterative development cycles:

**Sprint 1:** Basic socket programming and connection establishment
**Sprint 2:** Multi-client support and threading implementation
**Sprint 3:** Message broadcasting and user management
**Sprint 4:** Cross-platform compatibility and error handling
**Sprint 5:** User interface improvement and documentation

**Benefits of Agile Model:**
- Rapid prototyping and early testing
- Incremental feature addition
- Flexible response to changing requirements
- Continuous integration and testing

#### **3.2.2. System Architecture**

```
┌─────────────────────────────────────────────────────────┐
│                    LOCAL NETWORK                        │
│                                                         │
│  ┌─────────────┐         ┌─────────────────┐           │
│  │   Client 1  │◄────────┤                 │           │
│  │ (ChatClient)│         │   Chat Server   │           │
│  └─────────────┘         │  (ChatServer)   │           │
│                          │                 │           │
│  ┌─────────────┐         │  - Port 12345   │           │
│  │   Client 2  │◄────────┤  - Multi-thread │           │
│  │ (ChatClient)│         │  - Broadcasting │           │
│  └─────────────┘         │                 │           │
│                          │                 │           │
│  ┌─────────────┐         │                 │           │
│  │   Client N  │◄────────┤                 │           │
│  │ (ChatClient)│         └─────────────────┘           │
│  └─────────────┘                                       │
│                                                         │
└─────────────────────────────────────────────────────────┘
```

#### **3.2.3. Use Case Diagram**

```
                    LocalChat System Use Cases

    User                                    Server Admin
      │                                          │
      │                                          │
  ┌───▼───┐     ┌─────────────────────┐     ┌───▼───┐
  │Connect│     │                     │     │ Start │
  │to     │────▶│   LocalChat System  │◄────│Server │
  │Server │     │                     │     │       │
  └───────┘     │                     │     └───────┘
      │         │                     │          │
  ┌───▼───┐     │                     │     ┌───▼───┐
  │Send   │────▶│                     │◄────│ Stop  │
  │Message│     │                     │     │Server │
  └───────┘     │                     │     └───────┘
      │         │                     │          │
  ┌───▼───┐     │                     │     ┌───▼───┐
  │Receive│◄────│                     │◄────│Monitor│
  │Message│     │                     │     │Clients│
  └───────┘     │                     │     └───────┘
      │         │                     │
  ┌───▼───┐     │                     │
  │Leave  │────▶│                     │
  │Chat   │     │                     │
  └───────┘     └─────────────────────┘
```

#### **3.2.4. Context Level Diagram**

```
                     Context Diagram (DFD-0)
                         LocalChat System

┌─────────────┐                                 ┌─────────────┐
│             │        Connection Request       │             │
│    User     │────────────────────────────────▶│             │
│             │                                 │             │
│             │◄────────────────────────────────│  LocalChat  │
│             │        Message Display          │   System    │
│             │                                 │             │
│             │────────────────────────────────▶│             │
│             │        User Messages            │             │
└─────────────┘                                 └─────────────┘
                                                      │
                                                      │
                                              ┌───────▼───────┐
                                              │               │
                                              │  Network      │
                                              │  Infrastructure│
                                              │               │
                                              └───────────────┘
```

#### **3.2.5. Data Flow Diagram**

```
                    Data Flow Diagram (Level 1)
                       LocalChat System

┌─────────────┐                                 ┌─────────────┐
│             │    1. Username + Message        │             │
│    User     │────────────────────────────────▶│   Process   │
│             │                                 │   Message   │
│             │◄────────────────────────────────│             │
│             │    5. Formatted Message         └──────┬──────┘
└─────────────┘                                        │
                                                       │
                                                2. Raw Message
                                                       │
                                                       ▼
                                              ┌─────────────┐
                                              │             │
                                              │   Store     │
                                              │   Message   │
                                              │             │
                                              └──────┬──────┘
                                                     │
                                               3. Message Data
                                                     │
                                                     ▼
┌─────────────┐                             ┌─────────────┐
│             │◄────────────────────────────│             │
│   Other     │    4. Broadcast Message     │  Broadcast  │
│   Users     │                             │   Message   │
│             │                             │             │
└─────────────┘                             └─────────────┘
```

#### **3.2.6. Database Schema**

**Note:** This project uses in-memory storage rather than persistent database storage. The data structures used are:

```
In-Memory Data Storage:

1. Client Information:
   ┌─────────────────────────────────┐
   │          ClientInfo             │
   ├─────────────────────────────────┤
   │ socket_t socket                 │
   │ std::string username            │
   └─────────────────────────────────┘

2. Chat History:
   ┌─────────────────────────────────┐
   │         ChatHistory             │
   ├─────────────────────────────────┤
   │ std::vector<std::string>        │
   │ chatHistory                     │
   └─────────────────────────────────┘

3. Active Connections:
   ┌─────────────────────────────────┐
   │       ActiveConnections         │
   ├─────────────────────────────────┤
   │ std::vector<socket_t>           │
   │ clientSockets                   │
   │ std::map<socket_t, string>      │
   │ clientUsernames                 │
   └─────────────────────────────────┘
```

#### **3.2.7. Algorithms/Flowchart**

**Server Main Algorithm:**
```
START Server
    │
    ▼
Initialize Socket
    │
    ▼
Bind to Port 12345
    │
    ▼
Listen for Connections
    │
    ▼
┌───Accept Connection───┐
│                      │
│  ┌─New Client?───┐   │
│  │              │   │
│  │     YES      │   │
│  │     │        │   │
│  │     ▼        │   │
│  │ Create Thread│   │
│  │ for Client   │   │
│  │     │        │   │
│  │     ▼        │   │
│  │ Handle Client│   │
│  │ Messages     │   │
│  └─────────────┘   │
│                      │
└──────────────────────┘
    │
    ▼
Continue Until Stop Signal
    │
    ▼
Cleanup and EXIT
```

**Client Message Flow:**
```
START Client
    │
    ▼
Connect to Server
    │
    ▼
Send Username
    │
    ▼
┌────Start Threads────┐
│                     │
│ Send Thread    Receive Thread
│     │              │
│     ▼              ▼
│ Get User       Listen for
│ Input          Messages
│     │              │
│     ▼              ▼
│ Send to        Display
│ Server         Messages
│     │              │
│     └──────┬───────┘
│            │
└────────────┘
    │
    ▼
Disconnect and EXIT
```

---

## **Chapter 4: IMPLEMENTATION**

### **4.1. Interface/Front-End Design**

**Console Interface Design Philosophy:**
The LocalChat system employs a console-based interface designed for simplicity, universality, and efficiency. The interface utilizes color-coding and text formatting to enhance user experience within the constraints of a terminal environment.

**Design Elements:**
- **Color Scheme:** ANSI color codes for Linux and Windows console color API for Windows
- **Message Formatting:** Different colors for different message types (system messages in yellow, user messages in cyan/magenta, join/leave notifications in green/red)
- **Clear Visual Hierarchy:** Bold text for important information, regular text for messages
- **Cross-platform Compatibility:** Unified color system that works on both Linux and Windows terminals

**User Interface Components:**

**Server Interface:**
```
===== Local Chat Server =====
Server starting on port 12345
Press Enter to stop the server.
[System] Server started. Waiting for connections...
New client connected. Socket ID: 4
[Alice joined the chat]
[Alice]: Hello everyone!
[Bob joined the chat]
[Bob]: Hi Alice!
[Alice left the chat]
```

**Client Interface:**
```
===== Local Chat Client =====
Enter server IP (default 127.0.0.1): 192.168.1.100
Enter your username: Alice
Connecting to 192.168.1.100...
===== Connected to Chat Server =====
Type 'exit' to quit or 'clear' to clear screen
[Bob joined the chat]
[Bob]: Hello everyone!
Hello from Alice!
[You] Hello from Alice!
```

### **4.2. Interface/Front-End Design**

**Server-Side Architecture:**

**Socket Management:**
- Creates server socket and binds to port 12345
- Listens for incoming client connections
- Accepts connections and creates dedicated threads for each client
- Maintains vector of active client sockets with mutex protection

**Threading Model:**
- Main thread handles new connection acceptance
- Separate thread for each connected client handles message reception
- Thread-safe operations using std::mutex for shared resources
- Graceful thread cleanup on client disconnection

**Message Broadcasting System:**
- Receives messages from individual clients
- Parses username and message content
- Broadcasts formatted messages to all other connected clients
- Maintains chat history in memory for potential future features

**Client-Side Architecture:**

**Dual-Threading Approach:**
- Main thread handles user input and message sending
- Separate receive thread continuously listens for incoming messages
- Non-blocking operation ensures smooth user experience

**Connection Management:**
- Establishes TCP connection to server
- Sends username as first message for identification
- Handles connection errors and provides user feedback
- Graceful disconnection with proper socket cleanup

### **4.3. Modules/Features**

**Core Modules:**

**1. ChatServer Module (`ChatServer.hpp/cpp`):**
- Server socket initialization and configuration
- Client connection acceptance and management
- Multi-threaded client handling
- Message broadcasting functionality
- Thread-safe operations with mutex locks
- Cross-platform socket compatibility

**2. ChatClient Module (`ChatClient.hpp/cpp`):**
- Client socket creation and server connection
- Dual-threaded send/receive operations
- Message formatting and display
- User input handling
- Connection error management

**3. Console Utilities Module (`ConsoleUtils.hpp`):**
- Cross-platform color support
- Message formatting macros
- Console initialization functions
- Platform-specific implementations

**4. Main Applications:**
- `main_server.cpp`: Server application entry point
- `main_client.cpp`: Client application entry point

**Key Features Implemented:**

**1. Real-time Messaging:**
- Instant message delivery using TCP sockets
- Non-blocking send/receive operations
- Message acknowledgment and error handling

**2. Multi-user Support:**
- Concurrent client connections (limited by system resources)
- Thread-per-client architecture
- Shared resource protection with mutex locks

**3. User Management:**
- Username-based identification
- Join/leave notifications
- Client list management

**4. Cross-platform Compatibility:**
- Conditional compilation for Windows/Linux
- Platform-specific socket API handling
- Unified codebase with abstraction layer

**5. Error Handling:**
- Network connection error detection
- Graceful client disconnection handling
- Resource cleanup and memory management

**6. User Interface Features:**
- Color-coded message types
- Clear command system (exit, clear)
- Status indicators and system messages

---

## **Chapter 5: USER MANUAL**

### **5.1. System Requirements**

#### **5.1.1. Hardware Requirements**

**Minimum Hardware Configuration:**
- **Processor:** Intel Pentium 4 or AMD equivalent (1.5 GHz or higher)
- **RAM:** 512 MB minimum, 1 GB recommended
- **Storage:** 50 MB free disk space for installation
- **Network:** Ethernet adapter or Wi-Fi capability for LAN connectivity
- **Display:** Any monitor capable of displaying text (console application)

**Recommended Hardware Configuration:**
- **Processor:** Intel Core i3 or AMD equivalent (2.0 GHz or higher)
- **RAM:** 2 GB or more
- **Storage:** 100 MB free disk space
- **Network:** Gigabit Ethernet for optimal performance
- **Multiple Devices:** For testing multi-client functionality

#### **5.1.2. Software Requirements**

**For Linux (Ubuntu/Debian):**
- **Operating System:** Ubuntu 16.04 LTS or newer, Debian 9 or newer
- **Compiler:** GCC 7.0 or higher with C++11 support
- **Build Tools:** GNU Make
- **Terminal:** Any terminal emulator (GNOME Terminal, Konsole, etc.)

**Installation Commands:**
```bash
sudo apt-get update
sudo apt-get install build-essential
sudo apt-get install g++
sudo apt-get install make
sudo apt-get install git
```

**For Windows:**
- **Operating System:** Windows 7 or newer (Windows 10 recommended)
- **Compiler:** MinGW-w64 or Microsoft Visual Studio with C++ support
- **Build Tools:** Make for Windows or Visual Studio build tools
- **Terminal:** Command Prompt, PowerShell, or Windows Terminal

**Installation for Windows:**
1. Install MinGW-w64 from: https://www.mingw-w64.org/
2. Install Git for Windows from: https://git-scm.com/download/win
3. Add MinGW bin directory to system PATH

### **5.2. User Interfaces**

#### **5.2.1. Installation and Setup**

**Step 1: Download and Build**
```bash
# Clone the repository
git clone https://github.com/username/LocalChat.git
cd LocalChat

# Build the applications
make all
```

**Step 2: Verify Installation**
```bash
# Check if executables were created
ls -la server client
```

#### **5.2.2. Server Panel (Starting the Server)**

**Interface:** Server Terminal Window

**Steps to Start Server:**
1. Open terminal/command prompt
2. Navigate to LocalChat directory
3. Run the server application:
   ```bash
   # Linux
   ./server
   
   # Windows
   server.exe
   ```

**Server Interface Screenshot:**
```
===== Local Chat Server =====
Server starting on port 12345
Press Enter to stop the server.
[SYSTEM] Server started. Waiting for connections...
New client connected. Socket ID: 4
[Alice joined the chat]
[Alice]: Hello everyone!
[Bob joined the chat]
[Bob]: Hi there!
```

**Server Controls:**
- **Start:** Automatic on application launch
- **Stop:** Press Enter key
- **Monitor:** View real-time connection and message logs

#### **5.2.3. Client Panel (User Chat Interface)**

**Interface:** Client Terminal Window

**Steps to Connect:**
1. Ensure server is running
2. Open new terminal/command prompt
3. Run client application:
   ```bash
   # Linux
   ./client
   
   # Windows
   client.exe
   ```

**Client Connection Interface:**
```
===== Local Chat Client =====
Enter server IP (default 127.0.0.1): 192.168.1.100
Enter your username: Alice
Connecting to 192.168.1.100...
[SYSTEM] Connected to server successfully
===== Connected to Chat Server =====
Type 'exit' to quit or 'clear' to clear screen
```

**Chat Interface:**
```
[Bob joined the chat]
[Bob]: Hello everyone!
Hello from Alice!
[You] Hello from Alice!
[Charlie joined the chat]
[Charlie]: Good morning!
How is everyone doing?
[You] How is everyone doing?
[Bob]: Great, thanks for asking!
```

#### **5.2.4. Multi-Client Setup**

**Local Testing (Same Computer):**
1. Start server in first terminal
2. Start multiple clients in separate terminals
3. Use different usernames for each client
4. All clients will use 127.0.0.1 (localhost) as server IP

**Network Testing (Different Computers):**
1. Find server computer's IP address:
   ```bash
   # Linux
   ip addr show
   
   # Windows
   ipconfig
   ```
2. Start server on main computer
3. Configure firewall to allow port 12345
4. Connect clients using server's network IP address

#### **5.2.5. Login Credentials**

**No Authentication Required:**
- The system uses username-based identification only
- No passwords or authentication mechanisms
- Users simply provide a username when connecting
- Usernames should be unique for better identification

**Default Configuration:**
- **Server IP:** 127.0.0.1 (localhost)
- **Port:** 12345
- **Username:** User-defined during connection
- **Maximum Clients:** Limited by system resources

**Troubleshooting:**
- **Connection Refused:** Check if server is running and IP address is correct
- **Port Already in Use:** Ensure no other application is using port 12345
- **Build Errors:** Verify all dependencies are installed
- **Firewall Issues:** Allow port 12345 through system firewall

---

## **Conclusion**

The LocalChat Emergency Communication System successfully addresses the critical need for reliable local network communication during internet outages. Inspired by the internet shutdown during Bangladesh's quota reform movement in 2024, this project demonstrates a practical solution to real-world connectivity challenges while showcasing fundamental computer science concepts.

The system's implementation proves that effective communication networks can be established using existing local infrastructure, providing resilience against centralized communication failures. The project serves both as a functional tool for emergency communication and an educational resource for understanding distributed systems, network programming, and concurrent application development.

Future enhancements could include GUI development, message encryption, file sharing capabilities, and persistent message storage, making the system even more robust for emergency communication scenarios.

---

**Project Developed by:**   
**Course:** SDP-1 (Software Development Project - 1)  
**Institution:** [University Name]  
**Date:** June 2025
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

## Prerequisites

Before you begin, ensure you have the following installed:
- G++ compiler (version 7.0 or higher)
- Make build system
- POSIX-compliant operating system (Linux/Unix/Windows)
- Git (for version control)

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
- `server`: The chat server
- `client`: The chat client

## Usage

### Starting the Server

1. Open a terminal and navigate to the project directory
2. Run the server:
```bash
./server
```
3. The server will start and listen for connections on port 12345

### Starting a Client

1. Open a new terminal
2. Run the client:
```bash
./client
```
3. When prompted, enter:
   - The server's IP address (e.g., 127.0.0.1 for local testing)
   - Your username

### Chat Commands

- Send message: Simply type your message and press Enter
- Exit chat: Type 'exit' and press Enter
- Clear screen: Type 'clear' and press Enter

## Network Configuration

### Local Testing
- Server IP: 127.0.0.1
- Port: 12345

### LAN Configuration
1. Find server's IP address:
```bash
ip addr show
```
2. Configure firewall:
```bash
sudo ufw allow 12345/tcp
```

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

- Your Name <mail.owhab@gmail.com>

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
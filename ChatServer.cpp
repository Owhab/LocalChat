#include "ChatServer.hpp"
#include "ConsoleUtils.hpp"
#include <iostream>
#include <algorithm>
#include <cstring>
#include <map>
#include <sstream>

// Client information structure
struct ClientInfo
{
    std::string username;
    socket_t socket;
};

// Global map to store client info
std::map<socket_t, std::string> clientUsernames;

#ifdef _WIN32
bool ChatServer::initializeWinsock()
{
    WSADATA wsaData;
    return WSAStartup(MAKEWORD(2, 2), &wsaData) == 0;
}
#endif

ChatServer::ChatServer(int port)
{
#ifdef _WIN32
    if (!initializeWinsock())
    {
        std::cerr << "Failed to initialize Winsock\n";
        exit(1);
    }
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET)
    {
        std::cerr << "Socket creation failed with error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        exit(1);
    }
#else
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0)
    {
        std::cerr << RED_COLOR BOLD_TEXT "Socket creation failed" RESET_COLOR << std::endl;
        exit(1);
    }
#endif

    // Initialize console colors
    initConsoleColors();

    // Allow reuse of address
#ifdef _WIN32
    char opt = 1;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
#else
    int opt = 1;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
#endif

    // Try to bind to the requested port, if fails try alternative ports
    int currentPort = port;
    bool bindSuccessful = false;

    for (int attempt = 0; attempt < 10; attempt++)
    {
        sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(currentPort);
        serverAddr.sin_addr.s_addr = INADDR_ANY;

#ifdef _WIN32
        if (bind(serverSocket, (sockaddr *)&serverAddr, sizeof(serverAddr)) == 0)
        {
            bindSuccessful = true;
            break;
        }
        else
        {
            if (attempt == 0)
            {
                std::cout << YELLOW_COLOR "Port " << currentPort << " is already in use, trying alternative ports..." RESET_COLOR << std::endl;
            }
            currentPort++;
        }
#else
        if (bind(serverSocket, (sockaddr *)&serverAddr, sizeof(serverAddr)) == 0)
        {
            bindSuccessful = true;
            break;
        }
        else
        {
            if (attempt == 0)
            {
                std::cout << YELLOW_COLOR "Port " << currentPort << " is already in use, trying alternative ports..." RESET_COLOR << std::endl;
            }
            currentPort++;
        }
#endif
    }

    if (!bindSuccessful)
    {
        std::cerr << RED_COLOR BOLD_TEXT "Failed to bind to any port from " << port << " to " << (port + 9) << RESET_COLOR << std::endl;
        std::cerr << YELLOW_COLOR "Solutions:" RESET_COLOR << std::endl;
        std::cerr << "1. Kill any existing server process: " CYAN_COLOR "pkill -f server" RESET_COLOR << std::endl;
        std::cerr << "2. Wait a moment and try again" << std::endl;
        std::cerr << "3. Restart your terminal/computer" << std::endl;
#ifdef _WIN32
        closesocket(serverSocket);
        WSACleanup();
#else
        close(serverSocket);
#endif
        exit(1);
    }

    // Update the port if we had to use an alternative
    if (currentPort != port)
    {
        std::cout << GREEN_COLOR "Successfully bound to alternative port: " << currentPort << RESET_COLOR << std::endl;
        std::cout << YELLOW_COLOR "Clients should connect to port " << currentPort << " instead of " << port << RESET_COLOR << std::endl;
    }

#ifdef _WIN32
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR)
    {
        std::cerr << "Listen failed with error: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        exit(1);
    }
#else
    if (listen(serverSocket, SOMAXCONN) < 0)
    {
        std::cerr << RED_COLOR BOLD_TEXT "Listen failed" RESET_COLOR << std::endl;
        close(serverSocket);
        exit(1);
    }
#endif

    running = false;
}

ChatServer::~ChatServer()
{
    stop();
}

void ChatServer::start()
{
    running = true;
    std::cout << FORMAT_SYSTEM_MESSAGE("Server started. Waiting for connections...") << std::endl;

    while (running)
    {
#ifdef _WIN32
        socket_t clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket != INVALID_SOCKET)
#else
        socket_t clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket >= 0)
#endif
        {
            std::lock_guard<std::mutex> lock(clientsMutex);
            clientSockets.push_back(clientSocket);
            std::cout << BLUE_COLOR << "New client connected. Socket ID: " << clientSocket << RESET_COLOR << std::endl;
            std::thread(&ChatServer::handleClient, this, clientSocket).detach();
        }
    }
}

void ChatServer::handleClient(socket_t clientSocket)
{
    char buffer[1024];

    // First message from client should be username
#ifdef _WIN32
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesReceived <= 0)
    {
        return;
    }
#else
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesReceived <= 0)
    {
        return;
    }
#endif

    std::string username(buffer, bytesReceived);
    clientUsernames[clientSocket] = username;
    std::string joinMessage = "SERVER:" + username + " joined the chat";

    // Add to chat history and notify others
    chatHistory.push_back(joinMessage);
    broadcastMessage(joinMessage, clientSocket);

    std::cout << FORMAT_USER_JOIN(username) << std::endl;

    // Handle other messages
    while (running)
    {
#ifdef _WIN32
        bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0)
#else
        bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0)
#endif
        {
            break;
        }

        std::string messageContent(buffer, bytesReceived);
        std::string formattedMessage = username + ":" + messageContent;

        // Log the message to server console
        std::cout << CYAN_COLOR << "[" << username << "]: " << RESET_COLOR << messageContent << std::endl;

        // Save to chat history
        chatHistory.push_back(formattedMessage);

        // Send to other clients
        broadcastMessage(formattedMessage, clientSocket);
    }

    // Handle client disconnect
    {
        std::lock_guard<std::mutex> lock(clientsMutex);
        auto it = std::find(clientSockets.begin(), clientSockets.end(), clientSocket);
        if (it != clientSockets.end())
        {
            clientSockets.erase(it);
        }
    }

    // Get username before removing from map
    std::string disconnectedUsername = clientUsernames[clientSocket];
    std::string leaveMessage = "SERVER:" + disconnectedUsername + " left the chat";
    clientUsernames.erase(clientSocket);

    // Broadcast that user has left
    chatHistory.push_back(leaveMessage);
    broadcastMessage(leaveMessage, SOCKET_ERROR_VAL);

    std::cout << FORMAT_USER_LEAVE(disconnectedUsername) << std::endl;

#ifdef _WIN32
    closesocket(clientSocket);
#else
    close(clientSocket);
#endif
}

void ChatServer::broadcastMessage(const std::string &message, socket_t sender)
{
    std::lock_guard<std::mutex> lock(clientsMutex);
    for (socket_t client : clientSockets)
    {
        if (client != sender)
        {
            send(client, message.c_str(), message.length(), 0);
        }
    }
}

void ChatServer::stop()
{
    running = false;
    std::cout << FORMAT_SYSTEM_MESSAGE("Shutting down server...") << std::endl;

    for (socket_t client : clientSockets)
    {
#ifdef _WIN32
        closesocket(client);
#else
        close(client);
#endif
    }
    clientSockets.clear();
    clientUsernames.clear();

#ifdef _WIN32
    closesocket(serverSocket);
    WSACleanup();
#else
    close(serverSocket);
#endif
}
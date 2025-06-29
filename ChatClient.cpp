#include "ChatClient.hpp"
#include "ConsoleUtils.hpp"
#include <iostream>
#include <cstring>
#include <sstream>

#ifdef _WIN32
bool ChatClient::initializeWinsock()
{
    WSADATA wsaData;
    return WSAStartup(MAKEWORD(2, 2), &wsaData) == 0;
}
#endif

ChatClient::ChatClient()
{
#ifdef _WIN32
    if (!initializeWinsock())
    {
        std::cerr << "Failed to initialize Winsock\n";
        exit(1);
    }
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET)
    {
        std::cerr << "Socket creation failed with error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        exit(1);
    }
#else
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
#endif
    running = false;
    // Initialize console colors
    initConsoleColors();
}

ChatClient::~ChatClient()
{
    disconnect();
}

bool ChatClient::connect(const std::string &serverIP, int port)
{
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);

#ifdef _WIN32
    inet_pton(AF_INET, serverIP.c_str(), &serverAddr.sin_addr);
    if (::connect(clientSocket, (sockaddr *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        std::cerr << FORMAT_SYSTEM_MESSAGE("Connect failed with error: " + std::to_string(WSAGetLastError())) << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return false;
    }
#else
    inet_pton(AF_INET, serverIP.c_str(), &serverAddr.sin_addr);
    if (::connect(clientSocket, (sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        std::cerr << FORMAT_SYSTEM_MESSAGE("Failed to connect to server") << std::endl;
        return false;
    }
#endif

    std::cout << FORMAT_SYSTEM_MESSAGE("Connected to server successfully") << std::endl;
    running = true;
    receiveThread = std::thread(&ChatClient::receiveMessages, this);
    return true;
}

void ChatClient::receiveMessages()
{
    char buffer[1024];
    while (running)
    {
#ifdef _WIN32
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0)
        {
            break;
        }
#else
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0)
        {
            break;
        }
#endif
        std::string rawMessage(buffer, bytesReceived);

        // Parse message to get username and content
        size_t colonPos = rawMessage.find(':');
        if (colonPos != std::string::npos)
        {
            std::string username = rawMessage.substr(0, colonPos);
            std::string messageContent = rawMessage.substr(colonPos + 1);

            // Special system messages
            if (username == "SERVER")
            {
                if (messageContent.find("joined") != std::string::npos)
                {
                    std::cout << FORMAT_USER_JOIN(messageContent) << std::endl;
                }
                else if (messageContent.find("left") != std::string::npos)
                {
                    std::cout << FORMAT_USER_LEAVE(messageContent) << std::endl;
                }
                else
                {
                    std::cout << FORMAT_SYSTEM_MESSAGE(messageContent) << std::endl;
                }
                // Add separator line after system messages
                std::cout << createSeparator() << std::endl;
            }
            else
            {
                // Regular message from another user with colorful border
                std::cout << formatReceivedMessage(username, messageContent) << std::endl;
                std::cout << createSeparator() << std::endl;
            }
        }
        else
        {
            // If message format is unexpected, print as is
            std::cout << YELLOW_COLOR << rawMessage << RESET_COLOR << std::endl;
        }
    }

    std::cout << FORMAT_SYSTEM_MESSAGE("Disconnected from server") << std::endl;
}

void ChatClient::sendMessage(const std::string &message)
{
    // No need to format here since it will be formatted when echoed back
    send(clientSocket, message.c_str(), message.length(), 0);

    // Display the message locally with styling and border
    std::cout << FORMAT_SENT_MESSAGE("You", message) << std::endl;
    std::cout << createSeparator() << std::endl;
}

void ChatClient::disconnect()
{
    running = false;
    if (receiveThread.joinable())
    {
        receiveThread.join();
    }
#ifdef _WIN32
    closesocket(clientSocket);
    WSACleanup();
#else
    close(clientSocket);
#endif
}

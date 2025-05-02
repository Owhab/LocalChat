#include "ChatClient.hpp"
#include <iostream>
#include <cstring>

ChatClient::ChatClient()
{
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    running = false;
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
    inet_pton(AF_INET, serverIP.c_str(), &serverAddr.sin_addr);

    if (::connect(clientSocket, (sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        return false;
    }

    running = true;
    receiveThread = std::thread(&ChatClient::receiveMessages, this);
    return true;
}

void ChatClient::receiveMessages()
{
    char buffer[1024];
    while (running)
    {
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0)
        {
            break;
        }
        std::string message(buffer, bytesReceived);
        std::cout << message << std::endl;
    }
}

void ChatClient::sendMessage(const std::string &message)
{
    send(clientSocket, message.c_str(), message.length(), 0);
}

void ChatClient::disconnect()
{
    running = false;
    if (receiveThread.joinable())
    {
        receiveThread.join();
    }
    close(clientSocket);
}

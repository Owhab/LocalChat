#include "ChatServer.hpp"
#include <iostream>
#include <algorithm>
#include <cstring>

ChatServer::ChatServer(int port)
{
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Allow reuse of address
    int opt = 1;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    bind(serverSocket, (sockaddr *)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, SOMAXCONN);

    running = false;
}

ChatServer::~ChatServer()
{
    stop();
}

void ChatServer::start()
{
    running = true;
    std::cout << "Server started. Waiting for connections...\n";

    while (running)
    {
        int clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket >= 0)
        {
            std::lock_guard<std::mutex> lock(clientsMutex);
            clientSockets.push_back(clientSocket);
            std::thread(&ChatServer::handleClient, this, clientSocket).detach();
        }
    }
}

void ChatServer::handleClient(int clientSocket)
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
        chatHistory.push_back(message);
        broadcastMessage(message, clientSocket);
    }

    std::lock_guard<std::mutex> lock(clientsMutex);
    auto it = std::find(clientSockets.begin(), clientSockets.end(), clientSocket);
    if (it != clientSockets.end())
    {
        clientSockets.erase(it);
    }
    close(clientSocket);
}

void ChatServer::broadcastMessage(const std::string &message, int sender)
{
    std::lock_guard<std::mutex> lock(clientsMutex);
    for (int client : clientSockets)
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
    for (int client : clientSockets)
    {
        close(client);
    }
    close(serverSocket);
}
// ChatServer.hpp
#pragma once
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

class ChatServer
{
private:
    int serverSocket;
    std::vector<int> clientSockets;
    std::vector<std::string> chatHistory;
    std::mutex clientsMutex;
    bool running;

    void handleClient(int clientSocket);
    void broadcastMessage(const std::string &message, int sender);

public:
    ChatServer(int port);
    ~ChatServer();
    void start();
    void stop();
};
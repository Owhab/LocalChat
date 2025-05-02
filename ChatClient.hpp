#pragma once
#include <string>
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

class ChatClient
{
private:
    int clientSocket;
    std::thread receiveThread;
    bool running;

    void receiveMessages();

public:
    ChatClient();
    ~ChatClient();
    bool connect(const std::string &serverIP, int port);
    void sendMessage(const std::string &message);
    void disconnect();
};
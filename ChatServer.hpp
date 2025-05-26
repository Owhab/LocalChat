// ChatServer.hpp
#pragma once
#include <vector>
#include <string>
#include <thread>
#include <mutex>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
typedef SOCKET socket_t;
#define SOCKET_ERROR_VAL INVALID_SOCKET
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
typedef int socket_t;
#define SOCKET_ERROR_VAL -1
#endif

class ChatServer
{
private:
    socket_t serverSocket;
    std::vector<socket_t> clientSockets;
    std::vector<std::string> chatHistory;
    std::mutex clientsMutex;
    bool running;

    void handleClient(socket_t clientSocket);
    void broadcastMessage(const std::string &message, socket_t sender);

#ifdef _WIN32
    static bool initializeWinsock();
#endif

public:
    ChatServer(int port);
    ~ChatServer();
    void start();
    void stop();
};
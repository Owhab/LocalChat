#pragma once
#include <string>
#include <thread>

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

class ChatClient
{
private:
    socket_t clientSocket;
    std::thread receiveThread;
    bool running;

    void receiveMessages();

#ifdef _WIN32
    static bool initializeWinsock();
#endif

public:
    ChatClient();
    ~ChatClient();
    bool connect(const std::string &serverIP, int port);
    void sendMessage(const std::string &message);
    void disconnect();
};
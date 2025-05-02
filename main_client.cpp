#include "ChatClient.hpp"
#include <iostream>
#include <string>

int main()
{
    ChatClient client;

    std::cout << "Enter server IP: ";
    std::string serverIP;
    std::getline(std::cin, serverIP);

    std::cout << "Enter your username: ";
    std::string username;
    std::getline(std::cin, username);

    if (!client.connect(serverIP, 12345))
    {
        std::cout << "Failed to connect to server.\n";
        return 1;
    }

    std::cout << "Connected to server. Start chatting:\n";

    std::string message;
    while (std::getline(std::cin, message))
    {
        if (message == "exit")
        {
            break;
        }
        client.sendMessage(username + ": " + message);
    }

    return 0;
}
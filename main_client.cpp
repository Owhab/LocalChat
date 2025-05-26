#include "ChatClient.hpp"
#include "ConsoleUtils.hpp"
#include <iostream>
#include <string>

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main()
{
    // Initialize console colors
    initConsoleColors();

    std::cout << YELLOW_COLOR BOLD_TEXT "===== Local Chat Client =====" RESET_COLOR << std::endl;

    ChatClient client;

    std::cout << CYAN_COLOR "Enter server IP" RESET_COLOR << " (default 127.0.0.1): ";
    std::string serverIP;
    std::getline(std::cin, serverIP);
    if (serverIP.empty())
    {
        serverIP = "127.0.0.1";
    }

    std::cout << CYAN_COLOR "Enter your username: " RESET_COLOR;
    std::string username;
    std::getline(std::cin, username);
    while (username.empty())
    {
        std::cout << RED_COLOR "Username cannot be empty! Try again: " RESET_COLOR;
        std::getline(std::cin, username);
    }

    std::cout << YELLOW_COLOR "Connecting to " << serverIP << "..." RESET_COLOR << std::endl;
    if (!client.connect(serverIP, 12345))
    {
        std::cout << RED_COLOR BOLD_TEXT "Failed to connect to server." RESET_COLOR << std::endl;
        return 1;
    }

    // Send username to server as first message
    client.sendMessage(username);

    clearScreen();
    std::cout << GREEN_COLOR BOLD_TEXT "===== Connected to Chat Server =====" RESET_COLOR << std::endl;
    std::cout << YELLOW_COLOR "Type 'exit' to quit or 'clear' to clear screen" RESET_COLOR << std::endl;

    std::string message;
    while (std::getline(std::cin, message))
    {
        if (message == "exit")
        {
            std::cout << YELLOW_COLOR "Disconnecting from server..." RESET_COLOR << std::endl;
            break;
        }
        else if (message == "clear")
        {
            clearScreen();
            std::cout << GREEN_COLOR BOLD_TEXT "===== Connected to Chat Server =====" RESET_COLOR << std::endl;
            std::cout << YELLOW_COLOR "Type 'exit' to quit or 'clear' to clear screen" RESET_COLOR << std::endl;
            continue;
        }

        // No need to add username here as the server handles it with the stored username
        client.sendMessage(message);
    }

    return 0;
}
#include "ChatServer.hpp"
#include "ConsoleUtils.hpp"
#include <iostream>
#include <string>
#include <thread>

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

    clearScreen();
    std::cout << BLUE_COLOR BOLD_TEXT "===== Local Chat Server =====" RESET_COLOR << std::endl;

    int port = 12345;
    ChatServer server(port);

    std::cout << BLUE_COLOR "Server starting on port " << port << RESET_COLOR << std::endl;
    std::cout << YELLOW_COLOR "Press Enter to stop the server." RESET_COLOR << std::endl;

    // Start server in a separate thread
    std::thread serverThread([&server]()
                             { server.start(); });

    // Wait for Enter key to stop the server
    std::cin.get();

    std::cout << RED_COLOR "Stopping server..." RESET_COLOR << std::endl;
    server.stop();

    if (serverThread.joinable())
    {
        serverThread.join();
    }

    std::cout << GREEN_COLOR "Server stopped successfully." RESET_COLOR << std::endl;

    return 0;
}